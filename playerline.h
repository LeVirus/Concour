#ifndef PLAYERLINE_H
#define PLAYERLINE_H

#include <QHBoxLayout>
#include <memory>
#include "modifyline.h"

class QLabel;
class QPushButton;
class ModifyLine;

class PlayerLine : public QHBoxLayout
{
    Q_OBJECT
private:
    QLabel *m_label = nullptr;
    QPushButton *m_del = nullptr, *m_modif = nullptr;
    ModifyLine m_modifLineWindow;
    bool m_gender;
private:
    void setButtons();
    void linkButtons();
public:
    PlayerLine(const QString &labelStr, bool homme);
    void setLabel(const QString &label);
    void setGender(bool gender);
    const QLabel *getLabel()const;
    bool getGender()const;
    ~PlayerLine();

signals:

private slots:
    void delThis();
    void createModifyWindow();
};

#endif // PLAYERLINE_H

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
