#include "chandler.h"

CDir dirHandler;
CFile fileHandler;
struct sockaddr_in server_addr,client_addr;
int sockfd, newsockfd, portno;
int msgLen;
char msgBuffer[256];
char buffer[30];
int fileID;
int delID;
char fileName[16];
char userName[10];
int fileSize;
socklen_t clientLen;
int fSID;
int tempBlock;

struct Client client[5];
int clientNum;

CHandler::CHandler()
{
    //memset(client,-1,5);
    for(int i=0;i<CLIENTNUM;i++)
    {
        client[i].sfd=-1;
        client[i].status=0;
        printf("1all client %d %d\n",client[i].sfd,i);
    }
    sockfd=socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd==-1)
         perror("ERROR socket");
    bzero((char *) &server_addr, sizeof(server_addr));
    portno=8500;
//    portno = atoi(argv[1]);//字符串转换为整型
    clientLen=sizeof(client_addr);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &server_addr,sizeof(server_addr)) < 0)
         perror("ERROR bind");
}


int CHandler::waitForConnection()
{
    listen(sockfd,5);
    pthread_t thread[2];
    pthread_create(&thread[0],NULL,connectionHandler,(void*)&sockfd);
    pthread_create(&thread[1],NULL,commandHandler,NULL);
    printf("thread is ok\n");
    for(int i=0;i<2;i++){
        pthread_join(thread[i],NULL);
        printf("thread is ok\n");
    }
    return 0;
}

int handleRequest(int i);

void *CHandler::commandHandler(void *arg)
{
    int maxfd = -1;/*最大侦听文件描述符*/
    fd_set scanfd;	/*侦听描述符集合*/
    struct   timeval   timeout; 	/*超时*/
    timeout.tv_sec = 1; /*   阻塞1秒后超时返回   */
    timeout.tv_usec = 0;
    FD_ZERO(&scanfd);
    int i = 0;
    int err  = -1;
    for(;;)
    {
       /*最大文件描述符值初始化为-1*/
        maxfd = -1;
        timeout.tv_sec = 1; /*   阻塞1秒后超时返回   */
        timeout.tv_usec = 0;
        FD_ZERO(&scanfd);/*清零文件描述符集合*/
        for(i=0;i<clientNum;i++)/*将文件描述符放入集合*/
        {
//          printf("2all client %d %d\n",client[i].sfd,i);
          if(client[i].sfd !=-1)/*合法的文件描述符*/
          {
//              printf("hhhhhh  client is %d,%d\n",client[i].sfd,i);
              FD_SET(client[i].sfd, &scanfd);/*放入集合*/
              if(maxfd < client[i].sfd)/*更新最大文件描述符值*/
                   maxfd = client[i].sfd;
          }
        }
        /*select等待*/
        err = select(maxfd + 1, &scanfd, NULL, NULL, &timeout) ;//1s超时
        switch(err)
        {
            case 0:/*超时*/
//                 printf("select is timeout\n");
                 break;
            case -1:/*错误发生*/
                 break;
            default:/*有可读套接字文件描述符*/
                 if(clientNum<=0)
                    break;
                 for(i = 0;i<CLIENTNUM;i++)
                 {
//                     printf("3all client %d %d\n",client[i].sfd,i);
                    /*查找激活的文件描述符*/
                    if(client[i].sfd != -1){
                       if(FD_ISSET(client[i].sfd,&scanfd))
                       {
                           printf("DATA : the client is %d  %d\n",client[i].sfd,i);
                           switch(client[i].status)
                           {
                            case 0:
                               memset(fileName,0,16);
                               memset(userName,0,10);
                               handleRequest(i);
                               break;
                            case 1:
                               fileHandler.receive_uploadFile(fileName,fileSize,userName,client[i].sfd);
                               client[i].status=0;
                               printf("receive ok!\n");
                               break;
                           default:
                               break;
                           }
                        }
                    }
                 }
                break;
            }
        }
     return NULL;
}

