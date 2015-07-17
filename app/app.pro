QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = app
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp \
    SimulationView.cpp

HEADERS  += \
    SimulationView.h
FORMS    +=

INCLUDEPATH += $$PWD/../libs


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libs/wmath/release/ -lwmath
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libs/wmath/debug/ -lwmath
else:unix: LIBS += -L$$OUT_PWD/../libs/wmath/ -lwmath

DEPENDPATH += $$PWD/../libs/wmath

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libs/wmath/release/libwmath.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libs/wmath/debug/libwmath.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libs/wmath/release/wmath.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libs/wmath/debug/wmath.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../libs/wmath/libwmath.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libs/wparticles/release/ -lwparticles
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libs/wparticles/debug/ -lwparticles
else:unix: LIBS += -L$$OUT_PWD/../libs/wparticles/ -lwparticles

DEPENDPATH += $$PWD/../libs/wparticles

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libs/wparticles/release/libwparticles.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libs/wparticles/debug/libwparticles.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libs/wparticles/release/wparticles.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libs/wparticles/debug/wparticles.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../libs/wparticles/libwparticles.a
