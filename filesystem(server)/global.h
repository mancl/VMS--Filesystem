#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string>
#include <iostream>
#include <sys/time.h>

using namespace std;

#define GENERAL 1
#define DIRECTORY 2
#define HXSH 0
#define BlockFcbCount 128
#define BlockSize 8192
#define BlockCount 32768
#define DiskSize 80*8192+32688*2048
#define DataBlockSize 2048
struct FCB  //64
{
    char fname[18]; //文件名
    char time_upload[18];//上传时间
    char userName[8];
    char type;
    int size;    //文件大小
    int fatherBlockNum;    //当前的父目录盘块号
    int currentBlockNum;    //当前的盘块
    int needBlockCount;//需要占用的磁盘块数目

    void initialize()
    {
        strcpy(fname,"\0");
        strcpy(userName,"\0");
        strcpy(time_upload,"\0");
        type = HXSH;
        size =0;
        fatherBlockNum = currentBlockNum = needBlockCount= 0;
    }
};

extern struct FCB tempFCB;
/*常量设置*/
extern char* FilePath;
extern int Content_BlockNum;


/*-------------目录文件结构---------------*/
 struct dirFile
{
    struct FCB fcb[BlockFcbCount];//能存储128个目录项，每个占64字节
    void init(int _FatherBlockNum,int _CurrentBlockNum,char *name)//父块号，当前块号，目录名
    {
        strcpy(fcb[0].fname,name); //本身的FCB
        fcb[0].fatherBlockNum=_FatherBlockNum;
        fcb[0].currentBlockNum=_CurrentBlockNum;
        fcb[0].type=DIRECTORY;     //标记目录文件
        for(int i=1;i<BlockFcbCount;i++)
        {
            fcb[i].fatherBlockNum=_CurrentBlockNum; //标记为子项
            fcb[i].type=HXSH;    // 标记为空白项
        }
        fcb[0].needBlockCount=0;
    }
};

/**********************************************************************/
 struct FAT
 {
     int useflag;
     int nextblock;
 };

/**********************************************************************/
struct DISK
{
    FAT FAT1[BlockCount];     //FAT1   暂用盘块  0---7
    struct dirFile root;    //根目录  8
//    char data[BlockCount-3][BlockSize];
    char data[47][BlockSize];//主要用于存储目录 2048为单位块长度

    void format()
    {
        for(int i=0;i<BlockCount;i++)
        {
            FAT1[i].useflag/*=FAT2[i].useflag*/=0;
            FAT1[i].nextblock/*=FAT2[i].nextblock*/=0;
        }
        for(int n=0;n<32;n++)//前面的fat区和根目录区
        {
            FAT1[n].useflag=-2;
//            FAT1[n].nextblock=0;
        }
        root.init(32,32,"/home/");//根目录区
//        memset(data,0,sizeof(data));//数据区
//        for(int i=0;i<32;i++)
//        {
//            for(int j=0;j<2048;j++)
//                data[i][j]=0;
//        }
    }
};


/*-----------------全局变量--------------------------*/
extern FILE *fp;      //磁盘文件地址
extern char * BaseAddr;    //虚拟磁盘空间基地址
extern string currentPath;   //当前路径
extern int current;    //当前目录的盘块号
extern struct DISK *osPoint;    //磁盘操作系统指针



#endif // GLOBAL_H
