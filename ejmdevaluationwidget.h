#ifndef EJMDEVALUATIONWIDGET_H
#define EJMDEVALUATIONWIDGET_H

#include <QWidget>
#include "framewidget.h"
#include "lomodel.h"

namespace Ui {
    class ejmdEvaluationWidget;
}

class ejmdEvaluationWidget : public frameWidget {
    Q_OBJECT
public:
    ejmdEvaluationWidget(EjmdEvaluation *data, QWidget *parent = 0);
    ~ejmdEvaluationWidget();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ejmdEvaluationWidget *ui;
};

#endif // EJMDEVALUATIONWIDGET_H
