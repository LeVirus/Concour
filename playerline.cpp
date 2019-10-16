#include "playerline.h"
#include "meleemeleeform.h"
#include <QPushButton>
#include <QLabel>
#include <memory>

PlayerLine::PlayerLine(const QString &labelStr, bool homme)
{
    m_gender = homme;
    m_label = new QLabel(labelStr);
    addWidget(m_label);
    setGeometry(QRect());
    setButtons();
    linkButtons();
}

void PlayerLine::setLabel(const QString &label)
{
    m_label->setText(label);
}

void PlayerLine::setGender(bool gender)
{
    m_gender = gender;
}

void PlayerLine::setButtons()
{
    QString pathDel;
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

bool PlayerLine::getGender() const
{
    return m_gender;
}

void PlayerLine::delThis()
{
    MeleeMeleeForm* form = MeleeMeleeForm::getInstance();
    if(form)
    {
        form->setDataSaved(false);
    }
    delete this;
}

void PlayerLine::createModifyWindow()
{
        m_modifLineWindow.setParams(m_label->text(), m_gender, this);
        m_modifLineWindow.exec();
}

PlayerLine::~PlayerLine()
{
    if(m_label)delete m_label;
    if(m_del)delete m_del;
    if(m_modif)delete m_modif;
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
