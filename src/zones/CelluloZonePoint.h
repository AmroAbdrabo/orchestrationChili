#ifndef CELLULOZONEPOINT_H
#define CELLULOZONEPOINT_H

#include "CelluloZone.h"

/**
 * @brief CelluloZone Base Class for point zones
 */
class CelluloZonePoint : public CelluloZone{
    Q_OBJECT
    Q_PROPERTY(float x WRITE setX READ getX NOTIFY xChanged)
    Q_PROPERTY(float y WRITE setY READ getY NOTIFY yChanged)

public:
    /**
     * @brief Creates a new Cellulo point zone
     */
   CelluloZonePoint();

    /**
     * @brief Gets the x position of the point
     * @return X position of the point
     */
    float getX() { return x; }
    void setX(float newX) {
        if(newX!=x){
            x = newX;
            emit(xChanged());
        }
    }

    /**
     * @brief Gets the y position of the point
     * @return Y position of the point
     */
    float getY() { return y; }
    void setY(float newY) {
        if(newY!=y){
            y = newY;
            emit(yChanged());
        }
    }

    /**
     * @brief get the properties of this zone in rationalized form
     * @param realPlaygroundWidth real playground width
     * @param realPlaygroundHeight real playground height
     * @return map of rationalized properties
     */
    QVariantMap getRatioProperties(float realPlaygroundWidth, float realPlaygroundHeight);

    /**
     * @brief Calculate the zone quantity of this line zone according to the robot's pose
     *
     * @param xRobot x position of the robot
     * @param yRobot y position of the robot
     * @param thetaRobot theta position of the robot
     *
     * @return Zone quantity for this zone and this robot's pose
     */
    Q_INVOKABLE virtual float calculate(float xRobot, float yRobot, float thetaRobot) = 0;

    /**
     * @brief Write the zone infos to the given json Object
     * @param json json object to be written
     */
    void write(QJsonObject &json);


    /**
     * @brief Read the zone infos from the given json Object
     * @param json json object to be read
     */
    void read(const QJsonObject &json);

protected:
    float x;                               ///< X position of the point
    float y;                               ///< Y position of the point

signals:

    /**
     * @brief Emitted when the X position of the point changes
     */
    void xChanged();
    /**
     * @brief Emitted when the Y position of the point changes
     */
    void yChanged();

};

/**
 * @brief CelluloZone Specific Class for point zones inner determination
 */
class CelluloZonePointInner : public CelluloZonePoint {
    Q_OBJECT

public:
    CelluloZonePointInner();

    /**
     * @brief Calculate whether the robot lies inside this point zone
     *
     * @param xRobot x position of the robot
     * @param yRobot y position of the robot
     * @param thetaRobot theta position of the robot
     *
     * @return  1 if the robot is inside this point zone 0 otherwise
     */
    Q_INVOKABLE float calculate(float xRobot, float yRobot, float thetaRobot);

};


/**
 * @brief CelluloZone Specific Class for point zones distance determination
 */
class CelluloZonePointDistance : public CelluloZonePoint {
    Q_OBJECT

public:
    CelluloZonePointDistance();

    /**
     * @brief Calculate the distance between the robot pose and this point zone
     *
     * @param xRobot x position of the robot
     * @param yRobot y position of the robot
     * @param thetaRobot theta position of the robot
     *
     * @return the distance between the robot pose and this point zone
     */
    Q_INVOKABLE float calculate(float xRobot, float yRobot, float thetaRobot);

};

#endif // CELLULOZONEPOINT_H
