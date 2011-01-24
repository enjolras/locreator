#ifndef IMSMDTEREQUIREMENTWIDGET_H
#define IMSMDTEREQUIREMENTWIDGET_H

#include "framewidget.h"

namespace Ui {
    class imsmdTeRequirementWidget;
}

class imsmdTeRequirementWidget : public frameWidget {
    Q_OBJECT
public:
    imsmdTeRequirementWidget(RequirementData *data,QWidget *parent = 0);
    ~imsmdTeRequirementWidget();

private:
    Ui::imsmdTeRequirementWidget *ui;
};

#endif // IMSMDTEREQUIREMENTWIDGET_H
