//
// Created by 洛青宇 on 2023/4/18.
//

#ifndef LIBRARY_MANAGEMENT_SYSTEM_STUDENTSQLMODEL_H
#define LIBRARY_MANAGEMENT_SYSTEM_STUDENTSQLMODEL_H


#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>


class StudentSqlModel: public QSqlQueryModel{
    Q_OBJECT
public:
    StudentSqlModel(QObject *parent = nullptr) ;
    QString queryDataByUsername(const QString &tableName, const QString &usernameColumn,
                                const QString &username);
    QString getOverdueCount(const QString &tableName, const QString &returnDateColumn,
                            const QString &borrowDateColumn,const QString &username) ;
    QString getUser(const QString &tablename,const QString ColumnNameconst,const QString &username);
    void studentdata_loans(const QString &tablename, const QString &columName,const QString &username);
private:
};


#endif //LIBRARY_MANAGEMENT_SYSTEM_STUDENTSQLMODEL_H
