#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"senderwidget.h"
#include"monitorwidget.h"
#include"utilitywidget.h"
#include<QDockWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

    void createToolBar();
    void createBars();
    bool startConnection();
    bool stopConnection();
signals:

public slots:
    void sendData(QString data);
    void updateStatusBar();
    void startConSlot();
    void stopConSlot();
private:
    UtilityWidget *utilityWidget;
    MonitorWidget *monitorWidget;
    QString port;
    bool isConnected;
    int baudrate;
    int stopBits;
    int dataBits;
    QDockWidget *utilityDock;
    QAction* connectAction;
    QAction* stopAction;
    QAction* findAction;
};

#endif // MAINWINDOW_H
