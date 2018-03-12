# group `comm` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[`Cellulo::CelluloBluetooth`](doc/doc-comm.md#classCellulo_1_1CelluloBluetooth) | Object that communicates with one [Cellulo](#namespaceCellulo) robot over Bluetooth.
`class `[`Cellulo::CelluloBluetoothEMP`](doc/doc-comm.md#classCellulo_1_1CelluloBluetoothEMP) | Object that mass reset/shuts down all robots.
`class `[`Cellulo::CelluloBluetoothScanner`](doc/doc-comm.md#classCellulo_1_1CelluloBluetoothScanner) | Object that scans for [Cellulo](#namespaceCellulo) robots.
`class `[`Cellulo::CelluloCommUtil`](doc/doc-comm.md#classCellulo_1_1CelluloCommUtil) | [Cellulo](#namespaceCellulo) communication utilities.

# class `Cellulo::CelluloBluetooth` 

```
class Cellulo::CelluloBluetooth
  : public CelluloZoneClient
```  

Object that communicates with one [Cellulo](#namespaceCellulo) robot over Bluetooth.

Inherits from `CelluloZoneClient` and therefore can be used as one.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} QString `[`localAdapterMacAddr`](doc/doc-comm.md#classCellulo_1_1CelluloBluetooth_1a31ca21c1a395893cbfe0e4ea4bb6e590) | Local adapter's MAC address chosen to connect to the robot, empty string if using default adapter; only works on Linux and if the plugin is built with BlueZ.
`{property} bool `[`autoConnect`](doc/doc-comm.md#classCellulo_1_1CelluloBluetooth_1a2c2f916967bee8e06038b92f46bb4248) | Whether to start connecting immediately as soon as **macAddr** is set and to reconnect if connection drops, default true.
`{property} QString `[`macAddr`](doc/doc-comm.md#classCellulo_1_1CelluloBluetooth_1a3a4f9fd2da2440be2368bd4b9e74f0f2) | Robot MAC address in the form "XX:XX:XX:XX:XX:XX".
`{property} `[`CelluloBluetoothEnums::ConnectionStatus`](#classCellulo_1_1CelluloBluetoothEnums_1a9bdbb91140cd33c3daa779af49c7ed97)` `[`connectionStatus`](#classCellulo_1_1CelluloBluetooth_1a9520239e44d19dd120c6779a126a543f) | Current connection status to the robot, read-only.
`{property} `[`CelluloBluetoothEnums::BatteryState`](#classCellulo_1_1CelluloBluetoothEnums_1a895a56801308039dd778b0a0fb6809b8)` `[`batteryState`](#classCellulo_1_1CelluloBluetooth_1a87f7b19fe478e73346094a8208c00ea5) | Robot's current battery state, read-only.
`{property} float `[`x`](doc/doc-comm.md#classCellulo_1_1CelluloBluetooth_1af13c47b29e25220131c182d963e41034) | Robot's x coordinate in mm, read-only.
`{property} float `[`y`](doc/doc-comm.md#classCellulo_1_1CelluloBluetooth_1ac1276ac29b10f1f28fa0f6a00416fa60) | Robot's y coordinate in mm, read-only.
`{property} float `[`theta`](doc/doc-comm.md#classCellulo_1_1CelluloBluetooth_1acaee9ee4adc6528bcaae8c9577790d02) | Robot's orientation in degrees, read-only.
`{property} bool `[`kidnapped`](doc/doc-comm.md#classCellulo_1_1CelluloBluetooth_1a4be50315021f3a8df91275ee89bccfa5) | Whether the robot is not on encoded paper, read-only.
`{property} `[`CelluloBluetoothEnums::Gesture`](#classCellulo_1_1CelluloBluetoothEnums_1aac0e86c82f086708674759431d6ff0fb)` `[`gesture`](#classCellulo_1_1CelluloBluetooth_1af9c3ebbd5cd9b40135f3b0289b8189ab) | Current robot gesture (if gesture detection is enabled), read-only.
`{property} bool `[`timestampingEnabled`](doc/doc-comm.md#classCellulo_1_1CelluloBluetooth_1ab93e751696cdaa7635681bb05b5598f5) | Whether the robot will send its own timestamp along with its pose, default false.
`{property} int `[`lastTimestamp`](doc/doc-comm.md#classCellulo_1_1CelluloBluetooth_1a7884ff94eaf821db9310d20f95024ad5) | Last local timestamp received along with pose (is valid if **timestampingEnabled** is true), read-only.
`{property} float `[`framerate`](doc/doc-comm.md#classCellulo_1_1CelluloBluetooth_1aa64ae00fc5683f384940db4b9e72ac8d) | Localization framerate calculated from local timestamps received along with pose (is valid if **timestampingEnabled** is true), read-only.
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
`{slot} public void `[`polyBezierAppend`](#classCellulo_1_1CelluloBluetooth_1ac6034aa0cea06d6843281e8ecda357fd)`(const QVector2D & point1,const QVector2D & point2,const QVector2D & point3)` | Adds a segment to the composite Bézier curve for motion tracking; [polyBezierInit()](doc/doc-comm.md#classCellulo_1_1CelluloBluetooth_1a5943ebcea0fe39fb517fff8ec3c26d0f) must be called before.
`{slot} public void `[`polyBezierSetFromZone`](#classCellulo_1_1CelluloBluetooth_1ad183a2dd9341750e9449532ea9a6880a)`(CelluloZone * zone)` | Sends the composite Bézier curve in the zone to the robot.
`{slot} public void `[`setGoalPolyBezier`](#classCellulo_1_1CelluloBluetooth_1aa225ca6d3c15fe4461f16e9fb873299b)`(float v,float w)` | Starts tracking the previously set composite Bézier curve.
`{slot} public void `[`setGoalPolyBezierAligned`](#classCellulo_1_1CelluloBluetooth_1afbda284c48ef1cae82357cd2a6afc83d)`(float v,float theta,float w)` | Starts tracking the previously set composite Bézier curve while keeping orientation aligned to the curve.
`{slot} public void `[`reset`](#classCellulo_1_1CelluloBluetooth_1ab29c7d9cce6b8ec5e5b8f82da6332886)`()` | Initiates a software reset on the robot.
`{slot} public void `[`shutdown`](#classCellulo_1_1CelluloBluetooth_1a6920c929fca0d2573144d53de1667a85)`()` | Initiates sleep on the robot.

## Members

#### `{property} QString `[`localAdapterMacAddr`](doc/doc-comm.md#classCellulo_1_1CelluloBluetooth_1a31ca21c1a395893cbfe0e4ea4bb6e590) 

Local adapter's MAC address chosen to connect to the robot, empty string if using default adapter; only works on Linux and if the plugin is built with BlueZ.

MAC address of the local adapter to use when connecting to the robot, only works on Linux.

#### `{property} bool `[`autoConnect`](doc/doc-comm.md#classCellulo_1_1CelluloBluetooth_1a2c2f916967bee8e06038b92f46bb4248) 

Whether to start connecting immediately as soon as **macAddr** is set and to reconnect if connection drops, default true.

Whether the socket will try to reconnect every time it drops, will connect when mac address is set.

#### `{property} QString `[`macAddr`](doc/doc-comm.md#classCellulo_1_1CelluloBluetooth_1a3a4f9fd2da2440be2368bd4b9e74f0f2) 

Robot MAC address in the form "XX:XX:XX:XX:XX:XX".

Bluetooth MAC address of the server.

#### `{property} `[`CelluloBluetoothEnums::ConnectionStatus`](#classCellulo_1_1CelluloBluetoothEnums_1a9bdbb91140cd33c3daa779af49c7ed97)` `[`connectionStatus`](#classCellulo_1_1CelluloBluetooth_1a9520239e44d19dd120c6779a126a543f) 

Current connection status to the robot, read-only.

Bluetooth connection status.

#### `{property} `[`CelluloBluetoothEnums::BatteryState`](#classCellulo_1_1CelluloBluetoothEnums_1a895a56801308039dd778b0a0fb6809b8)` `[`batteryState`](#classCellulo_1_1CelluloBluetooth_1a87f7b19fe478e73346094a8208c00ea5) 

Robot's current battery state, read-only.

Current battery state.

#### `{property} float `[`x`](doc/doc-comm.md#classCellulo_1_1CelluloBluetooth_1af13c47b29e25220131c182d963e41034) 

Robot's x coordinate in mm, read-only.

Current x position in mm.

#### `{property} float `[`y`](doc/doc-comm.md#classCellulo_1_1CelluloBluetooth_1ac1276ac29b10f1f28fa0f6a00416fa60) 

Robot's y coordinate in mm, read-only.

Current y position in mm.

#### `{property} float `[`theta`](doc/doc-comm.md#classCellulo_1_1CelluloBluetooth_1acaee9ee4adc6528bcaae8c9577790d02) 

Robot's orientation in degrees, read-only.

Current orientation in degrees.

#### `{property} bool `[`kidnapped`](doc/doc-comm.md#classCellulo_1_1CelluloBluetooth_1a4be50315021f3a8df91275ee89bccfa5) 

Whether the robot is not on encoded paper, read-only.

Whether currently kidnapped.

#### `{property} `[`CelluloBluetoothEnums::Gesture`](#classCellulo_1_1CelluloBluetoothEnums_1aac0e86c82f086708674759431d6ff0fb)` `[`gesture`](#classCellulo_1_1CelluloBluetooth_1af9c3ebbd5cd9b40135f3b0289b8189ab) 

Current robot gesture (if gesture detection is enabled), read-only.

Current gesture.

#### `{property} bool `[`timestampingEnabled`](doc/doc-comm.md#classCellulo_1_1CelluloBluetooth_1ab93e751696cdaa7635681bb05b5598f5) 

Whether the robot will send its own timestamp along with its pose, default false.

Whether timestamping along with pose is enabled and idling disabled.

#### `{property} int `[`lastTimestamp`](doc/doc-comm.md#classCellulo_1_1CelluloBluetooth_1a7884ff94eaf821db9310d20f95024ad5) 

Last local timestamp received along with pose (is valid if **timestampingEnabled** is true), read-only.

Latest received onboard timestamp (in milliseconds)

#### `{property} float `[`framerate`](doc/doc-comm.md#classCellulo_1_1CelluloBluetooth_1aa64ae00fc5683f384940db4b9e72ac8d) 

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
`{property} bool `[`continuous`](doc/doc-comm.md#classCellulo_1_1CelluloBluetoothEMP_1aa0ffa9fb0d5d25770529ddfb231e5ec4) | Whether to shut down or reset the same robots over and over, default false.
`{property} QStringList `[`macAddrToBlast`](doc/doc-comm.md#classCellulo_1_1CelluloBluetoothEMP_1a948d8212e52c2514a0329cfcbfabeff3) | List of robots waiting to be shut down or reset.
`{property} QStringList `[`macAddrBlasted`](doc/doc-comm.md#classCellulo_1_1CelluloBluetoothEMP_1a1af9f3d90c9cf47bd112d8a453d3a6da) | List of robots already shut down or reset.
`{slot} public void `[`resetLater`](#classCellulo_1_1CelluloBluetoothEMP_1ab12436c821fecc2050cc3c37925229b2)`(QString macAddr)` | Initiates connection to the robot to reset it when it's connected.
`{slot} public void `[`shutdownLater`](#classCellulo_1_1CelluloBluetoothEMP_1a72fe2ad6c136c80f7e685b5620a5d394)`(QString macAddr)` | Initiates connection to the robot to shut it down when it's connected.
`{slot} public void `[`clear`](#classCellulo_1_1CelluloBluetoothEMP_1a9dda86060b992a8104ad9f13e4030a1f)`()` | Clears both lists, drops all connections.

## Members

#### `{property} bool `[`continuous`](doc/doc-comm.md#classCellulo_1_1CelluloBluetoothEMP_1aa0ffa9fb0d5d25770529ddfb231e5ec4) 

Whether to shut down or reset the same robots over and over, default false.

Whether to blast same robots.

#### `{property} QStringList `[`macAddrToBlast`](doc/doc-comm.md#classCellulo_1_1CelluloBluetoothEMP_1a948d8212e52c2514a0329cfcbfabeff3) 

List of robots waiting to be shut down or reset.

List of mac addresses that are being blasted.

#### `{property} QStringList `[`macAddrBlasted`](doc/doc-comm.md#classCellulo_1_1CelluloBluetoothEMP_1a1af9f3d90c9cf47bd112d8a453d3a6da) 

List of robots already shut down or reset.

List of mac addresses that are confirmed to be blasted.

#### `{slot} public void `[`resetLater`](#classCellulo_1_1CelluloBluetoothEMP_1ab12436c821fecc2050cc3c37925229b2)`(QString macAddr)` 

Initiates connection to the robot to reset it when it's connected.

#### `{slot} public void `[`shutdownLater`](#classCellulo_1_1CelluloBluetoothEMP_1a72fe2ad6c136c80f7e685b5620a5d394)`(QString macAddr)` 

Initiates connection to the robot to shut it down when it's connected.

#### `{slot} public void `[`clear`](#classCellulo_1_1CelluloBluetoothEMP_1a9dda86060b992a8104ad9f13e4030a1f)`()` 

Clears both lists, drops all connections.

# class `Cellulo::CelluloBluetoothScanner` 

```
class Cellulo::CelluloBluetoothScanner
  : public QQuickItem
```  

Object that scans for [Cellulo](#namespaceCellulo) robots.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} bool `[`continuous`](doc/doc-comm.md#classCellulo_1_1CelluloBluetoothScanner_1a31ff7b1923a5fd0164407a10bde44667) | Whether to scan continuously, default false.
`{property} bool `[`scanning`](doc/doc-comm.md#classCellulo_1_1CelluloBluetoothScanner_1af415501e8197aff4cb8705b5743451f4) | Whether scanning now, read-only.
`{property} QStringList `[`foundRobots`](doc/doc-comm.md#classCellulo_1_1CelluloBluetoothScanner_1ac93b05ef41326660bd48f6eca8a2ffb2) | List of found robots, read-only.
`{signal} public void `[`robotDiscovered`](#classCellulo_1_1CelluloBluetoothScanner_1a3107786d8400a26b0cf8f5ef970f3ca4)`(QString const & macAddr)` | Emitted when a new [Cellulo](#namespaceCellulo) robot is discovered.
`{signal} public void `[`finished`](#classCellulo_1_1CelluloBluetoothScanner_1a35d79f8e7315ad2fc807bbb482e7ee1b)`()` | Emitted when scanning finishes.
`{slot} public void `[`start`](#classCellulo_1_1CelluloBluetoothScanner_1aa1d2d32cfc92e514c0e901556b81fafc)`()` | Starts scanning.
`{slot} public void `[`stop`](#classCellulo_1_1CelluloBluetoothScanner_1a929b9cbdd80e6408606a6aa89072475e)`()` | Stops scanning.
`{slot} public void `[`clear`](#classCellulo_1_1CelluloBluetoothScanner_1ad289a3fbcb416c37d7c6bd36ec14d2f4)`()` | Clears the list of found robots.

## Members

#### `{property} bool `[`continuous`](doc/doc-comm.md#classCellulo_1_1CelluloBluetoothScanner_1a31ff7b1923a5fd0164407a10bde44667) 

Whether to scan continuously, default false.

Whether to continuously scan.

#### `{property} bool `[`scanning`](doc/doc-comm.md#classCellulo_1_1CelluloBluetoothScanner_1af415501e8197aff4cb8705b5743451f4) 

Whether scanning now, read-only.

#### `{property} QStringList `[`foundRobots`](doc/doc-comm.md#classCellulo_1_1CelluloBluetoothScanner_1ac93b05ef41326660bd48f6eca8a2ffb2) 

List of found robots, read-only.

List of robot MAC addresses that are found.

#### `{signal} public void `[`robotDiscovered`](#classCellulo_1_1CelluloBluetoothScanner_1a3107786d8400a26b0cf8f5ef970f3ca4)`(QString const & macAddr)` 

Emitted when a new [Cellulo](#namespaceCellulo) robot is discovered.

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

[Cellulo](#namespaceCellulo) communication utilities.

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

