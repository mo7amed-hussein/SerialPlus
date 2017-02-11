#include "monitorwidget.h"
#include"config.h"
#include<QGridLayout>
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
    mainLayout->setContentsMargins(WIDGETS_LEFT_MARGIN,WIDGETS_TOP_MARGIN,0,0);
    mainLayout->addWidget(displayTabs);
}

void MonitorWidget::print(QDateTime dt,SOURCETYPE type,QString &data)
{
asciiDisplay->print(dt,type,data);
hexDisplay->print(dt,type,data);
binaryDisplay->print(dt,type,data);
}
