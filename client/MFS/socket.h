#ifndef SOCKET_H
#define SOCKET_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

//socket操作类
class Socket
{
public:
    Socket();
    
    //连接到服务器，返回连接结果
    int connect(char * hostname,int port);
    //关闭socket
    void close();
    //发送数据到服务器
    int write(char *data,int size);
    //读取文件路径中的文件，并发送到服务器，size 文件大小
    int writeFile(char *filePath,int size);
    //接收文件并存到文件路径上，size 文件大小
    int readFile(char *filename,int size);
    //接收操作请求返回信息
    char * readMsg();


private:
    //连接成功获得到socketID；端口号，操作结果
    int sockfd, portno, n;
    //服务器地址
    struct sockaddr_in serv_addr;
    struct hostent *server;
    //用于发送和接收数据
    char buffer[2048];


};

#endif // SOCKET_H
