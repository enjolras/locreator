#include <QtGui/QApplication>
#include <QTranslator>
#include <QLocale>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainWindow w;

    QString locale = QLocale::system().name() ;

    QTranslator translator ;
    translator.load(QString(":/translations/%1.qm").arg(locale)) ;
    a.installTranslator(&translator) ;

    w.show();
    return a.exec();
}
