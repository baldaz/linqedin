#include "gui_viewcontact.h"

Gui_ViewContact::Gui_ViewContact(Gui_DisplayInfo* disp, vector<SmartPtr<User> > users, QString view) : _display(disp), _contacts(users), _toView(view) {

}