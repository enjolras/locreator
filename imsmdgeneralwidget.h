#ifndef IMSMDGENERALWIDGET_H
#define IMSMDGENERALWIDGET_H

#include "framewidget.h"

namespace Ui {
    class imsmdGeneralWidget;
}

class imsmdGeneralWidget : public frameWidget {
    Q_OBJECT
public:
    imsmdGeneralWidget(GeneralData *argData, QWidget *parent = 0);
    ~imsmdGeneralWidget();

private:
    Ui::imsmdGeneralWidget *ui;
    GeneralData *data ;

private slots:
    void setIdentifier(QString content) ;
    void setLanguage(QString content) ;
};

#endif // IMSMDGENERALWIDGET_H
