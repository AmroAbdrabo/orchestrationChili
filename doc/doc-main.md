# group `main` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[`Cellulo::CelluloBluetoothEnums`](doc/doc-main.md#classCellulo_1_1CelluloBluetoothEnums) | Wrapper containing all the enums of [CelluloBluetooth](doc/doc-comm.md#classCellulo_1_1CelluloBluetooth).

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
`enum `[`ConnectionStatus`](doc/doc-main.md#classCellulo_1_1CelluloBluetoothEnums_1a9bdbb91140cd33c3daa779af49c7ed97) | Bluetooth connection status.
`enum `[`BatteryState`](doc/doc-main.md#classCellulo_1_1CelluloBluetoothEnums_1a895a56801308039dd778b0a0fb6809b8) | Battery state of the robot.
`enum `[`LEDResponseMode`](doc/doc-main.md#classCellulo_1_1CelluloBluetoothEnums_1a57ece08557723b6428a74ba3b1265b29) | LED response mode of the robot.
`enum `[`LocomotionInteractivityMode`](doc/doc-main.md#classCellulo_1_1CelluloBluetoothEnums_1ae5126bceecb95ffc8846e8c72f379812) | Locomotion interactivity mode of the robot.
`enum `[`VisualEffect`](doc/doc-main.md#classCellulo_1_1CelluloBluetoothEnums_1a810aca61e84c1e31fb751335cd776361) | List of possible visual effects.
`enum `[`Gesture`](doc/doc-main.md#classCellulo_1_1CelluloBluetoothEnums_1aac0e86c82f086708674759431d6ff0fb) | List of possible getures.

## Members

#### `enum `[`ConnectionStatus`](doc/doc-main.md#classCellulo_1_1CelluloBluetoothEnums_1a9bdbb91140cd33c3daa779af49c7ed97) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
ConnectionStatusDisconnected            | Idle and not connected
ConnectionStatusConnecting            | Actively trying to connect
ConnectionStatusConnected            | Connected
ConnectionStatusNumElements            | 

Bluetooth connection status.

#### `enum `[`BatteryState`](doc/doc-main.md#classCellulo_1_1CelluloBluetoothEnums_1a895a56801308039dd778b0a0fb6809b8) 

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

#### `enum `[`LEDResponseMode`](doc/doc-main.md#classCellulo_1_1CelluloBluetoothEnums_1a57ece08557723b6428a74ba3b1265b29) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
LEDResponseModeResponsiveIndividual            | LEDs respond to touches by slightly increasing brightness
LEDResponseModeAbsolute            | LEDs don't respond to touches
LEDResponseModeResponsiveHold            | LEDs respond to hold by all changing color
LEDResponseModeNumElements            | 

LED response mode of the robot.

#### `enum `[`LocomotionInteractivityMode`](doc/doc-main.md#classCellulo_1_1CelluloBluetoothEnums_1ae5126bceecb95ffc8846e8c72f379812) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
LocomotionInteractivityModeNormal            | Robot moves normally
LocomotionInteractivityModeRequiresHold            | Robot requires Hold gesture
LocomotionInteractivityModeNumElements            | 

Locomotion interactivity mode of the robot.

#### `enum `[`VisualEffect`](doc/doc-main.md#classCellulo_1_1CelluloBluetoothEnums_1a810aca61e84c1e31fb751335cd776361) 

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

#### `enum `[`Gesture`](doc/doc-main.md#classCellulo_1_1CelluloBluetoothEnums_1aac0e86c82f086708674759431d6ff0fb) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
GestureNone            | No gesture
GestureHold            | Robot is held
GestureNumElements            | 

List of possible getures.

