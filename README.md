# BrowserForFun

1.Test Enviroment : Ubuntu 18.04

<br>
2.To render the browser ,you need to install SFML :

    sudo apt-get install libsfml-dev

<br>
3.Clone this project:

    git clone https://github.com/windlunar/BrowserForFun

<br>
4.Go to BrowserForFun folder.
And Compile all the source file:

    make

<br>
5. Open a simple html webpage in html_test folder:

    ./build/browser_test

![image](https://github.com/windlunar/BrowserForFun/blob/main/result/test2.png)


## Simple server and client :

By default, it will use the localhost which is "127.0.0.1" for testing.<br><br>
1.Go to BrowserForFun folder ,open a server to provide html webpage and image file to clients:

    cd ./src/server
    ./Server

2.Then open anathor terminal and move to BrowserForFun folder:<br><br>
3.Execute the binary to open browser as the client.<br>
The client will send the request to server ,and then download the html webpage first.<br>After parsing the html page by browser ,it will create a dom tree ,and then get the image url info from this dom tree.<br>
And then the client will send anothor request to download the image files from server.<br>
The layout of texts and pictures will be done by browser ,then create a window and render all components to the window:

    ./build/main

![image](https://github.com/windlunar/BrowserForFun/blob/main/result/test3.png)


## Simple server and client on different computer :

1. For server side ,you should open the port which you want to use ,or the port may be block by your firewall.<br>
2. At server side ,move to BrowserForFun folder:

    cd ./src/server
    ./Server \<ip address of server\> \<port number of server\>
<br>
3. For another computer as client(move to BrowserForFun folder) :

    ./build/main \<ip address of server\> \<port number of server\>
<br>
Then the client will connect to server computer and open the page by Browser.