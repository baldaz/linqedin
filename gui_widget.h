#ifndef GUI_WIDGET_H
#define GUI_WIDGET_H

#include <QApplication>
#include <QFont>
#include <QPushButton>
#include <QWidget>
#include <QGroupBox>
#include <QTextEdit>
#include <QTextBrowser>
#include <QLabel>
#include <QLineEdit>
#include <QAction>
#include <QGridLayout>
#include <QMenu>
#include <QMenuBar>
#include "linqclient.h"

class Gui_Widget : public QWidget {
    Q_OBJECT
public:
    Gui_Widget();
    public slots:
    void insertContatto();
    void removeContatto();
    void mostraProfilo();
    void viewNet();
    void userSearch();
private:
    // campo dati logico
    LinqClient* user;
    // inizializzazione logica
    void logicInitialize();

    // Componenti grafiche di Gui_Widget
    QGroupBox* horizontalGroupBox;
    QGroupBox* gridGroupBox;
    QTextEdit* smallEditor;
    QTextEdit* bigEditor;
    enum { NumGridRows = 2, NumButtons = 6 };
    QLabel* labels[NumGridRows];
    QLabel* portrait;
    QLineEdit* lineEdits[NumGridRows];
    QPushButton* buttons[NumButtons];

    // metodi privati di set-up di Gui_Widget
    void createHorizontalGroupBox();
    void createGridGroupBox();
};

#endif