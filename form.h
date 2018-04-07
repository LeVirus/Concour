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



class Form : public QDialog
{
    Q_OBJECT
private:
    static Form* m_FormInstance;
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
    explicit Form(QWidget *parent = 0);
    bool checkGlobalExist(const QString &str)const;
    void setDataSaved(bool saved);
    void changePlayerLineGenderArray(PlayerLine *playerLine);
    void cleanUpPlayers();
    void insertPlayer(bool man, const QString &name);
    static inline Form *getInstance(){return m_FormInstance;}
    inline const QVBoxLayout* getManLayout()const{return m_memListMan;}
    inline const QVBoxLayout* getWomanLayout()const{return m_memListWoman;}
    void setTeamBuildOption(unsigned int option);
    void setGenerationOK(bool ok);
    ~Form();

private slots:
    void on_pushButton_clicked();
    void clearPlayerLines();
    void openGenerateContestMenu();
public slots:
    void slotSavePlayers();
};

#endif // FORM_H
