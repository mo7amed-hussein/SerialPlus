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
#ifndef MONITORWIDGET_H
#define MONITORWIDGET_H

#include <QWidget>
#include<QTableWidget>
#include<QFile>
#include"datadisplay.h"
#include"hexdisplay.h"
#include"binarydisplay.h"
#include"asciidisplay.h"

class MonitorWidget : public QWidget
{
    Q_OBJECT
public:

    explicit MonitorWidget(QWidget *parent = 0);

    void printData(QDateTime dt,SOURCETYPE type,QByteArray &data);

    void clear();



    void startLog(QString file, QIODevice::OpenMode mode);

    void zoomIn();

    void zoomOut();

    void stopLog();

    void print();

signals:

public slots:
private:
    QTabWidget *displayTabs;
    DataDisplay *asciiDisplay;
    DataDisplay *hexDisplay;
    DataDisplay *binaryDisplay;

    QFile log;
    bool isLogged;
};

#endif // MONITORWIDGET_H
