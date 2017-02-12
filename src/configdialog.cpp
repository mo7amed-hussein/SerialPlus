#include "configdialog.h"

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
#include<QDebug>
#include<QtSerialPort/QSerialPortInfo>

//QT_USE_NAMESPACE

ConfigDialog::ConfigDialog(QWidget *parent) : QDialog(parent)
{
    QVBoxLayout *mainLayout=new QVBoxLayout(this);

    QLabel *portLabel=new QLabel(tr("Communication Port :"));
    portList=new QComboBox;
    portList->addItem("None");

    QLabel *baudLabel=new QLabel(tr("Baud Rate :"));
    baudList=new QComboBox;

    baudList->addItem("300",300);
    baudList->addItem("600",600);
    baudList->addItem("1200",QSerialPort::Baud1200);
    baudList->addItem("1800",1800);
    baudList->addItem("2400",QSerialPort::Baud2400);
    baudList->addItem("4800",QSerialPort::Baud4800);
    baudList->addItem("7200",7200);
    baudList->addItem("9600",QSerialPort::Baud9600);

    baudList->addItem("14400",14400);
    baudList->addItem("19200",QSerialPort::Baud19200);
    baudList->addItem("38400",QSerialPort::Baud38400);
    baudList->addItem("57600",QSerialPort::Baud57600);
    baudList->addItem("115200",QSerialPort::Baud115200);
    baudList->addItem("230400",230400);
    baudList->addItem("460800",460800);
    baudList->addItem("921600",460800);

    QLabel *dataLabel=new QLabel(tr("Data Bits :"));
    dataList=new QComboBox;

    dataList->addItem("5",QSerialPort::Data5);
    dataList->addItem("6",QSerialPort::Data6);
    dataList->addItem("7",QSerialPort::Data7);
    dataList->addItem("8",QSerialPort::Data8);

    QLabel *stopLabel=new QLabel(tr("Stop Bits :"));
    stopList=new QComboBox;

    stopList->addItem("1",QSerialPort::OneStop);
    stopList->addItem("1.5",QSerialPort::OneAndHalfStop);
    stopList->addItem("2",QSerialPort::TwoStop);

    QLabel *parityLabel=new QLabel(tr("Parity :"));
    parityList=new QComboBox;

    parityList->addItem("None",QSerialPort::NoParity);
    parityList->addItem("Even",QSerialPort::EvenParity);
    parityList->addItem("Odd",QSerialPort::OddParity);
    parityList->addItem("Mark",QSerialPort::MarkParity);
    parityList->addItem("Space",QSerialPort::SpaceParity);

    QLabel *flowLabel=new QLabel(tr("Flow Control :"));
    flowList=new QComboBox;

    flowList->addItem("None",QSerialPort::NoFlowControl);
    flowList->addItem("XON/XOFF",QSerialPort::SoftwareControl);
    flowList->addItem("RTS/CTS",QSerialPort::HardwareControl);


    logFileGroup=new QGroupBox("Log File");
    logFileGroup->setCheckable(true);
    logFileGroup->setChecked(false);

    QVBoxLayout *logLayout=new QVBoxLayout;
    QHBoxLayout *fileLayout=new QHBoxLayout;
    QLineEdit *filePath=new QLineEdit;
    QPushButton *fileBtn=new QPushButton("...",this);
    fileBtn->setMaximumWidth(20);
    fileLayout->addWidget(filePath);
    fileLayout->addWidget(fileBtn);

    appendFlag=new QRadioButton(tr("Append data"));
    QRadioButton *overwriteFlag=new QRadioButton(tr("Overwrite data"));
    logLayout->addLayout(fileLayout);
    logLayout->addWidget(overwriteFlag);
    logLayout->addWidget(appendFlag);

    logFileGroup->setLayout(logLayout);

    QPushButton *cancelBtn=new QPushButton(tr("Cancel"),this);
    QPushButton *applyBtn=new QPushButton(tr("Apply"),this);


    connect(cancelBtn,&QPushButton::clicked,this,&ConfigDialog::close);
    QHBoxLayout *btnsLayout=new QHBoxLayout;
    btnsLayout->addWidget(cancelBtn);
    btnsLayout->addWidget(applyBtn);


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
    mainLayout->addWidget(logFileGroup);
    mainLayout->addLayout(btnsLayout);
    mainLayout->addStretch();
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    this->setWindowTitle(tr("Connection Settings"));
    this->setWindowFlags(Qt::Tool);


    initConfig();
}

void ConfigDialog::initConfig()
{
    const auto ports=QSerialPortInfo::availablePorts();
    qDebug()<<"the number of ports is "<<ports.size();
    foreach (const QSerialPortInfo &info, ports)
    {
        portList->addItem(info.portName());

    }
}
