#include "windowteamconstruct.h"
#include "ui_windowteamconstruct.h"
#include "form.h"

WindowTeamConstruct::WindowTeamConstruct(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WindowTeamConstruct)
{
    ui->setupUi(this);
    linkButtons();
}

WindowTeamConstruct::~WindowTeamConstruct()
{
    delete ui;
}

void WindowTeamConstruct::linkButtons()
{
    QPushButton* buttonMelee = findChild<QPushButton*>("pushButton");
    QPushButton* buttonMeleeMelee = findChild<QPushButton*>("pushButton_2");
    QPushButton* buttonManual = findChild<QPushButton*>("pushButton_3");

    if(buttonMelee)
    {
        QObject::connect(buttonMelee, SIGNAL(clicked()), this, SLOT(launchGenerationWindow(unsigned int)));
    }
    if(buttonMeleeMelee)
    {
        QObject::connect(buttonMeleeMelee, SIGNAL(clicked()), this, SLOT(launchGenerationWindow(unsigned int)));
    }
    if(buttonManual)
    {
        QObject::connect(buttonManual, SIGNAL(clicked()), this, SLOT(launchGenerationWindow(unsigned int)));
    }
}

void WindowTeamConstruct::launchGenerationWindow(unsigned int option)
{
    Form *form = Form::getInstance();
    if(form)
    {
        form->setTeamBuildOption(option);
    }
    close();
}
