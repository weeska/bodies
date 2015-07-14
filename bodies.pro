TEMPLATE = subdirs

SUBDIRS += \
    app \
    libs


app.depends = libs
