#include "gui/gui_login.h"
#include "gui/gui_userwindow.h"

int main(int argc, char**argv) {
    QApplication app(argc, argv);
    Gui_Login logW;
    QFile File("style/stylesheet.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    app.setStyleSheet(StyleSheet);
    logW.show();
    return app.exec();
}