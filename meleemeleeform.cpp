#include "meleemeleeform.h"
#include "ui_meleemeleeform.h"
#include <QMessageBox>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>

MeleeMeleeForm *MeleeMeleeForm::m_FormInstance;

MeleeMeleeForm::MeleeMeleeForm(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::Form)
{
    m_ui->setupUi(this);
    setLayouts();
    setScrolls();
    m_FormInstance = this;

    QPushButton* buttonSave = findChild<QPushButton*>("pushButton_2");
    QPushButton* buttonGenerate = findChild<QPushButton*>("pushButton_3");

    if(buttonSave)
    {
        QObject::connect(buttonSave, SIGNAL(clicked()), this, SLOT(slotSavePlayers()));
    }
    if(buttonGenerate)
    {
        QObject::connect(buttonGenerate, SIGNAL(clicked()), this, SLOT(openGenerateContestMenu()));
    }
    m_lineEdit = findChild<QLineEdit*>("lineEdit");
    m_comboBox = findChild<QComboBox*>("comboBox");
}

void MeleeMeleeForm::on_pushButton_clicked()
{
    if(m_lineEdit && m_comboBox && m_memListMan && m_memListWoman)
    {
        const QString &text = m_lineEdit->text();
        if(text == "")
        {
            QMessageBox::warning(this, "Erreur", "Le nom entré est vide.");
        }
        else if(! checkExist(text, *m_memListMan) && ! checkExist(text, *m_memListWoman))
        {
            const QString &gender = m_comboBox->currentText();
            if(gender == "Homme")
            {
                m_memListMan->addLayout(new PlayerLine(m_lineEdit->text(), true));
            }
            if(gender == "Femme")
            {
                m_memListWoman->addLayout(new PlayerLine(m_lineEdit->text(), false));
            }
        }
        else
        {
            QMessageBox::warning(this, "Erreur", "Le nom entré est déja existant.");
        }
        m_lineEdit->clear();
    }
    m_saved = false;
}

bool MeleeMeleeForm::checkExist(const QString &str, QVBoxLayout &memVbox) const
{
    for(int i = 0; i < memVbox.count(); ++i)
    {
        PlayerLine* memLine = static_cast<PlayerLine*>(memVbox.itemAt(i));
        if(memLine && memLine->getLabel()->text() == str)
        {
            return true;
        }
    }
    return false;
}

bool MeleeMeleeForm::checkGlobalExist(const QString &str) const
{
    return checkExist(str, *m_memListMan) || checkExist(str, *m_memListWoman);
}

void MeleeMeleeForm::setDataSaved(bool saved)
{
    m_saved = saved;
}

void MeleeMeleeForm::changePlayerLineGenderArray(PlayerLine *playerLine)
{
    if(! playerLine)
    {
        return;
    }
    m_saved = false;
    bool gender = playerLine->getGender();
    if(gender)//new gender :: man
    {
        m_memListWoman->removeItem(playerLine);
        m_memListMan->addLayout(playerLine);
    }
    else//new gender :: woman
    {
        m_memListMan->removeItem(playerLine);
        m_memListWoman->addLayout(playerLine);
    }
}

void MeleeMeleeForm::cleanUpPlayers()
{
    clearPlayerLines();
    if(m_lineEdit)
    {
        m_lineEdit->clear();
    }
}

void MeleeMeleeForm::insertPlayer(bool man, const QString &name)
{
    if(checkGlobalExist(name))
    {
        return;
    }
    if(man && m_memListMan)
    {
        m_memListMan->addLayout(new PlayerLine(name, true));
    }
    else
    {
        if(m_memListWoman)
        {
            m_memListWoman->addLayout(new PlayerLine(name, false));
        }
    }

}

void MeleeMeleeForm::setTeamBuildOption(unsigned int gamesNumber)
{
    m_contestGenWindow.setTeamBuildOption(gamesNumber);
}

void MeleeMeleeForm::setGenerationOK(bool ok)
{
    m_okGenerate = ok;
}

void MeleeMeleeForm::setLayouts()
{
    QScrollArea *sds = findChild<QScrollArea*>("scrollArea");
    QScrollArea *sdsB = findChild<QScrollArea*>("scrollArea_2");
    m_memListMan = new QVBoxLayout(sds);
    m_memListWoman = new QVBoxLayout(sdsB);
    sds->setLayout(m_memListMan);
    sdsB->setLayout(m_memListWoman);
}

void MeleeMeleeForm::setScrolls()
{
    QWidget* wid = findChild<QScrollArea*>("scrollArea")->
            findChild<QWidget*>("scrollAreaWidgetContents");
    wid->setLayout(m_memListMan);
    wid->setMaximumWidth(300);
    QWidget* widg = findChild<QScrollArea*>("scrollArea_2")->
            findChild<QWidget*>("scrollAreaWidgetContents_4");
    widg->setLayout(m_memListWoman);
    widg->setMaximumWidth(300);
    /**SOLUTION SCROLL*/
}

void MeleeMeleeForm::getJsonFromPlayers(QJsonObject &jsonObj) const
{
    if(! jsonObj.empty())
    {
        QMessageBox::warning(m_FormInstance, "Erreur", "Erreur lors de la sauvegarde. L'objet json n'est pas vide.");
        return;
    }

    QJsonArray men, women;

    for(int i = 0; i < m_memListMan->count(); ++i)
    {
        PlayerLine* memLine = static_cast<PlayerLine*>(m_memListMan->itemAt(i));
        if(memLine)
        {
            men.insert(0, memLine->getLabel()->text());
        }
    }
    for(int i = 0; i < m_memListWoman->count(); ++i)
    {
        PlayerLine* memLine = static_cast<PlayerLine*>(m_memListWoman->itemAt(i));
        if(memLine)
        {
            women.insert(0, memLine->getLabel()->text());
        }
    }
    jsonObj.insert("Hommes", men);
    jsonObj.insert("Femmes", women);
}

void MeleeMeleeForm::clearPlayerLines()
{
    bool first = false;
    QVBoxLayout *ptrCurrent = m_memListWoman;//begin women
    do
    {
        QLayoutItem *item = ptrCurrent->layout()->takeAt(0);
        if(item)
        {
            delete item;
        }
        else
        {
            if(!first)
            {
                first = true;
                ptrCurrent = m_memListMan;//finish men
            }
            else
            {
                break;
            }
        }
    }while(true);
}

void MeleeMeleeForm::openGenerateContestMenu()
{
    if(m_contestGenWindow.updateCurrentContestMeleeMelee(m_memListMan, m_memListWoman))
    {
        m_windowConstruct.exec();
        m_contestGenWindow.generateGlobalGames();
        m_contestGenWindow.updateUI();
        m_contestGenWindow.exec();
        m_okGenerate = false;
    }
}

void MeleeMeleeForm::slotSavePlayers()
{
    QString fileName = getPathFile(this);

    QJsonObject jsonObj;
    getJsonFromPlayers(jsonObj);
    QJsonDocument doc(jsonObj);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    QFile file(fileName);
    if (file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << strJson;
        file.close();
    }
    m_saved = true;
}

QString MeleeMeleeForm::getPathFile(QWidget* ptrWidget)
{
    if(! ptrWidget)
    {
        return "";
    }
    return QFileDialog::getSaveFileName(ptrWidget,
                       tr("Save File"),
                       ".",
                                        tr("json(*.json);;All files (*)"));
}

MeleeMeleeForm::~MeleeMeleeForm()
{
    delete m_ui;
    clearPlayerLines();
    if(m_memListMan)delete m_memListMan;
    if(m_memListWoman)delete m_memListWoman;
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
