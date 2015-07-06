#ifndef RADIOBUTTONDELEGATE_H
#define RADIOBUTTONDELEGATE_H

#include <QItemDelegate>

class RadioButtonDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit RadioButtonDelegate(QObject *parent = 0);

signals:

public slots:

    void commitMyData();
};

#endif // RADIOBUTTONDELEGATE_H
