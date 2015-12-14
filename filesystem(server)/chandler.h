#ifndef CHANDLER_H
#define CHANDLER_H
#include "global.h"
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/select.h>
#include <pthread.h>
#include<time.h>
#include"cdir.h"
#include"cfile.h"
#define CLIENTNUM 5

#define RES_NEW_DIR 11
#define RES_DEL_FILE 12
#define RES_UPLOAD_FILE 13
#define RES_DOWNLOAD_FILE 14
#define RES_CHG_POS 15
#define RES_CHG_DIR 16

#define REQ_NEW_DIR 21
#define REQ_DEL_FILE 22
#define REQ_UPLOAD_FILE 23
#define REQ_DOWNLOAD_FILE 24
#define REQ_CHG_POS_START 25
#define REQ_CHG_POS_END 26
#define REQ_CHG_DIR 27




class CHandler
{
public:
    CHandler();
    static void *commandHandler(void *s);
    int waitForConnection();
    static void *connectionHandler(void *sockfd);
//    int handleRequest(int i);

};

#endif // CHANDLER_H
