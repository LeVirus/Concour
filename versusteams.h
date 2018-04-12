#ifndef VERSUSTEAMS_H
#define VERSUSTEAMS_H

#include <QHBoxLayout>

class QVBoxLayout;
class GamesOpponentsContainer;

class VersusTeams : public QHBoxLayout
{
private:
    QVBoxLayout *m_firstTeams = nullptr, *m_secondTeams = nullptr;

    void setVersusUI(const GamesOpponentsContainer &gamesOpp);
public:
    VersusTeams(const GamesOpponentsContainer &gamesOpp, QWidget *parent = nullptr);
    ~VersusTeams();
};

#endif // VERSUSTEAMS_H
