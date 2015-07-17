TEMPLATE = subdirs

SUBDIRS += \
    app \
    libs \
    benchmarks \
    tests


app.depends = libs
