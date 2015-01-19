// #include <iostream>
// #include "linqclient.h"
// #include "linqadmin.h"
// #include "gui/gui_widget.h"
#include "gui/gui_userwindow.h"
// #include <QPalette>
// #include <QStyleFactory>

using std::cout;
using std::endl;

int main(int argc, char**argv) {
    // LinqClient* client = new LinqClient(Username("Baldaz", "qwerty"));
    // client->addContact(Username("Casey", "rayback"));
    // client->removeContact(Username("Atilio", ""));
    // cout << client->displayProfile() << endl;
    // // client->save();
    // delete client;
    QApplication app(argc, argv);
    Gui_UserWindow window;
    QFile File("style/stylesheet.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    app.setStyleSheet(StyleSheet);
    window.setWindowTitle("");
    return app.exec();
    // return 0;
}