#include "gui_bill.h"
#include <QMessageBox>
#include <QLabel>

Gui_Bill::Gui_Bill(LinqClient* cli, QWidget* parent) : QDialog(parent), _client(cli) {
    setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    setWindowOpacity(0.95);
    setStyleSheet("background:#1a1a1a");
    QVBoxLayout* _mainLayout = new QVBoxLayout;
    QFormLayout* frm = new QFormLayout;
    QPushButton* quit = new QPushButton(this);
    QPushButton* conf = new QPushButton("CONFIM", this);
    quit->setIcon(QPixmap("img/prohibited1.png"));
    connect(quit, SIGNAL(clicked()), this, SLOT(close()));
    _mainLayout->addWidget(quit, 0, Qt::AlignTop | Qt::AlignRight);
    for(int i = 0; i < 2; ++i) {
        edt[i] = new QLineEdit(this);
        edt[i]->setStyleSheet("background:#000");
    }
    frm->addRow(new QLabel("BILL INFORMATIONS"));
    frm->addRow("Nominee:", edt[0]);
    frm->addRow("Code:", edt[1]);
    frm->addRow(conf);
    connect(conf, SIGNAL(clicked()), this, SLOT(confirm()));
    _mainLayout->addLayout(frm);
    setLayout(_mainLayout);
    move(500, 200);
    resize(300, 70);
}

void Gui_Bill::setLevel(privLevel lvl) {
    _level = lvl;
}

//SLOT
void Gui_Bill::confirm() {
    string nom = edt[0]->text().toStdString();
    string cod = edt[1]->text().toStdString();
    try {
        _client->requestUpgrade(cod, nom, _level);
        QMessageBox::information(this, "Operation successful", "Account subscription change requested succesfully");
        close();
    }catch(Error e) {
        QMessageBox::critical(this, "Error occoured", QString::fromStdString(e.errorMessage()));
    }
}