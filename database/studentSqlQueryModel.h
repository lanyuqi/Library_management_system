//
// Created by 洛青宇 on 2023/4/16.
//

#ifndef LIBRARY_MANAGEMENT_SYSTEM_STUDENTSQLQUERYMODEL_H
#define LIBRARY_MANAGEMENT_SYSTEM_STUDENTSQLQUERYMODEL_H

#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QtSql/QSqlQueryModel>

class studentSqlQueryModel : public QSqlQueryModel {
    Q_OBJECT
public:
    studentSqlQueryModel(QObject *parent = nullptr);
    void setModel(int tableIndex);
    QString getColumnCount(const QString &tableName,const QString &columName);
    QString getOverdueCount(const QString &tableName, const QString &returnDateColumn, const QString &borrowDateColumn);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool updateStudent(QString &student_number,QString &name,QString &password, QString &email, QString &phone);
private:
    QStringList headerList;
};


#endif //LIBRARY_MANAGEMENT_SYSTEM_STUDENTSQLQUERYMODEL_H
