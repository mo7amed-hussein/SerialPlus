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
