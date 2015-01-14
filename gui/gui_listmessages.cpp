#include "gui_listmessages.h"

Gui_ListMessages::Gui_ListMessages(QWidget* parent) : QTableView(parent) {
    MessageModel* model = new MessageModel;
    // model->setHeaderData(0, Qt::Horizontal, "ID");
    // model->setHeaderData(1, Qt::Horizontal, "Name");
    // model->setHeaderData(2, Qt::Horizontal, "City");
    // model->setHeaderData(3, Qt::Horizontal, "Country");
    setModel(model);
    setShowGrid(false);
    setColumnWidth(0, 150);
    setColumnWidth(1, 200);
    setColumnWidth(2, 200);
    show();
    // setEditTriggers(QAbstractItemView::NoEditTriggers);
}