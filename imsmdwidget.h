#ifndef IMSMDWIDGET_H
#define IMSMDWIDGET_H

#include <QWidget>
#include "lomodel.h"

namespace Ui {
    class imsmdWidget;
}

class imsmdWidget : public QWidget {
    Q_OBJECT
public:
    imsmdWidget(ImsmdMetadata *data, QWidget *parent = 0);
    ~imsmdWidget();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::imsmdWidget *ui;
};

#endif // IMSMDWIDGET_H
