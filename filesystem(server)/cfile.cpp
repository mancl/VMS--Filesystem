#include "cfile.h"

CFile::CFile()
{
}
/*-----------接收上传的文件，在当前目录下创建文本文件,并写入文件系统---------------*/
int CFile::receive_uploadFile(char *name,int size,char *user,int client_sockfd)
{
    int i;//temp,
    int emptyNum = 0,isFound = 0;        //空闲目录项个数
    if(current==32)
        dir=&(osPoint->root);
    else
        dir=(struct dirFile *)(osPoint->data [current-33]);

    int needBlockNum=size/DataBlockSize +1;
    if(size%DataBlockSize==0)  needBlockNum--;
    printf("needBlockNUm=%d\n",needBlockNum);

    int iFAT[needBlockNum];//记录需要存储数据的盘块
    //查看目录是否已满 为了避免同名的文本文件
    for(i=1;i<BlockFcbCount;i++)
    {
        if(dir->fcb[i].type == HXSH && isFound == 0)
        {
            emptyNum = i;
            isFound = 1;
            break;
        }
        else if(dir->fcb[i].type==GENERAL && strcmp(dir->fcb[i].fname,name)==0 )
        {
            printf("can not create the file with the same name!\n");
            return 0;
        }
    }
    if(emptyNum == 0)
    {
        printf("directory is full!\n");
        return 0;
    }

    //查找FAT表寻找空白区，用来分配磁盘块号j  从Content_BlockNum后才是记录数据的
    int cnt=0;
    for(i = Content_BlockNum;i<BlockCount && cnt<needBlockNum;i++)
    {
        if(osPoint->FAT1[i].useflag==0)//找到空闲的存储盘块
        {
            iFAT[cnt]=i;
            cnt++;
        }
    }

    printf("ifat = %d\n",iFAT[0]);

    if(i==BlockCount)
    {
        printf("磁盘已满!\n");
        return 0;
    }

    dir->fcb[0].needBlockCount++;//表示当前目录下到文件和文件夹总数

    /*------进入分配阶段---------*/
    //分配磁盘块
    for(int t=0;t<needBlockNum;t++)
    {
        osPoint->FAT1[iFAT[t]].useflag=1;
        if(t<needBlockNum-1)//最后一个盘块的nextBlock为0
              osPoint->FAT1[iFAT[t]].nextblock=iFAT[t+1];
         printf("iFAT[t]=%d  next= %d\n",iFAT[t],osPoint->FAT1[iFAT[t]].nextblock);
    }

    //填写该分派新的盘块的参数
    strcpy(dir->fcb[emptyNum].fname,name);
    strcpy(dir->fcb[emptyNum].userName,user);
    dir->fcb[emptyNum].type=GENERAL;
    dir->fcb[emptyNum].fatherBlockNum=current;
    dir->fcb[emptyNum].currentBlockNum=iFAT[0];//为文件存储的第一个盘块地址
    dir->fcb[emptyNum].size =size;
    dir->fcb[emptyNum].needBlockCount=needBlockNum;

    time_t t = time(0);
    strftime(dir->fcb[emptyNum].time_upload, sizeof(dir->fcb[emptyNum].time_upload), "%Y/%m/%d %H:%M",localtime(&t));
    printf("file allocated finished!%s\n",dir->fcb[emptyNum].time_upload);

    fp= fopen(FilePath,"r+");//r+ 才能不改变文件内容
    int offset=0;//offset to insert data to the filesystem
    int leftLength=0;
    int writeCnt=0;
    leftLength=size;
    int dataNeedRead=0;

    int rLen=0;
    int dataCount=0;
    char receive_buffer[DataBlockSize];
    bzero(receive_buffer,DataBlockSize);
    for(int n=0;n<needBlockNum;n++)
    {
        dataCount=0;
        if(leftLength>DataBlockSize){
            dataNeedRead=DataBlockSize;
        }
        else{
            dataNeedRead=leftLength;
        }
        while(dataNeedRead>0)
        {
            rLen=read(client_sockfd,receive_buffer+dataCount,dataNeedRead);
            printf("the receice length=%d\n",rLen);
            dataNeedRead=dataNeedRead-rLen;
            dataCount+=rLen;
        }
        if(dataNeedRead==0)
        {
            offset=DataBlockSize*(iFAT[n]-Content_BlockNum)+BlockSize*Content_BlockNum;
            printf("ifat=%d\n",iFAT[n]);
            fseek(fp,offset,SEEK_SET);
            if(leftLength>DataBlockSize)
            {
                writeCnt=fwrite(receive_buffer,1,DataBlockSize,fp);
                fflush(fp);
            }
            else
            {
                writeCnt=fwrite(receive_buffer,1,DataBlockSize,fp);
                fflush(fp);
            }
            printf("RECEIVE : writeCnt= %d %d \n",writeCnt,n);

            leftLength=leftLength-DataBlockSize;
            printf("RECEIVE : leftLength= %d\n",leftLength);

            bzero(receive_buffer,DataBlockSize);

        }
    }

    fseek(fp,0,SEEK_SET);
    fwrite(BaseAddr,sizeof(char),Content_BlockNum*BlockSize,fp);

    fclose(fp);
    printf("-----------------------------------------------\n\n");
    return 1;
}

