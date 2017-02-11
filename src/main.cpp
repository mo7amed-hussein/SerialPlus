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
#include <QApplication>
#include <QtDebug>
#include <QIcon>
#include <QMainWindow>

//temp include
#include"monitorwidget.h"
#include"senderwidget.h"
#include"utilitywidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

     app.setApplicationName("SeialPlus");
     app.setOrganizationDomain("www.SeialPlus.com");
     app.setOrganizationName("Mohamed-Hussein");
     app.setApplicationVersion("1.0.0");

UtilityWidget m;
m.show();


    return app.exec();
}
