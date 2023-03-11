QT       += core gui opengl openglwidgets
include(gif/gifimage/qtgifimage.pri)


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += warn_off

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controller/controller.cc \
    model/model.cc \
    view/border.cc \
    main.cc \
    view/mainviewer.cc \
    view/perspective.cc \
    view/save.cc \
    view/setting.cc \
    view/vertex.cc \
    view/widget.cc

HEADERS += \
    model/model.h \
    view/border.h \
    view/mainviewer.h \
    view/perspective.h \
    view/save.h \
    view/setting.h \
    view/vertex.h \
    view/widget.h \
    controller/controller.h

FORMS += \
    view/border.ui \
    view/mainviewer.ui \
    view/perspective.ui \
    view/save.ui \
    view/vertex.ui



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    shaders/fshader.qrc \
    shaders/vshader.qrc

