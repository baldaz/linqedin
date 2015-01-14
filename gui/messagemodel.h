#ifndef MESSAGEMODEL_H
#define MESSAGEMODEL_H

#include <QAbstractTableModel>
#include <QString>

const int COLS= 3;
const int ROWS= 2;

class MessageModel : public QAbstractTableModel {
    Q_OBJECT
public:
    MessageModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int, Qt::Orientation, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex&, const QVariant&, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex & index) const;
private:
    QString m_gridData[ROWS][COLS];
signals:
    void editCompleted(const QString &);
};
#endif