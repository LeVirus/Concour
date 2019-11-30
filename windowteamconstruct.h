#ifndef WINDOWTEAMCONSTRUCT_H
#define WINDOWTEAMCONSTRUCT_H

#include <QDialog>



namespace Ui {
class WindowTeamConstruct;
}
class QRadioButton;
class QSpinBox;
class PresetTeamForm;

class WindowTeamConstruct : public QDialog
{
    Q_OBJECT

public:
    explicit WindowTeamConstruct(bool meleeMeleeMode = true, QWidget *parent = 0);
    void memPresetTeamForm(PresetTeamForm *form);
    ~WindowTeamConstruct();
private:
    Ui::WindowTeamConstruct *ui;
    QSpinBox * m_spinNumberGames = nullptr;
    bool m_meleeMeleeMode;
    PresetTeamForm *m_presetTeamForm = nullptr;
private:
    void linkButtons();
    void linkRadio();
private slots:
    void launchGenerationWindow();
    void cancel();

};

#endif // WINDOWTEAMCONSTRUCT_H

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
