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
#include "terminalsender.h"
#include"config.h"
#include<QGridLayout>
#include<QGroupBox>
#include<QRadioButton>
#include<QHBoxLayout>
#include<QPushButton>
#include<QDebug>
TerminalSender::TerminalSender(QWidget *parent) : DataSender(parent)
{
    term=new TerminalEdit(this);
    QGridLayout *mainLayout=new QGridLayout(this);
   // term->setAutoFillBackground(true);
   // term->setBackgroundRole(QPalette::Highlight);
   // term->setTextBackgroundColor(Qt::black);

    term->setPlaceholderText(tr("Type to send"));

    connect(term,&TerminalEdit::newCommand,this,&TerminalSender::sendTerm);
    QGroupBox *radioGroup=new QGroupBox(tr("Append sent data"));

    cr=new QRadioButton(tr("CR"));
    cr->setChecked(true);
    lf=new QRadioButton(tr("LF"));
    QRadioButton *cf=new QRadioButton(tr("CR+LF"));

    QPushButton *clearBtn=new QPushButton(this);
    const QIcon clearIcon(":/resources/icons/clear.png");
    clearBtn->setToolTip(tr("clear terminal"));
    clearBtn->setIcon(clearIcon);
    connect(clearBtn,&QPushButton::clicked,this,&TerminalSender::clear);
    QHBoxLayout *radioLayout=new QHBoxLayout;
    radioLayout->addWidget(cr);
    radioLayout->addWidget(lf);
    radioLayout->addWidget(cf);
    radioLayout->addStretch();
    radioLayout->addWidget(clearBtn);
    radioLayout->setContentsMargins(5,0,0,0);

    radioGroup->setLayout(radioLayout);


    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(WIDGETS_LEFT_MARGIN,WIDGETS_TOP_MARGIN,0,5);
    mainLayout->addWidget(radioGroup);
    mainLayout->addWidget(term);

}
void TerminalSender::send()
{

}
void TerminalSender::sendTerm(QString d)
{
    QString append="\r\n";
    if(cr->isChecked())
    {
        append="\r";
    }
    else if(lf->isChecked())
    {
        append="\n";
    }
    d+=append;
    qDebug()<<"term Data is : "<<d;
    emit sendDataSig(QByteArray(d.toLocal8Bit()));
}
void TerminalSender::clear()
{
    term->clear();
    term->append(">>");
}
