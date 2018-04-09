#include "form.h"
#include "ui_form.h"
#include <QMessageBox>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>

Form *Form::m_FormInstance;

Form::Form(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::Form)
{
    m_ui->setupUi(this);
    setLayouts();
    setScrolls();
    m_FormInstance = this;

    QPushButton* buttonSave = findChild<QPushButton*>("pushButton_2");
    QPushButton* buttonGenerate = findChild<QPushButton*>("pushButton_3");

    if(buttonSave)
    {
        QObject::connect(buttonSave, SIGNAL(clicked()), this, SLOT(slotSavePlayers()));
    }
    if(buttonGenerate)
    {
        QObject::connect(buttonGenerate, SIGNAL(clicked()), this, SLOT(openGenerateContestMenu()));
    }
    m_lineEdit = findChild<QLineEdit*>("lineEdit");
    m_comboBox = findChild<QComboBox*>("comboBox");
}

void Form::on_pushButton_clicked()
{
    if(m_lineEdit && m_comboBox && m_memListMan && m_memListWoman)
    {
        const QString &text = m_lineEdit->text();
        if(text == "")
        {
            QMessageBox::warning(this, "Erreur", "Le nom entré est vide.");
        }
        else if(! checkExist(text, *m_memListMan) && ! checkExist(text, *m_memListWoman))
        {
            const QString &gender = m_comboBox->currentText();
            if(gender == "Homme")
            {
                m_memListMan->addLayout(new PlayerLine(m_lineEdit->text(), true));
            }
            if(gender == "Femme")
            {
                m_memListWoman->addLayout(new PlayerLine(m_lineEdit->text(), false));
            }
        }
        else
        {
            QMessageBox::warning(this, "Erreur", "Le nom entré est déja existant.");
        }
        m_lineEdit->clear();
    }
    m_saved = false;
}

bool Form::checkExist(const QString &str, QVBoxLayout &memVbox) const
{
    for(int i = 0; i < memVbox.count(); ++i)
    {
        PlayerLine* memLine = static_cast<PlayerLine*>(memVbox.itemAt(i));
        if(memLine && memLine->getLabel()->text() == str)
        {
            return true;
        }
    }
    return false;
}

bool Form::checkGlobalExist(const QString &str) const
{
    return checkExist(str, *m_memListMan) || checkExist(str, *m_memListWoman);
}

void Form::setDataSaved(bool saved)
{
    m_saved = saved;
}

void Form::changePlayerLineGenderArray(PlayerLine *playerLine)
{
    if(! playerLine)
    {
        return;
    }
    m_saved = false;
    bool gender = playerLine->getGender();
    if(gender)//new gender :: man
    {
        m_memListWoman->removeItem(playerLine);
        m_memListMan->addLayout(playerLine);
    }
    else//new gender :: woman
    {
        m_memListMan->removeItem(playerLine);
        m_memListWoman->addLayout(playerLine);
    }
}

void Form::cleanUpPlayers()
{
    clearPlayerLines();
    if(m_lineEdit)
    {
        m_lineEdit->clear();
    }
}

void Form::insertPlayer(bool man, const QString &name)
{
    if(checkGlobalExist(name))
    {
        return;
    }
    if(man && m_memListMan)
    {
        m_memListMan->addLayout(new PlayerLine(name, true));
    }
    else
    {
        if(m_memListWoman)
        {
            m_memListWoman->addLayout(new PlayerLine(name, false));
        }
    }

}

void Form::setTeamBuildOption(unsigned int teamOption, unsigned int gamesNumber)
{
    m_contestGenWindow.setTeamBuildOption(teamOption, gamesNumber);
}

void Form::setGenerationOK(bool ok)
{
    m_okGenerate = ok;
}

void Form::setLayouts()
{
    QScrollArea *sds = findChild<QScrollArea*>("scrollArea");
    QScrollArea *sdsB = findChild<QScrollArea*>("scrollArea_2");
    m_memListMan = new QVBoxLayout(sds);
    m_memListWoman = new QVBoxLayout(sdsB);
    sds->setLayout(m_memListMan);
    sdsB->setLayout(m_memListWoman);
}

void Form::setScrolls()
{
    QWidget* wid = findChild<QScrollArea*>("scrollArea")->
            findChild<QWidget*>("scrollAreaWidgetContents");
    wid->setLayout(m_memListMan);
    wid->setMaximumWidth(300);
    QWidget* widg = findChild<QScrollArea*>("scrollArea_2")->
            findChild<QWidget*>("scrollAreaWidgetContents_4");
    widg->setLayout(m_memListWoman);
    widg->setMaximumWidth(300);
    /**SOLUTION SCROLL*/
}

void Form::getJsonFromPlayers(QJsonObject &jsonObj) const
{
    if(! jsonObj.empty())
    {
        QMessageBox::warning(m_FormInstance, "Erreur", "Erreur lors de la sauvegarde. L'objet json n'est pas vide.");
        return;
    }

    QJsonArray men, women;

    for(int i = 0; i < m_memListMan->count(); ++i)
    {
        PlayerLine* memLine = static_cast<PlayerLine*>(m_memListMan->itemAt(i));
        if(memLine)
        {
            men.insert(0, memLine->getLabel()->text());
        }
    }
    for(int i = 0; i < m_memListWoman->count(); ++i)
    {
        PlayerLine* memLine = static_cast<PlayerLine*>(m_memListWoman->itemAt(i));
        if(memLine)
        {
            women.insert(0, memLine->getLabel()->text());
        }
    }
    jsonObj.insert("Hommes", men);
    jsonObj.insert("Femmes", women);
}

void Form::closeEvent(QCloseEvent *event)
{
    if(! m_saved)
    {
        m_windowSave.exec();
        event->ignore();
    }
    else
    {
        event->accept();
    }
}

void Form::clearPlayerLines()
{
    bool first = false;
    QVBoxLayout *ptrCurrent = m_memListWoman;//begin women
    do
    {
        QLayoutItem *item = ptrCurrent->layout()->takeAt(0);
        if(item)
        {
            delete item;
        }
        else
        {
            if(!first)
            {
                first = true;
                ptrCurrent = m_memListMan;//finish men
            }
            else
            {
                break;
            }
        }
    }while(true);
}

void Form::openGenerateContestMenu()
{
    if(m_contestGenWindow.updateCurrentContest(m_memListMan, m_memListWoman))
    {
        m_windowConstruct.exec();
        if(m_okGenerate)
        {
            m_contestGenWindow.generateTeam();
            m_contestGenWindow.exec();
        }
        m_okGenerate = false;
    }
}

void Form::slotSavePlayers()
{
    QString fileName = getPathFile(this);

    QJsonObject jsonObj;
    getJsonFromPlayers(jsonObj);
    QJsonDocument doc(jsonObj);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    QFile file(fileName);
    if (file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << strJson;
        file.close();
    }
    m_saved = true;
}

QString Form::getPathFile(QWidget* ptrWidget)
{
    if(! ptrWidget)
    {
        return "";
    }
    return QFileDialog::getSaveFileName(ptrWidget,
                       tr("Save File"),
                       ".",
                                        tr("json(*.json);;All files (*)"));
}

Form::~Form()
{
    delete m_ui;
    clearPlayerLines();
    if(m_memListMan)delete m_memListMan;
    if(m_memListWoman)delete m_memListWoman;
}
