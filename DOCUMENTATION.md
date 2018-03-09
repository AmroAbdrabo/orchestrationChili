qml-cellulo Documentation
=========================

Here you will find the complete documentation of all QML objects offered by `qml-cellulo`, organized into categories.

#### CelluloRobot [extends CelluloBluetooth]




Communication
-------------

#### CelluloBluetoothEnums [Singleton]

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

#### CelluloBluetooth [extends CelluloZoneClient]

Object that communicates with a Cellulo robot over Bluetooth. Inherits from `CelluloZoneClient` and therefore can be used as one.

**Properties:**

>  - **localAdapterMacAddr** : `string` - Local adapter's MAC address chosen to connect to the robot, empty string if using default adapter; only works on Linux and if the plugin is built with BlueZ
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

#### CelluloRobotPoolClient [extends CelluloLocalRelayClient]

Object that uses the robots connected to a `cellulorobotpoold`. Inherits from `CelluloLocalRelayClient`, which in turn inherits from `CelluloRelayClient`, which means that their properties, signals and slots can be used. The most useful among these is the `robots` property that exposes the list of currently available robots in this pool.

**Properties:**

>  - **createRobot** : `function` - Must be set to a user-defined function that takes the MAC address (string) of an already connected robot and returns a CelluloBluetooth object or CelluloBluetooth-derived object

#### CelluloBluetoothEMP

Object that shuts down or resets multiple robots simultaneously.

**Properties:**

>  - **continuous** :      `bool` - Whether to shut down or reset the same robots over and over, default false
>  - **macAddrToBlast** :  `readonly list<string>` - List of robots waiting to be shut down or reset
>  - **macAddrBlasted** :  `readonly list<string>` - List of robots already shut down or reset

**Slots**:

>  - **void resetLater(string macAddr)** : Starts a connection to the given robot and schedules a reset
>  - **void shutdownLater(string macAddr)** : Starts a connection to the given robot and schedules a shutdown
>  - **void clear()**: Clears both lists (macAddrToBlast and macAddrBlasted) and drops all connections

Communication - Relays
----------------------

#### CelluloRelayServer [Abstract]

Object that relays packets between a `CelluloRelayClient` and physical robots. The robots that are connected to this object (i.e having their relay server set as this object) have all their events routed to the `CelluloRelayClient` that is connected to this server. Listens for incoming connections from a client upon creation.

**Signals:**

>  - **clientConnected()** : Emitted when a connection from a `CelluloBluetoothRelayClient` is established
>  - **clientDisconnected()** : Emitted when the connection from the `CelluloBluetoothRelayClient` is closed
>  - **robotAdded(string macAddr)** : Emitted when a new robot is added to the server
>  - **robotRemoved(string macAddr)** : Emitted when a robot is removed from the server

**Slots:**

>  - **void setListening(bool enabled)** : Enables/disables listening for incoming connections from the client, enabled by default
>  - **bool isListening()** : Gets whether currently listening for incoming connections from the client
>  - **void addRobot(CelluloBluetooth robot)** : All event packets that arrive from the given robot from now on will be sent through the server instead of being emitted
>  - **void removeRobot(CelluloBluetooth robot)** : Removes the robot from the control of this server
>  - **void disconnectClient()** : Closes the connection to the client

#### CelluloLocalRelayServer [extends CelluloRelayServer]

Relay server that operates over UNIX domain sockets, i.e super-fast, local channels. Accepts connections from a `CelluloLocalRelayClient`.

**Properties:**

>  - **address** : `string` - Address to listen to, i.e name of the domain socket; default is "cellulo_relay"

#### CelluloTcpRelayServer [extends CelluloRelayServer]

Relay server that operates over TCP sockets, i.e fast, networked channels. Accepts connections from a `CelluloTcpRelayClient`.

**Properties:**

>  - **address** : `string` - Address to listen to, i.e address of the TCP socket; default is "localhost"
>  - **port** : `int` - Port to listen on, between 0-65535; default is 2556

#### CelluloRelayClient [Abstract]