int CFile::createFile(char *name, int size, char *user)
{
    int i;//temp,
    int emptyNum = 0,isFound = 0;        //空闲目录项个数
    if(current==8)
        dir=&(osPoint->root);
    else
        dir=(struct dirFile *)(osPoint->data [current-9]);

    int needBlockNum=size/BlockSize +1;
    if(size%BlockSize==0)  needBlockNum--;

    int iFAT[needBlockNum];//记录需要存储数据的盘块
    //查看目录是否已满 为了避免同名的文本文件
    for(i=1;i<BlockFcbCount;i++)
    {
        if(dir->fcb[i].type == HXSH && isFound == 0)
        {
            emptyNum = i;
            isFound = 1;
        }
        else if(dir->fcb[i].type==GENERAL && strcmp(dir->fcb[i].fname,name)==0 )
        {
            printf("can not create the file with the same name!\n");
            return 0;
        }
    }
    if(emptyNum == 0)
    {
        printf("directory is full!\n");
        return 0;
    }

    //查找FAT表寻找空白区，用来分配磁盘块号j  从Content_BlockNum后才是记录数据的
    int cnt=0;
    for(i = Content_BlockNum;i<BlockCount && cnt<needBlockNum;i++)
    {
        if(osPoint->FAT1[i].useflag==0)//找到空闲的存储盘块
        {
            iFAT[cnt]=i;
            cnt++;
        }
    }

    printf("ifat = %d\n",iFAT[0]);

    if(i==BlockCount)
    {
        printf("磁盘已满!\n");
        return 0;
    }

    dir->fcb[0].needBlockCount++;//表示当前目录下到文件和文件夹总数

    /*------进入分配阶段---------*/
    //分配磁盘块
    for(int t=0;t<needBlockNum;t++)
    {
        osPoint->FAT1[iFAT[t]].useflag=1;
        if(t<needBlockNum-1)//最后一个盘块的nextBlock为0
              osPoint->FAT1[iFAT[t]].nextblock=iFAT[t+1];
         printf("iFAT[t]=%d  next= %d\n",iFAT[t],osPoint->FAT1[iFAT[t]].nextblock);
    }

    //填写该分派新的盘块的参数
    strcpy(dir->fcb[emptyNum].fname,name);
    strcpy(dir->fcb[emptyNum].userName,user);
    dir->fcb[emptyNum].type=GENERAL;
    dir->fcb[emptyNum].fatherBlockNum=current;
    dir->fcb[emptyNum].currentBlockNum=iFAT[0];//为文件存储的第一个盘块地址
    dir->fcb[emptyNum].size =size;
    dir->fcb[emptyNum].needBlockCount=needBlockNum;
    time_t t = time(0);
    strftime(dir->fcb[emptyNum].time_upload, sizeof(dir->fcb[emptyNum].time_upload), "%Y/%m/%d %H%M",localtime(&t));
//    printf("file allocated finished!%s\n",dir->fcb[emptyNum].time_upload);

    fp= fopen(FilePath,"r+");//r+ 才能不改变文件内容
    int offset=0;//offset to insert data to the filesystem
    int leftLength=0;
    int writeCnt=0;
    leftLength=size;
    char *buffer=(char *)malloc(size);
    for(int n=0;n<needBlockNum;n++)
    {
        memset(buffer,'V',size);
//        printf("the receice is %s\n",receive_buffer);
        offset=BlockSize*iFAT[n];
//        printf("CREATE : offset = %d\n",offset);
        fseek(fp,offset,SEEK_SET);
        //将上传过来的文件内容写进文件系统中
        if(leftLength>=BlockSize)
        {
            writeCnt=fwrite(buffer+n*BlockSize,1,BlockSize,fp);//
            fflush(fp);
            printf("CREATE : writeCnt= %d %d \n",writeCnt,n);
        }
        else
        {
            writeCnt=fwrite(buffer+n*BlockSize,1,leftLength,fp);//
            printf("CREATE : writeCnt= %d %d\n",writeCnt,n);
        }
        leftLength=leftLength-BlockSize;
    }
    free(buffer);
    fseek(fp,0,SEEK_SET);
    fwrite(BaseAddr,sizeof(char),Content_BlockNum*BlockSize,fp);
    fclose(fp);

    printf("-----------------------------------------------\n\n");
    return 1;
}


