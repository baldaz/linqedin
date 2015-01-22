#ifndef GUI_VIEWCONTACT_H
#define GUI_VIEWCONTACT_H

#include <QVBoxLayout>
#include "gui_displayinfo.h"

class Gui_ViewContact : public QVBoxLayout {
    Q_OBJECT
private:
    Gui_DisplayInfo* _display;
    vector<SmartPtr<User> > _contacts;
    QString _toView;
public:
    Gui_ViewContact(Gui_DisplayInfo*, const vector<SmartPtr<User> > &, const QString&, QWidget* parent = 0);
    Gui_ViewContact(LinqClient*, Gui_DisplayInfo*, const QString&, QWidget* parent = 0);
signals:

public slots:

};
#endif