Object that relays packets between a `CelluloRelayServer` and virtual robot objects. The robots that are connected to this object (i.e having their relay client set as this object) have all their commands routed to the `CelluloRelayServer` that is connected to this client, effectively making the `CelluloBluetooth`s under control of this client to become virtual robots that represent the physical robots connected to the server side.

**Properties:**

>  - **connected** : `readonly bool` - Whether currently connected to the server
>  - **autoConnect** : `bool` - Whether to try to reconnect when the connection drops or in the beginning, default is true
>  - **robots** : `readonly list<CelluloBluetooth>` - List of virtual robots currently under control of this client

**Signals:**

>  - **connected()** : Emitted when the connection to the `CelluloRelayServer` is established
>  - **disconnected()** : Emitted when the connection to the `CelluloRelayServer` is closed
>  - **unknownRobotAtServer(string macAddr)** : Emitted when the server has a robot already connected that is not in the robots list covered by this client, so that a virtual counterpart robot can be created and added to the client in order to establish a connection to this unknown robot at the server side

**Slots:**

>  - **void connectToServer()** : Initiates a connection to the `CelluloRelayServer`
>  - **void disconnectFromServer()** : Disconnects from the `CelluloRelayServer`
>  - **void addRobot(CelluloBluetooth robot, bool select = false)** : All command packets coming from the given robot from now on will be sent through this client instead of a direct Bluetooth connection to a physical robot. Essentially makes the given `CelluloBluetooth` a virtual robot. If `select` is true, will select the newly added robot as the current robot, raising all subsequent events on that robot. Pass true if robot is added as a result of an `unknownRobotAtServer()` signal.
>  - **void removeRobot(CelluloBluetooth robot)** : Removes the robot from the control of this client

#### CelluloLocalRelayClient [extends CelluloRelayClient]

Relay client that operates over UNIX domain sockets, i.e super-fast, local channels.

**Properties:**

>  - **serverAddress** : `string` - Address to connect to, i.e name of the domain socket; default is "cellulo_relay"

#### CelluloTcpRelayClient [extends CelluloRelayClient]

Relay client that operates over TCP sockets, i.e fast, networked channels.

**Properties:**

>  - **serverAddress** : `string` - Address to connect to, i.e address of the TCP socket; default is "localhost"
>  - **port** : `int` - Port to connect to, between 0-65535; default is 2556

Utilities
---------

#### CelluloCommUtil [Singleton]

Object that provides communication utilities.

**Slots:**

>  - **bool testRobotPoolDaemon()** : Returns whether `cellulorobotpoold` is installed
>  - **bool startRobotPoolDaemon()** : Attempts to start `cellulorobotpoold`, returns whether successful
>  - **bool stopRobotPoolDaemon()** : Attempts to stop the already running `cellulorobotpoold`, returns whether successful

#### CelluloSystemUtil [Singleton]

Object that provides system utilities.

**Slots:**

>  - **int exec(string command, list&lt;string&gt; arguments)** : Executes a system command with the given arguments and returns the exit code

#### TranslationTool

Object that provides a language translation for the entire app. To use, create one `TranslationTool` named e.g `tr`, and concatenate every user-readable string in the app with `tr.estr`. For example, a text property in another object would look like `text: tr.estr + "Text that would normally be here."`

**Properties:**

>  - **languageList** : `map<string,string>` - List of languages (e.g `"en"`) versus their translation resource files loaded into the app
>  - **estr** : `readonly string` - An empty string to be concatenated to all user-visible strings in the app to be translated if dynamic modification of the language during runtime is desired

**Slots:**

>  - **void selectLanguage(string language)** : A language given in **languageList** or `"default"` to unload the translator

#### AssociativeArray

Associative array data structure.

**Properties:**

>  - **defaultValue** : `var` - Default value to get if a key doesn't exist

**Slots:**

>  - **AssociativeArray copy()** : Returns a shallow copy of the array, internal array is shared so this slot is cheap. Can be used to get a copy to be modified set back to an AssociativeArray property to trigger its onChanged event.
>  - **void clear()** : Removes all key-value pairs from the array
>  - **var get(string key)** : Gets the value associated with a key
>  - **void set(string key, var value)** Sets the value associated with the key

