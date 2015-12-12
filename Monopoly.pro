#-------------------------------------------------
#
# Project created by QtCreator 2010-12-31T11:15:11
#
#-------------------------------------------------

QT += widgets

TARGET = Monopoly
TEMPLATE = app
CONFIG += c++11 -static -static-libstdc++

SOURCES += main.cpp\
        Widget.cpp \
    UI/GameStart.cpp \
    UI/GameRoom.cpp \
    UI/GameScene.cpp \
    UI/Scene.cpp \
    UI/BasicSceneBlock.cpp \
    UI/ActionButton.cpp \
    UI/GameEnd.cpp \
    Monopoly/MapProperty.cpp \
    Monopoly/Map.cpp \
    Monopoly/WorldMap.cpp \
    Monopoly/Player.cpp \
    Monopoly/WorldPlayer.cpp \
    Monopoly/BuyableMap.cpp \
    Monopoly/UnbuyableMap.cpp \
    Monopoly/UpgradableMap.cpp \
    Monopoly/CollectableMap.cpp \
    Monopoly/RandomCostMap.cpp \
    Monopoly/PrisonMap.cpp

HEADERS  += Widget.h \
    UI/GameStart.h \
    UI/GameRoom.h \
    UI/GameScene.h \
    UI/Scene.h \
    UI/BasicSceneBlock.h \
    UI/ActionButton.h \
    UI/GameEnd.h \
    Monopoly/GameConstant.h \
    Monopoly/MapProperty.h \
    Monopoly/Map.h \
    Monopoly/WorldMap.h \
    Monopoly/Player.h \
    Monopoly/WorldPlayer.h \
    Monopoly/UpgradableMap.h \
    Monopoly/UnbuyableMap.h \
    Monopoly/RandomCostMap.h \
    Monopoly/PrisonMap.h \
    Monopoly/CollectableMap.h \
    Monopoly/BuyableMap.h

DISTFILES += \
    map.dat
