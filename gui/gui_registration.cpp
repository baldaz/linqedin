#include "gui_registration.h"

Gui_Registration::Gui_Registration(QWidget* parent) : QWidget(parent) {
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowOpacity(0.95);
    _mainLayout = new QVBoxLayout;
    // _mainLayout->addWidget(new QLabel("REGISTRATION"), 0, Qt::AlignTop | Qt::AlignLeft);
    QPushButton* quit = new QPushButton;
    quit->setIcon(QPixmap("img/prohibited1.png"));
    connect(quit, SIGNAL(clicked()), this, SLOT(close()));
    _mainLayout->addWidget(quit, 0, Qt::AlignTop | Qt::AlignRight);
    createForm();
    _mainLayout->addWidget(_mandatory);
    _mainLayout->addWidget(_registration);
    QPushButton* confirm = new QPushButton("Confirm");
    confirm->setIcon(QPixmap("img/enter3.png"));
    _mainLayout->addWidget(confirm);
    setLayout(_mainLayout);
    move(250, 150);
    resize(900, 450);
}

void Gui_Registration::createForm() {
    _registration = new QGroupBox("Additional informations");
    _mandatory = new QGroupBox("Mandatory");
    QGridLayout* layout = new QGridLayout;
    QGridLayout* mlayout = new QGridLayout;
    QFormLayout* formus = new QFormLayout;
    QFormLayout* formsx = new QFormLayout;
    QFormLayout* formdx = new QFormLayout;
    QCalendarWidget* calendar = new QCalendarWidget;

    calendar->setStyleSheet("font-size:12px");
    calendar->setHorizontalHeaderFormat(QCalendarWidget::NoHorizontalHeader);
    calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    for(int i = 0; i < edit; ++i)
        edt[i] = new QLineEdit;
    formus->addRow("Username:", edt[0]);
    formus->addRow("Password:", edt[1]);

    formsx->addRow("Name:", edt[2]);
    formdx->addRow("Surname:", edt[3]);
    formsx->addRow("Address:", edt[4]);
    formdx->addRow("Telephon:", edt[5]);
    formsx->addRow("E-mail:", edt[6]);
    formdx->addRow("Website:", edt[7]);
    formsx->addRow("Birthdate:", calendar);
    mlayout->addLayout(formus, 0, 0, 1, 1);
    mlayout->setColumnStretch(0,1);
    mlayout->setColumnStretch(1,1);
    layout->addLayout(formsx, 1, 0, 1, 1);
    layout->addLayout(formdx, 1, 1, 1, 1);
    layout->setRowStretch(0,0);
    layout->setRowStretch(1,10);
    _mandatory->setLayout(mlayout);
    _registration->setLayout(layout);
}