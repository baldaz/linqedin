#ifndef GUI_UPGRADE
#define GUI_UPGRADE

#include <QDialog>
#include <QTextBrowser>
#include <QPushButton>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include "linqclient.h"

class Gui_Upgrade : public QDialog {
    Q_OBJECT
private:
    LinqClient* _client;
    QTextBrowser* offers[3];
    QPushButton* select[3];
public:
    Gui_Upgrade(LinqClient*, QWidget* parent = 0);
public slots:
    void basicSelected();
    void businessSelected();
    void executiveSelected();
};

#endif