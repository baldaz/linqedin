#include "gui_statistics.h"

Gui_Statistics::Gui_Statistics(LinqClient* cli, QWidget* parent) : _client(cli), QGridLayout(parent) {
    Gui_Avatar* avatar = new Gui_Avatar(QString::fromStdString(_client->avatar()));
    QTextBrowser* keywords = new QTextBrowser(parent);
    QGridLayout* frm = new QGridLayout;
    keywords->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

    _list = new QTextBrowser(parent);
    // _list->setEnabled(true);
    _list->setStyleSheet("background:#000");
    vector<SmartPtr<Payment> > hist = _client->paymentHistory();
    QString content = QString("<h2>Payments History</h2>");
    content.append("<table border=0 cellspacing='15' width='80\%'><tr><th align=center>Date</th><th align=center>Expiration</th><th align=center>Level</th><th align=center>Status</th></tr>");
    QString lvl, status;
    for(vector<SmartPtr<Payment> >::iterator i = hist.begin(); i != hist.end(); ++i) {
        if(_client->level() == basic) lvl = "Basic";
        else if (_client->level() == business) lvl = "Business";
        else lvl = "Executive";
        bool appr = (*i)->approvation();
        if(!appr) status = "Pending";
        else {
            if((*i)->appDate().addDays(30) < QDate::currentDate())
                status = "Expired";
            else status = "Approved";
        }
        content.append("<tr><td style='font-weight:400' align=center>" + (*i)->appDate().toString() + "</td><td style='font-weight:400' align=center>" + (*i)->appDate().addDays(30).toString() + "</td><td style='font-weight:400' align=center>" + lvl + "</td><td style='font-weight:400' align=center>" + status + "</td></tr>");
    }
    content.append("</table>");
    _list->setHtml(content);
    QString html = QString("<h2>Mail sent this month</h2>");
    int limit = _client->outMailLimit();
    int count = _client->outMailCount();
    if(limit == -1) html += QString("%1 / unlimited").arg(count);
    else html += QString("%1 / %2").arg(count).arg(limit);
    html += "<span style='font-weight:400'> mail sent.</span>";
    map<string, int> keys = _client->keywordFrequency();
    map<string, int>::iterator it = keys.begin();
    html += QString("<h2>Keywords frequency</h2>");
    if(!keys.empty())
        for(; it != keys.end(); ++it)
            html.append(QString("<span style='font-weight:700'>" + QString::fromStdString(it->first) + ":</span>&nbsp;<span style='font-weight:400'>%1 \%</span>&nbsp;&nbsp;&nbsp;").arg(it->second));
    html.append(QString("<h2>Visit received</h2> <span style='font-weight:700'> Total:</span>&nbsp;<span style='font-weight:400'> %1</span>").arg(_client->visitCount()));
    list<SmartPtr<User> > u = _client->visitors();
    html.append(QString("<h2>Last 10 visitors</h2><ul>"));
    UserInfo* i;
    for(list<SmartPtr<User> >::iterator itr = u.begin(); itr != u.end(); ++itr) {
        i = dynamic_cast<UserInfo*> ((*itr)->account()->info());
        bool linked = _client->linked((*itr)->account()->username());
        QString lnk;
        if(linked) lnk = "linked";
        else lnk = "unlinked";
        html.append(QString("<li><span style='font-weight:400'>" + QString::fromStdString(i->name()) + " " + QString::fromStdString(i->surname()) + "</span><span style='font-weight:400; color:#666'> (" + QString::fromStdString((*itr)->account()->username().login()) + ")</span><span style='font-weight:400'> %1 years old, " + lnk + "</span></li>").arg(i->age()));
    }
    html.append("</ul>");
    keywords->setHtml(html);

    frm->addWidget(keywords, 0, 0, -1, -1);
    addWidget(avatar, 0, 0, 1, 1, Qt::AlignTop);
    addWidget(_list, 0, 1, 1, -1);
    addLayout(frm, 1, 0, -1, -1);
    setColumnStretch(0, 1);
    setColumnStretch(1, 2);
    setColumnStretch(2, 4);
    setRowStretch(0, 0);
    setRowStretch(1, 10);
}