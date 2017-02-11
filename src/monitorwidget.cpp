#include "monitorwidget.h"
#include"config.h"
#include<QGridLayout>
MonitorWidget::MonitorWidget(QWidget *parent) : QWidget(parent)
{
    displayTabs=new QTabWidget(this);



    AsciiDisplay *as=new AsciiDisplay(this);
    BinaryDisplay *bin=new BinaryDisplay(this);
    HexDisplay *hex=new HexDisplay(this);

    displayTabs->addTab(as,tr("ASCII"));
    displayTabs->addTab(hex,tr("Hex"));
    displayTabs->addTab(bin,tr("Binary"));

    QGridLayout *mainLayout=new QGridLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(WIDGETS_LEFT_MARGIN,WIDGETS_TOP_MARGIN,0,0);
    mainLayout->addWidget(displayTabs);


    QDateTime td(QDate::currentDate(),QTime::currentTime());
    QString str("123");
    //this->showMaximized();
    as->print(td,TX,str);
    bin->print(td,TX,str);
    hex->print(td,TX,str);
    bin->print(td,RX,str);
    hex->print(td,RX,str);
    bin->print(td,TX,str);
    hex->print(td,TX,str);
    bin->print(td,RX,str);
    hex->print(td,RX,str);

}
