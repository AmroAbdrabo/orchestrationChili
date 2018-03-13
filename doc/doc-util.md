# group `util` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[`Cellulo::TranslationTool`](doc/doc-util.md#classCellulo_1_1TranslationTool) | Object that provides a language translation for the entire app.
`class `[`Cellulo::CelluloMathUtil`](doc/doc-util.md#classCellulo_1_1CelluloMathUtil) | Mathematical utilities used throughout Celullo activities.
`class `[`Cellulo::CelluloSVGUtil`](doc/doc-util.md#classCellulo_1_1CelluloSVGUtil) | Utilities for converting SVG files into [CelluloZone](doc/doc-zone.md#classCellulo_1_1CelluloZone) description files.
`class `[`Cellulo::CelluloSystemUtil`](doc/doc-util.md#classCellulo_1_1CelluloSystemUtil) | Object that provides system utilities.
`class `[`Cellulo::CelluloUIUtil`](doc/doc-util.md#classCellulo_1_1CelluloUIUtil) | User interface utilities used throughout Celullo activities.
`class `[`Cellulo::MacAddrSelector`](doc/doc-util.md#classCellulo_1_1MacAddrSelector) | MAC address selection GUI.
`class `[`Cellulo::Toast`](doc/doc-util.md#classCellulo_1_1Toast) | An Android-like timed message text in a box that selfdestroys when finished if desired.
`class `[`Cellulo::ToastManager`](doc/doc-util.md#classCellulo_1_1ToastManager) | Creates on-screen banner texts, like Android's `[Toast](doc/doc-util.md#classCellulo_1_1Toast)`s. Ensures that multiple toasts show correctly together.

# class `Cellulo::TranslationTool` 

```
class Cellulo::TranslationTool
  : public QObject
```  

Object that provides a language translation for the entire app.

To use, create one `[TranslationTool](#classCellulo_1_1TranslationTool)` named e.g `tr`, and concatenate every user-readable string in the app with `tr.estr`. For example, a text property in another object would look like `text: tr.estr + "Text that would
normally be here."`

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} QVariantMap `[`languageList`](doc/doc-util.md#classCellulo_1_1TranslationTool_1ae9be279823bda83156d8771a6ece9e00) | List of languages (e.g `"en"`) versus their translation resource files loaded into the app.
`{property} QString `[`estr`](doc/doc-util.md#classCellulo_1_1TranslationTool_1ad2205b8c75514bcb5fb7512809e11466) | An empty string (read-only) to be concatenated to all user-visible strings in the app to be translated if dynamic modification of the language during runtime is desired.
`{slot} public Q_INVOKABLE void `[`selectLanguage`](#classCellulo_1_1TranslationTool_1a1b48dd2accb7e5eb82c7b36548a23a44)`(const QString & language)` | Chooses language.

## Members

#### `{property} QVariantMap `[`languageList`](doc/doc-util.md#classCellulo_1_1TranslationTool_1ae9be279823bda83156d8771a6ece9e00) 

List of languages (e.g `"en"`) versus their translation resource files loaded into the app.

Language (QString) to translation file (QString) list.

#### `{property} QString `[`estr`](doc/doc-util.md#classCellulo_1_1TranslationTool_1ad2205b8c75514bcb5fb7512809e11466) 

An empty string (read-only) to be concatenated to all user-visible strings in the app to be translated if dynamic modification of the language during runtime is desired.

#### `{slot} public Q_INVOKABLE void `[`selectLanguage`](#classCellulo_1_1TranslationTool_1a1b48dd2accb7e5eb82c7b36548a23a44)`(const QString & language)` 

Chooses language.

#### Parameters
* `language` Language as provided to the translation list or "default" to uninstall translator

# class `Cellulo::CelluloMathUtil` 

```
class Cellulo::CelluloMathUtil
  : public QObject
```  

Mathematical utilities used throughout Celullo activities.

This class is **singleton**, you can call `ThisClass.anyFunction()` and use `ThisClass.anyProperty` directly.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public static Q_INVOKABLE qreal `[`pointToSegmentDist`](#classCellulo_1_1CelluloMathUtil_1aaaebc0a7dd54bc2e0b4bb47237530054)`(const QVector2D & p,const QVector2D & seg1,const QVector2D & seg2)` | Calculates the distance of a point to a line segment in 2D.
`public static Q_INVOKABLE qreal `[`pointToLineDistSigned`](#classCellulo_1_1CelluloMathUtil_1ae3dc27d0fc111c4a0128f933c0970033)`(const QVector2D & p,const QVector2D & lp1,const QVector2D & lp2)` | Calculates the signed distance of a point to a line in 2D.
`public static Q_INVOKABLE bool `[`pointInPoly`](#classCellulo_1_1CelluloMathUtil_1aefa1f8e82c7c4c54e95964b7d6d09de7)`(const QVector2D & p,const QList< QVector2D > & v)` | Calculates whether the given point is in the given polygon.
`public static Q_INVOKABLE qreal `[`pointToPolyBorderDist`](#classCellulo_1_1CelluloMathUtil_1ae1771e133a7a8b41efde0f6e22e030f7)`(const QVector2D & p,const QList< QVector2D > & v)` | Calculates the distance of the point to the polygon border.
`public static Q_INVOKABLE bool `[`hRayCrossesLineSeg`](#classCellulo_1_1CelluloMathUtil_1af13569931204ec6b3f1ae1b0a305e907)`(const QVector2D & r,const QVector2D & seg1,const QVector2D & seg2)` | Calculates whether a horizontal ray starting from r and continuing towards +infinity crosses the line segment.
`public static Q_INVOKABLE void `[`c_srand`](#classCellulo_1_1CelluloMathUtil_1a972aab4558a5493a68005ec5c1a49185)`(unsigned int seed)` | Initializes c's random number generator seed.
`public static Q_INVOKABLE int `[`c_rand`](#classCellulo_1_1CelluloMathUtil_1ab5ca178d6b922ecdc14e9f11cb258099)`(unsigned int max)` | Calls c's random number generator.
`public static Q_INVOKABLE bool `[`collinear`](#classCellulo_1_1CelluloMathUtil_1a0d2b1423fd9c17dbd4fd412827f56830)`(const QVector2D & a,const QVector2D & b,const QVector2D & c)` | Gets whether the given points are collinear enough.
`public static Q_INVOKABLE QVariantList `[`shuffle`](#classCellulo_1_1CelluloMathUtil_1a4c0226775e3f0a42b29282e704f4132b)`(const QVariantList & list)` | std::random_shuffles a list
`public static Q_INVOKABLE QVector2D `[`rotateVector`](#classCellulo_1_1CelluloMathUtil_1a3bb6db1423e9d3e4755f54ca73a27fb6)`(QVector2D const & vector,qreal angleRad)` | Returns the given vector rotated by the given angle.
`public static Q_INVOKABLE qreal `[`degToRad`](#classCellulo_1_1CelluloMathUtil_1afff0351c85b4147b57d01d10abf837c3)`(qreal deg)` | Converts degrees to radians.
`public static Q_INVOKABLE qreal `[`radToDeg`](#classCellulo_1_1CelluloMathUtil_1aebd81ebb37fb050b70bd9ed2f044d825)`(qreal rad)` | Converts radians to degrees.
`public static Q_INVOKABLE qreal `[`sigmoid`](#classCellulo_1_1CelluloMathUtil_1a3edaa9eb57c9a98fe58639fd92b83f6d)`(qreal L,qreal beta,qreal r_0,qreal r)` | Calculates a parametric sigmoid function value.
`public static Q_INVOKABLE qreal `[`clamp`](#classCellulo_1_1CelluloMathUtil_1a802dd180acb91fdea9d3b1e4b18469d6)`(qreal val,qreal min,qreal max)` | Clamps value in an interval.

## Members

#### `public static Q_INVOKABLE qreal `[`pointToSegmentDist`](#classCellulo_1_1CelluloMathUtil_1aaaebc0a7dd54bc2e0b4bb47237530054)`(const QVector2D & p,const QVector2D & seg1,const QVector2D & seg2)` 

Calculates the distance of a point to a line segment in 2D.

#### Parameters
* `p` The point 

* `seg1` The first endpoint of the line segment 

* `seg2` The second endpoint of the line segment 

#### Returns
Distance between the point and the line segment

#### `public static Q_INVOKABLE qreal `[`pointToLineDistSigned`](#classCellulo_1_1CelluloMathUtil_1ae3dc27d0fc111c4a0128f933c0970033)`(const QVector2D & p,const QVector2D & lp1,const QVector2D & lp2)` 

Calculates the signed distance of a point to a line in 2D.

#### Parameters
* `p` The point 

* `lp1` First point the line passes through 

* `lp2` Second point the line passes through 

#### Returns
Distance between the point and line segment, negative if point is below the line

#### `public static Q_INVOKABLE bool `[`pointInPoly`](#classCellulo_1_1CelluloMathUtil_1aefa1f8e82c7c4c54e95964b7d6d09de7)`(const QVector2D & p,const QList< QVector2D > & v)` 

Calculates whether the given point is in the given polygon.

#### Parameters
* `p` The point 

* `v` The vertices of the polygon 

#### Returns
Whether the point lies in the given polygon

#### `public static Q_INVOKABLE qreal `[`pointToPolyBorderDist`](#classCellulo_1_1CelluloMathUtil_1ae1771e133a7a8b41efde0f6e22e030f7)`(const QVector2D & p,const QList< QVector2D > & v)` 

Calculates the distance of the point to the polygon border.

#### Parameters
* `p` The point (may be in the polygon) 

* `v` The vertices of the polygon 

#### Returns
The distance of the point to the polygon border

#### `public static Q_INVOKABLE bool `[`hRayCrossesLineSeg`](#classCellulo_1_1CelluloMathUtil_1af13569931204ec6b3f1ae1b0a305e907)`(const QVector2D & r,const QVector2D & seg1,const QVector2D & seg2)` 

Calculates whether a horizontal ray starting from r and continuing towards +infinity crosses the line segment.

#### Parameters
* `r` Ray origin 

* `seg1` Line segment first endpoint 

* `seg2` Line segment second endpoint 

#### Returns
Whether the ray crosses the line segment

#### `public static Q_INVOKABLE void `[`c_srand`](#classCellulo_1_1CelluloMathUtil_1a972aab4558a5493a68005ec5c1a49185)`(unsigned int seed)` 

Initializes c's random number generator seed.

This will be called with time(NULL) at [CelluloMathUtil](#classCellulo_1_1CelluloMathUtil) creation time.

#### Parameters
* `seed` The seed

#### `public static Q_INVOKABLE int `[`c_rand`](#classCellulo_1_1CelluloMathUtil_1ab5ca178d6b922ecdc14e9f11cb258099)`(unsigned int max)` 

Calls c's random number generator.

#### Parameters
* `max` Interval size 

#### Returns
Random integer in [0, max-1]

#### `public static Q_INVOKABLE bool `[`collinear`](#classCellulo_1_1CelluloMathUtil_1a0d2b1423fd9c17dbd4fd412827f56830)`(const QVector2D & a,const QVector2D & b,const QVector2D & c)` 

Gets whether the given points are collinear enough.

#### Parameters
* `a` Point 1 

* `b` Point 2 

* `c` Point 3 

#### Returns
Whether the three points are collinear enough

#### `public static Q_INVOKABLE QVariantList `[`shuffle`](#classCellulo_1_1CelluloMathUtil_1a4c0226775e3f0a42b29282e704f4132b)`(const QVariantList & list)` 

std::random_shuffles a list

#### Parameters
* `list` The list to shuffle 

#### Returns
Shuffled list

#### `public static Q_INVOKABLE QVector2D `[`rotateVector`](#classCellulo_1_1CelluloMathUtil_1a3bb6db1423e9d3e4755f54ca73a27fb6)`(QVector2D const & vector,qreal angleRad)` 

Returns the given vector rotated by the given angle.

#### Parameters
* `vector` Vector to rotate 

* `angleRad` Angle to rotate by 

#### Returns
Rotated vector

#### `public static Q_INVOKABLE qreal `[`degToRad`](#classCellulo_1_1CelluloMathUtil_1afff0351c85b4147b57d01d10abf837c3)`(qreal deg)` 

Converts degrees to radians.

#### Parameters
* `deg` Angle in degrees 

#### Returns
Corresponding angle in radians

#### `public static Q_INVOKABLE qreal `[`radToDeg`](#classCellulo_1_1CelluloMathUtil_1aebd81ebb37fb050b70bd9ed2f044d825)`(qreal rad)` 

Converts radians to degrees.

#### Parameters
* `rad` Angle in radians 

#### Returns
Corresponding angle in degrees

#### `public static Q_INVOKABLE qreal `[`sigmoid`](#classCellulo_1_1CelluloMathUtil_1a3edaa9eb57c9a98fe58639fd92b83f6d)`(qreal L,qreal beta,qreal r_0,qreal r)` 

Calculates a parametric sigmoid function value.

#### Parameters
* `L` Magnitude parameter 

* `beta` Steepness parameter 

* `r_0` Horizontal offset parameter 

* `r` Input 

#### Returns
L/(1 + exp(beta*(r - r_0)))

#### `public static Q_INVOKABLE qreal `[`clamp`](#classCellulo_1_1CelluloMathUtil_1a802dd180acb91fdea9d3b1e4b18469d6)`(qreal val,qreal min,qreal max)` 

Clamps value in an interval.

#### Parameters
* `val` Value to clamp 

* `min` Minimum allowed value 

* `max` Maximum allowed value 

#### Returns
Value in [min, max]

# class `Cellulo::CelluloSVGUtil` 

```
class Cellulo::CelluloSVGUtil
  : public QObject
```  

Utilities for converting SVG files into [CelluloZone](#classCellulo_1_1CelluloZone) description files.

This class is **singleton**, you can call `ThisClass.anyFunction()` and use `ThisClass.anyProperty` directly.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public static Q_INVOKABLE QString `[`dumpAllPathsToJSON`](#classCellulo_1_1CelluloSVGUtil_1a03ff9f602eed155d9c49a8106b36a304)`(const QString & inSVGFile,const QString & outJSONFile,const QString & type,const QString & name,float dpi,bool optimized)` | Parses the given SVG file and dumps all paths into the given JSON file in the [CelluloZonePolyBezierClosestT](#classCellulo_1_1CelluloZonePolyBezierClosestT) type.
`public static Q_INVOKABLE QVariantList `[`loadZonesQML`](#classCellulo_1_1CelluloSVGUtil_1ab2e7db8bc5c58aa058f42cef70ce78c9)`(const QString & inSVGFile,const QString & name,float dpi,bool optimized)` | Parses the given SVG file into zones.

## Members

#### `public static Q_INVOKABLE QString `[`dumpAllPathsToJSON`](#classCellulo_1_1CelluloSVGUtil_1a03ff9f602eed155d9c49a8106b36a304)`(const QString & inSVGFile,const QString & outJSONFile,const QString & type,const QString & name,float dpi,bool optimized)` 

Parses the given SVG file and dumps all paths into the given JSON file in the [CelluloZonePolyBezierClosestT](#classCellulo_1_1CelluloZonePolyBezierClosestT) type.

If optimize is true, tries to parsed into a more accurate shape and outputs in the distance type of the more accurately parsed zone.

#### Parameters
* `inSVGFile` Full path to the local SVG file, can be in QUrl form 

* `outJSONFile` Full path to the local JSON file, will be overwritten, can be in QUrl form 

* `type` UNUSED 

* `name` Name prefix for all zones, consecutive zones are suffixed with "_1", "_2" etc 

* `dpi` Dots Per Inch to be used during conversion to millimeters (90 is the default for inkscape) 

* `optimized` Whether to try to extract as lines, points, circles, rectangles or polygons instead of polybezier zones, if possible (default, but EXPERIMENTAL). If disabled, all zones are converted into `POLBEZIERCLOSESTT`. 

#### Returns
Human readable result message

#### `public static Q_INVOKABLE QVariantList `[`loadZonesQML`](#classCellulo_1_1CelluloSVGUtil_1ab2e7db8bc5c58aa058f42cef70ce78c9)`(const QString & inSVGFile,const QString & name,float dpi,bool optimized)` 

Parses the given SVG file into zones.

#### Parameters
* `inSVGFile` Full path to the local SVG file, can be in QUrl form 

* `name` Name prefix for all zones 

* `dpi` Dots Per Inch to be used during conversion to millimeters (90 is the default for inkscape) 

* `optimized` Whether to try to extract as lines, points, circles, rectangles or polygons instead of polybezier zones, if possible 

#### Returns
Parsed zones (QML-compatible)

# class `Cellulo::CelluloSystemUtil` 

```
class Cellulo::CelluloSystemUtil
  : public QObject
```  

Object that provides system utilities.

This class is **singleton**, you can call `ThisClass.anyFunction()` and use `ThisClass.anyProperty` directly.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public static Q_INVOKABLE int `[`exec`](#classCellulo_1_1CelluloSystemUtil_1a860091df1106a70ff24c962007743879)`(QString const & command,QStringList const & arguments)` | Executes a system command.

## Members

#### `public static Q_INVOKABLE int `[`exec`](#classCellulo_1_1CelluloSystemUtil_1a860091df1106a70ff24c962007743879)`(QString const & command,QStringList const & arguments)` 

Executes a system command.

#### Parameters
* `command` The command 

* `arguments` List of arguments 

#### Returns
Return code of the executed command

# class `Cellulo::CelluloUIUtil` 

```
class Cellulo::CelluloUIUtil
  : public QObject
```  

User interface utilities used throughout Celullo activities.

This class is **singleton**, you can call `ThisClass.anyFunction()` and use `ThisClass.anyProperty` directly.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public static Q_INVOKABLE QColor `[`colorFromString`](#classCellulo_1_1CelluloUIUtil_1a99775ee04460bcec80b53afb5790e425)`(const QString & color)` | Converts string representation of color to actual color.
`public static Q_INVOKABLE QColor `[`colorInterpolate`](#classCellulo_1_1CelluloUIUtil_1a54a7011e0dce87a8efdae1d7fc26b0ac)`(const QColor & color1,const QColor & color2,qreal color1Weight)` | Interpolates two colors.

## Members

#### `public static Q_INVOKABLE QColor `[`colorFromString`](#classCellulo_1_1CelluloUIUtil_1a99775ee04460bcec80b53afb5790e425)`(const QString & color)` 

Converts string representation of color to actual color.

#### Parameters
* `color` String representation of color 

#### Returns
Color object

#### `public static Q_INVOKABLE QColor `[`colorInterpolate`](#classCellulo_1_1CelluloUIUtil_1a54a7011e0dce87a8efdae1d7fc26b0ac)`(const QColor & color1,const QColor & color2,qreal color1Weight)` 

Interpolates two colors.

#### Parameters
* `color1` First color 

* `color2` Second color 

* `color1Weight` Weight of the first color in [0.0,1.0]; second color's weight will be (1 - color1Weight) 

#### Returns
Interpolated color

# class `Cellulo::MacAddrSelector` 

```
class Cellulo::MacAddrSelector
  : public Row
```  

MAC address selection GUI.

TODO: Replace selectedAddress, connectionStatus, [connectRequested()](#classCellulo_1_1MacAddrSelector_1aa4aaeebaa7f611cb7a8f05c3f3477d16) and [disconnectRequested()](#classCellulo_1_1MacAddrSelector_1aa22b77041e3d02c3dbc2489b0a1af4a5) with property [CelluloBluetooth](#classCellulo_1_1CelluloBluetooth) robot: null

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} list< string > `[`addresses`](doc/doc-util.md#classCellulo_1_1MacAddrSelector_1a6a95e584a6ddfdaa91e6a89a76c79146) | List of possible MAC addresses, set by the user
`{property} string `[`selectedAddress`](doc/doc-util.md#classCellulo_1_1MacAddrSelector_1a7c34aa5cc712e4f1563ab2dc9f980a92) | Currently selected address. This property is read-only
`{property} string `[`selectedLocalAdapterAddress`](doc/doc-util.md#classCellulo_1_1MacAddrSelector_1a48231dcf6a4bd1a7af8d80391c1005e6) | Currently selected local adapter address (only available in Linux). This property is read-only
`{property} enum `[`connectionStatus`](doc/doc-util.md#classCellulo_1_1MacAddrSelector_1a093d56caa0a8e16770a4682bdd6c9a7f) | Current connection status to display, set by the user, one of [CelluloBluetoothEnums.ConnectionStatus](doc/doc-comm.md#classCellulo_1_1CelluloBluetoothEnums_1a9bdbb91140cd33c3daa779af49c7ed97)
`public void `[`selectAddress`](#classCellulo_1_1MacAddrSelector_1a8e1907b760f6a4e94abdba5dd9cc5a97)`(string address)` | Selects the given address if it exists in the list of addresses.
`public void `[`selectLocalAdapterAddress`](#classCellulo_1_1MacAddrSelector_1a1b6856a770ee61ddf08125cca72be228)`(string address)` | Selects the given local adapter address if it exists in the list of addresses.
`{signal} public void `[`connectRequested`](#classCellulo_1_1MacAddrSelector_1aa4aaeebaa7f611cb7a8f05c3f3477d16)`()` | Emitted when the connect button is pressed.
`{signal} public void `[`disconnectRequested`](#classCellulo_1_1MacAddrSelector_1aa22b77041e3d02c3dbc2489b0a1af4a5)`()` | Emitted when the disconnect button is pressed.

## Members

#### `{property} list< string > `[`addresses`](doc/doc-util.md#classCellulo_1_1MacAddrSelector_1a6a95e584a6ddfdaa91e6a89a76c79146) 

List of possible MAC addresses, set by the user

#### `{property} string `[`selectedAddress`](doc/doc-util.md#classCellulo_1_1MacAddrSelector_1a7c34aa5cc712e4f1563ab2dc9f980a92) 

Currently selected address. This property is read-only

#### `{property} string `[`selectedLocalAdapterAddress`](doc/doc-util.md#classCellulo_1_1MacAddrSelector_1a48231dcf6a4bd1a7af8d80391c1005e6) 

Currently selected local adapter address (only available in Linux). This property is read-only

#### `{property} enum `[`connectionStatus`](doc/doc-util.md#classCellulo_1_1MacAddrSelector_1a093d56caa0a8e16770a4682bdd6c9a7f) 

Current connection status to display, set by the user, one of [CelluloBluetoothEnums.ConnectionStatus](#classCellulo_1_1CelluloBluetoothEnums_1a9bdbb91140cd33c3daa779af49c7ed97)

#### `public void `[`selectAddress`](#classCellulo_1_1MacAddrSelector_1a8e1907b760f6a4e94abdba5dd9cc5a97)`(string address)` 

Selects the given address if it exists in the list of addresses.

#### Parameters
* `address` Address to look for in the list of addresses

#### `public void `[`selectLocalAdapterAddress`](#classCellulo_1_1MacAddrSelector_1a1b6856a770ee61ddf08125cca72be228)`(string address)` 

Selects the given local adapter address if it exists in the list of addresses.

#### Parameters
* `address` Address to look for in the list of addresses

#### `{signal} public void `[`connectRequested`](#classCellulo_1_1MacAddrSelector_1aa4aaeebaa7f611cb7a8f05c3f3477d16)`()` 

Emitted when the connect button is pressed.

#### `{signal} public void `[`disconnectRequested`](#classCellulo_1_1MacAddrSelector_1aa22b77041e3d02c3dbc2489b0a1af4a5)`()` 

Emitted when the disconnect button is pressed.

# class `Cellulo::Toast` 

```
class Cellulo::Toast
  : public Rectangle
```  

An Android-like timed message text in a box that selfdestroys when finished if desired.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} bool `[`selfDestroying`](doc/doc-util.md#classCellulo_1_1Toast_1a670947dec5e4993ccb5f3224e5808c90) | Whether this [Toast](doc/doc-util.md#classCellulo_1_1Toast) will selfdestroy when it is finished
`public void `[`show`](#classCellulo_1_1Toast_1a3109b6b63038539291ac3d9c9e9459e5)`(string text,real duration)` | Shows this [Toast](doc/doc-util.md#classCellulo_1_1Toast).

## Members

#### `{property} bool `[`selfDestroying`](doc/doc-util.md#classCellulo_1_1Toast_1a670947dec5e4993ccb5f3224e5808c90) 

Whether this [Toast](#classCellulo_1_1Toast) will selfdestroy when it is finished

#### `public void `[`show`](#classCellulo_1_1Toast_1a3109b6b63038539291ac3d9c9e9459e5)`(string text,real duration)` 

Shows this [Toast](#classCellulo_1_1Toast).

Public 
#### Parameters
* `text` Text to show 

* `duration` Duration to show in milliseconds, defaults to 3000

# class `Cellulo::ToastManager` 

```
class Cellulo::ToastManager
  : public Column
```  

Creates on-screen banner texts, like Android's `[Toast](#classCellulo_1_1Toast)`s. Ensures that multiple toasts show correctly together.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public void `[`show`](#classCellulo_1_1ToastManager_1ad253e4b6c7e3be8c9190f922adf12b9f)`(string text,real duration)` | Shows a [Toast](doc/doc-util.md#classCellulo_1_1Toast).

## Members

#### `public void `[`show`](#classCellulo_1_1ToastManager_1ad253e4b6c7e3be8c9190f922adf12b9f)`(string text,real duration)` 

Shows a [Toast](#classCellulo_1_1Toast).

Public 
#### Parameters
* `text` Text to show 

* `duration` Duration to show in milliseconds, defaults to 3000

