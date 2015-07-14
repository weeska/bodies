TEMPLATE = lib
CONFIG += static c++11
CONFIG -= app_bundle qt

SOURCES += \
    Attraction.cpp \
    AttractionToParticle.cpp \
    Particle.cpp \
    Space.cpp

HEADERS += \
    Attraction.h \
    AttractionToParticle.h \
    Force.h \
    Particle.h \
    Space.h


INCLUDEPATH += ../
