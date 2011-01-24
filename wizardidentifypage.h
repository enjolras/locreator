#ifndef WIZARDIDENTIFYPAGE_H
#define WIZARDIDENTIFYPAGE_H

#include <QWizardPage>

namespace Ui {
    class wizardIdentifyPage;
}

class wizardIdentifyPage : public QWizardPage {
    Q_OBJECT
public:
    wizardIdentifyPage(QWidget *parent = 0);
    ~wizardIdentifyPage();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::wizardIdentifyPage *ui;
};

#endif // WIZARDIDENTIFYPAGE_H
