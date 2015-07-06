#ifndef BUTTONGROUP_H
#define BUTTONGROUP_H

#include <QWidget>
#include <QButtonGroup>
#include <QVBoxLayout>
#include <QAbstractButton>

class ButtonGroup : public QWidget
{
    Q_OBJECT
public:
    explicit ButtonGroup(QWidget *parent = 0);

    Q_PROPERTY(int checkedId READ getCheckedId WRITE checkId USER true)
    int getCheckedId();
    void checkId(int id);

    void addButton(QAbstractButton *button, int id);

signals:
    void buttonClicked(int);

private:
    QButtonGroup *m_buttonGroup;
    QVBoxLayout *m_layout;


};

#endif // BUTTONGROUP_H
