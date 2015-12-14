#include "cdir.h"

CDir::CDir()
{
}
/*------------------------初始化-----------------------*/
int CDir::format()
{
    current = 32;//根目录在第8块
    currentPath="/home/";   //当前路径
    /*-------保存到磁盘上myfiles--------*/
    char end=EOF;
    fp = fopen(FilePath,"w");
    fseek(fp,DiskSize-1,SEEK_SET);
    fwrite(&end,1,1,fp);
    fclose(fp);
    osPoint->format();//打开文件列表初始化
    printf("----------------------------------------------------------\n\n");
    return 1;
}

int CDir::exit()
{
    //将所有文件都关闭,保存到磁盘上
    fp=fopen(FilePath,"r+");
    fwrite(BaseAddr,sizeof(char),Content_BlockNum*BlockSize,fp);
//    int length=ftell(fp);
//    printf("the length is %d\n",length);
    fclose(fp);
    //释放内存上的虚拟磁盘
    free(osPoint);
    printf("---------------------------------------------------------\n\n");
    return 1;
}

int CDir::mkdir(char *dirName,char *uName)
{
    int i,temp,FAT_set;
    if(current==32)
        dir=&(osPoint->root);
    else
        dir=(struct dirFile *)(osPoint->data [current-33]);
    /*----------为了避免该目录下同名文件夹--------*/
    for(i = 1;i<BlockFcbCount;i++)
    {
        if(dir->fcb[i].type==DIRECTORY && strcmp(dir->fcb[i].fname,dirName)==0 )
        {
            printf("there is a file or diretory with the same name!\n");
            return 0;
        }
    }
    //查找空白fcb序号
    for(i=1;i<BlockFcbCount;i++)
    {
        if(dir->fcb[i].type==HXSH)
            break;
    }

    if(i==BlockFcbCount)
    {
        printf("该目录已满!请选择新的目录下创建!\n");
        return 0;
    }
    temp=i;
    for(i = 33;i < Content_BlockNum;i++)  //这里应限制为目录区内 即Content_BlockNum
    {
        if(osPoint->FAT1[i].useflag== 0)
            break;
    }
    if(i == Content_BlockNum)
    {
        printf("目录区已满!\n");
        return 0;
    }
    dir->fcb[0].needBlockCount++;//表示当前目录下到文件和文件夹总数
    FAT_set=i;//在FAT分块表中的位置

    /*-------------接下来进行分配----------*/
    osPoint->FAT1[FAT_set].useflag= 2;   //2表示分配给下级目录文件
    //填写该分派新的盘块的参数
    strcpy(dir->fcb[temp].fname,dirName);
    strcpy(dir->fcb[temp].userName,uName);
    dir->fcb[temp].type=DIRECTORY;
    dir->fcb[temp].fatherBlockNum=current;
    dir->fcb[temp].currentBlockNum=FAT_set;
    time_t t = time(0);
    strftime(dir->fcb[temp].time_upload, sizeof(dir->fcb[temp].time_upload), "%Y/%m/%d %H:%M",localtime(&t));
    printf("dir allocated finished! %s\n",dir->fcb[temp].time_upload);
    //初始化子目录文件盘块
    dir=(struct dirFile*)(osPoint->data[FAT_set-33]);   //定位到子目录盘块号
    dir->init(current,FAT_set,dirName);//iFAT是要分配的块号，这里的current用来指要分配的块的父块号

    fp=fopen(FilePath,"r+");
    fseek(fp,0,SEEK_SET);
    fwrite(BaseAddr,sizeof(char),Content_BlockNum*BlockSize,fp);
    fclose(fp);
    printf("---------------------------------------------------------------\n\n");
    //delete dir;
    return temp;
}

int CDir::removeDir(int delDir)
{
    int i,temp,j;//确保当前目录下有该文件,并记录下该FCB下标
//    struct dirFile *dir;     //当前目录的指针
    if(current==32)
        dir=&(osPoint->root);
    else
        dir=(struct dirFile *)(osPoint->data [current-33]);

    if(dir->fcb[delDir].type!=DIRECTORY)
    {
        printf("Folder not found!\n");
        return 0;
    }

    temp=delDir;

    j = dir->fcb[temp].currentBlockNum;//获取目录存储的盘块
    printf("the block num is %d\n",j);
    struct dirFile *sonDir;     //当前子目录的指针
    sonDir=(struct dirFile *)(osPoint->data[j-33]);

    for(i=1;i<BlockFcbCount;i++)  //查找子目录是否为空目录
    {
        if(sonDir->fcb[i].type!=HXSH)
        {
            printf("file isn't empty!\n");
            return 0;
        }
    }
    dir->fcb[0].needBlockCount--;//表示当前目录下到文件和文件夹总数

    /*开始删除子目录操作*/
    osPoint->FAT1[j].useflag=0;     //fat清空
    char *p=osPoint->data[j-33];      //格式化子目录
    memset(p,0,BlockSize);
    dir->fcb[temp].initialize();          //回收子目录占据目录项

    fp=fopen(FilePath,"r+");
    fseek(fp,0,SEEK_SET);
    fwrite(BaseAddr,sizeof(char),Content_BlockNum*BlockSize,fp);
    fclose(fp);
    printf("---------------------------------------------------------------\n\n");
    return 1;
}

