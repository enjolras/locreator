#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QDialog>

namespace Ui {
    class preferencesDialog;
}

class preferencesDialog : public QDialog {
    Q_OBJECT
public:
    preferencesDialog(QWidget *parent = 0);
    ~preferencesDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::preferencesDialog *ui;

private slots:
    void updateFont() ;
    void updateFontName(QFont font) ;
    void updateFontSize(int size) ;
    void accept() ;

signals:
    void updateFontSignal() ;

};

#endif // PREFERENCESDIALOG_H
