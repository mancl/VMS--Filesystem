#ifndef CFILE_H
#define CFILE_H
#include"cdir.h"
#include"global.h"
#include <sys/socket.h>

struct Client
{
    int sfd;
    int status;
};
class CFile
{
public:
    CFile();
    int receive_uploadFile(char *name,int size, char *user,int client_sockfd);
    int send_downLoad(int fileId, int client_sockfd);
    int delFile(int delID);
    int check(char *name, int size);
    int createFile(char *name,int size, char *user);
    int fileChangeDir(int fSID, int tempBlock);
private:
    struct dirFile *dir;
//    char receive_buffer[8192];
};

#endif // CFILE_H
