#include "mainpage.h"
#include<QInputDialog>
#include<QMessageBox>
MainPage::MainPage(QWidget *parent) :
    QWidget(parent)
{
    mConnectFlags=false;

    setStyleSheet( "QToolButton{ qproperty-iconSize:80px 80px;font-size: 16px } "
                   "QListWidget{background-color:rgba(255,255,255,155);border: 0px solid gray;}"
                   "QListWidget::item{background-color:rgba(255,255,255,0);} "
                   "QListWidget::item:focus{background-color:rgba(125,137,139,50);} ");
    setAutoFillBackground(true);
    QPixmap background("./images/background.jpg");
    QPalette palette;
    palette.setBrush(backgroundRole(), QBrush(background));
    setPalette(palette);
    setFixedSize(680,480);
    setContentsMargins(5,5,5,0);



    mUserNameLabel=new QLabel();
    mUserNameLabel->setText("UserName：");
    mUserNameEditText=new QLineEdit();
    mUserNameEditText->setText("lana");

    mHostNameLabel=new QLabel();
    mHostNameLabel->setText("Server IP:");
    mHostNameEditText=new QLineEdit();
    mHostNameEditText->setFixedWidth(150);
    mHostNameEditText->setText("127.0.0.1");

    mHostPortLabel=new QLabel();
    mHostPortLabel->setText("Server Port：");
    mHostPortEditText=new QLineEdit();
    mHostPortEditText->setText("8500");

    mConnectButton=new QPushButton();
    mConnectButton->setText("Connect");


    myFileList=new QListWidget(this);
    QPixmap background2("./images/bg.png");
    QPalette pl = myFileList->palette();
    pl.setBrush(myFileList->backgroundRole(),QBrush(background2));
    myFileList->setPalette(pl);
    myFileList->setAutoFillBackground(true);



    myFileList->setIconSize(QSize(50,50));
    myFileList->setViewMode(QListView::IconMode);
    myFileList->setDragEnabled(false);
    myFileList->setFixedHeight(350);

    myFileList->setContentsMargins(10,10,10,10);

    mUploadButton=new QToolButton(this);
    mUploadButton->setText("Upload");

    mDownloadButton=new QToolButton(this);
    mDownloadButton->setText("Download");

    mBackButton=new QToolButton(this);
    mBackButton->setText("Back");

    mMoveButton=new QToolButton(this);
    mMoveButton->setText("Move");
    mMoveButton->setCheckable(true);
    setStyleSheet("QToolButton{ qproperty-iconSize:80px 80px} "
                   "QToolButton:checked {color:rgba(255,0,0,255);} ");

    mCreateButton=new QToolButton(this);
    mCreateButton->setText("Create");

    mDeleteButton=new QToolButton(this);
    mDeleteButton->setText("Delete");

    mFileInfo=new QLabel(this);
    mFileInfo->setMargin(10);

    QHBoxLayout *layout1=new QHBoxLayout();

    layout1->addWidget(mUserNameLabel);
    layout1->addWidget(mUserNameEditText);
    layout1->addWidget(mHostNameLabel);
    layout1->addWidget(mHostNameEditText);
    layout1->addWidget(mHostPortLabel);
    layout1->addWidget(mHostPortEditText);
    layout1->addWidget(mConnectButton);
    layout1->addStretch();

    QHBoxLayout *layout2=new QHBoxLayout();

    layout2->addWidget(mUploadButton);
    layout2->addWidget(mDownloadButton);
    layout2->addWidget(mBackButton);
    layout2->addWidget(mMoveButton);
    layout2->addWidget(mCreateButton);
    layout2->addWidget(mDeleteButton);
    layout2->addStretch();
    layout2->setSpacing(10);


    mLayout=new QVBoxLayout(this);
    mLayout->addLayout(layout1);
    mLayout->addSpacing(5);
    mLayout->addLayout(layout2);
    mLayout->addSpacing(5);
    mLayout->addWidget(myFileList);
    mLayout->addSpacing(5);
    mLayout->addWidget(mFileInfo);



    mMovingFlags=false;
    setOperateButtonEnable(false);
    connect(myFileList,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT( slotEnterFile(QListWidgetItem*)));
    connect(myFileList,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(slotItemClicked(QListWidgetItem*)));
    connect(mUploadButton,SIGNAL(clicked()),this,SLOT(slotUploadClicked()));
    connect(mDownloadButton,SIGNAL(clicked()),this,SLOT(slotDownloadClicked()));
    connect(mMoveButton,SIGNAL(clicked()),this,SLOT(slotMoveClicked()));
    connect(mBackButton,SIGNAL(clicked()),this,SLOT(slotBackClicked()));
    connect(mDeleteButton,SIGNAL(clicked()),this,SLOT(slotDeleteClicked()));
    connect(mCreateButton,SIGNAL(clicked()),this,SLOT(slotCreateClicked()));
    connect(mConnectButton,SIGNAL(clicked()),this,SLOT(slotConnectClicked()));

    connect(this,SIGNAL(sgnalBackDir()),SocketHandler::getInstance(),SLOT(sltBackDir()));
    connect(this,SIGNAL(sgnalConnectServer(QString,int)),SocketHandler::getInstance(),SLOT(sltConnectServer(QString,int)));
    connect(this,SIGNAL(sgnalCreateDir(QString,QString)),SocketHandler::getInstance(),SLOT(sltCreateDir(QString,QString)));
    connect(this,SIGNAL(sgnalDeleteFile(int,int)),SocketHandler::getInstance(),SLOT(sltDeleteFile(int,int)));
    connect(this,SIGNAL(sgnalDownloadFile(int,int,QString)),SocketHandler::getInstance(),SLOT(sltDownloadFile(int,int,QString)));
    connect(this,SIGNAL(sgnalEnterDir(int)),SocketHandler::getInstance(),SLOT(sltEnterDir(int)));
    connect(this,SIGNAL(sgnalUploadFile(QString,QString)),SocketHandler::getInstance(),SLOT(sltUploadFile(QString,QString)));
    connect(this,SIGNAL(sgnalMoveFile(int,bool)),SocketHandler::getInstance(),SLOT(sltMoveFile(int,bool)));


    connect(SocketHandler::getInstance(),SIGNAL(sgnlUpdateRecord(QList<MFile>*)),this,SLOT(slotUpdateData(QList<MFile>*)));
    connect(SocketHandler::getInstance(),SIGNAL(sgnlOperateResult(int,int)),this,SLOT(slotOperateResult(int,int)));
    connect(SocketHandler::getInstance(),SIGNAL(sgnlAddRecord(MFile*)),this,SLOT(slotAddFile(MFile*)));
//    emit this->sgnalConnectServer(mHostName,mPort);

}
void MainPage::slotEnterFile(QListWidgetItem* item)
{
    int i =myFileList->currentRow();
    qDebug()<<"currentRow:"<<i<<item->checkState();
    if(i>=0&&mFileData->at(i).fileType==0)
    {
        emit sgnalEnterDir(mFileData->at(i).fileId);
    }

}
void MainPage::slotDownloadClicked()
{
    int i= myFileList->currentRow();
   qDebug()<<"mainpage:download clicked~"<<i;
   if(i>=0&&mFileData->at(i).fileType==1)//文件才能下载
   {
       QString path = QFileDialog::getExistingDirectory(this,"Please select Path",".");
       if(path.length() >0)
       {
           mDownLoadPath=path+"/";
          emit sgnalDownloadFile(mFileData->at(i).fileId,mFileData->at(i).fileSize,mDownLoadPath+mFileData->at(i).fileName);
       }

   }
}
void MainPage::slotUploadClicked()
{
     qDebug()<<"mainpage:upload clicked~";
     QString path = QFileDialog::getOpenFileName(this, "Please select File", ".", "All Files(*.*)");
     if(path.length() >0)
     {
         emit sgnalUploadFile(path,mUserName);
     }
    qDebug()<<"mainpage:upload clicked~";

}

