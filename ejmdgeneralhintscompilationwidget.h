#ifndef EJMDGENERALHINTSCOMPILATIONWIDGET_H
#define EJMDGENERALHINTSCOMPILATIONWIDGET_H

#include <QWidget>
#include "framewidget.h"
#include "lomodel.h"

namespace Ui {
    class ejmdGeneralHintsCompilationWidget;
}

class ejmdGeneralHintsCompilationWidget : public frameWidget {
    Q_OBJECT
public:
    ejmdGeneralHintsCompilationWidget(EjmdGeneralHintsCompilation *data, QWidget *parent = 0);
    ~ejmdGeneralHintsCompilationWidget();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ejmdGeneralHintsCompilationWidget *ui;
};

#endif // EJMDGENERALHINTSCOMPILATIONWIDGET_H
