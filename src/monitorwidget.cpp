#include "monitorwidget.h"
#include"config.h"
#include<QGridLayout>
#include<QPushButton>
#include<QMessageBox>
MonitorWidget::MonitorWidget(QWidget *parent) : QWidget(parent)
{
    displayTabs=new QTabWidget(this);



    asciiDisplay=new AsciiDisplay(this);
    binaryDisplay=new BinaryDisplay(this);
    hexDisplay=new HexDisplay(this);

    displayTabs->addTab(asciiDisplay,tr("ASCII"));
    displayTabs->addTab(hexDisplay,tr("Hex"));
    displayTabs->addTab(binaryDisplay,tr("Binary"));

    QGridLayout *mainLayout=new QGridLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(WIDGETS_LEFT_MARGIN,WIDGETS_TOP_MARGIN,5,10);
    mainLayout->addWidget(displayTabs);

    QPushButton *clearBtn=new QPushButton(this);
    const QIcon clearIcon(":/resources/icons/clear.png");
    clearBtn->setIcon(clearIcon);
    clearBtn->setToolTip(tr("clear Display"));
    connect(clearBtn,&QPushButton::clicked,this,&MonitorWidget::clear);
    displayTabs->setCornerWidget(clearBtn,Qt::TopRightCorner);
}

void MonitorWidget::print(QDateTime dt,SOURCETYPE type,QString &data)
{
asciiDisplay->print(dt,type,data);
hexDisplay->print(dt,type,data);
binaryDisplay->print(dt,type,data);

if(log.isOpen())
{
    QString str;
    str="< "+dt.date().toString(Qt::ISODate)+ " , "+dt.time().toString(Qt::ISODate)+" > ";
    if(type==TX)
    {
        str+=" [TX] -";

    }
    else
    {
       str+=" [RX] -";

    }
    str+=data;
    QTextStream f(&log);
    f<<str;
    //log.write(str.toLocal8Bit());
    qDebug()<<"write";
}
}

void MonitorWidget::clear()
{
    asciiDisplay->clear();
    hexDisplay->clear();
    binaryDisplay->clear();
}
bool MonitorWidget::find(QString str,bool wd,bool cs)
{
    QTextDocument::FindFlags flags;
    if(wd)
    {
        flags |=QTextDocument::FindWholeWords;
    }
    if(cs)
    {
        flags |=QTextDocument::FindCaseSensitively;
    }
    DataDisplay * currentDisp=(DataDisplay *)displayTabs->currentWidget();
    return (currentDisp->find(str,flags));
}

void MonitorWidget::startLog(QString file, QIODevice::OpenMode mode)
{
    log.setFileName(file);
    if(!log.open(mode))
    {
        QMessageBox::critical(this,"error",log.errorString());

    }

}

void MonitorWidget::stopLog()
{

    if(log.isOpen())
    {
        log.close();

    }
    isLogged=false;
}
