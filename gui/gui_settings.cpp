#include "gui_settings.h"

Gui_Settings::Gui_Settings(LinqClient* cli, QWidget* parent) : _client(cli), QGridLayout(parent) {
    Gui_Avatar* avatar = new Gui_Avatar(QString::fromStdString(_client->avatar()));
    setSpacing(5);
    QLabel* name = new QLabel("Name:", parent);
    QLineEdit *edtName = new QLineEdit(parent);
    QLabel* surname = new QLabel("Last Name:", parent);
    QLineEdit *edtSurname = new QLineEdit(parent);
    QLabel* address = new QLabel("Address:", parent);
    QLineEdit* edtAddr = new QLineEdit(parent);
    QLabel* email = new QLabel("E-mail:", parent);
    QLineEdit* edtMail = new QLineEdit(parent);
    QLabel* birth = new QLabel("Birth:", parent);
    QLineEdit* edtBirth = new QLineEdit(parent);
    QLabel* phone = new QLabel("Phone:", parent);
    QLineEdit* edtPhone = new QLineEdit(parent);
    QLabel* website = new QLabel("Website:", parent);
    QLineEdit* edtWebsite = new QLineEdit(parent);
    QLabel* uname = new QLabel("Username:", parent);
    QLineEdit* edtUname = new QLineEdit(parent);

    skills = new QListWidget;
    inters = new QListWidget;
    lang = new QListWidget;
    vector<string> v = _client->skills();
    vector<string> i = _client->interests();
    vector<string> l = _client->languages();
    for(vector<string>::iterator it = v.begin(); it != v.end(); ++it) {
        QListWidgetItem* item = new QListWidgetItem;
        item->setData(Qt::DisplayRole, QString::fromStdString(*it));
        item->setData(Qt::DecorationRole, QPixmap("img/rugby100.png"));
        skills->addItem(item);
    }
    for(vector<string>::iterator it = i.begin(); it != i.end(); ++it) {
        QListWidgetItem* item = new QListWidgetItem;
        item->setData(Qt::DisplayRole, QString::fromStdString(*it));
        item->setData(Qt::DecorationRole, QPixmap("img/atom2.png"));
        inters->addItem(item);
    }
    for(vector<string>::iterator it = l.begin(); it != l.end(); ++it) {
        QListWidgetItem* item = new QListWidgetItem;
        item->setData(Qt::DisplayRole, QString::fromStdString(*it));
        item->setData(Qt::DecorationRole, QPixmap("img/flag27.png"));
        lang->addItem(item);
    }
    connect(skills, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(skillsMenu(const QPoint &)));
    connect(inters, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(interestsMenu(const QPoint &)));

    QLineEdit* newskill = new QLineEdit(parent);

    edtName->setEnabled(false);
    edtAddr->setEnabled(false);
    edtMail->setEnabled(false);
    edtSurname->setEnabled(false);
    edtBirth->setEnabled(false);
    edtPhone->setEnabled(false);
    edtWebsite->setEnabled(false);
    edtUname->setEnabled(false);
    newskill->setPlaceholderText("Add new experience");
    newskill->setEnabled(false);

    edtName->setText("Steven");
    edtAddr->setText("Via IV Novembre 24 Stra (VE)");
    edtMail->setText("steven@seagal.ss");
    edtSurname->setText("Seagal");
    edtBirth->setText("08-11-1946");
    edtPhone->setText("3250525147");
    edtWebsite->setText("www.stevenseagal.ss");
    edtUname->setText("Casey");

    addWidget(avatar, 0, 0, 1, 1, Qt::AlignTop);

    QHBoxLayout* hbl = new QHBoxLayout;
    QHBoxLayout* hbl2 = new QHBoxLayout;

    QVBoxLayout* vbl = new QVBoxLayout;
    QFormLayout* frm = new QFormLayout;
    QFormLayout* frm2 = new QFormLayout;
    QPushButton* box = new QPushButton("Alter");

    frm->setVerticalSpacing(10);
    frm2->setVerticalSpacing(10);

    frm->addRow(name, edtName);
    frm->addRow(surname, edtSurname);
    frm->addRow(birth, edtBirth);
    frm->addRow(address, edtAddr);
    frm->addRow("Skills:", skills);
    frm->addRow("Languages:", lang);
    frm2->addRow(phone, edtPhone);
    frm2->addRow(email, edtMail);
    frm2->addRow(website, edtWebsite);
    frm2->addRow(uname, edtUname);
    frm2->addRow("Interests:", inters);
    frm->addRow(newskill);
    newskill->hide();
    addLayout(frm, 0, 1, 1, 1);
    addLayout(frm2, 0, 2, 1, 1);
    addWidget(box, 2, 1, 1, 1);

    // hbl->setSpacing(0);
    // hbl->setMargin(0);
    // hbl->setContentsMargins(0,0,0,0);
    // hbl->addWidget(name);
    // hbl->addWidget(edtName);
    // hbl->addWidget(birth);
    // hbl->addWidget(edtBirth);
    // hbl->addWidget(surname);
    // hbl->addWidget(edtSurname);
    // hbl->addWidget(email);
    // hbl->addWidget(edtMail);

    // hbl2->addWidget(address);
    // hbl2->addWidget(edtAddr);
    // hbl2->addWidget(phone);
    // hbl2->addWidget(edtPhone);
    // hbl2->addWidget(website);
    // hbl2->addWidget(edtWebsite);

    // setColumnStretch(0, 0);
    // setColumnStretch(1, 0);
    // setColumnStretch(2, 0);
    // setColumnStretch(3, 0);
    // setColumnStretch(4, 0);
    // setRowStretch(0, 0);
    // setRowStretch(1, 0);
    // setRowStretch(2, 10);
    // vbl->addLayout(hbl);
    // vbl->addLayout(hbl2);
    // vbl->setSpacing(0);
    // vbl->setMargin(0);
    // vbl->setContentsMargins(0,0,0,0);
    // addLayout(vbl, 0, 1, 1, 1);
}

void Gui_Settings::skillsMenu(const QPoint& pos) {
    QPoint globalPos = skills->mapToGlobal(pos);    // Map the global position to the userlist
    QModelIndex t = skills->indexAt(pos);
    skills->item(t.row())->setSelected(true);           // even a right click will select the item
    // userListMenu->exec(globalPos);
}

void Gui_Settings::interestsMenu(const QPoint& pos) {
    QPoint globalPos = inters->mapToGlobal(pos);    // Map the global position to the userlist
    QModelIndex t = inters->indexAt(pos);
    inters->item(t.row())->setSelected(true);           // even a right click will select the item
    // userListMenu->exec(globalPos);
}