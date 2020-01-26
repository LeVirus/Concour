#ifndef CONTESTGENERATE_H
#define CONTESTGENERATE_H

#include <QDialog>
#include <vector>
#include "team.h"
#include "gamesopponnentscontainer.h"
#include "pdfdocgeneration.h"

class QVBoxLayout;
class QLabel;
class QSpinBox;
class QTabWidget;

namespace Ui {
class ContestGenerate;
}

using vectTeam = std::vector<Team>;
using vectString = std::vector<std::string>;
using vectUi = std::vector<uint32_t>;
using vectPdfGen = std::vector<PdfDocGeneration>;
using vectGamesOpCont= std::vector<GamesOpponentsContainer>;

enum TeamGenerationMode
{
    PRESET_TEAM, MELEE_MELEE
};

class ContestGenerate : public QDialog
{
    Q_OBJECT

private:
    bool setNumberContestTeam();
    bool setNumberContestTeamForDefinedThreesome();
    bool linkWidgets();
    void setTeamsOpponentsMeleeMelee(uint32_t gameNumber);
    void setTeamsOpponentsPresetTeam(uint32_t gameNumber);
    void createNewTeamTab(uint32_t gameNumber);
    void instanciateTeams(uint32_t threesomeNumber, uint32_t doubletNumber);
    void getVectNumberTeam(vectUi &threeSome, vectUi &doublet)const;
    void generateTeamMeleeMelee();
    void generateThreePlayersTeam(vectString &men, vectString &women);
    void generateTwoPlayersTeam(vectString &men, vectString &women);
public:
    explicit ContestGenerate(QWidget *parent = 0);
    void setTeamBuildOption(uint32_t gamesNumber, TeamGenerationMode mode = MELEE_MELEE);
    void storePlayersNames();
    void displayTeams()const;
    void updateUI();
    void generateGlobalGames();
    void displayNames()const;
    bool updateCurrentContestMeleeMelee(const QVBoxLayout *manLayout, const QVBoxLayout *womanLayout);
    void updateContestPresetTeam(const std::vector<vectString> &vectTeam);
    ~ContestGenerate();
private slots:
    void pdfGeneration();
private:
#ifdef WIN32
const QString m_slash="\\";
#else
const QString m_slash = "/";
#endif
    vectGamesOpCont m_vectGamesOpContainer;
    vectTeam m_threePlayersTeam, m_twoPlayersTeam, m_vectPresetTeam;
    QLabel *m_MenTotal = nullptr, *m_WomenTotal = nullptr, *m_DoubletNumber = nullptr, *m_ThreesomeNumber = nullptr;
    QTabWidget *m_gamesTab = nullptr;
    uint32_t m_threePlayersTeamNumber, m_twoPlayersTeamNumber;
    const QVBoxLayout* m_manLayout, *m_womanLayout;
    uint32_t m_numberMan = 0, m_numberWoman = 0, m_gamesNumber = 0;
    Ui::ContestGenerate *ui;
    TeamGenerationMode m_teamBuildOption;
    vectString m_stockPlayersMen, m_stockPlayersWomen;
//    std::vector<vectString> m_vectPresetTeam;
    vectUi m_vectOddTeamNumber;
};

#endif // CONTESTGENERATE_H

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
