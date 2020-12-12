
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

	server->sendHtmlFile(server->serverfd ,server->clientfd ,server->html_file_path) ;
}


int main(int argc, char *argv[]) {

	string file_path ;
    if( argc != 2 ){
        cout << "Default file path :" << SERVER_HTML_FILE_PATH << endl ;
        file_path = SERVER_HTML_FILE_PATH ;
    }else{
        cout << "File path :" << argv[1] << endl ;
        file_path = argv[1] ;
    }

	
	SERVER server(SERVER_PORT_NUM ,file_path) ;
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



	return 0 ;
}
