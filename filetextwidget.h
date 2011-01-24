#ifndef FILETEXTWIDGET_H
#define FILETEXTWIDGET_H

#include <QWidget>

class QByteArray ;
class myQTextEdit ;

namespace Ui {
    class fileTextWidget;
}

class fileTextWidget : public QWidget {
    Q_OBJECT
public:
    fileTextWidget(QByteArray *data=0,QWidget *parent = 0);
    ~fileTextWidget();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::fileTextWidget *ui;
    myQTextEdit *textEdit ;
};

#endif // FILETEXTWIDGET_H
