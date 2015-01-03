#ifndef GUI_VIEWCONTACT_H
#define GUI_VIEWCONTACT_H

#include "gui_displayinfo.h"

class Gui_ViewContact {
private:
    QString _toView;
    Gui_DisplayInfo* _display;
    vector<SmartPtr<User> > _contacts;
public:
    Gui_ViewContact(Gui_DisplayInfo*, vector<SmartPtr<User> >, QString);
};
#endif