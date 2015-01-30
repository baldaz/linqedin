#ifndef DISPLAYINFO_H
#define DISPLAYINFO_H

#include <QTextBrowser>

class Gui_DisplayInfo : public QTextBrowser{
    Q_OBJECT
private:
    QString _output, _info1, _info2;
public:
    Gui_DisplayInfo(const QString& = "", QWidget *parent = 0);
    void setInfo1(const QString&);
    QString info1() const;
    void setInfo2(const QString&);
    QString info2() const;
signals:

public slots:

};
#endif