#include "asciidisplay.h"
#include<QDebug>

AsciiDisplay::AsciiDisplay(QWidget *parent):DataDisplay(parent)
{


}

void AsciiDisplay::print(QDateTime dt,SOURCETYPE type,QString &data)
{
    QString str;
    str="< "+dt.date().toString(Qt::ISODate)+ " , "+dt.time().toString(Qt::ISODate)+" > ";
    if(type==TX)
    {
        str+=" [TX] -";
        this->setTextColor(Qt::blue);
    }
    else
    {
       str+=" [RX] -";
       this->setTextColor(Qt::red);
    }
    str+=data;
    this->append(str);
}
