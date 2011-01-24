#ifndef WIZARDINTROPAGE_H
#define WIZARDINTROPAGE_H

#include <QWizardPage>

namespace Ui {
    class wizardIntroPage;
}

class wizardIntroPage : public QWizardPage {
    Q_OBJECT
public:
    wizardIntroPage(QWidget *parent = 0);
    ~wizardIntroPage();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::wizardIntroPage *ui;
};

#endif // WIZARDINTROPAGE_H
