

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
