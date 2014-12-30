TEMPLATE = app
TARGET = gameoflife
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
    cursesrenderer.cpp \
    controls.cpp

HEADERS += \
    gameoflife.h \
    grid.h \
    cell.h \
    size.h \
    renderer.h \
    terminalrenderer.h \
    cursesrenderer.h \
    generation.h \
    controls.h \
    actions.h \
    main.h

install_var.path = $$OUT_PWD
install_var.files += $$PWD/settings.ini
INSTALLS += install_var
