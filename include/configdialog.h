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

class ConfigDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ConfigDialog(QWidget *parent = 0);
    void initConfig();
signals:

public slots:
private:
     QComboBox *portList;
     QComboBox *baudList;
     QComboBox *dataList;
     QComboBox *stopList;
     QComboBox *parityList;
     QComboBox *flowList;
     QGroupBox *logFileGroup;
     QRadioButton *appendFlag;
     QString *filePath;
};

#endif // CONFIGWIDGET_H
