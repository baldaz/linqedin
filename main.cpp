#include "gui/gui_login.h"
#include "gui/gui_userwindow.h"

using std::cout;
using std::endl;

int main(int argc, char**argv) {
    // LinqAdmin* admin = new LinqAdmin;
    // // admin->removeUser(Username("Baldaz",""));
    // // Bio b;
    // // Username u("ciao", "pirla");
    // // Account a(&b, u, basic);
    // // User* n = new BasicUser(&a);
    // // admin->insertUser(n);
    // map<string, string> par;
    // par["name"] = "ciao";
    // admin->insertUser("osis", "dsds", par);
    // delete admin;
    // LinqClient* client = new LinqClient(Username("Casey", "rayback"));
    // client->addContact(Username("Casey", "rayback"));
    // client->removeContact(Username("Atilio", ""));
    // client->sendMail("Casey", "Memcheck", "Garbage left?", false);
    // cout << client->displayProfile() << endl;
    // cout << client->displayHtmlInfo() << endl;
    // cout << client->displayHtmlSettings() << endl;
    // cout << client->displayHtmlMessages() << endl;
    // cout << client->displayHtmlPayments() << endl;
    // vector<SmartPtr<User> > vs = client->contactsInfo();
    // client->save();
    // delete client;
    QApplication app(argc, argv);
    // Gui_UserWindow window;
    Gui_Login logW;
    QFile File("style/stylesheet.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    app.setStyleSheet(StyleSheet);
    // window.setWindowTitle("");
    // if (logW.exec() == QDialog::Accepted) {
        // window.show();
    // }
    // else return 0;
    logW.show();
    return app.exec();
    // return 0;
}