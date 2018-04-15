#ifndef CONTESTGENERATE_H
#define CONTESTGENERATE_H

#include <QDialog>
#include <vector>
#include "team.h"
#include "gamesopponnentscontainer.h"

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

enum
{
    MELEE, MELEE_MELEE
};

class ContestGenerate : public QDialog
{
    Q_OBJECT

private:
    GamesOpponentsContainer m_gamesOpContainer;
    vectTeam m_threePlayersTeam, m_twoPlayersTeam;
    QLabel *m_MenTotal = nullptr, *m_WomenTotal = nullptr, *m_DoubletNumber = nullptr, *m_ThreesomeNumber = nullptr;
    QTabWidget *m_gamesTab = nullptr;
    unsigned int m_threePlayersTeamNumber, m_twoPlayersTeamNumber;
    const QVBoxLayout* m_manLayout, *m_womanLayout;
    unsigned int m_numberMan = 0, m_numberWoman = 0;
    Ui::ContestGenerate *ui;
    unsigned int m_teamBuildOption = MELEE, m_gamesNumber = 0;
    vectString m_stockPlayersMen, m_stockPlayersWomen;
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
    void setTeamBuildOption(unsigned int option, unsigned int gamesNumber);
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
};

#endif // CONTESTGENERATE_H
