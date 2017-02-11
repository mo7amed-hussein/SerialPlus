#include "searchwidget.h"
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

SearchWidget::SearchWidget(QWidget *parent) : QWidget(parent)
{

    QVBoxLayout *mainLayout=new QVBoxLayout(this);

    QLabel *findLabel=new QLabel(tr("Find :"));
    QLineEdit *findEdit=new QLineEdit;
    findEdit->setPlaceholderText(tr("type to search"));

    QCheckBox *wholeWord=new QCheckBox(tr("Match the whole word"));
    QCheckBox *caseFlag=new QCheckBox(tr("Match case"));

    QPushButton *searchBtn=new QPushButton(tr("Find Next"),this);
    QPushButton *countBtn=new QPushButton(tr("Count"),this);

    mainLayout->addWidget(findLabel);
    mainLayout->addWidget(findEdit);
    mainLayout->addWidget(wholeWord);
    mainLayout->addWidget(caseFlag);
    mainLayout->addWidget(searchBtn);
    mainLayout->addWidget(countBtn);
    mainLayout->addStretch();


}
