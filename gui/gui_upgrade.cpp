#include "gui_upgrade.h"

Gui_Upgrade::Gui_Upgrade(QWidget* parent) : QDialog(parent) {
    setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    setWindowOpacity(0.95);
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
    offers[0]->setHtml("<h3>BASIC</h3><h4>Offer</h4><ul style='font-weight:400'><li>Basic search(display only name if user exists)</li><li>10 in mail / month</li><li>Visit counter</li></ul><p>0.00 € / month</p>");
    offers[1]->setHtml("<h3>BUSINESS</h3><h4>Offer</h4><ul style='font-weight:400'><li>Business search (display full profile if user exists)</li><li>Similiar users suggestions</li><li>25 in mail / month</li><li>Groups guest, with posting rights</li><li>Visit counter</li></ul><p>29.90 € / month</p>");
    offers[2]->setHtml("<h3>EXECUTIVE</h3><h4>Offer</h4><ul style='font-weight:400'><li>Executive search (display full profile and his network connections if user exists)</li><li>Smart search, parameter search</li><li>Similiar users suggestions</li><li>Keyword frequency used to find your profile by others.</li><li>Unlimited in mail / month</li><li>Groups guest, with posting rights + Creation rights and administration of personal groups</li><li>Visit counter + last 10 visitors</li></ul><p>49.90 € / month</p>");
    select[0]->setText("BASIC");
    select[1]->setText("BUSINESS");
    select[2]->setText("EXECUTIVE");
    _mainLayout->addLayout(layout);
    setLayout(_mainLayout);
    move(400, 30);
    resize(550, 700);
}

//SLOT
void Gui_Upgrade::offerSelected() {

}