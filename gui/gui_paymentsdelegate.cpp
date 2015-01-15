#include "gui_paymentsdelegate.h"

PaymentsDelegate::PaymentsDelegate(QObject* parent) {}

PaymentsDelegate::~PaymentsDelegate() {}

void PaymentsDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const {
    QRect r = option.rect;
    int imageSpace = 75;
    QIcon ic = QIcon(qvariant_cast<QPixmap>(index.data(Qt::DecorationRole)));
    QString dateFrom = index.data(Qt::DisplayRole).toString();
    QString dateTo = index.data(Qt::UserRole + 4).toString();
    QString description = index.data(Qt::UserRole + 1).toString();
    QString price = index.data(Qt::UserRole + 2).toString();
    QString sub = index.data(Qt::UserRole + 3).toString();

    //DATEFROM
    r = option.rect.adjusted(imageSpace, 30, 0, -10);
    painter->drawText(r.left(), r.top(), dateFrom);

    //DATETO
    r = option.rect.adjusted(imageSpace, 30, 0, -10);
    painter->drawText(r.left() + 130, r.top(), dateTo);

    //SUBSCRIPTION
    r = option.rect.adjusted(imageSpace, 30, 0, -10);
    painter->drawText(r.left() + 260, r.top(), sub);

    //PRICE
    r = option.rect.adjusted(imageSpace, 30, 0, -10);
    painter->drawText(r.left()+ 390, r.top(), price);

    //DESCRIPTION
    r = option.rect.adjusted(imageSpace, 30, 0, -10);
    painter->drawText(r.left() + 530, r.top(), description);
}

QSize PaymentsDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const {
    return QSize(50, 30); // very dumb value
}