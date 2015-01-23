// #include <iostream>
// #include "linqclient.h"
// #include "linqadmin.h"
#include "gui/gui_login.h"
#include "gui/gui_userwindow.h"

using std::cout;
using std::endl;

int main(int argc, char**argv) {
    // LinqAdmin* admin = new LinqAdmin;
    // admin->removeUser(Username("Baldaz",""));
    // delete admin;
    LinqClient* client = new LinqClient(Username("Baldaz", "qwerty"));
    client->addContact(Username("Casey", "rayback"));
    client->removeContact(Username("Atilio", ""));
    cout << client->displayProfile() << endl;
    // // client->save();
    delete client;
    // QApplication app(argc, argv);
    // Gui_UserWindow window;
    // Gui_Login logW;
    // QFile File("style/stylesheet.qss");
    // File.open(QFile::ReadOnly);
    // QString StyleSheet = QLatin1String(File.readAll());
    // app.setStyleSheet(StyleSheet);
    // window.setWindowTitle("");
    // if (logW.exec() == QDialog::Accepted) {
    //     window.show();
    // }
    // else return 0;
    // return app.exec();
    return 0;
}