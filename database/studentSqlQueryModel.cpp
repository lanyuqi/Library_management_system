//
// Created by 洛青宇 on 2023/4/16.
//

#include "studentSqlQueryModel.h"

studentSqlQueryModel::studentSqlQueryModel(QObject *parent) : QSqlQueryModel(parent) {
}

void studentSqlQueryModel::setModel(int tableIndex) {
    QSqlQuery query;

    switch (tableIndex) {
        case 1:
            query.prepare("SELECT * FROM students");
            headerList = {"ID", "学号", "姓名", "密码", "邮箱", "手机号码"};
            break;
        case 2:
            query.prepare("SELECT * FROM books");
            headerList = {"ID", "书名", "ISBN", "作者", "出版社", "借阅次数"};
            break;
        case 3:
            query.prepare("SELECT * FROM loans");
            headerList = {"ID", "ISBN", "学号", "借阅时间", "归还时间","借阅姓名"};
            break;
            default:
                return;
    }
    if (!query.exec()) {
        qDebug() << "Error: Cannot execute query." << query.lastError();
        return;
    }

    setQuery(std::move(query)); // 使用移动语义调用setQuery
}

QString studentSqlQueryModel::getColumnCount(const QString &tableName,const QString &columName) {
    QSqlQuery query;
    query.prepare(QString("SELECT COUNT(%1) FROM %2").arg(columName, tableName));

    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        return QString::number(count) ;
    } else {
        // 查询执行失败或无法检索结果时返回-1
        QString i;
        return i="错误";
    }
}

QString studentSqlQueryModel::getOverdueCount(const QString &tableName, const QString &returnDateColumn,
                                              const QString &borrowDateColumn) {
    int count = 0;
    QSqlQuery query;
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentDateStr = currentDateTime.toString("yyyy-MM-dd");

    query.prepare(QString(
            "SELECT COUNT(*) FROM %1 WHERE DATEDIFF(%2, %3) > 0 AND %2 < :currentDate").arg(
                    tableName, returnDateColumn, borrowDateColumn));
    query.bindValue(":currentDate", currentDateStr);

    if (query.exec()) {
        if (query.next()) {
            count = query.value(0).toInt();
        }
    } else {
        qDebug() << "Error:" << query.lastError().text();
    }

    return QString::number(count);
}

bool studentSqlQueryModel::updateStudent(QString &student_number, QString &name, QString &password, QString &email,
                                         QString &phone) {
    QSqlQuery query;
    query.prepare("UPDATE students SET name = :name, password = :password, email = :email, phone = :phone "
                  "WHERE student_number = :student_number");
    query.bindValue(":name", name);
    query.bindValue(":password", password);
    query.bindValue(":email", email);
    query.bindValue(":phone", phone);
    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Error:" << query.lastError().text();
        return false;
    }

}

QVariant studentSqlQueryModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return headerList.value(section);
    };

    return QSqlQueryModel::headerData(section, orientation, role);
};