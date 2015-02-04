#include "gui_login.h"

Gui_Login::Gui_Login(QWidget* parent) : QDialog(parent) {
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowOpacity(0.95);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QLabel* splash = new QLabel("LINQEDIN" ,this);
    QLabel* username = new QLabel("Username:", this);
    uname = new QLineEdit(this);
    QLabel* password = new QLabel("Password:", this);
    passw = new QLineEdit(this);
    passw->setEchoMode(QLineEdit::Password);

    splash->setPixmap(QPixmap("img/linked5.png"));
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    QPushButton* quit = new QPushButton;
    // QPushButton* login = new QPushButton("&Login");
    // QPushButton* reg = new QPushButton("&Register");

    quit->setIcon(QPixmap("img/prohibited1.png"));
    connect(quit, SIGNAL(clicked()), this, SLOT(close()));
    mainLayout->addWidget(quit, 0, Qt::AlignTop | Qt::AlignRight);
    mainLayout->addWidget(new QLabel("LINQEDIN"), 0, Qt::AlignTop | Qt::AlignCenter);
    mainLayout->addWidget(splash, Qt::AlignCenter);
    mainLayout->addWidget(username, Qt::AlignLeft);
    mainLayout->addWidget(uname, Qt::AlignRight);
    mainLayout->addWidget(password, Qt::AlignLeft);
    mainLayout->addWidget(passw, Qt::AlignRight);
    mainLayout->addWidget(buttonBox, Qt::AlignLeft|Qt::AlignCenter);

    setLayout(mainLayout);
    connect(buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(onClicked(QAbstractButton*)));
}

void Gui_Login::resizeEvent(QResizeEvent* event) {
    QPixmap pixmap(size());
    QPainter painter(&pixmap);
    painter.fillRect(pixmap.rect(), Qt::white);
    painter.setBrush(Qt::black);
    painter.drawRoundRect(pixmap.rect());
    setMask(pixmap.createMaskFromColor(Qt::white));
}

//SLOT
void Gui_Login::onClicked(QAbstractButton* button) {
    QDialogButtonBox::StandardButton btn = buttonBox->standardButton(button);
    if(btn == QDialogButtonBox::Ok) {
        QString us = uname->text();
        QString pw = passw->text();
        Username u(us.toStdString(), pw.toStdString());
        if(_loader.isAdmin(u)) {
            admwin = new Gui_AdminWindow;
            admwin->show();
        }
        else {
            window = new Gui_UserWindow(_loader.getClientHandle(u));
            window->show();
        }
        close();
    }
    else {
        reg = new Gui_Registration;
        reg->show();
        close();
    }
}