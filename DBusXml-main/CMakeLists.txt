cmake_minimum_required(VERSION 3.7)

set(VERSION 4.0)

project(DBusXml)
set(BIN_NAME DBusXml)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_FLAGS "-g -Wall")


# 查找Qt
find_package(Qt5 REQUIRED COMPONENTS Core DBus Widgets)

set(DBUS_INTERFACE_XML_FILES
    adaptors/com.deepin.dde.blackscreen.xml
    # 添加其他DBus接口的XML文件
)
# 为每个XML文件生成DBus适配器类的C++代码
qt5_generate_dbus_interface(DBUS_INTERFACE_SRCS ${DBUS_INTERFACE_XML_FILES})


#QT5_ADD_DBUS_INTERFACE(DBUS_INTERFACE_SRCS
#    adaptors/com.deepin.dde.blackscreen.xml
#    adaptors/BlackScreenAdaptor
#)

include_directories(
    adaptors/BlackScreenInterfaceAdaptor.h
    manage.h
    window.h
    manage.h
)

# 添加源文件
set(SOURCES
    main.cpp
    adaptors/BlackScreenInterfaceAdaptor.cpp
    window.cpp
    manage.cpp
    ${DBUS_INTERFACE_XML_FILES}
)

# 创建可执行文件
add_executable(${BIN_NAME} ${SOURCES} ${DBUS_INTERFACE_SRCS})

# 链接Qt的库
target_link_libraries(${BIN_NAME} ${INTERFACES} Qt5::Core Qt5::DBus Qt5::Widgets)

#services files
#install(FILES com.deepin.dde.BlackScreen.service DESTINATION ${CMAKE_INSTALL_DATADIR}/dbus-1/services)
install(FILES com.deepin.dde.BlackScreen.service DESTINATION /usr/share/dbus-1/services)

# bin
#install(TARGETS ${BIN_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION /usr/bin)

