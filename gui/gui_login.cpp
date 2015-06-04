#include "gui_login.h"
#include <QMessageBox>

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
    passw->installEventFilter(this);
    splash->setPixmap(QPixmap("img/linked5.png"));
    buttonBox = new QDialogButtonBox;
    QPushButton* quit = new QPushButton;
    QPushButton* login = new QPushButton("&Login");
    QPushButton* reg = new QPushButton("&Register");
    buttonBox->addButton(login, QDialogButtonBox::AcceptRole);
    buttonBox->addButton(reg, QDialogButtonBox::RejectRole);

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
    try {
        _loader = new Loader;
    }catch (Error e) {
        QMessageBox::warning(this, "Database missing", "No database found, creating a new one");
        _loader = new Loader;
    }
    connect(buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(onClicked(QAbstractButton*)));
    connect(this, SIGNAL(logged()), this, SLOT(login()));

}

void Gui_Login::resizeEvent(QResizeEvent* event) {
    QPixmap pixmap(size());
    QPainter painter(&pixmap);
    painter.fillRect(pixmap.rect(), Qt::white);
    painter.setBrush(Qt::black);
    painter.drawRoundRect(pixmap.rect());
    setMask(pixmap.createMaskFromColor(Qt::white));
    event->accept();
}

//SLOT
void Gui_Login::onClicked(QAbstractButton* button) {
    QDialogButtonBox::ButtonRole btn = buttonBox->buttonRole(button);
    if(btn == QDialogButtonBox::AcceptRole) {
        bool log = true;
        QString us = uname->text();
        QString pw = passw->text();
        Username u(us.toStdString(), pw.toStdString());
        if(_loader->isAdmin(u)) {
            admwin = new Gui_AdminWindow;
            admwin->show();
            close();
        }
        else {
            try {
                c = _loader->getClientHandle(u);
            }catch(Error e) {
                QMessageBox::critical(this, "Error!", QString::fromStdString(e.errorMessage()));
                log = false;
            }
            if(log) emit logged();
        }
    }
    else {
        reg = new Gui_Registration;
        reg->show();
        close();
    }
}

//SLOT
void Gui_Login::login() {
    window = new Gui_UserWindow(c);
    window->show();
    connect(window, SIGNAL(logOut()), this, SLOT(showMe()));
    connect(window, SIGNAL(ext()), this, SLOT(close()));
    hide();
}

//SLOT
void Gui_Login::showMe() {
    show();
}

void Gui_Login::closeEvent(QCloseEvent* event) {
    delete c;
    event->accept();
}
