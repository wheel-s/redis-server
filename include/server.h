#ifndef REDIS_SERVER_H
#define REDIS_SERVER_H

#include <string>
#include <atomic>
#include <sys/types.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#if defined(MSC_VER) 
#pragma comment(lib, "ws2_32.lib")
#endif
class Server{

   public:
        Server(int port);
        void run();
        void shutdown();


  private:
        int port;
        SOCKET server_socket;
        std::atomic<bool> running;
};


#endif