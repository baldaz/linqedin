// #include <QApplication>
// #include <QFont>
// #include <QPushButton>
// #include <QWidget>
#include <iostream>
// #include "account.h"
// #include "linqnet.h"
// #include "linqdb.h"
#include "linqclient.h"
#include "linqadmin.h"
#include "gui_widget.h"

using std::cout;
using std::endl;

int main(int argc, char**argv) {
    // // LinqAdmin* admin = new LinqAdmin();
    // // Info* info = new UserInfo();
    // Username* ser = new Username("ser", "wword");
    // // admin->alterSubscription(ser, business);
    // // Account* a = new Account(info , ser, basic);
    // // LinqNet* inet = new LinqNet();
    // // User* prova = new BasicUser(a, inet);
    // // admin->removeUser(ser);
    // // admin->insertUser(prova);
    // cout << endl << "+++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    // Username* user = new Username("Baldaz", "password");
    // LinqClient* client = new LinqClient(user);
    // Username* sara = new Username("Sara87", "sara");
    // // Username* ser = new Username("ser", "wword");
    // client->addContact(sara);
    // // client->addContact(sara);
    // // client->addContact(ser);
    // client->removeContact(sara);
    // Experience* frm = new Instruction("ITIS F.Severi", "2002", "2007");
    // // client->addFormation(frm);
    // client->displayProfile();
    // client->find();
    // // client->save();
    // // delete ser, user, sara, client;
    // cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

    QApplication app(argc, argv);
    Gui_Widget window;
    QFile File("style/stylesheet.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    app.setStyleSheet(StyleSheet);
    // window.setStyleSheet("width:400px; height:200px;");
    // window.setGeometry(250, 100, 800, 600);
    window.setStyleSheet("border: none");
    window.setWindowTitle("");
    window.show();
    return app.exec();
    // return 0;
}