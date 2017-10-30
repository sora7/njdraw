TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    src/main.cpp

win32 {
    INCLUDEPATH += $$PWD/SDL/include/

    LIBS += -L$$PWD/SDL/lib -lmingw32 -lSDL2main -lSDL2
    DEPENDPATH += $$PWD/SDL/bin/SDL2.dll
#    QMAKE_LFLAGS += -shared
#    QMAKE_LFLAGS += -mwindows
}
