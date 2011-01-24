#include <QSettings>
#include "preferencesdialog.h"
#include "ui_preferencesdialog.h"

preferencesDialog::preferencesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::preferencesDialog)
{
    ui->setupUi(this);

    QSettings settings("locreator","locreator") ;

    ui->fontName->setCurrentFont(QFont(settings.value("TextEditFontName").toString()));
    ui->fontSize->setValue(settings.value("TextEditFontSize").toInt());

    connect(ui->fontName,SIGNAL(currentFontChanged(QFont)),this,SLOT(updateFontName(QFont))) ;
    connect(ui->fontSize,SIGNAL(valueChanged(int)),this,SLOT(updateFontSize(int))) ;
    connect(this,SIGNAL(updateFontSignal()),this,SLOT(updateFont())) ;

    emit(updateFontSignal()) ;

}

preferencesDialog::~preferencesDialog()
{
    delete ui;
}

void preferencesDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void preferencesDialog::updateFontName(QFont font) {

    Q_UNUSED(font) ;

    emit(updateFontSignal()) ;

}

void preferencesDialog::updateFontSize(int size) {

    Q_UNUSED(size) ;

    emit(updateFontSignal()) ;

}

void preferencesDialog::updateFont() {
    ui->fontPreview->setFont(QFont(ui->fontName->currentFont().family(),ui->fontSize->value()));
}

void preferencesDialog::accept() {
    QSettings settings("locreator","locreator") ;

    settings.setValue("TextEditFontName",ui->fontName->currentFont().family());
    settings.setValue("TextEditFontSize",ui->fontSize->value());

    this->deleteLater();

}
