1. 使用该命令生成对应文件：qdbusxml2cpp -c BlackScreenInterface -a BlackScreenInterfaceAdaptor com.deepin.dde.blackscreen.xml
2. 编译: mkdir build & cd build & cmake .. & make -j8 & sudo make install
3. dbus调用: gdbus call --session --dest com.deepin.dde.BlackScreen --object-path /com/deepin/dde/BlackScreen --method com.deepin.dde.BlackScreen.Show
