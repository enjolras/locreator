#ifndef IMSMDTECHNICALWIDGET_H
#define IMSMDTECHNICALWIDGET_H

#include "framewidget.h"

namespace Ui {
    class imsmdTechnicalWidget;
}

class imsmdTechnicalWidget : public frameWidget {
    Q_OBJECT
public:
    imsmdTechnicalWidget(TechnicalData *data, QWidget *parent = 0);
    ~imsmdTechnicalWidget();

private:
    Ui::imsmdTechnicalWidget *ui;
    void putRequirementItems(RequirementData *data) ;
    void putFormatItems(FormatData *data) ;

};

#endif // IMSMDTECHNICALWIDGET_H
