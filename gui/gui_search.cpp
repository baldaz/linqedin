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
    vector<string> res = _client->find(text().toStdString());
    if(res.empty()) {
        _tbar->hide();
        _display->setHtml("<h2> Nessun riscontro</h2>");
    }
    else {
        _tbar->show();
        vector<string>::iterator it = res.begin() + _i;
        if(it < res.end()) {
            QList<QListWidgetItem*> list = _links->findItems(text(), Qt::MatchContains);
            if(list.empty()) {
                _tbar->actions().at(0)->setVisible(true);
                _tbar->actions().at(1)->setVisible(false);
                _tbar->actions().at(2)->setVisible(false);
            }
            else {
                _tbar->actions().at(0)->setVisible(false);
                _tbar->actions().at(1)->setVisible(true);
                _tbar->actions().at(2)->setVisible(false);
            }
            if(it < res.end()-1) _tbar->actions().at(2)->setVisible(true);
            else _tbar->actions().at(2)->setVisible(false);
            connect(_tbar->childAt(0, 2), SIGNAL(clicked()), this, SLOT(incrementIterator()));
            QString htmloutput = QString::fromStdString(*it);
            showResult(htmloutput);
        }
        else {showResult("<h2>Fine</h2>");}
    }
}

void Gui_Search::showResult(const QString& res) {
    _display->setHtml(res);
}

//slot
void Gui_Search::incrementIterator() {
    ++_i;
    search();
}

int Gui_Search::_i = 0;