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
#ifndef HEXDISPLAY_H
#define HEXDISPLAY_H

#include <QWidget>
#include"datadisplay.h"

class HexDisplay : public DataDisplay
{
    Q_OBJECT
public:
    explicit HexDisplay(QWidget *parent = 0);

    virtual void printData(QDateTime dt, SOURCETYPE type, QByteArray data);

    QByteArray toHex(QByteArray data);


signals:

public slots:
};

#endif // HEXDISPLAY_H
