QT += core gui widgets multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# 你可以使代码在使用已弃用 API 时编译失败
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000  # 禁用 Qt 6.0 之前弃用的 API

# ------------------------------
# 头文件路径
INCLUDEPATH += $$PWD             # 项目根目录
INCLUDEPATH += $$PWD/libs        # MathLib 头文件
INCLUDEPATH += $$PWD/include     # FFmpeg 头文件
INCLUDEPATH += $$PWD/CustomizeFunction
INCLUDEPATH += $$PWD/GlobalManager
INCLUDEPATH += $$PWD/SplashVideoWidget

# ------------------------------
# 链接库
LIBS += -L$$PWD/libs -lMathLib   # 告诉链接器库文件在哪里并链接
LIBS += -L$$PWD/lib -lavcodec -lavformat -lavutil -lswscale

# 可选 Windows 库（已注释）
# LIBS += D:/project/SimpleTemplate/SimpleTemplate/lib/avcodec-60.lib
# LIBS += D:/project/SimpleTemplate/SimpleTemplate/lib/avformat-60.lib
# LIBS += D:/project/SimpleTemplate/SimpleTemplate/lib/avutil-60.lib
# LIBS += D:/project/SimpleTemplate/SimpleTemplate/lib/swscale-6.lib

# 静态库
LIBS += -L$$PWD/libs -lMathStaticLib

# ------------------------------
# 源文件
SOURCES += \
    CustomizeFunction/dashboardwidget.cpp \
    GlobalManager/globalmanager.cpp \
    main.cpp \
    mainwindow.cpp \
    SplashVideoWidget/splashvideowidget.cpp

# 头文件
HEADERS += \
    SharedStatus.h \
    CustomizeFunction/dashboardwidget.h \
    GlobalManager/globalmanager.h \
    mainwindow.h \
    SplashVideoWidget/splashvideowidget.h

# UI 文件
FORMS += \
    mainwindow.ui

# ------------------------------
# 默认部署规则
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
