#include "gui_viewcontact.h"

Gui_ViewContact::Gui_ViewContact(Gui_DisplayInfo* disp, const vector<SmartPtr<User> >& users, const QString& view, QWidget* parent) : _display(disp), _contacts(users), _toView(view), QVBoxLayout(parent) {
    vector<SmartPtr<User> >::iterator it = _contacts.begin();
    for(; it < _contacts.end(); ++it)
        if(QString::fromStdString((*it)->account()->username().login()) == _toView) {
            QString output = QString(QString::fromStdString((*it)->account()->info()->printHtml()) + "<h5>Visit Count</h5><p> %1").arg((*it)->visitCount());
            _display->setHtml(output);
            QString title = QString(QString::fromStdString((*it)->account()->username().login()));
            _display->setDocumentTitle(title);
        }
}
// Gui_ViewContact::Gui_ViewContact(LinqClient* client, Gui_DisplayInfo* disp, const QString& view, QWidget* parent) : _display(disp), _toView(view), QVBoxLayout(parent) {
//     disp->setHtml(QString::fromStdString(client->find(view.toStdString())));
// }