#ifndef DISPLAYINFO_H
#define DISPLAYINFO_H

#include <QTextBrowser>
#include "../linqclient.h"

class Gui_DisplayInfo : public QTextBrowser{
    Q_OBJECT
private:
    LinqClient* _client;
public:
    Gui_DisplayInfo(LinqClient*, QWidget *parent = 0);
signals:

public slots:

};
#endif