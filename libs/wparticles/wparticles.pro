TEMPLATE = lib
CONFIG += static c++11
CONFIG -= app_bundle qt

SOURCES += \
    Space.cpp \
    UniformParticleGenerator.cpp

HEADERS += \
    Space.h \
    ParticleGenerator.h \
    UniformParticleGenerator.h


INCLUDEPATH += ../
