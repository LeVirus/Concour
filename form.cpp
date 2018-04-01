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
    QWidget(parent),
    m_ui(new Ui::Form)
{
    m_ui->setupUi(this);
    setLayouts();
    setScrolls();
    m_FormInstance = this;

    QPushButton* buttonSave = findChild<QPushButton*>("pushButton_2");
    if(buttonSave)
    {
        QObject::connect(buttonSave, SIGNAL(clicked()), this, SLOT(slotSavePlayers()));
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
        m_windowSave.show();
        m_windowSave.activateWindow();
        event->ignore();
    }
    else
    {
        event->accept();
    }
}

void Form::clearPlayerLines()
{
    for(int i = 0; i < m_memListWoman->count(); ++i)
    {
        delete m_memListWoman->itemAt(i);
    }
    for(int i = 0; i < m_memListMan->count(); ++i)
    {
        delete m_memListMan->itemAt(i);
    }
}

void Form::slotSavePlayers()
{
    QFileDialog dialog;
    dialog.setDefaultSuffix("json");//doesn't work
    QString fileName = dialog.getSaveFileName(this,
                       tr("Save File"),
                       ".",
                       tr("json(*.json);;All files (*)"));
    QJsonObject jsonObj;
    getJsonFromPlayers(jsonObj);
    QJsonDocument doc(jsonObj);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    QFile file(fileName);
    if (file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        stream << strJson;
    }
    m_saved = true;
}

Form::~Form()
{
    delete m_ui;
    clearPlayerLines();
    if(m_memListMan)delete m_memListMan;
    if(m_memListWoman)delete m_memListWoman;
}
