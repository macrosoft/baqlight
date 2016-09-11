#include "settingsfactory.h"
#include <QFile>
#include <QJsonDocument>
#include <QDir>
#include <QStandardPaths>
#include <QVariantMap>

QVariantMap* SettingsFactory::settingsMap;
QFile SettingsFactory::settingsFile;

QVariantMap *SettingsFactory::getSettings() {
    static bool firstCall = true;
    if (firstCall) {
        settingsMap = NULL;
        firstCall = false;
    }
    if (settingsMap) {
        return settingsMap;
    }
    QDir dir(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation));
    settingsFile.setFileName(dir.absoluteFilePath("baqlite.json"));
    if (!settingsFile.open(QIODevice::ReadOnly)) {
        settingsMap = new QVariantMap();
        return settingsMap;
    }
    QJsonDocument doc = QJsonDocument::fromJson(settingsFile.readAll());
    settingsFile.close();
    settingsMap = new QVariantMap(doc.object().toVariantMap());
    return settingsMap;
}

void SettingsFactory::saveSettings() {
    if (!settingsMap) {
        return;
    }
    if (!settingsFile.open(QIODevice::WriteOnly)) {
        return;
    }
    QJsonDocument doc(QJsonObject::fromVariantMap(*(settingsMap)));
    settingsFile.write(doc.toJson());
    settingsFile.close();
}
