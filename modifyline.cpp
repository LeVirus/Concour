#include "modifyline.h"
#include "ui_modifyline.h"

ModifyLine::ModifyLine(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifyLine)
{
    ui->setupUi(this);
    QPushButton* buttonOK = findChild<QPushButton*>("pushButton_2");
    QPushButton* buttonCancel = findChild<QPushButton*>("pushButton");

    if(buttonOK)
    {
        QObject::connect(buttonOK, SIGNAL(clicked()), this, SLOT(clickedOk()));
    }
    if(buttonCancel)
    {
        QObject::connect(buttonCancel, SIGNAL(clicked()), this,
                         SLOT(clickedCancel()));
    }

}

void ModifyLine::setParams(const QString &nom, bool homme)
{
    QComboBox* comboBox = findChild<QComboBox*>("comboBox");
    QLineEdit* lineEdit = findChild<QLineEdit*>("lineEdit");
    if(homme)
    {
        comboBox->setCurrentIndex(HOMME);
    }
    else
    {
        comboBox->setCurrentIndex(FEMME);
    }
    lineEdit->setText(nom);
}

ModifyLine::~ModifyLine()
{
    delete ui;
}

void ModifyLine::clickedOk()
{
    m_memPlayerLine = nullptr;
}

void ModifyLine::clickedCancel()
{
    m_memPlayerLine = nullptr;
}
