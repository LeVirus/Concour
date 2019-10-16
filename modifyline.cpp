#include "modifyline.h"
#include "ui_modifyline.h"
#include "playerline.h"
#include "meleemeleeform.h"
#include <QComboBox>
#include <QLineEdit>
#include <QMessageBox>
#include <QKeyEvent>

ModifyLine::ModifyLine(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifyLine)
{
    ui->setupUi(this);
    QPushButton* buttonOK = findChild<QPushButton*>("pushButton_2");
    QPushButton* buttonCancel = findChild<QPushButton*>("pushButton");
    m_comboBox = findChild<QComboBox*>("comboBox");
    m_lineEdit = findChild<QLineEdit*>("lineEdit");

    if(buttonOK)
    {
        QObject::connect(buttonOK, SIGNAL(clicked()), this, SLOT(clickedOk()));
    }
    if(buttonCancel)
    {
        QObject::connect(buttonCancel, SIGNAL(clicked()), this,
                         SLOT(clickedCancel()));
    }

}

void ModifyLine::setParams(const QString &nom, bool homme, PlayerLine *refPlayerLine)
{
    if(m_comboBox && m_lineEdit)
    {
        if(homme)
        {
            m_comboBox->setCurrentIndex(HOMME);
        }
        else
        {
            m_comboBox->setCurrentIndex(FEMME);
        }
        m_PreviousLabelValue = nom;
        m_lineEdit->setText(nom);
        m_memPlayerLine = refPlayerLine;
    }
}

void ModifyLine::clickedOk()
{
    if(m_comboBox && m_lineEdit && m_memPlayerLine)
    {
        modifyPlayerLineGender();

        if(! modifyPlayerLineLabel())
        {
            return;
        }
    }
    m_memPlayerLine = nullptr;
    MeleeMeleeForm::getInstance()->setDataSaved(false);
    hide();
}

bool ModifyLine::modifyPlayerLineLabel()
{
    MeleeMeleeForm* instance = MeleeMeleeForm::getInstance();
    const QString &memStrLabel = m_lineEdit->text();
    if(m_PreviousLabelValue != memStrLabel && instance)
    {
        if(! instance->checkGlobalExist(memStrLabel))
        {
            m_memPlayerLine->setLabel(memStrLabel);
        }
        else
        {
            QMessageBox::warning(this, "Erreur", "Le nom entré est déja existant.");
            return false;
        }
    }
    return true;
}

void ModifyLine::modifyPlayerLineGender()
{
    bool currentGender = m_memPlayerLine->getGender();
    if(m_comboBox->currentIndex() == HOMME)
    {
        m_memPlayerLine->setGender(true);
    }
    else if(m_comboBox->currentIndex() == FEMME)
    {
        m_memPlayerLine->setGender(false);
    }
    if(currentGender != m_memPlayerLine->getGender())
    {
        changeArrayLine();
    }
}

void ModifyLine::clickedCancel()
{
    m_memPlayerLine = nullptr;
    hide();
}

void ModifyLine::changeArrayLine()
{
    MeleeMeleeForm::getInstance()->changePlayerLineGenderArray(m_memPlayerLine);
}

void ModifyLine::keyPressEvent(QKeyEvent *e)
{
    switch (e->key ()) {
    case Qt::Key_Return:
    case Qt::Key_Enter:
    clickedOk();
        break;

    default:
        QDialog::keyPressEvent (e);
    }
}

ModifyLine::~ModifyLine()
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
