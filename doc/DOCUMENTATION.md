# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`namespace `[`Cellulo`](#namespaceCellulo) | 
`class `[`CameraFrameImageProvider`](#classCameraFrameImageProvider) | QImage provider from QByteArray.
`class `[`CelluloBluetooth`](#classCelluloBluetooth) | Bluetooth communicator for a Cellulo robot.
`class `[`CelluloBluetoothEMP`](#classCelluloBluetoothEMP) | 
`class `[`CelluloBluetoothScanner`](#classCelluloBluetoothScanner) | 
`class `[`CelluloCommUtil`](#classCelluloCommUtil) | 
`class `[`CelluloLocalRelayClient`](#classCelluloLocalRelayClient) | 
`class `[`CelluloLocalRelayServer`](#classCelluloLocalRelayServer) | 
`class `[`CelluloRelayClient`](#classCelluloRelayClient) | 
`class `[`CelluloRelayServer`](#classCelluloRelayServer) | 
`class `[`CelluloRobotPoolClient`](#classCelluloRobotPoolClient) | 
`class `[`CelluloTcpRelayClient`](#classCelluloTcpRelayClient) | 
`class `[`CelluloTcpRelayServer`](#classCelluloTcpRelayServer) | 

# namespace `Cellulo` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[`Cellulo::CelluloBluetoothEnums`](#classCellulo_1_1CelluloBluetoothEnums) | Wrapper containing all the enums of [CelluloBluetooth](#classCelluloBluetooth).
`class `[`Cellulo::CelluloRobot`](#classCellulo_1_1CelluloRobot) | The main object that represents a Cellulo robot. Inherits from `[CelluloBluetooth](#classCelluloBluetooth)` and has all its functionalities (not listed here).

# class `Cellulo::CelluloBluetoothEnums` 

```
class Cellulo::CelluloBluetoothEnums
  : public QObject
```  

Wrapper containing all the enums of [CelluloBluetooth](#classCelluloBluetooth).

This class is **singleton**, you can call `ThisClass.anyFunction()` and use `ThisClass.anyProperty` directly.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`enum `[`ConnectionStatus`](#classCellulo_1_1CelluloBluetoothEnums_1a9bdbb91140cd33c3daa779af49c7ed97) | Bluetooth connection status.
`enum `[`BatteryState`](#classCellulo_1_1CelluloBluetoothEnums_1a895a56801308039dd778b0a0fb6809b8) | Battery state of the robot.
`enum `[`LEDResponseMode`](#classCellulo_1_1CelluloBluetoothEnums_1a57ece08557723b6428a74ba3b1265b29) | LED response mode of the robot.
`enum `[`LocomotionInteractivityMode`](#classCellulo_1_1CelluloBluetoothEnums_1ae5126bceecb95ffc8846e8c72f379812) | Locomotion interactivity mode of the robot.
`enum `[`VisualEffect`](#classCellulo_1_1CelluloBluetoothEnums_1a810aca61e84c1e31fb751335cd776361) | List of possible visual effects.
`enum `[`Gesture`](#classCellulo_1_1CelluloBluetoothEnums_1aac0e86c82f086708674759431d6ff0fb) | List of possible getures.

## Members

#### `enum `[`ConnectionStatus`](#classCellulo_1_1CelluloBluetoothEnums_1a9bdbb91140cd33c3daa779af49c7ed97) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
ConnectionStatusDisconnected            | Idle and not connected
ConnectionStatusConnecting            | Actively trying to connect
ConnectionStatusConnected            | Connected
ConnectionStatusNumElements            | 

Bluetooth connection status.

#### `enum `[`BatteryState`](#classCellulo_1_1CelluloBluetoothEnums_1a895a56801308039dd778b0a0fb6809b8) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
BatteryStateDischarging            | No charger present, battery draining
BatteryStateLow            | No charger present, battery low, will shut down
BatteryStateCharging            | Charger present, battery charging
BatteryStateCharged            | Charger present, battery full
BatteryStateShutdown            | Charger charging disabled, voltage too low or battery not present
BatteryStateError            | Thermal fault or charge timeout
BatteryStateNumElements            | 

Battery state of the robot.

#### `enum `[`LEDResponseMode`](#classCellulo_1_1CelluloBluetoothEnums_1a57ece08557723b6428a74ba3b1265b29) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
LEDResponseModeResponsiveIndividual            | LEDs respond to touches by slightly increasing brightness
LEDResponseModeAbsolute            | LEDs don't respond to touches
LEDResponseModeResponsiveHold            | LEDs respond to hold by all changing color
LEDResponseModeNumElements            | 

LED response mode of the robot.

#### `enum `[`LocomotionInteractivityMode`](#classCellulo_1_1CelluloBluetoothEnums_1ae5126bceecb95ffc8846e8c72f379812) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
LocomotionInteractivityModeNormal            | Robot moves normally
LocomotionInteractivityModeRequiresHold            | Robot requires Hold gesture
LocomotionInteractivityModeNumElements            | 

Locomotion interactivity mode of the robot.

#### `enum `[`VisualEffect`](#classCellulo_1_1CelluloBluetoothEnums_1a810aca61e84c1e31fb751335cd776361) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
VisualEffectConstAll            | Set all LED colors (value unused)
VisualEffectConstSingle            | Set one LED color (value is LED index)
VisualEffectAlertAll            | Alert animation for all LEDs (value unused)
VisualEffectAlertSingle            | Alert animation for one LED (value is LED index)
VisualEffectProgress            | Static progress circularly (value 0-255 maps to 0-100%)
VisualEffectWaiting            | Circular waiting/processing animation (value unused)
VisualEffectDirection            | Point toward one direction (value 0-255 maps to 0-360 degrees)
VisualEffectBlink            | Alert forever (value*20 is LED on time in milliseconds)
VisualEffectBreathe            | Breathe animation (value unused)
VisualEffectPulse            | Slower breathe-like animation (value unused)
VisualEffectNumElements            | 

List of possible visual effects.

#### `enum `[`Gesture`](#classCellulo_1_1CelluloBluetoothEnums_1aac0e86c82f086708674759431d6ff0fb) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
GestureNone            | No gesture
GestureHold            | Robot is held
GestureNumElements            | 

List of possible getures.

# class `Cellulo::CelluloRobot` 

```
class Cellulo::CelluloRobot
  : public CelluloBluetooth
```  

The main object that represents a Cellulo robot. Inherits from `[CelluloBluetooth](#classCelluloBluetooth)` and has all its functionalities (not listed here).

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} QVector3D `[`vxyw`](#classCellulo_1_1CelluloRobot_1a3ff41aa3eaa381074e5553a126de3ce0) | Robot's estimated velocity in mm/s, mm/s, rad/s, read-only.
`{property} qreal `[`vx`](#classCellulo_1_1CelluloRobot_1a88f98737ed629ece9b4ded6d69f2090d) | Robot's estimated X velocity in mm/s, read-only.
`{property} qreal `[`vy`](#classCellulo_1_1CelluloRobot_1ae34e11c148c9a77dacf1fc94af910153) | Robot's estimated Y velocity in mm/s, read-only.
`{property} qreal `[`w`](#classCellulo_1_1CelluloRobot_1adba256d1ff2391f395d99dacd3111b5f) | Robot's estimated angular velocity in rad/s, read-only.
`{property} bool `[`poseVelControlEnabled`](#classCellulo_1_1CelluloRobot_1a3b59966b09c1f1b81d090aa1239de383) | Whether the simultaneous pose/velocity is enabled, must be set by the user, default false.
`{property} int `[`poseVelControlPeriod`](#classCellulo_1_1CelluloRobot_1ae9623a6305f54063ac903d13aefb49f1) | Desired pose/velocity control period in ms, set to 0 for highest possible frequency, default 20.
`{property} QVector3D `[`poseVelControlKGoalVel`](#classCellulo_1_1CelluloRobot_1afd3187099bb2b39dc99967e0631d4fd2) | Goal velocity coefficients when tracking pose/velocity, default (0.9, 0.9, 0.9), do not change if you don't have a good reason.
`{property} QVector3D `[`poseVelControlKGoalVelErr`](#classCellulo_1_1CelluloRobot_1ad0bd66a4a9b1744517a744e4470ec492) | Goal velocity error coefficients when tracking pose/velocity, default (0.2, 0.2, 0.2), do not change if you don't have a good reason.
`{property} QVector3D `[`poseVelControlKGoalPoseErr`](#classCellulo_1_1CelluloRobot_1a0461ff18bdf125f1587ff616368db7c2) | Goal pose error coefficients when tracking pose/velocity, default (2.0, 2.0, 2.3), do not change if you don't have a good reason.
`{property} QList< bool > `[`keysTouched`](#classCellulo_1_1CelluloRobot_1a93d1d8408926e0be31885b4c57afb768) | Whether the 6 keys are touched.
`{property} QList< bool > `[`keysLongTouched`](#classCellulo_1_1CelluloRobot_1ab2688290d750b53f9bf958c65dd70ff0) | Whether the 6 keys are long touched.
`{signal} public void `[`nextGoalPoseVelRequested`](#classCellulo_1_1CelluloRobot_1a9d942783a095a74edf14065de5e6e529)`(qreal deltaTime)` | Emitted when the controller needs the next goal pose and velocity.
`{slot} public void `[`setGoalPoseAndVelocity`](#classCellulo_1_1CelluloRobot_1a1594ddde1c1acedfa9b75b86da0c6148)`(qreal x,qreal y,qreal theta,qreal Vx,qreal Vy,qreal w,bool xEnabled,bool yEnabled,bool thetaEnabled)` | Sets the simultaneous pose and velocity goal of the robot, i.e the robot tries to be at the pose and move with the desired velocity while there.

## Members

#### `{property} QVector3D `[`vxyw`](#classCellulo_1_1CelluloRobot_1a3ff41aa3eaa381074e5553a126de3ce0) 

Robot's estimated velocity in mm/s, mm/s, rad/s, read-only.

Robot velocities: x,y in mm/s, z in rad/s (representing w)

#### `{property} qreal `[`vx`](#classCellulo_1_1CelluloRobot_1a88f98737ed629ece9b4ded6d69f2090d) 

Robot's estimated X velocity in mm/s, read-only.

#### `{property} qreal `[`vy`](#classCellulo_1_1CelluloRobot_1ae34e11c148c9a77dacf1fc94af910153) 

Robot's estimated Y velocity in mm/s, read-only.

#### `{property} qreal `[`w`](#classCellulo_1_1CelluloRobot_1adba256d1ff2391f395d99dacd3111b5f) 

Robot's estimated angular velocity in rad/s, read-only.

#### `{property} bool `[`poseVelControlEnabled`](#classCellulo_1_1CelluloRobot_1a3b59966b09c1f1b81d090aa1239de383) 

Whether the simultaneous pose/velocity is enabled, must be set by the user, default false.

Whether the simultaneous pose and velocity controller is enabled, must be enabled by the user.

#### `{property} int `[`poseVelControlPeriod`](#classCellulo_1_1CelluloRobot_1ae9623a6305f54063ac903d13aefb49f1) 

Desired pose/velocity control period in ms, set to 0 for highest possible frequency, default 20.

Desired pose/velocity control period in ms, set to 0 for highest possible frequency.

#### `{property} QVector3D `[`poseVelControlKGoalVel`](#classCellulo_1_1CelluloRobot_1afd3187099bb2b39dc99967e0631d4fd2) 

Goal velocity coefficients when tracking pose/velocity, default (0.9, 0.9, 0.9), do not change if you don't have a good reason.

Goal velocity coefficients when tracking pose/velocity.

#### `{property} QVector3D `[`poseVelControlKGoalVelErr`](#classCellulo_1_1CelluloRobot_1ad0bd66a4a9b1744517a744e4470ec492) 

Goal velocity error coefficients when tracking pose/velocity, default (0.2, 0.2, 0.2), do not change if you don't have a good reason.

Goal velocity error coefficients when tracking pose/velocity.

#### `{property} QVector3D `[`poseVelControlKGoalPoseErr`](#classCellulo_1_1CelluloRobot_1a0461ff18bdf125f1587ff616368db7c2) 

Goal pose error coefficients when tracking pose/velocity, default (2.0, 2.0, 2.3), do not change if you don't have a good reason.

Goal pose error coefficients when tracking pose/velocity.

#### `{property} QList< bool > `[`keysTouched`](#classCellulo_1_1CelluloRobot_1a93d1d8408926e0be31885b4c57afb768) 

Whether the 6 keys are touched.

Whether keys are touched.

#### `{property} QList< bool > `[`keysLongTouched`](#classCellulo_1_1CelluloRobot_1ab2688290d750b53f9bf958c65dd70ff0) 

Whether the 6 keys are long touched.

Whether keys are touched.

#### `{signal} public void `[`nextGoalPoseVelRequested`](#classCellulo_1_1CelluloRobot_1a9d942783a095a74edf14065de5e6e529)`(qreal deltaTime)` 

Emitted when the controller needs the next goal pose and velocity.

Upon receiving this signal, [setGoalPoseAndVelocity()](#classCellulo_1_1CelluloRobot_1a1594ddde1c1acedfa9b75b86da0c6148) should be called by the user if a user control loop that cycles on each received pose of the robot is present.

#### Parameters
* `deltaTime` Delta time in milliseconds that should be used if a controller differentiates or integrates in a loop triggered by this signal

#### `{slot} public void `[`setGoalPoseAndVelocity`](#classCellulo_1_1CelluloRobot_1a1594ddde1c1acedfa9b75b86da0c6148)`(qreal x,qreal y,qreal theta,qreal Vx,qreal Vy,qreal w,bool xEnabled,bool yEnabled,bool thetaEnabled)` 

Sets the simultaneous pose and velocity goal of the robot, i.e the robot tries to be at the pose and move with the desired velocity while there.

#### Parameters
* `x` X coordinate (larger than 0mm) 

* `y` Y coordinate (larger than 0mm) 

* `theta` Orientation (between -180 degrees and 180 degrees) 

* `Vx` X velocity (between -185 mm/s and and 185 mm/s) 

* `Vy` Y velocity (between -185 mm/s and and 185 mm/s) 

* `w` Angular velocity (between -7.5 rad/s and 7.5 rad/s) 

* `xEnabled` Whether to enable control on x, default true 

* `yEnabled` Whether to enable control on y, default true 

* `thetaEnabled` Whether to enable control on theta, default true

# class `CameraFrameImageProvider` 

```
class CameraFrameImageProvider
  : public QQuickImageProvider
```  

QImage provider from QByteArray.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CameraFrameImageProvider`](#classCameraFrameImageProvider_1a0cb30c9805d79426a683afe45ec4a4b9)`()` | 
`public QImage `[`requestImage`](#classCameraFrameImageProvider_1a8aa2a18b29502db727a32027c5a839d3)`(QString const & id,QSize * size,QSize const & requestedSize)` | 

## Members

#### `public  `[`CameraFrameImageProvider`](#classCameraFrameImageProvider_1a0cb30c9805d79426a683afe45ec4a4b9)`()` 

#### `public QImage `[`requestImage`](#classCameraFrameImageProvider_1a8aa2a18b29502db727a32027c5a839d3)`(QString const & id,QSize * size,QSize const & requestedSize)` 

# class `CelluloBluetooth` 

```
class CelluloBluetooth
  : public CelluloZoneClient
```  

Bluetooth communicator for a Cellulo robot.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} QString `[`localAdapterMacAddr`](#classCelluloBluetooth_1a7836e15b93cd5cb0756b20d37c81f41d) | MAC address of the local adapter to use when connecting to the robot, only works on Linux.
`{property} bool `[`autoConnect`](#classCelluloBluetooth_1aae68306a7aa2672394054abd3191c5bb) | Whether the socket will try to reconnect every time it drops, will connect when mac address is set.
`{property} QString `[`macAddr`](#classCelluloBluetooth_1a5375cc2f136cc73c5f8c1eb72a8c16e2) | Bluetooth MAC address of the server.
`{property} CelluloBluetoothEnums::ConnectionStatus `[`connectionStatus`](#classCelluloBluetooth_1aa126a939727eb99cbeb450d682e9dd24) | Bluetooth connection status.
`{property} CelluloBluetoothEnums::BatteryState `[`batteryState`](#classCelluloBluetooth_1a4dc33acde1c88ecb77ac95964c673503) | Current battery state.
`{property} float `[`x`](#classCelluloBluetooth_1ac6f0f93ed11198b4a11e054db5b4174d) | Current x position in mm.
`{property} float `[`y`](#classCelluloBluetooth_1a0d630fab04d15fc808d80a3d448cdb11) | Current y position in mm.
`{property} float `[`theta`](#classCelluloBluetooth_1abc03848eb9a0c8d0fa21d825c84fe3e6) | Current orientation in degrees.
`{property} bool `[`kidnapped`](#classCelluloBluetooth_1a1e0bbe55e2fabe69cfbf3587149af647) | Whether currently kidnapped.
`{property} CelluloBluetoothEnums::Gesture `[`gesture`](#classCelluloBluetooth_1a2d07c00994adec97db9f3af6de82b16f) | Current gesture.
`{property} bool `[`timestampingEnabled`](#classCelluloBluetooth_1a60bb98ff051f8b675a9ed46608390f6d) | Whether timestamping along with pose is enabled and idling disabled.
`{property} int `[`lastTimestamp`](#classCelluloBluetooth_1a0ac2d6eeb1b5eb527f6f4c58f84ec4e8) | Latest received onboard timestamp (in milliseconds)
`{property} float `[`framerate`](#classCelluloBluetooth_1a371262b0de0c702a7336b9724a251867) | Framerate calculated over time.
`{property} float `[`cameraImageProgress`](#classCelluloBluetooth_1a6e75d3adb21a479a8dea2d0d0c48bd92) | Camera image streaming progress.
`public  explicit `[`CelluloBluetooth`](#classCelluloBluetooth_1a2cd8c1e2d18b3fa9ecf43c8157e8e5f3)`(QQuickItem * parent)` | Creates a new Cellulo robot communicator.
`public virtual  `[`~CelluloBluetooth`](#classCelluloBluetooth_1aa4f1a76db4147b20c30de7756f60aeb8)`()` | Destroys this Cellulo robot communicator.
`public inline QString `[`getLocalAdapterMacAddr`](#classCelluloBluetooth_1a13d2664a51c278f992560a0594bab58d)`() const` | Get the chosen local adapter's MAC address.
`public inline bool `[`getAutoConnect`](#classCelluloBluetooth_1ac04e5e87de4f43c05a187b61f32be4a9)`()` | Gets whether the socket tries to reconnect when it drops, connects when mac address is set.
`public QVariantList `[`getFrame`](#classCelluloBluetooth_1a525eeb6b7fd43e409595742c2c67d1d2)`() const` | Gets the latest camera frame.
`public inline QString `[`getMacAddr`](#classCelluloBluetooth_1a3674d17d4a2291f8c50037bf679a638b)`()` | Gets the current MAC address.
`public inline CelluloBluetoothEnums::ConnectionStatus `[`getConnectionStatus`](#classCelluloBluetooth_1aff548470566a85ced744efd0ef2c1a68)`()` | Gets current Bluetooth connection status.
`public inline bool `[`getTimestampingEnabled`](#classCelluloBluetooth_1adabe723862d8e6b4a0be145f3653ee1c)`()` | Gets whether timestamping along with pose is currently enabled.
`public inline CelluloBluetoothEnums::BatteryState `[`getBatteryState`](#classCelluloBluetooth_1a96140bdeb8db23192d034d08bf02da02)`()` | Gets the latest battery state.
`public inline float `[`getX`](#classCelluloBluetooth_1a353c584c291379a7bdde2d8d37b88b95)`()` | Gets the latest x position.
`public inline float `[`getY`](#classCelluloBluetooth_1a4316ae671b74aab0aa0cb4ceef371080)`()` | Gets the latest y position.
`public inline float `[`getTheta`](#classCelluloBluetooth_1a9ea419ff52fcc98a2c637669b9e20125)`()` | Gets the latest orientation.
`public inline int `[`getLastTimestamp`](#classCelluloBluetooth_1a21ec48d70902394ca8bce2c03bb5b80f)`()` | Gets the latest available timestamp.
`public inline float `[`getFramerate`](#classCelluloBluetooth_1a1c9efc7143b345513794b8898ef9b1b4)`()` | Gets the localization framerate.
`public inline bool `[`getKidnapped`](#classCelluloBluetooth_1a06690c10ec703437b22aa7844cef9499)`()` | Gets the latest kidnapped state.
`public inline CelluloBluetoothEnums::Gesture `[`getGesture`](#classCelluloBluetooth_1a3c09e7d568ae684a0dc96e8727bf6896)`()` | Gets the current gesture.
`public inline float `[`getCameraImageProgress`](#classCelluloBluetooth_1aa22c4d5d2138f795a6098a6510853560)`()` | Gets the camera image progress.
`{signal} public void `[`localAdapterMacAddrChanged`](#classCelluloBluetooth_1af2382e32dbb8af7d75d4ed7b15c0a659)`()` | Emitted when the desired local adapter changes.
`{signal} public void `[`autoConnectChanged`](#classCelluloBluetooth_1a7c1d9052c6e694395031a94b15a00eaa)`()` | Auto connect strategy changed.
`{signal} public void `[`macAddrChanged`](#classCelluloBluetooth_1a623d1e33bd7474a2151e6a7e6bb648ca)`()` | Emitted when the MAC address changes.
`{signal} public void `[`connectionStatusChanged`](#classCelluloBluetooth_1afa082631e751a3de965ad652199da290)`()` | Emitted when Bluetooth connection status changes.
`{signal} public void `[`bootCompleted`](#classCelluloBluetooth_1a420fd1e4780ae686d57de7ab7f1eaef1)`()` | Emitted when the robot is ready after a power up or a reset.
`{signal} public void `[`shuttingDown`](#classCelluloBluetooth_1afdaded09d3a9a9eeeff84818cc4bc754)`()` | Emitted when the robot is about to sleep (shutdown) due to the user command via touch keys.
`{signal} public void `[`lowBattery`](#classCelluloBluetooth_1acdaf5f8354d9edb628f20518f7f45a30)`()` | Emitted when the robot is about to sleep (shutdown) due to low battery.
`{signal} public void `[`batteryStateChanged`](#classCelluloBluetooth_1a6a8de2995ace189a65092a0778d481a7)`()` | Emitted when the battery state changes.
`{signal} public void `[`touchBegan`](#classCelluloBluetooth_1aed0425f022a3a4cfbbc79142c9428037)`(int key)` | Emitted when a key is touched.
`{signal} public void `[`longTouch`](#classCelluloBluetooth_1a6d19a9c15347b0a0d62a910ccee3e28a)`(int key)` | Emitted when a key is touched for more than the long touch time.
`{signal} public void `[`touchReleased`](#classCelluloBluetooth_1a71b1d0fa9770ae9638b34d6d1f215999)`(int key)` | Emitted when a key is released.
`{signal} public void `[`gestureChanged`](#classCelluloBluetooth_1a6cbf2b03df06d2cb0480250b768bbf9c)`()` | Emitted when the gesture on the robot changes.
`{signal} public void `[`poseChanged_inherited`](#classCelluloBluetooth_1ae97ec0bc62cc48aa65ba7ca05ea908ba)`()` | DO NOT USE EXPLICITLY.
`{signal} public void `[`timestampChanged`](#classCelluloBluetooth_1ab1aa47981bdd88e980b66a7d22afbb57)`()` | A new onboard localization timestamp has been received.
`{signal} public void `[`kidnappedChanged`](#classCelluloBluetooth_1a5ec07a6c47b49f7552aaaa28a50e5ba6)`()` | Emitted when the kidnap state of the robot changes.
`{signal} public void `[`trackingGoalReached`](#classCelluloBluetooth_1a47f03e2b7cc139ade1ee2e3b73c29359)`()` | Emitted when pose/position/orientation goal is reached.
`{signal} public void `[`cameraImageProgressChanged`](#classCelluloBluetooth_1abc66a5a27dcb9662b241c75754c873a8)`()` | Emitted when a new camera image line is received.
`{signal} public void `[`frameReady`](#classCelluloBluetooth_1a0f4d459c4eee87be34dfdd12e2eeb1e2)`()` | Emitted when a camera frame from the robot is ready to read.
`{slot} public void `[`setLocalAdapterMacAddr`](#classCelluloBluetooth_1a575e6b84252f6e4c691043e27b8acee0)`(QString localAdapterMacAddr)` | Sets the MAC address of the local adapter to use when connecting to the robot.
`{slot} public void `[`setAutoConnect`](#classCelluloBluetooth_1aac8c78cd5617b9bd828a3808faddedc9)`(bool autoConnect)` | Sets whether the socket will try to reconnect when it drops, connects when mac address is set.
`{slot} public void `[`setMacAddr`](#classCelluloBluetooth_1a2f64c38944bf67d644a32f734b45779e)`(QString macAddr)` | Sets the MAC address of the server and immediately connects to it.
`{slot} public void `[`connectToServer`](#classCelluloBluetooth_1a84ea50aecaf82b4c6bad18f27f4d5f93)`()` | Creates socket and connects to the current target MAC address.
`{slot} public void `[`disconnectFromServer`](#classCelluloBluetooth_1aa35ba04f5a04974c85e45c6dbf5c74b6)`()` | Disconnects from the currently connected device and destroys the socket if possible.
`{slot} public void `[`setPoseBcastPeriod`](#classCelluloBluetooth_1a86e136276443c4fb7ecddb2f577a6f00)`(unsigned int period)` | Sets the pose broadcast period.
`{slot} public void `[`setTimestampingEnabled`](#classCelluloBluetooth_1a693ede4c55b4a9473dda42696cdaa201)`(bool enabled)` | Enables timestamping along with pose and disables pose idling or vice-versa.
`{slot} public void `[`setMotor1Output`](#classCelluloBluetooth_1aa0c6ff4a156053a1691fcd20e2329f06)`(int output)` | Sets output of motor 1.
`{slot} public void `[`setMotor2Output`](#classCelluloBluetooth_1a982e84f2569ef553b1fdc500ffca8acb)`(int output)` | Sets output of motor 2.
`{slot} public void `[`setMotor3Output`](#classCelluloBluetooth_1a6538d69fdf9a349e4b6317b3a6525011)`(int output)` | Sets output of motor 3.
`{slot} public void `[`setAllMotorOutputs`](#classCelluloBluetooth_1af2e645653bf5f44be38a3a12ad2a7f34)`(int m1output,int m2output,int m3output)` | Sets outputs of all motors.
`{slot} public void `[`setGoalVelocity`](#classCelluloBluetooth_1a45fcd08efd5f54acc9d0d7ac394ee8ae)`(float vx,float vy,float w)` | Sets robot goal velocity in global world frame.
`{slot} public void `[`setGoalPose`](#classCelluloBluetooth_1a1b9e87e13815417da14995af6d4c41c8)`(float x,float y,float theta,float v,float w)` | Sets a pose goal to track.
`{slot} public void `[`setGoalPosition`](#classCelluloBluetooth_1aefcacac8e953c60d0824d7c41b416189)`(float x,float y,float v)` | Sets a position goal to track.
`{slot} public void `[`setGoalXCoordinate`](#classCelluloBluetooth_1a6edd8d42ed8ecaf75c354c4e0ed7517f)`(float x,float v)` | Sets an X coordinate to track.
`{slot} public void `[`setGoalYCoordinate`](#classCelluloBluetooth_1aa3b3e1e3c77a3e331216e5369450c174)`(float y,float v)` | Sets a Y coordinate to track.
`{slot} public void `[`setGoalOrientation`](#classCelluloBluetooth_1abd7ed6fed814e632d2e73cf6f284aa0e)`(float theta,float w)` | Sets a position goal to track.
`{slot} public void `[`setGoalXThetaCoordinate`](#classCelluloBluetooth_1aa0783b43ce5352bb51f78b02407b67d7)`(float x,float theta,float v,float w)` | Sets an X and Theta goal at the same time.
`{slot} public void `[`setGoalYThetaCoordinate`](#classCelluloBluetooth_1a3e7762e1796b547aeffa76568d74f38e)`(float y,float theta,float v,float w)` | Sets a Y and Theta goal at the same time.
`{slot} public void `[`clearTracking`](#classCelluloBluetooth_1a0d4b5c15fd448f53094825b87fbd3f7b)`()` | Clears pose/position/velocity goals.
`{slot} public void `[`simpleVibrate`](#classCelluloBluetooth_1ad704c04dd187e8ee9f2fee20f2fa3845)`(float iX,float iY,float iTheta,unsigned int period,unsigned int duration)` | Constantly vibrates the robot.
`{slot} public void `[`vibrateOnMotion`](#classCelluloBluetooth_1a570f90bb872bbd867d609f1ee192097f)`(float iCoeff,unsigned int period)` | Enables vibration against motion.
`{slot} public void `[`clearHapticFeedback`](#classCelluloBluetooth_1a99cd609933e4305f54dbb698907ee8cc)`()` | Clears all haptic feedbacks.
`{slot} public void `[`ping`](#classCelluloBluetooth_1acf39a7628fd606fd508dfa518e078b86)`()` | Sends a ping, expecting an acknowledge.
`{slot} public void `[`requestFrame`](#classCelluloBluetooth_1abb01f282036d9da5bca947ba2b300448)`()` | Requests a camera frame to be sent.
`{slot} public void `[`setExposureTime`](#classCelluloBluetooth_1a61b49eb96246d87a08946f9f97b5512e)`(int pixels)` | Sets the exposure time for super-fast unkidnap detection for uniform and known paper colors known or enables autoexposure.
`{slot} public void `[`queryBatteryState`](#classCelluloBluetooth_1aebf5bf30f73bba6b36ded05e15e45159)`()` | Sends a battery state query.
`{slot} public void `[`setLEDResponseMode`](#classCelluloBluetooth_1aa947f4da0ebc8773085f94ca280101c7)`(CelluloBluetoothEnums::LEDResponseMode mode)` | Sets the LED response mode, i.e the LED visual response of the robot to touches.
`{slot} public void `[`setLocomotionInteractivityMode`](#classCelluloBluetooth_1a85422447a3e2fe4196943aaece7ed5de)`(CelluloBluetoothEnums::LocomotionInteractivityMode mode)` | Sets the locomotion interactivity mode, i.e the dependance of locomotion to user input.
`{slot} public void `[`setGestureEnabled`](#classCelluloBluetooth_1aaf73d22964f223ec5562fc341c335ac2)`(bool enabled)` | Enables/disables raw touch signal offset querying and processing.
`{slot} public void `[`setCasualBackdriveAssistEnabled`](#classCelluloBluetooth_1a76686c8a966b40696f2bee22dcd3edee)`(bool enabled)` | Enables/disables assist for easy backdriving.
`{slot} public void `[`setHapticBackdriveAssist`](#classCelluloBluetooth_1a34db590212bf9e8550f198a652534e07)`(float xAssist,float yAssist,float thetaAssist)` | Haptic feedback-oriented backdrive assist.
`{slot} public void `[`setVisualEffect`](#classCelluloBluetooth_1a409c8fdc5ddef1ec7c6ed36d697e9fba)`(CelluloBluetoothEnums::VisualEffect effect,QColor color,int value)` | Sets the visual effect on the robot, changing LED illumination.
`{slot} public void `[`polyBezierInit`](#classCelluloBluetooth_1a7ccf2d7537ea578bbcf01a243ea89c46)`(const QVector2D & point0)` | Sends the first control point of the composite Bézier curve for motion tracking.
`{slot} public void `[`polyBezierAppend`](#classCelluloBluetooth_1a20c7612aa3fb9f01f760ad5437226a2e)`(const QVector2D & point1,const QVector2D & point2,const QVector2D & point3)` | Adds a segment to the composite Bézier curve for motion tracking; [polyBezierInit()](#classCelluloBluetooth_1a7ccf2d7537ea578bbcf01a243ea89c46) must be called before.
`{slot} public void `[`polyBezierSetFromZone`](#classCelluloBluetooth_1a1c991b608d73ac95fca4f48949490f25)`(CelluloZone * zone)` | Sends the composite Bézier curve in the zone to the robot.
`{slot} public void `[`setGoalPolyBezier`](#classCelluloBluetooth_1a58c5e750ecdac6f00a7fcdf991b00481)`(float v,float w)` | Starts tracking the previously set composite Bézier curve.
`{slot} public void `[`setGoalPolyBezierAligned`](#classCelluloBluetooth_1aa5df9a58af8b395b4146600dd820766b)`(float v,float theta,float w)` | Starts tracking the previously set composite Bézier curve while keeping orientation aligned to the curve.
`{slot} public void `[`reset`](#classCelluloBluetooth_1a6f60aac2259a6e6e72f221ebfb9a00d4)`()` | Initiates a software reset on the robot.
`{slot} public void `[`shutdown`](#classCelluloBluetooth_1a8115abd66d4acd9aaf7d8e1aeab91fae)`()` | Initiates sleep on the robot.

## Members

#### `{property} QString `[`localAdapterMacAddr`](#classCelluloBluetooth_1a7836e15b93cd5cb0756b20d37c81f41d) 

MAC address of the local adapter to use when connecting to the robot, only works on Linux.

#### `{property} bool `[`autoConnect`](#classCelluloBluetooth_1aae68306a7aa2672394054abd3191c5bb) 

Whether the socket will try to reconnect every time it drops, will connect when mac address is set.

#### `{property} QString `[`macAddr`](#classCelluloBluetooth_1a5375cc2f136cc73c5f8c1eb72a8c16e2) 

Bluetooth MAC address of the server.

#### `{property} CelluloBluetoothEnums::ConnectionStatus `[`connectionStatus`](#classCelluloBluetooth_1aa126a939727eb99cbeb450d682e9dd24) 

Bluetooth connection status.

#### `{property} CelluloBluetoothEnums::BatteryState `[`batteryState`](#classCelluloBluetooth_1a4dc33acde1c88ecb77ac95964c673503) 

Current battery state.

#### `{property} float `[`x`](#classCelluloBluetooth_1ac6f0f93ed11198b4a11e054db5b4174d) 

Current x position in mm.

#### `{property} float `[`y`](#classCelluloBluetooth_1a0d630fab04d15fc808d80a3d448cdb11) 

Current y position in mm.

#### `{property} float `[`theta`](#classCelluloBluetooth_1abc03848eb9a0c8d0fa21d825c84fe3e6) 

Current orientation in degrees.

#### `{property} bool `[`kidnapped`](#classCelluloBluetooth_1a1e0bbe55e2fabe69cfbf3587149af647) 

Whether currently kidnapped.

#### `{property} CelluloBluetoothEnums::Gesture `[`gesture`](#classCelluloBluetooth_1a2d07c00994adec97db9f3af6de82b16f) 

Current gesture.

#### `{property} bool `[`timestampingEnabled`](#classCelluloBluetooth_1a60bb98ff051f8b675a9ed46608390f6d) 

Whether timestamping along with pose is enabled and idling disabled.

#### `{property} int `[`lastTimestamp`](#classCelluloBluetooth_1a0ac2d6eeb1b5eb527f6f4c58f84ec4e8) 

Latest received onboard timestamp (in milliseconds)

#### `{property} float `[`framerate`](#classCelluloBluetooth_1a371262b0de0c702a7336b9724a251867) 

Framerate calculated over time.

#### `{property} float `[`cameraImageProgress`](#classCelluloBluetooth_1a6e75d3adb21a479a8dea2d0d0c48bd92) 

Camera image streaming progress.

#### `public  explicit `[`CelluloBluetooth`](#classCelluloBluetooth_1a2cd8c1e2d18b3fa9ecf43c8157e8e5f3)`(QQuickItem * parent)` 

Creates a new Cellulo robot communicator.

#### Parameters
* `parent` Parent of this QML item

#### `public virtual  `[`~CelluloBluetooth`](#classCelluloBluetooth_1aa4f1a76db4147b20c30de7756f60aeb8)`()` 

Destroys this Cellulo robot communicator.

#### `public inline QString `[`getLocalAdapterMacAddr`](#classCelluloBluetooth_1a13d2664a51c278f992560a0594bab58d)`() const` 

Get the chosen local adapter's MAC address.

#### Returns
Chosen local adapter's MAC address, empty string if using default adapter

#### `public inline bool `[`getAutoConnect`](#classCelluloBluetooth_1ac04e5e87de4f43c05a187b61f32be4a9)`()` 

Gets whether the socket tries to reconnect when it drops, connects when mac address is set.

#### Returns
Whether the socket tries to reconnect when it drops, connects when mac address is set

#### `public QVariantList `[`getFrame`](#classCelluloBluetooth_1a525eeb6b7fd43e409595742c2c67d1d2)`() const` 

Gets the latest camera frame.

#### Returns
The latest camera frame; IMG_WIDTH*IMG_HEIGHT many ints in grayscale, 0 to 255

#### `public inline QString `[`getMacAddr`](#classCelluloBluetooth_1a3674d17d4a2291f8c50037bf679a638b)`()` 

Gets the current MAC address.

#### Returns
The current MAC address

#### `public inline CelluloBluetoothEnums::ConnectionStatus `[`getConnectionStatus`](#classCelluloBluetooth_1aff548470566a85ced744efd0ef2c1a68)`()` 

Gets current Bluetooth connection status.

#### Returns
Current Bluetooth connection status

#### `public inline bool `[`getTimestampingEnabled`](#classCelluloBluetooth_1adabe723862d8e6b4a0be145f3653ee1c)`()` 

Gets whether timestamping along with pose is currently enabled.

#### Returns
Whether timestamping is enabled

#### `public inline CelluloBluetoothEnums::BatteryState `[`getBatteryState`](#classCelluloBluetooth_1a96140bdeb8db23192d034d08bf02da02)`()` 

Gets the latest battery state.

#### Returns
Battery state

#### `public inline float `[`getX`](#classCelluloBluetooth_1a353c584c291379a7bdde2d8d37b88b95)`()` 

Gets the latest x position.

#### Returns
Latest x position in mm

#### `public inline float `[`getY`](#classCelluloBluetooth_1a4316ae671b74aab0aa0cb4ceef371080)`()` 

Gets the latest y position.

#### Returns
Latest y position in mm

#### `public inline float `[`getTheta`](#classCelluloBluetooth_1a9ea419ff52fcc98a2c637669b9e20125)`()` 

Gets the latest orientation.

#### Returns
Latest orientation in degrees

#### `public inline int `[`getLastTimestamp`](#classCelluloBluetooth_1a21ec48d70902394ca8bce2c03bb5b80f)`()` 

Gets the latest available timestamp.

#### Returns
The latest received timestamp in milliseconds

#### `public inline float `[`getFramerate`](#classCelluloBluetooth_1a1c9efc7143b345513794b8898ef9b1b4)`()` 

Gets the localization framerate.

#### Returns
Localization framerate in milliseconds

#### `public inline bool `[`getKidnapped`](#classCelluloBluetooth_1a06690c10ec703437b22aa7844cef9499)`()` 

Gets the latest kidnapped state.

#### Returns
Whether kidnapped or on encoded paper

#### `public inline CelluloBluetoothEnums::Gesture `[`getGesture`](#classCelluloBluetooth_1a3c09e7d568ae684a0dc96e8727bf6896)`()` 

Gets the current gesture.

#### Returns
Current gesture

#### `public inline float `[`getCameraImageProgress`](#classCelluloBluetooth_1aa22c4d5d2138f795a6098a6510853560)`()` 

Gets the camera image progress.

#### Returns
Between 0.0 and 1.0

#### `{signal} public void `[`localAdapterMacAddrChanged`](#classCelluloBluetooth_1af2382e32dbb8af7d75d4ed7b15c0a659)`()` 

Emitted when the desired local adapter changes.

#### `{signal} public void `[`autoConnectChanged`](#classCelluloBluetooth_1a7c1d9052c6e694395031a94b15a00eaa)`()` 

Auto connect strategy changed.

#### `{signal} public void `[`macAddrChanged`](#classCelluloBluetooth_1a623d1e33bd7474a2151e6a7e6bb648ca)`()` 

Emitted when the MAC address changes.

#### `{signal} public void `[`connectionStatusChanged`](#classCelluloBluetooth_1afa082631e751a3de965ad652199da290)`()` 

Emitted when Bluetooth connection status changes.

#### `{signal} public void `[`bootCompleted`](#classCelluloBluetooth_1a420fd1e4780ae686d57de7ab7f1eaef1)`()` 

Emitted when the robot is ready after a power up or a reset.

#### `{signal} public void `[`shuttingDown`](#classCelluloBluetooth_1afdaded09d3a9a9eeeff84818cc4bc754)`()` 

Emitted when the robot is about to sleep (shutdown) due to the user command via touch keys.

#### `{signal} public void `[`lowBattery`](#classCelluloBluetooth_1acdaf5f8354d9edb628f20518f7f45a30)`()` 

Emitted when the robot is about to sleep (shutdown) due to low battery.

#### `{signal} public void `[`batteryStateChanged`](#classCelluloBluetooth_1a6a8de2995ace189a65092a0778d481a7)`()` 

Emitted when the battery state changes.

#### `{signal} public void `[`touchBegan`](#classCelluloBluetooth_1aed0425f022a3a4cfbbc79142c9428037)`(int key)` 

Emitted when a key is touched.

#### Parameters
* `key` The key that is touched

#### `{signal} public void `[`longTouch`](#classCelluloBluetooth_1a6d19a9c15347b0a0d62a910ccee3e28a)`(int key)` 

Emitted when a key is touched for more than the long touch time.

#### Parameters
* `key` The key that is touched

#### `{signal} public void `[`touchReleased`](#classCelluloBluetooth_1a71b1d0fa9770ae9638b34d6d1f215999)`(int key)` 

Emitted when a key is released.

#### Parameters
* `key` The key that is released

#### `{signal} public void `[`gestureChanged`](#classCelluloBluetooth_1a6cbf2b03df06d2cb0480250b768bbf9c)`()` 

Emitted when the gesture on the robot changes.

#### `{signal} public void `[`poseChanged_inherited`](#classCelluloBluetooth_1ae97ec0bc62cc48aa65ba7ca05ea908ba)`()` 

DO NOT USE EXPLICITLY.

Emitted when the base class emits poseChanged() since NOTIFY cannot be used with inherited signals

#### `{signal} public void `[`timestampChanged`](#classCelluloBluetooth_1ab1aa47981bdd88e980b66a7d22afbb57)`()` 

A new onboard localization timestamp has been received.

#### `{signal} public void `[`kidnappedChanged`](#classCelluloBluetooth_1a5ec07a6c47b49f7552aaaa28a50e5ba6)`()` 

Emitted when the kidnap state of the robot changes.

#### `{signal} public void `[`trackingGoalReached`](#classCelluloBluetooth_1a47f03e2b7cc139ade1ee2e3b73c29359)`()` 

Emitted when pose/position/orientation goal is reached.

#### `{signal} public void `[`cameraImageProgressChanged`](#classCelluloBluetooth_1abc66a5a27dcb9662b241c75754c873a8)`()` 

Emitted when a new camera image line is received.

#### `{signal} public void `[`frameReady`](#classCelluloBluetooth_1a0f4d459c4eee87be34dfdd12e2eeb1e2)`()` 

Emitted when a camera frame from the robot is ready to read.

#### `{slot} public void `[`setLocalAdapterMacAddr`](#classCelluloBluetooth_1a575e6b84252f6e4c691043e27b8acee0)`(QString localAdapterMacAddr)` 

Sets the MAC address of the local adapter to use when connecting to the robot.

Only works on Linux; must be built with bluez.

#### Parameters
* `localAdapterMacAddr` MAC address of the local adapter, must exist; set to empty string to connect with default adapter

#### `{slot} public void `[`setAutoConnect`](#classCelluloBluetooth_1aac8c78cd5617b9bd828a3808faddedc9)`(bool autoConnect)` 

Sets whether the socket will try to reconnect when it drops, connects when mac address is set.

#### Parameters
* `autoReconnect` Whether the socket will try to reconnect when it drops, connects when mac address is set

#### `{slot} public void `[`setMacAddr`](#classCelluloBluetooth_1a2f64c38944bf67d644a32f734b45779e)`(QString macAddr)` 

Sets the MAC address of the server and immediately connects to it.

#### Parameters
* `macAddr` Bluetooth MAC address of the server (robot)

#### `{slot} public void `[`connectToServer`](#classCelluloBluetooth_1a84ea50aecaf82b4c6bad18f27f4d5f93)`()` 

Creates socket and connects to the current target MAC address.

#### `{slot} public void `[`disconnectFromServer`](#classCelluloBluetooth_1aa35ba04f5a04974c85e45c6dbf5c74b6)`()` 

Disconnects from the currently connected device and destroys the socket if possible.

#### `{slot} public void `[`setPoseBcastPeriod`](#classCelluloBluetooth_1a86e136276443c4fb7ecddb2f577a6f00)`(unsigned int period)` 

Sets the pose broadcast period.

#### Parameters
* `period` Desired period in milliseconds

#### `{slot} public void `[`setTimestampingEnabled`](#classCelluloBluetooth_1a693ede4c55b4a9473dda42696cdaa201)`(bool enabled)` 

Enables timestamping along with pose and disables pose idling or vice-versa.

#### Parameters
* `enabled` Whether to enable timestamping

#### `{slot} public void `[`setMotor1Output`](#classCelluloBluetooth_1aa0c6ff4a156053a1691fcd20e2329f06)`(int output)` 

Sets output of motor 1.

#### Parameters
* `output` Value between -0xFFF and 0xFFF

#### `{slot} public void `[`setMotor2Output`](#classCelluloBluetooth_1a982e84f2569ef553b1fdc500ffca8acb)`(int output)` 

Sets output of motor 2.

#### Parameters
* `output` Value between -0xFFF and 0xFFF

#### `{slot} public void `[`setMotor3Output`](#classCelluloBluetooth_1a6538d69fdf9a349e4b6317b3a6525011)`(int output)` 

Sets output of motor 3.

#### Parameters
* `output` Value between -0xFFF and 0xFFF

#### `{slot} public void `[`setAllMotorOutputs`](#classCelluloBluetooth_1af2e645653bf5f44be38a3a12ad2a7f34)`(int m1output,int m2output,int m3output)` 

Sets outputs of all motors.

#### Parameters
* `m1output` Value between -0xFFF and 0xFFF 

* `m2output` Value between -0xFFF and 0xFFF 

* `m3output` Value between -0xFFF and 0xFFF

#### `{slot} public void `[`setGoalVelocity`](#classCelluloBluetooth_1a45fcd08efd5f54acc9d0d7ac394ee8ae)`(float vx,float vy,float w)` 

Sets robot goal velocity in global world frame.

#### Parameters
* `vx` X velocity in mm/s 

* `vy` Y velocity in mm/s 

* `w` Angular velocity in rad/s

#### `{slot} public void `[`setGoalPose`](#classCelluloBluetooth_1a1b9e87e13815417da14995af6d4c41c8)`(float x,float y,float theta,float v,float w)` 

Sets a pose goal to track.

#### Parameters
* `x` X goal in mm 

* `y` Y goal in mm 

* `theta` Theta goal in degrees 

* `v` Maximum linear speed to track pose in mm/s 

* `w` Maximum angular speed to track pose in rad/s

#### `{slot} public void `[`setGoalPosition`](#classCelluloBluetooth_1aefcacac8e953c60d0824d7c41b416189)`(float x,float y,float v)` 

Sets a position goal to track.

#### Parameters
* `x` X goal in mm 

* `y` Y goal in mm 

* `v` Maximum linear speed to track pose in mm/s

#### `{slot} public void `[`setGoalXCoordinate`](#classCelluloBluetooth_1a6edd8d42ed8ecaf75c354c4e0ed7517f)`(float x,float v)` 

Sets an X coordinate to track.

#### Parameters
* `x` X goal in mm 

* `v` Maximum linear speed to track pose in mm/s

#### `{slot} public void `[`setGoalYCoordinate`](#classCelluloBluetooth_1aa3b3e1e3c77a3e331216e5369450c174)`(float y,float v)` 

Sets a Y coordinate to track.

#### Parameters
* `y` Y goal in mm 

* `v` Maximum linear speed to track pose in mm/s

#### `{slot} public void `[`setGoalOrientation`](#classCelluloBluetooth_1abd7ed6fed814e632d2e73cf6f284aa0e)`(float theta,float w)` 

Sets a position goal to track.

#### Parameters
* `theta` Theta goal in degrees 

* `w` Maximum angular speed to track pose in rad/s

#### `{slot} public void `[`setGoalXThetaCoordinate`](#classCelluloBluetooth_1aa0783b43ce5352bb51f78b02407b67d7)`(float x,float theta,float v,float w)` 

Sets an X and Theta goal at the same time.

#### Parameters
* `x` X goal in mm 

* `theta` Theta goal in degrees 

* `v` Maximum linear speed to track pose in mm/s 

* `w` Maximum angular speed to track pose in rad/s

#### `{slot} public void `[`setGoalYThetaCoordinate`](#classCelluloBluetooth_1a3e7762e1796b547aeffa76568d74f38e)`(float y,float theta,float v,float w)` 

Sets a Y and Theta goal at the same time.

#### Parameters
* `y` Y goal in mm 

* `theta` Theta goal in degrees 

* `v` Maximum linear speed to track pose in mm/s 

* `w` Maximum angular speed to track pose in rad/s

#### `{slot} public void `[`clearTracking`](#classCelluloBluetooth_1a0d4b5c15fd448f53094825b87fbd3f7b)`()` 

Clears pose/position/velocity goals.

#### `{slot} public void `[`simpleVibrate`](#classCelluloBluetooth_1ad704c04dd187e8ee9f2fee20f2fa3845)`(float iX,float iY,float iTheta,unsigned int period,unsigned int duration)` 

Constantly vibrates the robot.

#### Parameters
* `iX` X intensity, scale is the same as linear velocity 

* `iY` Y intensity, scale is the same as linear velocity 

* `iTheta` Theta intensity, scale is the same as angular velocity 

* `period` Period of vibration in milliseconds, maximum is 0xFFFF 

* `duration` Duration of vibration in milliseconds, maximum is 0xFFFF, 0 for vibrate forever

#### `{slot} public void `[`vibrateOnMotion`](#classCelluloBluetooth_1a570f90bb872bbd867d609f1ee192097f)`(float iCoeff,unsigned int period)` 

Enables vibration against motion.

#### Parameters
* `iCoeff` Vibration intensity with respect to the drive velocities 

* `period` Period of vibration in milliseconds, maximum is 0xFFFF

#### `{slot} public void `[`clearHapticFeedback`](#classCelluloBluetooth_1a99cd609933e4305f54dbb698907ee8cc)`()` 

Clears all haptic feedbacks.

#### `{slot} public void `[`ping`](#classCelluloBluetooth_1acf39a7628fd606fd508dfa518e078b86)`()` 

Sends a ping, expecting an acknowledge.

#### `{slot} public void `[`requestFrame`](#classCelluloBluetooth_1abb01f282036d9da5bca947ba2b300448)`()` 

Requests a camera frame to be sent.

#### `{slot} public void `[`setExposureTime`](#classCelluloBluetooth_1a61b49eb96246d87a08946f9f97b5512e)`(int pixels)` 

Sets the exposure time for super-fast unkidnap detection for uniform and known paper colors known or enables autoexposure.

460 pixels for the latest white plastic frame and white paper is a good value.

#### Parameters
* `pixels` Exposure time in pixels, must be larger than 260; 0 is a special value that enables autoexposure

#### `{slot} public void `[`queryBatteryState`](#classCelluloBluetooth_1aebf5bf30f73bba6b36ded05e15e45159)`()` 

Sends a battery state query.

#### `{slot} public void `[`setLEDResponseMode`](#classCelluloBluetooth_1aa947f4da0ebc8773085f94ca280101c7)`(CelluloBluetoothEnums::LEDResponseMode mode)` 

Sets the LED response mode, i.e the LED visual response of the robot to touches.

#### Parameters
* `mode` LED resposne mode

#### `{slot} public void `[`setLocomotionInteractivityMode`](#classCelluloBluetooth_1a85422447a3e2fe4196943aaece7ed5de)`(CelluloBluetoothEnums::LocomotionInteractivityMode mode)` 

Sets the locomotion interactivity mode, i.e the dependance of locomotion to user input.

#### Parameters
* `mode` Locomotion interactivity mode

#### `{slot} public void `[`setGestureEnabled`](#classCelluloBluetooth_1aaf73d22964f223ec5562fc341c335ac2)`(bool enabled)` 

Enables/disables raw touch signal offset querying and processing.

#### Parameters
* `enabled` Whether to enable

#### `{slot} public void `[`setCasualBackdriveAssistEnabled`](#classCelluloBluetooth_1a76686c8a966b40696f2bee22dcd3edee)`(bool enabled)` 

Enables/disables assist for easy backdriving.

#### Parameters
* `enabled` Whether to enable

#### `{slot} public void `[`setHapticBackdriveAssist`](#classCelluloBluetooth_1a34db590212bf9e8550f198a652534e07)`(float xAssist,float yAssist,float thetaAssist)` 

Haptic feedback-oriented backdrive assist.

Pass 0 to all parameters to disable. Disables casual backdrive assist upon enabling.

#### Parameters
* `xAssist` X assist with respect to x drive velocity, can be negative 

* `yAssist` Y assist with respect to y drive velocity, can be negative 

* `thetaAssist` Theta assist with respect to w drive, can be negative

#### `{slot} public void `[`setVisualEffect`](#classCelluloBluetooth_1a409c8fdc5ddef1ec7c6ed36d697e9fba)`(CelluloBluetoothEnums::VisualEffect effect,QColor color,int value)` 

Sets the visual effect on the robot, changing LED illumination.

#### Parameters
* `effect` The effect ordinal 

* `color` Color 

* `value` A value possibly meaningful for the effect (between 0 and 255)

#### `{slot} public void `[`polyBezierInit`](#classCelluloBluetooth_1a7ccf2d7537ea578bbcf01a243ea89c46)`(const QVector2D & point0)` 

Sends the first control point of the composite Bézier curve for motion tracking.

#### Parameters
* `point0` The initial point, i.e the first control point of the first segment

#### `{slot} public void `[`polyBezierAppend`](#classCelluloBluetooth_1a20c7612aa3fb9f01f760ad5437226a2e)`(const QVector2D & point1,const QVector2D & point2,const QVector2D & point3)` 

Adds a segment to the composite Bézier curve for motion tracking; [polyBezierInit()](#classCelluloBluetooth_1a7ccf2d7537ea578bbcf01a243ea89c46) must be called before.

The first control point is the last control point of the previously added segment or the initial point.

#### Parameters
* `point1` The second control point for the curve 

* `point2` The third control point for the curve 

* `point3` The fourth control point for the curve

#### `{slot} public void `[`polyBezierSetFromZone`](#classCelluloBluetooth_1a1c991b608d73ac95fca4f48949490f25)`(CelluloZone * zone)` 

Sends the composite Bézier curve in the zone to the robot.

#### Parameters
* `zone` The zone that contains the composite Bézier curve path

#### `{slot} public void `[`setGoalPolyBezier`](#classCelluloBluetooth_1a58c5e750ecdac6f00a7fcdf991b00481)`(float v,float w)` 

Starts tracking the previously set composite Bézier curve.

#### Parameters
* `v` Linear velocity tangent to the curve 

* `w` Angular velocity throughout the traversal

#### `{slot} public void `[`setGoalPolyBezierAligned`](#classCelluloBluetooth_1aa5df9a58af8b395b4146600dd820766b)`(float v,float theta,float w)` 

Starts tracking the previously set composite Bézier curve while keeping orientation aligned to the curve.

#### Parameters
* `v` Linear velocity tangent to the curve 

* `theta` Orientation to track with respect to the curve tangent orientation, in degrees 

* `w` Maximum angular velocity while tracking orientation, in rad/s

#### `{slot} public void `[`reset`](#classCelluloBluetooth_1a6f60aac2259a6e6e72f221ebfb9a00d4)`()` 

Initiates a software reset on the robot.

#### `{slot} public void `[`shutdown`](#classCelluloBluetooth_1a8115abd66d4acd9aaf7d8e1aeab91fae)`()` 

Initiates sleep on the robot.

# class `CelluloBluetoothEMP` 

```
class CelluloBluetoothEMP
  : public QQuickItem
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} bool `[`continuous`](#classCelluloBluetoothEMP_1a57fbcba07a125504001d358ecf2b6e48) | Whether to blast same robots.
`{property} QStringList `[`macAddrToBlast`](#classCelluloBluetoothEMP_1a80301e3720211a0ca339467fd9f556f9) | List of mac addresses that are being blasted.
`{property} QStringList `[`macAddrBlasted`](#classCelluloBluetoothEMP_1a8674de706d8466f9aeb62aabdeb4830f) | List of mac addresses that are confirmed to be blasted.
`public  explicit `[`CelluloBluetoothEMP`](#classCelluloBluetoothEMP_1a07e7c6e15ac3f974aceed7d6786da4a2)`(QQuickItem * parent)` | Creates a new EMP blaster.
`public virtual  `[`~CelluloBluetoothEMP`](#classCelluloBluetoothEMP_1ab3080112b93ad6214c468b9ff77550de)`()` | Destroys this EMP blaster.
`public inline bool `[`getContinuous`](#classCelluloBluetoothEMP_1aa53dc4d25230e7b264b09358cc27b8db)`()` | Gets whether to blast same robots.
`public inline QStringList `[`getMacAddrToBlast`](#classCelluloBluetoothEMP_1a29aba45acbc2fe169c0852c227717238)`() const` | Gets the mac addresses of robots that are waiting to be blasted.
`public inline QStringList `[`getMacAddrBlasted`](#classCelluloBluetoothEMP_1a4a35114a80408b9ffb7b6ed2fc4ad978)`() const` | Gets the mac addresses of robots that are confirmed to be blasted.
`{signal} public void `[`continuousChanged`](#classCelluloBluetoothEMP_1a597015df3660046071aa724cce896ea0)`()` | Whether to blast same robots strategy changed.
`{signal} public void `[`macAddrToBlastChanged`](#classCelluloBluetoothEMP_1a69dec88fba645f57ebaa617a427e02f2)`()` | Emitted when list of mac addresses waiting to be blasted changes.
`{signal} public void `[`macAddrBlastedChanged`](#classCelluloBluetoothEMP_1a558865a1d22781809a5c52f84529fedf)`()` | Emitted when list of mac addresses confirmed to be blasted changes.
`{slot} public void `[`setContinuous`](#classCelluloBluetoothEMP_1a698b6d37c0f91733e9a375b2257608a6)`(bool continuous)` | Sets whether to blast same robots.
`{slot} public void `[`resetLater`](#classCelluloBluetoothEMP_1a57e79f8d43eac34a719a9daea9660403)`(QString macAddr)` | Initiates connection to the robot to reset it when it's connected.
`{slot} public void `[`shutdownLater`](#classCelluloBluetoothEMP_1a15e0cbfa49c37ed7fafbac491dda1a71)`(QString macAddr)` | Initiates connection to the robot to shut it down when it's connected.
`{slot} public void `[`clear`](#classCelluloBluetoothEMP_1af9369395d05fb3fb41fe0a80e156b43b)`()` | Clears both lists, drops all connections.

## Members

#### `{property} bool `[`continuous`](#classCelluloBluetoothEMP_1a57fbcba07a125504001d358ecf2b6e48) 

Whether to blast same robots.

#### `{property} QStringList `[`macAddrToBlast`](#classCelluloBluetoothEMP_1a80301e3720211a0ca339467fd9f556f9) 

List of mac addresses that are being blasted.

#### `{property} QStringList `[`macAddrBlasted`](#classCelluloBluetoothEMP_1a8674de706d8466f9aeb62aabdeb4830f) 

List of mac addresses that are confirmed to be blasted.

#### `public  explicit `[`CelluloBluetoothEMP`](#classCelluloBluetoothEMP_1a07e7c6e15ac3f974aceed7d6786da4a2)`(QQuickItem * parent)` 

Creates a new EMP blaster.

#### Parameters
* `parent` Parent of this QML item

#### `public virtual  `[`~CelluloBluetoothEMP`](#classCelluloBluetoothEMP_1ab3080112b93ad6214c468b9ff77550de)`()` 

Destroys this EMP blaster.

#### `public inline bool `[`getContinuous`](#classCelluloBluetoothEMP_1aa53dc4d25230e7b264b09358cc27b8db)`()` 

Gets whether to blast same robots.

#### Returns
Whether to blast same robots

#### `public inline QStringList `[`getMacAddrToBlast`](#classCelluloBluetoothEMP_1a29aba45acbc2fe169c0852c227717238)`() const` 

Gets the mac addresses of robots that are waiting to be blasted.

#### Returns
Mac addresses of robots that are waiting to be blasted

#### `public inline QStringList `[`getMacAddrBlasted`](#classCelluloBluetoothEMP_1a4a35114a80408b9ffb7b6ed2fc4ad978)`() const` 

Gets the mac addresses of robots that are confirmed to be blasted.

#### Returns
Mac addresses of robots that are confirmed to be blasted

#### `{signal} public void `[`continuousChanged`](#classCelluloBluetoothEMP_1a597015df3660046071aa724cce896ea0)`()` 

Whether to blast same robots strategy changed.

#### `{signal} public void `[`macAddrToBlastChanged`](#classCelluloBluetoothEMP_1a69dec88fba645f57ebaa617a427e02f2)`()` 

Emitted when list of mac addresses waiting to be blasted changes.

#### `{signal} public void `[`macAddrBlastedChanged`](#classCelluloBluetoothEMP_1a558865a1d22781809a5c52f84529fedf)`()` 

Emitted when list of mac addresses confirmed to be blasted changes.

#### `{slot} public void `[`setContinuous`](#classCelluloBluetoothEMP_1a698b6d37c0f91733e9a375b2257608a6)`(bool continuous)` 

Sets whether to blast same robots.

#### Parameters
* `continuous` Whether to blast same robots

#### `{slot} public void `[`resetLater`](#classCelluloBluetoothEMP_1a57e79f8d43eac34a719a9daea9660403)`(QString macAddr)` 

Initiates connection to the robot to reset it when it's connected.

#### `{slot} public void `[`shutdownLater`](#classCelluloBluetoothEMP_1a15e0cbfa49c37ed7fafbac491dda1a71)`(QString macAddr)` 

Initiates connection to the robot to shut it down when it's connected.

#### `{slot} public void `[`clear`](#classCelluloBluetoothEMP_1af9369395d05fb3fb41fe0a80e156b43b)`()` 

Clears both lists, drops all connections.

# class `CelluloBluetoothScanner` 

```
class CelluloBluetoothScanner
  : public QQuickItem
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} bool `[`continuous`](#classCelluloBluetoothScanner_1a14148bced248eb2718eab2761674bfdf) | Whether to continuously scan.
`{property} bool `[`scanning`](#classCelluloBluetoothScanner_1a1a20e2fa83811cdf0a4aa1719e947af5) | 
`{property} QStringList `[`foundRobots`](#classCelluloBluetoothScanner_1ab5bf8c5660aaed4825f1fa56a034e9d4) | List of robot MAC addresses that are found.
`public  `[`CelluloBluetoothScanner`](#classCelluloBluetoothScanner_1aaabcd5a86babbdee4f8b34fce274de34)`(QQuickItem * parent)` | Creates a new Cellulo robot scanner.
`public virtual  `[`~CelluloBluetoothScanner`](#classCelluloBluetoothScanner_1a589f4beeb292795676ddc9d2e0cb7fda)`()` | Destroys this Cellulo robot scanner.
`public bool `[`isScanning`](#classCelluloBluetoothScanner_1ac9b4f45b98b0300c6b3fc6d4f74d11df)`() const` | Gets whether currently scanning.
`public inline QStringList `[`getFoundRobots`](#classCelluloBluetoothScanner_1af535605bcf5d931f2ecf6748625922f4)`() const` | Gets the list of found robot MAC addresses.
`{signal} public void `[`robotDiscovered`](#classCelluloBluetoothScanner_1a793a02b08e02b4d871fd04860ed3944f)`(QString const & macAddr)` | Emitted when a new Cellulo robot is discovered.
`{signal} public void `[`finished`](#classCelluloBluetoothScanner_1a1dd46e5241eed46a317de3ef93298c71)`()` | Emitted when scanning finishes.
`{signal} public void `[`scanningChanged`](#classCelluloBluetoothScanner_1ac7a4a553601681e1b4f1409a0989ef4c)`()` | Emitted when scan stops or starts.
`{signal} public void `[`foundRobotsChanged`](#classCelluloBluetoothScanner_1a205e132b289bec1e783c77e026ba0f38)`()` | Emitted when list of found robot MAC addresses changes.
`{slot} public void `[`start`](#classCelluloBluetoothScanner_1a05cd4bd6e5d5e2ec128a9fdf4139524d)`()` | Starts scanning.
`{slot} public void `[`stop`](#classCelluloBluetoothScanner_1af8647804881f980d27e615fb79b01f60)`()` | Stops scanning.
`{slot} public void `[`clear`](#classCelluloBluetoothScanner_1a1a5039be91a7b554bfec282be915ae70)`()` | Clears the list of found robots.

## Members

#### `{property} bool `[`continuous`](#classCelluloBluetoothScanner_1a14148bced248eb2718eab2761674bfdf) 

Whether to continuously scan.

#### `{property} bool `[`scanning`](#classCelluloBluetoothScanner_1a1a20e2fa83811cdf0a4aa1719e947af5) 

#### `{property} QStringList `[`foundRobots`](#classCelluloBluetoothScanner_1ab5bf8c5660aaed4825f1fa56a034e9d4) 

List of robot MAC addresses that are found.

#### `public  `[`CelluloBluetoothScanner`](#classCelluloBluetoothScanner_1aaabcd5a86babbdee4f8b34fce274de34)`(QQuickItem * parent)` 

Creates a new Cellulo robot scanner.

#### Parameters
* `parent` Parent of this QML item

#### `public virtual  `[`~CelluloBluetoothScanner`](#classCelluloBluetoothScanner_1a589f4beeb292795676ddc9d2e0cb7fda)`()` 

Destroys this Cellulo robot scanner.

#### `public bool `[`isScanning`](#classCelluloBluetoothScanner_1ac9b4f45b98b0300c6b3fc6d4f74d11df)`() const` 

Gets whether currently scanning.

#### Returns
Whether currently scanning

#### `public inline QStringList `[`getFoundRobots`](#classCelluloBluetoothScanner_1af535605bcf5d931f2ecf6748625922f4)`() const` 

Gets the list of found robot MAC addresses.

#### Returns
The list of found robot MAC addresses

#### `{signal} public void `[`robotDiscovered`](#classCelluloBluetoothScanner_1a793a02b08e02b4d871fd04860ed3944f)`(QString const & macAddr)` 

Emitted when a new Cellulo robot is discovered.

#### Parameters
* `macAddr` Mac address of the newly discovered robot

#### `{signal} public void `[`finished`](#classCelluloBluetoothScanner_1a1dd46e5241eed46a317de3ef93298c71)`()` 

Emitted when scanning finishes.

#### `{signal} public void `[`scanningChanged`](#classCelluloBluetoothScanner_1ac7a4a553601681e1b4f1409a0989ef4c)`()` 

Emitted when scan stops or starts.

#### `{signal} public void `[`foundRobotsChanged`](#classCelluloBluetoothScanner_1a205e132b289bec1e783c77e026ba0f38)`()` 

Emitted when list of found robot MAC addresses changes.

#### `{slot} public void `[`start`](#classCelluloBluetoothScanner_1a05cd4bd6e5d5e2ec128a9fdf4139524d)`()` 

Starts scanning.

#### `{slot} public void `[`stop`](#classCelluloBluetoothScanner_1af8647804881f980d27e615fb79b01f60)`()` 

Stops scanning.

#### `{slot} public void `[`clear`](#classCelluloBluetoothScanner_1a1a5039be91a7b554bfec282be915ae70)`()` 

Clears the list of found robots.

# class `CelluloCommUtil` 

```
class CelluloCommUtil
  : public QObject
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CelluloCommUtil`](#classCelluloCommUtil_1af00a865bc2754fb4ae980212622664c9)`(QObject * parent)` | 
`public virtual  `[`~CelluloCommUtil`](#classCelluloCommUtil_1af58ca708188dc6196ca8f2d10b1d8c61)`()` | 
`enum `[`RelayProtocol`](#classCelluloCommUtil_1ad5d3ecb403413a31b98c9d85f9faa32c) | Underlying transfer protocols supported by the relay servers and clients.

## Members

#### `public  `[`CelluloCommUtil`](#classCelluloCommUtil_1af00a865bc2754fb4ae980212622664c9)`(QObject * parent)` 

#### `public virtual  `[`~CelluloCommUtil`](#classCelluloCommUtil_1af58ca708188dc6196ca8f2d10b1d8c61)`()` 

#### `enum `[`RelayProtocol`](#classCelluloCommUtil_1ad5d3ecb403413a31b98c9d85f9faa32c) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
Local            | Unix domain socket.
Tcp            | TCP socket.

Underlying transfer protocols supported by the relay servers and clients.

# class `CelluloLocalRelayClient` 

```
class CelluloLocalRelayClient
  : public CelluloRelayClient
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CelluloLocalRelayClient`](#classCelluloLocalRelayClient_1a1d68e9485d3f5a81a633c1c8f6ce9da1)`(QQuickItem * parent)` | Creates a new [CelluloLocalRelayClient](#classCelluloLocalRelayClient) with the given QML parent.
`public virtual  `[`~CelluloLocalRelayClient`](#classCelluloLocalRelayClient_1a9aa8f1be42c64d796807546d67e77ced)`()` | Destroys this [CelluloLocalRelayClient](#classCelluloLocalRelayClient).

## Members

#### `public  `[`CelluloLocalRelayClient`](#classCelluloLocalRelayClient_1a1d68e9485d3f5a81a633c1c8f6ce9da1)`(QQuickItem * parent)` 

Creates a new [CelluloLocalRelayClient](#classCelluloLocalRelayClient) with the given QML parent.

#### Parameters
* `parent` The QML parent

#### `public virtual  `[`~CelluloLocalRelayClient`](#classCelluloLocalRelayClient_1a9aa8f1be42c64d796807546d67e77ced)`()` 

Destroys this [CelluloLocalRelayClient](#classCelluloLocalRelayClient).

# class `CelluloLocalRelayServer` 

```
class CelluloLocalRelayServer
  : public CelluloRelayServer
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CelluloLocalRelayServer`](#classCelluloLocalRelayServer_1ad998bd5e6f463ce17137b482461e9aa4)`(QQuickItem * parent)` | Creates a new [CelluloLocalRelayServer](#classCelluloLocalRelayServer) with the given QML parent.
`public virtual  `[`~CelluloLocalRelayServer`](#classCelluloLocalRelayServer_1a33b3799ac88aa42f28d2ddfc63970ba1)`()` | Destroys this [CelluloLocalRelayServer](#classCelluloLocalRelayServer).

## Members

#### `public  `[`CelluloLocalRelayServer`](#classCelluloLocalRelayServer_1ad998bd5e6f463ce17137b482461e9aa4)`(QQuickItem * parent)` 

Creates a new [CelluloLocalRelayServer](#classCelluloLocalRelayServer) with the given QML parent.

#### Parameters
* `parent` The QML parent

#### `public virtual  `[`~CelluloLocalRelayServer`](#classCelluloLocalRelayServer_1a33b3799ac88aa42f28d2ddfc63970ba1)`()` 

Destroys this [CelluloLocalRelayServer](#classCelluloLocalRelayServer).

# class `CelluloRelayClient` 

```
class CelluloRelayClient
  : public QQuickItem
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} bool `[`connected`](#classCelluloRelayClient_1a04c4ab11efbd9e1155768fb110f948e8) | 
`{property} QString `[`serverAddress`](#classCelluloRelayClient_1a971dec7154d10d2573f3ead2e6020683) | Server's address, e.g "127.0.0.1".
`{property} int `[`port`](#classCelluloRelayClient_1ab16e05f8895c6621583029d73bb15540) | 
`{property} int `[`autoConnect`](#classCelluloRelayClient_1a443ce2c4020bae476d23491a7db61b47) | 
`{property} QVariantList `[`robots`](#classCelluloRelayClient_1a1566df1bec9695e84651583468dc0141) | 
`public  `[`CelluloRelayClient`](#classCelluloRelayClient_1aa5d3df76b127479580cda28fcc1672d2)`(`[`CelluloCommUtil::RelayProtocol`](#classCelluloCommUtil_1ad5d3ecb403413a31b98c9d85f9faa32c)` protocol,QQuickItem * parent)` | Creates a new [CelluloRelayClient](#classCelluloRelayClient) with the given QML parent.
`public virtual  `[`~CelluloRelayClient`](#classCelluloRelayClient_1a220518075873164bc2199da047a875c7)`()` | Destroys this [CelluloRelayClient](#classCelluloRelayClient).
`public bool `[`isConnected`](#classCelluloRelayClient_1a1f0448aa746ca1d9c5cab7ce9b0ed195)`()` | Gets whether the client is connected to the server.
`public inline bool `[`getAutoConnect`](#classCelluloRelayClient_1a38dfcb11d89db10a6501e14ef1234b9b)`()` | Gets whether the socket tries to reconnect when it drops.
`public void `[`setAutoConnect`](#classCelluloRelayClient_1ae30730ec2839c702c55a0efb35c60b11)`(bool autoConnect)` | Sets whether the socket will try to reconnect when it drops.
`public inline QString `[`getServerAddress`](#classCelluloRelayClient_1a818a29042e7430a670b4a1eabd4e6342)`() const` | Gets the current server's address.
`public void `[`setServerAddress`](#classCelluloRelayClient_1aaf0039b956bdda7034517ca1409cb4c8)`(QString serverAddress)` | Sets the server address to connect to.
`public inline int `[`getPort`](#classCelluloRelayClient_1a80eff6b18307b905c3795ab66c76bad7)`() const` | Gets the current port.
`public void `[`setPort`](#classCelluloRelayClient_1a66ff6a2651ea5a63589b9169870d2361)`(int port)` | Sets the port.
`public QVariantList `[`getRobots`](#classCelluloRelayClient_1ae58443c6de32c353ffe827f9714a3b1e)`() const` | Gets the list of robots belonging to this client.
`{signal} public void `[`connectedChanged`](#classCelluloRelayClient_1ab8235e12a43d95bc2df590d9f3562e9e)`()` | Emitted when connected/disconnected to/from server.
`{signal} public void `[`autoConnectChanged`](#classCelluloRelayClient_1ab803c2b7ffc98424239d9397d0cb3cb9)`()` | Auto connect strategy changed.
`{signal} public void `[`serverAddressChanged`](#classCelluloRelayClient_1a5bd992c77bc94038507cf10ae8628c5e)`()` | Emitted when the server address changes.
`{signal} public void `[`portChanged`](#classCelluloRelayClient_1a3d37db3e79a036f6af85ec4dbb44f846)`()` | Emitted whe the port changes.
`{signal} public void `[`connected`](#classCelluloRelayClient_1aa83e90529db5b28a8004ca585b53d50b)`()` | Emitted when the server socket is connected.
`{signal} public void `[`disconnected`](#classCelluloRelayClient_1a4d69a1bdc018e41c83dd5784a46392f1)`()` | Emitted when the server socket is disconected.
`{signal} public void `[`robotsChanged`](#classCelluloRelayClient_1af5d33a8ed7f225aa3975eef8deb9a428)`()` | Emitted when the robot list changes.
`{signal} public void `[`unknownRobotAtServer`](#classCelluloRelayClient_1ab00116362bf76ce6c838ba371c8a279f)`(QString macAddr)` | Emitted when the server has a robot already connected that is not in the robots list covered by this client.
`{slot} public void `[`connectToServer`](#classCelluloRelayClient_1af22d77704e18200325f2a6742bff80b6)`()` | Initiates a connection to the service on the server.
`{slot} public void `[`disconnectFromServer`](#classCelluloRelayClient_1a7a29e93e4f49f0a64a338f65284b7ae5)`()` | Starts closing the socket.
`{slot} public void `[`addRobot`](#classCelluloRelayClient_1ab3deda55f6440d46c0b48f351d170875)`(`[`CelluloBluetooth`](#classCelluloBluetooth)` * robot,bool select)` | Adds the robot to the robots list, sets the robot's relay client to this object.
`{slot} public void `[`removeRobot`](#classCelluloRelayClient_1aa058c7b7405766a6be8ca862891b22af)`(`[`CelluloBluetooth`](#classCelluloBluetooth)` * robot)` | Removes the robot from the robots list.

## Members

#### `{property} bool `[`connected`](#classCelluloRelayClient_1a04c4ab11efbd9e1155768fb110f948e8) 

#### `{property} QString `[`serverAddress`](#classCelluloRelayClient_1a971dec7154d10d2573f3ead2e6020683) 

Server's address, e.g "127.0.0.1".

#### `{property} int `[`port`](#classCelluloRelayClient_1ab16e05f8895c6621583029d73bb15540) 

#### `{property} int `[`autoConnect`](#classCelluloRelayClient_1a443ce2c4020bae476d23491a7db61b47) 

#### `{property} QVariantList `[`robots`](#classCelluloRelayClient_1a1566df1bec9695e84651583468dc0141) 

#### `public  `[`CelluloRelayClient`](#classCelluloRelayClient_1aa5d3df76b127479580cda28fcc1672d2)`(`[`CelluloCommUtil::RelayProtocol`](#classCelluloCommUtil_1ad5d3ecb403413a31b98c9d85f9faa32c)` protocol,QQuickItem * parent)` 

Creates a new [CelluloRelayClient](#classCelluloRelayClient) with the given QML parent.

#### Parameters
* `protocol` Underlying transfer protocol to use 

* `parent` The QML parent

#### `public virtual  `[`~CelluloRelayClient`](#classCelluloRelayClient_1a220518075873164bc2199da047a875c7)`()` 

Destroys this [CelluloRelayClient](#classCelluloRelayClient).

#### `public bool `[`isConnected`](#classCelluloRelayClient_1a1f0448aa746ca1d9c5cab7ce9b0ed195)`()` 

Gets whether the client is connected to the server.

#### Returns
Whether the client is connected to the server

#### `public inline bool `[`getAutoConnect`](#classCelluloRelayClient_1a38dfcb11d89db10a6501e14ef1234b9b)`()` 

Gets whether the socket tries to reconnect when it drops.

#### Returns
Whether the socket tries to reconnect when it drops

#### `public void `[`setAutoConnect`](#classCelluloRelayClient_1ae30730ec2839c702c55a0efb35c60b11)`(bool autoConnect)` 

Sets whether the socket will try to reconnect when it drops.

#### Parameters
* `autoReconnect` Whether the socket will try to reconnect when it drops

#### `public inline QString `[`getServerAddress`](#classCelluloRelayClient_1a818a29042e7430a670b4a1eabd4e6342)`() const` 

Gets the current server's address.

#### Returns
Current server address, e.g `127.0.0.1` for TCP

#### `public void `[`setServerAddress`](#classCelluloRelayClient_1aaf0039b956bdda7034517ca1409cb4c8)`(QString serverAddress)` 

Sets the server address to connect to.

#### Parameters
* `peer` The new server address, e.g `127.0.0.1` for TCP

#### `public inline int `[`getPort`](#classCelluloRelayClient_1a80eff6b18307b905c3795ab66c76bad7)`() const` 

Gets the current port.

#### Returns
Current port

#### `public void `[`setPort`](#classCelluloRelayClient_1a66ff6a2651ea5a63589b9169870d2361)`(int port)` 

Sets the port.

#### Parameters
* `port` The new port, must be in [0,65535]

#### `public QVariantList `[`getRobots`](#classCelluloRelayClient_1ae58443c6de32c353ffe827f9714a3b1e)`() const` 

Gets the list of robots belonging to this client.

#### Returns
List of robots belonging to this client

#### `{signal} public void `[`connectedChanged`](#classCelluloRelayClient_1ab8235e12a43d95bc2df590d9f3562e9e)`()` 

Emitted when connected/disconnected to/from server.

#### `{signal} public void `[`autoConnectChanged`](#classCelluloRelayClient_1ab803c2b7ffc98424239d9397d0cb3cb9)`()` 

Auto connect strategy changed.

#### `{signal} public void `[`serverAddressChanged`](#classCelluloRelayClient_1a5bd992c77bc94038507cf10ae8628c5e)`()` 

Emitted when the server address changes.

#### `{signal} public void `[`portChanged`](#classCelluloRelayClient_1a3d37db3e79a036f6af85ec4dbb44f846)`()` 

Emitted whe the port changes.

#### `{signal} public void `[`connected`](#classCelluloRelayClient_1aa83e90529db5b28a8004ca585b53d50b)`()` 

Emitted when the server socket is connected.

#### `{signal} public void `[`disconnected`](#classCelluloRelayClient_1a4d69a1bdc018e41c83dd5784a46392f1)`()` 

Emitted when the server socket is disconected.

#### `{signal} public void `[`robotsChanged`](#classCelluloRelayClient_1af5d33a8ed7f225aa3975eef8deb9a428)`()` 

Emitted when the robot list changes.

#### `{signal} public void `[`unknownRobotAtServer`](#classCelluloRelayClient_1ab00116362bf76ce6c838ba371c8a279f)`(QString macAddr)` 

Emitted when the server has a robot already connected that is not in the robots list covered by this client.

#### Parameters
* `macAddr` MAC address of the unknown robot

#### `{slot} public void `[`connectToServer`](#classCelluloRelayClient_1af22d77704e18200325f2a6742bff80b6)`()` 

Initiates a connection to the service on the server.

#### `{slot} public void `[`disconnectFromServer`](#classCelluloRelayClient_1a7a29e93e4f49f0a64a338f65284b7ae5)`()` 

Starts closing the socket.

#### `{slot} public void `[`addRobot`](#classCelluloRelayClient_1ab3deda55f6440d46c0b48f351d170875)`(`[`CelluloBluetooth`](#classCelluloBluetooth)` * robot,bool select)` 

Adds the robot to the robots list, sets the robot's relay client to this object.

#### Parameters
* `robot` New robot 

* `select` Selects the newly added robot as current; pass true if robot is added as a result of an [unknownRobotAtServer()](#classCelluloRelayClient_1ab00116362bf76ce6c838ba371c8a279f) signal

#### `{slot} public void `[`removeRobot`](#classCelluloRelayClient_1aa058c7b7405766a6be8ca862891b22af)`(`[`CelluloBluetooth`](#classCelluloBluetooth)` * robot)` 

Removes the robot from the robots list.

#### Parameters
* `robot` Robot to remove

# class `CelluloRelayServer` 

```
class CelluloRelayServer
  : public QQuickItem
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} QString `[`address`](#classCelluloRelayServer_1abc5bb4b52d5604dea3918aa5116d9ff2) | Host address, e.g "127.0.0.1" for TCP.
`{property} int `[`port`](#classCelluloRelayServer_1a231d9064887546f9b3b6c7c417d44417) | 
`public  `[`CelluloRelayServer`](#classCelluloRelayServer_1a0fd33636ec0ecbff77ab4e30350f54aa)`(`[`CelluloCommUtil::RelayProtocol`](#classCelluloCommUtil_1ad5d3ecb403413a31b98c9d85f9faa32c)` protocol,QQuickItem * parent)` | Creates a new [CelluloRelayServer](#classCelluloRelayServer) with the given QML parent.
`public  `[`~CelluloRelayServer`](#classCelluloRelayServer_1a845c3fa8e623c2c752042051784a499c)`()` | Destroys this [CelluloRelayServer](#classCelluloRelayServer).
`public bool `[`isListening`](#classCelluloRelayServer_1ae2365a6901a3b0eca2d28384f7f0220e)`() const` | Gets whether the server is listening.
`public void `[`setListening`](#classCelluloRelayServer_1a6d57d125c563f335557aa708834b35ad)`(bool enable)` | Enables/disables listening.
`public inline QString `[`getAddress`](#classCelluloRelayServer_1af30edfe0d41ab1ce563192a3369d5467)`() const` | Gets the current host address.
`public void `[`setAddress`](#classCelluloRelayServer_1a076711ad2c93dec691d4195e64538672)`(QString address)` | Sets the host address.
`public inline int `[`getPort`](#classCelluloRelayServer_1a7b1f1d980079e0dd3c8dbb6e792b7eb4)`() const` | Gets the current port.
`public void `[`setPort`](#classCelluloRelayServer_1a82cde258aca0d20443d2e5501842b081)`(int port)` | Sets the port.
`{signal} public void `[`addressChanged`](#classCelluloRelayServer_1a8f96e24229457116a28e53805d5e5140)`()` | Emitted when the host address changes.
`{signal} public void `[`portChanged`](#classCelluloRelayServer_1a4eeb05a798f96c09f490580dec3c6afc)`()` | Emitted whe the port changes.
`{signal} public void `[`clientConnected`](#classCelluloRelayServer_1ac9dcb95002794e8ae6c6eb5432229ca6)`()` | Emitted when a new client connects.
`{signal} public void `[`clientDisconnected`](#classCelluloRelayServer_1acf6e25a38e961463a874eac047f4b0c6)`()` | Emitted when the client disconnects.
`{signal} public void `[`robotAdded`](#classCelluloRelayServer_1ac99a70c736a23a023b24b31c18785dc8)`(QString macAddr)` | Emitted when a new robot is added to the server.
`{signal} public void `[`robotRemoved`](#classCelluloRelayServer_1a9bd76fb184f57283c6b8b14f143735f0)`(QString macAddr)` | Emitted when a robot is removed from the server.
`{slot} public void `[`addRobot`](#classCelluloRelayServer_1aedc9439890646149929f8589b6312eff)`(`[`CelluloBluetooth`](#classCelluloBluetooth)` * robot)` | Adds robot to the robots list, sets the robot's relay server to this object.
`{slot} public void `[`removeRobot`](#classCelluloRelayServer_1ad07138c15ff34f6396365bdaf4562420)`(`[`CelluloBluetooth`](#classCelluloBluetooth)` * robot)` | Removes the robot from the robots list.
`{slot} public void `[`disconnectClient`](#classCelluloRelayServer_1a0b0d7822a00058793f3d717c4db6dfba)`()` | Closes the client's socket.

## Members

#### `{property} QString `[`address`](#classCelluloRelayServer_1abc5bb4b52d5604dea3918aa5116d9ff2) 

Host address, e.g "127.0.0.1" for TCP.

#### `{property} int `[`port`](#classCelluloRelayServer_1a231d9064887546f9b3b6c7c417d44417) 

#### `public  `[`CelluloRelayServer`](#classCelluloRelayServer_1a0fd33636ec0ecbff77ab4e30350f54aa)`(`[`CelluloCommUtil::RelayProtocol`](#classCelluloCommUtil_1ad5d3ecb403413a31b98c9d85f9faa32c)` protocol,QQuickItem * parent)` 

Creates a new [CelluloRelayServer](#classCelluloRelayServer) with the given QML parent.

#### Parameters
* `protocol` Underlying transfer protocol to use 

* `parent` The QML parent

#### `public  `[`~CelluloRelayServer`](#classCelluloRelayServer_1a845c3fa8e623c2c752042051784a499c)`()` 

Destroys this [CelluloRelayServer](#classCelluloRelayServer).

#### `public bool `[`isListening`](#classCelluloRelayServer_1ae2365a6901a3b0eca2d28384f7f0220e)`() const` 

Gets whether the server is listening.

#### Returns
Whether the server is listening

#### `public void `[`setListening`](#classCelluloRelayServer_1a6d57d125c563f335557aa708834b35ad)`(bool enable)` 

Enables/disables listening.

#### Parameters
* `enable` Whether to listen or close the server and stop listening

#### `public inline QString `[`getAddress`](#classCelluloRelayServer_1af30edfe0d41ab1ce563192a3369d5467)`() const` 

Gets the current host address.

#### Returns
Current host address, e.g "127.0.0.1"

#### `public void `[`setAddress`](#classCelluloRelayServer_1a076711ad2c93dec691d4195e64538672)`(QString address)` 

Sets the host address.

#### Parameters
* `host` The new host address, e.g "127.0.0.1"

#### `public inline int `[`getPort`](#classCelluloRelayServer_1a7b1f1d980079e0dd3c8dbb6e792b7eb4)`() const` 

Gets the current port.

#### Returns
Current port

#### `public void `[`setPort`](#classCelluloRelayServer_1a82cde258aca0d20443d2e5501842b081)`(int port)` 

Sets the port.

#### Parameters
* `port` The new port, must be in [0,65535]

#### `{signal} public void `[`addressChanged`](#classCelluloRelayServer_1a8f96e24229457116a28e53805d5e5140)`()` 

Emitted when the host address changes.

#### `{signal} public void `[`portChanged`](#classCelluloRelayServer_1a4eeb05a798f96c09f490580dec3c6afc)`()` 

Emitted whe the port changes.

#### `{signal} public void `[`clientConnected`](#classCelluloRelayServer_1ac9dcb95002794e8ae6c6eb5432229ca6)`()` 

Emitted when a new client connects.

#### `{signal} public void `[`clientDisconnected`](#classCelluloRelayServer_1acf6e25a38e961463a874eac047f4b0c6)`()` 

Emitted when the client disconnects.

#### `{signal} public void `[`robotAdded`](#classCelluloRelayServer_1ac99a70c736a23a023b24b31c18785dc8)`(QString macAddr)` 

Emitted when a new robot is added to the server.

#### Parameters
* `macAddr` MAC address of the added robot

#### `{signal} public void `[`robotRemoved`](#classCelluloRelayServer_1a9bd76fb184f57283c6b8b14f143735f0)`(QString macAddr)` 

Emitted when a robot is removed from the server.

#### Parameters
* `macAddr` MAC address of the removed robot

#### `{slot} public void `[`addRobot`](#classCelluloRelayServer_1aedc9439890646149929f8589b6312eff)`(`[`CelluloBluetooth`](#classCelluloBluetooth)` * robot)` 

Adds robot to the robots list, sets the robot's relay server to this object.

#### Parameters
* `robot` New robot

#### `{slot} public void `[`removeRobot`](#classCelluloRelayServer_1ad07138c15ff34f6396365bdaf4562420)`(`[`CelluloBluetooth`](#classCelluloBluetooth)` * robot)` 

Removes the robot from the robots list.

#### Parameters
* `robot` Existing robot

#### `{slot} public void `[`disconnectClient`](#classCelluloRelayServer_1a0b0d7822a00058793f3d717c4db6dfba)`()` 

Closes the client's socket.

# class `CelluloRobotPoolClient` 

```
class CelluloRobotPoolClient
  : public CelluloLocalRelayClient
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} QJSValue `[`createRobot`](#classCelluloRobotPoolClient_1a3c6d0595b4a283d395c682eeaf1bb78b) | 
`public  `[`CelluloRobotPoolClient`](#classCelluloRobotPoolClient_1ac5602bfae77fb466e45a0980d9d66c77)`(QQuickItem * parent)` | Creates a new [CelluloRobotPoolClient](#classCelluloRobotPoolClient) with the given QML parent.
`public virtual  `[`~CelluloRobotPoolClient`](#classCelluloRobotPoolClient_1a1dfbcdb7eeb2cdef6349b732d7f09a36)`()` | Destroys this [CelluloRobotPoolClient](#classCelluloRobotPoolClient).
`public inline QJSValue `[`getCreateRobot`](#classCelluloRobotPoolClient_1a91659c3e9954f4d210d90fcdc3ec2455)`() const` | Gets the createRobot function.
`public void `[`setCreateRobot`](#classCelluloRobotPoolClient_1a431e4688bdffff39b21c18b584e9c240)`(QJSValue const & function)` | Sets the createRobot function.
`{signal} public void `[`createRobotChanged`](#classCelluloRobotPoolClient_1ab1df06a697039e029d682c26c7ffcefd)`()` | Emitted when the createRobot function changes.

## Members

#### `{property} QJSValue `[`createRobot`](#classCelluloRobotPoolClient_1a3c6d0595b4a283d395c682eeaf1bb78b) 

#### `public  `[`CelluloRobotPoolClient`](#classCelluloRobotPoolClient_1ac5602bfae77fb466e45a0980d9d66c77)`(QQuickItem * parent)` 

Creates a new [CelluloRobotPoolClient](#classCelluloRobotPoolClient) with the given QML parent.

#### Parameters
* `parent` The QML parent

#### `public virtual  `[`~CelluloRobotPoolClient`](#classCelluloRobotPoolClient_1a1dfbcdb7eeb2cdef6349b732d7f09a36)`()` 

Destroys this [CelluloRobotPoolClient](#classCelluloRobotPoolClient).

#### `public inline QJSValue `[`getCreateRobot`](#classCelluloRobotPoolClient_1a91659c3e9954f4d210d90fcdc3ec2455)`() const` 

Gets the createRobot function.

#### Returns
The createRobot function

#### `public void `[`setCreateRobot`](#classCelluloRobotPoolClient_1a431e4688bdffff39b21c18b584e9c240)`(QJSValue const & function)` 

Sets the createRobot function.

#### Parameters
* `function` The createRobot function that takes a string and returns a [CelluloBluetooth](#classCelluloBluetooth) pointer or CelluloBluetooth-derived object pointer

#### `{signal} public void `[`createRobotChanged`](#classCelluloRobotPoolClient_1ab1df06a697039e029d682c26c7ffcefd)`()` 

Emitted when the createRobot function changes.

# class `CelluloTcpRelayClient` 

```
class CelluloTcpRelayClient
  : public CelluloRelayClient
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CelluloTcpRelayClient`](#classCelluloTcpRelayClient_1a425a065be96718d19c4842e741502590)`(QQuickItem * parent)` | Creates a new [CelluloTcpRelayClient](#classCelluloTcpRelayClient) with the given QML parent.
`public virtual  `[`~CelluloTcpRelayClient`](#classCelluloTcpRelayClient_1a84d7fe1961bc3d65c401e5ea97ae9258)`()` | Destroys this [CelluloTcpRelayClient](#classCelluloTcpRelayClient).

## Members

#### `public  `[`CelluloTcpRelayClient`](#classCelluloTcpRelayClient_1a425a065be96718d19c4842e741502590)`(QQuickItem * parent)` 

Creates a new [CelluloTcpRelayClient](#classCelluloTcpRelayClient) with the given QML parent.

#### Parameters
* `parent` The QML parent

#### `public virtual  `[`~CelluloTcpRelayClient`](#classCelluloTcpRelayClient_1a84d7fe1961bc3d65c401e5ea97ae9258)`()` 

Destroys this [CelluloTcpRelayClient](#classCelluloTcpRelayClient).

# class `CelluloTcpRelayServer` 

```
class CelluloTcpRelayServer
  : public CelluloRelayServer
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CelluloTcpRelayServer`](#classCelluloTcpRelayServer_1aa69388909858b45811c75394340d3cd0)`(QQuickItem * parent)` | Creates a new [CelluloTcpRelayServer](#classCelluloTcpRelayServer) with the given QML parent.
`public virtual  `[`~CelluloTcpRelayServer`](#classCelluloTcpRelayServer_1a9462bf717c248280d8a8ca6f90dfd3e7)`()` | Destroys this [CelluloTcpRelayServer](#classCelluloTcpRelayServer).

## Members

#### `public  `[`CelluloTcpRelayServer`](#classCelluloTcpRelayServer_1aa69388909858b45811c75394340d3cd0)`(QQuickItem * parent)` 

Creates a new [CelluloTcpRelayServer](#classCelluloTcpRelayServer) with the given QML parent.

#### Parameters
* `parent` The QML parent

#### `public virtual  `[`~CelluloTcpRelayServer`](#classCelluloTcpRelayServer_1a9462bf717c248280d8a8ca6f90dfd3e7)`()` 

Destroys this [CelluloTcpRelayServer](#classCelluloTcpRelayServer).

Generated by [Moxygen](https://sourcey.com/moxygen)