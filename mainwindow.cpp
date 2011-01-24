#include <QFileDialog>
#include <QFileInfo>
#include <QSettings>
#include <QFile>
#include <QGridLayout>
#include <QByteArray>
#include <QFlags>
#include "lowriter.h"
#include "enums.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lomodel.h"
#include "aboutBox.h"
#include "filetextwidget.h"
#include "filehtmlwidget.h"
#include "fileimagewidget.h"
#include "preferencesdialog.h"
#include "imsmdwidget.h"
#include "ejmdwidget.h"
#include "newlolauncher.h"

mainWindow::mainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainWindow)
{
    ui->setupUi(this);

    ui->action_New->setIcon(style()->standardIcon(QStyle::SP_FileIcon)) ;
    ui->action_Open->setIcon(style()->standardIcon(QStyle::SP_DialogOpenButton)) ;
    ui->action_Save->setIcon(style()->standardIcon(QStyle::SP_DialogSaveButton)) ;
    ui->actionSave_As->setIcon(style()->standardIcon(QStyle::SP_FileDialogNewFolder)) ;
    ui->action_Quit->setIcon(style()->standardIcon(QStyle::SP_DialogCloseButton)) ;
    ui->action_About_loCreator->setIcon(style()->standardIcon(QStyle::SP_MessageBoxInformation)) ;

    ui->mainToolBar->addAction(ui->action_New) ;
    ui->mainToolBar->addAction(ui->action_Open) ;
    ui->mainToolBar->addAction(ui->action_Save) ;
    ui->mainToolBar->addAction(ui->actionSave_As) ;
    ui->mainToolBar->addSeparator() ;
    ui->mainToolBar->addAction(ui->action_About_loCreator) ;

    QSettings settings("locreator","locreator") ;
    restoreGeometry(settings.value("Geometry").toByteArray()) ;

    connect(ui->action_New,SIGNAL(triggered()),this,SLOT(launchNewLO())) ;
    connect(ui->action_Open,SIGNAL(triggered()),this,SLOT(selectFileName())) ;
    connect(ui->actionSave_As,SIGNAL(triggered()),this,SLOT(selectSaveAs())) ;
    connect(ui->action_About_loCreator,SIGNAL(triggered()),this,SLOT(showAboutBox())) ;
    connect(ui->treeView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(selectedItem(QModelIndex))) ;
    connect(ui->actionAbout_Qt,SIGNAL(triggered()),qApp,SLOT(aboutQt())) ;
    connect(ui->actionPre_ferences,SIGNAL(triggered()),this,SLOT(launchPreferences())) ;
}

mainWindow::~mainWindow()
{
    QSettings settings("locreator","locreator") ;
    settings.setValue("Geometry",saveGeometry()) ;
    delete ui;
}

void mainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void mainWindow::selectFileName() {

    QSettings settings("locreator","locreator") ;

    QString tmpFileName = QFileDialog::getOpenFileName(this,
                                                       tr("Open LO"),
                                                       settings.value("WorkDir").toString(),
                                                       tr("All files (* *.*)")) ;

    if(tmpFileName == NULL) return ;

    fileName = new QFileInfo(tmpFileName) ;

    settings.setValue("WorkDir",QVariant(fileName->absolutePath())) ;

    loModel *tmpTree = new loModel() ;
    if(tmpTree->setFile(fileName)) {
        tree = tmpTree ;
        if(ui->treeView->model()) {
            delete ui->treeView->model() ;
        }
        if(ui->widget->layout()) {
            delete ui->widget->layout()->takeAt(0)->widget() ;
            delete ui->widget->layout() ;
        }
        ui->treeView->setModel(tree) ;
        ui->treeView->resizeColumnToContents(0) ;

        this->setWindowTitle(fileName->absoluteFilePath() + " - loCreator");

    } else {
        tmpTree->deleteLater();
    }
}

void mainWindow::selectSaveAs() {

    QSettings settings("locreator","locreator") ;

    QString tmpFileName = QFileDialog::getSaveFileName(this,
                                                       tr("Save as..."),
                                                       (settings.value("SaveDir").isValid() ? settings.value("SaveDir").toString() : settings.value("WorkDir").toString()),
                                                       tr("All files (* *.*)")) ;
    if(tmpFileName == NULL) return ;

    fileName = new QFileInfo(tmpFileName) ;

    settings.setValue("SaveDir",QVariant(fileName->absolutePath())) ;

    loWriter writer(fileName,tree) ;

}

void mainWindow::showAboutBox() {

    aboutBox *about = new aboutBox(this) ;
    about->show() ;

}

void mainWindow::selectedItem(const QModelIndex &index) {

    if(!tree->data(index,Qt::UserRole+2).toInt()) {

    if(ui->widget->layout()) {
        delete ui->widget->layout()->takeAt(0)->widget() ;
        delete ui->widget->layout() ;
    }

    QGridLayout *tmpLayout = new QGridLayout(ui->widget) ;
    tmpLayout->setContentsMargins(0,0,0,0);

    QWidget *tmpWidget ;

    int itemType = qVariantValue<int>(tree->data(index,Qt::UserRole+1)) ;
    QFlags<ItemType::ItemTypes> itemFlags(itemType) ;

    if(itemFlags.testFlag(ItemType::ImsmdMetadata)) {
        tmpWidget = (QWidget*)new imsmdWidget(&qVariantValue<ImsmdMetadata>(tree->data(index,Qt::UserRole)),ui->widget) ;
    } else if(itemFlags.testFlag(ItemType::EjmdMetadata)) {
        tmpWidget = (QWidget*)  new ejmdWidget(&qVariantValue<EjmdMetadata>(tree->data(index,Qt::UserRole)),ui->widget) ;
    } else if(itemFlags.testFlag(ItemType::File)) {
        if(itemFlags.testFlag(ItemType::FileText)) {
            tmpWidget = (QWidget*)new fileTextWidget(&qVariantValue<QByteArray>(tree->data(index,Qt::UserRole)),ui->widget) ;
        } else if(itemFlags.testFlag(ItemType::FileHtml)) {
            tmpWidget = (QWidget*)new fileHtmlWidget(&qVariantValue<QByteArray>(tree->data(index,Qt::UserRole)),ui->widget) ;
        } else if(itemFlags.testFlag(ItemType::FileImage)) {
            tmpWidget = (QWidget*)new fileImageWidget(ui->widget) ;
        }
    }

    tmpLayout->addWidget(tmpWidget) ;
    ui->widget->setLayout(tmpLayout) ;
}

}

void mainWindow::launchPreferences() {

    preferencesDialog *prefDialog = new preferencesDialog(this) ;
    prefDialog->show();

}

void mainWindow::launchNewLO() {
    newLOLauncher *newLO = new newLOLauncher(this) ;
    newLO->start();
}
