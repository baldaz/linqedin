#ifndef GUI_UPGRADE
#define GUI_UPGRADE

#include <QDialog>
#include <QTextBrowser>
#include <QPushButton>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QGridLayout>

class Gui_Upgrade : public QDialog {
    Q_OBJECT
private:
    QTextBrowser* offers[3];
    QPushButton* select[3];
public:
    Gui_Upgrade(QWidget* parent = 0);
signals:
    void plan(int);
public slots:
    void offerSelected();
};

#endif