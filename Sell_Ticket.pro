QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addbus.cpp \
    bus.cpp \
    businfotable.cpp \
    buyticket.cpp \
    checkpassenger.cpp \
    deletebus.cpp \
    importfile.cpp \
    main.cpp \
    mainwindow.cpp \
    passenger.cpp \
    returnticket.cpp \
    savejson.cpp \
    searchinfo.cpp

HEADERS += \
    addbus.h \
    bus.h \
    businfotable.h \
    buyticket.h \
    checkpassenger.h \
    deletebus.h \
    importfile.h \
    mainwindow.h \
    passenger.h \
    returnticket.h \
    savejson.h \
    searchinfo.h

FORMS += \
    addbus.ui \
    buyticket.ui \
    checkpassenger.ui \
    deletebus.ui \
    mainwindow.ui \
    returnticket.ui \
    searchinfo.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Icons.qrc