int CDir::listShow()
{
    int i,DirCount=0,FileCount=0;
    //搜索当前目录
    if(current==32)
        dir=&(osPoint->root);
    else
        dir=(struct dirFile *)(osPoint->data [current-33]);

    for(i=1;i<BlockFcbCount;i++)
    {
        if(dir->fcb[i].type==GENERAL)
        {   //查找普通文件
            FileCount++;
            printf("%s     file.\n",dir->fcb[i].fname);
        }
        if(dir->fcb[i].type==DIRECTORY)
        {   //查找目录文件
            DirCount++;
            printf("%s     folder.\n",dir->fcb[i].fname);
        }
    }
    printf("\nThere is %d files, %d folders\n\n",FileCount,DirCount);
    printf("--------------------------------------------------------\n\n");
    //delete dir;
    return 1;
}

int CDir::changeDir(int changeID,int client_sfd)
{
    if(current==32)
        dir=&(osPoint->root);
    else
        dir=(struct dirFile *)(osPoint->data [current-33]);

    /*回到父目录*/
    if(changeID==0)
    {
        if(current==32)
        {
            printf("here is the root directory!\n");
            char root[8];
            sprintf(root,"16\n%d\n",129);//初始化消息头
            write(client_sfd,root,strlen(root));
            return 0;
        }
        current = dir->fcb[0].fatherBlockNum ;
//        currentPath = currentPath.substr(0,currentPath.size() - strlen(dir->fcb[0].fname )-1);
        //显示当前所在目录的路径
        if(current==32)
            dir=&(osPoint->root);
        else
            dir=(struct dirFile *)(osPoint->data [current-33]);

        char contentSend[512];
        char buffer[60];
        int count=dir->fcb[0].needBlockCount;
        sprintf(contentSend,"16\n%d\n",dir->fcb[0].needBlockCount);//初始化消息头
        for(int i=1;i<BlockFcbCount;i++)
        {
            if(dir->fcb[i].type==GENERAL)
            {   //查找普通文件
                sprintf(buffer,"%d\n1\n%d\n%s\n%s\n%s\n",i,dir->fcb[i].size,dir->fcb[i].fname,
                        dir->fcb[i].userName,dir->fcb[i].time_upload);
                strcat(contentSend,buffer);
            }
            if(dir->fcb[i].type==DIRECTORY)
            {   //查找目录文件
                sprintf(buffer,"%d\n0\n%d\n%s\n%s\n%s\n",i,dir->fcb[i].size,dir->fcb[i].fname,
                        dir->fcb[i].userName,dir->fcb[i].time_upload);
                strcat(contentSend,buffer);
            }
        }
        printf("the content is \n%s",contentSend);
        write(client_sfd,contentSend,strlen(contentSend));
        printf("-------------------------------------------------------------\n\n");
        return 1;
    }

    if(dir->fcb[changeID].type!=DIRECTORY){
        printf("this is not an folder!\n");
        return 0;
    }

    //修改当前文件信息
    current=dir->fcb [changeID].currentBlockNum ;
    dir=(struct dirFile *)(osPoint->data [current-33]);
    currentPath = currentPath+dir->fcb [changeID].fname +"\\";

    char contentSend[512];
    char buffer[60];
//    int count=dir->fcb[0].needBlockCount;
    sprintf(contentSend,"16\n%d\n",dir->fcb[0].needBlockCount);//初始化消息头
    for(int i=1;i<BlockFcbCount;i++)
    {
        if(dir->fcb[i].type==GENERAL)
        {   //查找普通文件
            sprintf(buffer,"%d\n1\n%d\n%s\n%s\n%s\n",i,dir->fcb[i].size,dir->fcb[i].fname,
                    dir->fcb[i].userName,dir->fcb[i].time_upload);
            strcat(contentSend,buffer);
        }
        if(dir->fcb[i].type==DIRECTORY)
        {   //查找目录文件
            sprintf(buffer,"%d\n0\n%d\n%s\n%s\n%s\n",i,dir->fcb[i].size,dir->fcb[i].fname,
                    dir->fcb[i].userName,dir->fcb[i].time_upload);
            strcat(contentSend,buffer);
        }
    }
    printf("father is %d\n the content is \n%s",dir->fcb[0].fatherBlockNum,contentSend);
    write(client_sfd,contentSend,strlen(contentSend));
    printf("-------------------------------------------------------------\n\n");
    return 1;
}
