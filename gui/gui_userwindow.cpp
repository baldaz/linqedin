#include "gui_userwindow.h"

Gui_UserWindow::Gui_UserWindow(QWidget* parent) : QWidget(parent) {
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowOpacity(0.95);
    // this->setStyleSheet("* { background-color: white; }");

    show();

    createHorizontalGroupBox();
    createGridGroupBox();
    QVBoxLayout* mainLayout = new QVBoxLayout;
    QPushButton* quit = new QPushButton;
    quit->setIcon(QPixmap("img/prohibited1.png"));
    connect(quit, SIGNAL(clicked()), this, SLOT(close()));
    mainLayout->addWidget(quit, 0, Qt::AlignBottom | Qt::AlignRight);
    mainLayout->addWidget(horizontalGroupBox);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(gridGroupBox);
    mainLayout->setSpacing(-1);
    // mainLayout->setMargin(0);
    setLayout(mainLayout);
    move(200, 30);
    resize(1000, 720);
}

void Gui_UserWindow::createHorizontalGroupBox() {
    horizontalGroupBox = new QGroupBox();
    QHBoxLayout* layout = new QHBoxLayout;

    buttons[0] = new QPushButton("OVERVIEW");
    buttons[0]->setIcon(QPixmap("img/user91.png"));
    // buttons[0]->installEventFilter(this);
    layout->addWidget(buttons[0]);
    connect(buttons[0], SIGNAL(clicked()), this, SLOT(overview()));

    buttons[1] = new QPushButton("SETTINGS");
    buttons[1]->setIcon(QPixmap("img/settings48.png"));
    layout->addWidget(buttons[1]);
    connect(buttons[1], SIGNAL(clicked()), this, SLOT(close()));

    buttons[2] = new QPushButton("PAYMENTS");
    buttons[2]->setIcon(QPixmap("img/banknotes.png"));
    layout->addWidget(buttons[2]);
    connect(buttons[2], SIGNAL(clicked()), this, SLOT(close()));

    buttons[3] = new QPushButton("MESSAGES");
    buttons[3]->setIcon(QPixmap("img/send4.png"));
    layout->addWidget(buttons[3]);
    connect(buttons[3], SIGNAL(clicked()), this, SLOT(close()));

    buttons[4] = new QPushButton("LOGOUT");
    buttons[4]->setIcon(QPixmap("img/logout13.png"));
    layout->addWidget(buttons[4]);
    connect(buttons[4], SIGNAL(clicked()), this, SLOT(close()));

    horizontalGroupBox->setLayout(layout);
}

void Gui_UserWindow::createGridGroupBox() {
    gridGroupBox = new QGroupBox;
    layout = new Gui_Overview;
    gridGroupBox->setLayout(layout);
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
    layout->refresh();
}

// bool Gui_UserWindow::eventFilter(QObject* obj, QEvent* event) {
//     if(event->type() == QEvent::MouseButtonDblClick) {
//         QMouseEvent * mouseEvent = static_cast <QMouseEvent *> (event);
//         if(mouseEvent->button() == Qt::LeftButton | Qt::RightButton)
//             return true;

//     }
//     else return true;
// }
