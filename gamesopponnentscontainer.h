#ifndef GAMESOPPONENTSCONTAINER_H
#define GAMESOPPONENTSCONTAINER_H

#include <vector>

class Team;

using t_vectPairTeam = std::vector<std::pair<const Team&, const Team&>>;

class GamesOpponentsContainer
{
private:
    t_vectPairTeam m_gamesOpponents;
public:
    GamesOpponentsContainer();
    void clear();
    void addGames(const Team &a, const Team &b);
    const t_vectPairTeam &getGames()const;
    void display()const;
};

#endif // GAMESOPPONNENTSCONTAINER_H
