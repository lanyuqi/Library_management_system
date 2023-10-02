//
// Created by 洛青宇 on 2023/4/5.
//

#ifndef LIBRARY_MANAGEMENT_SYSTEM_LIBRARY_LOGIN_H
#define LIBRARY_MANAGEMENT_SYSTEM_LIBRARY_LOGIN_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class Library_Login; }
QT_END_NAMESPACE

class Library_Login : public QMainWindow {
Q_OBJECT

public:
    explicit Library_Login(QWidget *parent = nullptr);

    ~Library_Login() override;

private:
    Ui::Library_Login *ui;
};


#endif //LIBRARY_MANAGEMENT_SYSTEM_LIBRARY_LOGIN_H
