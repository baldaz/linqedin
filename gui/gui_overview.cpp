#include "gui_overview.h"

Gui_Overview::Gui_Overview(QWidget* parent) : QGridLayout(parent) {
    logicInitialize();
    dispInfo = new Gui_DisplayInfo(user);

    portrait = new QLabel();
    QPixmap avatar ("img/seagal.jpg");
    QPixmap mask(avatar.size());
    QPainter maskPainter(&mask);
    maskPainter.fillRect(mask.rect(), Qt::white);
    maskPainter.setBrush(Qt::black);
    maskPainter.drawRoundedRect(mask.rect(), 75, 75);
    avatar.setMask(mask.createMaskFromColor(Qt::white));
    avatar = avatar.scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    portrait->setPixmap(avatar);
    QLabel* links = new QLabel(tr("Connections (%1)").arg(user->netSize()));
    links->setMaximumSize(120,20);
    // links->setPixmap(QPixmap("img/share12.png"));
    dispInfo->setStyleSheet("background:#000 url('img/abstract.png') no-repeat; background-attachment:fixed; border-radius: 10px; background-position: bottom;");
    // searchBar->setStyleSheet("background: #f0f");
    // dispInfo->setStyleSheet("background: #fff");

    toolbar = new QToolBar;
    toolButtons[0] = new QToolButton(toolbar);
    toolButtons[0]->setIcon(QPixmap("img/add70.png"));
    toolButtons[1] = new QToolButton(toolbar);
    toolButtons[1]->setIcon(QPixmap("img/cross108.png"));
    toolButtons[2] = new QToolButton(toolbar);
    toolButtons[2]->setIcon(QPixmap("img/right244.png"));
    toolbar->addWidget(toolButtons[0]);
    toolbar->addWidget(toolButtons[1]);
    toolbar->addWidget(toolButtons[2]);
    toolbar->hide();
    toolbar->blockSignals(true);

    listLinks = new Gui_Links(user, dispInfo, toolbar);

    searchBar = new Gui_Search(user, dispInfo, toolbar, listLinks);

    this->addWidget(portrait, 0, 0, 1, 1);
    this->addWidget(dispInfo, 0, 1, 3, 1); /* 0 1 4 2*/
    this->addWidget(links, 1, 0, 1, 1);
    // listLinks->setStyleSheet("background: #f0f");
    this->addWidget(listLinks, 2, 0, 1, 1);
    this->addWidget(searchBar, 3, 0, 1, 1);
    this->addWidget(toolbar, 3, 1, 1, 1, Qt::AlignCenter);
    QListWidget* lw = new QListWidget();
    // this->addWidget(lw, 4, 0, 1, 1);
    // lw->hide();
    createRightSideList(this);
    this->setColumnStretch(0, 1);
    this->setColumnStretch(1, 5);
    this->setColumnStretch(2, 2);
    // this->setColumnStretch(3, 2);
    this->setRowStretch(0, 0);
    this->setRowStretch(1, 10);
    // layout->setRowStretch(2, 20);
    // layout->setRowStretch(3, 1);
}

void Gui_Overview::logicInitialize() {
    user = new LinqClient(Username("Casey", "rayback"));
}

void Gui_Overview::createRightSideList(QGridLayout* lay) {
    vector<SmartPtr<User> > users = user->similarity();
    QListWidget* rightSide = new QListWidget();
    QFont font;
    font.setBold(true);
    QListWidgetItem* item = new QListWidgetItem();
    item->setData(Qt::DisplayRole, "People you may know");
    item->setFont(font);
    rightSide->addItem(item);

    vector<SmartPtr<User> >::iterator it = users.begin();
    QString fullname;
    UserInfo* uf;
    for(; it < users.end(); ++it) {
        QListWidgetItem* itemD = new QListWidgetItem();
        uf = dynamic_cast<UserInfo*> ((*it)->account()->info());
        fullname = QString(QString::fromStdString(uf->name()) + " " + QString::fromStdString(uf->surname()));
        itemD->setData(Qt::DisplayRole, fullname);
        itemD->setData(Qt::DecorationRole, QPixmap("img/link19.png"));
        // itemD->setData(Qt::ToolTipRole, "Connected with Pablos, Sara, Atos");
        rightSide->addItem(itemD);
    }
    // rightSide->setStyleSheet("background:#ff0");
    lay->addWidget(rightSide, 0, 2, 2, 1, Qt::AlignTop);
}

void Gui_Overview::refresh() {
    listLinks->refresh();
    dispInfo->setHtml(QString::fromStdString(user->displayHtmlInfo()));
    toolbar->hide();
}

// void Gui_Overview::mousePressEvent(QMouseEvent* event) {
//     mpos = event->pos();
// }

// void Gui_Overview::mouseMoveEvent(QMouseEvent* event) {
//     if(event->buttons() && Qt::LeftButton) {
//         QPoint diff = event->pos() - mpos;
//         QPoint newpos = pos() + diff;
//         move(newpos);
//     }
// }