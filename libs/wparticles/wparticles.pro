TEMPLATE = lib
CONFIG += static c++11
CONFIG -= app_bundle qt

SOURCES += \
    Particle.cpp \
    Space.cpp \
    UniformParticleGenerator.cpp \
    Octree.cpp

HEADERS += \
    Particle.h \
    Space.h \
    ParticleGenerator.h \
    UniformParticleGenerator.h \
    Octree.h


INCLUDEPATH += ../
