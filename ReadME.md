# Redis Server

-A light Redis-Compatable in-Memory data store written in C++. It supports strings, list , and hashes, full
 Redis Serialization Protocol, multi-client concurrency, and periodic disk persistense.   



# Features

- Commands: PING, ECHO, FLUSHALL
- Key/Value: SET, GET, KEYS, TYPES, DEL/UNLINK, EXPIRE, RENAME
- List: LGET, LLEN, LPUSH/RPUSH, LPOP/RPOP, LINDEX, LSET

Data is automatically dumped to dump.my_rdb every 300 seconds and on shutdowns; at startup, the server attemps to load from this file.



# Installation

- install C++17 (or later) compiler;
```
#from the root
make
```
- or compile manually
```
#windows
g++ -std=c++17 -pthread -Iinclude src/*.cpp -o redisServer -lws2_32
#linux
g++ -std=c++17 -pthread -Iinclude src/*.cpp -o redisServer

```