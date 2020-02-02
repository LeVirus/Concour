#ifndef VERSUSTEAMS_H
#define VERSUSTEAMS_H

#include <QHBoxLayout>

class QVBoxLayout;
class GamesOpponentsContainer;

class VersusTeams : public QHBoxLayout
{
private:
    QVBoxLayout *m_firstTeams = nullptr, *m_secondTeams = nullptr;
private:
    void setVersusUI(const GamesOpponentsContainer &gamesOpp);
public:
    VersusTeams(const GamesOpponentsContainer &gamesOpp, QWidget *parent = nullptr);
    ~VersusTeams();
};

#endif // VERSUSTEAMS_H

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
