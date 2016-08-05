/*
 * Copyright (C) 2015 EPFL
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/.
 */

/**
 * @file CelluloBluetooth.h
 * @brief Header for Bluetooth communication with Cellulo robots
 * @author Ayberk Özgür
 * @date 2015-05-20
 */

#ifndef CELLULOBLUETOOTH_H
#define CELLULOBLUETOOTH_H

#include <QTimer>
#include <QQueue>
#include <QQuickItem>
#include <QBluetoothSocket>
#include <QColor>
#include <QMetaEnum>
#include <QVariantList>

#include "CelluloBluetoothEnums.h"
#include "CelluloBluetoothPacket.h"
#include "../zones/CelluloZoneClient.h"
#include "../zones/CelluloZonePolyBezier.h"

/**
 * @brief Bluetooth communicator for a Cellulo robot
 */
class CelluloBluetooth : public CelluloZoneClient {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

    Q_PROPERTY(QString macAddr WRITE setMacAddr READ getMacAddr)
    Q_PROPERTY(CelluloBluetoothEnums::ConnectionStatus connectionStatus READ getConnectionStatus NOTIFY connectionStatusChanged)

    Q_PROPERTY(CelluloBluetoothEnums::BatteryState batteryState READ getBatteryState NOTIFY batteryStateChanged)

    Q_PROPERTY(float x READ getX NOTIFY poseChanged_inherited)
    Q_PROPERTY(float y READ getY NOTIFY poseChanged_inherited)
    Q_PROPERTY(float theta READ getTheta NOTIFY poseChanged_inherited)
    Q_PROPERTY(bool kidnapped READ getKidnapped NOTIFY kidnappedChanged)

    Q_PROPERTY(bool timestampingEnabled WRITE setTimestampingEnabled READ getTimestampingEnabled)
    Q_PROPERTY(int lastTimestamp READ getLastTimestamp NOTIFY timestampChanged)
    Q_PROPERTY(float framerate READ getFramerate NOTIFY timestampChanged)

    Q_PROPERTY(float cameraImageProgress READ getCameraImageProgress NOTIFY cameraImageProgressChanged)

public:

    static const int BT_CONNECT_TIMEOUT_MILLIS     = 30000;  ///< Will try to reconnect after this much time
    static constexpr float FRAMERATE_SMOOTH_FACTOR = 0.99f;  ///< Smoothing factor for framerate, closer to 1.0 means less update

    static QByteArray frameBuffer;                           ///< Container for the received camera frame data

    /**
     * @brief Creates a new Cellulo robot communicator
     *
     * @param parent Parent of this QML item
     */
    explicit CelluloBluetooth(QQuickItem* parent = 0);

    /**
     * @brief Destroys this Cellulo robot communicator
     */
    virtual ~CelluloBluetooth();

    /**
     * @brief Gets the latest camera frame
     *
     * @return The latest camera frame; IMG_WIDTH*IMG_HEIGHT many ints in grayscale, 0 to 255
     */
    QVariantList getFrame() const;

    /**
     * @brief Gets the current MAC address
     *
     * @return The current MAC address
     */
    QString getMacAddr(){ return macAddr; }

    /**
     * @brief Gets current Bluetooth connection status
     *
     * @return Current Bluetooth connection status
     */
    CelluloBluetoothEnums::ConnectionStatus getConnectionStatus(){ return connectionStatus; }

    /**
     * @brief Gets whether timestamping along with pose is currently enabled
     *
     * @return Whether timestamping is enabled
     */
    bool getTimestampingEnabled(){ return timestampingEnabled; }

    /**
     * @brief Gets the latest battery state
     *
     * @return Battery state
     */
    CelluloBluetoothEnums::BatteryState getBatteryState(){ return batteryState; }

    /**
     * @brief Gets the latest x position
     *
     * @return Latest x position in mm
     */
    float getX(){ return x; }

    /**
     * @brief Gets the latest y position
     *
     * @return Latest y position in mm
     */
    float getY(){ return y; }

    /**
     * @brief Gets the latest orientation
     *
     * @return Latest orientation in degrees
     */
    float getTheta(){ return theta; }

    /**
     * @brief Gets the latest available timestamp
     *
     * @return The latest received timestamp in milliseconds
     */
    int getLastTimestamp(){ return lastTimestamp; }

