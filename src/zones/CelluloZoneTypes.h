#ifndef CELLULOZONETYPES_H
#define CELLULOZONETYPES_H

#include <QQuickItem>

/**
 * @brief holds Q_ENUMS used from frontend and associtated conversion functions
 */
class CelluloZoneTypes : public QQuickItem
{
    Q_OBJECT
    Q_ENUMS(ZoneType)


public:
    enum ZoneType{
        CIRCLEINNER = 0,
        CIRCLEBORDER,
        CIRCLEDISTANCE,
        RECTANGLEINNER,
        RECTANGLEBORDER,
        RECTANGLEDISTANCE,
        LINEINNER,
        LINEDISTANCE,
        POINTINNER,
        POINTDISTANCE,
        RPOLYGONINNER,
        RPOLYGONBORDER,
        RPOLYGONDISTANCE,
        IRPOLYGONINNER,
        IRPOLYGONBORDER,
        IRPOLYGONDISTANCE
    };

    /**
     * @brief convert the enum type to a Qstring
     * @param type ZoneType to be converted
     * @return QString representation of the ZoneType
     */
   Q_INVOKABLE static QString typeToString(const CelluloZoneTypes::ZoneType &type);

    /**
     * @brief convert the QString to its ZoneType representation
     * @param typeName QString to be converted
     * @return ZoneType reprensentation of the QString
     */
    Q_INVOKABLE static CelluloZoneTypes::ZoneType typeFromString(const QString &typeName);

};

#endif // CELLULOZONETYPES_H
