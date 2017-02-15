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
#include "mainwindow.h"
#include<QVBoxLayout>
#include<QGridLayout>
#include<QToolBar>
#include<QIcon>
#include<QAction>
#include<QMenu>
#include<QMenuBar>
#include<QCloseEvent>
#include<QStatusBar>
#include<QApplication>
#include<QMessageBox>
#include<QLabel>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    const QIcon icon(":/resources/icons/seialplus.png");
    this->setWindowIcon(icon);
    this->resize(800,700);
    serialHandler=new QSerialPort(this);
   monitorWidget=new MonitorWidget(this);
   sender=new SenderWidget(this);
   comConfig=new ConfigDialog(this);

    this->setCentralWidget(monitorWidget);



   QDockWidget *senderDock=new QDockWidget;
   senderDock->setWidget(sender);
   senderDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
   addDockWidget(Qt::BottomDockWidgetArea,senderDock);

   createBars();

   connect(sender,&SenderWidget::sendDataSig,this,&MainWindow::sendData);
   connect(serialHandler,&QSerialPort::readyRead,this,&MainWindow::readData);
   connect(serialHandler, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
               this, &MainWindow::handleError);


}

void MainWindow::createBars()
{
QToolBar *mainTool=new QToolBar("main",this);
mainTool->setFloatable(false);
mainTool->setMovable(false);

mainTool->setContextMenuPolicy(Qt::PreventContextMenu);

QMenu *fileMenu=menuBar()->addMenu(tr("&File"));

addToolBar(Qt::LeftToolBarArea,mainTool);

mainTool->setOrientation(Qt::Vertical);

const QIcon openIcon(":/resources/icons/document-open.png");
QAction *openAction=new QAction(openIcon,tr("Load Command history"),this);
openAction->setShortcut(QKeySequence::Open);
connect(openAction,&QAction::triggered,sender,&SenderWidget::loadHistory);
openAction->setToolTip(tr("Load Command history"));
fileMenu->addAction(openAction);
mainTool->addAction(openAction);

const QIcon saveIcon(":/resources/icons/document-save.png");
QAction *saveAction=new QAction(saveIcon,tr("&Save History"),this);
saveAction->setShortcut(QKeySequence::Save);
saveAction->setToolTip(tr("Save Command History"));
connect(saveAction,&QAction::triggered,sender,&SenderWidget::saveHistory);
fileMenu->addAction(saveAction);
mainTool->addAction(saveAction);

fileMenu->addSeparator();

const QIcon printIcon(":/resources/icons/document-print.png");
QAction* printAction=new QAction(printIcon,tr("Print"),this);
printAction->setShortcut(QKeySequence::Print);
printAction->setToolTip(tr("print"));
connect(printAction,&QAction::triggered,monitorWidget,&MonitorWidget::print);
mainTool->addAction(printAction);
fileMenu->addAction(printAction);

fileMenu->addSeparator();
QAction *quitAction=new QAction(tr("Quit"),this);
quitAction->setShortcut(QKeySequence::Quit);
quitAction->setToolTip(tr("Quit SerialPlus"));
connect(quitAction,&QAction::triggered,this,&MainWindow::quitApp);
fileMenu->addAction(quitAction);

QMenu *editMenu=menuBar()->addMenu(tr("&Edit"));

mainTool->addSeparator();

const QIcon zoominIcon(":/resources/icons/zoom-in.png");
QAction* zoominAction=new QAction(zoominIcon,tr("Zoom In"),this);
zoominAction->setShortcut(QKeySequence::ZoomIn);
zoominAction->setToolTip(tr("zoom in"));
connect(zoominAction,&QAction::triggered,monitorWidget,&MonitorWidget::zoomIn);
editMenu->addAction(zoominAction);
mainTool->addAction(zoominAction);

const QIcon zoomoutIcon(":/resources/icons/zoom-out.png");
QAction* zoomoutAction=new QAction(zoomoutIcon,tr("Zoom Out"),this);
zoomoutAction->setShortcut(QKeySequence::ZoomOut);
zoomoutAction->setToolTip(tr("zoom out"));
connect(zoomoutAction,&QAction::triggered,monitorWidget,&MonitorWidget::zoomOut);
editMenu->addAction(zoomoutAction);
mainTool->addAction(zoomoutAction);

mainTool->addSeparator();

QMenu *connectMenu=menuBar()->addMenu(tr("&Connection"));

const QIcon connectIcon(":/resources/icons/connect.png");
connectAction=new QAction(connectIcon,tr("Strart Connection"),this);
connectAction->setShortcut(Qt::Key_F6);
connectAction->setToolTip(tr("Strart Connection"));
connect(connectAction,&QAction::triggered,this,&MainWindow::startConSlot);
connectMenu->addAction(connectAction);
mainTool->addAction(connectAction);

const QIcon stopIcon(":/resources/icons/disconnect.png");
stopAction=new QAction(stopIcon,tr("Stop Connection"),this);
stopAction->setEnabled(false);
stopAction->setShortcut(Qt::Key_F5);
stopAction->setToolTip(tr("Stop Connection"));
connect(stopAction,&QAction::triggered,this,&MainWindow::stopConSlot);
connectMenu->addAction(stopAction);
mainTool->addAction(stopAction);

const QIcon configIcon(":/resources/icons/preferences-system.png");
configAction=new QAction(configIcon,tr("Configuration"),this);
configAction->setToolTip(tr("connection Configuration"));
connect(configAction,&QAction::triggered,this,&MainWindow::showComconfig);

connectMenu->addAction(configAction);
mainTool->addAction(configAction);
mainTool->addSeparator();

QMenu *helpMenu=menuBar()->addMenu(tr("Help"));

const QIcon aboutIcon=QIcon::fromTheme("document-about",QIcon(":/images/icons/about.png"));
QAction *aboutAction=new QAction(aboutIcon,tr("about"),this);
connect(aboutAction,&QAction::triggered,this,&MainWindow::aboutApp);
helpMenu->addAction(aboutAction);


const QIcon aboutQtIcon=QIcon::fromTheme("document-aboutQt",QIcon(":/images/icons/aboutQt.png"));
QAction *aboutQtAction=new QAction(aboutQtIcon,tr("aboutQt"),this);
aboutQtAction->setToolTip(tr("aboutQt"));
connect(aboutQtAction,&QAction::triggered,qApp,&QApplication::aboutQt);
helpMenu->addAction(aboutQtAction);

statusBar()->setVisible(true);

}



