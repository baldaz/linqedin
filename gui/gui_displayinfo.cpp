#include "gui_displayinfo.h"

Gui_DisplayInfo::Gui_DisplayInfo(LinqClient* client, QWidget* parent) : _client(client), QTextBrowser(parent) {
    setHtml(QString::fromStdString(_client->displayHtmlInfo()));
}