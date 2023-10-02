#include <QApplication>
#include "database/database.h"
#include "include/library_login.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Database db;
    Library_Login library_login;
    library_login.show();
    return QApplication::exec();
}
