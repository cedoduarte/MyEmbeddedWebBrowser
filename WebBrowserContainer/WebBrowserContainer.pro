QT += core
QT += gui
QT += widgets
QT += network

CONFIG += c++11

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    myembeddedwidget.cpp \
    myembeddedwindow.cpp \
    myembeddedwindowprocess.cpp \
    mytcpserver.cpp

HEADERS += \
    mainwindow.h \
    myembeddedwidget.h \
    myembeddedwindow.h \
    myembeddedwindowprocess.h \
    mytcpserver.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