    /**
     * @brief Gets the localization framerate
     *
     * @return Localization framerate in milliseconds
     */
    float getFramerate(){ return framerate; }

    /**
     * @brief Gets the latest kidnapped state
     *
     * @return Whether kidnapped or on encoded paper
     */
    bool getKidnapped(){ return kidnapped; }

    /**
     * @brief Gets the camera image progress
     *
     * @return Between 0.0 and 1.0
     */
    float getCameraImageProgress(){ return cameraImageProgress; }

private slots:

    /**
     * @brief Called when the server sends data
     */
    void socketDataArrived();

    /**
     * @brief Called when (re)connected to server
     */
    void socketConnected();

    /**
     * @brief Called when disconnected from server
     */
    void socketDisconnected();

    /**
     * @brief Disconnects first and then connects again if not connected yet
     */
    void refreshConnection();

public slots:

    /**
     * @brief Sets the MAC address of the server and immediately connects to it
     *
     * @param macAddr Bluetooth MAC address of the server (robot)
     */
    void setMacAddr(QString macAddr);

    /**
     * @brief Creates socket and connects to the current target MAC address
     */
    void connectToServer();

    /**
     * @brief Disconnects from the currently connected device and destroys the socket if possible
     */
    void disconnectFromServer();

    /**
     * @brief Sets the pose broadcast period
     *
     * @param period Desired period in milliseconds
     */
    void setPoseBcastPeriod(unsigned int period);

    /**
     * @brief Enables timestamping along with pose and disables pose idling or vice-versa
     *
     * @param enabled Whether to enable timestamping
     */
    void setTimestampingEnabled(bool enabled);

    /**
     * @brief Sets output of motor 1
     *
     * @param output Value between -0xFFF and 0xFFF
     */
    void setMotor1Output(int output);

    /**
     * @brief Sets output of motor 2
     *
     * @param output Value between -0xFFF and 0xFFF
     */
    void setMotor2Output(int output);

    /**
     * @brief Sets output of motor 3
     *
     * @param output Value between -0xFFF and 0xFFF
     */
    void setMotor3Output(int output);

    /**
     * @brief Sets outputs of all motors
     *
     * @param m1output Value between -0xFFF and 0xFFF
     * @param m2output Value between -0xFFF and 0xFFF
     * @param m3output Value between -0xFFF and 0xFFF
     */
    void setAllMotorOutputs(int m1output, int m2output, int m3output);

    /**
     * @brief Sets robot goal velocity in global world frame
     *
     * @param vx X velocity in mm/s
     * @param vy Y velocity in mm/s
     * @param w Angular velocity in rad/s
     */
    void setGoalVelocity(float vx, float vy, float w);

    /**
     * @brief Sets a pose goal to track
     *
     * @param x X goal in mm
     * @param y Y goal in mm
     * @param theta Theta goal in degrees
     * @param v Maximum linear speed to track pose in mm/s
     * @param w Maximum angular speed to track pose in rad/s
     */
    void setGoalPose(float x, float y, float theta, float v, float w);

    /**
     * @brief Sets a position goal to track
     *
     * @param x X goal in mm
     * @param y Y goal in mm
     * @param v Maximum linear speed to track pose in mm/s
     */
    void setGoalPosition(float x, float y, float v);

    /**
     * @brief Sets an X coordinate to track
     *
     * @param x X goal in mm
     * @param v Maximum linear speed to track pose in mm/s
     */
    void setGoalXCoordinate(float x, float v);

    /**
     * @brief Sets a Y coordinate to track
     *
     * @param y Y goal in mm
     * @param v Maximum linear speed to track pose in mm/s
     */
    void setGoalYCoordinate(float y, float v);

    /**
     * @brief Sets a position goal to track
     *
     * @param theta Theta goal in degrees
     * @param w Maximum angular speed to track pose in rad/s
     */
    void setGoalOrientation(float theta, float w);

    /**
     * @brief Sets an X and Theta goal at the same time
     *
     * @param x X goal in mm
     * @param theta Theta goal in degrees
     * @param v Maximum linear speed to track pose in mm/s
     * @param w Maximum angular speed to track pose in rad/s
     */
    void setGoalXThetaCoordinate(float x, float theta, float v, float w);

