#include "messagemodel.h"

MessageModel::MessageModel(QObject *parent) : QAbstractTableModel(parent) { }
int MessageModel::rowCount(const QModelIndex & /*parent*/) const { return 2; }
int MessageModel::columnCount(const QModelIndex & /*parent*/) const { return 3;}
QVariant MessageModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        return QString("Message %1")
                    .arg(index.row() + 1);
    }
    return QVariant();
}
QVariant MessageModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0:
                return QString("Title");
            case 1:
                return QString("From");
            case 2:
                return QString("Object");
            }
        }
    }
    return QVariant();
}

bool MessageModel::setData(const QModelIndex & index, const QVariant & value, int role) {
    if (role == Qt::EditRole) {
        //save value from editor to member m_gridData
        m_gridData[index.row()][index.column()] = value.toString();
        //for presentation purposes only: build and emit a joined string
        QString result;
        for(int row= 0; row < ROWS; row++) {
            for(int col= 0; col < COLS; col++) {
                result += m_gridData[row][col] + " ";
            }
        }
        emit editCompleted(result);
    }
    return true;
}

Qt::ItemFlags MessageModel::flags(const QModelIndex & /*index*/) const {
    return Qt::ItemIsSelectable |  Qt::ItemIsEditable | Qt::ItemIsEnabled;
}