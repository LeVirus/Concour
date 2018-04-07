#include "windowteamconstruct.h"
#include "ui_windowteamconstruct.h"
#include "form.h"
#include <QRadioButton>

WindowTeamConstruct::WindowTeamConstruct(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WindowTeamConstruct)
{
    ui->setupUi(this);
    linkButtons();
    linkRadio();
}

WindowTeamConstruct::~WindowTeamConstruct()
{
    delete ui;
}

void WindowTeamConstruct::linkButtons()
{
    QPushButton* buttonOK = findChild<QPushButton*>("pushButton");
    QPushButton* buttonCancel = findChild<QPushButton*>("pushButton_2");

    if(buttonOK)
    {
        QObject::connect(buttonOK, SIGNAL(clicked()), this, SLOT(launchGenerationWindow()));
    }
    if(buttonCancel)
    {
        QObject::connect(buttonCancel, SIGNAL(clicked()), this, SLOT(cancel()));
    }
}

void WindowTeamConstruct::linkRadio()
{
    m_radMelee = findChild<QRadioButton*>("radioButton");
    m_radManual = findChild<QRadioButton*>("radioButton_2");
    m_radMeleeMelee = findChild<QRadioButton*>("radioButton_3");
}

void WindowTeamConstruct::launchGenerationWindow()
{
    Form *form = Form::getInstance();
    if(form)
    {
        if(m_radMelee && m_radManual && m_radMeleeMelee)
        {
            unsigned int option;
            if(m_radManual->isChecked())
            {
                option = MANUAL;
            }
            else if(m_radMelee)
            {
                option = MELEE;
            }
            else
            {
                option = MELEE_MELEE;
            }
            form->setTeamBuildOption(option);
        }
    }
    close();
}

void WindowTeamConstruct::cancel()
{
    close();
}
