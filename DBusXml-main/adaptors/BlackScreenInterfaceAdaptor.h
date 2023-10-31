/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp -c BlackScreenInterface -a BlackScreenInterfaceAdaptor com.deepin.dde.blackscreen.xml
 *
 * qdbusxml2cpp is Copyright (C) 2017 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * This file may have been hand-edited. Look for HAND-EDIT comments
 * before re-generating it.
 */

#ifndef BLACKSCREENINTERFACEADAPTOR_H
#define BLACKSCREENINTERFACEADAPTOR_H

#include <QtCore/QObject>
#include <QtDBus/QtDBus>
QT_BEGIN_NAMESPACE
class QByteArray;
template<class T> class QList;
template<class Key, class Value> class QMap;
class QString;
class QStringList;
class QVariant;
QT_END_NAMESPACE

/*
 * Adaptor class for interface com.deepin.dde.BlackScreen
 */
class BlackScreenInterface: public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.deepin.dde.BlackScreen")
    Q_CLASSINFO("D-Bus Introspection", ""
"  <interface name=\"com.deepin.dde.BlackScreen\">\n"
"    <method name=\"SetVisible\">\n"
"      <arg direction=\"in\" type=\"b\" name=\"visible\"/>\n"
"    </method>\n"
"    <method name=\"Quit\"/>\n"
"    <method name=\"Show\"/>\n"
"  </interface>\n"
        "")
public:
    BlackScreenInterface(QObject *parent);
    virtual ~BlackScreenInterface();

public: // PROPERTIES
public Q_SLOTS: // METHODS
    void Quit();
    void SetVisible(bool visible);
    void Show();
Q_SIGNALS: // SIGNALS
};

#endif