#include "gui_userwindow.h"

Gui_UserWindow::Gui_UserWindow(QWidget* parent) : QWidget(parent) {
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowOpacity(0.95);
    // this->setStyleSheet("* { background-color: white; }");

    createHorizontalGroupBox();
    createOverview();
    createMessages();
    _layoutStack = new QStackedLayout;

    // overviewLayout = new QVBoxLayout(this);
    // messagesLayout = new QVBoxLayout(this);

    QPushButton* quit = new QPushButton;
    quit->setIcon(QPixmap("img/prohibited1.png"));
    connect(quit, SIGNAL(clicked()), this, SLOT(close()));
    _layoutStack->addWidget(overviewGroupBox);
    _layoutStack->addWidget(messagesGroupBox);

    _mainLayout = new QVBoxLayout;
    _mainLayout->addWidget(quit, 0, Qt::AlignTop | Qt::AlignRight);
    _mainLayout->addWidget(horizontalGroupBox);
    _mainLayout->addLayout(_layoutStack);
    setLayout(_mainLayout);
    show();
    move(200, 30);
    resize(1000, 720);
}

void Gui_UserWindow::createHorizontalGroupBox() {
    horizontalGroupBox = new QGroupBox(this);
    QHBoxLayout* layout = new QHBoxLayout(this);

    buttons[0] = new QPushButton("&OVERVIEW");
    buttons[0]->setIcon(QPixmap("img/user91.png"));
    // buttons[0]->installEventFilter(this);
    layout->addWidget(buttons[0], Qt::AlignTop);
    connect(buttons[0], SIGNAL(clicked()), this, SLOT(overview()));

    buttons[1] = new QPushButton("&SETTINGS");
    buttons[1]->setIcon(QPixmap("img/settings48.png"));
    layout->addWidget(buttons[1], Qt::AlignTop);
    connect(buttons[1], SIGNAL(clicked()), this, SLOT(close()));

    buttons[2] = new QPushButton("&PAYMENTS");
    buttons[2]->setIcon(QPixmap("img/banknotes.png"));
    layout->addWidget(buttons[2], Qt::AlignTop);
    connect(buttons[2], SIGNAL(clicked()), this, SLOT(overview()));

    buttons[3] = new QPushButton("&MESSAGES");
    buttons[3]->setIcon(QPixmap("img/send4.png"));
    layout->addWidget(buttons[3], Qt::AlignTop);
    connect(buttons[3], SIGNAL(clicked()), this, SLOT(messages()));

    buttons[4] = new QPushButton("&LOGOUT");
    buttons[4]->setIcon(QPixmap("img/logout13.png"));
    layout->addWidget(buttons[4], Qt::AlignTop);
    connect(buttons[4], SIGNAL(clicked()), this, SLOT(close()));
    layout->stretch(1);
    horizontalGroupBox->setLayout(layout);
    // horizontalGroupBox->setStyleSheet("background-color:#fff");
}

void Gui_UserWindow::createOverview() {
    overviewGroupBox = new QGroupBox;
    _layout = new Gui_Overview;
    overviewGroupBox->setLayout(_layout);
}

void Gui_UserWindow::createMessages() {
    messagesGroupBox = new QGroupBox;
    _mex = new Gui_Messages(this);
    messagesGroupBox->setLayout(_mex);
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
    if(isMaximized()) showNormal();
    else showMaximized();
}

//SLOT
void Gui_UserWindow::overview() {
    _layoutStack->widget(1)->hide();
    _layoutStack->widget(0)->show();
    _layout->refresh();
}

//SLOT
void Gui_UserWindow::messages() {
    _layoutStack->widget(0)->hide();
    _layoutStack->widget(1)->show();
    _layoutStack->setCurrentWidget(messagesGroupBox);
}

// bool Gui_UserWindow::eventFilter(QObject* obj, QEvent* event) {
//     if(event->type() == QEvent::MouseButtonDblClick) {
//         QMouseEvent * mouseEvent = static_cast <QMouseEvent *> (event);
//         if(mouseEvent->button() == Qt::LeftButton | Qt::RightButton)
//             return true;

//     }
//     else return true;
// }
