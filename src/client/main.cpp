

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


#include "client.h"


#define READ_BUF_SIZE	4096

using namespace std;

int main(int argc, char *argv[]) {
	CLIENT client(SERVER_PORT_NUM) ;
	string str ;
	client.socketWriteTest();
	client.receiveHtmlFile(client.clientSocketfd ,READ_BUF_SIZE ,str ,CLIENT_FILE_PATH) ;

	client.socketWriteTest();
	client.receiveImageFile(client.clientSocketfd ,"./temp/earth.jpg") ;

	client.socketWriteTest();
	client.receiveImageFile(client.clientSocketfd ,"./temp/solar.jpg") ;

	//open browser
	int rtn = fork();

	if(rtn < 0){
		perror("Fail to fork a process to open browser\n") ;
		exit(0);
	//child process :browser
	}else if(rtn == 0){
		cout << "Open Browser." << endl ;
		char *arg =strdup("./temp") ;
		execlp("./build/browser" ,"browser" ,arg ,NULL) ;

	}else{
		int rtn_wait = wait(NULL) ;
	}

	return 0 ;
}
