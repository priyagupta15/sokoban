TEMPLATE = app
TARGET = sokoban

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


SOURCES += \
    main.cpp \
    player.cpp \
    map.cpp \
    game.cpp \
    cell.cpp \
    stone.cpp

HEADERS += \
    player.h \
    map.h \
    game.h \
    cell.h \
    stone.h

RESOURCES += \
    resources.qrc
