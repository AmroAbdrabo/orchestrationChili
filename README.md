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

QML wrapper for enums used across the Cellulo objects.

**Enums:**

>  - **ConnectionStatus** - Robot connection status
> > - `ConnectionStatusDisconnected` - Idle and not connected
> > - `ConnectionStatusConnecting` - Actively trying to connect
> > - `ConnectionStatusConnected` - Connected

>  - **BatteryState** - Robot battery state
> > - `BatteryStateDischarging` - No charger present, battery draining
> > - `BatteryStateLow` - No charger present, battery low, will shut down
> > - `BatteryStateCharging` - Charger present, battery charging
> > - `BatteryStateCharged` - Charger present, battery full
> > - `BatteryStateShutdown` - Charger charging disabled, voltage too low or battery not present
> > - `BatteryStateError` - Thermal fault or charge timeout

>  - **LEDResponseMode** - Robot LED response mode to touch
> > - `LEDResponseModeResponsiveIndividual` - LEDs respond to touches by slightly increasing brightness
> > - `LEDResponseModeAbsolute` - LEDs don't respond to touches
> > - `LEDResponseModeResponsiveHold` - LEDs respond to Hold gesture by all changing color

>  - **LocomotionInteractivityMode** - Robot locomotion relation to touches
> > - `LocomotionInteractivityModeNormal` - Robot moves normally
> > - `LocomotionInteractivityModeRequiresHold` - Robot doesn't move unless Hold gesture is present

>  - **VisualEffect** - Robot LED effects
> > - `VisualEffectConstAll` - Set all LED colors (value unused)
> > - `VisualEffectConstSingle` - Set one LED color (value is LED index)
> > - `VisualEffectAlertAll` - Alert animation for all LEDs (value unused)
> > - `VisualEffectAlertSingle` - Alert animation for one LED (value is LED index)
> > - `VisualEffectProgress` - Static progress circularly (value 0-255 maps to 0-100%)
> > - `VisualEffectWaiting` - Circular waiting/processing animation (value unused)
> > - `VisualEffectDirection` - Point toward one direction (value 0-255 maps to 0-360 degrees)
> > - `VisualEffectBlink` - Alert forever (value*20 is LED on time in milliseconds)
> > - `VisualEffectBreathe` - Breathe animation (value unused)
> > - `VisualEffectPulse` - Slower breathe-like animation (value unused)

>  - **Gesture** - Special robot key touch states
> > - `GestureNone` - No gesture
> > - `GestureHold` - Robot is "held" (a general presence is detected on the keys)
