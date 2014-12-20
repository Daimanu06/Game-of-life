TEMPLATE = app
CONFIG += console
CONFIG += C++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lncursesw -lpthread

SOURCES += \
    main.cpp \
    gameoflife.cpp \
    grid.cpp \
    cell.cpp \
    terminalrenderer.cpp \
    cursesrenderer.cpp

HEADERS += \
    gameoflife.h \
    grid.h \
    cell.h \
    size.h \
    renderer.h \
    terminalrenderer.h \
    cursesrenderer.h
