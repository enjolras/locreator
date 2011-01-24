#include <QWizard>
#include <QLabel>
#include <QVBoxLayout>
#include "newlolauncher.h"
#include "wizardintropage.h"
#include "wizardidentifypage.h"
#include "wizardresourcespage.h"
#include "wizardpresentationpage.h"
#include "wizardevaluationpage.h"
#include "wizardevsamplepage.h"
#include "wizardevicpcpage.h"
#include "wizardevioipage.h"

newLOLauncher::newLOLauncher(QObject *parent) : QObject(parent)
{

}

void newLOLauncher::start() {

    wizardIntroPage *introPage = new wizardIntroPage ;
    wizardIdentifyPage *identifyPage = new wizardIdentifyPage ;
    wizardResourcesPage *resourcesPage = new wizardResourcesPage ;
    wizardPresentationPage *presentationPage = new wizardPresentationPage ;
    wizardEvaluationPage *evaluationPage = new wizardEvaluationPage ;
    wizardEvSamplePage *evSamplePage = new wizardEvSamplePage ;
    wizardEvIcpcPage *evIcpcPage = new wizardEvIcpcPage ;
    wizardEvIoiPage *evIoiPage = new wizardEvIoiPage ;

    QWizard *wizard = new QWizard();
    wizard->setWizardStyle(QWizard::ModernStyle);
    wizard->addPage(introPage) ;
    wizard->addPage(identifyPage);
    wizard->addPage(presentationPage) ;
    wizard->addPage(resourcesPage) ;
    wizard->addPage(evaluationPage) ;
    wizard->addPage(evSamplePage) ;
    wizard->addPage(evIcpcPage) ;
    wizard->addPage(evIoiPage) ;

    wizard->setWindowTitle(tr("Create New LO"));

    wizard->show();
}
