#include "gui_messages.h"

Gui_Messages::Gui_Messages(QWidget* parent) : QGridLayout(parent) {
    _list = new Gui_ListMessages(parent);
    QLabel* portrait = new QLabel;
    QPixmap avatar ("img/seagal.jpg");
    QPixmap mask(avatar.size());
    QPainter maskPainter(&mask);
    maskPainter.fillRect(mask.rect(), Qt::white);
    maskPainter.setBrush(Qt::black);
    maskPainter.drawRoundedRect(mask.rect(), 75, 75);
    avatar.setMask(mask.createMaskFromColor(Qt::white));
    avatar = avatar.scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    portrait->setPixmap(avatar);
    // portrait->setStyleSheet("background:#fff");
    // _list->setStyleSheet("background:#ff0");
    this->addWidget(portrait, 0, 0, 1, 1, Qt::AlignCenter);
    this->addWidget(_list, 0, 1, 3, 1);
    this->setColumnStretch(0, 1);
    this->setColumnStretch(1, 5);
    this->setColumnStretch(2, 2);
    // this->setColumnStretch(3, 2);
    this->setRowStretch(0, 0);
    this->setRowStretch(1, 10);
    // this->setColumnStretch(0, 1);
    // this->setColumnStretch(1, 10);
    // this->setColumnStretch(2, 2);
    // this->setRowStretch(0, 0);
    // this->setRowStretch(1, 10);
}