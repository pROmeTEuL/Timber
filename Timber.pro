TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
S
SOURCES += \
        cloud.cpp \
        main.cpp

DISTFILES += \
    fonts/KOMIKAP_.ttf \
    graphics/axe.png \
    graphics/background.png \
    graphics/bee.png \
    graphics/branch.png \
    graphics/cloud.png \
    graphics/log.png \
    graphics/player.png \
    graphics/rip.png \
    graphics/tree.png \
    graphics/tree2.png \
    sound/chop.wav \
    sound/death.wav \
    sound/out_of_time.wav

HEADERS += \
    cloud.h
