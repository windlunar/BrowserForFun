# BrowserForFun

To render the browser ,you need to install SFML :

    sudo apt-get install libsfml-dev


Go to BrowserForFun directory.
Compile All :

    make

Open a simple html file in html_test folder:

    ./build/browser

![image](https://github.com/windlunar/BrowserForFun/blob/main/result/test2.png)


Simple server and client :
It will use "127.0.0.1" for test.

open server to provide html and image file to clients:

    ./src/server/Server

And then open anathor terminal and go to BrowserForFun directory.:

    ./build/main

![image](https://github.com/windlunar/BrowserForFun/blob/main/result/test3.png)


