#include <QPainter>
#include <QAbstractItemDelegate>

class PaymentsDelegate : public QAbstractItemDelegate {
public:
    PaymentsDelegate(QObject *parent = 0);
    void paint ( QPainter*, const QStyleOptionViewItem&, const QModelIndex&) const;
    QSize sizeHint ( const QStyleOptionViewItem&, const QModelIndex&) const;
    virtual ~PaymentsDelegate();
};