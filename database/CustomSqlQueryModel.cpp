//
// Created by 洛青宇 on 2023/4/14.
//

#include "CustomSqlQueryModel.h"

CustomSqlQueryModel::CustomSqlQueryModel(QObject *parent) : QSqlQueryModel(parent) {}

QVariant CustomSqlQueryModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return QStringLiteral("ID");
            case 1:
                return QStringLiteral("书名");
            case 2:
                return QStringLiteral("ISBN");
            case 3:
                return QStringLiteral("作者");
            case 4:
                return QStringLiteral("出版社");
            case 5:
                return QStringLiteral("借阅次数");

            default:
                break;
        }
    }

    return QSqlQueryModel::headerData(section, orientation, role);
}
