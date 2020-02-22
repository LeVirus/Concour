#include "pdfdocgeneration.h"
#include "team.h"
#include "gamesopponnentscontainer.h"
#include <QtWidgets>
#include <QPrinter>

QString PdfDocGeneration::m_htmlContent;
QString PdfDocGeneration::m_saveDir;
unsigned int PdfDocGeneration::m_gameNumber;
uint32_t PdfDocGeneration::m_groundNumber;

void PdfDocGeneration::updateDocFromGames(const GamesOpponentsContainer &goc, unsigned int numGame)
{
    m_htmlContent.clear();
    m_gameNumber = numGame;
    m_groundNumber = 0;
    initDocument();

    const t_vectPairTeam &m_gamesOpponents = goc.getGames();
    for(size_t i = 0; i < m_gamesOpponents.size(); i += 2)
    {
        m_htmlContent.append("<br>");
        if(i + 1 >= m_gamesOpponents.size())
        {
            createVersusTableTeams(&m_gamesOpponents[i], nullptr);
        }
        else
        {
            createVersusTableTeams(&m_gamesOpponents[i], &m_gamesOpponents[i + 1]);
        }
    }
    m_htmlContent.append("</body></html>");
    generateDoc();

}

void PdfDocGeneration::setSaveDirectory(const QString &path)
{
    m_saveDir = path;
}

void PdfDocGeneration::initDocument()
{
    m_htmlContent.clear();
    m_htmlContent.append("<!DOCTYPE html>");
    m_htmlContent.append("<html><head><style>");
    m_htmlContent.append("td{font-size: 20px;}");
    m_htmlContent.append("table{border-style:solid; border-width:1px; border-color:black;}");
    m_htmlContent.append("</style></head>");
    m_htmlContent.append("<body><h1 style='text-align: center;'>Manche "
                         + QString::number(m_gameNumber) + "</h1>");
}

void PdfDocGeneration::createGroundNumberLine()
{
    m_htmlContent.append("<tr><td></td>");
    m_htmlContent.append("<td colspan = 2 style='height: 18px;'><strong>Terrain " +
                         QString::number(++m_groundNumber) +
                         "</strong></td>");
    m_htmlContent.append("<td></td>");
    m_htmlContent.append("<td colspan = 2 style='height: 18px;'><strong>Terrain " +
                         QString::number(++m_groundNumber) +
                         "</strong></td></tr>");
}

void PdfDocGeneration::createVersusTableTeams(const t_pairTeam *versusA, const t_pairTeam *versusB)
{
    if(versusB)
    {
        m_htmlContent.append("<table style='text-align: center;'align='left'>");
    }
    else
    {
        m_htmlContent.append("<table style='text-align: center;'align='left'>");
    }
    createGroundNumberLine();
    m_htmlContent.append("<tr><td></td>");//set first case empty
    m_htmlContent.append("<td style='height: 18px;'><strong>Equipe " +
                         QString::number(versusA->first.getTeamNumber() + 1) +
                         "</strong></td>");

    m_htmlContent.append("<td style='height: 18px;'><strong>Equipe " +
                         QString::number(versusA->second.getTeamNumber() + 1) +
                         "</strong></td>");
    m_htmlContent.append("<td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>");//set middle case empty

    if(versusB)
    {
        m_htmlContent.append("<td style='height: 18px;'><strong>Equipe " +
                             QString::number(versusB->first.getTeamNumber() + 1) +
                             "</strong></td>");
    }
    else
    {
        m_htmlContent.append("<td></td>");
    }

    if(versusB)
    {
        m_htmlContent.append("<td style='height: 18px;'><strong>Equipe " +
                             QString::number(versusB->second.getTeamNumber() + 1) +
                             "</strong></td>");
    }
    else
    {
        m_htmlContent.append("<td></td>");
    }
    m_htmlContent.append("</tr>");

    for(size_t i = 0; i < 3; ++i)
    {
        createVersusLineTeams(versusA, versusB, i);
    }
    m_htmlContent.append("</table>");
}

void PdfDocGeneration::createVersusLineTeams(const t_pairTeam *versusA, const t_pairTeam *versusB, unsigned int lineNumber)
{
    m_htmlContent.append("<tr><td><strong>Joueur " + QString::number(lineNumber + 1) + "</strong></td>");
    m_htmlContent.append("<td style='height: 18px;'>" + QString(versusA->first.getPlayerName(lineNumber).c_str()) + "</td>");

    m_htmlContent.append("<td style='height: 18px;'>" + QString(versusA->second.getPlayerName(lineNumber).c_str()) + "</td>");
    m_htmlContent.append("<td></td>");//set middle case empty

    if(versusB)
    {
        m_htmlContent.append("<td style='height: 18px;'>" + QString(versusB->first.getPlayerName(lineNumber).c_str()) + "</td>");
    }
    else
    {
        m_htmlContent.append("<td></td>");
    }

    if(versusB)
    {
        m_htmlContent.append("<td style='height: 18px;'>" + QString(versusB->second.getPlayerName(lineNumber).c_str()) + "</td>");
    }
    else
    {
        m_htmlContent.append("<td></td>");
    }
    m_htmlContent.append("</tr>");
}

void PdfDocGeneration::generateDoc()
{

    QString fileName = m_saveDir + "doc" + QString::number(m_gameNumber) + ".pdf";
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setPageOrientation(QPageLayout::Landscape);
    printer.setOutputFileName(fileName);
    QTextDocument doc;
    doc.setHtml(m_htmlContent);
    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    doc.print(&printer);
}

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
