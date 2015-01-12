#include "gui_search.h"

Gui_Search::Gui_Search(LinqClient* cli, Gui_DisplayInfo* disp, QToolBar* tb, Gui_Links* links, QWidget* parent) : _client(cli), _display(disp), _tbar(tb), _links(links), QLineEdit(parent) {
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
    res = _client->find(text().toStdString());
    if(res.empty()) {
        _tbar->hide();
        _display->setHtml("<h2> Nessun riscontro</h2>");
    }
    else {
        _tbar->show();
        it = res.begin();
        connect(_tbar->childAt(60,1), SIGNAL(clicked()), this, SLOT(incrementIterator()));
        showResult();
    }
}

void Gui_Search::showResult() {
    if(it != res.end()) {
        // QList<QListWidgetItem*> list = _links->findItems(text(), Qt::MatchContains);
        bool list = _client->linked(Username(it->first, ""));
        if(!list) {
            _tbar->actions().at(0)->setVisible(true);
            _tbar->actions().at(1)->setVisible(false);
            _tbar->actions().at(2)->setVisible(false);
        }
        else {
            _tbar->actions().at(0)->setVisible(false);
            _tbar->actions().at(1)->setVisible(true);
            _tbar->actions().at(2)->setVisible(false);
        }
        if(res.size() > 1 && it != res.end()) _tbar->actions().at(2)->setVisible(true);
        else _tbar->actions().at(2)->setVisible(false);
        QString htmloutput = QString::fromStdString(it->second);
        _display->setHtml(htmloutput);
    }
    else {
        _display->setHtml("<h2>Fine</h2>");
        _tbar->actions().at(2)->setVisible(false);
    }
}

//slot
void Gui_Search::incrementIterator() {
    std::cout << "clicà" << std::endl;
    ++it;
    showResult();
}

// int Gui_Search::_i = 0;