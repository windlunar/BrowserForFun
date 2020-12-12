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
		SERVER(int portNum ,std::string html_path);
		~SERVER();

		int ServerPortNum ;

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

		std::string html_file_path ;

};




#endif