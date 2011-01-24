#ifndef FILEHTMLWIDGET_H
#define FILEHTMLWIDGET_H

#include <QWidget>

class QNetworkReply ;
class myQTextEdit ;

namespace Ui {
    class fileHtmlWidget;
}

class fileHtmlWidget : public QWidget {
    Q_OBJECT
public:
    fileHtmlWidget(QByteArray *data=0,QWidget *parent = 0);
    ~fileHtmlWidget();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::fileHtmlWidget *ui;
    myQTextEdit *sourceEdit ;

private slots:
    void textChanged() ;

};

#endif // FILEHTMLWIDGET_H
