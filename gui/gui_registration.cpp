#include "gui_registration.h"

Gui_Registration::Gui_Registration(QWidget* parent) : QWidget(parent) {
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowOpacity(0.95);
    _admin = new LinqAdmin;
    _mainLayout = new QVBoxLayout;
    QPushButton* quit = new QPushButton;
    quit->setIcon(QPixmap("img/prohibited1.png"));
    connect(quit, SIGNAL(clicked()), this, SLOT(close()));
    _mainLayout->addWidget(quit, 0, Qt::AlignTop | Qt::AlignRight);
    _mainLayout->addWidget(new QLabel("REGISTRATION"), 0, Qt::AlignTop | Qt::AlignCenter);
    createForm();
    _mainLayout->addWidget(_mandatory);
    _mainLayout->addWidget(_registration);
    _mandatory->setStyleSheet(QStringLiteral("QGroupBox::title{subcontrol-origin: margin;top:-1px;left: 6px;}QGroupBox {padding: 10px;margin-top: 8px;border-style: solid;border-width:1px;border-color: #fff;border-radius:15px;}"));
    _registration->setStyleSheet(QStringLiteral("QGroupBox::title{subcontrol-origin: margin;top:-1px;left: 6px;}QGroupBox {padding: 10px;margin-top: 8px;border-style: solid;border-width:1px;border-color: #fff;border-radius:15px;}"));
    QPushButton* confirm = new QPushButton("Confirm");
    confirm->setIcon(QPixmap("img/enter3.png"));
    _mainLayout->addWidget(confirm);
    connect(confirm, SIGNAL(clicked()), this, SLOT(submitData()));
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
    calendar = new QCalendarWidget;
    bio = new QTextEdit;
    bio->setStyleSheet("background:#1a1a1a; font-weight:400;");

    calendar->setStyleSheet("font-size:12px");
    calendar->setHorizontalHeaderFormat(QCalendarWidget::NoHorizontalHeader);
    calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    for(int i = 0; i < edit; ++i)
        edt[i] = new QLineEdit;
    edt[1]->setEchoMode(QLineEdit::Password);
    formus->addRow("Username:", edt[0]);
    formus->addRow("Password:", edt[1]);

    formsx->addRow("Name:", edt[2]);
    formdx->addRow("Surname:", edt[3]);
    formsx->addRow("Address:", edt[4]);
    formdx->addRow("Telephone:", edt[5]);
    formsx->addRow("E-mail:", edt[6]);
    formdx->addRow("Website:", edt[7]);
    formsx->addRow("Birthdate:", calendar);
    formdx->addRow("Short bio:", bio);
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

//SLOT
void Gui_Registration::submitData() {
    QString uname = edt[0]->text();
    QString pass = edt[1]->text();
    QMap<string, string> info;
    info.insert("name", edt[2]->text().toStdString());
    info.insert("surname", edt[3]->text().toStdString());
    info.insert("address", edt[4]->text().toStdString());
    info.insert("telephone", edt[5]->text().toStdString());
    info.insert("e-mail", edt[6]->text().toStdString());
    info.insert("website", edt[7]->text().toStdString());
    info.insert("birthdate", calendar->selectedDate().toString("dd.MM.yyyy").toStdString());
    info.insert("bio", bio->toPlainText().toStdString());
    _admin->insertUser(uname.toStdString(), pass.toStdString(), info.toStdMap());
}