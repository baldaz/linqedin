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
    toolbar = new QToolBar(this);
    toolButtons[0] = new QToolButton();
    toolButtons[0]->setIcon(QPixmap("img/add70.png"));
    toolButtons[1] = new QToolButton();
    toolButtons[1]->setIcon(QPixmap("img/cross108.png"));
    toolbar->addWidget(toolButtons[0]);
    toolbar->addWidget(toolButtons[1]);
    mainLayout->addWidget(toolbar, 0, Qt::AlignTop | Qt::AlignCenter);
    mainLayout->addWidget(gridGroupBox);
    setLayout(mainLayout);
    move(200, 50);
    resize(1000, 650);
}

void Gui_Widget::createGridGroupBox() {
    gridGroupBox = new QGroupBox;
    QGridLayout* layout = new QGridLayout;
    dispInfo = new Gui_DisplayInfo(user);
    dispInfo->setFocusProxy(*buttons);
    listLinks = new Gui_Links(user, dispInfo, layout);
    listLinks->setFocusProxy(*buttons);

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
    dispInfo->setStyleSheet("background: #000 url('img/abstract.png') no-repeat; background-attachment:fixed; border-radius: 10px; background-position: bottom;");
    searchBar = new Gui_Search(user, dispInfo);
    // searchBar->setStyleSheet("background: #f0f");
    // dispInfo->setStyleSheet("background: #fff");
    layout->addWidget(portrait, 0, 0, 1, 1);
    layout->addWidget(dispInfo, 0, 1, 4, 1); /* 0 1 4 2*/
    layout->addWidget(links, 1, 0, 1, 1);
    // listLinks->setStyleSheet("background: #f0f");
    layout->addWidget(listLinks, 2, 0, 1, 1);
    layout->addWidget(searchBar, 3, 0, 1, 1);
    createRightSideList(layout);
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 5);
    layout->setColumnStretch(2, 2);
    // layout->setColumnStretch(3, 2);
    layout->setRowStretch(0, 0);
    layout->setRowStretch(1, 10);
    // layout->setRowStretch(2, 2);
    gridGroupBox->setLayout(layout);
}

void Gui_Widget::logicInitialize() {
    user = new LinqClient(Username("Baldaz", "qwerty"));
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
    user->removeContact(Username("Sara87", ""));
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
}

//slot
void Gui_Widget::userSearch() {
    dispInfo->setText(QString::fromStdString(user->find("Andrea")));
}

//slot
void Gui_Widget::logout() {}

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
    connect(buttons[4], SIGNAL(clicked()), this, SLOT(close()));

    horizontalGroupBox->setLayout(layout);
}

void Gui_Widget::createRightSideList(QGridLayout* lay) {
    QLabel *rightLabel = new QLabel(tr("You could connect to"));
    rightLabel->setMaximumSize(160,15);
    QListWidget* rightSide = new QListWidget();
    QListWidgetItem* item = new QListWidgetItem();
    QListWidgetItem* itemD = new QListWidgetItem();
    QListWidgetItem* itemE = new QListWidgetItem();
    QFont font;
    font.setBold(true);
    item->setData(Qt::DisplayRole, "You could connect to..");
    item->setFont(font);

    itemD->setData(Qt::DisplayRole, "Darius");
    itemD->setData(Qt::DecorationRole, QPixmap("img/link19.png"));
    itemD->setData(Qt::ToolTipRole, "Connected with Pablos, Sara, Atos");

    itemE->setData(Qt::DisplayRole, "John Rambo");
    itemE->setData(Qt::DecorationRole, QPixmap("img/link19.png"));
    itemE->setData(Qt::ToolTipRole, "Connected with Andr, Pablos, Sara, Atos");

    rightSide->addItem(item);
    rightSide->addItem(itemD);
    rightSide->addItem(itemE);
    // lay->addWidget(rightLabel, 0, 2, 0, 1, Qt::AlignTop | Qt::AlignLeft);
    // rightSide->setStyleSheet("background:#ff0");
    // rightSide->setMaximumSize(160, 420);
    lay->addWidget(rightSide, 0, 2, 2, 1, Qt::AlignTop);
}