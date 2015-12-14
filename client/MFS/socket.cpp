#include "socket.h"
#include<QDebug>
Socket::Socket()
{
}
int Socket::connect(char * hostname,int port)
{
     portno = port;
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0)
     {
         perror("ERROR opening socket");
         return -1;
     }

       server = gethostbyname(hostname);
       if (server == NULL) {
           fprintf(stderr,"ERROR, no such host\n");
           return -2;
       }
       bzero((char *) &serv_addr, sizeof(serv_addr));
       serv_addr.sin_family = AF_INET;
       bcopy((char *)server->h_addr,
            (char *)&serv_addr.sin_addr.s_addr,
            server->h_length);
       serv_addr.sin_port = htons(portno);
       if (::connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
       {
           perror("ERROR connecting");
           return -3;
       }
return 0;
}
void Socket::close()
{
    ::close(sockfd);
}

int Socket::write(char *data,int size)
{
    int readLen;
    int i=0;
    while(i<size)
    {
        bzero(buffer,2048);
        int wSize;
        if(i+2048+1>size)
        {
            wSize=size-i;
        }
        else
        {
            wSize=2048;
        }
        memcpy(buffer, data + i, wSize);
        readLen = ::write(sockfd,buffer,wSize);
        i=i+readLen;
        qDebug()<<"SOCKET writeLength:"<<readLen<<"SOCKET WriteData:"<<buffer;
        if (readLen < 0)
        {
            perror("ERROR writing to socket");
            return -4;
        }
    }
    return 0;
}
int Socket:: writeFile(char *filePath,int filesize)
{
    FILE* fp;
    char *data;
    qDebug()<<"SOCKET WRITE FILE:"<<filePath;
    if((fp=fopen(filePath,"r"))!=NULL)
    {
        data =(char *)malloc(filesize);
        fread(data,sizeof(char),filesize,fp);
        fclose(fp);
        sleep(1);
        int n=write(data,filesize);
        free(data);
        return n;
    }
    else
    {
        return -2;
    }
    fclose(fp);
}

int Socket::readFile(char *fileName,int size)
{
    FILE* file=fopen(fileName,"w+");
    fseek(file, 0L, SEEK_SET);
    int readLen=0;
    int i=0;
    while(i<size)
    {
        qDebug()<<"SOCKET ReadFileLength:"<<i<<"filesize:"<<size;
        bzero(buffer,2048);
        readLen=read(sockfd,buffer,2048);
        i+=readLen;
        qDebug()<<"SOCKET readLen:"<<readLen;
        if (readLen < 0)
        {
            perror("ERROR reading to socket");
            return -1;
        }
        fwrite(buffer,sizeof(char),readLen,file);
    }

    fclose(file);
    return 0;
}

char * Socket::readMsg()
{
    bzero(buffer,2048);
    n = read(sockfd,buffer,2048);
    if (n < 0)
    {
        perror("ERROR reading from socket");
        printf("%s\n",buffer);
        return NULL;
    }
    qDebug()<<"SOCKET readMsg:"<<buffer;
    return buffer;

}
