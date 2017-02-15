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
#include "normalsender.h"
#include"config.h"
#include<QComboBox>
#include<QPushButton>
#include<QLabel>
#include<QDebug>
#include<QHBoxLayout>
#include<QLineEdit>
#include<QGridLayout>
#include<QListWidget>
#include<QGroupBox>
#include<QFile>
#include<QRadioButton>
#include<QCheckBox>
#include<QCompleter>
#include <QDomDocument>

NormalSender::NormalSender(QWidget *parent) : DataSender(parent)
{
    QLabel *dataLabel=new QLabel(tr("Command:"));
    QLabel *historyLabel=new QLabel(tr("Commands\nHistory:"));
    dataTyper=new QLineEdit;
    dataTyper->setClearButtonEnabled(true);
    dataTyper->setFrame(true);
    dataTyper->setPlaceholderText(tr("type to send"));
    QPushButton *sendBtn=new QPushButton(tr("Send"),this);
    sendBtn->setShortcut(QKeySequence::InsertParagraphSeparator);
    connect(sendBtn,&QPushButton::clicked,this,&NormalSender::send);
    connect(dataTyper,&QLineEdit::returnPressed,this,&NormalSender::send);

   loadAutoComp();

   comp=new QCompleter(autoCompList,this);
   comp->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
   comp->setCaseSensitivity(Qt::CaseInsensitive);

    dataTyper->setCompleter(comp);
    hexValidator=new QRegExpValidator(QRegExp("[0-9A-Fa-f]{0,}"),this);
    historyList=new QListWidget;
    historyList->setSortingEnabled(true);

    QGroupBox *editTypeGroup=new QGroupBox;

    ascii=new QRadioButton(tr("ASCII"));
    ascii->setChecked(true);

    hex=new QRadioButton(tr("Hex"));

    connect(ascii,&QRadioButton::toggled,this,&NormalSender::radioToggled);
    del=new QCheckBox(tr("clear after send"));
    del->setChecked(true);
    QHBoxLayout *editTypeLayout=new QHBoxLayout;
    editTypeLayout->setContentsMargins(0,0,0,0);
    editTypeLayout->addWidget(ascii);
    editTypeLayout->addWidget(hex);editTypeLayout->addWidget(del);
    editTypeLayout->addStretch();
    editTypeGroup->setLayout(editTypeLayout);
    //editTypeGroup->setContentsMargins(0,0,0,0);

    QGroupBox *radioGroup=new QGroupBox;

    cr=new QRadioButton(tr("CR"));
    cr->setChecked(true);
    lf=new QRadioButton(tr("LF"));
    QRadioButton *cf=new QRadioButton(tr("CR+LF"));

    QHBoxLayout *radioLayout=new QHBoxLayout;
    radioLayout->addWidget(cr);
    radioLayout->addWidget(lf);
    radioLayout->addWidget(cf);
    radioLayout->addStretch();
    radioLayout->setContentsMargins(0,0,0,0);
    radioGroup->setLayout(radioLayout);
    //radioGroup->setContentsMargins(0,0,0,0);

    QGridLayout *mainLayout=new QGridLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(WIDGETS_LEFT_MARGIN,WIDGETS_TOP_MARGIN,0,0);

    mainLayout->addWidget(dataLabel,0,0);
    mainLayout->addWidget(dataTyper,0,1);
    mainLayout->addWidget(sendBtn,0,2);
    mainLayout->addWidget(editTypeGroup,1,1);
    mainLayout->addWidget(radioGroup,2,1);
    mainLayout->addWidget(historyLabel,3,0);
    mainLayout->addWidget(historyList,3,1);
    connect(historyList,&QListWidget::itemClicked,this,&NormalSender::editCommand);
    connect(historyList,&QListWidget::itemDoubleClicked,this,&NormalSender::sendAgain);
}

void NormalSender::send()
{
    if(!dataTyper->text().isEmpty())
       {
        QByteArray data(dataTyper->text().toLocal8Bit());
        if(hex->isChecked())
        {
            data=toAscii(data);
           //qDebug()<<"line edit data in 8 bits hex again "<<toHex(data).toLocal8Bit();
        }
        QString append="\r\n";
        if(cr->isChecked())
        {
            append="\r";
        }
        else if(lf->isChecked())
        {
            append="\n";
        }
        QString listItem(data.data());
        qDebug()<<"item added is "<<listItem;
        historyList->addItem(listItem);
        data+=append.toLocal8Bit();
        emit sendDataSig(data);

        if(del->isChecked())
        {
            dataTyper->clear();
        }
      }
}

