#include "radiobuttondelegate.h"
#include <QDebug>
RadioButtonDelegate::RadioButtonDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}
void RadioButtonDelegate::commitMyData() {
    QWidget *obj = qobject_cast<QWidget*>(sender());
    emit commitData(obj);
    emit closeEditor(obj);

    qDebug() << "commitMyData";
}
