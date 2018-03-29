#ifndef PLAYERLINE_H
#define PLAYERLINE_H

#include <QHBoxLayout>

class QLabel;
class QPushButton;

class PlayerLine : public QHBoxLayout
{
    Q_OBJECT
private:
    QLabel *m_label = nullptr;
    QPushButton *m_del = nullptr, *m_modif = nullptr;
    void setButtons();
public:
    PlayerLine(const QString &labelStr);
    const QLabel *getLabel()const;
    ~PlayerLine();

signals:

public slots:
};

#endif // PLAYERLINE_H
