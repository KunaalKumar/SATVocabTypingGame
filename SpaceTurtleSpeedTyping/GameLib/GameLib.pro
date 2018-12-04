#-------------------------------------------------
#
# Project created by QtCreator 2018-11-20T13:15:31
#
#-------------------------------------------------

QT       += gui

TARGET = GameLib
TEMPLATE = lib

DEFINES += GAMELIB_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        gamelib.cpp \
    enemy.cpp \
    player.cpp \
    projectile.cpp \
    objectcontroller.cpp \
    stats.cpp \
    loadwords.cpp \
    explosion.cpp \
    gamelib_global.cpp

HEADERS += \
        gamelib.h \
    enemy.h \
    player.h \
    projectile.h \
    gameobjects.h \
    stats.h \
    objectcontroller.h \
    loadwords.h \
    explosion.h \
    gamelib_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    ../src/src.qrc

unix:!macx: LIBS += -L$$PWD/../3rdPartyLibraries/Box2D/lib/linux/ -lBox2D

INCLUDEPATH += $$PWD/../3rdPartyLibraries/Box2D/include
DEPENDPATH += $$PWD/../3rdPartyLibraries/Box2D/include

unix:!macx: PRE_TARGETDEPS += $$PWD/../3rdPartyLibraries/Box2D/lib/linux/libBox2D.a

macx: LIBS += -L$$PWD/../3rdPartyLibraries/Box2D/lib/osx/ -lBox2D

INCLUDEPATH += $$PWD/../3rdPartyLibraries/Box2D/include
DEPENDPATH += $$PWD/../3rdPartyLibraries/Box2D/include

macx: PRE_TARGETDEPS += $$PWD/../3rdPartyLibraries/Box2D/lib/osx/libBox2D.a
