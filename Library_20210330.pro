QT       += core gui multimedia multimediawidgets
QT       += charts
QT       += sql
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

INCLUDEPATH += D:\Zbar\include
INCLUDEPATH += D:\Opencv4.5.1-x64\include

LIBS += D:\ZBar\lib\libzbar64-0.lib
LIBS += D:\Opencv4.5.1-x64\x64\mingw\bin\libopencv_*.dll

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Applications/admin_widget.cpp \
    Applications/login_widget.cpp \
    Applications/regist_new_user.cpp \
    Applications/user_widget.cpp \
    BasicIO/Email_Sender.cpp \
    BasicIO/Insert_Book_To_DataBase.cpp \
    BasicIO/Insert_Record_To_DataBase.cpp \
    BasicIO/Insert_User_To_DataBase.cpp \
    BasicIO/Read_Book_From_ISBN_DataBase.cpp \
    BasicIO/Read_Book_From_MyLibrary.cpp \
    BasicIO/Read_Record_By_ISBN.cpp \
    BasicIO/Read_User_From_DataBase.cpp \
    DataStructure/Book.cpp \
    DataStructure/User.cpp \
    Function/Check_Functions.cpp \
    Function/Free_Fuction.cpp \
    Function/Get_ISBN_From_Camera.cpp \
    Function/add_book_widget.cpp \
    Function/borrowed_chart_widget.cpp \
    Function/change_book_info_widget.cpp \
    Function/change_password_wdiget.cpp \
    Function/change_user_info_widget.cpp \
    Function/find_password_widget.cpp \
    Initialize/DataBase_Initial.cpp \
    main.cpp

HEADERS += \
    Applications/admin_widget.h \
    Applications/login_widget.h \
    Applications/regist_new_user.h \
    Applications/user_widget.h \
    BasicIO/Email_Sender.h \
    BasicIO/Insert_Book_To_DataBase.h \
    BasicIO/Insert_Record_To_DataBase.h \
    BasicIO/Insert_User_To_DataBase.h \
    BasicIO/Read_Book_From_ISBN_DataBase.h \
    BasicIO/Read_Book_From_MyLibrary.h \
    BasicIO/Read_Record_By_ISBN.h \
    BasicIO/Read_User_From_DataBase.h \
    DataStructure/Book.h \
    DataStructure/User.h \
    Function/Check_Functions.h \
    Function/Free_Function.h \
    Function/Get_ISBN_From_Camera.h \
    Function/add_book_widget.h \
    Function/borrowed_chart_widget.h \
    Function/change_book_info_widget.h \
    Function/change_password_wdiget.h \
    Function/change_user_info_widget.h \
    Function/find_password_widget.h \
    Initialize/DataBase_Initial.h

FORMS += \
    Applications/admin_widget.ui \
    Applications/login_widget.ui \
    Applications/regist_new_user.ui \
    Applications/user_widget.ui \
    Function/add_book_widget.ui \
    Function/borrowed_chart_widget.ui \
    Function/change_book_info_widget.ui \
    Function/change_password_wdiget.ui \
    Function/change_user_info_widget.ui \
    Function/find_password_widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Images.qrc
