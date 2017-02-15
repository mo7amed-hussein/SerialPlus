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
#ifndef NORMALSENDER_H
#define NORMALSENDER_H

#include <QWidget>
#include<QLineEdit>
#include<QCheckBox>
#include<QRadioButton>
#include<QRegExpValidator>
#include<QListWidget>

#include"datasender.h"
class NormalSender : public DataSender
{
    Q_OBJECT
public:
    explicit NormalSender(QWidget *parent = 0);

    QByteArray toHex(QByteArray data);

    QByteArray toAscii(QByteArray data);

    void loadHistory(QString fileName);

    void saveHistory(QString filename);

    void loadAutoComp();

signals:

public slots:
     virtual void send();

    void radioToggled();

     void editCommand(QListWidgetItem * item);

     void sendAgain(QListWidgetItem * item);

 private:
 QLineEdit *dataTyper;
 QCheckBox *del;
 QRadioButton *ascii;
 QRadioButton *hex;
 QRegExpValidator *hexValidator;
 QCompleter *comp;
 QListWidget *historyList;
 QStringList autoCompList;
 QRadioButton *cr;
 QRadioButton *lf;
};

#endif // NORMALSENDER_H
