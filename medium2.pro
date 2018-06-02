QT += core
QT -= gui

CONFIG += c++11

TARGET = medium3
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/bin/ -lopencv_core310
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/bin/ -lopencv_core310d
else:unix: LIBS += -L$$PWD/bin/ -lopencv_core310

INCLUDEPATH += $$PWD/bin
DEPENDPATH += $$PWD/bin

INCLUDEPATH += \
         $$PWD/3rdparty \
        $$PWD/3rdparty/opencv3.1/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/bin/ -lopencv_highgui310
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/bin/ -lopencv_highgui310d
else:unix: LIBS += -L$$PWD/bin/ -lopencv_highgui310

INCLUDEPATH += $$PWD/bin
DEPENDPATH += $$PWD/bin

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/bin/ -lopencv_imgproc310
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/bin/ -lopencv_imgproc310d
else:unix: LIBS += -L$$PWD/bin/ -lopencv_imgproc310

INCLUDEPATH += $$PWD/bin
DEPENDPATH += $$PWD/bin

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/bin/ -lopencv_videoio310
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/bin/ -lopencv_videoio310d
else:unix: LIBS += -L$$PWD/bin/ -lopencv_videoio310

INCLUDEPATH += $$PWD/bin
DEPENDPATH += $$PWD/bin

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/bin/ -lopencv_imgcodecs310
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/bin/ -lopencv_imgcodecs310d
else:unix: LIBS += -L$$PWD/bin/ -lopencv_imgcodecs310

INCLUDEPATH += $$PWD/bin
DEPENDPATH += $$PWD/bin
