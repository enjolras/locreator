#ifndef FILEIMAGEWIDGET_H
#define FILEIMAGEWIDGET_H

#include <QWidget>

namespace Ui {
    class fileImageWidget;
}

class fileImageWidget : public QWidget {
    Q_OBJECT
public:
    fileImageWidget(QWidget *parent = 0);
    ~fileImageWidget();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::fileImageWidget *ui;
};

#endif // FILEIMAGEWIDGET_H
