#include "../include/database.h"

#include <mutex>


Database& Database::getInstance(){
    static Database instance;
    return instance;
}

bool Database::dump(const std::string &filename){
   return true;
}

bool Database::load(const std::string& filenme){
    return true;
}


