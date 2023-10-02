cmake_minimum_required(VERSION 3.22)
project(Library_management_system)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/opt/homebrew/Cellar/qt/6.2.3_1")

find_package(Qt6 COMPONENTS
        Sql
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(Library_management_system
        main.cpp
        Resource/res.qrc
        src/library_login.cpp
        include/library_login.h
        src/library_login.ui
        src/login_ad.cpp
        include/login_ad.h
        src/login_ad.ui
        src/login_st.cpp
        include/login_st.h
        src/login_st.ui
        src/stu_main.cpp
        include/stu_main.h
        src/stu_main.ui
        database/database.cpp
        database/database.h
        database/database.ui
        src/admin_main.cpp
        include/admin_main.h
        src/admin_main.ui
        database/CustomSqlQueryModel.cpp
        database/CustomSqlQueryModel.h
        database/studentSqlQueryModel.cpp
        database/studentSqlQueryModel.h
        src/addstudentdialog.cpp
        include/addstudentdialog.h
        src/addstudentdialog.ui
        src/addbookdialog.cpp
        include/addbookdialog.h
        src/addbookdialog.ui
        src/editstudentdialog.cpp
        include/editstudentdialog.h
        src/editstudentdialog.ui
        database/StudentSqlModel.cpp
        database/StudentSqlModel.h src/editbookdialog.cpp include/editbookdialog.h src/editbookidalog.ui)
target_link_libraries(Library_management_system
        Qt::Core
        Qt::Gui
        Qt::Sql
        Qt::Widgets
        )

