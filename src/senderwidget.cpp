/***************************************************************************
 *   Copyright (C) 2017 by Mohamed Hussein                                 *
 *   m.hussein1389@gmail.com                                               *
     https://github.com/mo7amed-hussein/                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, see <http://www.gnu.org/licenses/>.  *
 *                                                                         *
 ***************************************************************************/
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


    senderTabs->addTab(normal,tr("Normal Mode"));
    senderTabs->addTab(terminal,tr("Terminal Mode"));


    QGridLayout *mainLayout=new QGridLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(WIDGETS_LEFT_MARGIN,0,5,0);
    mainLayout->addWidget(senderTabs);

    connect(normal,&NormalSender::sendDataSig,this,&SenderWidget::sendDataSlot);
    connect(terminal,&TerminalSender::sendDataSig,this,&SenderWidget::sendDataSlot);


}
void SenderWidget::sendDataSlot(QByteArray data)
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
