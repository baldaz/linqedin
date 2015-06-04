#include "gui_upgrade.h"

Gui_Upgrade::Gui_Upgrade(LinqClient* cli, QWidget* parent) : QDialog(parent), _client(cli) {
    setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    setWindowOpacity(0.95);
    _bill = new Gui_Bill(_client);
    QVBoxLayout* _mainLayout = new QVBoxLayout;
    QPushButton* quit = new QPushButton;
    quit->setIcon(QPixmap("img/prohibited1.png"));
    connect(quit, SIGNAL(clicked()), this, SLOT(close()));
    _mainLayout->addWidget(quit, 0, Qt::AlignTop | Qt::AlignRight);
    QGridLayout* layout = new QGridLayout;
    for(int i = 0; i < 3; ++i) {
        offers[i] = new QTextBrowser(this);
        offers[i]->setStyleSheet("background:transparent");
        select[i] = new QPushButton(this);
        layout->addWidget(offers[i], 1, i, 1, 1);
        layout->addWidget(select[i], 2, i, 1, 1);
    }
    layout->setRowStretch(1, 10);
    layout->setRowStretch(2, 1);
    layout->setSpacing(5);
    if(_client->level() == basic) {
        offers[0]->setStyleSheet("background:#1a1a1a");
        select[0]->setEnabled(false);
        select[0]->setStyleSheet("color:#1a1a1a");
    }
    else if(_client->level() == business) {
        offers[1]->setStyleSheet("background:#1a1a1a");
        select[1]->setEnabled(false);
        select[1]->setStyleSheet("color:#1a1a1a");
    }
    else if(_client->level() == executive) {
        offers[2]->setStyleSheet("background:#1a1a1a");
        select[2]->setEnabled(false);
        select[2]->setStyleSheet("color:#1a1a1a");
    }
    offers[0]->setHtml("<h3>BASIC</h3><h4>Offer</h4><ul style='font-weight:400'><li>Basic search(display only name if user exists)</li><li>10 in mail / month</li><li>Visit counter</li></ul><p>" + QString::number(Subscription::levelAmount(basic)) + "€ / month</p>");
    offers[1]->setHtml("<h3>BUSINESS</h3><h4>Offer</h4><ul style='font-weight:400'><li>Business search (display full profile if user exists)</li><li>Similiar users suggestions</li><li>25 in mail / month</li><li>Groups guest, with posting rights</li><li>Visit counter</li></ul><p>" + QString::number(Subscription::levelAmount(business)) + " € / month</p>");
    offers[2]->setHtml("<h3>EXECUTIVE</h3><h4>Offer</h4><ul style='font-weight:400'><li>Executive search (display full profile and his network connections if user exists)</li><li>Smart search, parameter search</li><li>Similiar users suggestions</li><li>Keyword frequency used to find your profile by others.</li><li>Unlimited in mail / month</li><li>Groups guest, with posting rights + Creation rights and administration of personal groups</li><li>Visit counter + last 10 visitors</li></ul><p>" + QString::number(Subscription::levelAmount(executive)) + " € / month</p>");
    select[0]->setText("BASIC");
    select[1]->setText("BUSINESS");
    select[2]->setText("EXECUTIVE");
    connect(select[0], SIGNAL(clicked()), this, SLOT(basicSelected()));
    connect(select[1], SIGNAL(clicked()), this, SLOT(businessSelected()));
    connect(select[2], SIGNAL(clicked()), this, SLOT(executiveSelected()));
    _mainLayout->addLayout(layout);
    setLayout(_mainLayout);
    move(400, 30);
    resize(600, 700);
}

//SLOT
void Gui_Upgrade::basicSelected() {
    try {
        _client->requestUpgrade("N/A", "N/A", basic);
        QMessageBox::information(this, "Operation successful", "Account subscription change requested succesfully");
        close();
    }catch(Error e) {
        QMessageBox::critical(this, "Error occoured", QString::fromStdString(e.errorMessage()));
    }
}

//SLOT
void Gui_Upgrade::businessSelected() {
    _bill->setLevel(business);
    _bill->show();
}

//SLOT
void Gui_Upgrade::executiveSelected() {
    _bill->setLevel(executive);
    _bill->show();
}