{\rtf1\ansi\ansicpg1252\cocoartf1404\cocoasubrtf470
{\fonttbl\f0\fnil\fcharset0 Monaco;}
{\colortbl;\red255\green255\blue255;\red38\green38\blue38;\red242\green242\blue242;}
\margl1440\margr1440\vieww10800\viewh8400\viewkind0
\deftab720
\pard\pardeftab720\partightenfactor0

\f0\fs26 \cf2 \cb3 \expnd0\expndtw0\kerning0
all: lib\cb1 \
\
\cb3 lib: libMain.o LibraryItem.o Book.o Album.o Movie.o Patron.o Library.o\cb1 \
	\cb3 g++ -g libMain.o \cf2 \cb3 LibraryItem.o Book.o Album.o Movie.o Patron.o Library.o\cf2 \cb3  -o lib\cb1 \
\
\cb3 libMain.o: LibraryItem.hpp \cf2 \cb3 Book.hpp Movie.hpp Patron.hpp Library.hpp\cf2 \cb1 \
	\cb3 g++ -c libMain.cpp\cb1 \
\
\cb3 LibraryItem.o: LibraryItem.cpp LibraryItem.hpp \cf2 \cb3 Book.hpp Movie.hpp Patron.hpp Library.hpp\cf2 \cb1 \
	\cb3 g++ -c LibraryItem.cpp\
\
\pard\pardeftab720\partightenfactor0
\cf2 \cb3 Book.o: Book.cpp Book.hpp Movie.hpp Patron.hpp Library.hpp\cb1 \
	\cb3 g++ -c Book.cpp\
\pard\pardeftab720\partightenfactor0
\cf2 \cb3 \
\
\pard\pardeftab720\partightenfactor0
\cf2 \cb3 Album.o: Album.cpp Album.hpp Movie.hpp Patron.hpp Library.hpp\cb1 \
	\cb3 g++ -c Album.cpp\
\pard\pardeftab720\partightenfactor0
\cf2 \cb3 \
\
\pard\pardeftab720\partightenfactor0
\cf2 \cb3 Movie.o: Movie.cpp Movie.hpp Patron.hpp Library.hpp\cb1 \
	\cb3 g++ -c Movie.cpp\cf2 \cb3 \
\
\cf2 \cb3 Patron.o: Patron.cpp Patron.hpp Library.hpp\cb1 \
	\cb3 g++ -c Patron.cpp\cf2 \cb1 \
\
\pard\pardeftab720\partightenfactor0
\cf2 \cb3 Library.o: Library.cpp Library.hpp\cb1 \
	\cb3 g++ -c Library.cpp\cb1 \
\
\
\cb3 clean:\cb1 \
\cb3 \'a0\'a0\'a0\'a0 \'a0\'a0\'a0 \'a0rm -f *.o}