#ifndef PLAYERLINE_H
#define PLAYERLINE_H

#include <QHBoxLayout>
#include <memory>

class QLabel;
class QPushButton;
class ModifyLine;

class PlayerLine : public QHBoxLayout
{
    Q_OBJECT
private:
    QLabel *m_label = nullptr;
    QPushButton *m_del = nullptr, *m_modif = nullptr;
    std::unique_ptr<ModifyLine> m_modifLineWindow;
    bool m_gender;
private:
    void setButtons();
    void linkButtons();

public:
    PlayerLine(const QString &labelStr, bool homme);
    const QLabel *getLabel()const;
    ~PlayerLine();

signals:

private slots:
    void delThis();
    void createModifyWindow();
};

#endif // PLAYERLINE_H
