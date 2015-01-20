#include "gui_login.h"

Gui_Login::Gui_Login(QWidget* parent) : QDialog(parent) {
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowOpacity(0.95);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QLabel* splash = new QLabel(this);
    QLabel* username = new QLabel("Username:", this);
    QLineEdit* uname = new QLineEdit(this);
    QLabel* password = new QLabel("Password:", this);
    QLineEdit* passw = new QLineEdit(this);
    passw->setEchoMode(QLineEdit::Password);

    splash->setPixmap(QPixmap("img/linked5.png"));
    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    mainLayout->addWidget(splash, Qt::AlignCenter);
    mainLayout->addWidget(username, Qt::AlignLeft);
    mainLayout->addWidget(uname, Qt::AlignRight);
    mainLayout->addWidget(password, Qt::AlignLeft);
    mainLayout->addWidget(passw, Qt::AlignRight);
    mainLayout->addWidget(buttonBox, Qt::AlignLeft|Qt::AlignCenter);
    setLayout(mainLayout);
}

void Gui_Login::resizeEvent(QResizeEvent* event) {
    QPixmap pixmap(size());
    QPainter painter(&pixmap);
    painter.fillRect(pixmap.rect(), Qt::white);
    painter.setBrush(Qt::black);
    painter.drawRoundRect(pixmap.rect());
    setMask(pixmap.createMaskFromColor(Qt::white));
}