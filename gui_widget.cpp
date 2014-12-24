#include "gui_widget.h"

Gui_Widget::Gui_Widget() {
    createHorizontalGroupBox();
    createGridGroupBox();
    bigEditor = new QTextEdit();

    // Layout principale della dialog
    QVBoxLayout* mainLayout = new QVBoxLayout;
    // crea menu
    QMenuBar* menuBar = new QMenuBar(0);
    QMenu* fileMenu = menuBar->addMenu(tr("File"));
    fileMenu->addAction(tr("Open..."));
    fileMenu->addAction(tr("Close..."));
    fileMenu->addSeparator();
    QAction* exitAction = fileMenu->addAction(tr("Close LinkedIn"));
    QMenu* viewMenu = menuBar->addMenu(tr("&View"));
    QAction* fullScreenAction = viewMenu->addAction(tr("Full screen"));
    QAction* normalViewAction = viewMenu->addAction(tr("Normal view"));
    QMenu* helpMenu = new QMenu(tr("&Help"));
    menuBar->addMenu(helpMenu);

    // connessione signal-slot
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(fullScreenAction, SIGNAL(triggered()), this, SLOT(showFullScreen()));
    connect(normalViewAction, SIGNAL(triggered()), this, SLOT(showNormal()));


    mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(horizontalGroupBox);
    mainLayout->addWidget(gridGroupBox);
    mainLayout->addWidget(bigEditor);
    setLayout(mainLayout);
    logicInitialize();
}

void Gui_Widget::createGridGroupBox() {
    gridGroupBox = new QGroupBox;
    QGridLayout* layout = new QGridLayout;

    for (int i = 0; i < NumGridRows-1; ++i) {
    labels[i] = new QLabel(tr("Line %1:").arg(i + 1));
    lineEdits[i] = new QLineEdit;
    layout->addWidget(labels[i], i + 1, 0);
    layout->addWidget(lineEdits[i], i + 1, 1);
    }

    labels[NumGridRows-1] = new QLabel();
    lineEdits[NumGridRows-1] = new QLineEdit;
    layout->addWidget(labels[NumGridRows-1], NumGridRows, 0);
    layout->addWidget(lineEdits[NumGridRows-1], NumGridRows, 1);

    smallEditor = new QTextEdit;
    QFont font = smallEditor->font();
    font.setPointSize(font.pointSize() + 8);
    smallEditor->setFont(font);





    layout->addWidget(smallEditor, 0, 2, 4, 1);
    layout->setColumnStretch(1, 10);
    layout->setColumnStretch(2, 20);
    gridGroupBox->setLayout(layout);
}

void Gui_Widget::logicInitialize() {
    Username* usr = new Username("Baldaz", "password");
    user = new LinqClient(usr);
}

// slot
void Gui_Widget::insertContatto() {
    // user->insertRete(Username(""));
    smallEditor->setText(tr("Inserito nuovo contatto"));
}

// slot
void Gui_Widget::removeContatto() {
    // user->removeRete(Username(""));
    smallEditor->setText(tr("Contatto rimosso"));
}

// slot
void Gui_Widget::mostraProfilo() {
    user->displayProfile();
    bigEditor->setText(tr("Il mio profilo"));
}

void Gui_Widget::createHorizontalGroupBox() {
    horizontalGroupBox = new QGroupBox();
    QHBoxLayout* layout = new QHBoxLayout;

    buttons[0] = new QPushButton("Inserisci nuovo contatto nella rete");
    layout->addWidget(buttons[0]);
    connect(buttons[0], SIGNAL(clicked()), this, SLOT(insertContatto()));

    buttons[1] = new QPushButton("Rimuovi contatto dalla rete");
    layout->addWidget(buttons[1]);
    connect(buttons[1], SIGNAL(clicked()),this, SLOT(removeContatto()));

    buttons[2] = new QPushButton("Mostra il mio profilo");
    layout->addWidget(buttons[2]);
    connect(buttons[2], SIGNAL(clicked()),this, SLOT( mostraProfilo() ));

    horizontalGroupBox->setLayout(layout);
}