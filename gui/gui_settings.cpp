#include "gui_settings.h"

Gui_Settings::Gui_Settings(LinqClient* cli, QWidget* parent) : _client(cli), QGridLayout(parent) {
    Gui_Avatar* avatar = new Gui_Avatar(QString::fromStdString(_client->avatar()));
    setSpacing(5);
    QLabel* name = new QLabel("Name:", parent);
    edtInfo[0] = new QLineEdit(parent);
    QLabel* surname = new QLabel("Last Name:", parent);
    edtInfo[1] = new QLineEdit(parent);
    QLabel* address = new QLabel("Address:", parent);
    edtInfo[2] = new QLineEdit(parent);
    QLabel* email = new QLabel("E-mail:", parent);
    edtInfo[3] = new QLineEdit(parent);
    QLabel* birth = new QLabel("Birth:", parent);
    edtInfo[4] = new QLineEdit(parent);
    QLabel* phone = new QLabel("Phone:", parent);
    edtInfo[5] = new QLineEdit(parent);
    QLabel* website = new QLabel("Website:", parent);
    edtInfo[6] = new QLineEdit(parent);
    QLabel* uname = new QLabel("Username:", parent);
    edtInfo[7] = new QLineEdit(parent);
    QLabel* bio = new QLabel("Short Bio:", parent);
    edtBio = new QTextEdit(parent);
    edtInfo[11] = new QLineEdit(parent);
    edtInfo[12] = new QLineEdit(parent);
    edtInfo[12]->setPlaceholderText("Insert new password");

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
    skills->setContextMenuPolicy(Qt::CustomContextMenu);
    inters->setContextMenuPolicy(Qt::CustomContextMenu);
    lang->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(skills, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(skillsMenu(const QPoint &)));
    connect(inters, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(interestsMenu(const QPoint &)));
    connect(lang, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(languagesMenu(const QPoint&)));

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

    edtInfo[0]->setText("Steven");
    edtInfo[1]->setText("Via IV Novembre 24 Stra (VE)");
    edtInfo[2]->setText("steven@seagal.ss");
    edtInfo[3]->setText("Seagal");
    edtInfo[4]->setText("08-11-1946");
    edtInfo[5]->setText("3250525147");
    edtInfo[6]->setText("www.stevenseagal.ss");
    edtInfo[7]->setText("Casey");
    edtInfo[11]->setText(QString::fromStdString(_client->avatar()));
    edtBio->setText("Seagal was born in Lansing, Michigan, where he lived until he was five years old, when the family moved to California. His mother, Patricia (1930–2003), was a medical technician, and his father, Samuel Steven Seagal (1928–1991), was a high school math teacher. His mother was of Irish ancestry and his father was Jewish (the son of immigrants from Russia). Seagal has reported that he had a Mongolian grandfather, but this seems unlikely. His parents relocated to Fullerton, California, where Seagal attended Buena Park High School in Buena Park.");
    edtBio->setStyleSheet("background: transparent");

    addWidget(avatar, 0, 0, 1, 1, Qt::AlignTop);
/*
    QHBoxLayout* hbl = new QHBoxLayout;
    QHBoxLayout* hbl2 = new QHBoxLayout;

    QVBoxLayout* vbl = new QVBoxLayout; */
    QFormLayout* frm = new QFormLayout;
    QFormLayout* frm2 = new QFormLayout;
    QPushButton* box = new QPushButton("Alter");
    toggle = new QPushButton("Unlock");
    toggle->setCheckable(true);
    connect(toggle, SIGNAL(clicked()), this, SLOT(buttonToggled()));

    frm->setVerticalSpacing(10);
    frm2->setVerticalSpacing(10);

    frm->addRow(name, edtInfo[0]);
    frm->addRow(surname, edtInfo[1]);
    frm->addRow(birth, edtInfo[2]);
    frm->addRow(address, edtInfo[3]);
    frm->addRow(uname, edtInfo[7]);
    frm->addRow("Skills:", skills);
    frm->addRow(edtInfo[8]);
    frm->addRow("Languages:", lang);
    frm->addRow(edtInfo[9]);
    frm2->addRow(phone, edtInfo[4]);
    frm2->addRow(email, edtInfo[5]);
    frm2->addRow(website, edtInfo[6]);
    frm2->addRow("Avatar path:", edtInfo[11]);
    frm2->addRow(edtInfo[12]); //pwd
    frm2->addRow("Interests:", inters);
    frm2->addRow(edtInfo[10]);
    frm2->addRow(bio, edtBio);

    addLayout(frm, 0, 1, 1, 1);
    addLayout(frm2, 0, 2, 1, 1);
    addWidget(box, 2, 1, 1, 1);
    addWidget(toggle, 2, 2, 1, 1);
}

void Gui_Settings::skillsMenu(const QPoint& pos) {
    QPoint globalPos = skills->mapToGlobal(pos);    // Map the global position to the userlist
    QModelIndex t = skills->indexAt(pos);
    skills->item(t.row())->setSelected(true);           // even a right click will select the item
    _selected = skills->item(t.row())->data(Qt::DisplayRole).toString();
    QMenu myMenu;
    myMenu.addAction("Delete", this, SLOT(deleteSkill()));
    myMenu.addAction("Modify", this, SLOT(modifySkill()));
    myMenu.exec(globalPos);
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

void Gui_Settings::buttonToggled() {
    if(toggle->isChecked()) {
        toggle->setText("Lock");
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
    }
}

//SLOT
void Gui_Settings::addSkill() {
    if(!edtInfo[8]->text().isEmpty())
        _client->addTrait(0, edtInfo[8]->text().toStdString());
}

//SLOT
void Gui_Settings::deleteSkill() {
    std::cout << "click on delete" << std::endl;
    _client->deleteTrait(0, _selected.toStdString());
}

//SLOT
void Gui_Settings::modifySkill() {

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

}