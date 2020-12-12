
#include <iostream>
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

#include "server.h"



using namespace std;


int main(int argc, char *argv[]) {

	string file_path ;
    if( argc != 2 ){
        cout << "Default file path :" << SERVER_HTML_FILE_PATH << endl ;
        file_path = SERVER_HTML_FILE_PATH ;
    }else{
        cout << "File path :" << argv[1] << endl ;
        file_path = argv[1] ;
    }

	
	SERVER server(SERVER_PORT_NUM) ;

	server.clientfd = server.socketAccept(server.serverfd ,&server.clientSocAddr) ;
	server.socketReadTest(server.serverfd ,server.clientfd) ;

	server.sendHtmlFile(server.serverfd ,server.clientfd ,file_path) ;


	return 0 ;
}
