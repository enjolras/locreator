#ifndef EJMDGENERALWIDGET_H
#define EJMDGENERALWIDGET_H

#include <QWidget>
#include "framewidget.h"
#include "lomodel.h"

namespace Ui {
    class ejmdGeneralWidget;
}

class ejmdGeneralWidget : public frameWidget {
    Q_OBJECT
public:
    ejmdGeneralWidget(EjmdGeneral *data, QWidget *parent = 0);
    ~ejmdGeneralWidget();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ejmdGeneralWidget *ui;
};

#endif // EJMDGENERALWIDGET_H
