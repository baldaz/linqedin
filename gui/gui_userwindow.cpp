#include "gui_userwindow.h"

Gui_UserWindow::Gui_UserWindow(LinqClient* cli, QWidget* parent) : QWidget(parent), user(cli) {
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowOpacity(0.95);

    createHorizontalGroupBox();
    createOverview();
    createSettings();
    createMessages();
    createPayments();
    if(user->level() >= business)
        createGroups();
    _layoutStack = new QStackedLayout;
    _layoutStack->addWidget(overviewGroupBox);
    _layoutStack->addWidget(messagesGroupBox);
    _layoutStack->addWidget(settingsGroupBox);
    _layoutStack->addWidget(paymentsGroupBox);
    if(user->level() >= business)
        _layoutStack->addWidget(groupsGroupBox);

    _mainLayout = new QVBoxLayout;
    QPushButton* quit = new QPushButton;
    quit->setIcon(QPixmap("img/prohibited1.png"));
    connect(quit, SIGNAL(clicked()), this, SLOT(exit()));
    _mainLayout->addWidget(quit, 0, Qt::AlignTop | Qt::AlignRight);
    _mainLayout->addWidget(horizontalGroupBox);
    _mainLayout->addLayout(_layoutStack);
    setLayout(_mainLayout);
    move(100, 30);
    resize(1150, 720);
}

void Gui_UserWindow::createHorizontalGroupBox() {
    horizontalGroupBox = new QGroupBox(this);
    QHBoxLayout* layout = new QHBoxLayout(this);

    buttons[0] = new QPushButton("&OVERVIEW");
    buttons[0]->setIcon(QPixmap("img/user91.png"));
    connect(buttons[0], SIGNAL(clicked()), this, SLOT(overview()));

    buttons[1] = new QPushButton("&SETTINGS");
    buttons[1]->setIcon(QPixmap("img/settings48.png"));
    connect(buttons[1], SIGNAL(clicked()), this, SLOT(settings()));

    buttons[2] = new QPushButton("S&TATISTICS");
    buttons[2]->setIcon(QPixmap("img/business155.png"));
    connect(buttons[2], SIGNAL(clicked()), this, SLOT(payments()));

    buttons[3] = new QPushButton("&MESSAGES");
    buttons[3]->setIcon(QPixmap("img/send4.png"));
    connect(buttons[3], SIGNAL(clicked()), this, SLOT(messages()));

    buttons[4] = new QPushButton("&LOGOUT");
    buttons[4]->setIcon(QPixmap("img/logout13.png"));
    connect(buttons[4], SIGNAL(clicked()), this, SLOT(logout()));

    layout->addWidget(buttons[0], Qt::AlignTop);
    layout->addWidget(buttons[2], Qt::AlignTop);
    if(user->level() >= business) {
        buttons[5] = new QPushButton("&GROUPS");
        buttons[5]->setIcon(QPixmap("img/multiple25.png"));
        connect(buttons[5], SIGNAL(clicked()), this, SLOT(groups()));
        layout->addWidget(buttons[5], Qt::AlignTop);
    }
    layout->addWidget(buttons[3], Qt::AlignTop);
    layout->addWidget(buttons[1], Qt::AlignTop);
    layout->addWidget(buttons[4], Qt::AlignTop);
    layout->stretch(1);
    horizontalGroupBox->setLayout(layout);
    horizontalGroupBox->installEventFilter(this);
}

void Gui_UserWindow::createOverview() {
    overviewGroupBox = new QGroupBox;
    _layout = new Gui_Overview(user);
    overviewGroupBox->setLayout(_layout);
}

void Gui_UserWindow::createMessages() {
    messagesGroupBox = new QGroupBox;
    _mex = new Gui_Messages(user, this);
    messagesGroupBox->setLayout(_mex);
}

void Gui_UserWindow::createSettings() {
    settingsGroupBox = new QGroupBox;
    _set = new Gui_Settings(user, this);
    settingsGroupBox->setLayout(_set);
}

void Gui_UserWindow::createPayments() {
    paymentsGroupBox = new QGroupBox;
    _pay = new Gui_Statistics(user, this);
    paymentsGroupBox->setLayout(_pay);
}

void Gui_UserWindow::createGroups() {
    groupsGroupBox = new QGroupBox;
    _grp = new Gui_Groups(user, this);
    groupsGroupBox->setLayout(_grp);
}

void Gui_UserWindow::setClient(LinqClient* cli) {
    user = cli;
}

bool Gui_UserWindow::eventFilter(QObject* obj, QEvent* event) {
    if(obj == horizontalGroupBox && event->type() == QEvent::MouseButtonDblClick) {
        QMouseEvent * mouseEvent = static_cast <QMouseEvent *> (event);
        if(mouseEvent->button() == Qt::LeftButton)
            return true;
    }
    return false;
}

//overload
void Gui_UserWindow::mousePressEvent(QMouseEvent* event) {
    mpos = event->pos();
}

void Gui_UserWindow::mouseMoveEvent(QMouseEvent* event) {
    if(event->buttons() && Qt::LeftButton) {
        QPoint diff = event->pos() - mpos;
        QPoint newpos = pos() + diff;
        move(newpos);
    }
}

void Gui_UserWindow::mouseDoubleClickEvent(QMouseEvent* event) {
    if(event->button() == Qt::LeftButton) {
        if(isMaximized()) showNormal();
        else showMaximized();
    }
}

//SLOT
void Gui_UserWindow::overview() {
    _layoutStack->widget(0)->show();
    _layoutStack->setCurrentWidget(overviewGroupBox);
    _layout->refresh();
}

//SLOT
void Gui_UserWindow::messages() {
    _layoutStack->widget(1)->show();
    _layoutStack->setCurrentWidget(messagesGroupBox);
}

//SLOT
void Gui_UserWindow::settings() {
    _layoutStack->widget(2)->show();
    _layoutStack->setCurrentWidget(settingsGroupBox);
}

//SLOT
void Gui_UserWindow::payments() {
    _layoutStack->widget(3)->show();
    _layoutStack->setCurrentWidget(paymentsGroupBox);
}

//SLOT
void Gui_UserWindow::groups() {
    _layoutStack->widget(4)->show();
    _layoutStack->setCurrentWidget(groupsGroupBox);
}

//SLOT
void Gui_UserWindow::logout() {
    emit logOut();
    close();
}

void Gui_UserWindow::closeEvent(QCloseEvent* event) {
    event->accept();
}

void Gui_UserWindow::exit() {
    emit ext();
    close();
}
