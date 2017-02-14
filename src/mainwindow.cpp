#include "mainwindow.h"
#include<QVBoxLayout>
#include<QGridLayout>
#include<QToolBar>
#include<QIcon>
#include<QAction>
#include<QMenu>
#include<QMenuBar>
#include<QStatusBar>
#include<QApplication>
#include<QMessageBox>
#include<QLabel>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    const QIcon icon(":/resources/icons/play.png");
this->setWindowIcon(icon);
            isConnected=false;
    baudrate=0;
    stopBits=0;
    dataBits=0;

    //QVBoxLayout *mainLayout=new QVBoxLayout(this);
    //mainLayout->setSpacing(0);

   monitorWidget=new MonitorWidget(this);
   sender=new SenderWidget(this);
    comConfig=new ConfigDialog(this);

   //mainLayout->addWidget(monitorWidget);
   //mainLayout->addWidget(sender);

    this->setCentralWidget(monitorWidget);
    findDialog=new SearchDialog(monitorWidget);
/*
   utilityDock=new QDockWidget;
   utilityWidget=new UtilityWidget(utilityDock);
   utilityDock->setWidget(utilityWidget);
   utilityDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
*/
    serialHandler=new QSerialPort(this);
   QDockWidget *senderDock=new QDockWidget;
   senderDock->setWidget(sender);
   senderDock->setFeatures(QDockWidget::NoDockWidgetFeatures);

   //addDockWidget(Qt::RightDockWidgetArea,utilityDock);
   addDockWidget(Qt::BottomDockWidgetArea,senderDock);

  this->resize(800,700);

   createToolBar();
   createBars();

   connect(sender,&SenderWidget::sendDataSig,this,&MainWindow::sendData);
   connect(serialHandler,&QSerialPort::readyRead,this,&MainWindow::readData);
   // setLayout(mainLayout);

}

