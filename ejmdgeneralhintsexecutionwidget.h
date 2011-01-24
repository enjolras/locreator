#ifndef EJMDGENERALHINTSEXECUTIONWIDGET_H
#define EJMDGENERALHINTSEXECUTIONWIDGET_H

#include <QWidget>
#include "framewidget.h"
#include "lomodel.h"

namespace Ui {
    class ejmdGeneralHintsExecutionWidget;
}

class ejmdGeneralHintsExecutionWidget : public frameWidget {
    Q_OBJECT
public:
    ejmdGeneralHintsExecutionWidget(EjmdGeneralHintsExecution *data, QWidget *parent = 0);
    ~ejmdGeneralHintsExecutionWidget();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ejmdGeneralHintsExecutionWidget *ui;
};

#endif // EJMDGENERALHINTSEXECUTIONWIDGET_H
