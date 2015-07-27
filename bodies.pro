TEMPLATE = subdirs

SUBDIRS += \
    app \
    libs \
    benchmarks \
    tests


app.depends = libs
benchmarks.depends = libs
tests.depends = libs
