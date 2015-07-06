#include "buttongroup.h"

ButtonGroup::ButtonGroup(QWidget *parent) :
    QWidget(parent)
{
    m_buttonGroup=new QButtonGroup(this);
    m_layout=new QVBoxLayout(this);
    connect(m_buttonGroup,SIGNAL(buttonClicked(int)),this,SIGNAL(buttonClicked(int)));
    setLayout(m_layout);
}

int ButtonGroup::getCheckedId()
{
    int id=m_buttonGroup->id(m_buttonGroup->checkedButton());
    return id;
}

void ButtonGroup::checkId(int id)
{
    m_buttonGroup->button(id)->setChecked(true);
}

void ButtonGroup::addButton(QAbstractButton *button, int id)
{
    m_buttonGroup->addButton(button,id);
    m_layout->addWidget(button);
}
