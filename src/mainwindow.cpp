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
#include<QLabel>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{


    isConnected=false;
    baudrate=0;
    stopBits=0;
    dataBits=0;

    //QVBoxLayout *mainLayout=new QVBoxLayout(this);
    //mainLayout->setSpacing(0);

   monitorWidget=new MonitorWidget(this);
   SenderWidget *sender=new SenderWidget(this);
    comConfig=new ConfigDialog(this);

   //mainLayout->addWidget(monitorWidget);
   //mainLayout->addWidget(sender);

    this->setCentralWidget(monitorWidget);

   utilityDock=new QDockWidget;
   utilityWidget=new UtilityWidget(utilityDock);
   utilityDock->setWidget(utilityWidget);
   utilityDock->setFeatures(QDockWidget::NoDockWidgetFeatures);


   QDockWidget *senderDock=new QDockWidget;
   senderDock->setWidget(sender);
   senderDock->setFeatures(QDockWidget::NoDockWidgetFeatures);

   addDockWidget(Qt::RightDockWidgetArea,utilityDock);
   addDockWidget(Qt::BottomDockWidgetArea,senderDock);

  this->resize(800,700);

   createToolBar();
   createBars();
    updateStatusBar();
   connect(sender,&SenderWidget::sendDataSig,this,&MainWindow::sendData);
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

const QIcon newIcon=QIcon::fromTheme("document-new",QIcon(":/images/icons/new.png"));
QAction *newAction=new QAction(newIcon,tr("&New"),this);
newAction->setShortcut(QKeySequence::New);
newAction->setToolTip(tr("clear everything"));
fileMenu->addAction(newAction);
mainTool->addAction(newAction);

const QIcon openIcon=QIcon::fromTheme("document-open",QIcon(":/images/icons/open.png"));
QAction *openAction=new QAction(openIcon,tr("Load Command history"),this);
openAction->setShortcut(QKeySequence::Open);
openAction->setToolTip(tr("Load Command history"));
//connect(openAction,&QAction::triggered,this,&MainWindow::openfile);
fileMenu->addAction(openAction);
mainTool->addAction(openAction);

const QIcon saveIcon=QIcon::fromTheme("document-save",QIcon(":/images/icons/save.png"));
QAction *saveAction=new QAction(saveIcon,tr("&Save History"),this);
saveAction->setShortcut(QKeySequence::Save);
saveAction->setToolTip(tr("History"));
//connect(saveAction,&QAction::triggered,this,&MainWindow::save);
fileMenu->addAction(saveAction);
mainTool->addAction(saveAction);

fileMenu->addSeparator();

const QIcon quitIcon=QIcon::fromTheme("document-saveas",QIcon(":/images/icons/save.png"));
QAction *quitAction=new QAction(quitIcon,tr("Quit"),this);
quitAction->setShortcut(QKeySequence::SaveAs);
quitAction->setToolTip(tr("Quit KISLab"));
//connect(quitAction,&QAction::triggered,this,&MainWindow::quitApp);
fileMenu->addAction(quitAction);

const QIcon findIcon=QIcon::fromTheme("edit-find",QIcon(":/images/icons/find.png"));
findAction=new QAction(findIcon,tr("Find"),this);
findAction->setShortcut(QKeySequence::Find);
findAction->setToolTip(tr("find"));
connect(findAction,&QAction::triggered,utilityWidget,&UtilityWidget::showSearch);
//searchMenu->addAction(findAction);
mainTool->addAction(findAction);

const QIcon printIcon=QIcon::fromTheme("document-print",QIcon(":/images/icons/find.png"));
QAction* printAction=new QAction(printIcon,tr("Find"),this);
printAction->setShortcut(QKeySequence::Find);
printAction->setToolTip(tr("find"));
// connect(findAction,&QAction::triggered,this,&MainWindow::find);
//searchMenu->addAction(findAction);
mainTool->addAction(printAction);

QMenu *editMenu=menuBar()->addMenu(tr("&Edit"));

const QIcon settingIcon=QIcon::fromTheme("edit-settings",QIcon(":/images/icons/find.png"));
QAction* settingAction=new QAction(settingIcon,tr("Setting"),this);
settingAction->setShortcut(QKeySequence::Find);
settingAction->setToolTip(tr("find"));
// connect(findAction,&QAction::triggered,this,&MainWindow::find);
editMenu->addAction(settingAction);
mainTool->addAction(settingAction);

mainTool->addSeparator();

QMenu *connectMenu=menuBar()->addMenu(tr("&Connection"));

const QIcon connectIcon=QIcon::fromTheme("edit-settings",QIcon(":/resources/icons/play.png"));
connectAction=new QAction(connectIcon,tr("Strart Connection"),this);
connectAction->setShortcut(QKeySequence::Find);
connectAction->setToolTip(tr("Strart Connection"));
connect(connectAction,&QAction::triggered,this,&MainWindow::startConSlot);
connectMenu->addAction(connectAction);
mainTool->addAction(connectAction);

const QIcon stopIcon=QIcon::fromTheme("edit-settings",QIcon(":/resources/icons/stop.png"));
stopAction=new QAction(stopIcon,tr("Stop Connection"),this);
stopAction->setEnabled(false);
stopAction->setShortcut(QKeySequence::Find);
stopAction->setToolTip(tr("Stop Connection"));
connect(stopAction,&QAction::triggered,this,&MainWindow::stopConSlot);

// stop(findAction,&QAction::triggered,this,&MainWindow::find);
connectMenu->addAction(stopAction);
mainTool->addAction(stopAction);

const QIcon configIcon=QIcon::fromTheme("edit-settings",QIcon(":/resources/icons/info.png"));
QAction* configAction=new QAction(configIcon,tr("Configuration"),this);
configAction->setShortcut(QKeySequence::Find);
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
    QDateTime dt(QDate::currentDate(),QTime::currentTime());
    monitorWidget->print(dt,RX,data);

}
void MainWindow::updateStatusBar()
{
    QLabel *state=new QLabel(this);
    state->setText("<font size=3 color=#ff0000>mohamed<font color=#00ff00>ali ");
    state->setTextFormat(Qt::RichText);

    QLabel *state2=new QLabel(this);
    state2->setText("<font size=3 color=#0000ff>mohamed<font color=#00ff00>ali ");
    state2->setTextFormat(Qt::RichText);

    statusBar()->addPermanentWidget(state);
    statusBar()->addPermanentWidget(state2);
    //statusBar()->showMessage("<b>ali</b>mohamed");
}

bool MainWindow::startConnection()
{
    return true;
}
bool MainWindow::stopConnection()
{
    return true;
}
void MainWindow::startConSlot()
{
    if(startConnection())
    {
        connectAction->setEnabled(false);
        stopAction->setEnabled(true);
        utilityDock->setEnabled(false);
        findAction->setEnabled(false);
    }

}
void MainWindow::stopConSlot()
{
    if(stopConnection())
    {
        connectAction->setEnabled(true);
        stopAction->setEnabled(false);
        utilityDock->setEnabled(true);
         findAction->setEnabled(true);
    }

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
