Client/server application to control remote objects
===================================

# Introduction
There are two objects controlled by application: PhotoEditor and Stream. 
PhotoEditor is sync object i.e. all methods are blocking.
Stream is async object. All replies are processed by its callbacks in a separate thread.

# Overall architecture
I approached the task with classical Req/Reply pattern. Client and server interracts by sending msgs to each other. I did not use UNIX pipes since they are differs from NamedPipe in Widnows OS hence I chose standard sokets.

Payload of a message is JSON. A payload consits of header and arguments part and is defined as follow.

```sh
{
    "object": "Stream",
    "methode": "send_chat_msg",
    "arguments": {
        "uuid": "some id"
        "msg": "some message to a chat"
    }
}
```

The main focus was done toward decomposition of responsibilities. To have small high cochesion classes. There is deffenetly lack of supporting multithreaded environment. And would be reasonable to reduce Messeges coping by developing some kind of memory manager.

# Client architecture
PhotoEditor is implemented in a HTTP way. New connection is created on each remote methode to ther server.

Stream as I mentioned before is implemented on callbacks. Each object hold connection to the server until is done.

# Server architecture
Typical `accept` based server. New socket for each new connection is created.

Each remote object has its own class on server side and is implemented in event driven fasion. On a Req from client specific callback will be called on specific object.

All objects are stored in map. I wonted to find simple implementation of AVL tree but did not find due to lack of time.

# Build
The project was developed on Ubuntu

Dependencies: c++14 libboost 1.65.1
```sh
$ mkdir build
$ cd build
$ cmake ..
$ make
```
# Hot to start
Start server from build directory
```sh
$ ./server/server
```

Start client from build directory
```sh
$ ./client/client
``` 