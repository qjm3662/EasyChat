#-------------------------------------------------
#
# Project created by QtCreator 2016-07-11T13:54:57
#
#-------------------------------------------------

QT       += core gui
QT += sql
QT +=network

TARGET = EasyChat
TEMPLATE = app


SOURCES += main.cpp\
    login.cpp \
    register.cpp \
    ChatView.cpp \
    critem.cpp \
    user.cpp \
    cr.cpp \
    chatdb.cpp \
    client/client.cpp \
    connext.cpp \
    client/clientstic.cpp \
    FriendListItem.cpp \
    MainUI/GroupChat.cpp \
    MainUI/MainUI.cpp \
    MainUI/mainitem.cpp

HEADERS  += \
    login.h \
    register.h \
    ChatView.h \
    critem.h \
    user.h \
    cr.h \
    chatdb.h \
    client/client.h \
    connext.h \
    client/clientstic.h \
    FriendListItem.h \
    MainUI/GroupChat.h \
    MainUI/MainUI.h \
    MainUI/mainitem.h

FORMS    +=  \
    login.ui \
    register.ui \
    ChatView.ui \
    critem.ui \
    connext.ui \
    FriendListItem.ui \
    MainUI/GroupChat.ui \
    MainUI/MainUI.ui \
    MainUI/mainitem.ui

RESOURCES += \
    src.qrc
