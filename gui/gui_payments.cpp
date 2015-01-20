#include "gui_payments.h"

Gui_Payments::Gui_Payments(LinqClient* cli, QWidget* parent) : _client(cli), QGridLayout(parent) {
    Gui_Avatar* avatar = new Gui_Avatar(QString::fromStdString(_client->avatar()));

    // _list = new QListWidget;
    // _list->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum));
    // _list->setItemDelegate(new PaymentsDelegate(_list));
    // QListWidgetItem* item = new QListWidgetItem;
    // QListWidgetItem* item2 = new QListWidgetItem;
    // QListWidgetItem* item3 = new QListWidgetItem;
    // QListWidgetItem* item4 = new QListWidgetItem;
    QTextBrowser* keywords = new QTextBrowser(parent);
    // keywords->setStyleSheet("background:#0f0");
    keywords->setEnabled(false);

    // item->setData(Qt::DisplayRole, "12-12-2014");
    // item->setData(Qt::DecorationRole, QPixmap("img/envelope12.png"));
    // item->setData(Qt::UserRole + 4, "12-01-2015");
    // item->setData(Qt::UserRole + 1, "expired");
    // item->setData(Qt::UserRole + 2, "€ 29.90");
    // item->setData(Qt::UserRole + 3, "Executive");

    // item2->setData(Qt::DisplayRole, "12-09-2014");
    // item2->setData(Qt::DecorationRole, QPixmap("img/envelope12.png"));
    // item2->setData(Qt::UserRole + 4, "12-01-2015");
    // item2->setData(Qt::UserRole + 1, "expired");
    // item2->setData(Qt::UserRole + 2, "€ 29.90");
    // item2->setData(Qt::UserRole + 3, "Executive");

    // item3->setData(Qt::DisplayRole, "02-08-2014");
    // item3->setData(Qt::DecorationRole, QPixmap("img/envelope12.png"));
    // item3->setData(Qt::UserRole + 4, "12-01-2015");
    // item3->setData(Qt::UserRole + 1, "expired");
    // item3->setData(Qt::UserRole + 2, "€ 29.90");
    // item3->setData(Qt::UserRole + 3, "Executive");

    // item4->setData(Qt::DisplayRole, "12-11-2014");
    // item4->setData(Qt::DecorationRole, QPixmap("img/envelope12.png"));
    // item4->setData(Qt::UserRole + 4, "12-01-2015");
    // item4->setData(Qt::UserRole + 1, "pending");
    // item4->setData(Qt::UserRole + 2, "€ 29.90");
    // item4->setData(Qt::UserRole + 3, "Executive");

    // _list->addItem(item);
    // _list->addItem(item2);
    // _list->addItem(item3);
    // _list->addItem(item4);

    _list = new QTextBrowser(parent);
    _list->setEnabled(false);
    _list->setStyleSheet("background:#000");
    QString content = QString("<h2>Payments History</h2>");
    content.append("<table border=0 cellspacing='15' width='80\%'><tr><th align=center>Date</th><th align=center>Expiration</th><th align=center>Level</th><th align=center>Status</th></tr>");
    content.append("<tr><td style='font-weight:400' align=center>12-11-2014</td><td style='font-weight:400' align=center>12-01-2015</td><td style='font-weight:400' align=center>Executive</td><td style='font-weight:400' align=center>Expired</td></tr>");
    content.append("<tr><td style='font-weight:400' align=center>12-01-2015</td><td style='font-weight:400' align=center>12-03-2015</td><td style='font-weight:400' align=center>Executive</td><td style='font-weight:400' align=center>Pending</td></tr>");
    content.append("</table>");
    _list->setHtml(content);

    map<string, int> keys = _client->keywordFrequency();
    map<string, int>::iterator it = keys.begin();
    QString html = QString("<h2>Keywords frequency</h2>");
    if(!keys.empty())
        for(; it != keys.end(); ++it)
            html.append(QString("<span style='font-weight:700'>" + QString::fromStdString(it->first) + ":</span>&nbsp;<span style='font-weight:400'>%1 \%</span>&nbsp;&nbsp;&nbsp;").arg(it->second));
    html.append(QString("<h2>Visit received</h2> <span style='font-weight:700'> Total:</span>&nbsp;<span style='font-weight:400'> %1</span>").arg(_client->visitCount()));
    keywords->setHtml(html);

    addWidget(avatar, 0, 0, 1, 1, Qt::AlignBottom);
    // addWidget(new QLabel("parent"), 0, 1, 1, 1, Qt::AlignTop);
    addWidget(_list, 0, 1, 2, -1);
    addWidget(keywords, 2, 1, 1, -1, Qt::AlignTop);
    setColumnStretch(0, 1);
    setColumnStretch(1, 5);
    setColumnStretch(2, 2);
    setRowStretch(0, 0);
    setRowStretch(1, 0);
    setRowStretch(2, 10);
}