#include "gui_search.h"

Gui_Search::Gui_Search(LinqClient* cli, Gui_DisplayInfo* disp, QToolBar* tb, Gui_Links* links, Gui_Avatar* avt, QWidget* parent) : _client(cli), _display(disp), _tbar(tb), _links(links), _avt(avt), QLineEdit(parent) {
    setPlaceholderText("Search..");
    setToolTip("<p>You can activate unified search by typing ':'. E.G: ':c++,perl,snowboard' will list all users that have c++ perl and snowboard into their skills / interests fields.</p>");
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
    setClearButtonEnabled(true);
    connect(this, SIGNAL(returnPressed()), this, SLOT(search()));
}

void Gui_Search::search() {
    res = _client->find(text().toStdString());
    if(res.empty()) {
        if(!_tbar->isHidden()) _tbar->hide();
        _display->setHtml("<h2> Nessun riscontro</h2>");
    }
    else {
        if(_tbar->isHidden()) _tbar->show();
        // _tbar->actions().at(0)->setEnabled(true);
        // _tbar->actions().at(2)->setEnabled(true);
        it = res.begin();
        if(res.size() > 1)
            if(!_tbar->actions().at(2)->isVisible()) _tbar->actions().at(2)->setVisible(true);
        connect(_tbar->childAt(60,0), SIGNAL(clicked()), this, SLOT(incrementIterator()));
        showResult();
    }
}

void Gui_Search::showResult() {
    if(it != res.end()) {
        bool list = _client->linked(Username(it->first, ""));
        _display->setInfo1(QString::fromStdString(it->first));
        _cnt = _display->info1();
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
        QString htmloutput = QString("<span style='color: #666'>( " + QString::fromStdString(it->first) + " )</span>" + QString::fromStdString(it->second));
        _display->setHtml(htmloutput);
        _avt->setPath(QString::fromStdString(_client->avatarFromUser(Username(it->first, ""))));
    }
    else {
        _display->setHtml("<h2>Fine</h2>");
        _tbar->actions().at(2)->setVisible(false);
        // disconnect(_tbar->childAt(60,0), 0, 0, 0);
    }
}

//slot
void Gui_Search::incrementIterator() {
    std::cout << "clicà" << std::endl;
    ++it;
    showResult();
}

void Gui_Search::addConn() {
    std::cout << "added" << std::endl;
    std::cout << _cnt.toStdString() << std::endl;
    Username us(_cnt.toStdString(), "");
    _client->addContact(us);
}

void Gui_Search::rmConn() {
    std::cout << "removed" << std::endl;
    std::cout << _cnt.toStdString() << std::endl;
    Username us(_cnt.toStdString(), "");
    _client->removeContact(us);
}
// int Gui_Search::_i = 0;