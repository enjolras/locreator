#ifndef EJMDGENERALHINTSWIDGET_H
#define EJMDGENERALHINTSWIDGET_H

#include <QWidget>
#include "framewidget.h"
#include "lomodel.h"

namespace Ui {
    class ejmdGeneralHintsWidget;
}

class ejmdGeneralHintsWidget : public frameWidget {
    Q_OBJECT
public:
    ejmdGeneralHintsWidget(EjmdGeneralHints *data, QWidget *parent = 0);
    ~ejmdGeneralHintsWidget();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ejmdGeneralHintsWidget *ui;
};

#endif // EJMDGENERALHINTSWIDGET_H
