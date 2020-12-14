/**
 * Date : 2020/12/15
 * Author : Yi-Ying-Lin
 * 
 */ 

#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "server_ip_port.h"

class CLIENT{
	public:
		int serverPortNum ;
		const char *server_ip ;

		int clientSocketfd ;

		struct sockaddr_in serverSocAddr ;
		in_addr_t server_IP_Addr ;

		CLIENT(const char *server_ip_num ,int portNum) ;
		~CLIENT() ;
		int createSocket() ;
		int SocketConnect(int client_socket_fd ,struct sockaddr_in *server_Soc_Addr) ;
		int sendRequest(const char *data);
		int socketReadTest() ;


		std::string readStrData(int client_fd ,int readBufSize) ;
		void writeStrToFile(std::string data ,std::string path) ;
		void receiveHtmlFile(int client_fd ,int readBufSize ,std::string path);

		//image related
		char imgBuf[BUF_SIZE] ;
		int readData(int client_fd ,unsigned char *buf);
		void receiveImageFile(int client_fd ,std::string output_path);
};




#endif