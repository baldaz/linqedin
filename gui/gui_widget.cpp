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
    QPixmap avatar ("img/darius.png");
    QPixmap mask(avatar.size());
    QPainter maskPainter(&mask);
    maskPainter.fillRect(mask.rect(), Qt::white);
    maskPainter.setBrush(Qt::black);
    maskPainter.drawRoundedRect(mask.rect(), 65, 65);
    avatar.setMask(mask.createMaskFromColor(Qt::white));
    avatar = avatar.scaled(140, 140, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    portrait->setPixmap(avatar);
    QLabel* links = new QLabel(tr("Connections (%1)").arg(user->netSize()));
    links->setMaximumSize(120,20);
    // links->setPixmap(QPixmap("img/share12.png"));
    dispInfo->setStyleSheet("background: #000 url('img/abstract.png') no-repeat; background-attachment:fixed; border-radius: 10px;");
    searchBar = new Gui_Search(user, dispInfo);
    // searchBar->setStyleSheet("background: #f0f");
    // dispInfo->setStyleSheet("background: #fff");
    layout->addWidget(portrait, 0, 0, 1, 1);
    layout->addWidget(dispInfo, 0, 2, 4, -1);
    layout->addWidget(links, 1, 0, 1, 1);
    layout->addWidget(listLinks, 2, 0, 1 ,1);
    layout->addWidget(searchBar, 3, 0, -1, 1);
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(2, 5);
    layout->setRowStretch(0, 0);
    layout->setRowStretch(1, 1);
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
    dispInfo->setText(tr("inserito"));
    user->addContact(Username("ser", ""));
    user->save();
    // dispInfo->setText(tr("Inserito nuovo contatto"));
}

// slot
void Gui_Widget::removeContatto() {
    user->removeContact(Username("Sara87", ""));
    user->save();
    // dispInfo->setText(QString::fromStdString(user->displayProfile()));
}

// slot
void Gui_Widget::mostraProfilo() { }

// slot
void Gui_Widget::viewNet() {
    // dispInfo->setText(tr("net"));
}

//slot
void Gui_Widget::userSearch() {
    dispInfo->setText(QString::fromStdString(user->find("Andrea")));
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
    connect(buttons[1], SIGNAL(clicked()), this, SLOT(removeContatto()));

    buttons[2] = new QPushButton("PAYMENTS");
    layout->addWidget(buttons[2]);
    connect(buttons[2], SIGNAL(clicked()), this, SLOT(viewNet()));

    // buttons[3] = new QPushButton("SEARCH");
    // layout->addWidget(buttons[3]);
    // connect(buttons[3], SIGNAL(clicked()), this, SLOT(userSearch()));

    buttons[3] = new QPushButton("MESSAGES");
    layout->addWidget(buttons[3]);
    connect(buttons[3], SIGNAL(clicked()), this, SLOT(insertContatto()));

    buttons[4] = new QPushButton("LOGOUT");
    layout->addWidget(buttons[4]);

    horizontalGroupBox->setLayout(layout);
    // buttons[0]->setGeometry(1, 1, 50, 25);
}