int CFile::check(char *name,int size)
{
    int i;//temp,
    int emptyNum = 0,isFound = 0;        //空闲目录项个数
    if(current==32)
        dir=&(osPoint->root);
    else
        dir=(struct dirFile *)(osPoint->data [current-33]);

    int needBlockNum=size/DataBlockSize +1;
    if(size%DataBlockSize==0)  needBlockNum--;
    //查看目录是否已满 为了避免同名的文本文件
    for(i=1;i<BlockFcbCount;i++)
    {
        if(dir->fcb[i].type == HXSH && isFound == 0)
        {
            emptyNum = i;
            isFound = 1;
        }
        else if(dir->fcb[i].type==GENERAL && strcmp(dir->fcb[i].fname,name)==0 )
        {
            printf("CHECK :can not create the file with the same name!\n");
            return 0;
        }
    }
    if(emptyNum == 0)
    {
        printf("directory is full!\n");
        return 0;
    }

    //查找FAT表寻找空白区，用来分配磁盘块号j  从Content_BlockNum后才是记录数据的
    int cnt=0;
    for(i = Content_BlockNum;i<BlockCount && cnt<needBlockNum;i++)
    {
        if(osPoint->FAT1[i].useflag==0)//找到空闲的存储盘块
        {
            cnt++;
        }
    }
    if(i==BlockCount)
    {
        printf("the disk is full!\n");
        return 0;
    }
    return emptyNum;
}


int CFile::send_downLoad(int file_set,int client_sockfd)
{
    int i=0;
    if(current==32)
        dir=&(osPoint->root);
    else
        dir=(struct dirFile *)(osPoint->data [current-33]);

    if(dir->fcb[file_set].type!=GENERAL){
        printf("File not found!\n");
        return 0;
    }

    int size=dir->fcb[file_set].size;
//    printf("the size is %d\n",size);
    int needBlockNum=size/DataBlockSize +1;
    if(size%DataBlockSize==0)  needBlockNum--;
    int iFAT[needBlockNum];//记录存储数据的盘块

    //记录该文件存储在的盘块
   iFAT[0]= dir->fcb[file_set].currentBlockNum;
   printf("SEND : the save block is %d\n",iFAT[0]);
   for(int t=0;t<needBlockNum-1;t++)
   {
       if(osPoint->FAT1[iFAT[t]].nextblock)
       {
            iFAT[t+1]=osPoint->FAT1[iFAT[t]].nextblock;
            printf("SEND : the save block is %d\n",iFAT[t+1]);
       }
   }

    char *fileData;
    int offset=0;

    if(size <DataBlockSize){
        fileData=(char*)malloc(size);
    }
    else{
        fileData=(char*)malloc(DataBlockSize);
    }

    int sendCnt;
    int leftlength=0;
    leftlength=size;

    fp=fopen(FilePath,"r");
    for(i=0;i<needBlockNum;i++)
    {
        offset=DataBlockSize*(iFAT[i]-Content_BlockNum)+BlockSize*Content_BlockNum;
        printf("SEND : offset = %d %d\n",offset,i);
        fseek(fp,offset,SEEK_SET);
        memset(fileData,0,DataBlockSize);
        if(leftlength>DataBlockSize)
        {
            int count=fread(fileData,1,DataBlockSize,fp);
//            printf("the file is \n %s\n",fileData);
//            printf("strlen=%d\n",strlen(fileData));
            sendCnt=send(client_sockfd,fileData,count,0);
            printf("the read out data = %d %d\n",sendCnt,count);
        }
        else
        {
//            memset(fileData,0,BlockSize);
            int readDataCnt=fread(fileData,1,leftlength,fp);
//            printf("the file is \n %s\n",fileData);
//            printf("strlen=%d\n",strlen(fileData));
            sendCnt=send(client_sockfd,fileData,readDataCnt,0);
            printf("the read out data = %d  %d  %d\n",sendCnt,readDataCnt);
        }
        leftlength=leftlength-DataBlockSize;
        printf("leftLength=%d\n",leftlength);
    }
    free(fileData);
    fclose(fp);
}

