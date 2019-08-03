# -*- coding: utf-8 -*-

# Chris Darnell
# Project #2
# Description: ftclient.py

# Full descrip/sources in ftserver.c



import os                      
import re                      
import sys                      
from socket import (  # Sockets API used, from assignment prompt          
    socket,
    gethostbyname,
    AF_INET,
    SOCK_STREAM,
    SOL_SOCKET,
    SO_REUSEADDR
)
from struct import pack, unpack 

QUE_SIZE = 6 
TAG_SIZE = 8  

def main():
    # Command-line arg. used
    global serverHost
    global serverPort
    global command
    global filename
    global dataPort

  
    if len(sys.argv) not in (5, 6):
        print (
            "To use: python2 ftclient <server-hostname> <server-port> " +
            "-l|-g [<filename>] <data-port>"
        )
        sys.exit(1)
    serverHost = gethostbyname(sys.argv[1])
    serverPort = sys.argv[2]
    command = sys.argv[3]
    filename = sys.argv[4] if len(sys.argv) == 6 else None
    dataPort = sys.argv[5] if len(sys.argv) == 6 else sys.argv[4]

    # Get command/filename check
    if command == "-g" and filename is None:
        print (
            "To use: python2 ftclient <server-hostname> <server-port> " +
            "-l|-g [<filename>] <data-port>"
        )
        sys.exit(1)

    # Server port = integer check 
    if not checkIfInteger(serverPort):
        print "ERROR: ftclient: Server port must be integer"
        sys.exit(1)
    serverPort = int(serverPort)

    # Server port in range [1024, 65535] check
    if int(serverPort) < 1024 or int(serverPort) > 65535:
        print "ERROR: ftclient: Server port must be in range [1024, 65535]"
        sys.exit(1)

    # Command either -l (list) or -g (get) check
    if command not in ("-l", "-g"):
        print "ERROR: ftclient: Command must be -l or -g"
        sys.exit(1)

    # Data port an integer check.
    if not checkIfInteger(dataPort):
        print "ERROR: ftclient: Data port must be integer"
        sys.exit(1)
    dataPort = int(dataPort)

    # Data port in range [1024, 65535] check.
    if int(dataPort) < 1024 or int(dataPort) > 65535:
        print "ERROR: ftclient: Data port must be in range [1024, 65535]"
        sys.exit(1)

    # Server/data port no match check
    if serverPort == dataPort:
        print "ERROR: ftclient: Server/data port cannot match"
        sys.exit(1)

    # Start connection if all is good.
    startFtpClient()

    sys.exit(0)



def checkIfInteger(string):
    # Compare against int check
    return re.match("^[0-9]+$", string) is not None



def dataReceiver(socket, numberofBytes):
    # Get number bytes.
    data = "";
    while len(data) < numberofBytes:
        try:
            data += socket.recv(numberofBytes - len(data))
        except Exception as e:
            print e.strerror
            sys.exit(1);

    return data


# Receive packet from socket

def packetReceiver(socket):
    # Receive packet length.
    packetLength = unpack(">H", dataReceiver(socket, 2))[0]

    # Receive tag.
    tag = dataReceiver(socket, TAG_SIZE).rstrip("\0")

    # Receive data.
    data = dataReceiver(socket, packetLength - TAG_SIZE - 2)

    return tag, data


def runSess(controlSocket):
    # Send data port to server.
    print "  Sending port to server..."
    tagSent = "DPORT"
    dataSent = str(dataPort)
    packetSender(controlSocket, tagSent, dataSent)

    # Send command to server.
    print "  Sending command to server ..."
    tagSent = "NULL"
    dataSent = ""
    if command == "-l":
        tagSent = "LIST"
    elif command == "-g":
        tagSent = "GET"
        dataSent = filename
    packetSender(controlSocket, tagSent, dataSent)

    # Receive server's response.
    tagReceive, dataReceive = packetReceiver(controlSocket)

    # Server error...
    if tagReceive == "ERROR":
        print "ftclient: " + dataReceive
        return -1
    return 0



# Transfer file - FTP data connection.



def runData(controlSocket, dataSocket):
    ret = 0 

    # Retrieve first packet from server.
    tagReceive, dataReceive = packetReceiver(dataSocket)

    # List filenames
    if tagReceive == "FNAME":
        print "ftclient: File listing for \"{0}\"".format(serverHost, serverPort)

        # Print filenames.
        while tagReceive != "DONE":
            print "  " + dataReceive
            tagReceive, dataReceive = packetReceiver(dataSocket)

    # File transferred...
    elif tagReceive == "FILE":
        filename = dataReceive
        if os.path.exists(filename):
           print "ftclient: ERROR: File \"{0}\" exists".format(filename)
           ret = -1

        # Write received data...
        else:
            with open(filename, "w") as outfile:
                while tagReceive != "DONE":
                    tagReceive, dataReceive = packetReceiver(dataSocket)
                    outfile.write(dataReceive)
            print "ftclient: File transfer complete"

    # Error...
    else:
        ret = -1

    # ...or ack
    packetSender(controlSocket, "ACK", "")

    return ret



# Sends packet from socket.

def packetSender(socket, tag = "", data = ""):
    # Determine packet length.
    packetLength = 2 + TAG_SIZE + len(data)

    # Build packet.
    packet = pack(">H", packetLength)
    packet += tag.ljust(TAG_SIZE, "\0")
    packet += data

    # Send packet to server.
    try:
        socket.sendall(packet)
    except Exception as e:
        print e.strerror
        sys.exit



# Start FTP connect between client/server.

def startFtpClient():
    # Client-side endpoint
    try:
        controlSocket = socket(AF_INET, SOCK_STREAM, 0)
    except Exception as e:
        print e.strerror
        sys.exit(1)

    # Establish FTP connection.
    try:
        controlSocket.connect((serverHost, serverPort))
    except Exception as e:
        print e.strerror
        sys.exit(1)
    print ("ftclient: FTP connection established with " +
           "\"{0}\"".format(serverHost, serverPort)          )

    # Communicate over connection.
    status = runSess(controlSocket)

    # Accept FTP data
    if status != -1:
        # Create client socket.
        try:
            clientSocket = socket(AF_INET, SOCK_STREAM, 0)
        except Exception as e:
            print e.strerror
            sys.exit(1)

        # Bind client socket port.
        try:
            clientSocket.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
            clientSocket.bind(("", dataPort))
        except Exception as e:
            print e.strerror
            sys.exit(1)

        # Listen for connect.
        try:
            clientSocket.listen(QUE_SIZE)
        except Exception as e:
            print e.strerror
            sys.exit(1)

        # Establish FTP connection.
        try:
            dataSocket = clientSocket.accept()[0]
        except Exception as e:
            print e.strerror
            sys.exit(1)
        print ("ftclient: FTP data connection established with " +
               "\"{0}\"".format(serverHost)                       )

        # Transfer file info or...
        runData(controlSocket, dataSocket)

        # ...Display error messages
        while True:
            tagReceive, dataReceive = packetReceiver(controlSocket)
            if tagReceive == "ERROR":
                print "ftclient: " + dataReceive
            if tagReceive == "CLOSE":
                break

    # Close FTP connection/socket.
    try:
        controlSocket.close()
    except Exception as e:
        print e.strerror
        sys.exit(1)
    print "ftclient: FTP connection closed"


# Start.
if __name__ == "__main__":
    main()