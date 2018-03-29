#include "playerline.h"
#include "modifyline.h"
#include <QPushButton>
#include <QLabel>
#include <memory>

PlayerLine::PlayerLine(const QString &labelStr)
{
    m_label = new QLabel(labelStr);
    addWidget(m_label);
    setGeometry(QRect());
    setButtons();
    linkButtons();
}

void PlayerLine::setButtons()
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

void PlayerLine::linkButtons()
{
    QObject::connect(m_del, SIGNAL(clicked()), this, SLOT(delThis()));
    QObject::connect(m_modif, SIGNAL(clicked()), this, SLOT(createModifyWindow()));
}

const QLabel *PlayerLine::getLabel()const
{
    return m_label;
}

void PlayerLine::delThis()
{
    delete this;
}

void PlayerLine::createModifyWindow()
{
//    ModifyLine m;
//    m.show();
}

PlayerLine::~PlayerLine()
{
    if(m_label)delete m_label;
    if(m_del)delete m_del;
    if(m_modif)delete m_modif;
}

