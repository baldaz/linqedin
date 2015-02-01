#include "gui_modpopup.h"

Gui_ModPopup::Gui_ModPopup(QWidget* parent) : QDialog(parent) {
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowOpacity(0.95);
    _mainLayout = new QVBoxLayout;
    QPushButton* quit = new QPushButton;
    quit->setIcon(QPixmap("img/prohibited1.png"));
    connect(quit, SIGNAL(clicked()), this, SLOT(close()));
    _mainLayout->addWidget(quit, 0, Qt::AlignTop | Qt::AlignRight);

    edt = new QLineEdit;

    QFormLayout* frm = new QFormLayout;
    frm->addRow("New value: ", edt);
    _mainLayout->addLayout(frm);

    setLayout(_mainLayout);
    move(500, 250);
    resize(230, 70);
}

void Gui_ModPopup::resizeEvent(QResizeEvent* event) {
    QPixmap pixmap(size());
    QPainter painter(&pixmap);
    painter.fillRect(pixmap.rect(), Qt::white);
    painter.setBrush(Qt::black);
    painter.drawRoundRect(pixmap.rect(), 12);
    setMask(pixmap.createMaskFromColor(Qt::white));
}