void MainWindow::createToolBar()
{
QToolBar *mainTool=new QToolBar("main",this);
mainTool->setFloatable(false);
mainTool->setMovable(false);

mainTool->setContextMenuPolicy(Qt::PreventContextMenu);

QMenu *fileMenu=menuBar()->addMenu(tr("&File"));

addToolBar(Qt::LeftToolBarArea,mainTool);
//mainTool->setAllowedAreas(Qt::LeftToolBarArea);
mainTool->setOrientation(Qt::Vertical);
/*
const QIcon newIcon(":/resources/icons/new.png");
QAction *newAction=new QAction(newIcon,tr("&New"),this);
newAction->setShortcut(QKeySequence::New);
newAction->setToolTip(tr("clear everything"));
fileMenu->addAction(newAction);
mainTool->addAction(newAction);*/

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

//connect(saveAction,&QAction::triggered,this,&MainWindow::save);
fileMenu->addAction(saveAction);
mainTool->addAction(saveAction);

fileMenu->addSeparator();

//const QIcon quitIcon=QIcon::fromTheme("document-saveas",QIcon(":/images/icons/save.png"));
QAction *quitAction=new QAction(tr("Quit"),this);
quitAction->setShortcut(QKeySequence::SaveAs);
quitAction->setToolTip(tr("Quit SerialPlus"));
//connect(quitAction,&QAction::triggered,this,&MainWindow::quitApp);
fileMenu->addAction(quitAction);
/*
const QIcon findIcon=QIcon::fromTheme("edit-find",QIcon(":/images/icons/find.png"));
findAction=new QAction(findIcon,tr("Find"),this);
findAction->setShortcut(QKeySequence::Find);
findAction->setToolTip(tr("find"));
connect(findAction,&QAction::triggered,this,&MainWindow::showSearch);
//searchMenu->addAction(findAction);
mainTool->addAction(findAction);
*/
const QIcon printIcon(":/resources/icons/document-print.png");
QAction* printAction=new QAction(printIcon,tr("Find"),this);
printAction->setShortcut(QKeySequence::Find);
printAction->setToolTip(tr("print "));
// connect(findAction,&QAction::triggered,this,&MainWindow::find);
//searchMenu->addAction(findAction);
mainTool->addAction(printAction);

QMenu *editMenu=menuBar()->addMenu(tr("&Edit"));

const QIcon settingIcon(":/resources/icons/settings.png");
QAction* settingAction=new QAction(settingIcon,tr("Setting"),this);
settingAction->setShortcut(QKeySequence::Find);
settingAction->setToolTip(tr("setting"));
// connect(findAction,&QAction::triggered,this,&MainWindow::find);
editMenu->addAction(settingAction);
mainTool->addAction(settingAction);

mainTool->addSeparator();

QMenu *connectMenu=menuBar()->addMenu(tr("&Connection"));

const QIcon connectIcon(":/resources/icons/connect.png");
connectAction=new QAction(connectIcon,tr("Strart Connection"),this);
connectAction->setShortcut(QKeySequence::Find);
connectAction->setToolTip(tr("Strart Connection"));
connect(connectAction,&QAction::triggered,this,&MainWindow::startConSlot);
connectMenu->addAction(connectAction);
mainTool->addAction(connectAction);

const QIcon stopIcon(":/resources/icons/disconnect.png");
stopAction=new QAction(stopIcon,tr("Stop Connection"),this);
stopAction->setEnabled(false);
stopAction->setShortcut(QKeySequence::Find);
stopAction->setToolTip(tr("Stop Connection"));
connect(stopAction,&QAction::triggered,this,&MainWindow::stopConSlot);

// stop(findAction,&QAction::triggered,this,&MainWindow::find);
connectMenu->addAction(stopAction);
mainTool->addAction(stopAction);

const QIcon configIcon(":/resources/icons/preferences-system.png");
configAction=new QAction(configIcon,tr("Configuration"),this);
//configAction->setShortcut(QKeySequence::Find);
configAction->setToolTip(tr("connection Configuration"));
// config(findAction,&QAction::triggered,this,&MainWindow::find);
connect(configAction,&QAction::triggered,this,&MainWindow::showComconfig);

connectMenu->addAction(configAction);
mainTool->addAction(configAction);
mainTool->addSeparator();

QMenu *helpMenu=menuBar()->addMenu(tr("Help"));

    const QIcon aboutIcon=QIcon::fromTheme("document-about",QIcon(":/images/icons/about.png"));
    QAction *aboutAction=new QAction(aboutIcon,tr("about"),this);
    connect(aboutAction,&QAction::triggered,this,&MainWindow::aboutApp);
    helpMenu->addAction(aboutAction);
    //fileToolBar->addAction(aboutAction);

    const QIcon aboutQtIcon=QIcon::fromTheme("document-aboutQt",QIcon(":/images/icons/aboutQt.png"));
    QAction *aboutQtAction=new QAction(aboutQtIcon,tr("aboutQt"),this);
   // aboutQtAction->setShortcut(QKeySequence::aboutQt);
    aboutQtAction->setToolTip(tr("aboutQt"));
    connect(aboutQtAction,&QAction::triggered,qApp,&QApplication::aboutQt);
    helpMenu->addAction(aboutQtAction);

}

void MainWindow::createBars()
{
    statusBar()->setVisible(true);


}

void MainWindow::sendData(QString data)
{
    if(serialHandler->isOpen())
    {
    QDateTime dt(QDate::currentDate(),QTime::currentTime());
    monitorWidget->print(dt,RX,data);
    serialHandler->write(data.toLocal8Bit());
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
 QString str(data.data());
 monitorWidget->print(dt,TX,str);

}

void MainWindow::showComconfig()
{
    comConfig->exec();
}
 void MainWindow::aboutApp()
 {
     AboutDialog f(this);
     f.exec();

 }
 void MainWindow::showSearch()
 {
    findDialog->show();
 }
