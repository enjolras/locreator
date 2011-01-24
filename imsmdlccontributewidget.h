#ifndef IMSMDLCCONTRIBUTEWIDGET_H
#define IMSMDLCCONTRIBUTEWIDGET_H

#include "framewidget.h"

namespace Ui {
    class imsmdLcContributeWidget;
}

class imsmdLcContributeWidget : public frameWidget {
    Q_OBJECT
public:
    imsmdLcContributeWidget(ContributeItem *item,QWidget *parent = 0);
    ~imsmdLcContributeWidget();

private:
    Ui::imsmdLcContributeWidget *ui;
};

#endif // IMSMDLCCONTRIBUTEWIDGET_H
