#include "gui_widget.h"

Gui_Widget::Gui_Widget() {
    logicInitialize();
    createHorizontalGroupBox();
    // bigEditor = new QTextBrowser();
    // bigEditor->setReadOnly(true);
    // bigEditor->setAcceptRichText(true);
    // bigEditor->setTextInteractionFlags(bigEditor->textInteractionFlags() | Qt::TextSelectableByKeyboard);
    // bigEditor->setFontWeight(400);
    // bigEditor->setStyleSheet("background: url('img/background1.png') no-repeat; background-attachment:fixed; border-radius: 10px;");
    createGridGroupBox();
    // Layout principale della dialog
    QVBoxLayout* mainLayout = new QVBoxLayout;
    // crea menu
    // QMenuBar* menuBar = new QMenuBar(0);
    // QMenu* fileMenu = menuBar->addMenu(tr("File"));
    // fileMenu->addAction(tr("Open..."));
    // fileMenu->addAction(tr("Close..."));
    // fileMenu->addSeparator();
    // QAction* exitAction = fileMenu->addAction(tr("Close LinkedIn"));
    // QMenu* viewMenu = menuBar->addMenu(tr("&View"));
    // QAction* fullScreenAction = viewMenu->addAction(tr("Full screen"));
    // QAction* normalViewAction = viewMenu->addAction(tr("Normal view"));
    // QMenu* helpMenu = new QMenu(tr("&Help"));
    // menuBar->addMenu(helpMenu);

    // connessione signal-slot
    // connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
    // connect(fullScreenAction, SIGNAL(triggered()), this, SLOT(showFullScreen()));
    // connect(normalViewAction, SIGNAL(triggered()), this, SLOT(showNormal()));


    // mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(horizontalGroupBox);
    mainLayout->addWidget(gridGroupBox);
    // mainLayout->addWidget(bigEditor);
    setLayout(mainLayout);
    move(200, 50);
    resize(1000, 650);
}

void Gui_Widget::createGridGroupBox() {
    gridGroupBox = new QGroupBox;
    QGridLayout* layout = new QGridLayout;
    // // gridGroupBox->setStyleSheet("background: QLinearGradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #eef, stop: 1 #ccf)");
    // for (int i = 0; i < NumGridRows-1; ++i) {
    //     labels[i] = new QLabel(tr("Line %1:").arg(i + 1));
    //     lineEdits[i] = new QLineEdit;
    //     layout->addWidget(labels[i], i + 1, 0);
    //     layout->addWidget(lineEdits[i], i + 1, 1);
    // }

    // labels[NumGridRows-1] = new QLabel();
    // lineEdits[NumGridRows-1] = new QLineEdit;
    // layout->addWidget(labels[NumGridRows-1], NumGridRows, 0);
    // layout->addWidget(lineEdits[NumGridRows-1], NumGridRows, 1);

    smallEditor = new QTextEdit();
    smallEditor->setReadOnly(true);
    smallEditor->setFontWeight(400);

    // listview = new QListWidget();
    // smallEditor->setStyleSheet("border-style:dotted; border-top-width:1px; border-color: #e6e6e6;");

    // listview->setStyleSheet("background:#fff;");

    // layout->addWidget(smallEditor, 0, 2, 4, 1);
    // layout->setColumnStretch(1, 10);
    // layout->setColumnStretch(2, 20);
    // gridGroupBox->setLayout(layout);
    dispInfo = new Gui_DisplayInfo(user);
    listLinks = new Gui_Links(user);
    portrait = new QLabel();
    QPixmap pixmap ("img/portrait2.png");
    portrait->setPixmap(pixmap);

    QLabel* links = new QLabel(tr("Links (%1)").arg(user->netSize()));
    // links->setStyleSheet("background:#fff;");
    links->setMaximumSize(70,20);
    // portrait->setStyleSheet("background: #fff;");
    dispInfo->setStyleSheet("background: #404040 url('img/background1.png') no-repeat; background-attachment:fixed; border-radius: 10px;");
    layout->addWidget(portrait, 0, 0, 1, 1);
    layout->addWidget(dispInfo, 0, 2, 4, -1);
    // layout->addWidget(smallEditor, 1, 0, 1, 1);
    layout->addWidget(links, 1, 0, 1, 1);
    layout->addWidget(listLinks, 2, 0, -1 ,1);
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(2, 5);
    layout->setRowStretch(0, 0);
    layout->setRowStretch(1, 1);
    gridGroupBox->setLayout(layout);
}

void Gui_Widget::logicInitialize() {
    user = new LinqClient(new Username("Baldaz", "qwerty"));
    // mostraProfilo();
}

// slot
void Gui_Widget::insertContatto() {
    dispInfo->setText(tr("inserito"));
    user->addContact(new Username("ser", ""));
    user->save();
    // dispInfo->setText(tr("Inserito nuovo contatto"));
}

// slot
void Gui_Widget::removeContatto() {
    user->removeContact(new Username("Sara87", ""));
    user->save();
    // dispInfo->setText(QString::fromStdString(user->displayProfile()));
}

// slot
void Gui_Widget::mostraProfilo() {
    // createGridGroupBox();
    // dispInfo->setHtml(QString::fromStdString(user->displayHtmlInfo()));
    // listLinks = new Gui_Links(user);
    // smallEditor->setHtml(QString::fromStdString(user->displayHtmlNet()));
    // listview->addItems(tr("Links"));
}

// slot
void Gui_Widget::viewNet() {
    // dispInfo->setText(tr("net"));
}

//slot
void Gui_Widget::userSearch() {
    // dispInfo->setText(QString::fromStdString(user->find()));
}

void Gui_Widget::createHorizontalGroupBox() {
    horizontalGroupBox = new QGroupBox();
    QHBoxLayout* layout = new QHBoxLayout;


    buttons[0] = new QPushButton("OVERVIEW");
    layout->addWidget(buttons[0]);
    connect(buttons[0], SIGNAL(clicked()), this, SLOT(mostraProfilo()));

    buttons[1] = new QPushButton("PROFILE");
    layout->addWidget(buttons[1]);
    connect(buttons[1], SIGNAL(clicked()), this, SLOT(removeContatto()));

    buttons[2] = new QPushButton("PAYMENTS");
    layout->addWidget(buttons[2]);
    connect(buttons[2], SIGNAL(clicked()), this, SLOT(viewNet()));

    buttons[3] = new QPushButton("SEARCH");
    layout->addWidget(buttons[3]);
    connect(buttons[3], SIGNAL(clicked()), this, SLOT(userSearch()));

    buttons[4] = new QPushButton("MESSAGES");
    layout->addWidget(buttons[4]);
    connect(buttons[4], SIGNAL(clicked()), this, SLOT(insertContatto()));

    buttons[5] = new QPushButton("LOGOUT");
    layout->addWidget(buttons[5]);

    horizontalGroupBox->setLayout(layout);
    // buttons[0]->setGeometry(1, 1, 50, 25);
}