void MainPage::slotMoveClicked()
{
    int i= myFileList->currentRow();
    qDebug()<<"mainpage:move clicked!"<<i;
    if(!mMovingFlags)
    {
        int currentRow= myFileList->currentRow();
        if(currentRow>=0)
        {
            mMoveButton->setChecked(true);
            mMoveButton->setText("Move to");
            QList<QListWidgetItem*> list = myFileList->selectedItems();
            if(list.size() == 0)
            {
                return;
            }
            QListWidgetItem* sel = list[0];
            if (sel)
            {
                int r = myFileList->row(sel);
                mMovingFile=mFileData->at(r);
                emit this->sgnalMoveFile(mFileData->at(r).fileId,mMovingFlags);
            }
            qDebug()<<"mainpage: has select"<<currentRow;
            mMovingFlags=!mMovingFlags;
        }
        else{
            mMoveButton->setChecked(false);
        }
    }
    else
    {
        mMoveButton->setText("Move");
        emit this->sgnalMoveFile(0,mMovingFlags);
        mMovingFlags=!mMovingFlags;
        qDebug()<<"mainpage:has moved"<<myFileList->currentRow();
    }

}
void MainPage::slotBackClicked()
{
    qDebug()<<"mainpage:back clicked!"<<myFileList->currentRow();
    emit sgnalBackDir();

}
void MainPage::slotDeleteClicked()
{
    qDebug()<<"mainpage:delete clicked!"<<myFileList->currentRow();
    QList<QListWidgetItem*> list = myFileList->selectedItems();

    if(list.size() == 0)
    {
        return;
    }
    QListWidgetItem* sel = list[0];
    if (sel)
    {
        int r = myFileList->row(sel);
        emit sgnalDeleteFile(mFileData->at(r).fileId,mFileData->at(r).fileType);
    }
}
void MainPage::slotCreateClicked()
{
    qDebug()<<"mainpage:create clicked!";
    bool ok = FALSE;
    QString path = QInputDialog::getText(this,
    "","please enter your file name!" ,QLineEdit::Normal, QString::null, &ok);
    if ( ok && !path.isEmpty() )
    {
        emit this->sgnalCreateDir(path,mUserName);
    }


}
void MainPage::slotConnectClicked()
{
    qDebug()<<"mainpage:connect clicked~";
    mUserName=mUserNameEditText->text();
    mHostName=mHostNameEditText->text();
    mPort=mHostPortEditText->text().toInt();
    if(!mConnectFlags)
    {
        if(mPort>=1200&&mPort<=65535)
        {
            emit this->sgnalConnectServer(mHostName,mPort);
        }
        else
        {
            QMessageBox::about(this,"Tips","Error invalid Port!");
        }

    }
    else
    {
        //表示Socket断开操作
        emit sgnalConnectServer(mHostName,-1);
        mConnectFlags=false;
        mConnectButton->setText("Connect");
        setOperateButtonEnable(false);
    }


}
void MainPage::slotUpdateData(QList<struct MFile>* list)
{
    mFileData=list;
    if(mFileData!=NULL)
    {
        myFileList->clear();
        for(int i=0;i<mFileData->count();i++)
        {
            struct MFile data=mFileData->at(i);
            QListWidgetItem *item=new QListWidgetItem(myFileList);
            if(data.fileType==1)
            {
                item->setIcon(QIcon("./images/file.png"));
            }
            else if(data.fileType==0)
            {
                item->setIcon(QIcon("./images/dir.png"));
            }
            item->setText(data.fileName);
        }
 }

}
void MainPage::slotOperateResult(int type, int state)
 {
    qDebug()<<"MainPage operateResult type:"<<type<<" state:"<<state;
    QString info="";
     switch(type)
     {
     case RES_NEW_DIR:
         {
             if(state==2)
             {
                 info="Create directory fail,no space!";
             }
             else if(state==-4)
             {
                 info="Create directory fail,network errors!";
             }
             else if(state==-5)
             {
                 info="Create directory fail,Already has this dir!";
             }
             else
             {
                 info="Create directory fail!";
             }
             break;
         }
     case RES_DEL_FILE:
         {
             if(state==0)
             {
                 myFileList->takeItem(myFileList->currentRow());
                 mFileData->removeAt(myFileList->currentRow());
             }

             else if(state==2)
             {
                 info="Delete  fail,directory not cleaned,please clean!";
             }
             else if(state==-4)
             {
                 info="Delete  fail,network errors!!";
             }
             else
             {
                  info="Delete  fail!";
             }
             break;
         }
     case RES_UPLOAD_FILE:
         {
             if(state==2)
             {
                 info="Upload file fail,no space!";
             }

             else if(state==-2)
             {
                 info="Upload file fail,open file error!";
             }
             else if(state==-4)
             {
                 info="Upload file fail,network errors!";
             }
             else
             {
                  info="Upload file fail!";
             }
             break;
         }
     case RES_DOWNLOAD_FILE:
         {
             if(state==0)
             {
                 info="Download file OK,please check!";
             }
             else if(state==-1)
             {
                 info="Download file fail,network errors!";
             }
             else
             {
                  info="Download file fail!";
             }
             break;
         }
     case RES_CHG_POS:
         {
             if(state>0)
             {
                 mMovingFile.fileId=state;
                 this->slotAddFile(&mMovingFile);
             }
             else if(state==-2)
             {
                 info="Change position fail,no space!";
             }
             else if(state==-4)
             {
                 info="Change position fail,network errors!";
             }
             else
             {
                 info="Change position fail!";
             }
             break;
         }
     case RES_CHG_DIR:
         {
             if(state==-4)
             {
                 info="Change directory fail,network errors!";
             }
             else if(state==-1)
             {
                 info="Change directory fail";
             }
             break;
         }
     case RES_CONNECT:
         {
             if(state==0)
             {
                mConnectButton->setText("Disconnect");
                mConnectFlags=true;
                setOperateButtonEnable(true);
             }
             else if(state==-1)
             {
                 info="ERROR opening socket!";
             }
             else if(state==-2)
             {
                 info="ERROR, no such host!";
             }
             else if(state==-3)
             {
                 info="ERROR connecting!";
             }
             else
             {
                  info=" Inetnet error!";
             }
             break;
         }
     }
     if(info.length()>0)
     {
         QMessageBox::about(this,"Tips",info);
     }

 }
