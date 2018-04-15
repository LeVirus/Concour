#ifndef PDFDOCGENERATION_H
#define PDFDOCGENERATION_H

#include <QString>

class GamesOpponentsContainer;

class PdfDocGeneration
{
private:
    QString m_htmlContent;
private:
    void updateDocFromGames(const GamesOpponentsContainer &goc);
public:
    PdfDocGeneration();
    PdfDocGeneration(const GamesOpponentsContainer &goc);
};

#endif // PDFDOCGENERATION_H
