#ifndef PRESETTEAMFORM_H
#define PRESETTEAMFORM_H

#include "windowteamconstruct.h"
#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QVBoxLayout>
#include <tuple>
#include <string>

class QVBoxLayout;

using vectStr_t = std::vector<std::string>;
using itStrVect_t = std::vector<vectStr_t>::iterator;
using cstItStrVect_t = std::vector<vectStr_t>::const_iterator;

namespace Ui
{
class PresetTeamForm;
}

class PresetTeamForm : public QDialog
{
    Q_OBJECT

public:
    explicit PresetTeamForm(QWidget *parent = 0);
    bool delTeam(const std::string &playerA,
                 const std::string &playerB,
                 const std::string &playerC);
    bool addTeam(const std::string &strStdA,
                 const std::string &strStdB,
                 const std::string &strStdC);
    ~PresetTeamForm();
private:
    void linkUIElement();
    void setLayouts();
    void clearLineEdit();
    itStrVect_t findElement(const std::string &playerA,
                            const std::string &playerB,
                            const std::string &playerC);
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

public slots:
    bool checkExistingPlayers(const std::string &strA,
                              const std::string &strB,
                              const std::string &strC)const;

private:
    Ui::PresetTeamForm *ui;
    QLineEdit *playerA, *playerB, *playerC;
    std::vector<vectStr_t> m_vectPlayers;
    QVBoxLayout *m_TeamLayout;
    WindowTeamConstruct m_windowTeamConstruct;
};

void displayError(const std::string &message);
bool checkEqualsEntries(const std::string &strA,
                        const std::string &strB,
                        const std::string &strC);

#endif // PRESETTEAMFORM_H
