#ifndef GUI_AVATAR_H
#define GUI_AVATAR_H

#include <QLabel>
#include <QPainter>
#include <QBitmap>

class Gui_Avatar : public QLabel {
    Q_OBJECT
private:
    QString _path;
public:
    Gui_Avatar(const QString& = "", QWidget* parent = 0);
    void setPath(const QString& = "");
};
#endif