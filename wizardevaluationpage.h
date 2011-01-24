#ifndef WIZARDEVALUATIONPAGE_H
#define WIZARDEVALUATIONPAGE_H

#include <QWizardPage>

namespace Ui {
    class wizardEvaluationPage;
}

class wizardEvaluationPage : public QWizardPage {
    Q_OBJECT
public:
    wizardEvaluationPage(QWidget *parent = 0);
    ~wizardEvaluationPage();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::wizardEvaluationPage *ui;
};

#endif // WIZARDEVALUATIONPAGE_H
