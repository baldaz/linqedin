#include "gui_links.h"

Gui_Links::Gui_Links(LinqClient* client, QWidget* parent) : QListWidget(parent) {
    vector<string> vec = client->displayHtmlNet();
    vector<string>::iterator it = vec.begin();
    for(; it < vec.end(); ++it)
        addItem(QString::fromStdString(*it));
}