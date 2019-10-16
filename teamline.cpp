#include "teamline.h"
#include <QLabel>
#include <QPushButton>

TeamLine::TeamLine(const QString &playerNames)
{
    m_label = new QLabel(playerNames);
    m_label->setText(playerNames);
    addWidget(m_label);
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

}

void TeamLine::createModifyWindow()
{

}

TeamLine::~TeamLine()
{
    if(m_label)delete m_label;
    if(m_del)delete m_del;
    if(m_modif)delete m_modif;
}
