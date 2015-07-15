TEMPLATE = subdirs

SUBDIRS += \
    app \
    libs \
    benchmarks


app.depends = libs
