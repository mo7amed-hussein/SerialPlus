#include "filesender.h"
#include"config.h"
#include<QPushButton>
#include<QLabel>
#include<QHBoxLayout>
#include<QLineEdit>
#include<QGridLayout>
#include<QListWidget>
#include<QTextStream>
#include<QGroupBox>
#include<QRadioButton>
#include<QCheckBox>
#include<QFileDialog>
#include<QProgressBar>
#include<QDebug>
FileSender::FileSender(QWidget *parent) : DataSender(parent)
{
    QLabel *fileLabel=new QLabel(tr("File:"));
    fileEdit=new QLineEdit;
   // dataTyper->setPlaceholderText(tr("type to send"));
    QPushButton *sendBtn=new QPushButton(tr("Send"),this);
    QPushButton *cancelBtn=new QPushButton(tr("Cancel"),this);
    QPushButton *fileBtn=new QPushButton(tr("..."),this);

    QHBoxLayout *fileLayout=new QHBoxLayout;
    fileLayout->addWidget(fileLabel);
    fileLayout->addWidget(fileEdit);
    fileLayout->addWidget(fileBtn);

     QHBoxLayout *sendBtnLayout=new QHBoxLayout;

     sendBtnLayout->setContentsMargins(0,5,0,5);
     sendBtnLayout->addWidget(sendBtn);
     //sendBtnLayout->addStretch();
     sendBtnLayout->addWidget(cancelBtn);
     sendBtnLayout->addStretch();
     //sendBtnLayout->addStretch();


    QGroupBox *sendTypeGroup=new QGroupBox;

    allfile=new QRadioButton(tr("Send The Whole File(e.g. hex file) "));

    QRadioButton *fileData=new QRadioButton(tr("Send Data only (e.g. text file) "));
    fileData->setChecked(true);

    sendBar=new QProgressBar;
    QHBoxLayout *sendTypeLayout=new QHBoxLayout;
    sendTypeLayout->addWidget(allfile);
    sendTypeLayout->addWidget(fileData);
   // radioLayout->addWidget(cf);
    sendTypeLayout->addStretch();
    sendTypeLayout->setContentsMargins(0,0,0,0);
    sendTypeGroup->setLayout(sendTypeLayout);
   // sendTypeGroup->setContentsMargins(0,0,0,0);




    QGroupBox *radioGroup=new QGroupBox;

    QRadioButton *cr=new QRadioButton(tr("CR"));
    QRadioButton *lf=new QRadioButton(tr("LF"));
    QRadioButton *cf=new QRadioButton(tr("CR+LF"));

    QHBoxLayout *radioLayout=new QHBoxLayout;
    radioLayout->addWidget(cr);
    radioLayout->addWidget(lf);
    radioLayout->addWidget(cf);
    radioLayout->addStretch();
    radioLayout->setContentsMargins(0,0,0,0);
    radioGroup->setLayout(radioLayout);
   // radioGroup->setContentsMargins(0,0,0,0);

    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(WIDGETS_LEFT_MARGIN,WIDGETS_TOP_MARGIN,0,0);

    mainLayout->addLayout(fileLayout);
    mainLayout->addWidget(sendTypeGroup);
    mainLayout->addWidget(radioGroup);
    mainLayout->addLayout(sendBtnLayout);
    mainLayout->addWidget(sendBar);
    mainLayout->addStretch();

    connect(fileBtn,&QPushButton::clicked,this,&FileSender::getFile);
    connect(sendBtn,&QPushButton::clicked,this,&FileSender::sendSlot);
}

void FileSender::send()
{

}
 void FileSender::getFile()
 {
     QString filename=QFileDialog::getOpenFileName(this,tr("Select File"),QDir::currentPath(),"Text File(*.txt)");
         if(filename.isEmpty())
             return;
         fileEdit->setText(filename);
         filePath=filename;

 }
 void FileSender::sendCommands()
 {
    QFile f(filePath);
    if(f.open(QIODevice::ReadOnly |QIODevice::Text))
    {
        while (!f.atEnd()) {
           QTextStream txt(&f);
           QString cmd=txt.readLine();
           emit sendDataSig(cmd);

        }
        f.close();

    }

 }

 void FileSender::sendData()
 {

 }

 void FileSender::sendSlot()
  {
    if(allfile->isChecked())
    {
        sendData();
        qDebug()<<"data";
    }
    else
    {
        qDebug()<<"command";
        sendCommands();
    }
  }
