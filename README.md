# qt_qradiobutton_qdatawidgetmapper_example

This is a sample solution to map radio buttons to sql databases in the Qt framework. Originally presented at 

http://stackoverflow.com/questions/31021852/connecting-radio-buttons-to-qsqltablemodel-via-qdatawidgetmapper-in-qt

based on 

http://www.qtcentre.org/threads/21860-QRadioButton-and-QDataWidgetMapper?p=123316#post123316


## Connecting radio buttons to QSqlTableModel via QDataWidgetMapper in Qt

### Original question on stackoverflow


I would like to map a radio buttons to a QDataWidgetMapper as per [this forum thread][1]. I am not sure though how to hook up the delegate mentioned. Could anyone explain this? 

I already have .ui files that contain the radio buttons, among QLineEdits etc. Those are already hooked via a QDataWidgetMapper to a QSqlTableModel. Can I use the solution mentioned in the url above to add the existing radio buttons in the .ui field to the button group, and get the state into the DB?

My radio buttons are actually binary selections, so storing boolean values in the db would be sufficient. I do not want to use a checkbox because radio buttons make the selection more easily comprehensible to the user, in this case.

So far I have added includes to the example .h file

    #include <QWidget>
    #include <QButtonGroup>
    #include <QVBoxLayout>
    #include <QAbstractButton>

and created the .cpp file. 

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
        //connect(button,SIGNAL(clicked()),this,SIGNAL(buttonClicked()));
    }

  [1]: http://www.qtcentre.org/threads/21860-QRadioButton-and-QDataWidgetMapper?p=123316#post123316

###  Answer (my own) ###

The delegate needs to be connected to the mapper.

I have created a sample project that works at http://scanrobot.fi/wp-content/uploads/2015/06/qradiobutton-qsqltablemodel.zip

Here is the essence of what I needed to understand in practice:

    QDataWidgetMapper* mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->toLast();

    QRadioButton *b1=new QRadioButton("a",this);
    QRadioButton *b2=new QRadioButton("b",this);

    RadioButtonDelegate *delegate=new RadioButtonDelegate(this);
    ButtonGroup *group=new ButtonGroup(this);
    mapper->addMapping(group,model->fieldIndex("radio"));

    // set the delegate as the item delegate of mapper
    mapper->setItemDelegate(delegate);
    // connect value change in group to delegate so it can send appropriate signals 
    connect(group,SIGNAL(buttonClicked(int)),delegate,SLOT(commitMyData()));

    group->addButton(b1,1);
    group->addButton(b2,0);


Source for buttongroup.cpp:

    #include "buttongroup.h"
    
    ButtonGroup::ButtonGroup(QWidget *parent) :
        QWidget(parent)
    {
        m_buttonGroup=new QButtonGroup(this);
        connect(m_buttonGroup,SIGNAL(buttonClicked(int)),this,SIGNAL(buttonClicked(int)));
    
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
    }
    
buttongroup.h (nothing very new here compared to the original url):

    #ifndef BUTTONGROUP_H
    #define BUTTONGROUP_H
    
    #include <QWidget>
    #include <QButtonGroup>
    #include <QVBoxLayout>
    #include <QAbstractButton>
    #include <QRadioButton>
    
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

radiobuttondelegate.h (nothing very new here either):

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

radiobuttondelegate.cpp (or here):

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

