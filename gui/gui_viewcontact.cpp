#include "gui_viewcontact.h"

Gui_ViewContact::Gui_ViewContact(Gui_DisplayInfo* disp, vector<SmartPtr<User> > users, QString view, QWidget* parent) : _display(disp), _contacts(users), _toView(view), QVBoxLayout(parent) {
    vector<SmartPtr<User> >::iterator it = _contacts.begin();
    for(; it < _contacts.end(); ++it)
        if(QString::fromStdString((*it)->account()->username()->login()) == _toView) {
            (*it)->addVisit();
            QString output = QString(QString::fromStdString((*it)->account()->info()->printHtml()) + "<h5>Visit Count</h5><p> %1").arg((*it)->visitCount());
            _display->setHtml(output);
            QString title = QString(QString::fromStdString((*it)->account()->username()->login()));
            _display->setDocumentTitle(title);
        }
}