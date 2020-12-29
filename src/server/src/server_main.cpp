/**
 * Date : 2020/12/15
 * Author : Yi-Ying-Lin
 * 
 */ 

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <string.h>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>


#include <pthread.h>

#include "server.h"



using namespace std;


int req_handler(SERVER *server){
	const char readBuf[32] = {0} ;

	while(1){
		memset((void *)readBuf ,0 ,sizeof(readBuf)) ;
		server->getRequest(server->serverfd ,server->clientfd ,readBuf) ;

		string readData = readBuf ;
		string req ;
		for(int i=0 ; i<4 ; i++){
			req += readBuf[i] ;
		}
		cout << "req :" << req << endl ;
		
		if(req != "GET "){
			if(req == "DONE"){
				cout << "		End." << endl ;
				return 0 ;
			}else{
				perror("		Unknown request ,End.") ;
				return 0 ;
			} 
		}

		//獲得檔案路徑
		string path ;
		for(int i=4 ; i<readData.size() ; i++){
			if(readData[i] == '\0') break ;
			path += readData[i] ;
		}
		//cout << "path :" << path << endl ;	

		if(path[1] == '.'){
			perror("Can't access parent directory.") ;
			return 0 ;
		}

		//傳送檔案給 client
		if(path.find("html") != string::npos){
			server->sendHtmlFile(server->serverfd ,server->clientfd ,path) ;
			cout << "Send html file to client." << endl ;

		}else if(path.find("jpg") != string::npos){
			server->sendImgFile(server->serverfd ,server->clientfd ,path) ;
			cout << "Send html file to client." << endl ;
			
		}else{
			cout << "Not implement Yet!" << endl ;
		}
	}
}


int main(int argc, char *argv[]) {

	const char *server_ip ;
	int server_port ;
    if( argc != 3 ){
        cout << "Default ip :" << SERVER_IP << endl ;
		server_ip = SERVER_IP ;
        cout << "Default port :" << SERVER_PORT_NUM << endl ;
		server_port = SERVER_PORT_NUM ;

    }else{
        cout << "server ip:" << argv[1] << endl ;
        server_ip = argv[1] ;
		cout << "server port:" << argv[2] << endl ;
		server_port = stoi(argv[2]) ;
    }

    cout << "ip :" << server_ip << endl ;
    cout << "port :" << server_port << endl ;

	cout << "Run Server..." << endl ;
	SERVER server(server_ip, server_port) ;

	while(1){
		
		server.clientfd = server.socketAccept(server.serverfd ,&server.clientSocAddr) ;
		int client_fd = server.clientfd ;

		if(client_fd < 0){
			perror("Error!\n");
		}else{
			int rtn = fork() ;
			if(rtn < 0){
				perror("Fail to fork a process to open browser\n") ;
				exit(0);

			//child process to handle request from client.
			}else if(rtn == 0){
				cout << "	Handle request ,child pid :" << getpid() << endl ;
				req_handler(&server) ;
				close(server.clientfd) ;
				close(server.clientfd) ;
				exit(0) ;
			}
		}
	}
	close(server.clientfd) ;
	close(server.clientfd) ;



	return 0 ;
}
