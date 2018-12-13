#ifndef SERIAL_ARDUINO
#define SERIAL_ARDUINO

// **************** //
// **** INCLUDE *** //
// **************** //
//#include <stdio.h>
//#include <time.h>
//#include <math.h>
//#include <string.h>
//#include <sstream>
//#include <cstdint>
//#include <iostream>
//#include <unistd.h>
#include "stdafx.h"



#ifdef _WIN32
	#include <winsock2.h>
#elif __unix__
	#include <sys/types.h>
	#include <sys/time.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <unistd.h>
	#include <stdlib.h> 
	#include <fcntl.h>
	#include <errno.h>
	#include <termios.h>
typedef int SOCKET;
typedef unsigned int socklen_t;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
	#define INVALID_SOCKET -1
	#define SOCKET_ERROR -1
	#define closesocket(s) close(s)
	#define WSAGetLastError() errno
#endif



#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()


// prototypes ******************************************
int initializeSerialPort(void);
void readSerialPort(int &serialConnection);
int writeIntToSerialPort(int &serialConnection, int val);
void testArduinoOutput(int &serialConnection);
void testServoCommands(int &serialConnection);




#endif
