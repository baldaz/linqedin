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
#include <QCalendarWidget>
#include <QLineEdit>
#include <QGroupBox>
#include <QFileDialog>
#include "gui_modpopup.h"
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
    QListWidget* forms;
    QListWidget* jobs;
    QPushButton* toggle;
    Gui_ModPopup* _modpop;
    QString _selected;
    QCalendarWidget* calendar;
    QString avatarPath;
public:
    Gui_Settings(LinqClient*, QWidget* = 0);
signals:
    // void modified(int);
public slots:
    void triggerFileDialog();

    void skillsMenu(const QPoint&);
    void interestsMenu(const QPoint&);
    void languagesMenu(const QPoint&);
    void formationsMenu(const QPoint&);
    void jobsMenu(const QPoint&);

    void buttonToggled();
    void addSkill();
    void deleteSkill();
    void addInterest();
    void deleteInterest();
    void addLanguage();
    void deleteLanguage();
    void deleteExperience();
    void modifyExperience();

    void addFormation();
    void addJob();
};
#endif