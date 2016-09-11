#ifndef SETTINGSFACTORY_H
#define SETTINGSFACTORY_H

#include <QFile>
#include <QObject>
#include <QJsonObject>
#include <QHash>

class SettingsFactory : public QObject {
    Q_OBJECT
public:
    static QVariantMap *getSettings();
    static void saveSettings();
    static QString getCurrientSettingsPath();

private:
    static QFile settingsFile;
    static QVariantMap* settingsMap;
};

#endif // SETTINGSFACTORY_H
