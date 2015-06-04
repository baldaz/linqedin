#include <QPainter>
#include <QAbstractItemDelegate>

class ListDelegate : public QAbstractItemDelegate {
public:
    ListDelegate(QObject *parent = 0);
    void paint ( QPainter*, const QStyleOptionViewItem&, const QModelIndex&) const;
    QSize sizeHint ( const QStyleOptionViewItem&, const QModelIndex&) const;
    virtual ~ListDelegate();
};
