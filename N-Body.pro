TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

include("paths.pri")

INCLUDEPATH += $$SFML_PATH/include

LIBS += -L$$SFML_PATH/lib

LIBS += -lsfml-main-d
LIBS += -lsfml-graphics-d
LIBS += -lsfml-system-d
LIBS += -lsfml-window-d
LIBS += -lopengl32

SOURCES += main.cpp \
    Math/Vector3D.cpp \
    Space.cpp \
    Particle.cpp \
    Attraction.cpp \

HEADERS += \
    Math/Vector3D.h \
    Space.h \
    Particle.h \
    Force.h \
    Attraction.h \

