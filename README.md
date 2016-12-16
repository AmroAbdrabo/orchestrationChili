qml-cellulo
===========

This is a qml module for communicating with Cellulo robots over bluetooth or
simulated robots over web sockets for debugging purposes. It supports desktop
and Android and was tested with Qt 5.4.2.

Dependencies
-------------

Depends on `nanosvg`, run `git submodule init && git submodule update` on the root directory to obtain it.

Desktop build
-------------

Tested on Ubuntu 14.04:

```
mkdir build-desktop && cd build-desktop
/path-to-qt-install-root/5.4/gcc_64/bin/qmake ..
make -j5 install
```

Android build
-------------

Tested with Android API 17 (Android version 4.2) and Android NDK r10e:

```
export ANDROID_NDK_ROOT=/path-to-android-ndk/
```

```
mkdir build-android && cd build-android
/path-to-qt-install-root/5.4/android_armv7/bin/qmake ..
make -j5 install
```

Build & run unit tests
----------------------

```
mkdir build-test && cd build-test
/path-to-qt-install-root/5.4/gcc_64/bin/qmake .. "CONFIG += test"
make -j5
./celluloplugintests
```

QML API
-------

### `CelluloBluetoothEnums [Singleton]`

Object that contains enums used across the Cellulo objects.

**Enums:**

`ConnectionStatus` - Robot connection status
> - `ConnectionStatusDisconnected` - Idle and not connected
> - `ConnectionStatusConnecting` - Actively trying to connect
> - `ConnectionStatusConnected` - Connected

`BatteryState` - Robot battery state
> - `BatteryStateDischarging` - No charger present, battery draining
> - `BatteryStateLow` - No charger present, battery low, will shut down
> - `BatteryStateCharging` - Charger present, battery charging
> - `BatteryStateCharged` - Charger present, battery full
> - `BatteryStateShutdown` - Charger charging disabled, voltage too low or battery not present
> - `BatteryStateError` - Thermal fault or charge timeout

`LEDResponseMode` - Robot LED response mode to touch
> - `LEDResponseModeResponsiveIndividual` - LEDs respond to touches by slightly increasing brightness
> - `LEDResponseModeAbsolute` - LEDs don't respond to touches
> - `LEDResponseModeResponsiveHold` - LEDs respond to Hold gesture by all changing color

`LocomotionInteractivityMode` - Robot locomotion relation to touches
> - `LocomotionInteractivityModeNormal` - Robot moves normally
> - `LocomotionInteractivityModeRequiresHold` - Robot doesn't move unless Hold gesture is present

`VisualEffect` - Robot LED effects
> - `VisualEffectConstAll` - Set all LED colors (value unused)
> - `VisualEffectConstSingle` - Set one LED color (value is LED index)
> - `VisualEffectAlertAll` - Alert animation for all LEDs (value unused)
> - `VisualEffectAlertSingle` - Alert animation for one LED (value is LED index)
> - `VisualEffectProgress` - Static progress circularly (value 0-255 maps to 0-100%)
> - `VisualEffectWaiting` - Circular waiting/processing animation (value unused)
> - `VisualEffectDirection` - Point toward one direction (value 0-255 maps to 0-360 degrees)
> - `VisualEffectBlink` - Alert forever (value*20 is LED on time in milliseconds)
> - `VisualEffectBreathe` - Breathe animation (value unused)
> - `VisualEffectPulse` - Slower breathe-like animation (value unused)

`Gesture` - Special robot key touch states
> - `GestureNone` - No gesture
> - `GestureHold` - Robot is "held" (a general presence is detected on the keys)

### `CelluloBluetooth`

Object that communicates with a Cellulo robot over Bluetooth.

**Properties:**

>  - **autoConnect** :      `bool` - Whether to start connecting immediately as soon as **macAddr** is set and to reconnect if connection drops, default true
>  - **macAddr** :          `string` - Robot MAC address in the form "XX:XX:XX:XX:XX:XX"
>  - **connectionStatus** : `readonly CelluloBluetoothEnums.ConnectionStatus` - Current connection status to the robot
>  - **batteryState** :     `readonly CelluloBluetoothEnums.BatteryState` - Robot's current battery state
>  - **x** :                `readonly real` - Robot's x coordinate in mm
>  - **y** :                `readonly real` - Robot's y coordinate in mm
>  - **theta** :            `readonly real` - Robot's orientation in degrees
>  - **kidnapped** :        `readonly bool` - Whether the robot is not on encoded paper
>  - **gesture** :          `readonly CelluloBluetoothEnums.Gesture` - Current robot gesture (if gesture detection is enabled)
>  - **timestampingEnabled** : `bool` - Whether the robot will send its own timestamp along with its pose, default false
>  - **lastTimestamp** :    `readonly int` - Last local timestamp received along with pose (is valid if **timestampingEnabled** is true)
>  - **framerate** :        `readonly real` - Localization framerate calculated from local timestamps received along with pose (is valid if **timestampingEnabled** is true)

**Signals:**

>  - **bootCompleted()**: Emitted when the robot is ready after reset
>  - **shuttingDown()**: Emitted when the robot is shutting down due to user touch key command
>  - **lowBattery()**: Emitted when the robot is shutting down due to low battery
>  - **touchBegan(int key)**: Emitted when a key is touched, **key** is in [0,5]
>  - **longTouch(int key)**: Emitted when a key is touched for a long time, **key** is in [0,5]
>  - **touchReleased(int key)**: Emitted when a key is released, **key** is in [0,5]
>  - **poseChanged()**: Emitted when **x**, **y** or **theta** changes
>  - **trackingGoalReached()**: Emitted when the robot reaches the pose/position/orientation goal

