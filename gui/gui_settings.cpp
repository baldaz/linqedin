#include "gui_settings.h"

Gui_Settings::Gui_Settings(LinqClient* cli, QWidget* parent) : _client(cli), QGridLayout(parent) {
    Gui_Avatar* avatar = new Gui_Avatar(QString::fromStdString(_client->avatar()));
    setSpacing(5);
    for(int i = 0; i < NumLineEdit; ++i)
        edtInfo[i] = new QLineEdit(parent);
    edtBio = new QTextEdit(parent);
    edtInfo[12]->setPlaceholderText("Insert new password");

    _modpop = new Gui_ModPopup;

    skills = new QListWidget;
    inters = new QListWidget;
    lang = new QListWidget;
    exps = new QListWidget;
    vector<string> v = _client->skills();
    vector<string> i = _client->interests();
    vector<string> l = _client->languages();
    list<Experience*> e = _client->experiences();
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
    for(list<Experience*>::iterator it = e.begin(); it != e.end(); ++it) {
        QListWidgetItem* item = new QListWidgetItem;
        QString cont = QString(QString::fromStdString((*it)->role()) + " " + QString::fromStdString((*it)->location()));
        item->setData(Qt::DisplayRole, cont);
        item->setData(Qt::DecorationRole, QPixmap("img/work3.png"));
        exps->addItem(item);
    }
    skills->setContextMenuPolicy(Qt::CustomContextMenu);
    inters->setContextMenuPolicy(Qt::CustomContextMenu);
    lang->setContextMenuPolicy(Qt::CustomContextMenu);
    exps->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(skills, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(skillsMenu(const QPoint&)));
    connect(inters, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(interestsMenu(const QPoint&)));
    connect(lang, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(languagesMenu(const QPoint&)));
    connect(exps, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(experiencesMenu(const QPoint&)));

    edtInfo[8] = new QLineEdit(parent);
    edtInfo[8]->setPlaceholderText("Add new skill");
    edtInfo[8]->setEnabled(false);
    edtInfo[8]->hide();
    edtInfo[9] = new QLineEdit(parent);
    edtInfo[9]->setPlaceholderText("Add new interest");
    edtInfo[9]->setEnabled(false);
    edtInfo[9]->hide();
    edtInfo[10] = new QLineEdit(parent);
    edtInfo[10]->setPlaceholderText("Add new language");
    edtInfo[10]->setEnabled(false);
    edtInfo[10]->hide();
    edtInfo[12]->hide();

    connect(edtInfo[8], SIGNAL(returnPressed()), this, SLOT(addSkill()));
    connect(edtInfo[9], SIGNAL(returnPressed()), this, SLOT(addInterest()));
    connect(edtInfo[10], SIGNAL(returnPressed()), this, SLOT(addLanguage()));

    edtInfo[0]->setEnabled(false);
    edtInfo[1]->setEnabled(false);
    edtInfo[2]->setEnabled(false);
    edtInfo[3]->setEnabled(false);
    edtInfo[4]->setEnabled(false);
    edtInfo[5]->setEnabled(false);
    edtInfo[6]->setEnabled(false);
    edtInfo[7]->setEnabled(false);
    edtInfo[11]->setEnabled(false);
    edtBio->setReadOnly(true);

    Info* in = _client->info();
    Bio* b = dynamic_cast<Bio*>(in);
    if(b) {
        edtInfo[0]->setText(QString::fromStdString(b->name()));
        edtInfo[1]->setText(QString::fromStdString(b->surname()));
        edtInfo[3]->setText(QString::fromStdString(b->address()));
        edtInfo[5]->setText(QString::fromStdString(b->email()));
        edtInfo[2]->setText(b->birthdate().toString("dd.MM.yyyy"));
        edtInfo[4]->setText(QString::fromStdString(b->telephon()));
        edtInfo[6]->setText(QString::fromStdString(b->website()));
        edtInfo[7]->setText(QString::fromStdString(_client->username().login()));
        edtInfo[11]->setText(QString::fromStdString(_client->avatar()));
        edtBio->setText(QString::fromStdString(b->bio()));
    }
    edtBio->setStyleSheet("background: transparent");

    addWidget(avatar, 0, 0, 1, 1, Qt::AlignTop);

    QFormLayout* frm = new QFormLayout;
    QFormLayout* frm2 = new QFormLayout;
    QPushButton* box = new QPushButton("Alter");
    toggle = new QPushButton("Unlock");
    toggle->setCheckable(true);
    connect(toggle, SIGNAL(clicked()), this, SLOT(buttonToggled()));

    frm->setVerticalSpacing(10);
    frm2->setVerticalSpacing(10);

    frm->addRow("Name:", edtInfo[0]);
    frm->addRow("Surname:", edtInfo[1]);
    frm->addRow("Birthdate:", edtInfo[2]);
    frm->addRow("Address:" , edtInfo[3]);
    frm->addRow("Username:", edtInfo[7]);
    frm->addRow("Skills:", skills);
    frm->addRow(edtInfo[8]);
    frm->addRow("Languages:", lang);
    frm->addRow(edtInfo[9]);
    frm2->addRow("Phone:", edtInfo[4]);
    frm2->addRow("E-mail:", edtInfo[5]);
    frm2->addRow("Website:", edtInfo[6]);
    frm2->addRow("Avatar path:", edtInfo[11]);
    frm2->addRow(edtInfo[12]); //pwd
    frm2->addRow("Interests:", inters);
    frm2->addRow(edtInfo[10]);
    frm2->addRow("Experiences:", exps);
    frm2->addRow("Short bio:", edtBio);

    addLayout(frm, 0, 1, 1, 1);
    addLayout(frm2, 0, 2, 1, 1);
    // addWidget(box, 2, 1, 1, 1);
    addWidget(toggle, 2, 2, 1, 1);
}

