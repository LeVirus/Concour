#include "windowteamconstruct.h"
#include "ui_windowteamconstruct.h"
#include "meleemeleeform.h"
#include "presetteamform.h"
#include <QRadioButton>
#include <QSpinBox>
#include <cassert>

WindowTeamConstruct::WindowTeamConstruct(bool meleeMeleeMode, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WindowTeamConstruct),
    m_meleeMeleeMode(meleeMeleeMode)
{
    ui->setupUi(this);
    linkButtons();
    linkRadio();
}

void WindowTeamConstruct::memPresetTeamForm(PresetTeamForm *form)
{
    m_presetTeamForm = form;
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
    m_spinNumberGames = findChild<QSpinBox*>("spinBox");
}

void WindowTeamConstruct::launchGenerationWindow()
{
    if(m_spinNumberGames)
    {
        if(m_meleeMeleeMode)
        {
            MeleeMeleeForm *form = MeleeMeleeForm::getInstance();
            if(form)
            {
                form->setTeamBuildOption(m_spinNumberGames->value());
                form->setGenerationOK(true);
            }
        }
        //preset team
        else
        {
            assert(m_presetTeamForm);
            m_presetTeamForm->setGamesNumber(m_spinNumberGames->value());
        }
    }
    close();
}


void WindowTeamConstruct::cancel()
{
    close();
}

/**
 * Petanque Competition Management Program
 * Copyright (C) 2018 Cyril Charbonneau
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * his program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
