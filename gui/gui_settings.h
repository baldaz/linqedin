#ifndef GUI_SETTINGS_H
#define GUI_SETTINGS_H

#include <QGridLayout>
// #include <QFormLayout>
#include <QListWidget>
#include <QPushButton>
// #include <QMessageBox>
#include <QTextEdit>
#include <QMenu>
#include <QLabel>
// #include <QCalendarWidget>
// #include <QLineEdit>
#include <QGroupBox>
#include <QFileDialog>
#include "gui_newexp.h"
#include "gui_upgrade.h"
#include "gui_avatar.h"
#include "linqclient.h"

class Gui_Settings : public QGridLayout {
    Q_OBJECT
private:
    enum {NumLineEdit = 13};
    LinqClient* _client;
    QLabel* bdate;
    QLabel* setBdate;
    QLineEdit* edtInfo[NumLineEdit];
    QTextEdit* edtBio;
    QListWidget* skills;
    QListWidget* inters;
    QListWidget* lang;
    QListWidget* exps;
    QPushButton* toggle;
    QPushButton* upg;
    Gui_NewExp* _newxp;
    Gui_Upgrade* _upop;
    QString _selected;
    QCalendarWidget* calendar;
    QString avatarPath;
    Experience xp;

    void createLists();
public:
    Gui_Settings(LinqClient*, QWidget* = 0);
signals:
    // void modified(int);
public slots:
    void refresh();
    void triggerFileDialog();
    void upgradePopup();
    void skillsMenu(const QPoint&);
    void interestsMenu(const QPoint&);
    void languagesMenu(const QPoint&);
    void experiencesMenu(const QPoint&);

    void buttonToggled();
    void addSkill();
    void deleteSkill();
    void addInterest();
    void deleteInterest();
    void addLanguage();
    void deleteLanguage();
    void addExperience();
    void deleteExperience();
    void modifyExperience();
};
#endif