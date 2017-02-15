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
#ifndef FILESENDER_H
#define FILESENDER_H

#include <QWidget>
#include<QLineEdit>
#include<QRadioButton>
#include<QProgressBar>
#include"datasender.h"
class FileSender : public DataSender
{
    Q_OBJECT
public:
    explicit FileSender(QWidget *parent = 0);
    void getFile();
    void sendCommands();
    void sendData();
    void sendSlot();

signals:

public slots:
    virtual void send();
 private:
     QLineEdit *fileEdit;
     QString filePath;
     QRadioButton *allfile;
     QProgressBar *sendBar;
};

#endif // FILESENDER_H
