#include "pdfdocgeneration.h"
#include "gamesopponnentscontainer.h"
#include <QtWidgets>
#include <QPrinter>

//PdfDocGeneration::PdfDocGeneration()
//{

//}

PdfDocGeneration::PdfDocGeneration(const GamesOpponentsContainer &goc, unsigned int numGame):m_gamesOpContain(goc),
    m_gameNumber(numGame)
{
    updateDocFromGames();
}

void PdfDocGeneration::updateDocFromGames()
{
    initDocument();
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

void PdfDocGeneration::initDocument()
{
    m_htmlContent.clear();
    m_htmlContent.append("<h1 style='text-align: center;'>Manche ");
    m_htmlContent.append(QString::number(m_gameNumber));
    m_htmlContent.append("</h1>");
    generateDoc();
}

void PdfDocGeneration::generateDoc()
{
    QString fileName = "doc.pdf";/*QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }*/

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
//    doc.setHtml("<h1>Hello, World!</h1>\n<p>Lorem ipsum dolor sit amet, consectitur adipisci elit.</p>");
    doc.setHtml(m_htmlContent);
    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    doc.print(&printer);
}



