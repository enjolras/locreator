#ifndef IMSMDCLASSIFICATIONWIDGET_H
#define IMSMDCLASSIFICATIONWIDGET_H

#include "framewidget.h"

namespace Ui {
    class imsmdClassificationWidget;
}

class imsmdClassificationWidget : public frameWidget {
    Q_OBJECT
public:
    imsmdClassificationWidget(ClassificationData *data, QWidget *parent = 0);
    ~imsmdClassificationWidget();

private:
    Ui::imsmdClassificationWidget *ui;

};

#endif // IMSMDCLASSIFICATIONWIDGET_H
