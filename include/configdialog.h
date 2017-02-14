#ifndef CONFIGWIDGET_H
#define CONFIGWIDGET_H

#include <QWidget>
#include<QDialog>
#include<QComboBox>
#include<QGroupBox>
#include<QRadioButton>
#include<QCheckBox>
//#include<QSerialPort>
#include<QtSerialPort/QSerialPortInfo>
#include<QtSerialPort/QSerialPort>

struct Settings {
    QString name;
    qint32 baudRate;
    QSerialPort::DataBits dataBits;
    QSerialPort::Parity parity;
    QString parityStr;
    QSerialPort::StopBits stopBits;
    QSerialPort::FlowControl flowControl;
    QString flowStr;
    bool isLogged;
    QString logfile;
    bool isAppend;
};

class ConfigDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ConfigDialog(QWidget *parent = 0);
    void initConfig();
    void apply();
    void customClicked();

    Settings *CurrConSetting;
signals:

public slots:
    void checkOpen();
    void getFile();
private:
     QComboBox *portList;
     QComboBox *baudList;
     QComboBox *dataList;
     QComboBox *stopList;
     QComboBox *parityList;
     QComboBox *flowList;
     QGroupBox *logFileGroup;
     QRadioButton *appendFlag;
    // QString *filePath;
     QLineEdit *filePath;
     //Settings *CurrConSetting;
};

#endif // CONFIGWIDGET_H
