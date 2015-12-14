#ifndef CDIR_H
#define CDIR_H
#include "global.h"
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
class CDir
{
public:
    CDir();
    int format();
    int mkdir(char *dirName, char *uName);
    int removeDir(int delDir);
    int listShow();
    int changeDir(int changeID, int client_sfd);
    int exit();
private:
    struct dirFile *dir;
};

#endif // CDIR_H
