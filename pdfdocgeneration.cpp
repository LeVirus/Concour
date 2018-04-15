#include "pdfdocgeneration.h"
#include "gamesopponnentscontainer.h"


PdfDocGeneration::PdfDocGeneration()
{

}

PdfDocGeneration::PdfDocGeneration(const GamesOpponentsContainer &goc)
{
    updateDocFromGames(goc);
}

void PdfDocGeneration::updateDocFromGames(const GamesOpponentsContainer &goc)
{
//    const t_vectPairTeam &m_gamesOpponents = goc.getGames();
//    for(size_t i = 0; i < m_gamesOpponents.size(); ++i)
//    {
//        for(size_t k = 0; k < 2; ++k)
//        {
//            std::string mem, current;
//            size_t teamSize;
//            if(k == 0)
//            {
//                teamSize = m_gamesOpponents[i].first.getPlayerNumber();
//            }
//            else
//            {
//                teamSize = m_gamesOpponents[i].second.getPlayerNumber();
//            }
//            for(size_t j = 0; j < teamSize; ++j)
//            {
//                if(k == 0)
//                {
//                    current = m_gamesOpponents[i].first.getPlayerName(j);
//                }
//                else
//                {
//                    current = m_gamesOpponents[i].second.getPlayerName(j);
//                }

//                if(current.empty())
//                {
//                    continue;
//                }
//                if(j != 0)
//                {
//                    mem += '\n';
//                }
//                mem += current;
//            }
//            if(k == 0)
//            {
//                m_firstTeams->addWidget(new QLabel(mem.c_str()));
//            }
//            else
//            {
//                m_secondTeams->addWidget(new QLabel(mem.c_str()));
//            }
//        }
//    }
}



