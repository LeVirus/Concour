#include "modechoosewindow.h"
#include "ui_modechoosewindow.h"

ModeChooseWindow::ModeChooseWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModeChooseWindow)
{
    ui->setupUi(this);
    m_radioMeleeMeleeButton = findChild<QRadioButton*>("radioButton_3");
}

ModeChooseWindow::~ModeChooseWindow()
{
    delete ui;
}

void ModeChooseWindow::on_OKButton_clicked()
{
    m_OK = true;
    close();
}

void ModeChooseWindow::on_CancelButton_clicked()
{
    m_OK = false;
    close();
}
