
#include "server.h"

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



SERVER::SERVER(int portNum ,std::string html_path){
	this->html_file_path = html_path ;
	this->serverfd = -1 ;
	this->clientfd = -1 ;
	this->ServerPortNum = portNum ;
	
	this->serverfd = this->socketCreate() ;
	this->socketBind(this->serverfd ,&this->serverSocAddr) ;
	this->socketListen(this->serverfd);

}

SERVER::~SERVER(){
	close(this->serverfd) ;
	close(this->clientfd) ;
}


int SERVER::socketCreate(){
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
	int socketfd = socket(AF_INET, SOCK_STREAM, 0) ;
	
	/**
	 * unsigned long int inet_addr(const char *cp);
	 * 
	 * arg : const char *cp :為一般 ip格式
	 * return : 將一般在使用的ip格式轉換為 網路使用的binary格式, 失敗則回傳-1
	 */ 
	if(this->server_IP_Addr = inet_addr(SERVER_IP) == -1){
		perror("Setting IP error!") ;
		close(socketfd) ;
		return -1 ;
	}

	/**
	 * void bzero(void *s, int n);
	 * 將 s開始的記憶體位址之後的n bytes, 清空
	 */ 
	bzero(&this->serverSocAddr ,sizeof(this->serverSocAddr)) ;

	/**
	 * 結構sockaddr_in的成員
	 * sin_family : domain
	 * sin_port : port number
	 * struct sin_addr
	 * 			struct sin_addr 只有一個成員 s_addr : ip addr(網路的binary形式)
	 * 
	 * uint16_t htons(uint16_t hostshort) : 將ipv4的port number轉換為網路形式
	 */ 
	this->serverSocAddr.sin_family = AF_INET ;
	this->serverSocAddr.sin_port = htons(this->ServerPortNum) ;
	this->serverSocAddr.sin_addr.s_addr = this->server_IP_Addr ; /*INADDR_ANY*/

	return socketfd ;
}



int SERVER::socketBind(int server_fd ,struct sockaddr_in *server_Soc_Addr){
	//Bind error!: Address already in use
	/**
	 * int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
	 * 將socket綁訂到固定的ip
	 * arg1 : socket()回傳的檔案描述符
	 * arg2 : sockaddr結構 ,以ipv4來說為 sockaddr_in
	 * arg3 : sockaddr結構的長度
	 * return : 0為成功 ,-1為失敗
	 */ 
	int bindRTN = bind(server_fd ,(struct sockaddr *)server_Soc_Addr ,sizeof(*server_Soc_Addr)) ;
	if( bindRTN != 0){
		perror("Bind error!") ;
		close(server_fd) ;
		return -1 ;
	}
}

void SERVER::socketListen(int server_fd){
	/**
	 * int listen(int sockfd ,int backlog)
	 * 將socket標示為被動式, 可用來接受client socket的連線
	 */ 
	listen(server_fd ,5) ;
}


int SERVER::socketAccept(int server_fd ,struct sockaddr_in *client_Soc_Addr ){
	/**
	 * int accept(int sockfd, const struct sockaddr *addr, socklen_t *addrlen)
	 * 接受連線
	 * arg1 : server socket的fd
	 * arg2 : 要接受的client端的sockaddr結構
	 * arg3 : 要接受的client端的sockaddr結構的長度
	 * return : 代表client端的檔案描述符 ,之後用此fd與client端溝通 ,回傳-1為失敗
	 */ 
	socklen_t clientSocLen = sizeof(*client_Soc_Addr) ;
	int client_fd = accept(server_fd ,(struct sockaddr *)client_Soc_Addr ,&clientSocLen ) ;
	if( client_fd < 0){
		perror("accept error!") ;
		close(server_fd) ;
		return -1 ;
	}

	return client_fd ;
}

int SERVER::socketReadTest(int server_fd ,int client_fd){
	/* 從client端接收資料 */	
	char readBuf[16] = {0} ;
	int readRTN = read(client_fd ,readBuf ,sizeof(readBuf)) ;
	if(readRTN < 0){
		perror("Error,can't read data from client.") ;
		close(server_fd) ;		
		return -1 ;
	}
	std::cout << "Read from client : " << readBuf << std::endl ;
}


int SERVER::socketWriteTest(int server_fd ,int client_fd){
	/* 寫資料到client端 */
	const char *ServerWriteBuf = "Hi,I'm Server." ;
	std::cout << "Send data to client : " << ServerWriteBuf << std::endl ;
	int writeRTN = write(client_fd ,ServerWriteBuf ,strlen(ServerWriteBuf)) ;
	if(writeRTN < 0){
		perror("Error,can't write data to client.") ;
		close(server_fd) ;
		return -1 ;
	}
}




std::string SERVER::openHtmlFile(std::string htmlPath){
	std::fstream fs(htmlPath.c_str() ,std::fstream::in) ;

	std::string linebuf ;
	std::string fileData ;

	if(fs.is_open()){
		while(getline(fs, linebuf))
        {
			fileData += linebuf ;
			fileData += "\n" ;
        }

    }else{
        std::cout << "Can't open file!" << std::endl ;
    }
	fileData += "\0" ;
    fs.close() ;

	return fileData ;
}



int SERVER::writeStrData(int server_fd ,int client_fd ,std::string data){
	/* 寫資料到client端 */
	//std::cout << "Send data to client : " << data << std::endl ;
	//std::cout << "Size of data : " << data.size() << std::endl ;

	int rtn = write(client_fd ,data.c_str() ,data.size()) ;

	if(rtn < 0){
		perror("Error,can't write data to client.") ;
		close(server_fd) ;
		return -1 ;
	}
	return 0 ;
}

int SERVER::sendHtmlFile(int server_fd ,int client_fd ,std::string htmlPath){
	return this->writeStrData(server_fd ,client_fd ,this->openHtmlFile(htmlPath)) ;
}



int SERVER::openImgFile(std::string file_name){
    std::fstream fs;
    fs.open(file_name.c_str(), std::fstream::binary | std::fstream::in);

    memset(this->imgBuf, 0, BUF_SIZE);
    fs.read(this->imgBuf, BUF_SIZE);

    std::cout << " read size:" << fs.gcount() << std::endl;
	return fs.gcount() ;
}


int SERVER::writeImgData(int server_fd ,int client_fd ,int size){
	/* 寫資料到client端 */
	std::cout << "Send img to client" << std::endl ;
	std::cout << "Size :" << size << std::endl ;

	int rtn = write(client_fd ,&this->imgBuf ,size) ;

	if(rtn < 0){
		perror("Error,can't write data to client.") ;
		close(server_fd) ;
		return -1 ;
	}
	return 0 ;
}


int SERVER::sendImgFile(int server_fd ,int client_fd ,std::string file_name){
	int size = this->openImgFile(file_name) ;
	return this->writeImgData(server_fd ,client_fd ,size) ;
}

