#### CelluloMathUtil [Singleton]

Mathematical utilities.

**Slots:**

>  - **real pointToSegmentDist(vector2d p, vector2d seg1, vector2d seg2)** : Returns the distance of the given point to the line segment whose ends are given
>  - **real pointToLineDistSigned(vector2d p, vector2d lp1, vector2d lp2)** : Returns the signed distance of the given point to the line segment whose ends are given (negative if below the segment, positive if above)
>  - **bool pointInPoly(vector2d p, list<vector2d> v)** : Returns whether the given point is in the polygon with given vertices
>  - **real pointToPolyBorderDist(vector2d p, list<vector2d> v)** : Returns the distance of the point to the border of the polygon whose vertices are given
>  - **bool hRayCrossesLineSeg(vector2d r, vector2d seg1, vector2d seg2)** : Returns whether a horizontal ray originating from **r** and continuing towards +infinity crosses the line segment whose ends are given
>  - **void c_srand(int seed)** : Call to c's `srand()`. This method is called with `time(NULL)` at `CelluloMathUtil` creation time
>  - **int c_rand(int max)** : Call to c's `rand()`, returns a random integer in [0, **max** - 1]
>  - **bool collinear(vector2d a, vector2d b, vector2d c)** : Returns whether given points are collinear (enough)
>  - **list shuffle(list list)** : Calls `std::random_shuffle` with the given list. Returns the shuffled list.
>  - **vector2d rotateVector(vector2d vector, real angleRad)** : Returns the given vector rotated by the given angle
>  - **real degToRad(real deg)** : Converts degrees to radians
>  - **real radToDeg(real rad)** : Converts radians to degrees
>  - **real sigmoid(real L, real beta, real r_0, real r)** : Calculates L/(1 + exp(beta*(r - r_0)))
>  - **real clamp(real val, real min, real max)** : Forces val in [min, max]

#### CelluloSVGUtil [Singleton]

Utilities for converting SVG files into CelluloZone description files.

**Slots:**

>  - **string dumpAllPathsToJSON(string inSVGFile, string outJSONFile, string type, string name = "SVG_DUMP_ZONE", real dpi = 90.0, bool optimized = true)** : Loads an SVG and converts all paths/shapes to CelluloZone types and dumps these zones into a JSON file. **type** is DEPRECATED. **name** is the base name for the dumped zones, consecutive zones are suffixed with "_1", "_2" etc. **dpi** is the DPI setting to be used when converting to mm, which is the CelluloZone unit for all measurements; by default this is 90.0, which is the Inkscape export default. If **optimized** is disabled (enabled by default), all zones are converted into `POLBEZIERCLOSESTT`, if not, an EXPERIMENTAL module tries to interpret individual types of shapes like circle and rectangle. Returns a status string that can be shown to the user.

#### MacAddrSelector

A GUI for selecting a MAC address from a drop-down box and connecting to a robot.

**Properties:**

>  - **addresses** : `list<string>` - List of MAC addresses to display in the drop-down box
>  - **selectedAddress** : `readonly string` - Currently selected address
>  - **selectedLocalAdapterAddress** : `readonly string` - Currently selected local adapter address
>  - **connectionStatus** : `CelluloBluetooth.ConnectionStatus` - Connection status to display

**Signals:**

>  - **connectRequested()** : Emitted when the user presses the connect button
>  - **disconnectRequested()** : Emitted when the user presses the disconnect button

**Slots:**

>  - **selectAddress(string address)** : Selects the given address if it exists in the list of addresses
>  - **selectLocalAdapterAddress(string address)** : Selects the given local adapter address if it exists on this machine

#### ToastManager

Creates on-screen banner texts, like Android's `Toast`s. Ensures that multiple toasts show correctly together.

**Slots:**

>  - **void show(string text, real duration = 3000)** : Shows the given message for the given duration (ms)

