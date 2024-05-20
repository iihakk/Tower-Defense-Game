QT       += core
QT       += multimedia
QT       += gui
QT       += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bullet.cpp \
    cannonbullet.cpp \
    cannontower.cpp \
    enemy.cpp \
    gamecontroller.cpp \
    infernobullet.cpp \
    infernotower.cpp \
    main.cpp \
    map.cpp \
    help.cpp \
    shop.cpp \
    startmenu.cpp \
    teslabullet.cpp \
    teslatower.cpp \
    tower.cpp \
    xbowbullet.cpp \
    xbowtower.cpp

HEADERS += \
    bullet.h \
    cannonbullet.h \
    cannontower.h \
    enemy.h \
    gamecontroller.h \
    infernobullet.h \
    infernotower.h \
    map.h \
    help.h \
    shop.h \
    startmenu.h \
    teslabullet.h \
    teslatower.h \
    tower.h \
    xbowbullet.h \
    xbowtower.h

FORMS += \
    help.ui \
    shop.ui \
    startmenu.ui

RESOURCES += \
    Images.qrc \
    Sounds.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
