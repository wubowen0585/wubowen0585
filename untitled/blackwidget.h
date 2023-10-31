#ifndef BLACKWIDGET_H
#define BLACKWIDGET_H

#include <QWidget>

//class BlackWidget : public QWidget
//{
//    Q_OBJECT
//public:
//    explicit BlackWidget(QWidget *parent = nullptr);

//signals:

//public slots:
//};

class BlackWidget : public QWidget {
    Q_OBJECT

public:
    BlackWidget(QWidget *parent = nullptr) : QWidget(parent) {
        // 设置窗口无边框
        setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        // 设置背景色为黑色
        setStyleSheet("background-color: black;");
    }
};


#endif // BLACKWIDGET_H
