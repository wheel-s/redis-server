#include "../include/server.h"
#include "../include/database.h"
#include <iostream>
#include <thread>
#include <chrono>



int main(int argc, char* argv[]){

    
    WSADATA wsa;
    
    if(WSAStartup(MAKEWORD(2,2), &wsa) !=0){
        std::cout<< "WSAStartup failed";
        WSACleanup();
    }

    int port = 42069;
    
    if(argc >=2){
        port = std::stoi(argv[1]);
    }
   
    // std::cout<<"hello "<< port<<"\n";

    Server server(port);
    
    std::thread persistenceThread([](){
        while(true){
            std::this_thread::sleep_for(std::chrono::seconds(300));
             if(!Database::getInstance().dump("dump.my_rdb")){ std::cerr <<"Error Dumping Database\n";}
             else{std::cout<< "Database Dumped to dump.my_rdb\n";}
        }   
    });
    persistenceThread.detach();

    server.run();
    
}