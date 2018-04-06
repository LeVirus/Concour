#include "windowsaveask.h"
#include "ui_windowsaveask.h"
#include "form.h"

WindowSaveAsk::WindowSaveAsk(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WindowSaveAsk)
{
    ui->setupUi(this);
    linkButtons();
}

void WindowSaveAsk::linkButtons()
{
    QPushButton* buttonCancel = findChild<QPushButton*>("pushButton");
    QPushButton* buttonCloseWithoutSave = findChild<QPushButton*>("pushButton_2");
    QPushButton* buttonSave = findChild<QPushButton*>("pushButton_3");

    if(buttonCancel)
    {
        QObject::connect(buttonCancel, SIGNAL(clicked()), this, SLOT(hide()));
    }
    if(buttonCloseWithoutSave)
    {
        QObject::connect(buttonCloseWithoutSave, SIGNAL(clicked()), this, SLOT(closeForm()));
    }
    if(buttonSave)
    {
        QObject::connect(buttonSave, SIGNAL(clicked()), this, SLOT(saveForm()));
    }
}

void WindowSaveAsk::saveForm()
{
    Form::getInstance()->slotSavePlayers();
}

void WindowSaveAsk::closeForm()
{
    Form::getInstance()->hide();
    hide();
}

WindowSaveAsk::~WindowSaveAsk()
{
    delete ui;
}