Zones
-----

#### CelluloZone [Abstract]

Abstract description of a "zone" on a 2D plane. These zones could be closed curves, polygons, open curves, even points.

They are meant interact with `CelluloZoneClient`s (such as a robot, or a virtual robot on a screen), calculating a real value with respect to each client (for example, the distance to the client in the case of a point zone). With the help of `CelluloZoneEngine`, a zone emits each client's `zoneValueChanged()` signal upon the changing of the value with respect to that client.

This object cannot be used on its own but all usable Cellulo zones inherit from this object and possess the properties, signals and slots described here unless stated otherwise.

**Properties:**

>  - **active** : `bool` - Whether this zone is active, i.e generates `zoneValueChanged` signals on `CelluloZoneClient`s, default true
>  - **name** : `string` - Name of this zone, must be unique, default is `"anonymousZone"`
>  - **type** : `readonly CelluloZoneTypes.ZoneType` - Type of this zone

**Slots:**

>  - **CelluloZonePaintedItem createPaintedItem(item parent, color color, real physicalPlaygroundWidth, real physicalPlaygroundHeight)** : Creates a visual representation of this zone with the given parent (will be the canvas to draw this representation) and the given color. Physical playground width and height (in mm) must also be given to map the physical zone coordinates to the on-screen canvas item.
>  - **void setPaintedItem(CelluloZonePaintedItem newPaintedItem)** : Assigns an already existing CelluloZonePaintedItem to be the visual representation of this zone
>  - **CelluloZonePaintedItem getPaintedItem()** : Gets the visual representation of this zone so that its properties can be changed.
>  - **bool isMouseInside(vector2d mousePosition, real canvasWidth, real canvasHeight, real physicalWidth, real physicalHeight)** : Returns whether the given mouse position (in pixels within the canvas) is in the visual zone representation or not. Needs the canvas size (in pixels) and the physical playground size (in mm).

#### CelluloZonePaintedItem

Visual representation of a `CelluloZone`; can be used to draw `CelluloZone`s in e.g `Rectangle`s. Visually covers its parent (from `[0, 0]` to `[parent.width, parent.height]`), using it as a canvas and drawing the zone at the appropriate place.

**Properties:**

>  - **color** : `color` - The color of the drawn zone
>  - **associatedZone** : `CelluloZone` - Associated zone
>  - **physicalPlaygroundWidth** : `real` - Physical playground width that the canvas represents (in mm)
>  - **physicalPlaygroundHeight** : `real` - Physical playground height that the canvas represents (in mm)

#### CelluloZoneClient [Abstract]

Abstract object that interacts with `CelluloZone`s through a `CelluloZoneEngine`. Inherit from this object (i.e if being used from QML, create the `YourObject.qml` file with `CelluloZoneClient` as the top object) to have your custom object interact with `CelluloZone`s. For example, `CelluloBluetooth` already inherits from this object.

**Signals:**

>  - **zoneValueChanged(CelluloZone zone, real value)** : Emitted when a zone's value changes (passed as the **zone** attribute and the **value** attribute) with respect to this client
>  - **poseChanged(real x, real y, real theta)** : User is responsible for emitting this signal when this client's pose (in mm, mm, deg) changes

#### CelluloZoneEngine

Object that ensures `CelluloZone` and `CelluloZoneClient` interaction. All `CelluloZoneClient`s in this engine have their `zoneValueChanged()` signals emitted when the value of a `CelluloZone` (within this engine) with respect to the client changes.

`CelluloZone`s instantiated as children of a `CelluloZoneEngine` will be automatically added to it. `CelluloZoneClient`s must be manually added.

**Properties:**

>  - **active** : `bool` - Whether the zones in this engine are active, default true

**Slots:**

