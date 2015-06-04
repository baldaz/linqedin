#ifndef GUI_UPGRADE_H
#define GUI_UPGRADE_H

#include <QDialog>
#include <QTextBrowser>
#include <QPushButton>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include "linqclient.h"
#include "gui_bill.h"

class Gui_Upgrade : public QDialog {
    Q_OBJECT
private:
    LinqClient* _client;
    Gui_Bill* _bill;
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