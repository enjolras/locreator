#ifndef EJMDSOLUTIONWIDGET_H
#define EJMDSOLUTIONWIDGET_H

#include <QWidget>
#include "framewidget.h"
#include "lomodel.h"

namespace Ui {
    class ejmdSolutionWidget;
}

class ejmdSolutionWidget : public frameWidget {
    Q_OBJECT
public:
    ejmdSolutionWidget(EjmdSolution *data, QWidget *parent = 0);
    ~ejmdSolutionWidget();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ejmdSolutionWidget *ui;
};

#endif // EJMDSOLUTIONWIDGET_H
