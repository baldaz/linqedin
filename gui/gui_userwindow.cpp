#include "gui_userwindow.h"

Gui_UserWindow::Gui_UserWindow(QWidget* parent) : QWidget(parent) {
    createHorizontalGroupBox();
    createGridGroupBox();
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(horizontalGroupBox);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(gridGroupBox);
    setLayout(mainLayout);
    move(200, 30);
    resize(1000, 700);
}

void Gui_UserWindow::createHorizontalGroupBox() {
    horizontalGroupBox = new QGroupBox();
    QHBoxLayout* layout = new QHBoxLayout;

    buttons[0] = new QPushButton("OVERVIEW");
    buttons[0]->setIcon(QPixmap("img/user91.png"));
    layout->addWidget(buttons[0]);
    connect(buttons[0], SIGNAL(clicked()), this, SLOT(overview()));

    buttons[1] = new QPushButton("SETTINGS");
    buttons[1]->setIcon(QPixmap("img/settings48.png"));
    layout->addWidget(buttons[1]);
    connect(buttons[1], SIGNAL(clicked()), this, SLOT(close()));

    buttons[2] = new QPushButton("PAYMENTS");
    buttons[2]->setIcon(QPixmap("img/banknotes.png"));
    layout->addWidget(buttons[2]);
    connect(buttons[2], SIGNAL(clicked()), this, SLOT(close()));

    buttons[3] = new QPushButton("MESSAGES");
    buttons[3]->setIcon(QPixmap("img/send4.png"));
    layout->addWidget(buttons[3]);
    connect(buttons[3], SIGNAL(clicked()), this, SLOT(close()));

    buttons[4] = new QPushButton("LOGOUT");
    buttons[4]->setIcon(QPixmap("img/logout13.png"));
    layout->addWidget(buttons[4]);
    connect(buttons[4], SIGNAL(clicked()), this, SLOT(close()));

    horizontalGroupBox->setLayout(layout);
}

void Gui_UserWindow::createGridGroupBox() {
    gridGroupBox = new QGroupBox;
    layout = new Gui_Overview;
    gridGroupBox->setLayout(layout);
}

//SLOT
void Gui_UserWindow::overview() {
    layout->refresh();
}