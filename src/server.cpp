#include "../include/server.h"
#include "../include/commandHandler.h"
#include <iostream>
#include <unistd.h>
#include <vector>
#include <thread>
#include <exception>
#include <cstring>




static Server* globalServer = nullptr; 

Server::Server(int port) : port(port),server_socket(INVALID_SOCKET), running(true){

    globalServer = this;
}

void Server::shutdown(){
    running = false;
    if(server_socket != INVALID_SOCKET){
      close(server_socket);
      WSACleanup();
    }
    std::cout << "Server shutdown Complete!\n";
}

void Server::run(){

    

    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if(server_socket == INVALID_SOCKET){
         std::cout <<"COULD NOT RECIEVE SOCKET: \n";
         return;
     }

     int opt = 1;
     setsockopt(server_socket,  SOL_SOCKET, SO_REUSEADDR, (char*)&opt,sizeof(opt));

    sockaddr_in serverAddr{};
     serverAddr.sin_family =AF_INET;
     serverAddr.sin_port = htons(port);
     serverAddr.sin_addr.s_addr = INADDR_ANY;

     if(bind(server_socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0){
        std::cout<<"Error Binding Server Socket\n";
        return;
     }

     listen(server_socket,10);
 

     std::cout<<"Server Listening on port "<< port << "\n";


    std::vector<std::thread> threads;
    CommandHandler cmdHandler;

    while(running){
        
         SOCKET client_socket = accept(server_socket, nullptr, nullptr);

            

        if(client_socket == INVALID_SOCKET){
            printf("ACCEPT FAILED: %d\n", WSAGetLastError());
            closesocket(server_socket);
            WSACleanup();
            break;


        }

        threads.emplace_back([client_socket, &cmdHandler](){
            char buffer[1024];

            while(true){
                memset(buffer, 0, sizeof(buffer));
                int bytes= recv(client_socket, buffer, sizeof(buffer)-1, 0);
                if(bytes<=0){break;}

                std::string request(buffer, bytes);
                std::string response = cmdHandler.processCommand(request);
                send(client_socket, response.c_str(), response.size(),0);

            }  
            closesocket(client_socket);
        
        });

        for(auto& t : threads){
            if(t.joinable()) {t.join();}
            
        }
    }
   
}

