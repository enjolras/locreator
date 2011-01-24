#ifndef FRAMEWIDGET_H
#define FRAMEWIDGET_H

#include <QWidget>
#include <QString>
#include "lomodel.h"
#include "ui_framewidget.h"

namespace Ui {
    class frameWidget;
}

class frameWidget : public QWidget {
    Q_OBJECT
public:
    frameWidget(QWidget *parent = 0);
    ~frameWidget();

protected:
    void changeEvent(QEvent *e);
    void setTitle(const QString &title) ;
    void putLangString(LangString *langString, QLayout *layout) ;
    Ui::frameWidget *frameui;

private slots:
    void switchBanner() ;
};

#endif // FRAMEWIDGET_H
