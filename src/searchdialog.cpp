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
#include "searchdialog.h"
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

SearchDialog::SearchDialog(QWidget *parent) : QDialog(parent)
{

    display=(MonitorWidget*)parent;

    QVBoxLayout *mainLayout=new QVBoxLayout(this);

    QLabel *findLabel=new QLabel(tr("Find :"));
    findEdit=new QLineEdit;
    findEdit->setPlaceholderText(tr("type to search"));

    wholeWord=new QCheckBox(tr("Match the whole word"));
    caseFlag=new QCheckBox(tr("Match case"));

    QPushButton *searchBtn=new QPushButton(tr("Find Next"),this);
    QPushButton *countBtn=new QPushButton(tr("Count"),this);
    QPushButton *closeBtn=new QPushButton(tr("close"),this);

    connect(searchBtn,&QPushButton::clicked,this,&SearchDialog::find);
    connect(countBtn,&QPushButton::clicked,this,&SearchDialog::count);
    connect(closeBtn,&QPushButton::clicked,this,&SearchDialog::hide);

    mainLayout->addWidget(findLabel);
    mainLayout->addWidget(findEdit);
    mainLayout->addWidget(wholeWord);
    mainLayout->addWidget(caseFlag);
    mainLayout->addWidget(searchBtn);
    mainLayout->addWidget(countBtn);
    mainLayout->addWidget(closeBtn);
    mainLayout->addStretch();
mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    this->setWindowFlags(Qt::Tool);

}

void SearchDialog::find()
{
    if(!findEdit->text().isEmpty())
    {
        //display->find(findEdit->text(),wholeWord->isChecked(),caseFlag->isChecked());
    }

}

void SearchDialog::count()
{

}
