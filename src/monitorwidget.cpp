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
#include "monitorwidget.h"
#include"config.h"
#include<QGridLayout>
#include<QPushButton>
#include<QMessageBox>
#include<QPrinter>
#include<QPrintDialog>

MonitorWidget::MonitorWidget(QWidget *parent) : QWidget(parent)
{
    displayTabs=new QTabWidget(this);
    asciiDisplay=new AsciiDisplay(this);
    binaryDisplay=new BinaryDisplay(this);
    hexDisplay=new HexDisplay(this);

    displayTabs->addTab(asciiDisplay,tr("ASCII"));
    displayTabs->addTab(hexDisplay,tr("Hex"));
    displayTabs->addTab(binaryDisplay,tr("Binary"));

    QGridLayout *mainLayout=new QGridLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(WIDGETS_LEFT_MARGIN,WIDGETS_TOP_MARGIN,5,0);
    mainLayout->addWidget(displayTabs);

    QPushButton *clearBtn=new QPushButton(this);
    const QIcon clearIcon(":/resources/icons/clear.png");
    clearBtn->setIcon(clearIcon);
    clearBtn->setToolTip(tr("clear Display"));
    connect(clearBtn,&QPushButton::clicked,this,&MonitorWidget::clear);
    displayTabs->setCornerWidget(clearBtn,Qt::TopRightCorner);
}

void MonitorWidget::printData(QDateTime dt, SOURCETYPE type, QByteArray &data)
{
   qDebug()<<"data is : "<<data<<"size is "<<data.size();

asciiDisplay->printData(dt,type,data);
hexDisplay->printData(dt,type,data);
binaryDisplay->printData(dt,type,data);

}

void MonitorWidget::clear()
{
    asciiDisplay->clear();
    hexDisplay->clear();
    binaryDisplay->clear();
}


void MonitorWidget::startLog(QString file, QIODevice::OpenMode mode)
{
    asciiDisplay->startLog(file,mode);

}

void MonitorWidget::stopLog()
{
asciiDisplay->stopLog();

}

void MonitorWidget::print()
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog printDialog(&printer, this);
    if (printDialog.exec() == QDialog::Accepted) {
    DataDisplay *current=(DataDisplay *)displayTabs->currentWidget();
    current->print(&printer);
    qDebug()<<"printed";
    }

}
void MonitorWidget::zoomIn()
{
    DataDisplay *current=(DataDisplay *)displayTabs->currentWidget();
    current->zoomIn();
}

void MonitorWidget::zoomOut()
{
    DataDisplay *current=(DataDisplay *)displayTabs->currentWidget();
    current->zoomOut();
}

