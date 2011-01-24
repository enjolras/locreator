#ifndef LOITEM_H
#define LOITEM_H

#include <QList>
#include <QVariant>
#include <QIcon>

class loItem
{
public:
    loItem(const QList<QVariant> &data, loItem *parent = 0);
    ~loItem() ;

    void appendChild(loItem *child) ;
    void appendData(QVariant data) ;
    loItem *child(int row) ;
    int childCount() const ;
    QVariant data(int column) const ;
    int columnCount() const;
    int row() const ;
    loItem *parent() ;

private:
        QList<loItem*> childItems ;
        QList<QVariant> itemData ;
        loItem *parentItem ;
};

#endif // LOITEM_H
