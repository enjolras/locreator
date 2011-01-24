#ifndef EJMDGENERALHINTSSUBMISSIONWIDGET_H
#define EJMDGENERALHINTSSUBMISSIONWIDGET_H

#include <QWidget>
#include "framewidget.h"
#include "lomodel.h"

namespace Ui {
    class ejmdGeneralHintsSubmissionWidget;
}

class ejmdGeneralHintsSubmissionWidget : public frameWidget {
    Q_OBJECT
public:
    ejmdGeneralHintsSubmissionWidget(EjmdGeneralHintsSubmission *data, QWidget *parent = 0);
    ~ejmdGeneralHintsSubmissionWidget();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ejmdGeneralHintsSubmissionWidget *ui;
};

#endif // EJMDGENERALHINTSSUBMISSIONWIDGET_H
