#ifndef EJMDPRESENTATIONWIDGET_H
#define EJMDPRESENTATIONWIDGET_H

#include <QWidget>
#include "framewidget.h"
#include "lomodel.h"

namespace Ui {
    class ejmdPresentationWidget;
}

class ejmdPresentationWidget : public frameWidget {
    Q_OBJECT
public:
    ejmdPresentationWidget(EjmdPresentation *data, QWidget *parent = 0);
    ~ejmdPresentationWidget();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ejmdPresentationWidget *ui;
};

#endif // EJMDPRESENTATIONWIDGET_H
