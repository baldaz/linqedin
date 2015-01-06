#include "gui_search.h"

Gui_Search::Gui_Search(LinqClient* cli, Gui_DisplayInfo* disp, QWidget* parent) : _client(cli), _display(disp), QLineEdit(parent) {
    setPlaceholderText("Search..");
    vector<string> vec = _client->displayHtmlNet();
    QStringList completions;
    if(!vec.empty()) {
        vector<string>::iterator it = vec.begin();
        for(; it < vec.end(); ++it)
            completions.push_back(QString::fromStdString(*it));
    }
    QCompleter* completer = new QCompleter(completions);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    setCompleter(completer);
    connect(this, SIGNAL(returnPressed()), this, SLOT(search()));
}

void Gui_Search::search() {
    _display->setHtml(QString::fromStdString(_client->find(text().toStdString())));
}