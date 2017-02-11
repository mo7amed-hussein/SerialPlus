#ifndef UTILITYWIDGET_H
#define UTILITYWIDGET_H

#include <QWidget>
#include"configwidget.h"
#include"searchwidget.h"
class UtilityWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UtilityWidget(QWidget *parent = 0);

signals:

public slots:
    void showConfig();
    void showSearch();
 private:
    ConfigWidget *configWidget;

    SearchWidget *searchWidget;
};

#endif // UTILITYWIDGET_H
