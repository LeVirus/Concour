#include "windowsaveask.h"
#include "ui_windowsaveask.h"
#include "meleemeleeform.h"

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
    MeleeMeleeForm::getInstance()->slotSavePlayers();
    MeleeMeleeForm::getInstance()->hide();
    hide();
}

void WindowSaveAsk::closeForm()
{
    MeleeMeleeForm::getInstance()->hide();
    hide();
}

WindowSaveAsk::~WindowSaveAsk()
{
    delete ui;
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
