#include "gui_messages.h"

Gui_Messages::Gui_Messages(LinqClient* cli, QWidget* parent) : QGridLayout(parent), _client(cli) {
    mexcount = 0;
    QTabWidget* tab = new QTabWidget(parent);
    Gui_Avatar* portrait = new Gui_Avatar(QString::fromStdString(_client->avatar()));
    _listIn = new QListWidget;
    _listIn->setItemDelegate(new ListDelegate(_listIn));
    _listOut = new QListWidget;
    _listOut->setItemDelegate(new ListDelegate(_listOut));
    _output = new QTextBrowser;

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
    rcv = unreadMex(mexcount);
    tab->addTab(_listIn, rcv);
    tab->addTab(_listOut, "Sent");

    // portrait->setStyleSheet("background:#fff");
    // _listIn->setStyleSheet("background:#ff0");
    addWidget(portrait, 0, 0, 1, 1, Qt::AlignTop);
    addWidget(tab, 0, 1, 1, 1);
    addWidget(_output, 0, 2, 1, -1);
    setColumnStretch(0, 1);
    setColumnStretch(1, 2);
    setColumnStretch(2, 4);
    setRowStretch(0, 0);
    setRowStretch(1, 0);
    setRowStretch(2, 10);

    QPushButton* box = new QPushButton("SEND");

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
    connect(box, SIGNAL(clicked()), this, SLOT(refreshMessages()));
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
    _client->sendMail(dest.toStdString(), obj.toStdString(), body.toStdString(), false);
    emit messageSent();
}

void Gui_Messages::refreshMessages() {
    std::cout << "refresh" << std::endl;
}

QString Gui_Messages::unreadMex(int mc) {
    QString rcv = QString("Received");
    if(mc > 0)
        rcv.append(QString("(%1)").arg(mc));
    return rcv;
}