void Gui_Settings::skillsMenu(const QPoint& pos) {
    QPoint globalPos = skills->mapToGlobal(pos);    // Map the global position to the userlist
    QModelIndex t = skills->indexAt(pos);
    skills->item(t.row())->setSelected(true);           // even a right click will select the item
    _selected = skills->item(t.row())->data(Qt::DisplayRole).toString();
    QMenu myMenu;
    myMenu.addAction("Delete", this, SLOT(deleteSkill()));
    QAction* act = myMenu.addAction("Modify", this, SLOT(modifySkill()));
    myMenu.exec(globalPos);
    // connect(act, SIGNAL(modified(int)), this, SLOT(modifySkill(int)));
}

void Gui_Settings::interestsMenu(const QPoint& pos) {
    QPoint globalPos = inters->mapToGlobal(pos);    // Map the global position to the userlist
    QModelIndex t = inters->indexAt(pos);
    inters->item(t.row())->setSelected(true);           // even a right click will select the item
    _selected = inters->item(t.row())->data(Qt::DisplayRole).toString();
    QMenu myMenu;
    myMenu.addAction("Delete", this, SLOT(deleteInterest()));
    myMenu.addAction("Modify", this, SLOT(modifyInterest()));
    QAction* selectedItem = myMenu.exec(globalPos);
}

void Gui_Settings::languagesMenu(const QPoint& pos) {
    QPoint globalPos = lang->mapToGlobal(pos);
    QModelIndex t = lang->indexAt(pos);
    lang->item(t.row())->setSelected(true);
    _selected = lang->item(t.row())->data(Qt::DisplayRole).toString();
    QMenu myMenu;
    myMenu.addAction("Delete", this, SLOT(deleteLanguage()));
    myMenu.addAction("Modify", this, SLOT(modifyLanguage()));
    myMenu.exec(globalPos);
}

void Gui_Settings::experiencesMenu(const QPoint& pos) {
    QPoint globalPos = exps->mapToGlobal(pos);
    QModelIndex t = exps->indexAt(pos);
    exps->item(t.row())->setSelected(true);
    _selected = exps->item(t.row())->data(Qt::DisplayRole).toString();
    QMenu myMenu;
    myMenu.addAction("Delete", this, SLOT(deleteExperience()));
    myMenu.addAction("Modify", this, SLOT(modifyExperience()));
    myMenu.exec(globalPos);
}

