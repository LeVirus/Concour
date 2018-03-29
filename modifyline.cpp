#include "modifyline.h"
#include "ui_modifyline.h"

ModifyLine::ModifyLine(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifyLine)
{
    ui->setupUi(this);
}

ModifyLine::~ModifyLine()
{
    delete ui;
}
