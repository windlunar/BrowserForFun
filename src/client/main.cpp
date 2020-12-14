/**
 * Date : 2020/12/15
 * Author : Yi-Ying-Lin
 * 
 */ 

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

#include "../browser/loadfile.h"
#include "../browser/parse.h"
#include "../browser/dom.h"


#include "../browser/layout.h"


#define READ_BUF_SIZE	4096
#define DEFAULT_FILE_PATH   "./temp"
#define FILE_NAME   "/index.html"

using namespace std;

struct ClientReq{
	CLIENT *client_ptr ;
	char img_name[32] ;
};


void *downloadImageThread(void *arg){
	ClientReq *clientReq = (ClientReq *)arg ;

	string req = "GET " ;
	req += clientReq->img_name ;
	req += "\0\r\n" ;

	cout << "In thread req :" << req << endl ;

	clientReq->client_ptr->sendRequest(req.c_str());
	clientReq->client_ptr->receiveImageFile(clientReq->client_ptr->clientSocketfd ,clientReq->img_name) ;
	clientReq->client_ptr->sendRequest("DONE\0\r\n");
}



/**
 * arg1 : server ip
 * arg2 : server port
 * arg3 : file path
 */ 
int main(int argc, char *argv[]) {


	const char *server_ip ;
	int server_port ;
    if( argc != 3 ){
        cout << "Default server ip :" << SERVER_IP << endl ;
		server_ip = SERVER_IP ;
        cout << "Default server port :" << SERVER_PORT_NUM << endl ;
		server_port = SERVER_PORT_NUM ;

    }else{
        cout << "server ip:" << argv[1] << endl ;
        server_ip = argv[1] ;
		cout << "server port:" << argv[2] << endl ;
		server_port = stoi(argv[2]) ;
    }

    cout << "ip :" << server_ip << endl ;
    cout << "port :" << server_port << endl ;


    string file_path ;
    if( argc != 2 ){
        cout << "Default file path :" << DEFAULT_FILE_PATH << endl ;
        file_path = DEFAULT_FILE_PATH ;
    }else{
        cout << "File path :" << argv[1] << endl ;
        file_path = argv[3] ;
    }
    
    //變更當前程式的執行路徑
    chdir(file_path.c_str()) ;


	CLIENT *client = new CLIENT(server_ip ,server_port) ;
	client->sendRequest("GET ./index.html\0\r\n");
	client->receiveHtmlFile(client->clientSocketfd ,READ_BUF_SIZE ,"./index.html") ;
	client->sendRequest("DONE\0\r\n");
	delete client ;

    
    /** 載入 HTML 檔案*/
    LOADFILE load("./" ,FILE_NAME) ;
    vector<string> readHTML = load.deleteSpaceChar( load.loadFile() ) ;
    load.printHtmlRawData(readHTML) ;


    /** 解析 HTML*/
    PARSE parse(readHTML) ;

    parse.initTree();
    parse.createRootNode();

    parse.createDomTree();


	/** Create a child process to get image which parse from html file.*/
	int pipe_fd[2] ;
	if (pipe(pipe_fd) < 0){
		perror("Pipe create error.") ;
		exit(0) ;
	}

	int rtn = fork() ;
	if(rtn < 0){
		perror("Fail to fork a process to open browser\n") ;
		exit(0);

	//child process to get image from server.
	}else if(rtn == 0){
		//close write
		close(pipe_fd[1]) ;

		cout << "	To get image from server ,child pid :" << getpid() << endl ;

		CLIENT client1(server_ip ,server_port) ;
		ClientReq clientReq1 ;
		clientReq1.client_ptr = &client1 ;

		CLIENT client2(server_ip ,server_port) ;
		ClientReq clientReq2 ;
		clientReq2.client_ptr = &client2 ;

		memset((void *)&clientReq1.img_name ,0 ,sizeof(clientReq1.img_name)) ;
		memset((void *)&clientReq2.img_name ,0 ,sizeof(clientReq2.img_name)) ;
		

		/** Get the image file name from parent process.*/
		read(pipe_fd[0] , clientReq1.img_name, 32) ;
		read(pipe_fd[0] , clientReq2.img_name, 32) ;

		printf("Get First image name : %s\n" ,clientReq1.img_name) ;
		printf("Get Second image name : %s\n" ,clientReq2.img_name) ;


		/** Create 2 thread to get image file from server.*/
		pthread_t thread1;
		pthread_t thread2;
		if(pthread_create(&thread1 ,NULL ,&downloadImageThread ,&clientReq1) != 0 ){
			perror("Create Thread Error!\n");
		}

		if(pthread_create(&thread2 ,NULL ,&downloadImageThread ,&clientReq2) != 0 ){
			perror("Create Thread Error!\n");
		}

		pthread_join(thread1, NULL); 
		pthread_join(thread2, NULL); 


		close(pipe_fd[0]) ;
		exit(0) ;
	}

	//close read
	close(pipe_fd[0]) ;

	write(pipe_fd[1] , "./earth.jpg\0",32) ;
	write(pipe_fd[1] , "./solar.jpg\0",32) ;
	close(pipe_fd[1]) ;


	//等待 child process 完成
	int rtn_wait = wait(NULL) ;
	cout << "Continue to layout and render the text and image." << endl ;

    /** 根據tree排版*/
    LAYOUT layout ;

    /** 建立視窗*/
    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), layout.getTitle_of_Window());
    
    //背景顏色
    sf::Color color(240, 240, 255);

    /** Render*/
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(color);
        
        //render texts.
        layout.renderText(&window) ;

        //render image
        layout.renderImage(&window) ;
        
        window.display();
    }
	return 0 ;
}
