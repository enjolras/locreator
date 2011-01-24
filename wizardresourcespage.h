#ifndef WIZARDRESOURCESPAGE_H
#define WIZARDRESOURCESPAGE_H

#include <QWizardPage>

namespace Ui {
    class wizardResourcesPage;
}

class wizardResourcesPage : public QWizardPage {
    Q_OBJECT
public:
    wizardResourcesPage(QWidget *parent = 0);
    ~wizardResourcesPage();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::wizardResourcesPage *ui;
};

#endif // WIZARDRESOURCESPAGE_H
