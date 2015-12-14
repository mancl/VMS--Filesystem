#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>
#include<QListWidget>
#include<QBoxLayout>
#include<QTableWidget>
#include<QListWidgetItem>
#include<QToolButton>
#include<QPushButton>
#include<QDebug>
#include<QLabel>
#include<QFileDialog>
#include"sockethandler.h"
//主界面窗口类
class MainPage : public QWidget
{
    Q_OBJECT
public:
    explicit MainPage(QWidget *parent = 0);

private:
    //用户名输入框
    QLabel *mUserNameLabel;
    QLineEdit *mUserNameEditText;

    //服务器地址输入框
    QLabel *mHostNameLabel;
    QLineEdit *mHostNameEditText;

    //服务器端口输入框
    QLabel *mHostPortLabel;
    QLineEdit *mHostPortEditText;

    //连接按钮
    QPushButton *mConnectButton;

    //显示文件列表控件
    QListWidget *myFileList;

    //各操作按钮，上传文件，下载文件，移动文件或文件夹，返回上一层目录，新建文件夹，删除文件或文件夹
    QToolButton *mUploadButton;
    QToolButton *mDownloadButton;
    QToolButton *mMoveButton;
    QToolButton *mBackButton;
    QToolButton *mCreateButton;
    QToolButton *mDeleteButton;

    //显示文件信息控件
    QLabel  *mFileInfo;

    //选择上传文件对话框
    QFileDialog *mFileDiag;
    QVBoxLayout *mLayout;

    //标识是否在移动文件或文件夹中
    bool mMovingFlags;

    //连接是否成功到标志
    bool mConnectFlags;

    //记录要移动的文件或文件夹信息
    struct MFile mMovingFile;

    //当前目录下所有文件（包括文件夹）列表信息
    QList<struct MFile> *mFileData;
    
    //文件下载保存路径，服务器地址，用户名，端口
    QString mDownLoadPath;
    QString mHostName;
    QString mUserName;
    int mPort;

    void setOperateButtonEnable(bool enable);
signals:
    //用于触发SocketHandler的槽函数进行相应的操作
    void sgnalConnectServer(QString hostName, int port);
    void sgnalUploadFile(QString path,QString userName);  
    void sgnalDownloadFile(int fileId,int size,QString filePath);
    void sgnalEnterDir(int fileId);
    void sgnalMoveFile(int fileId,bool moveFlags);
    void sgnalBackDir();
    void sgnalCreateDir(QString dirName,QString userName);
    void sgnalDeleteFile(int fileId,int fileType);



public slots:

    //连接服务器，并且显示根目录
    void slotConnectClicked();
    //上传文件
    void slotUploadClicked();
    //下载文件
    void slotDownloadClicked();
    //进入文件夹
    void slotEnterFile(QListWidgetItem*);
    //返回上一级文件夹
    void slotMoveClicked();
    //移动文件或者文件夹
    void slotBackClicked();
    //在当前目录下新建文件夹
    void slotCreateClicked();
    //删除文件或者文件夹
    void slotDeleteClicked();
    
    //接收SocketHandler的信号，更新目录到文件列表
    void slotUpdateData(QList<struct MFile>*);
    void slotAddFile(struct MFile*);

    //接收SocketHandler的信号，处理操作结果
    void slotOperateResult(int type,int state);

    //显示选择文件或文件夹的详细信息
    void slotItemClicked(QListWidgetItem*);


};

#endif // MAINPAGE_H
