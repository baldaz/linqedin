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

using std::cout;
using std::endl;

int main(int argc, char**argv) {
    // LinqAdmin* admin = new LinqAdmin();
    // Username* ser = new Username("ser", "wword");
    // admin->removeUser(ser);
    cout << endl << "+++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    Username* user = new Username("Baldaz", "password");
    LinqClient* client = new LinqClient(user);
    Username* contact = new Username("Sara87", "sara");
    Username* ser = new Username("ser", "wword");
    client->addContact(contact);
    client->addContact(ser);
    client->removeContact(contact);
    client->displayProfile();
    client->find();
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

    // QApplication app(argc, argv);
    // QWidget window;
    // // window.setWindowTitle(“Im a QWidget”);
    // window.resize(300, 220);
    // QPushButton quit("Quit", &window);
    // quit.setFont(QFont("Inconsolata", 18, QFont::Bold));
    // quit.setGeometry(10, 40, 180, 40);
    // QObject::connect(&quit, SIGNAL(clicked()), &app, SLOT(quit()));
    // window.show();
    // return app.exec();
    return 0;
}