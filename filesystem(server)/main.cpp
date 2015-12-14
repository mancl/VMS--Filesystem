#include "cdir.h"
#include "cfile.h"
#include"chandler.h"
#include<signal.h>




char* FilePath = "/home/myfiles";
FILE* fp;
int Content_BlockNum =80;
string currentPath="/home/ ";   //当前路径
int current=32;    //当前目录的盘块号
//申请虚拟空间并且初始化
char* BaseAddr=(char *)malloc(Content_BlockNum*BlockSize);
//虚拟磁盘初始化
struct DISK* osPoint=(struct DISK *)(BaseAddr);
struct FCB tempFCB;


void signalHandler(int signo)
{
    printf("the file system is shutdown!\n");
    exit(0);
}


int main()
{
    /*********************************************************************/
    printf("-----Welcome To My File System -----\n");
//    printf("the FCB size is %d\n",sizeof(FCB));
    signal(SIGINT,signalHandler);

    CDir dHandler;//目录处理
//    CFile fileHandler;//文件处理
    CHandler clientHandler;
    //加载磁盘文件
    if((fp=fopen(FilePath,"r"))!=NULL)
    {
        fread(BaseAddr,sizeof(char),Content_BlockNum*BlockSize,fp);//只读取目录区的数据信息
        printf("the filesystem ( %s ) loaded successfully!\n\n",FilePath);
        dHandler.listShow();
    }
    else
    {
        printf("This is the first time you use the filesystem\tInitializing...\n");
        dHandler.format();
        printf("Initialize is done!\n\n");
    }

    clientHandler.waitForConnection();

    dHandler.exit();
    printf("--------------------------------------------------------------\n\n");
    printf("Thank you for using my file system!\n");
    return 0;
}
