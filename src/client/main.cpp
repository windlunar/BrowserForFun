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
	string filename = clientReq->img_name ;
	filename += "\n" ;

	string req = "GET " ;
	req += clientReq->img_name ;
	req += "\0\r\n" ;

	cout << "In thread req :" << req << endl ;

	clientReq->client_ptr->sendRequest(req.c_str());
	clientReq->client_ptr->receiveImageFile(clientReq->client_ptr->clientSocketfd ,clientReq->img_name) ;
	clientReq->client_ptr->sendRequest("DONE\0\r\n");

	fstream fs("./record.txt" ,fstream::out | fstream::app) ;
	if(fs.is_open()){
		cout << "Write file name to txt." << endl ;
		fs.write(filename.c_str() ,filename.size()) ;
	}else{
		perror("In downloadImageThread.Fail to open file") ;
	}
}



/**
 * arg1 : server ip
 * arg2 : server port
 * arg3 : file path
 */ 
int main(int argc, char *argv[]) {

	/** 根據輸入參數設定 server ip, port*/
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

	/** 根據輸入參數設定下載路徑*/
    string file_path ;
    if( argc != 2 ){
        cout << "Default file path :" << DEFAULT_FILE_PATH << endl ;
        file_path = DEFAULT_FILE_PATH ;
    }else{
        cout << "File path :" << argv[1] << endl ;
        file_path = argv[3] ;
    }
    
    //變更當前程式的執行路徑至下載路徑
    chdir(file_path.c_str()) ;


	//下載 html檔案
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

	//Get the img file name from dom tree
	parse.getImgTagsFilePath() ;


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


	/** 
	 * 
	 * child process to get image from server.
	 * 
	 */ 
	}else if(rtn == 0){
		//close write
		close(pipe_fd[1]) ;

		cout << "	To get image from server ,child pid :" << getpid() << endl ;

		int img_num = 0 ;
		read(pipe_fd[0] , &img_num, sizeof(int)) ;
		cout << "num of img :" << img_num << endl ;


		//CLIENT client(server_ip ,server_port) ;
		CLIENT *client[img_num] ;
		for(int j=0 ;j < img_num ;j++){

			client[j] = new CLIENT(server_ip ,server_port) ;

		}

		ClientReq clientReq[img_num] ;
		
		for(int j=0 ;j < img_num ;j++){

			clientReq[j].client_ptr = client[j] ;
			memset((void *)&clientReq[j].img_name ,0 ,sizeof(clientReq[j].img_name)) ;

		}

		/** Get the image file name from parent process.*/
		for(int j=0 ;j < img_num ;j++){
			read(pipe_fd[0] , clientReq[j].img_name, 32) ;
		}

		printf("Get First image name : %s\n" ,clientReq[0].img_name) ;
		printf("Get Second image name : %s\n" ,clientReq[1].img_name) ;


		/** Create threads to get image file from server.*/
		pthread_t thread[img_num];
		for(int j=0 ;j < img_num ;j++){
			if(pthread_create(&thread[j] ,NULL ,&downloadImageThread ,&clientReq[j]) != 0 ){
				perror("Create Thread Error!\n");
			}		
		}


		for(int j=0 ;j < img_num ;j++){
			pthread_join(thread[j], NULL); 
		}

		close(pipe_fd[0]) ;

		for(int j=0 ;j < img_num ;j++){

			delete client[j]  ;

		}
		
		exit(0) ;
	}


	//close read
	close(pipe_fd[0]) ;

	int img_num = parse.imgFilePathVec.size() ;
	write(pipe_fd[1] , &img_num,sizeof(int)) ;

	//send the img file name to child process.
	for(int j=0 ;j < parse.imgFilePathVec.size() ;j++){
		write(pipe_fd[1] , parse.imgFilePathVec[j].c_str(),32) ;
		usleep(100) ;
	}
	
	close(pipe_fd[1]) ;


	//等待 child process 完成
	int rtn_wait = wait(NULL) ;
	cout << "Continue to layout and render the text and image." << endl ;

    /** 根據tree排版*/
    LAYOUT layout(FONT_PATH) ;

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
