#ifndef REDIS_DATABASE_H
#define REDIS_DATABASE_H

#include <string>
#include <mutex>
#include <unordered_map>
#include <vector>
#include <chrono>

class Database {
    public:
        //Get the signleton instance
        static Database& getInstance();

        //commands
        bool flushAll();
        
        //key value operations 
        void set(const std::string& key, const std::string& value);
        bool get(const std::string& key,  std::string &value);
        std::vector<std::string> keys();
        std::string type(const std::string &key);
        bool del(const std::string& key);

        bool expire(const std::string& key, int seconds);
        //remane
        bool rename(const std::string& oldkey, const std::string& newkey);

        size_t llen(const std::string&key);
        void lpush(const std::string &key, const std::string& value);
        void rpush(const std::string &key, const std::string& value);
        bool lpop(const std::string &key, std::string& value);
        bool rpop(const std::string &key, std::string& value);
        int lrem(const std::string& key, int count, const std::string& value);
        bool lindex(const std::string& key, int index, std::string& value);
        bool lset(const std::string& key, int count, const std::string& value);




        //persistence: Dump / load the db from a file
        bool dump(const std::string& filename);
        bool load(const std::string& filename);
    
    
    private:
        Database() = default;
        ~Database() = default;
        Database(const Database&) = delete;
        Database& operator=(const Database) =delete;
 
        std::mutex db_mutex;
        std::unordered_map<std::string, std::string> kv_store;
        std::unordered_map<std::string, std::vector<std::string>> list_store;
        std::unordered_map<std::string,  std::unordered_map<std::string, std::string>> hash_store;

        std::unordered_map<std::string, std::chrono::steady_clock::time_point> expiry_map;

};





#endif