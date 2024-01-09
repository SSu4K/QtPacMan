QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    game.cpp \
    ghost.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    pacman.cpp \
    pathfindingsprite.cpp \
    sprite.cpp \
    spritesheetreader.cpp

HEADERS += \
    game.h \
    ghost.h \
    mainwindow.h \
    map.h \
    pacman.h \
    pathfindingsprite.h \
    sprite.h \
    spritesheetreader.h \
    spritesheetreader.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    README.md \
    assets/map.png \
    assets/map_layout.txt \
    assets/sprites.png
