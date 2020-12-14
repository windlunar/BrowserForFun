
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>


#include <pthread.h>

#include "server.h"



using namespace std;


void *request_handler(void *arg){
	SERVER *server = (SERVER *)arg ;

	server->socketReadTest(server->serverfd ,server->clientfd) ;
	server->sendHtmlFile(server->serverfd ,server->clientfd ,"./index.html") ;

	server->socketReadTest(server->serverfd ,server->clientfd) ;
	server->sendImgFile(server->serverfd ,server->clientfd ,"./earth.jpg") ;

	server->socketReadTest(server->serverfd ,server->clientfd) ;
	server->sendImgFile(server->serverfd ,server->clientfd ,"./solar.jpg") ;
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
	pthread_t thread;

	while(1){
		
		server.clientfd = server.socketAccept(server.serverfd ,&server.clientSocAddr) ;
		int client_fd = server.clientfd ;

		if(client_fd < 0){
			perror("Error!\n");
		}else{
			if(pthread_create(&thread ,NULL ,&request_handler ,&server) != 0 ){
				perror("Create Thread Error!\n");
			}
		}
	}
	close(server.clientfd) ;



	return 0 ;
}
