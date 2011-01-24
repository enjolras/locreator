#ifndef IMSMDRIGHTSWIDGET_H
#define IMSMDRIGHTSWIDGET_H

#include "framewidget.h"

namespace Ui {
    class imsmdRightsWidget;
}

class imsmdRightsWidget : public frameWidget {
    Q_OBJECT
public:
    imsmdRightsWidget(RightsData *data, QWidget *parent = 0);
    ~imsmdRightsWidget();

private:
    Ui::imsmdRightsWidget *ui;

};

#endif // IMSMDRIGHTSWIDGET_H
