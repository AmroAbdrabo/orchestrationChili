# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`namespace `[`Cellulo`](#namespaceCellulo) | 

# namespace `Cellulo` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[`Cellulo::CelluloBluetooth`](#classCellulo_1_1CelluloBluetooth) | Object that communicates with one Cellulo robot over Bluetooth.
`class `[`Cellulo::CelluloBluetoothEMP`](#classCellulo_1_1CelluloBluetoothEMP) | Object that mass reset/shuts down all robots.
`class `[`Cellulo::CelluloBluetoothEnums`](#classCellulo_1_1CelluloBluetoothEnums) | Wrapper containing all the enums of [CelluloBluetooth](#classCellulo_1_1CelluloBluetooth).
`class `[`Cellulo::CelluloBluetoothScanner`](#classCellulo_1_1CelluloBluetoothScanner) | Object that scans for Cellulo robots.
`class `[`Cellulo::CelluloCommUtil`](#classCellulo_1_1CelluloCommUtil) | Cellulo communication utilities.
`class `[`Cellulo::CelluloLocalRelayServer`](#classCellulo_1_1CelluloLocalRelayServer) | Relays packets between a client and physical robots over a Unix domain socket. Accepts connections from a `CelluloLocalRelayClient`.
`class `[`Cellulo::CelluloRelayClient`](#classCellulo_1_1CelluloRelayClient) | Object that relays packets between a `[CelluloRelayServer](#classCellulo_1_1CelluloRelayServer)` and virtual robot objects.
`class `[`Cellulo::CelluloRelayServer`](#classCellulo_1_1CelluloRelayServer) | Object that relays packets between a `[CelluloRelayClient](#classCellulo_1_1CelluloRelayClient)` and physical robots.
`class `[`Cellulo::CelluloRobot`](#classCellulo_1_1CelluloRobot) | The main object that represents a Cellulo robot. Inherits from `[CelluloBluetooth](#classCellulo_1_1CelluloBluetooth)` and has all its functionalities (not listed here).
`class `[`Cellulo::CelluloRobotPoolClient`](#classCellulo_1_1CelluloRobotPoolClient) | Object that uses the robots connected to a `cellulorobotpoold`.
`class `[`Cellulo::CelluloTcpRelayClient`](#classCellulo_1_1CelluloTcpRelayClient) | Relays packets between a server and virtual robot objects over a TCP socket. Connects to a `[CelluloTcpRelayServer](#classCellulo_1_1CelluloTcpRelayServer)`.
`class `[`Cellulo::CelluloTcpRelayServer`](#classCellulo_1_1CelluloTcpRelayServer) | Relays packets between a client and physical robots over a TCP socket. Accepts connections from a `[CelluloTcpRelayClient](#classCellulo_1_1CelluloTcpRelayClient)`.

# class `Cellulo::CelluloBluetooth` 

```
class Cellulo::CelluloBluetooth
  : public CelluloZoneClient
```  

Object that communicates with one Cellulo robot over Bluetooth.

Inherits from `CelluloZoneClient` and therefore can be used as one.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} QString `[`localAdapterMacAddr`](#classCellulo_1_1CelluloBluetooth_1a31ca21c1a395893cbfe0e4ea4bb6e590) | Local adapter's MAC address chosen to connect to the robot, empty string if using default adapter; only works on Linux and if the plugin is built with BlueZ.
`{property} bool `[`autoConnect`](#classCellulo_1_1CelluloBluetooth_1a2c2f916967bee8e06038b92f46bb4248) | Whether to start connecting immediately as soon as **macAddr** is set and to reconnect if connection drops, default true.
`{property} QString `[`macAddr`](#classCellulo_1_1CelluloBluetooth_1a3a4f9fd2da2440be2368bd4b9e74f0f2) | Robot MAC address in the form "XX:XX:XX:XX:XX:XX".
`{property} `[`CelluloBluetoothEnums::ConnectionStatus`](#classCellulo_1_1CelluloBluetoothEnums_1a9bdbb91140cd33c3daa779af49c7ed97)` `[`connectionStatus`](#classCellulo_1_1CelluloBluetooth_1a9520239e44d19dd120c6779a126a543f) | Current connection status to the robot, read-only.
`{property} `[`CelluloBluetoothEnums::BatteryState`](#classCellulo_1_1CelluloBluetoothEnums_1a895a56801308039dd778b0a0fb6809b8)` `[`batteryState`](#classCellulo_1_1CelluloBluetooth_1a87f7b19fe478e73346094a8208c00ea5) | Robot's current battery state, read-only.
`{property} float `[`x`](#classCellulo_1_1CelluloBluetooth_1af13c47b29e25220131c182d963e41034) | Robot's x coordinate in mm, read-only.
`{property} float `[`y`](#classCellulo_1_1CelluloBluetooth_1ac1276ac29b10f1f28fa0f6a00416fa60) | Robot's y coordinate in mm, read-only.
`{property} float `[`theta`](#classCellulo_1_1CelluloBluetooth_1acaee9ee4adc6528bcaae8c9577790d02) | Robot's orientation in degrees, read-only.
`{property} bool `[`kidnapped`](#classCellulo_1_1CelluloBluetooth_1a4be50315021f3a8df91275ee89bccfa5) | Whether the robot is not on encoded paper, read-only.
`{property} `[`CelluloBluetoothEnums::Gesture`](#classCellulo_1_1CelluloBluetoothEnums_1aac0e86c82f086708674759431d6ff0fb)` `[`gesture`](#classCellulo_1_1CelluloBluetooth_1af9c3ebbd5cd9b40135f3b0289b8189ab) | Current robot gesture (if gesture detection is enabled), read-only.
`{property} bool `[`timestampingEnabled`](#classCellulo_1_1CelluloBluetooth_1ab93e751696cdaa7635681bb05b5598f5) | Whether the robot will send its own timestamp along with its pose, default false.
`{property} int `[`lastTimestamp`](#classCellulo_1_1CelluloBluetooth_1a7884ff94eaf821db9310d20f95024ad5) | Last local timestamp received along with pose (is valid if **timestampingEnabled** is true), read-only.
`{property} float `[`framerate`](#classCellulo_1_1CelluloBluetooth_1aa64ae00fc5683f384940db4b9e72ac8d) | Localization framerate calculated from local timestamps received along with pose (is valid if **timestampingEnabled** is true), read-only.
`{signal} public void `[`bootCompleted`](#classCellulo_1_1CelluloBluetooth_1a29af380c02321d800dd3325fda88faa6)`()` | Emitted when the robot is ready after a power up or a reset.
`{signal} public void `[`shuttingDown`](#classCellulo_1_1CelluloBluetooth_1a43c60e18d72c5189ab8df6a7e2270c27)`()` | Emitted when the robot is about to sleep (shutdown) due to the user command via touch keys.
`{signal} public void `[`lowBattery`](#classCellulo_1_1CelluloBluetooth_1a843abaab9ef1d26ecea9f6328e522e38)`()` | Emitted when the robot is about to sleep (shutdown) due to low battery.
`{signal} public void `[`touchBegan`](#classCellulo_1_1CelluloBluetooth_1a017c36976bf9e3859cb8fa7f5af2b721)`(int key)` | Emitted when a key is touched.
`{signal} public void `[`longTouch`](#classCellulo_1_1CelluloBluetooth_1afdc4c2e93958e1402e1adc55a1883b37)`(int key)` | Emitted when a key is touched for more than the long touch time.
`{signal} public void `[`touchReleased`](#classCellulo_1_1CelluloBluetooth_1a743b1d878e052108259a119993f32cdb)`(int key)` | Emitted when a key is released.
`{signal} public void `[`poseChanged_inherited`](#classCellulo_1_1CelluloBluetooth_1a76412491f647df2979f90ba5f4f4c9d2)`()` | DO NOT USE EXPLICITLY, use poseChanged(x,y,theta) instead.
`{signal} public void `[`trackingGoalReached`](#classCellulo_1_1CelluloBluetooth_1ad14b579cf835ce856f624f2d258243c7)`()` | Emitted when pose/position/orientation goal is reached.
`{slot} public void `[`connectToServer`](#classCellulo_1_1CelluloBluetooth_1a0872bdaa7029f7e95b224a60469492bf)`()` | Creates socket and connects to the current target MAC address.
`{slot} public void `[`disconnectFromServer`](#classCellulo_1_1CelluloBluetooth_1a791aad74e895f39654df85dde102f55b)`()` | Disconnects from the currently connected device and destroys the socket if possible.
`{slot} public void `[`setPoseBcastPeriod`](#classCellulo_1_1CelluloBluetooth_1a59a2db962b5be2c2565e96ff279cb3ea)`(unsigned int period)` | Sets the pose broadcast period.
`{slot} public void `[`setGoalVelocity`](#classCellulo_1_1CelluloBluetooth_1a793b9865dd747f67523ea08749f1e7c9)`(float vx,float vy,float w)` | Sets robot goal velocity in global world frame.
`{slot} public void `[`setGoalPose`](#classCellulo_1_1CelluloBluetooth_1a5330b254b2c308865103f5019eb80b49)`(float x,float y,float theta,float v,float w)` | Sets a pose goal to track.
`{slot} public void `[`setGoalPosition`](#classCellulo_1_1CelluloBluetooth_1ac6e6054144920961c7fa23d0fb505c4a)`(float x,float y,float v)` | Sets a position goal to track.
`{slot} public void `[`setGoalXCoordinate`](#classCellulo_1_1CelluloBluetooth_1a8a95a56978be8e35f5b25ce7102fc697)`(float x,float v)` | Sets an X coordinate to track.
`{slot} public void `[`setGoalYCoordinate`](#classCellulo_1_1CelluloBluetooth_1a05cccd4cbd19b163e655d00f1d741f09)`(float y,float v)` | Sets a Y coordinate to track.
`{slot} public void `[`setGoalOrientation`](#classCellulo_1_1CelluloBluetooth_1a3375a9a395810a0b4ceececab4c41b9e)`(float theta,float w)` | Sets a position goal to track.
`{slot} public void `[`setGoalXThetaCoordinate`](#classCellulo_1_1CelluloBluetooth_1ab2cf48bdae70905b986399f1b4161c3a)`(float x,float theta,float v,float w)` | Sets an X and Theta goal at the same time.
`{slot} public void `[`setGoalYThetaCoordinate`](#classCellulo_1_1CelluloBluetooth_1a2fe88009044c9162353f13a8bbb11062)`(float y,float theta,float v,float w)` | Sets a Y and Theta goal at the same time.
`{slot} public void `[`clearTracking`](#classCellulo_1_1CelluloBluetooth_1a7247a33e64f535f33d3e7ecf899f028d)`()` | Clears pose/position/velocity goals.
`{slot} public void `[`simpleVibrate`](#classCellulo_1_1CelluloBluetooth_1a545e683162225e73ed3a6a2220396a00)`(float iX,float iY,float iTheta,unsigned int period,unsigned int duration)` | Constantly vibrates the robot.
`{slot} public void `[`vibrateOnMotion`](#classCellulo_1_1CelluloBluetooth_1a0b0ce5e1c237cbbc7d0ffc00e8b08192)`(float iCoeff,unsigned int period)` | Enables vibration against motion.
`{slot} public void `[`clearHapticFeedback`](#classCellulo_1_1CelluloBluetooth_1aae5231423781a97d4a21ff219750b95d)`()` | Clears all haptic feedbacks.
`{slot} public void `[`setExposureTime`](#classCellulo_1_1CelluloBluetooth_1a9c451386f116d48aebd5c4a0f09e02cf)`(int pixels)` | Sets the exposure time for super-fast unkidnap detection for uniform and known paper colors known or enables autoexposure.
`{slot} public void `[`queryBatteryState`](#classCellulo_1_1CelluloBluetooth_1af4ba396b5d36fd2c5c23abe9bb1262c8)`()` | Sends a battery state query.
`{slot} public void `[`setLEDResponseMode`](#classCellulo_1_1CelluloBluetooth_1aa56fe3eed954d834321fab5763142cba)`(`[`CelluloBluetoothEnums::LEDResponseMode`](#classCellulo_1_1CelluloBluetoothEnums_1a57ece08557723b6428a74ba3b1265b29)` mode)` | Sets the LED response mode, i.e the LED visual response of the robot to touches.
`{slot} public void `[`setLocomotionInteractivityMode`](#classCellulo_1_1CelluloBluetooth_1ad110ee7cb10a67b3aa4c4a3d55fa8d2d)`(`[`CelluloBluetoothEnums::LocomotionInteractivityMode`](#classCellulo_1_1CelluloBluetoothEnums_1ae5126bceecb95ffc8846e8c72f379812)` mode)` | Sets the locomotion interactivity mode, i.e the dependance of locomotion to user input.
`{slot} public void `[`setGestureEnabled`](#classCellulo_1_1CelluloBluetooth_1a9bd4f2f2feb7ff0f00c4f05767aca0ea)`(bool enabled)` | Enables/disables raw touch signal offset querying and processing.
`{slot} public void `[`setCasualBackdriveAssistEnabled`](#classCellulo_1_1CelluloBluetooth_1a5f26ca73c9bbb4ff882f94f2cfdfd62c)`(bool enabled)` | Enables/disables assist for easy backdriving.
`{slot} public void `[`setHapticBackdriveAssist`](#classCellulo_1_1CelluloBluetooth_1a4e127b89e9ac560b558262916d3230f5)`(float xAssist,float yAssist,float thetaAssist)` | Haptic feedback-oriented backdrive assist.
`{slot} public void `[`setVisualEffect`](#classCellulo_1_1CelluloBluetooth_1a87d834bff1ddded9c83e427802acf2d8)`(`[`CelluloBluetoothEnums::VisualEffect`](#classCellulo_1_1CelluloBluetoothEnums_1a810aca61e84c1e31fb751335cd776361)` effect,QColor color,int value)` | Sets the visual effect on the robot, changing LED illumination.
`{slot} public void `[`polyBezierInit`](#classCellulo_1_1CelluloBluetooth_1a5943ebcea0fe39fb517fff8ec3c26d0f)`(const QVector2D & point0)` | Sends the first control point of the composite Bézier curve for motion tracking.
`{slot} public void `[`polyBezierAppend`](#classCellulo_1_1CelluloBluetooth_1ac6034aa0cea06d6843281e8ecda357fd)`(const QVector2D & point1,const QVector2D & point2,const QVector2D & point3)` | Adds a segment to the composite Bézier curve for motion tracking; [polyBezierInit()](#classCellulo_1_1CelluloBluetooth_1a5943ebcea0fe39fb517fff8ec3c26d0f) must be called before.
`{slot} public void `[`polyBezierSetFromZone`](#classCellulo_1_1CelluloBluetooth_1ad183a2dd9341750e9449532ea9a6880a)`(CelluloZone * zone)` | Sends the composite Bézier curve in the zone to the robot.
`{slot} public void `[`setGoalPolyBezier`](#classCellulo_1_1CelluloBluetooth_1aa225ca6d3c15fe4461f16e9fb873299b)`(float v,float w)` | Starts tracking the previously set composite Bézier curve.
`{slot} public void `[`setGoalPolyBezierAligned`](#classCellulo_1_1CelluloBluetooth_1afbda284c48ef1cae82357cd2a6afc83d)`(float v,float theta,float w)` | Starts tracking the previously set composite Bézier curve while keeping orientation aligned to the curve.
`{slot} public void `[`reset`](#classCellulo_1_1CelluloBluetooth_1ab29c7d9cce6b8ec5e5b8f82da6332886)`()` | Initiates a software reset on the robot.
`{slot} public void `[`shutdown`](#classCellulo_1_1CelluloBluetooth_1a6920c929fca0d2573144d53de1667a85)`()` | Initiates sleep on the robot.

## Members

#### `{property} QString `[`localAdapterMacAddr`](#classCellulo_1_1CelluloBluetooth_1a31ca21c1a395893cbfe0e4ea4bb6e590) 

Local adapter's MAC address chosen to connect to the robot, empty string if using default adapter; only works on Linux and if the plugin is built with BlueZ.

MAC address of the local adapter to use when connecting to the robot, only works on Linux.

#### `{property} bool `[`autoConnect`](#classCellulo_1_1CelluloBluetooth_1a2c2f916967bee8e06038b92f46bb4248) 

Whether to start connecting immediately as soon as **macAddr** is set and to reconnect if connection drops, default true.

Whether the socket will try to reconnect every time it drops, will connect when mac address is set.

#### `{property} QString `[`macAddr`](#classCellulo_1_1CelluloBluetooth_1a3a4f9fd2da2440be2368bd4b9e74f0f2) 

Robot MAC address in the form "XX:XX:XX:XX:XX:XX".

Bluetooth MAC address of the server.

#### `{property} `[`CelluloBluetoothEnums::ConnectionStatus`](#classCellulo_1_1CelluloBluetoothEnums_1a9bdbb91140cd33c3daa779af49c7ed97)` `[`connectionStatus`](#classCellulo_1_1CelluloBluetooth_1a9520239e44d19dd120c6779a126a543f) 

Current connection status to the robot, read-only.

Bluetooth connection status.

#### `{property} `[`CelluloBluetoothEnums::BatteryState`](#classCellulo_1_1CelluloBluetoothEnums_1a895a56801308039dd778b0a0fb6809b8)` `[`batteryState`](#classCellulo_1_1CelluloBluetooth_1a87f7b19fe478e73346094a8208c00ea5) 

Robot's current battery state, read-only.

Current battery state.

#### `{property} float `[`x`](#classCellulo_1_1CelluloBluetooth_1af13c47b29e25220131c182d963e41034) 

Robot's x coordinate in mm, read-only.

Current x position in mm.

#### `{property} float `[`y`](#classCellulo_1_1CelluloBluetooth_1ac1276ac29b10f1f28fa0f6a00416fa60) 

Robot's y coordinate in mm, read-only.

Current y position in mm.

#### `{property} float `[`theta`](#classCellulo_1_1CelluloBluetooth_1acaee9ee4adc6528bcaae8c9577790d02) 

Robot's orientation in degrees, read-only.

Current orientation in degrees.

#### `{property} bool `[`kidnapped`](#classCellulo_1_1CelluloBluetooth_1a4be50315021f3a8df91275ee89bccfa5) 

Whether the robot is not on encoded paper, read-only.

Whether currently kidnapped.

#### `{property} `[`CelluloBluetoothEnums::Gesture`](#classCellulo_1_1CelluloBluetoothEnums_1aac0e86c82f086708674759431d6ff0fb)` `[`gesture`](#classCellulo_1_1CelluloBluetooth_1af9c3ebbd5cd9b40135f3b0289b8189ab) 

Current robot gesture (if gesture detection is enabled), read-only.

Current gesture.

#### `{property} bool `[`timestampingEnabled`](#classCellulo_1_1CelluloBluetooth_1ab93e751696cdaa7635681bb05b5598f5) 

Whether the robot will send its own timestamp along with its pose, default false.

Whether timestamping along with pose is enabled and idling disabled.

#### `{property} int `[`lastTimestamp`](#classCellulo_1_1CelluloBluetooth_1a7884ff94eaf821db9310d20f95024ad5) 

Last local timestamp received along with pose (is valid if **timestampingEnabled** is true), read-only.

Latest received onboard timestamp (in milliseconds)

#### `{property} float `[`framerate`](#classCellulo_1_1CelluloBluetooth_1aa64ae00fc5683f384940db4b9e72ac8d) 

Localization framerate calculated from local timestamps received along with pose (is valid if **timestampingEnabled** is true), read-only.

Framerate calculated over time.

#### `{signal} public void `[`bootCompleted`](#classCellulo_1_1CelluloBluetooth_1a29af380c02321d800dd3325fda88faa6)`()` 

Emitted when the robot is ready after a power up or a reset.

#### `{signal} public void `[`shuttingDown`](#classCellulo_1_1CelluloBluetooth_1a43c60e18d72c5189ab8df6a7e2270c27)`()` 

Emitted when the robot is about to sleep (shutdown) due to the user command via touch keys.

#### `{signal} public void `[`lowBattery`](#classCellulo_1_1CelluloBluetooth_1a843abaab9ef1d26ecea9f6328e522e38)`()` 

Emitted when the robot is about to sleep (shutdown) due to low battery.

#### `{signal} public void `[`touchBegan`](#classCellulo_1_1CelluloBluetooth_1a017c36976bf9e3859cb8fa7f5af2b721)`(int key)` 

Emitted when a key is touched.

#### Parameters
* `key` The key that is touched

#### `{signal} public void `[`longTouch`](#classCellulo_1_1CelluloBluetooth_1afdc4c2e93958e1402e1adc55a1883b37)`(int key)` 

Emitted when a key is touched for more than the long touch time.

#### Parameters
* `key` The key that is touched

#### `{signal} public void `[`touchReleased`](#classCellulo_1_1CelluloBluetooth_1a743b1d878e052108259a119993f32cdb)`(int key)` 

Emitted when a key is released.

#### Parameters
* `key` The key that is released

#### `{signal} public void `[`poseChanged_inherited`](#classCellulo_1_1CelluloBluetooth_1a76412491f647df2979f90ba5f4f4c9d2)`()` 

DO NOT USE EXPLICITLY, use poseChanged(x,y,theta) instead.

Emitted when the base class emits poseChanged() since NOTIFY cannot be used with inherited signals

#### `{signal} public void `[`trackingGoalReached`](#classCellulo_1_1CelluloBluetooth_1ad14b579cf835ce856f624f2d258243c7)`()` 

Emitted when pose/position/orientation goal is reached.

#### `{slot} public void `[`connectToServer`](#classCellulo_1_1CelluloBluetooth_1a0872bdaa7029f7e95b224a60469492bf)`()` 

Creates socket and connects to the current target MAC address.

#### `{slot} public void `[`disconnectFromServer`](#classCellulo_1_1CelluloBluetooth_1a791aad74e895f39654df85dde102f55b)`()` 

Disconnects from the currently connected device and destroys the socket if possible.

#### `{slot} public void `[`setPoseBcastPeriod`](#classCellulo_1_1CelluloBluetooth_1a59a2db962b5be2c2565e96ff279cb3ea)`(unsigned int period)` 

Sets the pose broadcast period.

#### Parameters
* `period` Desired period in milliseconds, set to 0 for as fast as possible, i.e around 93Hz

#### `{slot} public void `[`setGoalVelocity`](#classCellulo_1_1CelluloBluetooth_1a793b9865dd747f67523ea08749f1e7c9)`(float vx,float vy,float w)` 

Sets robot goal velocity in global world frame.

#### Parameters
* `vx` X velocity in mm/s 

* `vy` Y velocity in mm/s 

* `w` Angular velocity in rad/s

#### `{slot} public void `[`setGoalPose`](#classCellulo_1_1CelluloBluetooth_1a5330b254b2c308865103f5019eb80b49)`(float x,float y,float theta,float v,float w)` 

Sets a pose goal to track.

#### Parameters
* `x` X goal in mm 

* `y` Y goal in mm 

* `theta` Theta goal in degrees 

* `v` Maximum linear speed to track pose in mm/s 

* `w` Maximum angular speed to track pose in rad/s

#### `{slot} public void `[`setGoalPosition`](#classCellulo_1_1CelluloBluetooth_1ac6e6054144920961c7fa23d0fb505c4a)`(float x,float y,float v)` 

Sets a position goal to track.

#### Parameters
* `x` X goal in mm 

* `y` Y goal in mm 

* `v` Maximum linear speed to track pose in mm/s

#### `{slot} public void `[`setGoalXCoordinate`](#classCellulo_1_1CelluloBluetooth_1a8a95a56978be8e35f5b25ce7102fc697)`(float x,float v)` 

Sets an X coordinate to track.

#### Parameters
* `x` X goal in mm 

* `v` Maximum linear speed to track pose in mm/s

#### `{slot} public void `[`setGoalYCoordinate`](#classCellulo_1_1CelluloBluetooth_1a05cccd4cbd19b163e655d00f1d741f09)`(float y,float v)` 

Sets a Y coordinate to track.

#### Parameters
* `y` Y goal in mm 

* `v` Maximum linear speed to track pose in mm/s

#### `{slot} public void `[`setGoalOrientation`](#classCellulo_1_1CelluloBluetooth_1a3375a9a395810a0b4ceececab4c41b9e)`(float theta,float w)` 

Sets a position goal to track.

#### Parameters
* `theta` Theta goal in degrees 

* `w` Maximum angular speed to track pose in rad/s

#### `{slot} public void `[`setGoalXThetaCoordinate`](#classCellulo_1_1CelluloBluetooth_1ab2cf48bdae70905b986399f1b4161c3a)`(float x,float theta,float v,float w)` 

Sets an X and Theta goal at the same time.

#### Parameters
* `x` X goal in mm 

* `theta` Theta goal in degrees 

* `v` Maximum linear speed to track pose in mm/s 

* `w` Maximum angular speed to track pose in rad/s

#### `{slot} public void `[`setGoalYThetaCoordinate`](#classCellulo_1_1CelluloBluetooth_1a2fe88009044c9162353f13a8bbb11062)`(float y,float theta,float v,float w)` 

Sets a Y and Theta goal at the same time.

#### Parameters
* `y` Y goal in mm 

* `theta` Theta goal in degrees 

* `v` Maximum linear speed to track pose in mm/s 

* `w` Maximum angular speed to track pose in rad/s

#### `{slot} public void `[`clearTracking`](#classCellulo_1_1CelluloBluetooth_1a7247a33e64f535f33d3e7ecf899f028d)`()` 

Clears pose/position/velocity goals.

#### `{slot} public void `[`simpleVibrate`](#classCellulo_1_1CelluloBluetooth_1a545e683162225e73ed3a6a2220396a00)`(float iX,float iY,float iTheta,unsigned int period,unsigned int duration)` 

Constantly vibrates the robot.

#### Parameters
* `iX` X intensity, scale is the same as linear velocity 

* `iY` Y intensity, scale is the same as linear velocity 

* `iTheta` Theta intensity, scale is the same as angular velocity 

* `period` Period of vibration in milliseconds, maximum is 0xFFFF 

* `duration` Duration of vibration in milliseconds, maximum is 0xFFFF, 0 for vibrate forever

#### `{slot} public void `[`vibrateOnMotion`](#classCellulo_1_1CelluloBluetooth_1a0b0ce5e1c237cbbc7d0ffc00e8b08192)`(float iCoeff,unsigned int period)` 

Enables vibration against motion.

#### Parameters
* `iCoeff` Vibration intensity with respect to the drive velocities 

* `period` Period of vibration in milliseconds, maximum is 0xFFFF

#### `{slot} public void `[`clearHapticFeedback`](#classCellulo_1_1CelluloBluetooth_1aae5231423781a97d4a21ff219750b95d)`()` 

Clears all haptic feedbacks.

#### `{slot} public void `[`setExposureTime`](#classCellulo_1_1CelluloBluetooth_1a9c451386f116d48aebd5c4a0f09e02cf)`(int pixels)` 

Sets the exposure time for super-fast unkidnap detection for uniform and known paper colors known or enables autoexposure.

460 pixels for the latest white plastic frame and white paper is a good value.

#### Parameters
* `pixels` Exposure time in pixels, must be larger than 260; 0 is a special value that enables autoexposure

#### `{slot} public void `[`queryBatteryState`](#classCellulo_1_1CelluloBluetooth_1af4ba396b5d36fd2c5c23abe9bb1262c8)`()` 

Sends a battery state query.

#### `{slot} public void `[`setLEDResponseMode`](#classCellulo_1_1CelluloBluetooth_1aa56fe3eed954d834321fab5763142cba)`(`[`CelluloBluetoothEnums::LEDResponseMode`](#classCellulo_1_1CelluloBluetoothEnums_1a57ece08557723b6428a74ba3b1265b29)` mode)` 

Sets the LED response mode, i.e the LED visual response of the robot to touches.

#### Parameters
* `mode` LED resposne mode

#### `{slot} public void `[`setLocomotionInteractivityMode`](#classCellulo_1_1CelluloBluetooth_1ad110ee7cb10a67b3aa4c4a3d55fa8d2d)`(`[`CelluloBluetoothEnums::LocomotionInteractivityMode`](#classCellulo_1_1CelluloBluetoothEnums_1ae5126bceecb95ffc8846e8c72f379812)` mode)` 

Sets the locomotion interactivity mode, i.e the dependance of locomotion to user input.

#### Parameters
* `mode` Locomotion interactivity mode

#### `{slot} public void `[`setGestureEnabled`](#classCellulo_1_1CelluloBluetooth_1a9bd4f2f2feb7ff0f00c4f05767aca0ea)`(bool enabled)` 

Enables/disables raw touch signal offset querying and processing.

#### Parameters
* `enabled` Whether to enable

#### `{slot} public void `[`setCasualBackdriveAssistEnabled`](#classCellulo_1_1CelluloBluetooth_1a5f26ca73c9bbb4ff882f94f2cfdfd62c)`(bool enabled)` 

Enables/disables assist for easy backdriving.

#### Parameters
* `enabled` Whether to enable

#### `{slot} public void `[`setHapticBackdriveAssist`](#classCellulo_1_1CelluloBluetooth_1a4e127b89e9ac560b558262916d3230f5)`(float xAssist,float yAssist,float thetaAssist)` 

Haptic feedback-oriented backdrive assist.

Pass 0 to all parameters to disable. Disables casual backdrive assist upon enabling.

#### Parameters
* `xAssist` X assist with respect to x drive velocity, can be negative 

* `yAssist` Y assist with respect to y drive velocity, can be negative 

* `thetaAssist` Theta assist with respect to w drive, can be negative

#### `{slot} public void `[`setVisualEffect`](#classCellulo_1_1CelluloBluetooth_1a87d834bff1ddded9c83e427802acf2d8)`(`[`CelluloBluetoothEnums::VisualEffect`](#classCellulo_1_1CelluloBluetoothEnums_1a810aca61e84c1e31fb751335cd776361)` effect,QColor color,int value)` 

Sets the visual effect on the robot, changing LED illumination.

#### Parameters
* `effect` The effect ordinal 

* `color` Color 

* `value` A value possibly meaningful for the effect (between 0 and 255)

#### `{slot} public void `[`polyBezierInit`](#classCellulo_1_1CelluloBluetooth_1a5943ebcea0fe39fb517fff8ec3c26d0f)`(const QVector2D & point0)` 

Sends the first control point of the composite Bézier curve for motion tracking.

#### Parameters
* `point0` The initial point, i.e the first control point of the first segment

#### `{slot} public void `[`polyBezierAppend`](#classCellulo_1_1CelluloBluetooth_1ac6034aa0cea06d6843281e8ecda357fd)`(const QVector2D & point1,const QVector2D & point2,const QVector2D & point3)` 

Adds a segment to the composite Bézier curve for motion tracking; [polyBezierInit()](#classCellulo_1_1CelluloBluetooth_1a5943ebcea0fe39fb517fff8ec3c26d0f) must be called before.

The first control point is the last control point of the previously added segment or the initial point.

#### Parameters
* `point1` The second control point for the curve 

* `point2` The third control point for the curve 

* `point3` The fourth control point for the curve

#### `{slot} public void `[`polyBezierSetFromZone`](#classCellulo_1_1CelluloBluetooth_1ad183a2dd9341750e9449532ea9a6880a)`(CelluloZone * zone)` 

Sends the composite Bézier curve in the zone to the robot.

#### Parameters
* `zone` The zone that contains the composite Bézier curve path

#### `{slot} public void `[`setGoalPolyBezier`](#classCellulo_1_1CelluloBluetooth_1aa225ca6d3c15fe4461f16e9fb873299b)`(float v,float w)` 

Starts tracking the previously set composite Bézier curve.

#### Parameters
* `v` Linear velocity tangent to the curve 

* `w` Angular velocity throughout the traversal

#### `{slot} public void `[`setGoalPolyBezierAligned`](#classCellulo_1_1CelluloBluetooth_1afbda284c48ef1cae82357cd2a6afc83d)`(float v,float theta,float w)` 

Starts tracking the previously set composite Bézier curve while keeping orientation aligned to the curve.

#### Parameters
* `v` Linear velocity tangent to the curve 

* `theta` Orientation to track with respect to the curve tangent orientation, in degrees 

* `w` Maximum angular velocity while tracking orientation, in rad/s

#### `{slot} public void `[`reset`](#classCellulo_1_1CelluloBluetooth_1ab29c7d9cce6b8ec5e5b8f82da6332886)`()` 

Initiates a software reset on the robot.

#### `{slot} public void `[`shutdown`](#classCellulo_1_1CelluloBluetooth_1a6920c929fca0d2573144d53de1667a85)`()` 

Initiates sleep on the robot.

# class `Cellulo::CelluloBluetoothEMP` 

```
class Cellulo::CelluloBluetoothEMP
  : public QQuickItem
```  

Object that mass reset/shuts down all robots.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} bool `[`continuous`](#classCellulo_1_1CelluloBluetoothEMP_1aa0ffa9fb0d5d25770529ddfb231e5ec4) | Whether to shut down or reset the same robots over and over, default false.
`{property} QStringList `[`macAddrToBlast`](#classCellulo_1_1CelluloBluetoothEMP_1a948d8212e52c2514a0329cfcbfabeff3) | List of robots waiting to be shut down or reset.
`{property} QStringList `[`macAddrBlasted`](#classCellulo_1_1CelluloBluetoothEMP_1a1af9f3d90c9cf47bd112d8a453d3a6da) | List of robots already shut down or reset.
`{slot} public void `[`resetLater`](#classCellulo_1_1CelluloBluetoothEMP_1ab12436c821fecc2050cc3c37925229b2)`(QString macAddr)` | Initiates connection to the robot to reset it when it's connected.
`{slot} public void `[`shutdownLater`](#classCellulo_1_1CelluloBluetoothEMP_1a72fe2ad6c136c80f7e685b5620a5d394)`(QString macAddr)` | Initiates connection to the robot to shut it down when it's connected.
`{slot} public void `[`clear`](#classCellulo_1_1CelluloBluetoothEMP_1a9dda86060b992a8104ad9f13e4030a1f)`()` | Clears both lists, drops all connections.

## Members

#### `{property} bool `[`continuous`](#classCellulo_1_1CelluloBluetoothEMP_1aa0ffa9fb0d5d25770529ddfb231e5ec4) 

Whether to shut down or reset the same robots over and over, default false.

Whether to blast same robots.

#### `{property} QStringList `[`macAddrToBlast`](#classCellulo_1_1CelluloBluetoothEMP_1a948d8212e52c2514a0329cfcbfabeff3) 

List of robots waiting to be shut down or reset.

List of mac addresses that are being blasted.

#### `{property} QStringList `[`macAddrBlasted`](#classCellulo_1_1CelluloBluetoothEMP_1a1af9f3d90c9cf47bd112d8a453d3a6da) 

List of robots already shut down or reset.

List of mac addresses that are confirmed to be blasted.

#### `{slot} public void `[`resetLater`](#classCellulo_1_1CelluloBluetoothEMP_1ab12436c821fecc2050cc3c37925229b2)`(QString macAddr)` 

Initiates connection to the robot to reset it when it's connected.

#### `{slot} public void `[`shutdownLater`](#classCellulo_1_1CelluloBluetoothEMP_1a72fe2ad6c136c80f7e685b5620a5d394)`(QString macAddr)` 

Initiates connection to the robot to shut it down when it's connected.

#### `{slot} public void `[`clear`](#classCellulo_1_1CelluloBluetoothEMP_1a9dda86060b992a8104ad9f13e4030a1f)`()` 

Clears both lists, drops all connections.

# class `Cellulo::CelluloBluetoothEnums` 

```
class Cellulo::CelluloBluetoothEnums
  : public QObject
```  

Wrapper containing all the enums of [CelluloBluetooth](#classCellulo_1_1CelluloBluetooth).

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

# class `Cellulo::CelluloBluetoothScanner` 

```
class Cellulo::CelluloBluetoothScanner
  : public QQuickItem
```  

Object that scans for Cellulo robots.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} bool `[`continuous`](#classCellulo_1_1CelluloBluetoothScanner_1a31ff7b1923a5fd0164407a10bde44667) | Whether to scan continuously, default false.
`{property} bool `[`scanning`](#classCellulo_1_1CelluloBluetoothScanner_1af415501e8197aff4cb8705b5743451f4) | Whether scanning now, read-only.
`{property} QStringList `[`foundRobots`](#classCellulo_1_1CelluloBluetoothScanner_1ac93b05ef41326660bd48f6eca8a2ffb2) | List of found robots, read-only.
`{signal} public void `[`robotDiscovered`](#classCellulo_1_1CelluloBluetoothScanner_1a3107786d8400a26b0cf8f5ef970f3ca4)`(QString const & macAddr)` | Emitted when a new Cellulo robot is discovered.
`{signal} public void `[`finished`](#classCellulo_1_1CelluloBluetoothScanner_1a35d79f8e7315ad2fc807bbb482e7ee1b)`()` | Emitted when scanning finishes.
`{slot} public void `[`start`](#classCellulo_1_1CelluloBluetoothScanner_1aa1d2d32cfc92e514c0e901556b81fafc)`()` | Starts scanning.
`{slot} public void `[`stop`](#classCellulo_1_1CelluloBluetoothScanner_1a929b9cbdd80e6408606a6aa89072475e)`()` | Stops scanning.
`{slot} public void `[`clear`](#classCellulo_1_1CelluloBluetoothScanner_1ad289a3fbcb416c37d7c6bd36ec14d2f4)`()` | Clears the list of found robots.

## Members

#### `{property} bool `[`continuous`](#classCellulo_1_1CelluloBluetoothScanner_1a31ff7b1923a5fd0164407a10bde44667) 

Whether to scan continuously, default false.

Whether to continuously scan.

#### `{property} bool `[`scanning`](#classCellulo_1_1CelluloBluetoothScanner_1af415501e8197aff4cb8705b5743451f4) 

Whether scanning now, read-only.

#### `{property} QStringList `[`foundRobots`](#classCellulo_1_1CelluloBluetoothScanner_1ac93b05ef41326660bd48f6eca8a2ffb2) 

List of found robots, read-only.

List of robot MAC addresses that are found.

#### `{signal} public void `[`robotDiscovered`](#classCellulo_1_1CelluloBluetoothScanner_1a3107786d8400a26b0cf8f5ef970f3ca4)`(QString const & macAddr)` 

Emitted when a new Cellulo robot is discovered.

#### Parameters
* `macAddr` Mac address of the newly discovered robot

#### `{signal} public void `[`finished`](#classCellulo_1_1CelluloBluetoothScanner_1a35d79f8e7315ad2fc807bbb482e7ee1b)`()` 

Emitted when scanning finishes.

#### `{slot} public void `[`start`](#classCellulo_1_1CelluloBluetoothScanner_1aa1d2d32cfc92e514c0e901556b81fafc)`()` 

Starts scanning.

#### `{slot} public void `[`stop`](#classCellulo_1_1CelluloBluetoothScanner_1a929b9cbdd80e6408606a6aa89072475e)`()` 

Stops scanning.

#### `{slot} public void `[`clear`](#classCellulo_1_1CelluloBluetoothScanner_1ad289a3fbcb416c37d7c6bd36ec14d2f4)`()` 

Clears the list of found robots.

# class `Cellulo::CelluloCommUtil` 

```
class Cellulo::CelluloCommUtil
  : public QObject
```  

Cellulo communication utilities.

This class is **singleton**, you can call `ThisClass.anyFunction()` and use `ThisClass.anyProperty` directly.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public static Q_INVOKABLE bool `[`testRobotPoolDaemon`](#classCellulo_1_1CelluloCommUtil_1a6ec0d01253d86b0757f767be31c8de56)`()` | Tests whether cellulorobotpoold is installed.
`public static Q_INVOKABLE bool `[`startRobotPoolDaemon`](#classCellulo_1_1CelluloCommUtil_1ac5e3df561325999389b6927faaa56b35)`()` | Attempts to launch a cellulorobotpoold.
`public static Q_INVOKABLE bool `[`stopRobotPoolDaemon`](#classCellulo_1_1CelluloCommUtil_1a4c210c0e5c167acc4b9001680094fb11)`()` | Attempts to stop the already existing cellulorobotpoold.

## Members

#### `public static Q_INVOKABLE bool `[`testRobotPoolDaemon`](#classCellulo_1_1CelluloCommUtil_1a6ec0d01253d86b0757f767be31c8de56)`()` 

Tests whether cellulorobotpoold is installed.

#### Returns
Whether cellulorobotpoold is installed

#### `public static Q_INVOKABLE bool `[`startRobotPoolDaemon`](#classCellulo_1_1CelluloCommUtil_1ac5e3df561325999389b6927faaa56b35)`()` 

Attempts to launch a cellulorobotpoold.

#### Returns
Whether successfully launched

#### `public static Q_INVOKABLE bool `[`stopRobotPoolDaemon`](#classCellulo_1_1CelluloCommUtil_1a4c210c0e5c167acc4b9001680094fb11)`()` 

Attempts to stop the already existing cellulorobotpoold.

#### Returns
Whether successfully stopped

# class `Cellulo::CelluloLocalRelayServer` 

```
class Cellulo::CelluloLocalRelayServer
  : public Cellulo::CelluloRelayServer
```  

Relays packets between a client and physical robots over a Unix domain socket. Accepts connections from a `CelluloLocalRelayClient`.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `Cellulo::CelluloRelayClient` 

```
class Cellulo::CelluloRelayClient
  : public QQuickItem
```  

Object that relays packets between a `[CelluloRelayServer](#classCellulo_1_1CelluloRelayServer)` and virtual robot objects.

The robots that are connected to this object (i.e having their relay client set as this object) have all their commands routed to the `[CelluloRelayServer](#classCellulo_1_1CelluloRelayServer)` that is connected to this client, effectively making the `[CelluloBluetooth](#classCellulo_1_1CelluloBluetooth)`s under control of this client to become virtual robots that represent the physical robots connected to the server side.

This class is **abstract**, you cannot instantiate it directly. Refer to classes derived from it.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} bool `[`connected`](#classCellulo_1_1CelluloRelayClient_1a8425b7761ae0c840c8e34dc741c162f0) | Whether currently connected to the server, read-only.
`{property} QString `[`serverAddress`](#classCellulo_1_1CelluloRelayClient_1a61a164f2a1ff8077854253ccade0ebfa) | Address to connect to, i.e name of the domain socket (default is "cellulo_relay") or the IP address of the TCP socket (default is "localhost")
`{property} int `[`port`](#classCellulo_1_1CelluloRelayClient_1a6bf83800ed227b6c5e2e33f1de5d0702) | Port to connect to in TCP (default is 2556), unused in local sockets.
`{property} int `[`autoConnect`](#classCellulo_1_1CelluloRelayClient_1ac03d0024c5c1656d1e6308b8461e3190) | Whether to try to reconnect when the connection drops or in the beginning, default is true.
`{property} QVariantList `[`robots`](#classCellulo_1_1CelluloRelayClient_1ae88af0add6b8a6ecfa0e04ee5d34a53c) | List of virtual robots currently under control of this client, read-only.
`{signal} public void `[`connected`](#classCellulo_1_1CelluloRelayClient_1a7d5937c7d07a5a07f471f4e956a0b9a4)`()` | Emitted when the server socket is connected.
`{signal} public void `[`disconnected`](#classCellulo_1_1CelluloRelayClient_1a10cfb3ae0feb9843741af7cfa4125196)`()` | Emitted when the server socket is disconected.
`{signal} public void `[`unknownRobotAtServer`](#classCellulo_1_1CelluloRelayClient_1a8744b4de8ab1164e8b4e1659f56281ff)`(QString macAddr)` | Emitted when the server has a robot already connected that is not in the robots list covered by this client.
`{slot} public void `[`connectToServer`](#classCellulo_1_1CelluloRelayClient_1a53b79491108537bf602cadfe75fc026f)`()` | Initiates a connection to the service on the server.
`{slot} public void `[`disconnectFromServer`](#classCellulo_1_1CelluloRelayClient_1a70b239ca558b93c6993ba92b0d6f6649)`()` | Starts closing the socket.
`{slot} public void `[`addRobot`](#classCellulo_1_1CelluloRelayClient_1a891162b7696811d0eaf6266da607e39e)`(`[`CelluloBluetooth`](#classCellulo_1_1CelluloBluetooth)` * robot,bool select)` | Adds the robot to the robots list, sets the robot's relay client to this object.
`{slot} public void `[`removeRobot`](#classCellulo_1_1CelluloRelayClient_1a22a1ee57b76d1a0c4df249fd320de743)`(`[`CelluloBluetooth`](#classCellulo_1_1CelluloBluetooth)` * robot)` | Removes the robot from the robots list.

## Members

#### `{property} bool `[`connected`](#classCellulo_1_1CelluloRelayClient_1a8425b7761ae0c840c8e34dc741c162f0) 

Whether currently connected to the server, read-only.

#### `{property} QString `[`serverAddress`](#classCellulo_1_1CelluloRelayClient_1a61a164f2a1ff8077854253ccade0ebfa) 

Address to connect to, i.e name of the domain socket (default is "cellulo_relay") or the IP address of the TCP socket (default is "localhost")

Server's address, e.g "127.0.0.1".

#### `{property} int `[`port`](#classCellulo_1_1CelluloRelayClient_1a6bf83800ed227b6c5e2e33f1de5d0702) 

Port to connect to in TCP (default is 2556), unused in local sockets.

#### `{property} int `[`autoConnect`](#classCellulo_1_1CelluloRelayClient_1ac03d0024c5c1656d1e6308b8461e3190) 

Whether to try to reconnect when the connection drops or in the beginning, default is true.

#### `{property} QVariantList `[`robots`](#classCellulo_1_1CelluloRelayClient_1ae88af0add6b8a6ecfa0e04ee5d34a53c) 

List of virtual robots currently under control of this client, read-only.

#### `{signal} public void `[`connected`](#classCellulo_1_1CelluloRelayClient_1a7d5937c7d07a5a07f471f4e956a0b9a4)`()` 

Emitted when the server socket is connected.

#### `{signal} public void `[`disconnected`](#classCellulo_1_1CelluloRelayClient_1a10cfb3ae0feb9843741af7cfa4125196)`()` 

Emitted when the server socket is disconected.

#### `{signal} public void `[`unknownRobotAtServer`](#classCellulo_1_1CelluloRelayClient_1a8744b4de8ab1164e8b4e1659f56281ff)`(QString macAddr)` 

Emitted when the server has a robot already connected that is not in the robots list covered by this client.

#### Parameters
* `macAddr` MAC address of the unknown robot

#### `{slot} public void `[`connectToServer`](#classCellulo_1_1CelluloRelayClient_1a53b79491108537bf602cadfe75fc026f)`()` 

Initiates a connection to the service on the server.

#### `{slot} public void `[`disconnectFromServer`](#classCellulo_1_1CelluloRelayClient_1a70b239ca558b93c6993ba92b0d6f6649)`()` 

Starts closing the socket.

#### `{slot} public void `[`addRobot`](#classCellulo_1_1CelluloRelayClient_1a891162b7696811d0eaf6266da607e39e)`(`[`CelluloBluetooth`](#classCellulo_1_1CelluloBluetooth)` * robot,bool select)` 

Adds the robot to the robots list, sets the robot's relay client to this object.

#### Parameters
* `robot` New robot 

* `select` Selects the newly added robot as current; pass true if robot is added as a result of an [unknownRobotAtServer()](#classCellulo_1_1CelluloRelayClient_1a8744b4de8ab1164e8b4e1659f56281ff) signal

#### `{slot} public void `[`removeRobot`](#classCellulo_1_1CelluloRelayClient_1a22a1ee57b76d1a0c4df249fd320de743)`(`[`CelluloBluetooth`](#classCellulo_1_1CelluloBluetooth)` * robot)` 

Removes the robot from the robots list.

#### Parameters
* `robot` Robot to remove

# class `Cellulo::CelluloRelayServer` 

```
class Cellulo::CelluloRelayServer
  : public QQuickItem
```  

Object that relays packets between a `[CelluloRelayClient](#classCellulo_1_1CelluloRelayClient)` and physical robots.

The robots that are connected to this object (i.e having their relay server set as this object) have all their events routed to the `[CelluloRelayClient](#classCellulo_1_1CelluloRelayClient)` that is connected to this server. Listens for incoming connections from a client upon creation.

This class is **abstract**, you cannot instantiate it directly. Refer to classes derived from it.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} QString `[`address`](#classCellulo_1_1CelluloRelayServer_1ac4e8d3e0f576133076f78c24e283a8fe) | Host address, i.e name of the domain socket (default is "cellulo_relay") or the IP address of the TCP socket (default is "localhost")
`{property} int `[`port`](#classCellulo_1_1CelluloRelayServer_1aa6697416fd80d8f80bb3c9c6eba60535) | Port to listen to in TCP (default is 2556), unused in local sockets.
`{signal} public void `[`clientConnected`](#classCellulo_1_1CelluloRelayServer_1a0c177f69d6a00e9c46627a6350c2d2b0)`()` | Emitted when a new client connects.
`{signal} public void `[`clientDisconnected`](#classCellulo_1_1CelluloRelayServer_1a131a26e03a7f7bfd03cd63c196092be6)`()` | Emitted when the client disconnects.
`{signal} public void `[`robotAdded`](#classCellulo_1_1CelluloRelayServer_1a6f4ac79e3ce85bdf24ba05f1b71495ba)`(QString macAddr)` | Emitted when a new robot is added to the server.
`{signal} public void `[`robotRemoved`](#classCellulo_1_1CelluloRelayServer_1ac9a0a3c6db06a0e11b6f01910774295f)`(QString macAddr)` | Emitted when a robot is removed from the server.
`{slot} public bool `[`isListening`](#classCellulo_1_1CelluloRelayServer_1a26ed5be2621c7a65c61c6595c18bd808)`() const` | Gets whether the server is listening.
`{slot} public void `[`setListening`](#classCellulo_1_1CelluloRelayServer_1a3fc354faab1ee173a083453e5c7926b9)`(bool enable)` | Enables/disables listening.
`{slot} public void `[`addRobot`](#classCellulo_1_1CelluloRelayServer_1a00e7fdec95b84aae8dd429bc3cd57b88)`(`[`CelluloBluetooth`](#classCellulo_1_1CelluloBluetooth)` * robot)` | Adds robot to the robots list, sets the robot's relay server to this object.
`{slot} public void `[`removeRobot`](#classCellulo_1_1CelluloRelayServer_1ad5190154f36e71c91069dff9793cba1d)`(`[`CelluloBluetooth`](#classCellulo_1_1CelluloBluetooth)` * robot)` | Removes the robot from the robots list.
`{slot} public void `[`disconnectClient`](#classCellulo_1_1CelluloRelayServer_1af945c9a03a454a34dad636fa8f3eda1f)`()` | Closes the client's socket.

## Members

#### `{property} QString `[`address`](#classCellulo_1_1CelluloRelayServer_1ac4e8d3e0f576133076f78c24e283a8fe) 

Host address, i.e name of the domain socket (default is "cellulo_relay") or the IP address of the TCP socket (default is "localhost")

Host address, e.g "127.0.0.1" for TCP.

#### `{property} int `[`port`](#classCellulo_1_1CelluloRelayServer_1aa6697416fd80d8f80bb3c9c6eba60535) 

Port to listen to in TCP (default is 2556), unused in local sockets.

#### `{signal} public void `[`clientConnected`](#classCellulo_1_1CelluloRelayServer_1a0c177f69d6a00e9c46627a6350c2d2b0)`()` 

Emitted when a new client connects.

#### `{signal} public void `[`clientDisconnected`](#classCellulo_1_1CelluloRelayServer_1a131a26e03a7f7bfd03cd63c196092be6)`()` 

Emitted when the client disconnects.

#### `{signal} public void `[`robotAdded`](#classCellulo_1_1CelluloRelayServer_1a6f4ac79e3ce85bdf24ba05f1b71495ba)`(QString macAddr)` 

Emitted when a new robot is added to the server.

#### Parameters
* `macAddr` MAC address of the added robot

#### `{signal} public void `[`robotRemoved`](#classCellulo_1_1CelluloRelayServer_1ac9a0a3c6db06a0e11b6f01910774295f)`(QString macAddr)` 

Emitted when a robot is removed from the server.

#### Parameters
* `macAddr` MAC address of the removed robot

#### `{slot} public bool `[`isListening`](#classCellulo_1_1CelluloRelayServer_1a26ed5be2621c7a65c61c6595c18bd808)`() const` 

Gets whether the server is listening.

#### Returns
Whether the server is listening

#### `{slot} public void `[`setListening`](#classCellulo_1_1CelluloRelayServer_1a3fc354faab1ee173a083453e5c7926b9)`(bool enable)` 

Enables/disables listening.

#### Parameters
* `enable` Whether to listen or close the server and stop listening

#### `{slot} public void `[`addRobot`](#classCellulo_1_1CelluloRelayServer_1a00e7fdec95b84aae8dd429bc3cd57b88)`(`[`CelluloBluetooth`](#classCellulo_1_1CelluloBluetooth)` * robot)` 

Adds robot to the robots list, sets the robot's relay server to this object.

#### Parameters
* `robot` New robot

#### `{slot} public void `[`removeRobot`](#classCellulo_1_1CelluloRelayServer_1ad5190154f36e71c91069dff9793cba1d)`(`[`CelluloBluetooth`](#classCellulo_1_1CelluloBluetooth)` * robot)` 

Removes the robot from the robots list.

#### Parameters
* `robot` Existing robot

#### `{slot} public void `[`disconnectClient`](#classCellulo_1_1CelluloRelayServer_1af945c9a03a454a34dad636fa8f3eda1f)`()` 

Closes the client's socket.

# class `Cellulo::CelluloRobot` 

```
class Cellulo::CelluloRobot
  : public Cellulo::CelluloBluetooth
```  

The main object that represents a Cellulo robot. Inherits from `[CelluloBluetooth](#classCellulo_1_1CelluloBluetooth)` and has all its functionalities (not listed here).

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

# class `Cellulo::CelluloRobotPoolClient` 

```
class Cellulo::CelluloRobotPoolClient
  : public CelluloLocalRelayClient
```  

Object that uses the robots connected to a `cellulorobotpoold`.

Inherits from `CelluloLocalRelayClient`, which in turn inherits from `[CelluloRelayClient](#classCellulo_1_1CelluloRelayClient)`, which means that their properties, signals and slots can be used. The most useful among these is the `robots` property that exposes the list of currently available robots in this pool.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} QJSValue `[`createRobot`](#classCellulo_1_1CelluloRobotPoolClient_1a54e7e3a28f5ca7902b2834f836e1b6f2) | Must be set to a user-defined javascript function that takes the MAC address (string) of an already connected robot and returns a [CelluloBluetooth](#classCellulo_1_1CelluloBluetooth) object or CelluloBluetooth-derived object.

## Members

#### `{property} QJSValue `[`createRobot`](#classCellulo_1_1CelluloRobotPoolClient_1a54e7e3a28f5ca7902b2834f836e1b6f2) 

Must be set to a user-defined javascript function that takes the MAC address (string) of an already connected robot and returns a [CelluloBluetooth](#classCellulo_1_1CelluloBluetooth) object or CelluloBluetooth-derived object.

# class `Cellulo::CelluloTcpRelayClient` 

```
class Cellulo::CelluloTcpRelayClient
  : public Cellulo::CelluloRelayClient
```  

Relays packets between a server and virtual robot objects over a TCP socket. Connects to a `[CelluloTcpRelayServer](#classCellulo_1_1CelluloTcpRelayServer)`.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `Cellulo::CelluloTcpRelayServer` 

```
class Cellulo::CelluloTcpRelayServer
  : public Cellulo::CelluloRelayServer
```  

Relays packets between a client and physical robots over a TCP socket. Accepts connections from a `[CelluloTcpRelayClient](#classCellulo_1_1CelluloTcpRelayClient)`.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

Generated by [Moxygen](https://sourcey.com/moxygen)