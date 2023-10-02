//
// Created by 洛青宇 on 2023/4/5.
//

#ifndef LIBRARY_MANAGEMENT_SYSTEM_LOGIN_ST_H
#define LIBRARY_MANAGEMENT_SYSTEM_LOGIN_ST_H

#include <QWidget>
#include "../database/database.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Login_st; }
QT_END_NAMESPACE

class Login_st : public QWidget {
Q_OBJECT

public:
    explicit Login_st(QWidget *parent = nullptr);
    void on_loginButton_clicked();
    ~Login_st() override;
signals:
    void userLogin(QString &user_name, QString &pass_word);

private:
    Ui::Login_st *ui;
    Database *db;
    QString username;
    QString password;
};


#endif //LIBRARY_MANAGEMENT_SYSTEM_LOGIN_ST_H
