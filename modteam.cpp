#include "modteam.h"
#include "ui_modteam.h"

ModTeam::ModTeam(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModTeam)
{
    ui->setupUi(this);
}

ModTeam::~ModTeam()
{
    delete ui;
}
