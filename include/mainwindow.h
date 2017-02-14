#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"senderwidget.h"
#include"monitorwidget.h"
#include"searchdialog.h"
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

    void createToolBar();
    void createBars();
    bool startConnection();
    bool stopConnection();
    void showComconfig();
    void showSearch();
signals:

public slots:
    void sendData(QString data);
    void readData();
    void updateStatusBar();
    void startConSlot();
    void stopConSlot();
    void aboutApp();
private:

    MonitorWidget *monitorWidget;
    ConfigDialog * comConfig;
    QString port;
    bool isConnected;
    int baudrate;
    int stopBits;
    int dataBits;

    QAction* connectAction;
    QAction* stopAction;
    QAction* findAction;
    QAction* configAction;
    QSerialPort *serialHandler;
    QFile log;
    SearchDialog *findDialog;
    SenderWidget *sender;
};

#endif // MAINWINDOW_H
