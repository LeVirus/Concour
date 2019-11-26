#include "modteam.h"
#include "ui_modteam.h"
#include "teamline.h"
#include "modteam.h"
#include "presetteamform.h"
#include <cassert>

ModTeam::ModTeam(TeamLine &teamLine, QWidget *parent):
    QDialog(parent),
    ui(new Ui::ModTeam),
    m_teamLine(teamLine)
{
    ui->setupUi(this);
    linkFormWidgets();
    initForm();
}

ModTeam::~ModTeam()
{
    delete ui;
}

void ModTeam::initForm()
{
    m_oldPlayerA = m_teamLine.getPlayerA();
    m_oldPlayerB = m_teamLine.getPlayerB();
    m_oldPlayerC = m_teamLine.getPlayerC();
    m_linePlayerA->setText(QString(m_oldPlayerA.c_str()));
    m_linePlayerB->setText(QString(m_oldPlayerB.c_str()));
    if(m_teamLine.threePlayers())
    {
        m_linePlayerC->setText(QString(m_oldPlayerC.c_str()));
    }
    else
    {
        m_labelPlayerC->hide();
        m_linePlayerC->hide();
    }
}

void ModTeam::linkFormWidgets()
{
    m_labelPlayerC = findChild<QLabel*>("joueurC");
    assert(m_labelPlayerC);
    m_buttonOk= findChild<QPushButton*>("pushButton");
    assert(m_buttonOk);
    m_buttonCancel = findChild<QPushButton*>("pushButton_2");
    assert(m_buttonCancel);
    m_linePlayerA = findChild<QLineEdit*>("lineEdit");
    assert(m_linePlayerA);
    m_linePlayerB = findChild<QLineEdit*>("lineEdit_2");
    assert(m_linePlayerB);
    m_linePlayerC = findChild<QLineEdit*>("lineEdit_3");
    assert(m_linePlayerC);
}

void ModTeam::on_pushButton_2_clicked()
{
    close();
}

void ModTeam::on_pushButton_clicked()
{
    std::string playerA = m_linePlayerA->text().toStdString();
    std::string playerB = m_linePlayerB->text().toStdString();
    std::string playerC = m_linePlayerC->text().toStdString();
    //rm old entry and check if new entries not already exist
    if(m_teamLine.getPresetTeamForm().delTeam(
                m_oldPlayerA, m_oldPlayerB, m_oldPlayerC))
    {
        if(m_teamLine.getPresetTeamForm().addTeam(playerA, playerB, playerC))
        {
            //if OK
            m_teamLine.setPlayers(playerA, playerB, playerC);
            close();
        }
        else
        {
            //else replace old players DIRTY
            m_teamLine.getPresetTeamForm().addTeam(
                        m_oldPlayerA, m_oldPlayerB, m_oldPlayerC);
        }
    }
    else
    {
        assert(false);
    }
}
