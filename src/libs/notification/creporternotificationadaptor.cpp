/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -c CReporterNotificationAdaptor -a creporternotificationadaptor.h:creporternotificationadaptor.cpp com.nokia.CrashReporter.Notification.xml -N
 *
 * qdbusxml2cpp is Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#include "creporternotificationadaptor.h"
#include <QtCore/QMetaObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>

/*
 * Implementation of adaptor class CReporterNotificationAdaptor
 */

CReporterNotificationAdaptor::CReporterNotificationAdaptor(QObject *parent)
    : QDBusAbstractAdaptor(parent)
{
    // constructor
    setAutoRelaySignals(true);
}

CReporterNotificationAdaptor::~CReporterNotificationAdaptor()
{
    // destructor
}

void CReporterNotificationAdaptor::activate()
{
    // handle method call com.nokia.CrashReporter.Notification.activate
    QMetaObject::invokeMethod(parent(), "activate");
}
