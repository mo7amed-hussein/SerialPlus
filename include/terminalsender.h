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
#ifndef TERMINALSENDER_H
#define TERMINALSENDER_H

#include <QWidget>
#include<QTextEdit>
#include<QRadioButton>
#include"datasender.h"
#include"terminaledit.h"

class TerminalSender : public DataSender
{
    Q_OBJECT
public:
    explicit TerminalSender(QWidget *parent = 0);

    void sendTerm(QString d);

    void clear();
signals:

public slots:
    virtual void send();
 private:
    TerminalEdit *term;
    QRadioButton *cr;

    QRadioButton *lf;
};

#endif // TERMINALSENDER_H