int handleRequest(int i)
{
    char requestBuffer[50];
    int id;
    char header[5];
    int flag;

    bzero(requestBuffer,50);
    msgLen=read(client[i].sfd,requestBuffer,50);
    if(msgLen<=0){
        client[i].sfd=-1;
        return 0;
    }
    printf("msgLen =%d  %s\n",msgLen,requestBuffer);
    strcpy(header,strtok(requestBuffer,"\n"));
    printf("header is %d\n",atoi(header));


    if(atoi(header)==REQ_UPLOAD_FILE)
    {
        fileSize=atoi(strtok(NULL,"\n"));
        strcpy(fileName,strtok(NULL,"\n"));
        printf("fileName is %s\n",fileName);
        strcpy(userName,strtok(NULL,"\n"));
        id=fileHandler.check(fileName,fileSize);
        if(id==0){
            sprintf(requestBuffer,"13\n1\n%d\n",id);
            msgLen=send(client[i].sfd,requestBuffer,strlen(requestBuffer),0);
            printf("upload failed!\n");
            return 0;
        }
        memset(requestBuffer,0,50);
        sprintf(requestBuffer,"13\n0\n%d\n",id);
        msgLen=write(client[i].sfd,requestBuffer,strlen(requestBuffer));
        printf("send msgLen =%d  %s\n",msgLen,requestBuffer);
        client[i].status=1;
    }
    else if(atoi(header)==REQ_DOWNLOAD_FILE)
    {
        fileID=atoi(strtok(NULL,"\n"));
        flag=fileHandler.send_downLoad(fileID,client[i].sfd);
        if(!flag)
            printf("send is failed!\n");
        printf("send is ok!\n");
    }
    else if(atoi(header)==REQ_DEL_FILE)
    {
        delID=atoi(strtok(NULL,"\n"));
        int type=atoi(strtok(NULL,"\n"));
        if(type==1){
            flag=fileHandler.delFile(delID);
        }
        else if(type==0){
            flag=dirHandler.removeDir(delID);
        }
        if(flag)
        {
            sprintf(requestBuffer,"12\n0\n");
            send(client[i].sfd,requestBuffer,strlen(requestBuffer),0);
            printf("del is ok!\n");
        }
        else
        {
            sprintf(requestBuffer,"12\n1\n");
            send(client[i].sfd,requestBuffer,strlen(requestBuffer),0);
            printf("del is failed!\n");
        }
    }
    else if(atoi(header)==REQ_CHG_DIR)
    {
         int chgID=atoi(strtok(NULL,"\n"));
         flag=dirHandler.changeDir(chgID,client[i].sfd);
         if(flag)
             printf("change ok!\n");
    }
    else if(atoi(header)==REQ_NEW_DIR)
    {
        strcpy(fileName,strtok(NULL,"\n"));
        printf("fileName is %s\n",fileName);
        strcpy(userName,strtok(NULL,"\n"));
        id=dirHandler.mkdir(fileName,userName);
        memset(requestBuffer,0,50);
        sprintf(requestBuffer,"11\n0\n%d\n",id);
        msgLen=write(client[i].sfd,requestBuffer,strlen(requestBuffer));
        printf("new dir is ok!\n");
    }
    else if(atoi(header)==REQ_CHG_POS_START)
    {
        fSID=atoi(strtok(NULL,"\n"));
        tempBlock=fileHandler.fileChangeDir(fSID,0);
    }
    else if(atoi(header)==REQ_CHG_POS_END)
   {
        id=fileHandler.fileChangeDir(fSID,tempBlock);
        memset(requestBuffer,0,50);
        sprintf(requestBuffer,"15\n0\n%d\n",id);
        msgLen=write(client[i].sfd,requestBuffer,strlen(requestBuffer));
        printf("file change pos is ok!\n");
   }
}


void *CHandler::connectionHandler(void *sockfd)
{
    int socketfd=*((int *)sockfd);
    struct dirFile *rootDir;
    rootDir=&(osPoint->root);

    for(;;)
    {
        sprintf(msgBuffer,"16\n%d\n",rootDir->fcb[0].needBlockCount);//初始化消息头
//                printf("msgBuffer is %s\n",msgBuffer);
        for(int i=1;i<BlockFcbCount;i++)
        {
            if(rootDir->fcb[i].type==GENERAL)
            {   //查找普通文件
                sprintf(buffer,"%d\n1\n%d\n%s\n%s\n%s\n",i,rootDir->fcb[i].size,rootDir->fcb[i].fname,
                        rootDir->fcb[i].userName,rootDir->fcb[i].time_upload);
                strcat(msgBuffer,buffer);
            }
            if(rootDir->fcb[i].type==DIRECTORY)
            {   //查找目录文件
                sprintf(buffer,"%d\n0\n%d\n%s\n%s\n%s\n",i,rootDir->fcb[i].size,rootDir->fcb[i].fname,
                        rootDir->fcb[i].userName,rootDir->fcb[i].time_upload);
                strcat(msgBuffer,buffer);
            }
        }
//                printf("the msgBuffer is %s\n",msgBuffer);

        newsockfd = accept(socketfd,(struct sockaddr *) &client_addr,&clientLen);//记录新连接的客户端
        printf("newsockfd=%d\n",newsockfd);
        if(newsockfd<0)
            perror("ERROR accept");
        printf("accept is ok\n");

        int len=send(newsockfd,msgBuffer,strlen(msgBuffer),0);
        printf("send is ok\n");
        for(int i=0;i<CLIENTNUM;i++)
        {
            printf("4all client %d %d\n",client[i].sfd,i);
            if(client[i].sfd==-1)
            {
                client[i].sfd=newsockfd;
                clientNum++;
                printf("client is %d,%d\n",client[i].sfd,i);
                break;
            }
        }
    }
    return NULL;
}

