#include "loitem.h"

loItem::loItem(const QList<QVariant> &data, loItem *parent)
{
    parentItem = parent ;
    itemData = data ;
}

loItem::~loItem() {

}

void loItem::appendChild(loItem *child) {

    childItems.append(child) ;

}

loItem* loItem::child(int row) {

    return childItems.value(row) ;

}

int loItem::childCount() const {

    return childItems.count() ;

}

int loItem::row() const {

    if (parentItem)
         return parentItem->childItems.indexOf(const_cast<loItem*>(this));

     return 0;

}

QVariant loItem::data(int column) const {

    return itemData.value(column) ;

}

void loItem::appendData(QVariant data) {

    itemData << data ;

}

int loItem::columnCount() const {
    return itemData.count() ;
}

loItem* loItem::parent() {

    return parentItem ;

}
