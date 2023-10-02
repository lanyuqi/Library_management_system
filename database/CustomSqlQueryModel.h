//
// Created by 洛青宇 on 2023/4/14.
//

#ifndef LIBRARY_MANAGEMENT_SYSTEM_CUSTOMSQLQUERYMODEL_H
#define LIBRARY_MANAGEMENT_SYSTEM_CUSTOMSQLQUERYMODEL_H

#include <QSqlQueryModel>


class CustomSqlQueryModel : public QSqlQueryModel {
    Q_OBJECT
public:
    CustomSqlQueryModel(QObject *parent = nullptr);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};


#endif //LIBRARY_MANAGEMENT_SYSTEM_CUSTOMSQLQUERYMODEL_H
