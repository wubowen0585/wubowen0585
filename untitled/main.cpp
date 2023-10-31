#if 1

#include <QApplication>
#include <QSystemTrayIcon>
#include <QTimer>
#include <QDebug>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qInfo() << " argc : " << argc;
    QString pic1 = "";
    QString pic2 = "";
    for (int i = 0; i < argc; i++) {
        qInfo() << " i argv : " << i << argv[i];
    }
    if (argc >= 3) {
        pic1 = argv[1];
        pic2 = argv[2];
    }

    QSystemTrayIcon trayIcon;
    QTimer timer;
    timer.start(400);

    if (pic1 == "")
        pic1 = "/var/lib/AccountsService/icons/bigger/10.png";
    QObject::connect(&timer, &QTimer::timeout, [&](){
        trayIcon.setIcon(QIcon(pic1));
    });


    QTimer timer1;
    timer1.start(300);

    if (pic2 == "")
        pic2 = "/var/lib/AccountsService/icons/bigger/13.png";
    QObject::connect(&timer1, &QTimer::timeout, [&](){
        trayIcon.setIcon(QIcon(pic2));
    });


    trayIcon.show();

    return app.exec();
}


#else

#include <QApplication>
#include <QSystemTrayIcon>
#include <QMenu>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // 创建系统托盘图标
    QSystemTrayIcon trayIcon;

    // 创建菜单
    QMenu *menu = new QMenu();

    // 添加菜单项
    QAction *quitAction = new QAction("Quit", menu);
    QObject::connect(quitAction, &QAction::triggered, &app, &QApplication::quit);
    menu->addAction(quitAction);

    // 将菜单设置到系统托盘图标
    trayIcon.setContextMenu(menu);

    // 设置系统托盘图标的图标
    QIcon icon = QIcon("/home/uos/Desktop/dcc_auth_success.svg");  // 替换为实际的图标路径
    trayIcon.setIcon(icon);

    // 显示系统托盘图标
    trayIcon.show();

    return app.exec();
}
#endif
