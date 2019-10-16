#ifndef FORM_H
#define FORM_H

#include "playerline.h"
#include "contestgenerate.h"
#include "windowsaveask.h"
#include "windowteamconstruct.h"
#include <QCloseEvent>
#include <QJsonObject>
#include <QDialog>
#include <memory>

class QVBoxLayout;
class QLineEdit;
class QComboBox;

namespace Ui {
class Form;
}



class MeleeMeleeForm : public QDialog
{
    Q_OBJECT
private:
    static MeleeMeleeForm* m_FormInstance;
    Ui::Form *m_ui;
    QVBoxLayout* m_memListMan = nullptr;
    QVBoxLayout* m_memListWoman = nullptr;
    QLineEdit* m_lineEdit = nullptr;
    QComboBox* m_comboBox = nullptr;
    bool m_saved = true;
    WindowSaveAsk m_windowSave;
    ContestGenerate m_contestGenWindow;
    WindowTeamConstruct m_windowConstruct;
    bool m_okGenerate = false;
private:
    bool checkExist(const QString &str, QVBoxLayout &memVbox)const;
    void setLayouts();
    void setScrolls();
    void getJsonFromPlayers(QJsonObject &jsonObj)const;
    virtual void closeEvent (QCloseEvent *event);
    QString getPathFile(QWidget *ptrWidget);
public:
    explicit MeleeMeleeForm(QWidget *parent = 0);
    bool checkGlobalExist(const QString &str)const;
    void setDataSaved(bool saved);
    void changePlayerLineGenderArray(PlayerLine *playerLine);
    void cleanUpPlayers();
    void insertPlayer(bool man, const QString &name);
    static inline MeleeMeleeForm *getInstance(){return m_FormInstance;}
    inline const QVBoxLayout* getManLayout()const{return m_memListMan;}
    inline const QVBoxLayout* getWomanLayout()const{return m_memListWoman;}
    void setTeamBuildOption(unsigned int teamOption, unsigned int gamesNumber);
    void setGenerationOK(bool ok);
    ~MeleeMeleeForm();
private slots:
    void on_pushButton_clicked();
    void clearPlayerLines();
    void openGenerateContestMenu();
public slots:
    void slotSavePlayers();
};

#endif // FORM_H

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
