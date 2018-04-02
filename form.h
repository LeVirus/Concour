#ifndef FORM_H
#define FORM_H

#include "playerline.h"
#include "windowsaveask.h"
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

private:
    bool checkExist(const QString &str, QVBoxLayout &memVbox)const;
    void setLayouts();
    void setScrolls();
    void getJsonFromPlayers(QJsonObject &jsonObj)const;
    virtual void closeEvent (QCloseEvent *event);
    QString getPathSaveFile();
public:
    explicit Form(QWidget *parent = 0);
    bool checkGlobalExist(const QString &str)const;
    void setDataSaved(bool saved);
    void changePlayerLineGenderArray(PlayerLine *playerLine);
    static inline Form *getInstance(){return m_FormInstance;}
    void cleanUpPlayers();
    ~Form();

private slots:
    void on_pushButton_clicked();
    void clearPlayerLines();
public slots:
    void slotSavePlayers();
};



#endif // FORM_H
