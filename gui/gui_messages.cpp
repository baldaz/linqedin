#include "gui_messages.h"
#include <QMenu>
#include <QMouseEvent>
#include <QMessageBox>

Gui_Messages::Gui_Messages(LinqClient* cli, QWidget* parent) : QGridLayout(parent), _client(cli) {
    mexcount = 0;
    QTabWidget* tab = new QTabWidget(parent);
    Gui_Avatar* portrait = new Gui_Avatar(QString::fromStdString(_client->avatar()));
    _listIn = new QListWidget;
    _listIn->setItemDelegate(new ListDelegate(_listIn));
    _listOut = new QListWidget;
    _listOut->setItemDelegate(new ListDelegate(_listOut));
    _output = new QTextBrowser;
    _listIn->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(_listIn, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(delMenu(const QPoint&)));
    createLists();
    rcv = unreadMex(mexcount);
    tab->addTab(_listIn, rcv);
    tab->addTab(_listOut, "Sent");

    addWidget(portrait, 0, 0, 1, 1, Qt::AlignTop);
    addWidget(tab, 0, 1, 1, 1);
    addWidget(_output, 0, 2, 1, -1);
    setColumnStretch(0, 1);
    setColumnStretch(1, 2);
    setColumnStretch(2, 4);
    setRowStretch(0, 0);
    setRowStretch(1, 0);
    setRowStretch(2, 10);

    box = new QPushButton("SEND");
    box->installEventFilter(this);

    QLabel* ne = new QLabel("<h2>New message</h2>");
    addWidget(ne, 1, 0, 1, -1, Qt::AlignCenter);
    QGridLayout* frm = new QGridLayout;
    frm->setSpacing(20);
    QLabel *title = new QLabel("To:");
    frm->addWidget(title, 0, 0, 1, 1);

    edt1 = new QLineEdit();
    edt1->setPlaceholderText("Insert username");
    frm->addWidget(edt1, 0, 1, 1, 1);

    QLabel *author = new QLabel("Subject:");
    frm->addWidget(author, 1, 0, 1, 1);

    edt2 = new QLineEdit();
    edt2->setPlaceholderText("Subject");
    frm->addWidget(edt2, 1, 1, 1, 1);

    QLabel *review = new QLabel("Body:");
    frm->addWidget(review, 2, 0, 1, 1);

    te = new QTextEdit();
    te->setPlaceholderText("Body of mail");
    te->setStyleSheet("background: #1a1a1a; border-radius: 5px; color: #e6e6e6; font-weight: 400;");
    frm->addWidget(te, 2, 1, 3, 1);
    addLayout(frm, 2, 0, 3, -1);
    addWidget(box, 5, 2, 1, 1, Qt::AlignRight);

    connect(_listIn, SIGNAL(clicked(QModelIndex)), this, SLOT(viewInMailBody()));
    connect(_listOut, SIGNAL(clicked(QModelIndex)), this, SLOT(viewOutMailBody()));
    connect(box, SIGNAL(clicked()), this, SLOT(sendMail()));
    connect(this, SIGNAL(modified()), this, SLOT(refreshMessages()));
}

void Gui_Messages::createLists() {
    inm = _client->inMail();
    list<SmartPtr<Message> > out = _client->outMail();
    list<SmartPtr<Message> >::iterator it = inm.begin();
    for( ; it != inm.end(); ++it) {
        QListWidgetItem* item = new QListWidgetItem;
        QString from = QString("From: ").append(QString::fromStdString((*it)->sender().login())).append(" ").append((*it)->sent().toString("dd.MM.yyyy"));
        item->setData(Qt::DisplayRole, QString::fromStdString((*it)->object()));
        item->setData(Qt::DecorationRole, QPixmap("img/envelope12.png"));
        item->setData(Qt::UserRole + 1, from);
        item->setData(Qt::UserRole + 2, QString::fromStdString((*it)->body()));
        item->setData(Qt::UserRole + 3, (*it)->isRead());
        item->setData(Qt::UserRole + 5, (*it)->sent());
        item->setData(Qt::UserRole + 6, QString::fromStdString((*it)->sender().login()));
        if((*it)->isRead())
            item->setData(Qt::UserRole + 4, QPixmap("img/verification24.png"));
        else mexcount++;
        _listIn->addItem(item);
    }
    for(it = out.begin(); it != out.end(); ++it) {
        QListWidgetItem* item = new QListWidgetItem;
        QString from = QString("To: ").append(QString::fromStdString((*it)->receiver().login())).append(" ").append((*it)->sent().toString("dd.MM.yyyy"));
        item->setData(Qt::DisplayRole, QString::fromStdString((*it)->object()));
        item->setData(Qt::DecorationRole, QPixmap("img/envelope12.png"));
        item->setData(Qt::UserRole + 1, from);
        item->setData(Qt::UserRole + 2, QString::fromStdString((*it)->body()));
        item->setData(Qt::UserRole + 3, 1);
        _listOut->addItem(item);
    }
}

