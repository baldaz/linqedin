#include "gui_displayinfo.h"

Gui_DisplayInfo::Gui_DisplayInfo(const QString& out, const QString& i1, const QString& i2, QWidget* parent) : QTextBrowser(parent), _output(out), _info1(i1), _info2(i2) {
    setHtml(_output);
}

QString Gui_DisplayInfo::info1() const {
    return _info1;
}

void Gui_DisplayInfo::setInfo1(const QString& i) {
    _info1 = i;
}

QString Gui_DisplayInfo::info2() const {
    return _info2;
}

void Gui_DisplayInfo::setInfo2(const QString& i) {
    _info2 = i;
}