int CFile::delFile(int delID)
{
    int temp,j;
    //确保当前目录下有该文件,并且记录下它的FCB下标
//    struct dirFile *dir;     //当前目录的指针
    if(current==32)
        dir=&(osPoint->root);
    else
        dir=(struct dirFile *)(osPoint->data [current-33]);

    if(dir->fcb[delID].type!=GENERAL)
    {
        printf("File not found!\n");
        return 0;
    }

     dir->fcb[0].needBlockCount--;//表示当前目录下到文件和文件夹总数
//    从打开列表中删除
//   int count;
   int nextBlock;
   temp=delID;
    /*开始删除文件操作*/
   j = dir->fcb[temp].currentBlockNum ;    //查找盘块号j
   printf("the FCB num is %d\n",j);
//    count=dir->fcb[temp].needBlockCount;//获取所需的盘块数目
    while(1)
    {
        osPoint->FAT1[j].useflag=0;     //fat1,fat2表标记为空白
       //暂时不清理数据块内容，只在索引处标明已清空
        nextBlock= osPoint->FAT1[j].nextblock;
        printf("the nextblock is %d\n",nextBlock);
        if(nextBlock)
        {
            osPoint->FAT1[j].nextblock=0;//清空
            j=nextBlock;
        }
        else
        {
            break;
        }
    }

    dir->fcb[temp].initialize();    //type=0;     //标记该目录项为空文件
    fp=fopen(FilePath,"r+");
    fseek(fp,0,SEEK_SET);
    fwrite(BaseAddr,sizeof(char),Content_BlockNum*BlockSize,fp);
    fclose(fp);

    printf("------------------------------------------------------------\n\n");
    //delete dir;
    return 1;
}

int CFile::fileChangeDir(int fSID,int tempBlock)
{
    int emptyNum,isFound;
    if(current==32)
        dir=&(osPoint->root);
    else
        dir=(struct dirFile *)(osPoint->data [current-33]);

    if(tempBlock==0)
    {
        tempFCB.initialize();
        tempFCB=dir->fcb[fSID];
        return current;
    }
    else
    {
        tempFCB.fatherBlockNum=dir->fcb[0].currentBlockNum; //移动的文件的父目录为当前目录
        int Type=tempFCB.type;
        isFound=0;
        //查看目录是否已满 为了避免同名的文本文件
        for(int i=1;i<BlockFcbCount;i++)
        {
            if(dir->fcb[i].type == HXSH && isFound == 0)
            {
                emptyNum = i;
                isFound = 1;
            }
            else if((dir->fcb[i].type==GENERAL || dir->fcb[i].type==DIRECTORY) && strcmp(dir->fcb[i].fname,tempFCB.fname)==0 )
            {
                printf("CHANGE : can not create the file with the same name!\n");
                return 0;
            }
        }
        if(emptyNum == 0)
        {
            printf("directory is full!\n");
            return 0;
        }

        dir->fcb[0].needBlockCount++;

        dir->fcb[emptyNum]=tempFCB;//将移动的文件所在的新目录上分配空间,存储信息

        if(tempBlock==32)
            dir=&(osPoint->root);
        else
            dir=(struct dirFile *)(osPoint->data [tempBlock-33]);

        dir->fcb[0].needBlockCount--;
        dir->fcb[fSID].initialize();

        if(Type==2){
            int FAT_SET=tempFCB.currentBlockNum;
            dir=(struct dirFile*)(osPoint->data[FAT_SET-33]);
            dir->fcb[0].fatherBlockNum=current;
        }

        printf("the new father is %d\n",current);

        fp=fopen(FilePath,"r+");
        fseek(fp,0,SEEK_SET);
        fwrite(BaseAddr,sizeof(char),Content_BlockNum*BlockSize,fp);
        fclose(fp);
        printf("---------------------------------------------------------------\n\n");
        return emptyNum;
    }
}
