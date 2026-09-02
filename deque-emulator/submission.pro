QT += core gui widgets

CONFIG += c++20

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    algo.h \
    mainwindow.h \
    model.h

FORMS += \
    mainwindow.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