    /**
     * @brief Sets a Y and Theta goal at the same time
     *
     * @param y Y goal in mm
     * @param theta Theta goal in degrees
     * @param v Maximum linear speed to track pose in mm/s
     * @param w Maximum angular speed to track pose in rad/s
     */
    void setGoalYThetaCoordinate(float y, float theta, float v, float w);

    /**
     * @brief Clears pose/position/velocity goals
     */
    void clearTracking();

    /**
     * @brief Constantly vibrates the robot
     *
     * @param iX X intensity, scale is the same as linear velocity
     * @param iY Y intensity, scale is the same as linear velocity
     * @param iTheta Theta intensity, scale is the same as angular velocity
     * @param period Period of vibration in milliseconds, maximum is 0xFFFF
     * @param duration Duration of vibration in milliseconds, maximum is 0xFFFF, 0 for vibrate forever
     */
    void simpleVibrate(float iX, float iY, float iTheta, unsigned int period, unsigned int duration);

    /**
     * @brief Enables vibration against motion
     *
     * @param iCoeff Vibration intensity with respect to the drive velocities
     * @param period Period of vibration in milliseconds, maximum is 0xFFFF
     */
    void vibrateOnMotion(float iCoeff, unsigned int period);

    /**
     * @brief Clears all haptic feedbacks
     */
    void clearHapticFeedback();

    /**
     * @brief Sends a ping, expecting an acknowledge
     */
    void ping();

    /**
     * @brief Requests a camera frame to be sent
     */
    void requestFrame();

    /**
     * @brief Sets the exposure time for super-fast unkidnap detection for uniform and known paper colors known or enables autoexposure
     *
     * 460 pixels for the latest white plastic frame and white paper is a good value.
     *
     * @param pixels Exposure time in pixels, must be larger than 260; 0 is a special value that enables autoexposure
     */
    void setExposureTime(int pixels);

    /**
     * @brief Sends a battery state query
     */
    void queryBatteryState();

    /**
     * @brief Sets the LED response mode, i.e the LED visual response of the robot to touches
     *
     * @param mode LED resposne mode
     */
    void setLEDResponseMode(CelluloBluetoothEnums::LEDResponseMode mode);

    /**
     * @brief Sets the locomotion interactivity mode, i.e the dependance of locomotion to user input
     *
     * @param mode Locomotion interactivity mode
     */
    void setLocomotionInteractivityMode(CelluloBluetoothEnums::LocomotionInteractivityMode mode);

    /**
     * @brief Enables/disables raw touch signal offset querying and processing
     *
     * @param enabled Whether to enable
     */
    void setGestureEnabled(bool enabled);

    /**
     * @brief Enables/disables assist for easy backdriving
     *
     * @param enabled Whether to enable
     */
    void setCasualBackdriveAssistEnabled(bool enabled);

    /**
     * @brief Haptic feedback-oriented backdrive assist
     *
     * Pass 0 to all parameters to disable.
     * Disables casual backdrive assist upon enabling.
     *
     * @param xAssist X assist with respect to x drive velocity, can be negative
     * @param yAssist Y assist with respect to y drive velocity, can be negative
     * @param thetaAssist Theta assist with respect to w drive, can be negative
     */
    void setHapticBackdriveAssist(float xAssist, float yAssist, float thetaAssist);

    /**
     * @brief Sets the visual effect on the robot, changing LED illumination
     *
     * @param effect The effect ordinal
     * @param color Color
     * @param value A value possibly meaningful for the effect (between 0 and 255)
     */
    void setVisualEffect(CelluloBluetoothEnums::VisualEffect effect, QColor color, int value);

    /**
     * @brief Sends the first control point of the composite Bézier curve for motion tracking
     *
     * @param point0 The initial point, i.e the first control point of the first segment
     */
    void polyBezierInit(const QVector2D& point0);

    /**
     * @brief Adds a segment to the composite Bézier curve for motion tracking; polyBezierInit() must be called before
     *
     * The first control point is the last control point of the previously added segment or the initial point.
     *
     * @param point1 The second control point for the curve
     * @param point2 The third control point for the curve
     * @param point3 The fourth control point for the curve
     */
    void polyBezierAppend(const QVector2D& point1, const QVector2D& point2, const QVector2D& point3);

    /**
     * @brief Sends the composite Bézier curve in the zone to the robot
     *
     * @param zone The zone that contains the composite Bézier curve path
     */
    void polyBezierSetFromZone(CelluloZone* zone);

