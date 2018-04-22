#ifndef GAMESOPPONENTSCONTAINER_H
#define GAMESOPPONENTSCONTAINER_H

#include <vector>

class Team;

using t_pairTeam = std::pair<const Team, const Team>;
using t_vectPairTeam = std::vector<t_pairTeam>;

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
