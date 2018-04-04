#include "contestgenerate.h"
#include "ui_contestgenerate.h"

ContestGenerate::ContestGenerate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContestGenerate)
{
    ui->setupUi(this);
}

ContestGenerate::~ContestGenerate()
{
    delete ui;
}
