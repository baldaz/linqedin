#ifndef GUI_SETTINGS_H
#define GUI_SETTINGS_H

#include <QGridLayout>
#include <QFormLayout>
#include <QListWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QTextEdit>
#include <QMenu>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include "gui_avatar.h"
#include "linqclient.h"

class Gui_Settings : public QGridLayout {
    Q_OBJECT
private:
    enum {NumLineEdit = 13};
    LinqClient* _client;
    QLineEdit* edtInfo[NumLineEdit];
    QTextEdit* edtBio;
    QListWidget* skills;
    QListWidget* inters;
    QListWidget* lang;
    QPushButton* toggle;
    QString _selected;
public:
    Gui_Settings(LinqClient*, QWidget* = 0);
public slots:
    void skillsMenu(const QPoint&);
    void interestsMenu(const QPoint&);
    void languagesMenu(const QPoint&);
    void buttonToggled();
    void addSkill();
    void deleteSkill();
    void modifySkill();
    void addInterest();
    void deleteInterest();
    void modifyInterest();
    void addLanguage();
    void deleteLanguage();
    void modifyLanguage();
};
#endif