To Test or To Use:


Run 'make' to build.


    (1) Run ftserver on given port.
    (2) Run ftclient by passing IP address and port number of ftserver,
        then list (-l) or get (-g) command, with filename, and data port.
    (3) Repeat (2) for additional requests.

To Quit: 

    - SIGINT terminates once action complete.



Command line formats:

        <server-hostname> - IP address of server (dotted-quad or domain name)

        <server-port>     - must be in range [1024, 65535]

        -l|-g             - file listing (-l) or file transfer (-g) command

        <filename>        - file to transfer from server to client

        <data-port>       - must be in range [1024, 65535]



ftclient.py:

    usage: python2 ftclient.py <server-hostname> <server-port> -l|-g
                               [<filename>] <data-port>

        
ftserver.c:

    Run 'make' to build.


    usage: ./ftserver <server-port>

      

TESTED: FLIP OSU

- ftserver & ftclient must be in different directories
- each must be run on different flip servers (ex: flip2 & flip3)



Example:

-bash-4.2$ make
gcc -std=gnu99 -c ftserver.c
gcc ftserver.o -o ftserver
-bash-4.2$ ./ftserver 44444
ftserver: FTP server open on port 44444



ftserver: FTP control connection established with "128.193.36.41"
  Receiving data port (FTP active mode) ...
  Receiving command ...
  Transmitting data-connection go-ahead ...
ftserver: FTP data connection established with "128.193.36.41"
  Transmitting file listing ...
  Transmitting connection-termination go-ahead ...
ftserver: FTP data connection closed
^C
ftserver closed



-bash-4.2$ python2 ftclient.py flip2 44444 -l 44460
ftclient: FTP control connection established with "128.193.54.182"
  Transmitting data port (FTP active mode) ...
  Transmitting command ...
ftclient: FTP data connection established with "128.193.54.182"
ftclient: File listing on "128.193.54.182"
  ftserver.o
  README.txt
  makefile
  ftserver.c
  ftserver




-bash-4.2$ python2 ftclient.py flip2 44444 -g README.txt 44469
ftclient: FTP control connection established with "128.193.54.182"
  Transmitting data port (FTP active mode) ...
  Transmitting command ...
ftclient: FTP data connection established with "128.193.54.182"
ftclient: File transfer complete
ftclient: FTP control connection closed
