#include "gui_displayinfo.h"

Gui_DisplayInfo::Gui_DisplayInfo(const QString& out, QWidget* parent) : _output(out), QTextBrowser(parent) {
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