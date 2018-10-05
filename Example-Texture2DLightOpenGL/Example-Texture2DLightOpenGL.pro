TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += opengl

SOURCES += \
        main.cpp

LIBS += -lglut

HEADERS += \
    stb_image.h
