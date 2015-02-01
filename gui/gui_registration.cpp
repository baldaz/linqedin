#include "gui_registration.h"

Gui_Registration::Gui_Registration(QWidget* parent) : QWidget(parent) {
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowOpacity(0.95);
    _mainLayout = new QGridLayout;
    QPushButton* quit = new QPushButton;
    quit->setIcon(QPixmap("img/prohibited1.png"));
    connect(quit, SIGNAL(clicked()), this, SLOT(close()));
    _mainLayout->addWidget(quit, 0, Qt::AlignTop | Qt::AlignRight);
    createForm();
    setLayout(_mainLayout);
    move(100, 30);
    resize(900, 520);
}

void Gui_Registration::createForm() {
    QFormLayout* formsx = new QFormLayout;
    for(int i = 0; i < edit; ++i)
        edt[i] = new QLineEdit;
    formsx->addRow("Username", edt[0]);
    formsx->addRow("Password", edt[1]);
    formsx->addRow("Name:", edt[2]);
    formsx->addRow("Surname:", edt[3]);
    formsx->addRow("Address:", edt[4]);
    formsx->addRow("Telephon:", edt[5]);
    formsx->addRow("E-mail:", edt[6]);
    formsx->addRow("Website:", edt[7]);
    _mainLayout->addLayout(formsx,0,0,0,0);
}