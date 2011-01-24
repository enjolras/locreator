#ifndef WIZARDEVSAMPLEPAGE_H
#define WIZARDEVSAMPLEPAGE_H

#include <QWizardPage>

namespace Ui {
    class wizardEvSamplePage;
}

class wizardEvSamplePage : public QWizardPage {
    Q_OBJECT
public:
    wizardEvSamplePage(QWidget *parent = 0);
    ~wizardEvSamplePage();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::wizardEvSamplePage *ui;
};

#endif // WIZARDEVSAMPLEPAGE_H