void Gui_Settings::buttonToggled() {
    if(toggle->isChecked()) {
        toggle->setText("Save");
        edtInfo[0]->setEnabled(true);
        edtInfo[1]->setEnabled(true);
        edtInfo[2]->setEnabled(true);
        edtInfo[3]->setEnabled(true);
        edtInfo[4]->setEnabled(true);
        edtInfo[5]->setEnabled(true);
        edtInfo[6]->setEnabled(true);
        edtInfo[7]->setEnabled(true);
        edtInfo[8]->show();
        edtInfo[8]->setEnabled(true);
        edtInfo[9]->show();
        edtInfo[9]->setEnabled(true);
        edtInfo[10]->show();
        edtInfo[10]->setEnabled(true);
        edtInfo[11]->setEnabled(true);
        edtInfo[12]->show();
        edtBio->setReadOnly(false);
        edtBio->setStyleSheet("background: #1a1a1a;");
    }
    else {
        toggle->setText("Unlock");
        edtInfo[0]->setEnabled(false);
        edtInfo[1]->setEnabled(false);
        edtInfo[2]->setEnabled(false);
        edtInfo[3]->setEnabled(false);
        edtInfo[4]->setEnabled(false);
        edtInfo[5]->setEnabled(false);
        edtInfo[6]->setEnabled(false);
        edtInfo[7]->setEnabled(false);
        edtInfo[8]->hide();
        edtInfo[8]->setEnabled(false);
        edtInfo[9]->hide();
        edtInfo[9]->setEnabled(false);
        edtInfo[10]->hide();
        edtInfo[10]->setEnabled(false);
        edtInfo[11]->setEnabled(false);
        edtInfo[12]->hide();
        edtBio->setReadOnly(true);
        edtBio->setStyleSheet("background: transparent");
        _client->alterProfile(0, edtInfo[0]->text().toStdString());
        _client->alterProfile(1, edtInfo[1]->text().toStdString());
        _client->alterProfile(2, edtInfo[3]->text().toStdString());
        _client->alterProfile(3, edtInfo[2]->text().toStdString());
        _client->alterProfile(4, edtInfo[5]->text().toStdString());
        _client->alterProfile(5, edtInfo[4]->text().toStdString());
        _client->alterProfile(6, edtInfo[6]->text().toStdString());
        _client->alterProfile(7, edtBio->toPlainText().toStdString());
    }
}

//SLOT
void Gui_Settings::addSkill() {
    if(!edtInfo[8]->text().isEmpty())
        _client->addTrait(0, edtInfo[8]->text().toStdString());
}

//SLOT
void Gui_Settings::deleteSkill() {
    _client->deleteTrait(0, _selected.toStdString());
}

//SLOT
void Gui_Settings::modifySkill() {
    _modpop->show();
}

//SLOT
void Gui_Settings::addLanguage() {
    if(!edtInfo[10]->text().isEmpty())
        _client->addTrait(1, edtInfo[10]->text().toStdString());
}

//SLOT
void Gui_Settings::deleteLanguage() {
    _client->deleteTrait(1, _selected.toStdString());
}

//SLOT
void Gui_Settings::modifyLanguage() {
    _modpop->show();
}

//SLOT
void Gui_Settings::addInterest() {
    if(!edtInfo[9]->text().isEmpty())
        _client->addTrait(2, edtInfo[9]->text().toStdString());
}

//SLOT
void Gui_Settings::deleteInterest() {
    _client->deleteTrait(2, _selected.toStdString());
}

//SLOT
void Gui_Settings::modifyInterest() {
    _modpop->show();
}

//SLOT
void Gui_Settings::deleteExperience() {
    // _client->deleteTrait(2, _selected.toStdString());
}

//SLOT
void Gui_Settings::modifyExperience() {
    _modpop->show();
}