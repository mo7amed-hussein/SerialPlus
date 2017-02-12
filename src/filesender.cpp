#include "filesender.h"
#include"config.h"
#include<QPushButton>
#include<QLabel>
#include<QHBoxLayout>
#include<QLineEdit>
#include<QGridLayout>
#include<QListWidget>
#include<QGroupBox>
#include<QRadioButton>
#include<QCheckBox>
#include<QProgressBar>
FileSender::FileSender(QWidget *parent) : DataSender(parent)
{
    QLabel *fileLabel=new QLabel(tr("File:"));
    QLineEdit *fileEdit=new QLineEdit;
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

    QRadioButton *allfile=new QRadioButton(tr("Send The Whole File(e.g. hex file) "));
    QRadioButton *fileData=new QRadioButton(tr("Send Data only (e.g. text file) "));

    QProgressBar *sendBar=new QProgressBar;
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


   // mainLayout->addLayout(dataLayout,0,0);
   /* mainLayout->addWidget(fileLabel,0,0);
    mainLayout->addWidget(fileEdit,0,1);
    mainLayout->addWidget(fileBtn,0,2);
    mainLayout->addWidget(sendTypeGroup,1,1);
    mainLayout->addWidget(radioGroup,2,1);
    mainLayout->addLayout(sendBtnLayout,3,1);
    mainLayout->addWidget(sendBar,4,1);*/
    //mainLayout->addWidget(radioGroup,2,2);



}

void FileSender::send()
{

}
