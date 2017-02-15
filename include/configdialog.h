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
#ifndef CONFIGWIDGET_H
#define CONFIGWIDGET_H

#include <QWidget>
#include<QDialog>
#include<QComboBox>
#include<QGroupBox>
#include<QRadioButton>
#include<QCheckBox>
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
     QLineEdit *filePath;

};

#endif // CONFIGWIDGET_H
