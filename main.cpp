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
#include "gui/gui_widget.h"
#include <QPalette>
#include <QStyleFactory>

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
    // app.setStyle(QStyleFactory::create("Fusion"));

    // QPalette darkPalette;
    // darkPalette.setColor(QPalette::Window, QColor(53,53,53));
    // darkPalette.setColor(QPalette::WindowText, Qt::white);
    // darkPalette.setColor(QPalette::Base, QColor(25,25,25));
    // darkPalette.setColor(QPalette::AlternateBase, QColor(53,53,53));
    // darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    // darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    // darkPalette.setColor(QPalette::Text, Qt::white);
    // darkPalette.setColor(QPalette::Button, QColor(53,53,53));
    // darkPalette.setColor(QPalette::ButtonText, Qt::white);
    // darkPalette.setColor(QPalette::BrightText, Qt::red);
    // darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));

    // darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    // darkPalette.setColor(QPalette::HighlightedText, Qt::black);

    // app.setPalette(darkPalette);

    // app.setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
    app.setStyleSheet(StyleSheet);
    // window.setStyleSheet("width:400px; height:200px;");
    // window.setGeometry(250, 100, 800, 600);
    window.setStyleSheet("border: none");
    // window.setStyleSheet("background: url('img/mbuntu-10.jpg'); border-radius: 10px; border-color: beige; margin:0; padding:0;");
    window.setWindowTitle("");
    window.show();
    return app.exec();
    // return 0;
}