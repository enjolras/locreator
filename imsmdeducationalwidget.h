#ifndef IMSMDEDUCATIONALWIDGET_H
#define IMSMDEDUCATIONALWIDGET_H

#include "framewidget.h"

namespace Ui {
    class imsmdEducationalWidget;
}

class imsmdEducationalWidget : public frameWidget {
    Q_OBJECT
public:
    imsmdEducationalWidget(EducationalData *data, QWidget *parent = 0);
    ~imsmdEducationalWidget();

private:
    Ui::imsmdEducationalWidget *ui;
};

#endif // IMSMDEDUCATIONALWIDGET_H
