//
// Created by 洛青宇 on 2023/4/5.
//

#ifndef LIBRARY_MANAGEMENT_SYSTEM_LOGIN_AD_H
#define LIBRARY_MANAGEMENT_SYSTEM_LOGIN_AD_H

#include <QWidget>
#include "../database/database.h"
#include "admin_main.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Login_ad; }
QT_END_NAMESPACE

class Login_ad : public QWidget {
Q_OBJECT

signals:
    void userLogin(QString &user_name, QString &pass_word);

public:
    explicit Login_ad(QWidget *parent = nullptr);
    void on_loginButton_clicked();

    ~Login_ad() override;

private:
    Ui::Login_ad *ui;
    Database *db;
    QString username;
    QString password;
};


#endif //LIBRARY_MANAGEMENT_SYSTEM_LOGIN_AD_H