>  - **list<string> getAllZoneNames()** : Returns the list of names of all zones in this engine
>  - **CelluloZone getZoneByName(string name)** : Returns the zone with the given name or null if not found
>  - **list<CelluloZone> getZonesList()** : Returns the list of all zones in this engine
>  - **void addNewZones(list&lt;CelluloZone&gt; newZones)** : Adds the given list of zones to the engine
>  - **void addNewZone(CelluloZone newZone)** : Adds the given zone to the engine
>  - **void clearZones()** : Deletes all the zones in this engine
>  - **void addNewClient(CelluloZoneClient newClient)** : Adds the given client to the engine

#### CelluloZoneJsonHandler [Singleton]

Utilities to load/save `CelluloZone`s to to/from files in JSON format.

**Slots:**

>  - **void saveZones(list&lt;CelluloZone&gt; zones, string path)** : Saves all given zones to the given file
>  - **list&lt;CelluloZone&gt; loadZonesQML(string path)** : Loads zones from the given file

#### CelluloZoneTypes [Singleton]

`CelluloZone` type enum and utilities.

**Enums:**

`ZoneType` - All instantiatable zone types
> - `ANGLEDIFFERENCE` - Type for `CelluloZoneAngleDifference`
> - `ANGLEINTERVALINNER` - Type for `CelluloZoneAngleIntervalInner`
> - `ANGLEINTERVALBORDER` - Type for `CelluloZoneAngleIntervalBorder`
> - `ANGLEINTERVALDISTANCE` - Type for `CelluloZoneAngleIntervalDistance`
> - `CIRCLEINNER` - Type for `CelluloZoneCircleInner`
> - `CIRCLEBORDER` - Type for `CelluloZoneCircleBorder`
> - `CIRCLEDISTANCE` - Type for `CelluloZoneCircleDistance`
> - `RECTANGLEINNER` - Type for `CelluloZoneRectangleInner`
> - `RECTANGLEBORDER` - Type for `CelluloZoneRectangleBorder`
> - `RECTANGLEDISTANCE` - Type for `CelluloZoneRectangleDistance`
> - `LINESEGMENTDISTANCE` - Type for `CelluloZoneLineSegmentDistance`
> - `LINEDISTANCESIGNED` - Type for `CelluloZoneLineDistanceSigned`
> - `LINEBORDER` - Type for `CelluloZoneLineBorder`
> - `POINTDISTANCE` - Type for `CelluloZonePointDistance`
> - `RPOLYGONINNER` - Type for `CelluloZoneRegularPolygonDistance`
> - `RPOLYGONBORDER` - Type for `CelluloZoneRegularPolygonBorder`
> - `RPOLYGONDISTANCE` - Type for `CelluloZoneRegularPolygonDistance`
> - `IRPOLYGONINNER` - Type for `CelluloZoneIrregularPolygonInner`
> - `IRPOLYGONBORDER` - Type for `CelluloZoneIrregularPolygonBorder`
> - `IRPOLYGONDISTANCE` - Type for `CelluloZoneIrregularPolygonDistance`
> - `POLYBEZIERCLOSESTT` - Type for `CelluloZonePolyBezierClosestT`
> - `POLYBEZIERXT` - Type for `CelluloZonePolyBezierXT`
> - `POLYBEZIERYT` - Type for `CelluloZonePolyBezierYT`
> - `POLYBEZIERDISTANCE` - Type for `CelluloZonePolyBezierDistance`
> - `POLYBEZIERBORDER` - Type for `CelluloZonePolyBezierBorder`
> - `POLYBEZIERINNER` - Type for `CelluloZonePolyBezierInner`

**Slots:**

>  - **ZoneType typeFromString(string typeName)** : Gets the enum zone type from its string representation
>  - **CelluloZone newZoneFromType(ZoneType type)** : Creates a new CelluloZone with the given type

#### CelluloZoneAngleDifference

Calculates the signed difference of the client orientation angles to the zone's angle, value is in `]-180, 180]`.

**Properties:**

>  - **angle** : `real` - Zone's angle (deg)

#### CelluloZoneAngleIntervalInner [extends CelluloZone]

Calculates whether the client's orientation is within the zone's angle interval, value is `0.0` or `1.0`. The zone is described by the limits **fromAngle** to **toAngle**, in that order; e.g if `330` and `30` are provided, the zone interval includes `0` degrees and not `180` degrees.

