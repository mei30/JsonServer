# JsonServer
Simple high-performance server that accept requests for store, validate json. This server can support multiple requests simultaneously. It is created from two stage and two thread: handling incoming connections in async manner and writing connection data in files.

# Prerequisites
* g++ >= 11.3.0
* c++17
* cmake version 3.22.1


# Inistallation
```
apt install libboost-all-dev
apt install protobuf-compiler
apt instal  libgtest-dev

In project directory do following command respectively:

make build
cd build
cmake ../
make
./simple_server
```

# Notes
*The project config files must be placed next to the executable file. There is a **defaults** folder that contains defalut configs of server. To run the program correctly, you need to copy the contents of this folder next to the executable file.

* The log files are placed next to the executable file of the server named **server_logs.log**.

# Unsupported Features
* Unit Tests(most of the work with server is being done using async methods and threading, It is difficult to cover codes by unit testing)
* DLP mechanism
* Request Validatin
