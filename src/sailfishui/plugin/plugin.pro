TEMPLATE = lib
TARGET = $$qtLibraryTarget(settingsplugin)

MODULENAME = com/jolla/settings/crashreporter
TARGETPATH = $$[QT_INSTALL_QML]/$$MODULENAME

QT += dbus qml
CONFIG += plugin

qml.files = qmldir *.qml
qml.path = $$TARGETPATH

target.path = $$TARGETPATH

INCLUDEPATH += \
	../../libs \
	../../libs/coredir \
	../../libs/settings \
	../../libs/utils \

LIBS += -L../../../lib -lcrashreporter

DBUS_INTERFACES = \
	org.freedesktop.systemd1.Manager.xml \
	org.freedesktop.systemd1.Unit.xml \
	org.freedesktop.DBus.Properties.xml

HEADERS += \
	crashreporteradapter.h \
	crashreporterqmlplugin.h \
	pendinguploadsmodel.h \
	systemdservice.h \

SOURCES += \
	crashreporteradapter.cpp \
	crashreporterqmlplugin.cpp \
	pendinguploadsmodel.cpp \
	systemdservice.cpp \
	unitfilechange.cpp

INSTALLS += target qml

OTHER_FILES = *.qml $$DBUS_INTERFACES
