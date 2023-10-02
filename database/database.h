//
// Created by 洛青宇 on 2023/4/7.
//

#ifndef LIBRARY_MANAGEMENT_SYSTEM_DATABASE_H
#define LIBRARY_MANAGEMENT_SYSTEM_DATABASE_H

#include <QWidget>
#include <QSqlDatabase>


QT_BEGIN_NAMESPACE
namespace Ui { class Database; }
QT_END_NAMESPACE

class Database : public QWidget {
Q_OBJECT

public:
    explicit Database(QWidget *parent = nullptr);
    bool isConnect();
    QSqlDatabase getDatabase();

    ~Database() override;

private:
    Ui::Database *ui;
    QSqlDatabase db;
};


#endif //LIBRARY_MANAGEMENT_SYSTEM_DATABASE_H
