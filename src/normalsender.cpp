#include "normalsender.h"
#include"config.h"
#include<QComboBox>
#include<QPushButton>
#include<QLabel>
#include<QHBoxLayout>
#include<QLineEdit>
#include<QGridLayout>
#include<QListWidget>
#include<QGroupBox>
#include<QRadioButton>
#include<QCheckBox>

NormalSender::NormalSender(QWidget *parent) : DataSender(parent)
{
    QLabel *dataLabel=new QLabel(tr("Data:"));
    QLabel *historyLabel=new QLabel(tr("Data\nHistory:"));
    dataTyper=new QLineEdit;
    dataTyper->setPlaceholderText(tr("type to send"));
    QPushButton *sendBtn=new QPushButton(tr("Send"),this);
    connect(sendBtn,&QPushButton::clicked,this,&NormalSender::send);

    QListWidget *historyList=new QListWidget;

    QGroupBox *editTypeGroup=new QGroupBox;

    QRadioButton *ascii=new QRadioButton(tr("ASCII"));
    QRadioButton *hex=new QRadioButton(tr("Hex"));
    QCheckBox *del=new QCheckBox(tr("clear after send"));
    QHBoxLayout *editTypeLayout=new QHBoxLayout;
    editTypeLayout->setContentsMargins(0,0,0,0);
    editTypeLayout->addWidget(ascii);
    editTypeLayout->addWidget(hex);editTypeLayout->addWidget(del);
    editTypeLayout->addStretch();
    editTypeGroup->setLayout(editTypeLayout);
    editTypeGroup->setContentsMargins(0,0,0,0);

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
    radioGroup->setContentsMargins(0,0,0,0);

    QGridLayout *mainLayout=new QGridLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(WIDGETS_LEFT_MARGIN,0,0,0);
   // mainLayout->addLayout(dataLayout,0,0);
    mainLayout->addWidget(dataLabel,0,0);
    mainLayout->addWidget(dataTyper,0,1);
    mainLayout->addWidget(sendBtn,0,2);
    mainLayout->addWidget(editTypeGroup,1,1);
    mainLayout->addWidget(radioGroup,2,1);
    mainLayout->addWidget(historyLabel,3,0);
    mainLayout->addWidget(historyList,3,1);
    //mainLayout->addWidget(radioGroup,2,2);



}
void NormalSender::send()
{
    emit sendDataSig(dataTyper->text());
}
