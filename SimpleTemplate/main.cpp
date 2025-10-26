#include "mainwindow.h"
#include "MathLib.h"
#include "MathStaticLib.h"
#include <QApplication>
#include <QSharedMemory>
#include <QMessageBox>
#include <QDebug>
#include "SplashVideoWidget\SplashVideoWidget.h"
#include "SharedStatus.h"
#include "GlobalManager/GlobalManager.h"



void test(){
    // 设置变量
    GlobalManager::instance().setVar("userId", 1001);
    GlobalManager::instance().setVar("username", "Alice");
    GlobalManager::instance().setVar("isLoggedIn", true);

    // 获取变量
    int uid = GlobalManager::instance().getVar("userId").toInt();
    QString name = GlobalManager::instance().getVar("username").toString();
    bool loggedIn = GlobalManager::instance().getVar("isLoggedIn").toBool();


    qDebug() << uid << name << loggedIn;

    // 打印所有变量
    GlobalManager::instance().printAll();
}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    // 创建 SplashVideoWidget
    SplashVideoWidget splash;
    if (!splash.initSharedMemory()) {
        return 0;  // 若共享内存已存在，退出程序
    }
    splash.show();

    // 构造视频文件路径（相对于 exe 目录）
    QString videoPath = QCoreApplication::applicationDirPath() + "/loadVideo.mp4";
    splash.play(videoPath);

    // 视频播放完成后打开主窗口
    QObject::connect(&splash, &SplashVideoWidget::videoFinished, &splash,  [&]() {
        splash.close();

        // 创建主窗口
        MainWindow *w = new MainWindow();

        // // 调用 DLL 导出函数
        // int result_add = addaddadd(13, 5);
        // qDebug() << "Result =" << result_add;

        // int result_minus = minusminus(20, 6);
        // qDebug() << "Minus =" << result_minus;

        w->show();
    });

    test();


    return a.exec();
}
