#ifndef EJMDPRESENTATIONDESCRIPTIONWIDGET_H
#define EJMDPRESENTATIONDESCRIPTIONWIDGET_H

#include <QWidget>
#include "framewidget.h"

namespace Ui {
    class ejmdPresentationDescriptionWidget;
}

class ejmdPresentationDescriptionWidget : public frameWidget {
    Q_OBJECT
public:
    ejmdPresentationDescriptionWidget(EjmdPresentationDescription *data, QWidget *parent = 0);
    ~ejmdPresentationDescriptionWidget();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ejmdPresentationDescriptionWidget *ui;
};

#endif // EJMDPRESENTATIONDESCRIPTIONWIDGET_H
