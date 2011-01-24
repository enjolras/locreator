#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>

class QFileInfo ;
class loModel ;

namespace Ui {
    class mainWindow;
}

class mainWindow : public QMainWindow {
    Q_OBJECT
public:
    mainWindow(QWidget *parent = 0);
    ~mainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    QFileInfo *fileName ;
    Ui::mainWindow *ui;
    loModel *tree ;

private slots:
    void selectFileName() ;
    void showAboutBox() ;
    void selectedItem(const QModelIndex &index) ;
    void launchPreferences() ;
    void selectSaveAs() ;
    void launchNewLO() ;

};

#endif // MAINWINDOW_H
