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

  // list<<"man"<<"ali"<<"good"<<"goafg";
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

    QRadioButton *cr=new QRadioButton(tr("CR"));
    QRadioButton *lf=new QRadioButton(tr("LF"));
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
   // mainLayout->addLayout(dataLayout,0,0);
    mainLayout->addWidget(dataLabel,0,0);
    mainLayout->addWidget(dataTyper,0,1);
    mainLayout->addWidget(sendBtn,0,2);
    mainLayout->addWidget(editTypeGroup,1,1);
    mainLayout->addWidget(radioGroup,2,1);
    mainLayout->addWidget(historyLabel,3,0);
    mainLayout->addWidget(historyList,3,1);
    //mainLayout->addWidget(radioGroup,2,2);

    connect(historyList,&QListWidget::itemClicked,this,&NormalSender::editCommand);
    connect(historyList,&QListWidget::itemDoubleClicked,this,&NormalSender::sendAgain);


}
void NormalSender::send()
{
    if(!dataTyper->text().isEmpty())
       {
        QString data=dataTyper->text();
        if(hex->isChecked())
        {
            data=toAscii(dataTyper->text());
        }
        emit sendDataSig(data);

        historyList->addItem(data);

        if(del->isChecked())
        {
            dataTyper->clear();
        }
      }
}

QString NormalSender::toHex(QString data)
{
    QByteArray arr(data.toLocal8Bit());

    return QString(arr.toHex());
}

void NormalSender::radioToggled()
{


if(ascii->isChecked())
{
    dataTyper->setValidator(0);
    dataTyper->setCompleter(comp);
    if(!dataTyper->text().isEmpty())
       {
    QString str=toAscii(dataTyper->text());
    dataTyper->setText(str);
    }


}
else
{
    if(!dataTyper->text().isEmpty())
    {
    QString str=toHex(dataTyper->text());
    dataTyper->setText(str);
    }
    dataTyper->setValidator(hexValidator);
     dataTyper->setCompleter(0);
}

}

QString NormalSender::toAscii(QString data)
{
QByteArray arr=QByteArray::fromHex(data.toLocal8Bit());
return QString(arr.data());
}

void NormalSender::editCommand(QListWidgetItem * item)
{
    QString data=item->text();
    if(hex->isChecked())
    {
        data=toHex(item->text());
        qDebug()<<"data is "<<data;

    }
    dataTyper->setText(data);

}

void NormalSender::sendAgain(QListWidgetItem * item)
{
    emit sendDataSig(item->text());
}

void NormalSender::loadHistory(QString fileName)
{
    QFile f(fileName);
    if(f.open(QIODevice::ReadOnly))
    {
        /*while (!f.atEnd()) {
           // QTextStream txt(&f);
            historyList->addItem(txt.readLine());

        }*/
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

        if(root.hasAttribute("xmlns"))
        {
        QDomAttr attr=root.attributeNode("xmlns");
        }

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
