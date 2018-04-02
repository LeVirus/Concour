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
