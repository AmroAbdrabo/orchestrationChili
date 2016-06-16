#ifndef CELLULOZONEJSONHANDLER_H
#define CELLULOZONEJSONHANDLER_H

#include <QDebug>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "src/zones/CelluloZone.h"
#include "src/zones/CelluloZoneCircle.h"
#include "src/zones/CelluloZoneRectangle.h"
#include "src/zones/CelluloZoneLine.h"
#include "src/zones/CelluloZonePoint.h"
#include "src/zones/CelluloZonePolygon.h"

class CelluloZoneJsonHandler : public QQuickItem {
    Q_OBJECT

public:

    /**
     * @brief Save zones in JSON file from QML side
     *
     * @param qmlZones zones to be saved from QML world
     * @param path path of the JSON file where to save the zones
     * @param mmPgdWidth width of real playground in mm
     * @param mmPgdHeight height of real playground in mm
     *
     * @return  true if operation was successful, 0 otherwise
     */
    Q_INVOKABLE static bool saveQMLZones(QList<QVariant> qmlZones, QString path, const float mmPgdWidth, const float mmPgdHeight);
    /**
     * @brief Load zones from JSON file from QML side
     *
     * @param path path of the JSON file where to load the zones
     *
     * @return  map containing playground size (width and height) under "playgoundSizeInmm" and retrieved zones under "zones"
     */
    Q_INVOKABLE static QMap<QString, QVariant> loadQMLZones(QString path);
    /**
     * @brief Save zones in JSON file from QT side
     *
     * @param zones zones to be saved from QML world
     * @param path path of the JSON file where to save the zones
     * @param mmPgdWidth width of real playground in mm
     * @param mmPgdHeight height of real playground in mm
     *
     * @return true if operation was successful, 0 otherwise
     */
    bool static saveZones(QList<CelluloZone*> zones, QString path, const float mmPgdWidth, const float mmPgdHeight);
    /**
     * @brief Load zones from JSON file from QML side
     *
     * @param path path of the JSON file where to load the zones
     *
     * @return map containing playground size (width and height) under "playgoundSizeInmm" and retrieved zones under "zones"
     */
    QMap<QString, QVariant> static loadZones(QString path);

private:
    /**
     * @brief write write function to serialise member variables
     *
     * @param json json object to be filled
     * @param zones zones to serialize
     * @param mmPgdWidth width of real playground in mm
     * @param mmPgdHeight height of real playground in mm
     *
     * @return true if operation was successful, 0 otherwise
     */
    bool static write(QJsonObject &json, QList<CelluloZone*> zones, const float mmPgdWidth, const float mmPgdHeight);

    /**
     * @brief read read function to retrieved serialised member variables
     *
     * @param json json object where infor are extracted
     *
     * @return map containing playground size (width and height) under "playgoundSizeInmm" and retrieved zones under "zones"
     */
    QMap<QString, QVariant> static read(const QJsonObject &json);
};


#endif // CELLULOZONEJSONHANDLER_H
