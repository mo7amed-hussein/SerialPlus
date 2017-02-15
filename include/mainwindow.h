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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"senderwidget.h"
#include"monitorwidget.h"

#include"configdialog.h"
#include"configdialog.h"
#include"aboutdialog.h"

#include<QDockWidget>
#include<QFile>
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);


    void createBars();

    bool startConnection();
    bool stopConnection();

    void showComconfig();

    void quitApp();

signals:

public slots:
    void sendData(QByteArray data);
    void readData();
    void updateStatusBar();
    void startConSlot();
    void stopConSlot();
    void aboutApp();
    void handleError(QSerialPort::SerialPortError error);
private:
virtual void closeEvent(QCloseEvent * event);
private:

    MonitorWidget *monitorWidget;
    ConfigDialog * comConfig;
    QAction* connectAction;
    QAction* stopAction;
    QAction* findAction;
    QAction* configAction;
    QSerialPort *serialHandler;
    QFile log;

    SenderWidget *sender;
};

#endif // MAINWINDOW_H
