#include "imsmdlangstringcontainer.h"
#include "ui_imsmdlangstringcontainer.h"
#include "imsmdlangstringwidget.h"

imsmdLangStringContainer::imsmdLangStringContainer(LangString *argLangString, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::imsmdLangStringContainer),
    langString(argLangString)
{
    ui->setupUi(this);

    LangString *tmpLangString = langString ;

    imsmdLangStringWidget *tmpLangStringWidget = new imsmdLangStringWidget(tmpLangString,this,TRUE) ;
    connect(tmpLangStringWidget,SIGNAL(addLine()),this,SLOT(addLine())) ;
    ui->mainLayout->addWidget(tmpLangStringWidget);
    tmpLangString = tmpLangString->next ;

    while(tmpLangString != NULL) {
        imsmdLangStringWidget *tmpLangStringWidget = new imsmdLangStringWidget(tmpLangString,this) ;
        connect(tmpLangStringWidget,SIGNAL(removeLine(LangString*)),this,SLOT(removeLine(LangString*))) ;
        ui->mainLayout->addWidget(tmpLangStringWidget);
        tmpLangString = tmpLangString->next ;
    }

}

imsmdLangStringContainer::~imsmdLangStringContainer()
{
    delete ui;
}

void imsmdLangStringContainer::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void imsmdLangStringContainer::addLine() {
    LangString *tmpNewLangString = new LangString ;
    tmpNewLangString->next = NULL ;

    LangString *tmpLangString = langString ;
    while(tmpLangString->next != NULL) tmpLangString = tmpLangString->next ;
    tmpLangString->next = tmpNewLangString ;

    imsmdLangStringWidget *tmpLangStringWidget = new imsmdLangStringWidget(tmpNewLangString,this) ;
    connect(tmpLangStringWidget,SIGNAL(removeLine(LangString*)),this,SLOT(removeLine(LangString*))) ;
    ui->mainLayout->addWidget(tmpLangStringWidget);
}

void imsmdLangStringContainer::removeLine(LangString *langStringPointer) {
    LangString *tmpLangString = langString ;
    while(tmpLangString!=NULL) {
        if(tmpLangString->next == langStringPointer) {
            tmpLangString->next = tmpLangString->next->next ;
            delete langStringPointer ;
        }
        tmpLangString = tmpLangString->next ;
    }
}
