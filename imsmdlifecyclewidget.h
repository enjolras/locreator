#ifndef IMSMDLIFECYCLEWIDGET_H
#define IMSMDLIFECYCLEWIDGET_H

#include "framewidget.h"

namespace Ui {
    class imsmdLifecycleWidget;
}

class QLayout ;

class imsmdLifecycleWidget : public frameWidget {
    Q_OBJECT
public:
    imsmdLifecycleWidget(LifecycleData *data, QWidget *parent = 0);
    ~imsmdLifecycleWidget();

private:
    Ui::imsmdLifecycleWidget *ui;
    void putContributeItems(ContributeItem *data) ;

};

#endif // IMSMDLIFECYCLEWIDGET_H
