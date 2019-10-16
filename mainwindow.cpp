#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    linkButtons();
}

void MainWindow::linkButtons()
{
    QPushButton* buttonNew = findChild<QPushButton*>("pushButton_2");
    if(buttonNew)
    {
        QObject::connect(buttonNew, SIGNAL(clicked()), this, SLOT(loadDatasFromFile()));
    }
    QPushButton* buttonLoad = findChild<QPushButton*>("pushButton_3");
    if(buttonLoad)
    {
        QObject::connect(buttonLoad, SIGNAL(clicked()), this, SLOT(close()));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    m_meleeMeleeForm.cleanUpPlayers();
    m_meleeMeleeForm.setDataSaved(true);
    m_modeChooseWindow.exec();
    if(m_modeChooseWindow.checkOK())
    {
        if(m_modeChooseWindow.isMeleeMeleeMode())
        {
            m_meleeMeleeForm.exec();
        }
        else
        {
            m_presetTeamForm.exec();
        }
    }
}

QString MainWindow::getPathFile(QWidget* ptrWidget)
{
    if(! ptrWidget)
    {
        return "";
    }
    QFileDialog dialog;
    dialog.setDefaultSuffix("json");//doesn't work
    return dialog.getOpenFileName(ptrWidget,
                       tr("Load File"), ".", tr("json(*.json);;All files (*)"));
}

bool MainWindow::extractAndGetJsonDoc(QJsonDocument &doc)
{
    QString fileName = getPathFile(this), jsonContent;
    if (fileName.size() == 0)
    {
        return false;
    }
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream >> jsonContent;
        file.close();
    }
    else
    {
        return false;
    }

    doc = QJsonDocument::fromJson(jsonContent.toUtf8());
    if(doc.isNull() || doc.isEmpty())
    {
        QMessageBox::warning(this, "Erreur", "Le fichier est vide.");
        return false;
    }
    return true;
}

void MainWindow::loadDatasFromFile()
{
    MeleeMeleeForm *form = MeleeMeleeForm::getInstance();
    if(!form)
    {
        return;
    }
    QJsonDocument jsonDoc;
    if(! extractAndGetJsonDoc(jsonDoc))
    {
        return;
    }
    QJsonObject obj = jsonDoc.object();
    if(! obj["Femmes"].isArray() || ! obj["Hommes"].isArray())
    {
        QMessageBox::warning(this, "Erreur", "Les données de ce fichier sont corrompues.");
        return;
    }

    //clean up existing form
    m_meleeMeleeForm.cleanUpPlayers();
    m_meleeMeleeForm.setDataSaved(true);

    QJsonArray women = obj["Femmes"].toArray();
    QJsonArray men = obj["Hommes"].toArray();
    for(int i = 0; i < women.count(); ++i)
    {
        form->insertPlayer(false, women.at(i).toString());
    }
    for(int i = 0; i < men.count(); ++i)
    {
        form->insertPlayer(true, men.at(i).toString());
    }
    m_meleeMeleeForm.exec();
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
