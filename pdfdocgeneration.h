#ifndef PDFDOCGENERATION_H
#define PDFDOCGENERATION_H

#include <QString>
#include <vector>

class Team;
using t_pairTeam = std::pair<const Team&, const Team&>;
using t_vectPairTeam = std::vector<t_pairTeam>;

class GamesOpponentsContainer;

class PdfDocGeneration
{
private:
    QString m_htmlContent;
    unsigned int m_gameNumber;
    const GamesOpponentsContainer &m_gamesOpContain;
private:
    void updateDocFromGames(const GamesOpponentsContainer &goc);
    void initDocument();
    void createVersusTableTeams(const t_pairTeam *versusA, const t_pairTeam *versusB);
    void createVersusLineTeams(const t_pairTeam *versusA, const t_pairTeam *versusB, unsigned int lineNumber);
    void generateDoc();
public:
    //PdfDocGeneration();
    PdfDocGeneration(const GamesOpponentsContainer &goc, unsigned int numGame);
};

#endif // PDFDOCGENERATION_H
