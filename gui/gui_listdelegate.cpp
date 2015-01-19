#include "gui_listdelegate.h"

ListDelegate::ListDelegate(QObject* parent) {}

void ListDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const {
    QRect r = option.rect;
    //Color: #C4C4C4
    QPen linePen(QColor::fromRgb(0,0,0), 1, Qt::SolidLine);
    //Color: #005A83
    QPen lineMarkedPen(QColor::fromRgb(0,0,0), 1, Qt::SolidLine);
    //Color: #333
    QPen fontPen(QColor::fromRgb(255,255,255), 1, Qt::SolidLine);
    //Color: #fff
    QPen fontMarkedPen(Qt::white, 1, Qt::SolidLine);

    if(option.state & QStyle::State_Selected) {
        QLinearGradient gradientSelected(r.left(),r.top(),r.left(),r.height()+r.top());
        gradientSelected.setColorAt(0.0, QColor::fromRgb(0,0,0));
        gradientSelected.setColorAt(0.9, QColor::fromRgb(66,100,80));
        gradientSelected.setColorAt(1.0, QColor::fromRgb(0,0,0));
        painter->setBrush(gradientSelected);
        painter->drawRect(r);

        //BORDER
        painter->setPen(lineMarkedPen);
        painter->drawLine(r.topLeft(),r.topRight());
        painter->drawLine(r.topRight(),r.bottomRight());
        painter->drawLine(r.bottomLeft(),r.bottomRight());
        painter->drawLine(r.topLeft(),r.bottomLeft());

        painter->setPen(fontMarkedPen);
    }
    else {
        //BACKGROUND
        //ALTERNATING COLORS
        painter->setBrush(QColor(23,23,23));
        painter->drawRect(r);

        //BORDER
        painter->setPen(linePen);
        painter->drawLine(r.topLeft(),r.topRight());
        painter->drawLine(r.topRight(),r.bottomRight());
        painter->drawLine(r.bottomLeft(),r.bottomRight());
        painter->drawLine(r.topLeft(),r.bottomLeft());

        painter->setPen(fontPen);
    }

    //GET TITLE, DESCRIPTION AND ICON
    QIcon ic = QIcon(qvariant_cast<QPixmap>(index.data(Qt::DecorationRole)));
    QString title = index.data(Qt::DisplayRole).toString();
    QString description = index.data(Qt::UserRole + 1).toString();
    bool read = index.data(Qt::UserRole + 3).toBool();

    int imageSpace = 10;
    if (!ic.isNull()) {
        //ICON
        r = option.rect.adjusted(5, 10, -10, -10);
        ic.paint(painter, r, Qt::AlignVCenter|Qt::AlignLeft);
        imageSpace = 55;
    }

    QFont font;
    font.setBold(true);

    //TITLE
    r = option.rect.adjusted(imageSpace, 0, -10, -30);
    if(!read) painter->setFont(font);
    // painter->setFont(QFont("Lucida Grande", 12, QFont::Bold));
    painter->drawText(r.left(), r.top(), r.width(), r.height(), Qt::AlignBottom|Qt::AlignLeft, title, &r);

    //DESCRIPTION
    r = option.rect.adjusted(imageSpace, 20, -10, 0);
    font.setBold(false);
    painter->setFont(font);
    // painter->setFont(QFont("Lucida Grande", 8, QFont::Normal));
    painter->drawText(r.left(), r.top(), r.width(), r.height(), Qt::AlignLeft, description, &r);
}

QSize ListDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const {
    return QSize(80, 50); // very dumb value
}

ListDelegate::~ListDelegate() {}