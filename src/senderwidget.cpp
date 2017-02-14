#include "senderwidget.h"
#include"config.h"
#include<QGridLayout>
#include<QPushButton>
#include<QFileDialog>
SenderWidget::SenderWidget(QWidget *parent) : QWidget(parent)
{
    senderTabs=new QTabWidget(this);

    normal=new NormalSender(this);
    TerminalSender *terminal=new TerminalSender(this);
   // FileSender *file=new FileSender(this);

    senderTabs->addTab(normal,tr("Normal Mode"));
    senderTabs->addTab(terminal,tr("Terminal Mode"));
   // senderTabs->addTab(file,tr("File Mode"));

    QGridLayout *mainLayout=new QGridLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(WIDGETS_LEFT_MARGIN,WIDGETS_TOP_MARGIN,5,0);
    mainLayout->addWidget(senderTabs);

    connect(normal,&NormalSender::sendDataSig,this,&SenderWidget::sendDataSlot);
   // connect(file,&FileSender::sendDataSig,this,&SenderWidget::sendDataSlot);
    connect(terminal,&TerminalSender::sendDataSig,this,&SenderWidget::sendDataSlot);


   // connect(clearBtn,&QPushButton::clicked,this,&MonitorWidget::clear);
    //senderTabs->setCornerWidget(clearBtn,Qt::TopRightCorner);
}
void SenderWidget::sendDataSlot(QString data)
{
    emit sendDataSig(data);
}
void SenderWidget::loadHistory()
{
    QString filename=QFileDialog::getOpenFileName(this,tr("History File"),QDir::currentPath(),"XML File(*.xml)");
        if(filename.isEmpty())
            return;
        normal->loadHistory(filename);
}

void SenderWidget::saveHistory()
{
    QString filename=QFileDialog::getSaveFileName(this,tr("History File"),QDir::currentPath(),"XML File(*.xml)");
        if(filename.isEmpty())
            return;
        normal->saveHistory(filename);

}
