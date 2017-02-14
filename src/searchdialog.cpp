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
        display->find(findEdit->text(),wholeWord->isChecked(),caseFlag->isChecked());
    }

}

void SearchDialog::count()
{

}
