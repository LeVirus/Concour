#ifndef PDFDOCGENERATION_H
#define PDFDOCGENERATION_H

#include <QString>
#include <vector>

class Team;
using t_pairTeam = std::pair<const Team, const Team>;
using t_vectPairTeam = std::vector<t_pairTeam>;

class GamesOpponentsContainer;

class PdfDocGeneration
{
private:
    static QString m_htmlContent, m_saveDir;
    static unsigned int m_gameNumber;
//    const GamesOpponentsContainer &m_gamesOpContain;
private:
    static void initDocument();
    static void createVersusTableTeams(const t_pairTeam *versusA, const t_pairTeam *versusB);
    static void createVersusLineTeams(const t_pairTeam *versusA, const t_pairTeam *versusB, unsigned int lineNumber);
    static void generateDoc();
public:
    static void updateDocFromGames(const GamesOpponentsContainer &goc, unsigned int numGame);
    static void setSaveDirectory(const QString &path);
    //    PdfDocGeneration(const GamesOpponentsContainer &goc, unsigned int numGame);
};

#endif // PDFDOCGENERATION_H
