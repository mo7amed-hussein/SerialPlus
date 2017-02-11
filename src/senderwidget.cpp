#include "senderwidget.h"
#include"config.h"
#include<QGridLayout>
SenderWidget::SenderWidget(QWidget *parent) : QWidget(parent)
{
    senderTabs=new QTabWidget(this);

    NormalSender *normal=new NormalSender(this);
    TerminalSender *terminal=new TerminalSender(this);
    FileSender *file=new FileSender(this);

    senderTabs->addTab(normal,tr("Normal Mode"));
    senderTabs->addTab(terminal,tr("Terminal Mode"));
    senderTabs->addTab(file,tr("File Mode"));

    QGridLayout *mainLayout=new QGridLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(WIDGETS_LEFT_MARGIN,WIDGETS_TOP_MARGIN,0,0);
    mainLayout->addWidget(senderTabs);

}
