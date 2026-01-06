#ifndef REDIS_DATABASE_H
#define REDIS_DATABASE_H

#include <string>


class Database {
    public:
        //Get the signleton instance
        static Database& getInstance();

        bool dump(const std::string& filename);
        bool load(const std::string& filename);
    
    
    private:
        Database() = default;
        ~Database() = default;
        Database(const Database&) = delete;
        Database& operator=(const Database) =delete;

};





#endif