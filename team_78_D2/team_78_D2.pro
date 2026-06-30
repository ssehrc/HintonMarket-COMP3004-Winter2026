QT       += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BookingsWindow.cpp \
    MarketBrowserWindow.cpp \
    MarketController.cpp \
    MarketOpDashboard.cpp \
    Repository.cpp \
    VendorDashboardWindow.cpp \
    WaitlistController.cpp \
    WaitlistsWindow.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Booking.h \
    BookingsWindow.h \
    MarketBrowserWindow.h \
    MarketController.h \
    MarketDate.h \
    MarketOpDashboard.h \
    MarketOperator.h \
    Repository.h \
    Vendor.h \
    VendorDashboardWindow.h \
    Waitlist.h \
    WaitlistController.h \
    WaitlistsWindow.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md \
    database.sql

# Always copy the latest database to the build directory before build
copydb.commands = cp -f $$PWD/marketplace.db $$OUT_PWD/
QMAKE_EXTRA_TARGETS += copydb
PRE_TARGETDEPS += copydb
