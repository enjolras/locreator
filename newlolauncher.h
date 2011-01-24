#ifndef NEWLOLAUNCHER_H
#define NEWLOLAUNCHER_H

#include <QObject>

class QWizardPage ;

class newLOLauncher : public QObject
{
    Q_OBJECT
public:
    newLOLauncher(QObject *parent=0);
    void start() ;

private:
    QWizardPage *introPage() ;

};

#endif // NEWLOLAUNCHER_H
