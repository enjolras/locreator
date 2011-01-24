#ifndef WIZARDPRESENTATIONPAGE_H
#define WIZARDPRESENTATIONPAGE_H

#include <QWizardPage>

namespace Ui {
    class wizardPresentationPage;
}

class wizardPresentationPage : public QWizardPage {
    Q_OBJECT
public:
    wizardPresentationPage(QWidget *parent = 0);
    ~wizardPresentationPage();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::wizardPresentationPage *ui;
};

#endif // WIZARDPRESENTATIONPAGE_H
