#include "gui_displayinfo.h"

Gui_DisplayInfo::Gui_DisplayInfo(LinqClient* client, QWidget* parent) : QTextBrowser(parent) {
    _client = client;
    setHtml(QString::fromStdString(_client->displayHtmlInfo()));
}