#include "modifyline.h"
#include "ui_modifyline.h"

ModifyLine::ModifyLine(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifyLine)
{
    ui->setupUi(this);
}

void ModifyLine::setParams(const QString &nom, bool homme)
{
    QComboBox* comboBox = findChild<QComboBox*>("comboBox");
    QLineEdit* lineEdit = findChild<QLineEdit*>("lineEdit");
    if(homme)
    {
        comboBox->setCurrentIndex(0);
    }
    else
    {
        comboBox->setCurrentIndex(1);
    }
    lineEdit->setText(nom);
}

ModifyLine::~ModifyLine()
{
    delete ui;
}

void ModifyLine::on_buttonBox_clicked()
{

}
