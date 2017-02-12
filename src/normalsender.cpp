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
#include<QCompleter>
NormalSender::NormalSender(QWidget *parent) : DataSender(parent)
{
    QLabel *dataLabel=new QLabel(tr("Command:"));
    QLabel *historyLabel=new QLabel(tr("Commands\nHistory:"));
    dataTyper=new QLineEdit;
    dataTyper->setClearButtonEnabled(true);
    dataTyper->setFrame(true);
    dataTyper->setPlaceholderText(tr("type to send"));
    QPushButton *sendBtn=new QPushButton(tr("Send"),this);
    sendBtn->setShortcut(QKeySequence::InsertParagraphSeparator);
    connect(sendBtn,&QPushButton::clicked,this,&NormalSender::send);

    QStringList list;
   list<<"man"<<"ali"<<"good"<<"goafg";
    comp=new QCompleter(list,this);
    dataTyper->setCompleter(comp);
    hexValidator=new QRegExpValidator(QRegExp("[0-9A-Fa-f]{0,}"),this);
    historyList=new QListWidget;

    QGroupBox *editTypeGroup=new QGroupBox;

    ascii=new QRadioButton(tr("ASCII"));
    ascii->setChecked(true);

    hex=new QRadioButton(tr("Hex"));

    connect(ascii,&QRadioButton::toggled,this,&NormalSender::radioToggled);
    del=new QCheckBox(tr("clear after send"));
    del->setChecked(true);
    QHBoxLayout *editTypeLayout=new QHBoxLayout;
    editTypeLayout->setContentsMargins(0,0,0,0);
    editTypeLayout->addWidget(ascii);
    editTypeLayout->addWidget(hex);editTypeLayout->addWidget(del);
    editTypeLayout->addStretch();
    editTypeGroup->setLayout(editTypeLayout);
    //editTypeGroup->setContentsMargins(0,0,0,0);

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
    //radioGroup->setContentsMargins(0,0,0,0);

    QGridLayout *mainLayout=new QGridLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(WIDGETS_LEFT_MARGIN,WIDGETS_TOP_MARGIN,0,0);
   // mainLayout->addLayout(dataLayout,0,0);
    mainLayout->addWidget(dataLabel,0,0);
    mainLayout->addWidget(dataTyper,0,1);
    mainLayout->addWidget(sendBtn,0,2);
    mainLayout->addWidget(editTypeGroup,1,1);
    mainLayout->addWidget(radioGroup,2,1);
    mainLayout->addWidget(historyLabel,3,0);
    mainLayout->addWidget(historyList,3,1);
    //mainLayout->addWidget(radioGroup,2,2);

    connect(historyList,&QListWidget::itemClicked,this,&NormalSender::editCommand);
    connect(historyList,&QListWidget::itemDoubleClicked,this,&NormalSender::sendAgain);


}
void NormalSender::send()
{
    if(!dataTyper->text().isEmpty())
       {
        emit sendDataSig(dataTyper->text());

        historyList->addItem(dataTyper->text());

        if(del->isChecked())
        {
            dataTyper->clear();
        }
      }
}

QString NormalSender::toHex(QString data)
{
    QByteArray arr(data.toLocal8Bit());

    return QString(arr.toHex());
}

void NormalSender::radioToggled()
{


if(ascii->isChecked())
{
    dataTyper->setValidator(0);
    if(!dataTyper->text().isEmpty())
       {
    QString str=toAscii(dataTyper->text());
    dataTyper->setText(str);
    }


}
else
{
    if(!dataTyper->text().isEmpty())
    {
    QString str=toHex(dataTyper->text());
    dataTyper->setText(str);
    }
    dataTyper->setValidator(hexValidator);
}

}

QString NormalSender::toAscii(QString data)
{
QByteArray arr=QByteArray::fromHex(data.toLocal8Bit());
return QString(arr.data());
}

void NormalSender::editCommand(QListWidgetItem * item)
{
    dataTyper->setText(item->text());

}

void NormalSender::sendAgain(QListWidgetItem * item)
{

}
