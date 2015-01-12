#include "gui_widget.h"

Gui_Widget::Gui_Widget() {
    logicInitialize();
    createHorizontalGroupBox();
    createGridGroupBox();
    // Layout principale della dialog
    QVBoxLayout* mainLayout = new QVBoxLayout;
    // mainLayout->addWidget(new QSizeGrip(this), 0, Qt::AlignBottom | Qt::AlignRight);
    // mainLayout->addWidget(new QPushButton("X"), 0, Qt::AlignBottom | Qt::AlignRight);
    mainLayout->addWidget(horizontalGroupBox);
    mainLayout->setSpacing(0);
    // MENU
    // QMenuBar* menuBar = new QMenuBar(0);
    // QMenu* fileMenu = menuBar->addMenu(tr("File"));
    // fileMenu->addAction(tr("Open..."));
    // fileMenu->addAction(tr("Close..."));
    // fileMenu->addSeparator();
    // QAction* exitAction = fileMenu->addAction(tr("Quit"));
    // QMenu* viewMenu = menuBar->addMenu(tr("&View"));
    // QAction* fullScreenAction = viewMenu->addAction(tr("Full screen"));
    // QAction* normalViewAction = viewMenu->addAction(tr("Normal view"));
    // QMenu* helpMenu = new QMenu(tr("&Help"));
    // menuBar->addMenu(helpMenu);
    // // connessione signal-slot
    // connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
    // connect(fullScreenAction, SIGNAL(triggered()), this, SLOT(showFullScreen()));
    // connect(normalViewAction, SIGNAL(triggered()), this, SLOT(showNormal()));
    // mainLayout->setMenuBar(menuBar);
    // mainLayout->addWidget(toolbar, 0, Qt::AlignTop | Qt::AlignCenter);
    mainLayout->addWidget(gridGroupBox);
    setLayout(mainLayout);
    move(200, 30);
    resize(1000, 700);
}

void Gui_Widget::createGridGroupBox() {
    gridGroupBox = new QGroupBox;
    QGridLayout* layout = new QGridLayout;
    dispInfo = new Gui_DisplayInfo(user);
    dispInfo->setFocusProxy(*buttons);

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

    toolbar = new QToolBar(this);
    toolButtons[0] = new QToolButton();
    toolButtons[0]->setIcon(QPixmap("img/add70.png"));
    toolButtons[1] = new QToolButton();
    toolButtons[1]->setIcon(QPixmap("img/cross108.png"));
    toolButtons[2] = new QToolButton();
    toolButtons[2]->setIcon(QPixmap("img/right244.png"));
    toolbar->addWidget(toolButtons[0]);
    toolbar->addWidget(toolButtons[1]);
    toolbar->addWidget(toolButtons[2]);
    toolbar->hide();

    listLinks = new Gui_Links(user, dispInfo, toolbar);
    listLinks->setFocusProxy(*buttons);

    searchBar = new Gui_Search(user, dispInfo, toolbar, listLinks);

    layout->addWidget(portrait, 0, 0, 1, 1);
    layout->addWidget(dispInfo, 0, 1, 3, 1); /* 0 1 4 2*/
    layout->addWidget(links, 1, 0, 1, 1);
    // listLinks->setStyleSheet("background: #f0f");
    layout->addWidget(listLinks, 2, 0, 1, 1);
    layout->addWidget(searchBar, 3, 0, 1, 1);
    layout->addWidget(toolbar, 3, 1, 1, 1, Qt::AlignCenter);
    QListWidget* lw = new QListWidget();
    // layout->addWidget(lw, 4, 0, 1, 1);
    // lw->hide();
    createRightSideList(layout);
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 5);
    layout->setColumnStretch(2, 2);
    // layout->setColumnStretch(3, 2);
    layout->setRowStretch(0, 0);
    layout->setRowStretch(1, 10);
    // layout->setRowStretch(2, 20);
    // layout->setRowStretch(3, 1);
    gridGroupBox->setLayout(layout);
}

void Gui_Widget::logicInitialize() {
    user = new LinqClient(Username("Casey", "rayback"));
    // mostraProfilo();
}

// slot
void Gui_Widget::refreshLinks() {
    // toolButtons[0]->setEnabled(false);
    listLinks->refresh();
    dispInfo->setHtml(QString::fromStdString(user->displayHtmlInfo()));
}
// slot
void Gui_Widget::insertContatto() {
    dispInfo->setText(tr("Inserito"));
    user->addContact(Username("ser", ""));
    user->save();
}

// slot
void Gui_Widget::removeContatto() {
    user->removeContact(Username("Pablito", ""));
    user->save();
}

// slot
void Gui_Widget::viewSettings() {
    dispInfo->setHtml(QString::fromStdString(user->displayHtmlSettings()));
}

// slot
void Gui_Widget::viewPayments() {
    dispInfo->setHtml(QString::fromStdString(user->displayHtmlPayments()));
}

//slot
void Gui_Widget::viewMessages() {
    dispInfo->setHtml(QString::fromStdString(user->displayHtmlMessages()));
    // removeContatto();
}

//slot
void Gui_Widget::userSearch() {
//     vector<string> vec = user->find("Andrea");
//     dispInfo->setText(QString::fromStdString(vec));
}

//slot
void Gui_Widget::logout() {
    user->save();
    close();
}

void Gui_Widget::createHorizontalGroupBox() {
    horizontalGroupBox = new QGroupBox();
    QHBoxLayout* layout = new QHBoxLayout;

    buttons[0] = new QPushButton("OVERVIEW");
    buttons[0]->setIcon(QPixmap("img/user91.png"));
    layout->addWidget(buttons[0]);
    connect(buttons[0], SIGNAL(clicked()), this, SLOT(refreshLinks()));

    buttons[1] = new QPushButton("SETTINGS");
    buttons[1]->setIcon(QPixmap("img/settings48.png"));
    layout->addWidget(buttons[1]);
    connect(buttons[1], SIGNAL(clicked()), this, SLOT(viewSettings()));

    buttons[2] = new QPushButton("PAYMENTS");
    buttons[2]->setIcon(QPixmap("img/banknotes.png"));
    layout->addWidget(buttons[2]);
    connect(buttons[2], SIGNAL(clicked()), this, SLOT(viewPayments()));

    buttons[3] = new QPushButton("MESSAGES");
    buttons[3]->setIcon(QPixmap("img/send4.png"));
    layout->addWidget(buttons[3]);
    connect(buttons[3], SIGNAL(clicked()), this, SLOT(viewMessages()));

    buttons[4] = new QPushButton("LOGOUT");
    buttons[4]->setIcon(QPixmap("img/logout13.png"));
    layout->addWidget(buttons[4]);
    connect(buttons[4], SIGNAL(clicked()), this, SLOT(logout()));

    horizontalGroupBox->setLayout(layout);
}

void Gui_Widget::createRightSideList(QGridLayout* lay) {
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