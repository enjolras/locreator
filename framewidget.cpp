#include <QLayout>
#include "framewidget.h"
#include "imsmdlangstringcontainer.h"

frameWidget::frameWidget(QWidget *parent) :
    QWidget(parent),
    frameui(new Ui::frameWidget)
{
    frameui->setupUi(this);

    frameui->bannerLabel->setVisible(FALSE);

    connect(frameui->bannerLabel,SIGNAL(clicked()),this,SLOT(switchBanner())) ;
    connect(frameui->titleLabel,SIGNAL(clicked()),this,SLOT(switchBanner())) ;

}

frameWidget::~frameWidget()
{
    delete frameui;
}

void frameWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        frameui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void frameWidget::setTitle(const QString &title) {
    frameui->bannerLabel->setText(title);
    frameui->titleLabel->setText(title);
}

void frameWidget::switchBanner() {
    if(frameui->bannerLabel->isVisible()) {
        frameui->bannerLabel->setVisible(FALSE);
        frameui->mainWidget->setVisible(TRUE);
        frameui->titleLabel->setVisible(TRUE);
    } else {
        frameui->bannerLabel->setVisible(TRUE);
        frameui->mainWidget->setVisible(FALSE);
        frameui->titleLabel->setVisible(FALSE);
    }
}

void frameWidget::putLangString(LangString *langString, QLayout *layout) {
    imsmdLangStringContainer *tmpWidget = new imsmdLangStringContainer(langString,this) ;
    layout->addWidget(tmpWidget);
}
