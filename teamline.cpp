#include "teamline.h"
#include "presetteamform.h"
#include <QLabel>
#include <QPushButton>
#include <QScrollBar>
#include <cassert>

TeamLine::TeamLine(PresetTeamForm &memPresetTeamForm,
                   const std::string &playerA,
                   const std::string &playerB,
                   const std::string &playerC):
    m_memPresetTeamForm(memPresetTeamForm),
    m_playerA(playerA),
    m_playerB(playerB),
    m_playerC(playerC)
{
    m_label = new QLabel(QString(m_playerA.c_str()) + "\n" + QString(m_playerB.c_str()) +
                         "\n" + QString(m_playerC.c_str()));
    m_scroll.setWidget(m_label);
    m_scroll.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    addWidget(&m_scroll);
    setButtons();
    linkButtons();
}


void TeamLine::setButtons()
{
    m_del = new QPushButton();
    m_del->setIcon(QIcon("../Concour/Icon/del.png"));
    m_del->setFixedWidth(40);
    m_modif = new QPushButton();
    m_modif->setIcon(QIcon("../Concour/Icon/edit.png"));
    m_modif->setFixedWidth(40);
    addWidget(m_modif);
    addWidget(m_del);
}

void TeamLine::linkButtons()
{
    QObject::connect(m_del, SIGNAL(clicked()), this, SLOT(delThis()));
    QObject::connect(m_modif, SIGNAL(clicked()), this, SLOT(createModifyWindow()));
}

void TeamLine::delThis()
{
    bool ok = m_memPresetTeamForm.delTeam(m_playerA, m_playerB, m_playerC);
    assert(ok && "Error incoherent players array.");
    delete this;
}

void TeamLine::createModifyWindow()
{
    m_memPresetTeamForm.exec();
}

TeamLine::~TeamLine()
{
    if(m_label)delete m_label;
    if(m_del)delete m_del;
    if(m_modif)delete m_modif;
}