**Slots:**

*Related to connection/state/operation/visuals:*

>  - **bool connectToServer()**: Starts connecting to the robot
>  - **void disconnectFromServer()**: Disconnects from the robot
>  - **void setExposureTime(int pixels)**: Disables robot's camera autoexposure and sets a manual exposure time for super-fast unkidnap detection; **pixels** represents this time and must be greater than `260`. A good value for white paper is `460`. Setting **pixels** to `0` re-enables autoexposure.
>  - **void queryBatteryState()**: Manually requests the **batteryState**
>  - **void setVisualEffect(CelluloBluetoothEnums.VisualEffect effect, color color, int value)**: Sets the LED effect and color on the robot; **value** is in [0,255] and can be meaningful for a given effect.

>  - **void setLEDResponseMode(CelluloBluetoothEnums.LEDResponseMode mode)**: Sets the LED response mode to touch
>  - **void setLocomotionInteractivityMode(CelluloBluetoothEnums.LocomotionInteractivityMode mode)**: Sets the locomotion relation to touch
>  - **void setGestureEnabled(bool enabled)**: Sets whether gesture detection is enabled, it is disabled by default
>  - **void setPoseBcastPeriod(int period)**: Sets the pose broadcast period (in ms) from the robot; set to `0` to broadcast as fast as possible (about 93Hz)
>  - **void reset()**: Initiates a software reset on the robot
>  - **void shutdown()**: Initiates sleep on the robot

*Related to pose/position/orientation/velocity/trajectory tracking:*

>  - **void setGoalVelocity(real vx, real vy, real w)**: Sets the velocities to track (open loop) in the world frame (in mm/s, mm/s, rad/s)
>  - **void setGoalPose(real x, real y, real theta, real v, real w)**: Sets the pose to track (open loop) in the world frame (in mm, mm, deg) with max velocities (mm/s, rad/s)
>  - **void setGoalPosition(real x, real y, real v)**: Sets the position to track (open loop) in the world frame (in mm, mm) with max linear velocity (mm/s)
>  - **void setGoalXCoordinate(real x, real v)**: Sets the x coordinate to track (open loop) in the world frame (in mm) with max linear velocity (mm/s)
>  - **void setGoalYCoordinate(real y, real v)**: Sets the y coordinate to track (open loop) in the world frame (in mm) with max linear velocity (mm/s)
>  - **void setGoalOrientation(real theta, real w)**: Sets the orientation to track (open loop) in the world frame (in deg) with max angular velocity (rad/s)
>  - **void setGoalXThetaCoordinate(real x, real theta, real v, real w)**: Sets the x coordinate and orientation to track (open loop) in the world frame (in mm, deg) with max velocities (mm/s, rad/s)
>  - **void setGoalYThetaCoordinate(real y, real theta, real v, real w)**: Sets the y coordinate and orientation to track (open loop) in the world frame (in mm, deg) with max velocities (mm/s, rad/s)
>  - **void polyBezierInit(vector2d point0)**: Sets the first control point of the composite Bézier curve to track
>  - **void polyBezierAppend(vector2d point1, vector2d point2, vector2d point3)**: Adds a segment to the composite Bézier curve to track, first control point is the last control point of the previous segment; **polyBezierInit(vector2d)** must have been called before
>  - **void polyBezierSetFromZone(CelluloZonePolyBezier zone)**: Sends the composite Bézier curve in the given zone to the robot to track; i.e calls appropriate **polyBezierInit(vector2d)** and **polyBezierAppend(vector2d, vector2d, vector2d)**'s.
>  - **void setGoalPolyBezier(real v, real w)**: Starts tracking the previously set composite Bézier curve with given linear velocity tangent to the curve (mm/s) and given angular velocity throughout the traversal (open loop, rad/s); **polyBezierInit(vector2d)** and **polyBezierAppend(vector2d, vector2d, vector2d)**'s must have been called before.
>  - **void setGoalPolyBezierAligned(real v, real theta, real w)**: Starts tracking the previously set composite Bézier curve with given linear velocity tangent to the curve (mm/s) while keeping the orientation tangent to the curve (deg) with maximum given angular velocity (rad/s); **polyBezierInit(vector2d)** and **polyBezierAppend(vector2d, vector2d, vector2d)**'s must have been called before.
>  - **void clearTracking()**: Clears pose/position/velocity/trajectory goals

*Related to haptic feedback/backdrive assist:*

>  - **void setCasualBackdriveAssistEnabled(bool enabled)**: Enables/disables assist for easily backdriving the robot, default is disabled. Casual backdrive is amplified if gesture detection is enabled and a hold gesture is detected.
>  - **void setHapticBackdriveAssist(real xAssist, real yAssist, real thetaAssist)**: Enables assist with custom intensities per DOF. Intensities are given as coefficients to be multiplied with the drive velocities and accept negative values to go against the user's motion. Set all to `0` to disable. Enabling this assist disables casual backdrive assist.
>  - **void simpleVibrate(real iX, real iY, real iTheta, int period, int duration)**: Constantly vibrates the robot with given linear and angular intensities (scale same as linear and angular velocities) and with given period (ms, maximum is `0xFFFF`) for the given duration (ms, maximum is `0xFFFF`, set to `0` to vibrate forever).
>  - **void vibrateOnMotion(real iCoeff, int period)**: Enables vibration against user motion with given period (ms, maximum is `0xFFFF`) with given intensity for all DOF. Intensity is given as a coefficient to be multiplied with the drive velocities.
>  - **void clearHapticFeedback()**: Clears **vibrateOnMotion** and **simpleVibrate**
