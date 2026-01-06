#include "../include/commandHandler.h"
#include "../include/database.h"
#include <vector>
#include <exception>
#include <sstream>
#include <iostream>
#include <algorithm>

//resp parser
// *2\r\n$4\r\nPING\r\n$4\r\nTEST\r\n
// *2 -> array has 2 elements
// $4 -> neaxt string has 4 characters


std::vector<std::string>parseRespCommand(const std::string &input){  

    std::vector<std::string> tokens;
    if(input.empty()){ return tokens;}


    if(input[0] != '*'){
        std::istringstream iss(input);
        std::string token;

        while(iss >>token){
            tokens.push_back(token);
        }
        return tokens;
    }
    
    size_t pos =0;
    if(input[pos] !='*'){return tokens;}
    pos++;

    size_t crlf = input.find("\r\n",pos);
    if(crlf == std::string::npos){return tokens;}
   

    int numElements = std::stoi(input.substr(pos, crlf - pos));
    pos = crlf + 2;

    for(int i = 0; i < numElements; i++) {
        if(pos >= input.size() || input[pos] != '$') {break;}
        pos ++;

        crlf = input.find("\r\n", pos);
        if(crlf == std::string::npos){ break;}
    
        int len = std::stoi(input.substr(pos, crlf - pos));
        pos = crlf + 2;

        if(pos + len > input.size()){break;}
        std::string token = input.substr(pos, len);
        tokens.push_back(token);

        pos += len + 2;

    }
    
    return tokens;
}

CommandHandler::CommandHandler() {
    
}

std::string CommandHandler ::processCommand(const std::string& commandLine){
    
    auto tokens = parseRespCommand(commandLine);
    if(tokens.empty()){ return ".Error: Empty Command\r\n";}

    // std::cout<< commandLine<<"\n";
    // for(auto& t : tokens){ std::cout<<t <<"\n"; }

    std::string cmd = tokens[0];
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);
    std::ostringstream response;
    Database& db = Database::getInstance();

    if(cmd == "PING"){
        response << "+PONG\r\n";
    }else if(cmd == "ECHO"){
        // ........
    }
    else{
        response <<"+Error Unknown command\r\n";
    }

    
    return  response.str();
    
}
