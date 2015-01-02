#ifndef DISPLAYINFO_H
#define DISPLAYINFO_H

#include <QGroupBox>
#include <QTextBrowser>
#include "../linqclient.h"

class Gui_DisplayInfo : public QGroupBox {
    Q_OBJECT
private:
    LinqClient* _client;
    QTextBrowser* _infobox;
public:
    Gui_DisplayInfo(const LinqClient&, QWidget *parent = 0);
signals:

public slots:

};
#endif