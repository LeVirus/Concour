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

//using vectVectString = std::vector<std::vector<std::string>>;
using vectTeam = std::vector<Team>;
using vectString = std::vector<std::string>;
using vectUi = std::vector<unsigned int>;
using vectPdfGen = std::vector<PdfDocGeneration>;
using vectGamesOpCont= std::vector<GamesOpponentsContainer>;

enum
{
    MELEE, MELEE_MELEE
};

class ContestGenerate : public QDialog
{
    Q_OBJECT

private:
#ifdef WIN32
const QString m_slash="\\";
#else
const QString m_slash = "/";
#endif
    vectGamesOpCont m_vectGamesOpContainer;
//    GamesOpponentsContainer m_gamesOpContainer;
    vectTeam m_threePlayersTeam, m_twoPlayersTeam;
    QLabel *m_MenTotal = nullptr, *m_WomenTotal = nullptr, *m_DoubletNumber = nullptr, *m_ThreesomeNumber = nullptr;
    QTabWidget *m_gamesTab = nullptr;
    unsigned int m_threePlayersTeamNumber, m_twoPlayersTeamNumber;
    const QVBoxLayout* m_manLayout, *m_womanLayout;
    unsigned int m_numberMan = 0, m_numberWoman = 0;
    Ui::ContestGenerate *ui;
    unsigned int m_teamBuildOption = MELEE, m_gamesNumber = 0;
    vectString m_stockPlayersMen, m_stockPlayersWomen;
//    vectPdfGen m_pdfGen;
private:
    bool setNumberContestTeam();
    bool setNumberContestTeamForDefinedThreesome();
    bool linkWidgets();
    void setTeamsOpponents(unsigned int gameNumber);
    void createNewTeamTab(unsigned int gameNumber);
    void instanciateTeams(unsigned int threesomeNumber, unsigned int doubletNumber);
    void getVectNumberTeam(vectUi &threeSome, vectUi &doublet)const;
public:
    explicit ContestGenerate(QWidget *parent = 0);
    void setTeamBuildOption(unsigned int gamesNumber);
    void storePlayersNames();
    void generateTeam();
    void generateThreePlayersTeam(vectString &men, vectString &women);
    void generateTwoPlayersTeam(vectString &men, vectString &women);
    void displayTeams()const;
    void updateUI();
    void generateGlobalGames();
    void generateMeleeGames();
    void displayNames()const;
    bool updateCurrentContest(const QVBoxLayout *manLayout, const QVBoxLayout *womanLayout);
    ~ContestGenerate();
private slots:
    void pdfGeneration();
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
