/**
 * Date : 2020/12/15
 * Author : Yi-Ying-Lin
 * 
 */ 

#include <iostream>
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

#include <ctime>


#include "client.h"



CLIENT::CLIENT(const char *server_ip_num ,int portNum){
	this->server_ip = server_ip_num ;
	this->serverPortNum = portNum ;
	this->clientSocketfd = -1 ;

	this->clientSocketfd = this->createSocket() ;

	if(this->SocketConnect(this->clientSocketfd ,&this->serverSocAddr) < 0)
	{
		exit(-1) ;
	} 
	
}

CLIENT::~CLIENT(){
	/*關閉socket*/
	close(this->clientSocketfd) ;
}


int CLIENT::createSocket(){
	/**
	 * int socket(int domain, int type, int protocol) :
	 * arg1 : int domain ,有 
	 * 		AF_UNIX ,	透過kernal內通訊 ,addr structure為 sockaddr_un
	 * 		AF_INIT ,	使用ipv4 ,addr structure為 sockaddr_in
	 * 		AF_INET6,	使用ipv6 ,addr structure為 sockaddr_in6
	 * 
	 * arg2 : int type ,有
	 * 		SOCK_STREAM : TCP
	 * 		SOCK_DGRAM : UDP
	 * arg3 : int protocol
	 * 		通常設為0
	 * return : int資料型態, 為socket的檔案描述符號
	 */
	int client_socket_fd = socket(AF_INET ,SOCK_STREAM , 0) ;

	//string serverName ="localhost" ;
	//struct hostent *server = gethostbyname(serverName.data());
	//bcopy((char *)server->h_addr,(char *)&serverSocAddr.sin_addr.s_addr, server->h_length);

	/**
	 * void bzero(void *s, int n);
	 * 將 s開始的記憶體位址之後的n bytes, 清空
	 */ 
	bzero(&this->serverSocAddr ,sizeof(this->serverSocAddr)) ;

	/**
	 * 這邊設定想連線到的server端的sockaddr_in結構
	 * 
	 * 結構sockaddr_in的成員
	 * sin_family : domain
	 * sin_port : port number
	 * struct sin_addr
	 * 			struct sin_addr 只有一個成員 s_addr : ip addr(網路的binary形式)
	 * 
	 * uint16_t htons(uint16_t hostshort) : 將ipv4的port number轉換為網路形式
	 */ 	
	this->serverSocAddr.sin_family = AF_INET ;
	this->serverSocAddr.sin_port = htons((unsigned int)serverPortNum) ;

	/**
	 * unsigned long int inet_addr(const char *cp);
	 * 
	 * arg : const char *cp :為一般 ip格式
	 * return : 將一般在使用的ip格式轉換為 網路使用的binary格式, 失敗則回傳-1
	 */ 
	this->serverSocAddr.sin_addr.s_addr = inet_addr(server_ip) ;

	return client_socket_fd ;
}


int CLIENT::SocketConnect(int client_socket_fd ,struct sockaddr_in *server_Soc_Addr){
	/**
	 * 連線到對方socket(server)
	 * int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
	 * 
	 * arg1 : client自己的fd
	 * arg2 : 對方(server)的sockaddr結構
	 * arg3 : 對方(server)的sockaddr結構的長度
	 * return : 0為成功 ,-1為失敗
	 */ 
	int connectRTN = connect(client_socket_fd ,(struct sockaddr *)server_Soc_Addr ,sizeof(*server_Soc_Addr)) ;
	if(connectRTN != 0){
		perror("Connect to server error!") ;
		close(client_socket_fd) ;
		exit(0) ;
		return -1 ;
	}
	return 0 ;
}



int CLIENT::sendRequest(const char *data){
	/* 寫資料到Server端 */
	const char *writeBuf = data ;
	std::cout << "Send data to Server : " << writeBuf << std::endl ;

	int writeRTN = write(clientSocketfd ,writeBuf ,strlen(writeBuf)) ;

	if(writeRTN < 0){
		perror("Error,can't write data to Server.") ;
		
		close(clientSocketfd) ;
		return -1 ;
	}
	return 0 ;
}




int CLIENT::socketReadTest(){
	/* 從Server端接收資料 */
	char clientReadBuf[16] = {0} ;

	int readRTN = read(clientSocketfd ,clientReadBuf ,sizeof(clientReadBuf)) ;

	if(readRTN < 0){
		perror("Error,can't read data from Server.") ;
		
		close(clientSocketfd) ;
		return -1 ;
	}

	std::cout << "Read from Server : " << clientReadBuf << std::endl ;
	return 0 ;
}

std::string CLIENT::readStrData(int client_fd ,int readBufSize){
	char clientReadBuf[readBufSize] = {0} ;
	std::string linebuf ;
	std::string str ;
	std::stringstream ss ;


	int rtn = read(client_fd ,clientReadBuf ,readBufSize) ;

	if(rtn < 0){
		perror("Error,can't read data from Server.") ;
		close(client_fd) ;
		return "-1" ;
	}

	ss << clientReadBuf ;

	while(getline(ss, linebuf))
    {
		str += linebuf ;
		str += "\n" ;
    }

	std::cout << "Read from Server :" << str << std::endl ;

	return str ;	
}

void CLIENT::writeStrToFile(std::string data ,std::string path){

	std::cout << path << std::endl ;

    std::fstream fs;

    fs.open(path.c_str() ,std::fstream::out) ;

    if(fs.is_open()){
        fs << data ;

    }else{
        std::cout << "Can't open file!" << std::endl ;
    }
    
    /** close file*/
    fs.close() ;

}


void CLIENT::receiveHtmlFile(int client_fd ,int readBufSize ,std::string path)
{
	this->writeStrToFile(this->readStrData(client_fd ,readBufSize) ,path) ; 

}


int CLIENT::readData(int client_fd ,unsigned char *buf){

	//memset(buf, 0, size);
	int rtn = read(client_fd ,buf ,BUF_SIZE) ;

	if(rtn < 0){
		perror("Error,can't read data from Server.") ;
		close(client_fd) ;
		return -1 ;
	}
	return 0 ;
}

/**
 * jpg image 第一跟第二個byte須為 : 0xffd8
 * jpg image 最後兩個byte須為 : 0xffd9
 */ 
void CLIENT::receiveImageFile(int client_fd ,std::string output_path){
	//workaround
	usleep(100000) ;

	unsigned char *buf = new unsigned char[BUF_SIZE] ;
	memset(buf, 0, BUF_SIZE);

	this->readData(client_fd ,buf) ;

    std::fstream fs ;
    fs.open(output_path.c_str() ,std::fstream::binary | std::fstream::out) ;
    fs.write((const char *)buf ,BUF_SIZE) ;
	delete buf ;
}