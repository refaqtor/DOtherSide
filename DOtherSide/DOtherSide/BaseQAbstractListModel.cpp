#include "BaseQAbstractListModel.h"

BaseQAbstractListModel::BaseQAbstractListModel(void* modelObject,
        RowCountCallback rowCountCallback,
        DataCallback dataCallback,
        RoleNamesCallback roleNamesCallback)
    : m_modelObject(modelObject)
    , m_rowCountCallback(rowCountCallback)
    , m_dataCallback(dataCallback)
    , m_roleNamesCallback(roleNamesCallback)
{
}

int BaseQAbstractListModel::rowCount(const QModelIndex& index) const
{
    auto newIndex = new QModelIndex();
    *newIndex = index;
    int result;
    m_rowCountCallback(m_modelObject, newIndex, &result);
    return result;
}

QVariant BaseQAbstractListModel::data(const QModelIndex& index, int role) const
{
    auto newIndex = new QModelIndex();
    *newIndex = index;
    QVariant result;
    m_dataCallback(m_modelObject, newIndex, role, &result);
    return result;
}

void* BaseQAbstractListModel::modelObject()
{
    return m_modelObject;
}

QHash<int, QByteArray> BaseQAbstractListModel::roleNames() const
{
    QHash<int, QByteArray> result;
    m_roleNamesCallback(m_modelObject, &result);
    return result;
}

void BaseQAbstractListModel::publicBeginInsertRows(const QModelIndex& index, int first, int last)
{
    beginInsertRows(index, first, last);
}

void BaseQAbstractListModel::publicEndInsertRows()
{
    return endInsertRows();
}

void BaseQAbstractListModel::publicBeginResetModel()
{
    beginResetModel();
}

void BaseQAbstractListModel::publicEndResetModel()
{
    endResetModel();
}

void BaseQAbstractListModel::publicDataChanged(const QModelIndex& topLeft,
                                               const QModelIndex& bottomRight,
                                               const QVector<int>& roles)
{
    emit dataChanged(topLeft, bottomRight, roles);
}



