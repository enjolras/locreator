#ifndef WIZARDEVIOIPAGE_H
#define WIZARDEVIOIPAGE_H

#include <QWizardPage>

namespace Ui {
    class wizardEvIoiPage;
}

class wizardEvIoiPage : public QWizardPage {
    Q_OBJECT
public:
    wizardEvIoiPage(QWidget *parent = 0);
    ~wizardEvIoiPage();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::wizardEvIoiPage *ui;
};

#endif // WIZARDEVIOIPAGE_H