**Properties:**

>  - **fromAngle** : `real` - Beginning of this zone (deg)
>  - **toAngle** : `real` -  End of this zone (deg)

#### CelluloZoneAngleIntervalBorder [extends CelluloZone]

Calculates whether the client's orientation is within **borderThickness** of the zone's angle interval limits, value is `0.0` or `1.0`

**Properties:**

>  - **fromAngle** : `real` - Beginning of this zone (deg)
>  - **toAngle** : `real` -  End of this zone (deg)
>  - **borderThickness** : `real` - Thickness of the sensitivity (deg)

#### CelluloZoneAngleIntervalDistance [extends CelluloZone]

Calculates the client's angular distance to the zone's angle interval. The zone is described by the limits **fromAngle** to **toAngle**, in that order; e.g if `330` and `30` are provided, the zone interval includes `0` degrees and not `180` degrees.

**Properties:**

>  - **fromAngle** : `real` - Beginning of this zone (deg)
>  - **toAngle** : `real` -  End of this zone (deg)

#### CelluloZoneCircleInner [extends CelluloZone]

Calculates whether the client's position is within the circle, value is `0.0` or `1.0`.

**Properties:**

>  - **x** : `real` - X coordinate of this zone (mm)
>  - **y** : `real` - Y coordinate of this zone (mm)
>  - **r** : `real` - Radius of this zone (mm)

#### CelluloZoneCircleBorder [extends CelluloZone]

Calculates whether the client's position is within **borderThickness** of the zone's border, value is `0.0` or `1.0`.

**Properties:**

>  - **x** : `real` - X coordinate of this zone (mm)
>  - **y** : `real` - Y coordinate of this zone (mm)
>  - **r** : `real` - Radius of this zone (mm)
>  - **borderThickness** : `real` - Thickness of the sensitivity (mm)

#### CelluloZoneCircleDistance [extends CelluloZone]

Calculates the client's distance to the zone's border.

**Properties:**

>  - **x** : `real` - X coordinate of this zone (mm)
>  - **y** : `real` - Y coordinate of this zone (mm)
>  - **r** : `real` - Radius of this zone (mm)

#### CelluloZoneRectangleInner [extends CelluloZone]

Calculates whether the client's position is within the rectangle, value is `0.0` or `1.0`.

**Properties:**

>  - **x** : `real` - X coordinate of the top left corner (mm)
>  - **y** : `real` - Y coordinate of the top left corner (mm)
>  - **width** : `real` - Width of the rectangle (mm)
>  - **height** : `real` - Height of the rectangle (mm)

#### CelluloZoneRectangleBorder [extends CelluloZone]

Calculates whether the client's position is within **borderThickness** of the zone's border, value is `0.0` or `1.0`.

**Properties:**

>  - **x** : `real` - X coordinate of the top left corner (mm)
>  - **y** : `real` - Y coordinate of the top left corner (mm)
>  - **width** : `real` - Width of the rectangle (mm)
>  - **height** : `real` - Height of the rectangle (mm)
>  - **borderThickness** : `real` - Thickness of the sensitivity (mm)

#### CelluloZoneRectangleDistance [extends CelluloZone]

Calculates the client's distance to the zone's border.

**Properties:**

>  - **x** : `real` - X coordinate of the top left corner (mm)
>  - **y** : `real` - Y coordinate of the top left corner (mm)
>  - **width** : `real` - Width of the rectangle (mm)
>  - **height** : `real` - Height of the rectangle (mm)

#### CelluloZoneLineSegmentDistance [extends CelluloZone]

Calculates the client's distance to the zone that is a line segment.

**Properties:**

>  - **x1** : `real` - X coordinate of the first line segment end (mm)
>  - **y1** : `real` - Y coordinate of the first line segment end (mm)
>  - **x2** : `real` - X coordinate of the second line segment end (mm)
>  - **y2** : `real` - Y coordinate of the second line segment end (mm)

#### CelluloZoneLineDistanceSigned [extends CelluloZone]

