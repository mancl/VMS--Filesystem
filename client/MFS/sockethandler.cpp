#include "sockethandler.h"
#include<QStringList>
#include<QDateTime>
#include<QDebug>

SocketHandler* SocketHandler::m_pSocketHandler = NULL;
SocketHandler::SocketHandler(QObject* parent):
        QObject(parent)
{
    mSocket=new Socket();

}

SocketHandler* SocketHandler::getInstance()
{
    if(m_pSocketHandler==NULL)
    {
        m_pSocketHandler=new SocketHandler();
    }
    return m_pSocketHandler;
}


void SocketHandler::sltConnectServer(QString hostName, int port)
{
    if(port>=1200&&port<=65535)
    {
        qDebug()<<"SOCKETHANDLER connectServer";
        int res=mSocket->connect(hostName.toUtf8().data(),port);
        if(res<0)
        {
            qDebug()<<"SOCKETHANDLER connectServer fail!!!!!";
            emit sgnlOperateResult(RES_CONNECT,res);
            return;
        }
         emit sgnlOperateResult(RES_CONNECT,res);
        //读取服务器返回到根目录信息并解析
        char * getdata=mSocket->readMsg();
        handleMsg(getdata);

    }
    else
    {
        mSocket->close();;
    }

}
void SocketHandler::sltUploadFile(QString path,QString userName)
{
    qDebug()<<"SOCKETHANDLER upload:"<<path.toLocal8Bit().data()<<"userName:"<<userName;
    //封装请求上传文件信息
    CtrlMsg ctrlMsg;
    ctrlMsg.init();
    ctrlMsg.msgType=REQ_UPLOAD_FILE;
    QStringList pathlist=path.split("/");
    ctrlMsg.fileName=pathlist.at(pathlist.count()-1);
    FILE* fp;
    if((fp=fopen(path.toLocal8Bit().data(),"r"))!=NULL)
    {
        fseek(fp, 0L, SEEK_END);
        ctrlMsg.size=ftell(fp);
    }
    ctrlMsg.usrName=userName;
    //发送请求信息
    mSocket->write(ctrlMsg.getdata(),strlen(ctrlMsg.getdata()));
    
    //读取操作返回信息并处理
    char * msg=mSocket->readMsg();
    int res=handleMsg(msg);
    
    //返回信息为成功则读取文件并传输
    if(res==0)
    {
        //传输文件
        int resWriteFile= mSocket->writeFile(path.toLocal8Bit().data(),ctrlMsg.size);
        //处理传输文件结果
        if(resWriteFile==0)
        {
            tempFile->fileName=ctrlMsg.fileName;
            tempFile->userName=userName;
            tempFile->fileType=1;//文件
                QDateTime dt;
                QTime time;
                QDate date;
                dt.setTime(time.currentTime());
                dt.setDate(date.currentDate());
            tempFile->uploadTime=dt.toString("yyyy:MM:dd:hh:mm:ss");
            tempFile->fileSize=ctrlMsg.size;
            emit sgnlAddRecord(tempFile);
        }
        else
        {  //res -2文件打开错误 -4 socket写的过程中出错
            emit sgnlOperateResult(RES_UPLOAD_FILE,resWriteFile);
        }
    }
    else
    {    //NO_SPACE	2
        emit sgnlOperateResult(RES_UPLOAD_FILE,res);
    }



}
void SocketHandler::sltDownloadFile(int fileId,int size,QString filePath)
{
    qDebug()<<"SOCKETHANDLER download fileID:"<<fileId<<"Size:"<<size<<"FilePath:"<<filePath;

    CtrlMsg ctrlMsg;
    ctrlMsg.init();
    ctrlMsg.msgType=REQ_DOWNLOAD_FILE;
    ctrlMsg.fileId=fileId;
    mSocket->write(ctrlMsg.getdata(),strlen(ctrlMsg.getdata()));

    int n=mSocket->readFile(filePath.toLocal8Bit().data(),size);

    //-1 socket出错 0成功
    emit sgnlOperateResult(RES_DOWNLOAD_FILE,n);




}
void SocketHandler::sltEnterDir(int fileId)
{
    qDebug()<<"SOCKETHANDLER EnterDir："<<fileId;

    CtrlMsg ctrlMsg;
    ctrlMsg.init();
    ctrlMsg.msgType=REQ_CHG_DIR;
    ctrlMsg.fileId=fileId;
    int n= mSocket->write(ctrlMsg.getdata(),strlen(ctrlMsg.getdata()));

    if(n==0)
    {
        char *msg=mSocket->readMsg();
        handleMsg(msg);
    }
    else
    {
        emit sgnlOperateResult(RES_CHG_DIR,n); //-4 socket写的过程中出错
    }


}
void SocketHandler::sltBackDir()
{
    qDebug()<<"SOCKETHANDLER backDir";
    CtrlMsg ctrlMsg;
    ctrlMsg.msgType=REQ_CHG_DIR;
    ctrlMsg.fileId=0;//0代表向上一级
    int n=mSocket->write(ctrlMsg.getdata(),strlen(ctrlMsg.getdata()));
    if(n==0)
    {
        char *msg=mSocket->readMsg();
	handleMsg(msg);
    }
    else
    {
        //-4 socket写的过程中出错
	emit sgnlOperateResult(RES_CHG_DIR,n); 
    }
}
void SocketHandler::sltCreateDir(QString dirName,QString userName)
{
    qDebug()<<"SOCKETHANDLER CreateDir:"<<dirName;

    CtrlMsg ctrlMsg;
    ctrlMsg.init();
    ctrlMsg.msgType=REQ_NEW_DIR;
    ctrlMsg.fileName=dirName;
    ctrlMsg.usrName=userName;
    int n=mSocket->write(ctrlMsg.getdata(),strlen(ctrlMsg.getdata()));
    if(n==0)
    {
        char *msg=mSocket->readMsg();
        int res=handleMsg(msg);
        if(res==0)
        {
            tempFile->fileName=dirName;
            tempFile->userName=userName;
            tempFile->fileType=0;//0文件夹
                QDateTime dt;
                QTime time;
                QDate date;
                dt.setTime(time.currentTime());
                dt.setDate(date.currentDate());
            tempFile->uploadTime=dt.toString("yyyy:MM:dd:hh:mm:ss");
            emit sgnlAddRecord(tempFile);
        }
        else
        {
            //No space 2
            emit sgnlOperateResult(RES_NEW_DIR,res);
        }

    }
    else
    {
        //-4 socket写的过程中出错
        emit sgnlOperateResult(RES_NEW_DIR,n);
    }

}
void SocketHandler::sltDeleteFile(int fileId,int fileType)
{
    qDebug()<<"SOCKETHANDLER DeleteFile:"<<fileId<<" fileType:"<<fileType;

    CtrlMsg ctrlMsg;
    ctrlMsg.init();
    ctrlMsg.msgType=REQ_DEL_FILE;
    ctrlMsg.fileId=fileId;
    ctrlMsg.size=fileType;
    int n=mSocket->write(ctrlMsg.getdata(),strlen(ctrlMsg.getdata()));
    if(n==0)
    {
        char *msg=mSocket->readMsg();
        int res=handleMsg(msg);
        //0 成功，2文件夹没清空
         emit sgnlOperateResult(RES_DEL_FILE,res);
    }
    else
    {
         //-4 socket写的过程中出错
         emit sgnlOperateResult(REQ_DEL_FILE,n);
    }

}
void SocketHandler::sltMoveFile(int fileId, bool moveFlags)
{
    qDebug()<<"SOCKETHANDLER MoveFile:"<<fileId<<" moveflags:"<<moveFlags;

    CtrlMsg ctrlMsg;
    ctrlMsg.init();
    if(!moveFlags)
    {
        ctrlMsg.msgType=REQ_CHG_POS_START;
        ctrlMsg.fileId=fileId;
    }
    else
    {
        ctrlMsg.msgType=REQ_CHG_POS_END;
    }

    int n=mSocket->write(ctrlMsg.getdata(),strlen(ctrlMsg.getdata()));
    if(n==0)
    {

        if(moveFlags)
        {
            char *msg=mSocket->readMsg();
            int res=handleMsg(msg);
             emit sgnlOperateResult(RES_CHG_POS,res);//0 OK;-2 NO SPACE ;-1 fail >0; field Id;
        }

    }
    else
    {
         emit sgnlOperateResult(RES_CHG_POS,n);//-4 socket写的过程中出错
    }

}
int SocketHandler::handleMsg(char * msg)//return state or file
{
    QString strMsg=QString(msg);
    QStringList itemList=strMsg.split("\n");
    qDebug()<<"receive msg:"<<itemList;

    QString type=(QString)itemList.at(0);
    int itype=type.toInt();
    qDebug()<<"msg type:"<<itype;
    switch(itype)
    {
    case RES_NEW_DIR:
        {
            QString state=(QString)itemList.at(1);
            int istate=state.toInt();
            qDebug()<<"msg state:"<<istate;
            if(istate==0)
            {
                tempFile=new MFile;
                QString id=(QString)itemList.at(2);
                if(id.toInt()==0)//表示文件夹重名
                {
                    return -5;
                }
                tempFile->fileId=id.toInt();

            }
            return istate;
            break;
        }

    case RES_DEL_FILE:
        {
            QString state=(QString)itemList.at(1);
            int istate=state.toInt();
            qDebug()<<"msg state:"<<istate;
            return istate;
            break;
        }
    case RES_UPLOAD_FILE:
        {
            QString state=(QString)itemList.at(1);
            int istate=state.toInt();
            if(istate==0)
            {
                tempFile=new MFile;
                QString id=(QString)itemList.at(2);
                tempFile->fileId=id.toInt();
            }
            return istate;
            qDebug()<<"msg state:"<<istate;
            break;
        }
    case RES_CHG_DIR:
        {
            qDebug()<<"RES_CHG_DIR:";
            QString size=(QString)itemList.at(1);
            int isize=size.toInt();
            if(isize>=0&&isize<129&&itemList.count()==isize*6+3)//129 表示当前已经在根目录下无法再返回上一层目录，无需更新目录信息
            {
                QList<MFile> *list=new QList<MFile>();
                for(int i=0;i<isize;i++)
                {
                    int j=i*6+2;
                    MFile file;
                    QString fileId=(QString)itemList.at(j);
                    QString fileType=(QString)itemList.at(j+1);
                    QString fileSize=(QString)itemList.at(j+2);
                    file.fileId=fileId.toInt();
                    file.fileType=fileType.toInt();
                    file.fileSize=fileSize.toInt();
                    file.fileName=(QString)itemList.at(j+3);
                    file.userName=(QString)itemList.at(j+4);
                    file.uploadTime=(QString)itemList.at(j+5);
                    list->append(file);
                }
                if(isize!=129)
                {
                    emit this->sgnlUpdateRecord(list);
                }

                return 0;
            }
            return -1;

            break;
        }

    case RES_CHG_POS:
        {
            QString state=(QString)itemList.at(1);
            int istate=state.toInt();
            if(istate==0)
            {
                QString fileId=(QString)itemList.at(2);
                if(fileId>0)
                {
                     return fileId.toInt();
                }
               else
                {
                   return -1;
               }
            }
            else
            {
                return istate*-1;
            }
            break;
        }

    }
    return -1;
}
