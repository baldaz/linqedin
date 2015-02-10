#include "gui_avatar.h"

Gui_Avatar::Gui_Avatar(const QString& path, QWidget* parent) : QLabel(parent), _path(path) {
   setPath(_path);
}

void Gui_Avatar::setPath(const QString& path) {
    _path = path;
    QPixmap avatar(_path);
    QPixmap mask(avatar.size());
    QPainter maskPainter(&mask);
    maskPainter.fillRect(mask.rect(), Qt::white);
    maskPainter.setBrush(Qt::black);
    maskPainter.drawRoundedRect(mask.rect(), 75, 75);
    avatar.setMask(mask.createMaskFromColor(Qt::white));
    avatar = avatar.scaled(150, 150, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    setPixmap(avatar);
}
