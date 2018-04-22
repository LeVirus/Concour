#ifndef MODIFYLINE_H
#define MODIFYLINE_H

#include <QDialog>

class PlayerLine;
class QAbstractButton;
class QComboBox;
class QLineEdit;

enum{
    HOMME, FEMME
};
namespace Ui {
class ModifyLine;
}

class ModifyLine : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyLine(QWidget *parent = 0);
    void setParams(const QString &nom, bool homme, PlayerLine *refPlayerLine);
    ~ModifyLine();
signals:

private slots:
    void clickedOk();
    void clickedCancel();

private:
    Ui::ModifyLine *ui;
    PlayerLine *m_memPlayerLine = nullptr;
    QComboBox* m_comboBox = nullptr;
    QLineEdit* m_lineEdit = nullptr;
    QString m_PreviousLabelValue;
private:
    void changeArrayLine();
    bool modifyPlayerLineLabel();
    void modifyPlayerLineGender();
    virtual void keyPressEvent(QKeyEvent *e);
};

#endif // MODIFYLINE_H

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
