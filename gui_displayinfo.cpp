#include "gui_displayinfo.h"

Gui_DisplayInfo::Gui_DisplayInfo(const LinqClient& client) : QGroupBox(tr("User info"), parent) {
    client
}