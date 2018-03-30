#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::Form)
{
    m_ui->setupUi(this);
    setLayouts();
    setScrolls();
}

void Form::on_pushButton_clicked()
{
    QLineEdit* memLine = findChild<QLineEdit*>("lineEdit");
    QComboBox* comboBox = findChild<QComboBox*>("comboBox");
    if(memLine && comboBox && m_memListMan && m_memListWoman)
    {
        const QString &text = memLine->text();
        if(! checkExist(text, *m_memListMan) && ! checkExist(text, *m_memListWoman))
        {
            const QString &gender = comboBox->currentText();
            if(gender == "Homme")
            {
                m_memListMan->addLayout(new PlayerLine(memLine->text(), true));
            }
            if(gender == "Femme")
            {
                m_memListWoman->addLayout(new PlayerLine(memLine->text(), false));
            }
        }
        memLine->clear();
    }
}

void Form::clearPlayerLines()
{
    for(int i = 0; i < m_memListWoman->count(); ++i)
    {
        QLayoutItem *dd = m_memListWoman->itemAt(i);
        if(dd)delete dd;
    }
    for(int i = 0; i < m_memListMan->count(); ++i)
    {
        QLayoutItem *dd = m_memListMan->itemAt(i);
        if(dd)delete dd;
    }
}

bool Form::checkExist(const QString &str, QVBoxLayout &memVbox)
{
    for(int i = 0; i < memVbox.count(); ++i)
    {
        PlayerLine* memLine = static_cast<PlayerLine*>(memVbox.itemAt(i));
        if(memLine && memLine->getLabel()->text() == str)
        {
            return true;
        }
    }
    return false;
}

void Form::setLayouts()
{
    QScrollArea *sds = findChild<QScrollArea*>("scrollArea");
    QScrollArea *sdsB = findChild<QScrollArea*>("scrollArea_2");
    m_memListMan = new QVBoxLayout(sds);
    m_memListWoman = new QVBoxLayout(sdsB);
    sds->setLayout(m_memListMan);
    sdsB->setLayout(m_memListWoman);
}

void Form::setScrolls()
{
    QWidget* wid = findChild<QScrollArea*>("scrollArea")->
            findChild<QWidget*>("scrollAreaWidgetContents");
    wid->setLayout(m_memListMan);
    wid->setMaximumWidth(300);
    QWidget* widg = findChild<QScrollArea*>("scrollArea_2")->
            findChild<QWidget*>("scrollAreaWidgetContents_4");
    widg->setLayout(m_memListWoman);
    widg->setMaximumWidth(300);
    /**SOLUTION SCROLL*/
}

Form::~Form()
{
    delete m_ui;
    clearPlayerLines();
    if(m_memListMan)delete m_memListMan;
    if(m_memListWoman)delete m_memListWoman;
}
