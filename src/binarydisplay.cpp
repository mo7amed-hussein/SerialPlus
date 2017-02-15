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
#include "binarydisplay.h"

BinaryDisplay::BinaryDisplay(QWidget *parent) : DataDisplay(parent)
{


}

void BinaryDisplay::printData(QDateTime dt,SOURCETYPE type,QByteArray data)
{
 QString str;
 int count=data.size()-1;

 if(count>0)
 {
if(data.at(count)=='\r')
 {
     data.chop(1);
     data=toBin(data);
     data+="<CR>";
 }
 else if(data.at(count-1)=='\r' &&data.at(count)=='\n')
 {
     data.chop(2);
     data=toBin(data);
     data+="<CR><LF>";
 }
 else
 {
     data.chop(1);
    data=toBin(data);
      data+="<LF>";
 }
}
 else
 {
    data=toBin(data);
 }


 str="< "+dt.date().toString(Qt::ISODate)+ " , "+dt.time().toString(Qt::ISODate)+" >";
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
 str+=data.data();

 this->append(str);

}
QByteArray BinaryDisplay::toBin(QByteArray data)
{
    QByteArray bin;

    for(int i=0;i<data.size();i++)
    {

        bin.append(char2bin(data[i]));
        bin.append(' ');
    }
  ;
    return bin;
}

QByteArray BinaryDisplay::char2bin(unsigned char ch)
{

    QByteArray bin;
    bin.setNum(ch,2);
    return bin;
}
