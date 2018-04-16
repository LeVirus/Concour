#ifndef PDFDOCGENERATION_H
#define PDFDOCGENERATION_H

#include <QString>

class GamesOpponentsContainer;

class PdfDocGeneration
{
private:
    QString m_htmlContent;
    unsigned int m_gameNumber;
    const GamesOpponentsContainer &m_gamesOpContain;
private:
    void updateDocFromGames();
    void initDocument();
    void generateDoc();
public:
    //PdfDocGeneration();
    PdfDocGeneration(const GamesOpponentsContainer &goc, unsigned int numGame);
};

#endif // PDFDOCGENERATION_H
