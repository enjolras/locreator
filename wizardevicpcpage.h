#ifndef WIZARDEVICPCPAGE_H
#define WIZARDEVICPCPAGE_H

#include <QWizardPage>

namespace Ui {
    class wizardEvIcpcPage;
}

class wizardEvIcpcPage : public QWizardPage {
    Q_OBJECT
public:
    wizardEvIcpcPage(QWidget *parent = 0);
    ~wizardEvIcpcPage();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::wizardEvIcpcPage *ui;
};

#endif // WIZARDEVICPCPAGE_H
