#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "meleemeleeform.h"
#include "modechoosewindow.h"
#include "presetteamform.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    void linkButtons();
    QString getPathFile(QWidget *ptrWidget);
    bool extractAndGetJsonDoc(QJsonDocument &doc);
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void loadDatasFromFile();

private:
    Ui::MainWindow *ui;
    MeleeMeleeForm m_meleeMeleeForm;
    ModeChooseWindow m_modeChooseWindow;
    PresetTeamForm m_presetTeamForm;
};


#endif // MAINWINDOW_H

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
