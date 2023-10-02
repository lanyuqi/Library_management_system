//
// Created by 洛青宇 on 2023/4/18.
//

#include "StudentSqlModel.h"
StudentSqlModel::StudentSqlModel(QObject *parent) : QSqlQueryModel(parent) {


}


QString StudentSqlModel::queryDataByUsername(const QString &tableName, const QString &usernameColumn,
                                          const QString &username) {
    QSqlQuery query;
    query.prepare(QString("SELECT * FROM %1 WHERE %2 = :username").arg(tableName, usernameColumn));
    query.bindValue(":username", username);

    int count = 0;
    if(query.exec()&&query.next()){
        count = query.value(0).toInt();
    }else{
        qDebug() << "Error: Cannot execute query." << query.lastError().text();
    }
    return QString::number(count);

}
QString StudentSqlModel::getOverdueCount(const QString &tableName, const QString &returnDateColumn,
                                      const QString &borrowDateColumn,const QString &username) {
    int count = 0;
    QSqlQuery query;
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentDateStr = currentDateTime.toString("yyyy-MM-dd");


    query.prepare(QString(
            "SELECT COUNT(*) FROM %1 WHERE DATEDIFF(%2, %3) > 0 AND %2 < :currentDate AND %4 = :username").arg(
            tableName, returnDateColumn, borrowDateColumn, username));
    query.bindValue(":currentDate", currentDateStr);
    query.bindValue(":username", username);

    if (query.exec()) {
        if (query.next()) {
            count = query.value(0).toInt();
        }
    } else {
        qDebug() << "Error:" << query.lastError().text();
    }
    return QString::number(count);
}

QString StudentSqlModel::getUser(const QString &tablename,const QString ColumnName, const QString &username) {
    QSqlQuery query;
    QString user;
    query.prepare(QString("SELECT * FROM %1 WHERE %2 = :username").arg(tablename, username));
    query.bindValue(":username", username);
    if(query.exec() && query.next()){
        user = query.value(2).toString();
    }else{
        qDebug() << "Error: Cannot execute query." << query.lastError().text();
    }
    return user;
}

void StudentSqlModel::studentdata_loans(const QString &tablename, const QString &columName, const QString &username) {
    QSqlQuery query;
    query.prepare(QString("SELECT * FROM %1 WHERE %2 = :username").arg(tablename, columName));
    query.bindValue(":username", username);
    if(query.exec()){
        this->setQuery(std::move(query));
    }else{
        qDebug() << "Error: Cannot execute query." << query.lastError().text();
    }
}
