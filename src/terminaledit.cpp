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
#include "terminaledit.h"
#include<QKeyEvent>
#include<QDebug>
TerminalEdit::TerminalEdit(QWidget *parent) : QTextEdit(parent)
{
 this->append(">>");
    this->setCursorWidth(8);
    this->setContextMenuPolicy(Qt::PreventContextMenu);
    QPalette p=this->palette();
    p.setColor(QPalette::Base, Qt::darkCyan);
    this->setPalette(p);

    QFont f=this->font();
    f.setBold(true);
    this->setFont(f);
}
void TerminalEdit::keyPressEvent(QKeyEvent * e)
{
    QString str=e->text();
    QTextCursor cr=this->textCursor();
    cr.columnNumber();
   // str.to
    qDebug()<<"line pos : "<<cr.columnNumber();
    if(e->key()==Qt::Key_Up)
    {
        e->ignore();
    }
    else if(e->key()==Qt::Key_Enter || e->key()==Qt::Key_Return)
    {
        qDebug()<<"enter pressed: "<<command;
        if(!command.isEmpty())
        {
            emit newCommand(command);
        }
        command.clear();
       // QTextEdit::keyPressEvent(e);
        this->append(">>");

    }
    else if(e->key()==Qt::Key_Backspace)
    {
        if(cr.columnNumber()!=2)
        {
        command.chop(1);

        QTextEdit::keyPressEvent(e);
        }
    }
    else if(e->key()>31 && e->key()<128)
    {
        qDebug()<<"key "<<e->text()<<e->key();
        command+=e->text();
    return QTextEdit::keyPressEvent(e);
    }
}
