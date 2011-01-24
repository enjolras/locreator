#ifndef ABOUTBOX_H
#define ABOUTBOX_H

#include <QDialog>

namespace Ui {
    class aboutBox;
}

class aboutBox : public QDialog {
    Q_OBJECT
public:
    aboutBox(QWidget *parent = 0);
    ~aboutBox();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::aboutBox *ui;
};

#endif // ABOUTBOX_H
