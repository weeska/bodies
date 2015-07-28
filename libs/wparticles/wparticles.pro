TEMPLATE = lib
CONFIG += static c++11
CONFIG -= app_bundle qt

SOURCES += \
    Particle.cpp \
    Space.cpp \
    UniformParticleGenerator.cpp \
    Octree.cpp \
    SpaceAccumulator.cpp \
    BarnesHutAccumulator.cpp \
    NaiveAccumulator.cpp

HEADERS += \
    Particle.h \
    Space.h \
    ParticleGenerator.h \
    UniformParticleGenerator.h \
    Octree.h \
    SpaceAccumulator.h \
    BarnesHutAccumulator.h \
    NaiveAccumulator.h


INCLUDEPATH += ../
