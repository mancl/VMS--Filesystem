#ifndef SOCKETHANDLER_H
#define SOCKETHANDLER_H

//操作请求和响应消息类型定义
#define RES_NEW_DIR 11
#define RES_DEL_FILE 12
#define RES_UPLOAD_FILE 13
#define RES_DOWNLOAD_FILE 14
#define RES_CHG_POS 15
#define RES_CHG_DIR 16

#define RES_CONNECT 31

#define REQ_NEW_DIR 21
#define REQ_DEL_FILE 22
#define REQ_UPLOAD_FILE 23
#define REQ_DOWNLOAD_FILE 24
#define REQ_CHG_POS_START 25
#define REQ_CHG_POS_END 26
#define REQ_CHG_DIR 27

#include<QObject>
#include"socket.h"

//文件信息结构
struct MFile{
    QString fileName;
    QString uploadTime;
    QString userName;
    int fileId;
    int fileType; //0 文件夹 1文件
    int fileSize;
};

//操作请求消息结构
struct CtrlMsg{
    int msgType;
    int fileId;
    int size;
    QString fileName;
    QString usrName;
    void init()
    {
        msgType=-1;
        fileId=-1;
        size=-1;
    }

    char * getdata(){
        QString data;
        if(msgType>=0)
        {
            data.append(QString("%1").arg(msgType) );
            data.append("\n");
        }
        if(fileId>=0)
        {
            data.append(QString::number(fileId, 10));
            data.append("\n");
        }
        if(size>=0)
        {
            data.append(QString::number(size, 10));
            data.append("\n");
        }
       if(fileName!=NULL)
        {
           data.append(fileName);
           data.append("\n");
       }
        if(usrName!=NULL)
       {
           data.append(usrName);
       }

        return data.toLocal8Bit().data();
    }
};

//处理类，用于连接socket操作类和主界面类，在此类进行操作请求消息封装和操作请求返回消息解析。
class SocketHandler :public QObject
{
    Q_OBJECT
public:
    explicit SocketHandler(QObject *parent = 0);
    //单例模式
    static SocketHandler* getInstance();



private:
    static SocketHandler* m_pSocketHandler;
    //Socket操作对象
    Socket* mSocket;
    

    //记录新建的文件夹或者上传文件的信息
    MFile* tempFile;
    
    //处理接收到的操作请求返回信息
    int handleMsg(char *);

signals:
    //用于操作结束后通知界面更新的信号
    void sgnlUpdateRecord(QList<struct MFile> *);
    void sgnlOperateResult(int,int);
    void sgnlAddRecord(struct MFile *);


public slots:
    //连接服务器，并且返回根目录或者记录的上一次的目录，通知界面更新
    void sltConnectServer(QString hostName,int port);
    //上传文件
    void sltUploadFile(QString path,QString userName);
    //下载文件
    void sltDownloadFile(int fileId,int size,QString filePath);
    //进入文件夹
    void sltEnterDir(int fileId);
    //返回上一级文件夹
    void sltBackDir();
    //在当前目录下新建文件夹
    void sltCreateDir(QString dirName,QString userName);
    //删除文件或者文件夹
    void sltDeleteFile(int fileId,int fileType);
    //移动文件或者文件夹
    void sltMoveFile(int fileId,bool moveFlags);

};

#endif // SOCKETHANDLER_H
