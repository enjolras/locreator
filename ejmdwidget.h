#ifndef EJMDWIDGET_H
#define EJMDWIDGET_H

#include <QWidget>
#include "lomodel.h"

namespace Ui {
    class ejmdWidget;
}

class ejmdWidget : public QWidget {
    Q_OBJECT
public:
    ejmdWidget(EjmdMetadata *data, QWidget *parent = 0);
    ~ejmdWidget();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ejmdWidget *ui;
};

#endif // EJMDWIDGET_H
