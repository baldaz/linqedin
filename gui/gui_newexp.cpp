#include "gui_newexp.h"

Gui_NewExp::Gui_NewExp(LinqClient* cli, QWidget* parent) : QDialog(parent), _client(cli) {
    setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    setWindowOpacity(0.95);
    QVBoxLayout* _mainLayout = new QVBoxLayout;
    QPushButton* ok = new QPushButton("INSERT", this);
    for(int i = 0; i < 2; ++i)
        edt[i] = new QLineEdit(this);
    from = new QCalendarWidget(this);
    to = new QCalendarWidget(this);
    from->setStyleSheet("font-size:12px");
    from->setHorizontalHeaderFormat(QCalendarWidget::NoHorizontalHeader);
    from->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    to->setStyleSheet("font-size:12px");
    to->setHorizontalHeaderFormat(QCalendarWidget::NoHorizontalHeader);
    to->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    QFormLayout* frm = new QFormLayout;
    QPushButton* quit = new QPushButton;
    quit->setIcon(QPixmap("img/prohibited1.png"));
    connect(quit, SIGNAL(clicked()), this, SLOT(close()));
    _mainLayout->addWidget(quit, 0, Qt::AlignTop | Qt::AlignRight);
    rb[0] = new QRadioButton("Formation", this);
    rb[0]->setChecked(true);
    rb[1] = new QRadioButton("Work", this);
    frm->addRow(rb[0]);
    frm->addRow(rb[1]);
    frm->addRow("Location:", edt[0]);
    frm->addRow("Role:", edt[1]);
    frm->addRow("From:", from);
    frm->addRow("To:", to);
    frm->addRow(ok);
    _mainLayout->addLayout(frm);
    setLayout(_mainLayout);
    move(500, 250);
    resize(230, 70);
    connect(ok, SIGNAL(clicked()), this, SLOT(insert()));
}

//SLOT
void Gui_NewExp::insert() {
    int type = 0;
    if(rb[1]->isChecked()) type = 1;
    string location = edt[0]->text().toStdString();
    string role = edt[1]->text().toStdString();
    QDate frm = from->selectedDate();
    QDate t = to->selectedDate();
    try {
        Experience* e = new Experience(type, location, role, frm, t);
        _client->addExperience(*e);
        QMessageBox::information(this, "Operation success", "Experience added correctly", QMessageBox::Ok);
        emit modified();
        close();
    }catch(Error e) {
        QMessageBox::critical(this, "Date range error", QString::fromStdString(e.errorMessage()));
    }
}
