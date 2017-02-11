#include "configwidget.h"

#include"config.h"
#include<QPushButton>
#include<QLabel>
#include<QHBoxLayout>
#include<QLineEdit>
#include<QGridLayout>
#include<QListWidget>
#include<QGroupBox>
#include<QRadioButton>
#include<QCheckBox>
#include<QProgressBar>
#include<QComboBox>
ConfigWidget::ConfigWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout=new QVBoxLayout(this);

    QLabel *portLabel=new QLabel(tr("Communication Port :"));
    QComboBox *portList=new QComboBox;

    QLabel *baudLabel=new QLabel(tr("Baud Rate :"));
    QComboBox *baudList=new QComboBox;

    baudList->addItem("300");
    baudList->addItem("600");
    baudList->addItem("1200");
    baudList->addItem("1800");
    baudList->addItem("2400");
    baudList->addItem("7200");
    baudList->addItem("9600");
    baudList->addItem("14400");
    baudList->addItem("19200");
    baudList->addItem("38400");
    baudList->addItem("57600");
    baudList->addItem("115200");
    baudList->addItem("230400");
    baudList->addItem("460800");
    baudList->addItem("921600");

    QLabel *dataLabel=new QLabel(tr("Data Bits :"));
    QComboBox *dataList=new QComboBox;

    dataList->addItem("5");
    dataList->addItem("6");
    dataList->addItem("7");
    dataList->addItem("8");

    QLabel *stopLabel=new QLabel(tr("Stop Bits :"));
    QComboBox *stopList=new QComboBox;

    stopList->addItem("1");
    stopList->addItem("1.5");
    stopList->addItem("2");

    QLabel *parityLabel=new QLabel(tr("Parity :"));
    QComboBox *parityList=new QComboBox;

    parityList->addItem("None");
    parityList->addItem("Even");
    parityList->addItem("Odd");
    parityList->addItem("Mark");
    parityList->addItem("Space");

    QLabel *flowLabel=new QLabel(tr("flow control :"));
    QComboBox *flowList=new QComboBox;

    flowList->addItem("None");
    flowList->addItem("XON/XOFF");
    flowList->addItem("RTS/CTS");
    flowList->addItem("None");

    mainLayout->addWidget(portLabel);
    mainLayout->addWidget(portList);
    mainLayout->addWidget(baudLabel);
    mainLayout->addWidget(baudList);
    mainLayout->addWidget(dataLabel);
    mainLayout->addWidget(dataList);
    mainLayout->addWidget(stopLabel);
    mainLayout->addWidget(stopList);
    mainLayout->addWidget(parityLabel);
    mainLayout->addWidget(parityList);
    mainLayout->addWidget(flowLabel);
    mainLayout->addWidget(flowList);



}