Calculates the client's (signed) distance to the zone that is an infinite line.

**Properties:**

>  - **x1** : `real` - X coordinate of the first point that the line passes through (mm)
>  - **y1** : `real` - Y coordinate of the first point that the line passes through (mm)
>  - **x2** : `real` - X coordinate of the second point that the line passes through (mm)
>  - **y2** : `real` - Y coordinate of the second point that the line passes through (mm)

#### CelluloZoneLineBorder [extends CelluloZone]

Calculates whether the client's position is within **borderThickness** of the zone's border, value is `0.0` or `1.0`.

**Properties:**

>  - **x1** : `real` - X coordinate of the first point that the line passes through (mm)
>  - **y1** : `real` - Y coordinate of the first point that the line passes through (mm)
>  - **x2** : `real` - X coordinate of the second point that the line passes through (mm)
>  - **y2** : `real` - Y coordinate of the second point that the line passes through (mm)
>  - **borderThickness** : `real` - Thickness of the sensitivity (mm)

#### CelluloZonePointDistance [extends CelluloZone]

Calculates the client's distance to the zone.

**Properties:**

>  - **x** : `real` - X coordinate of the point (mm)
>  - **y** : `real` - Y coordinate of the point (mm)

#### CelluloZoneIrregularPolygonInner [extends CelluloZone]

Calculates whether the client's position is within the irregular polygon, value is `0.0` or `1.0`.

**Properties:**

>  - **vertices** : `list<vector2d>` - List of vertices, polygon has an edge between every `i`th and `i+1`th vertex

#### CelluloZoneIrregularPolygonBorder [extends CelluloZone]

Calculates whether the client's position is within **borderThickness** of the zone's border, value is `0.0` or `1.0`.

**Properties:**

>  - **vertices** : `list<vector2d>` - List of vertices, polygon has an edge between every `i`th and `i+1`th vertex
>  - **borderThickness** : `real` - Thickness of the sensitivity (mm)

#### CelluloZoneIrregularPolygonDistance [extends CelluloZone]

Calculates the client's distance to the zone's border.

**Properties:**

>  - **vertices** : `list<vector2d>` - List of vertices, polygon has an edge between every `i`th and `i+1`th vertex

#### CelluloZoneRegularPolygonInner [extends CelluloZone]

Calculates whether the client's position is within the regular polygon, value is `0.0` or `1.0`.

**Properties:**

>  - **numEdges** : `int` - Number of edges
>  - **x** : `real` - X coordinate of the center (mm)
>  - **y** : `real` - Y coordinate of the center (mm)
>  - **r** : `real` - Radius of the enclosing circle (mm)
>  - **rotAngle** : `real` - Extra rotation from the initial orientation (deg)

#### CelluloZoneRegularPolygonBorder [extends CelluloZone]

Calculates whether the client's position is within **borderThickness** of the zone's border, value is `0.0` or `1.0`.

**Properties:**

>  - **numEdges** : `int` - Number of edges
>  - **x** : `real` - X coordinate of the center (mm)
>  - **y** : `real` - Y coordinate of the center (mm)
>  - **r** : `real` - Radius of the enclosing circle (mm)
>  - **rotAngle** : `real` - Extra rotation from the initial orientation (deg)
>  - **borderThickness** : `real` - Thickness of the sensitivity (mm)

#### CelluloZoneRegularPolygonDistance [extends CelluloZone]

Calculates the client's distance to the zone's border.

**Properties:**

>  - **numEdges** : `int` - Number of edges
>  - **x** : `real` - X coordinate of the center (mm)
>  - **y** : `real` - Y coordinate of the center (mm)
>  - **r** : `real` - Radius of the enclosing circle (mm)
>  - **rotAngle** : `real` - Extra rotation from the initial orientation (deg)

#### CelluloZonePolyBezierClosestT [extends CelluloZone]

Calculates the parameter `t` of the composite Bézier curve whose corresponding point is closest to the client. `t` will be in `[0, number of segments]` where every interval of size `1` corresponds to the parameter `t` on that particular segment within the curve.