void MainPage::slotAddFile(MFile *file)
 {
     mFileData->append(*file);
     QListWidgetItem *item=new QListWidgetItem(myFileList);
     if(file->fileType==1)
     {
         item->setIcon(QIcon("./images/file.png"));
     }
     else if(file->fileType==0)
     {
         item->setIcon(QIcon("./images/dir.png"));
     }
     item->setText(file->fileName);
 }
void MainPage::slotItemClicked(QListWidgetItem *)
{
    int i =myFileList->currentRow();
    qDebug()<<"currentRow:"<<i;
    QString filedata;
    QString nameCaption=mFileData->at(i).fileType==0?"Directory  Name:":"File  Name:";
    filedata.append(nameCaption).append(mFileData->at(i).fileName)
            .append("            Size：").append(QString::number(mFileData->at(i).fileSize/1024+1))
            .append("KB            Date：").append(mFileData->at(i).uploadTime)
            .append("            User:").append(mFileData->at(i).userName);
    mFileInfo->setText(filedata);
}
void MainPage::setOperateButtonEnable(bool enable)
{

    mUploadButton->setEnabled(enable);
    mDownloadButton->setEnabled(enable);;
    mBackButton->setEnabled(enable);
    mMoveButton->setEnabled(enable);
    mCreateButton->setEnabled(enable);
    mDeleteButton->setEnabled(enable);

}