void Gui_Messages::viewInMailBody() {
    list<SmartPtr<Message> >::iterator it = inm.begin();
    int c = 0;
    while(c < _listIn->currentRow()) {++it; c++;}
    (*it)->setRead(true);
    _client->modifyInMail(inm);
    QString title = _listIn->currentItem()->data(Qt::DisplayRole).toString();
    QString sel = _listIn->currentItem()->data(Qt::UserRole + 2).toString();
    _listIn->currentItem()->setData(Qt::UserRole + 3, true);
    _listIn->currentItem()->setData(Qt::UserRole + 4, QPixmap("img/verification24.png"));
    _output->setHtml("</h2>" + title + "</h2><p style='font-weight:400'>" + sel + "</p>");
}

void Gui_Messages::viewOutMailBody() {
    QString title = _listOut->currentItem()->data(Qt::DisplayRole).toString();
    QString sel = _listOut->currentItem()->data(Qt::UserRole + 2).toString();
    _output->setHtml("</h2>" + title + "</h2><p style='font-weight:400'>" + sel + "</p>");
}

void Gui_Messages::sendMail() {
    QString dest = edt1->text();
    QString obj = edt2->text();
    QString body = te->toPlainText();
    try {
        _client->sendMail(dest.toStdString(), obj.toStdString(), body.toStdString(), false);
        emit modified();
    }catch(Error e) {
        QMessageBox::critical(0, "An error occoured", QString::fromStdString(e.errorMessage()));
    }
}

void Gui_Messages::refreshMessages() {
    _listIn->clear();
    _listOut->clear();
    createLists();
}

QString Gui_Messages::unreadMex(int mc) {
    QString rcv = QString("Received");
    if(mc > 0)
        rcv.append(QString("(%1)").arg(mc));
    return rcv;
}

//SLOT
void Gui_Messages::delMenu(const QPoint& pos) {
    if(_listIn->item(_listIn->indexAt(pos).row())) {
        QPoint globalPos = _listIn->mapToGlobal(pos);    // Map the global position to the userlist
        QModelIndex t = _listIn->indexAt(pos);
        _listIn->item(t.row())->setSelected(true);           // even a right click will select the item
        string obj = _listIn->item(t.row())->data(Qt::DisplayRole).toString().toStdString();
        string body = _listIn->item(t.row())->data(Qt::UserRole + 2).toString().toStdString();
        string from = _listIn->item(t.row())->data(Qt::UserRole + 6).toString().toStdString();
        string to = _client->username().login();
        QDate sent;
        sent = _listIn->item(t.row())->data(Qt::UserRole + 5).toDate();
        bool read = _listIn->item(t.row())->data(Qt::UserRole + 3).toBool();
        _m_sel = new Message(Username(from, ""), Username(to, ""), obj, body, read, sent);
        QMenu myMenu;
        myMenu.addAction("Delete", this, SLOT(deleteMessage()));
        myMenu.exec(globalPos);
    }
}

//SLOT
void Gui_Messages::deleteMessage() {
    try {
        _client->deleteMessage(*_m_sel);
        _client->save();
        emit modified();
    }catch (Error e) {
        QMessageBox::critical(0, "Error occoured", QString::fromStdString(e.errorMessage()));
    }
}

bool Gui_Messages::eventFilter(QObject* obj, QEvent* event) {
    if(obj == box && event->type() == QEvent::MouseButtonDblClick) {
        QMouseEvent * mouseEvent = static_cast <QMouseEvent *> (event);
        if(mouseEvent->button() == Qt::LeftButton)
            return true;
    }
    return false;
}