QByteArray NormalSender::toHex(QByteArray data)
{

    return data.toHex();
}

void NormalSender::radioToggled()
{

if(ascii->isChecked())
{
    dataTyper->setValidator(0);
    dataTyper->setCompleter(comp);
    if(!dataTyper->text().isEmpty())
       {
        qDebug()<<"to ascii as rec "<<dataTyper->text().toLocal8Bit();
    QString str=toAscii(dataTyper->text().toLocal8Bit()).data();
    dataTyper->setText(str.toLocal8Bit());
    }


}
else
{
    if(!dataTyper->text().isEmpty())
    {
    QString str=toHex(dataTyper->text().toLocal8Bit()).data();
    QByteArray arr;
    arr.append(dataTyper->text());
    qDebug()<<"to hex as array is "<<arr;
    qDebug()<<"to hex as toggled is "<<dataTyper->text();
    qDebug()<<"to string "<<toHex(dataTyper->text().toLocal8Bit());
    dataTyper->setText(str.toLocal8Bit());
    }
    dataTyper->setValidator(hexValidator);
     dataTyper->setCompleter(0);
}

}

QByteArray NormalSender::toAscii(QByteArray data)
{
    return QByteArray::fromHex(data);
}

void NormalSender::editCommand(QListWidgetItem * item)
{
    QString data=item->text();
    if(hex->isChecked())
    {
      data=toHex(item->text().toLocal8Bit()).data();
       qDebug()<<"data is "<<data;

    }
    dataTyper->setText(data);

}

void NormalSender::sendAgain(QListWidgetItem * item)
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
            QString d=item->text();
            d+=append;
            QByteArray snd(d.toLocal8Bit());

   emit sendDataSig(snd);
}

void NormalSender::loadHistory(QString fileName)
{
    QFile f(fileName);
    if(f.open(QIODevice::ReadOnly))
    {
        QByteArray content=f.readAll();
        QDomDocument doc;
        QString errormsg;
        int line,col;
        if(!doc.setContent(content,&errormsg,&line,&col))
        {
            qDebug()<<"error in "<<line <<col;
            f.close();
            return;
        }
        QDomDocumentType type=doc.doctype();
     //   qDebug()<<"doc type is "<<type.to;

        QDomElement root=doc.documentElement();

        QDomNode node=root.firstChild();
        while (!node.isNull()) {
            QDomElement elem=node.toElement();

            if(elem.tagName()=="Command")
            {
            historyList->addItem(elem.text());
            }
            node=node.nextSibling();

        }

        f.close();

    }

}

 void NormalSender::saveHistory(QString filename)
 {
    // QString filename=QFileDialog
      qDebug()<<"start";
     QDomDocument doc("history");
     QDomElement root=doc.createElement("Commands");
     doc.appendChild(root);
     for(int i=0;i<historyList->count();i++)
     {
         qDebug()<<"element";
         QDomElement child=doc.createElement("Command");
         root.appendChild(child);
         QListWidgetItem *item=historyList->item(i);
         QDomText txt=doc.createTextNode(item->text());
         child.appendChild(txt);
     }
     QString str=doc.toString();
     qDebug()<<"string "<<str;
    QFile f(filename);
    if(f.open(QIODevice::WriteOnly))
    {
       f.write(str.toLocal8Bit());
       f.close();
    }

 }
 void NormalSender::loadAutoComp()
 {
     QFile f(":/resources/Autocomplete.xml");
     if(f.open(QIODevice::ReadOnly))
     {
         QByteArray content=f.readAll();
         QDomDocument doc;
         QString errormsg;
         int line,col;
         if(!doc.setContent(content,&errormsg,&line,&col))
         {
             qDebug()<<"error in "<<line <<col;
             f.close();
             return;
         }
         QDomDocumentType type=doc.doctype();
      //   qDebug()<<"doc type is "<<type.to;

         QDomElement root=doc.documentElement();

         QDomNode node=root.firstChild();
         while (!node.isNull()) {
             QDomElement elem=node.toElement();

             if(elem.tagName()=="Command")
             {
             autoCompList<<elem.text();
             }
             node=node.nextSibling();

         }

         f.close();

     }

 }
