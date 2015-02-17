#include "avatar.h"
#include "gui_avatar.h"
#include <QFile>

Gui_Avatar::Gui_Avatar(const QString& path, QWidget* parent) : QLabel(parent), _path(path) {
   setPath(_path);
}

void Gui_Avatar::setPath(const QString& path) {
    _path = path;
    if(!QFile::exists(_path)) _path = QString::fromStdString(STANDARD_AVATAR);
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
