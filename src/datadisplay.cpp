#include "datadisplay.h"
#include<QAction>
#include<QMenu>
DataDisplay::DataDisplay(QWidget *parent) : QTextEdit(parent)
{

    this->setReadOnly(true);
    this->setContextMenuPolicy(Qt::CustomContextMenu);

    copyAction=new QAction(tr("Copy"),this);
    copyAction->setEnabled(false);

    connect(this,&DataDisplay::copyAvailable,this,&DataDisplay::toggleCopy);
    connect(this,&DataDisplay::customContextMenuRequested,this,&DataDisplay::onCustomContextMenuRequested);

}
void DataDisplay::onCustomContextMenuRequested(const QPoint& pos)
{
        QMenu menu;

        QAction selectAction(tr("SelectAll"),this);
        QAction clearAction(tr("Clear"),this);



        connect(copyAction,&QAction::triggered,this,&DataDisplay::copy);
        connect(&selectAction,&QAction::triggered,this,&DataDisplay::selectAll);
        connect(&clearAction,&QAction::triggered,this,&DataDisplay::clear);

        menu.addAction(copyAction);

        menu.addAction(&selectAction);
        menu.addAction(&clearAction);
        menu.exec(QWidget::mapToGlobal(pos));

}

void DataDisplay::toggleCopy(bool c)
{
    copyAction->setEnabled(c);
}
