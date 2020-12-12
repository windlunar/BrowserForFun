

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


using namespace std;



int main(int argc, char *argv[]) {
	CLIENT client(SERVER_PORT_NUM) ;
	string str ;
	client.receiveHtmlFile(client.clientSocketfd ,1587 ,str ,CLIENT_FILE_PATH) ;

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