**Properties:**

>  - **controlPoints** : `list<vector2d>` - List of consecutive control points, must contain `3N + 1` points; `N` is the number of segments

**Slots:**

>  - **void sendPathToRobot(CelluloBluetooth robot)** : Sends the path to the robot for tracking
>  - **vector2d getPoint(real t)** : Calculates the point on the curve corresponding to the parameter **t** that is in `[0, number of segments]`
>  - **vector2d getTangent(real t)** : Calculates the tangent to the point on the curve corresponding to the parameter **t** that is in `[0, number of segments]`
>  - **vector2d getNormal(real t)** : Calculates the normal to the point on the curve corresponding to the parameter **t** that is in `[0, number of segments]`

#### CelluloZonePolyBezierXT [extends CelluloZone]

Calculates the parameter `t` of the composite Bézier curve whose corresponding point has the same x coordinate as the client. `t` will be in `[0, number of segments]` where every interval of size `1` corresponds to the parameter `t` on that particular segment within the curve. Assumes that the curve is 1-to-1 along the x axis, i.e it is of the form `y = f(t)`.

**Properties:**

>  - **controlPoints** : `list<vector2d>` - List of consecutive control points, must contain `3N + 1` points; `N` is the number of segments

**Slots:**

>  - **void sendPathToRobot(CelluloBluetooth robot)** : Sends the path to the robot for tracking
>  - **vector2d getPoint(real t)** : Calculates the point on the curve corresponding to the parameter **t** that is in `[0, number of segments]`
>  - **vector2d getTangent(real t)** : Calculates the tangent to the point on the curve corresponding to the parameter **t** that is in `[0, number of segments]`
>  - **vector2d getNormal(real t)** : Calculates the normal to the point on the curve corresponding to the parameter **t** that is in `[0, number of segments]`

#### CelluloZonePolyBezierYT [extends CelluloZone]

Calculates the parameter `t` of the composite Bézier curve whose corresponding point has the same y coordinate as the client. `t` will be in `[0, number of segments]` where every interval of size `1` corresponds to the parameter `t` on that particular segment within the curve. Assumes that the curve is 1-to-1 along the y axis, i.e it is of the form `x = f(t)`.

**Properties:**

>  - **controlPoints** : `list<vector2d>` - List of consecutive control points, must contain `3N + 1` points; `N` is the number of segments

**Slots:**

>  - **void sendPathToRobot(CelluloBluetooth robot)** : Sends the path to the robot for tracking
>  - **vector2d getPoint(real t)** : Calculates the point on the curve corresponding to the parameter **t** that is in `[0, number of segments]`
>  - **vector2d getTangent(real t)** : Calculates the tangent to the point on the curve corresponding to the parameter **t** that is in `[0, number of segments]`
>  - **vector2d getNormal(real t)** : Calculates the normal to the point on the curve corresponding to the parameter **t** that is in `[0, number of segments]`

#### CelluloZonePolyBezierDistance [extends CelluloZone]

Calculates the distance of the client to the composite Bézier curve.

**Properties:**

>  - **controlPoints** : `list<vector2d>` - List of consecutive control points, must contain `3N + 1` points; `N` is the number of segments

#### CelluloZonePolyBezierBorder [extends CelluloZone]

Calculates whether the client's position is within **borderThickness** of the zone's border, value is `0.0` or `1.0`.

**Properties:**

>  - **controlPoints** : `list<vector2d>` - List of consecutive control points, must contain `3N + 1` points; `N` is the number of segments
>  - **borderThickness** : `real` - Thickness of the sensitivity (mm)

#### CelluloZonePolyBezierInner [extends CelluloZone]

Calculates whether the client is within the composite Bézier curve, value is `0.0` or `1.0`. The first and last control points of the curve are assumed to be connected with a line segment in order to ensure the curve is closed, if the curve is not already closed.

**Properties:**

>  - **controlPoints** : `list<vector2d>` - List of consecutive control points, must contain `3N + 1` points; `N` is the number of segments