void MainWindow::sendData(QByteArray data)
{
    if(serialHandler->isOpen())
    {
    QDateTime dt(QDate::currentDate(),QTime::currentTime());
    serialHandler->write(data.data());
   monitorWidget->printData(dt,RX,data);

    }
    else
    {
     QMessageBox msg(this);
     msg.setText(tr("start connection first"));
     msg.exec();
    }

}
void MainWindow::updateStatusBar()
{
    QString flow=comConfig->CurrConSetting->flowStr;
    QString parity=comConfig->CurrConSetting->parityStr;



    QString str=tr("Connected to : %1 ||BaudRate : %2 ||Data Bits : %3"
                   " ||Stop Bits : %4 ||Parity : %6 ||Flow Control :%7").arg(serialHandler->portName()).arg(serialHandler->baudRate()).arg(
                serialHandler->dataBits()).arg(serialHandler->stopBits()).arg(parity).arg(flow);
    statusBar()->showMessage(str);
}

bool MainWindow::startConnection()
{
    if(!comConfig->CurrConSetting->name.isEmpty())
    {
    serialHandler->setPortName(comConfig->CurrConSetting->name);
    serialHandler->setBaudRate(comConfig->CurrConSetting->baudRate);
    serialHandler->setDataBits(comConfig->CurrConSetting->dataBits);
    serialHandler->setFlowControl(comConfig->CurrConSetting->flowControl);
    serialHandler->setStopBits(comConfig->CurrConSetting->stopBits);
    serialHandler->setParity(comConfig->CurrConSetting->parity);

    if(serialHandler->open(QIODevice::ReadWrite))
    {
        updateStatusBar();
        if(comConfig->CurrConSetting->isLogged)
        {
            //log.setFileName(comConfig->CurrConSetting->logfile);
            QIODevice::OpenMode mode;
            mode=QIODevice::WriteOnly ;
            if(comConfig->CurrConSetting->isAppend)
            {
                mode |=QIODevice::Append;
            }
            monitorWidget->startLog(comConfig->CurrConSetting->logfile,mode);
        }
        return true;
    }
    else
    {
        QMessageBox::critical(this,"error",serialHandler->errorString());
        return false;
    }
    }
    else
    {
     showComconfig();
     return false;
    }

}
bool MainWindow::stopConnection()
{
   if(serialHandler->isOpen())
   {
       serialHandler->close();
       monitorWidget->stopLog();
       return true;
   }
   return false;
}
void MainWindow::startConSlot()
{
    if(startConnection())
    {
        connectAction->setEnabled(false);
        stopAction->setEnabled(true);
        configAction->setEnabled(false);
       // findAction->setEnabled(false);
    }

}
void MainWindow::stopConSlot()
{
    if(stopConnection())
    {
        connectAction->setEnabled(true);
        stopAction->setEnabled(false);
         configAction->setEnabled(true);
        // findAction->setEnabled(true);
         statusBar()->showMessage("Connection Stopped");
    }

}
void MainWindow::readData()
{
 QByteArray data=serialHandler->readAll();
 QDateTime dt(QDate::currentDate(),QTime::currentTime());
 //QString str(data.data());
 monitorWidget->printData(dt,TX,data);

}

void MainWindow::showComconfig()
{
    comConfig->initConfig();
    comConfig->exec();
}
 void MainWindow::aboutApp()
 {
     AboutDialog f(this);
     f.exec();

 }

 void MainWindow::quitApp()
 {

     QMessageBox msgBox(this);
     msgBox.setText("Close SerialPlus");
     msgBox.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
     int ret=msgBox.exec();
     if(ret==QMessageBox::Yes)
     {
     stopConnection();
     monitorWidget->stopLog();
     qApp->quit();
     }

 }
void MainWindow::closeEvent(QCloseEvent * event)
{
    event->ignore();
    quitApp();


}
 void MainWindow::handleError(QSerialPort::SerialPortError error)
 {
     if (error == QSerialPort::ResourceError) {
             QMessageBox::critical(this, tr("Critical Error"), serialHandler->errorString());
             stopConSlot();
         }
 }