    /**
     * @brief Starts tracking the previously set composite Bézier curve
     *
     * @param v Linear velocity tangent to the curve
     * @param w Angular velocity throughout the traversal
     */
    void setGoalPolyBezier(float v, float w);

    /**
     * @brief Starts tracking the previously set composite Bézier curve while keeping orientation aligned to the curve
     *
     * @param v Linear velocity tangent to the curve
     * @param theta Orientation to track with respect to the curve tangent orientation, in degrees
     * @param w Maximum angular velocity while tracking orientation, in rad/s
     */
    void setGoalPolyBezierAligned(float v, float theta, float w);

    /**
     * @brief Initiates a software reset on the robot
     */
    void reset();

    /**
     * @brief Initiates sleep on the robot
     */
    void shutdown();

signals:

    /**
     * @brief Emitted when Bluetooth connection status changes
     */
    void connectionStatusChanged();

    /**
     * @brief Emitted when the robot is ready after a power up or a reset
     */
    void bootCompleted();

    /**
     * @brief Emitted when the robot is about to sleep (shutdown) due to the user command via touch keys
     */
    void shuttingDown();

    /**
     * @brief Emitted when the robot is about to sleep (shutdown) due to low battery
     */
    void lowBattery();

    /**
     * @brief Emitted when the battery state changes
     */
    void batteryStateChanged();

    /**
     * @brief Emitted when a key is touched
     *
     * @param key The key that is touched
     */
    void touchBegan(int key);

    /**
     * @brief Emitted when a key is touched for more than the long touch time
     *
     * @param key The key that is touched
     */
    void longTouch(int key);

    /**
     * @brief Emitted when a key is released
     *
     * @param key The key that is released
     */
    void touchReleased(int key);

    /**
     * @brief DO NOT USE EXPLICITLY
     *
     * Emitted when the base class emits poseChanged() since NOTIFY cannot be used with inherited signals
     */
    void poseChanged_inherited();

    /**
     * @brief A new onboard localization timestamp has been received
     */
    void timestampChanged();

    /**
     * @brief Emitted when the kidnap state of the robot changes
     */
    void kidnappedChanged();

    /**
     * @brief Emitted when pose/position/orientation goal is reached
     */
    void trackingGoalReached();

    /**
     * @brief Emitted when a new camera image line is received
     */
    void cameraImageProgressChanged();

    /**
     * @brief Emitted when a camera frame from the robot is ready to read
     */
    void frameReady();

private:

    CelluloBluetoothPacket sendPacket;                        ///< Outgoing packet
    CelluloBluetoothPacket recvPacket;                        ///< Incoming packet

    QTimer btConnectTimeoutTimer;                             ///< Timeout timer to reconnect if connection fails
    QBluetoothSocket* socket;                                 ///< Bluetooth socket connected to the server
    QString macAddr;                                          ///< Bluetooth MAC address of the server
    CelluloBluetoothEnums::ConnectionStatus connectionStatus; ///< Bluetooth connection status

    bool timestampingEnabled;                                 ///< Whether timestamping along with pose is enabled and idling disabled
    int lastTimestamp;                                        ///< Latest received onboard timestamp (in milliseconds)
    float framerate;                                          ///< Framerate calculated over time
    float cameraImageProgress;                                ///< Camera image streaming progress

    CelluloBluetoothEnums::BatteryState batteryState;         ///< Current battery state
    float x;                                                  ///< Current x position in mm
    float y;                                                  ///< Current y position in mm
    float theta;                                              ///< Current orientation in degrees
    bool kidnapped;                                           ///< Whether currently kidnapped

    /**
     * @brief Resets properties of the robot to default
     */
    void resetProperties();

    /**
     * @brief Connects or reconnects to the service on the server if not already connected
     */
    void openSocket();

    /**
     * @brief Sets the motor output
     *
     * @param motor 1, 2 or 3
     * @param output Value between -FFF and FFF
     */
    void setMotorOutput(int motor, int output);

    /**
     * @brief Sends the already built packet over Bluetooth
     */
    void sendCommand();

    /**
     * @brief Processes the response in the receive buffer if possible
     */
    void processResponse();
};

#endif // CELLULOBLUETOOTH_H
