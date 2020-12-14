#ifndef _SERVER_H_
#define _SERVER_H


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

#include "common.h"

/**
 * (Server)					(client)
 * 
 * socket()					socket()
 * 
 * bind()
 * 
 * listen()
 * 
 * accept()
 * 					<-----	connect()
 * 
 * read() or write()		write() or read()
 * 
 * close()					close()
 */ 
class SERVER{
	public:
		SERVER(const char *server_ip ,int portNum);
		~SERVER();

		int ServerPortNum ;
		const char * server_ip_num ;

		int serverfd ;
		struct sockaddr_in serverSocAddr ;
		in_addr_t server_IP_Addr ;

		//連接過來的客戶端 ip
		int clientfd ;
		struct sockaddr_in clientSocAddr ;

		int socketCreate() ;
		int socketBind(int socked_fd ,struct sockaddr_in *server_Soc_Addr) ;
		void socketListen(int server_fd) ;
		int socketAccept(int server_fd ,struct sockaddr_in *client_Soc_Addr ) ;
		int socketReadTest(int server_fd ,int client_fd) ;
		int socketWriteTest(int server_fd ,int client_fd) ;


		std::string openHtmlFile(std::string htmlPath) ;
		int writeStrData(int server_fd ,int client_fd ,std::string data) ;
		int sendHtmlFile(int server_fd ,int client_fd ,std::string htmlPath);




		//Send image
		char imgBuf[BUF_SIZE] ;
		int openImgFile(std::string file_name) ;
		int writeImgData(int server_fd ,int client_fd ,int Size);
		int sendImgFile(int server_fd ,int client_fd ,std::string file_name) ;

};




#endif