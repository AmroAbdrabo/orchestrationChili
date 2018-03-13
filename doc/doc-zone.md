# group `zone` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[`Cellulo::CelluloZone`](doc/doc-zone.md#classCellulo_1_1CelluloZone) | [CelluloZone](doc/doc-zone.md#classCellulo_1_1CelluloZone) Base Class for zones.
`class `[`Cellulo::CelluloZoneRectangle`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRectangle) | [CelluloZone](doc/doc-zone.md#classCellulo_1_1CelluloZone) Base Class for rectangular zones.
`class `[`Cellulo::CelluloZoneRectangleInner`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRectangleInner) | [CelluloZone](doc/doc-zone.md#classCellulo_1_1CelluloZone) Specific Class for rectangular zones inner determination; calculates whether the client's position is within the rectangle, value is `0.0` or `1.0`.
`class `[`Cellulo::CelluloZoneRectangleBorder`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRectangleBorder) | [CelluloZone](doc/doc-zone.md#classCellulo_1_1CelluloZone) Specific Class for rectangular zones border determination; calculates whether the client's position is within **borderThickness** of the zone's border, value is `0.0` or `1.0`.
`class `[`Cellulo::CelluloZoneRectangleDistance`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRectangleDistance) | [CelluloZone](doc/doc-zone.md#classCellulo_1_1CelluloZone) Specific Class for rectangular zones distance determination; calculates the client's distance to the zone's border.
`class `[`Cellulo::CelluloZoneTypes`](doc/doc-zone.md#classCellulo_1_1CelluloZoneTypes) | `[CelluloZone](doc/doc-zone.md#classCellulo_1_1CelluloZone)` type enum and utilities.

# class `Cellulo::CelluloZone` 

```
class Cellulo::CelluloZone
  : public QQuickItem
```  

[CelluloZone](#classCellulo_1_1CelluloZone) Base Class for zones.

Abstract description of a "zone" on a 2D plane. These zones could be closed curves, polygons, open curves, even points.

They are meant interact with `[CelluloZoneClient](#classCellulo_1_1CelluloZoneClient)`s (such as a robot, or a virtual robot on a screen), calculating a real value with respect to each client (for example, the distance to the client in the case of a point zone). With the help of `[CelluloZoneEngine](#classCellulo_1_1CelluloZoneEngine)`, a zone emits each client's `zoneValueChanged()` signal upon the changing of the value with respect to that client.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} bool `[`active`](doc/doc-zone.md#classCellulo_1_1CelluloZone_1adb2c9434ea04be38ddb53c06632ce3db) | Whether this zone is active, i.e generates `zoneValueChanged` signals on `[CelluloZoneClient](#classCellulo_1_1CelluloZoneClient)`s, default true.
`{property} QString `[`name`](doc/doc-zone.md#classCellulo_1_1CelluloZone_1abb58a78cd5ce7c499a0926710862f188) | Name of this zone, must be unique, default is `"anonymousZone"`
`{property} `[`CelluloZoneTypes::ZoneType`](#classCellulo_1_1CelluloZoneTypes_1acb24a099726e8d59124afd691c86f9cf)` `[`type`](#classCellulo_1_1CelluloZone_1a703f7329dc9e335356e62ff90f6a3228) | Type of this zone, read-only.
`public Q_INVOKABLE float `[`calculate`](#classCellulo_1_1CelluloZone_1a404b8449396ad290e001370810b2a62f)`(float xRobot,float yRobot,float thetaRobot)` | Calculate the zone quantity of this zone according to the robot's pose.
`public Q_INVOKABLE bool `[`isMouseInside`](#classCellulo_1_1CelluloZone_1ae58727d9928c7ed7085902cd46bcfdd0)`(QVector2D mousePosition,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Get if the mouse position is inside the zone or not.
`public Q_INVOKABLE `[`CelluloZonePaintedItem`](#classCellulo_1_1CelluloZonePaintedItem)` * `[`createPaintedItem`](#classCellulo_1_1CelluloZone_1a305df5424bddb23ddb7f0935561b3206)`(QQuickItem * parent,QColor color,qreal physicalPlaygroundWidth,qreal physicalPlaygroundHeight)` | Creates a PaintedItem that is the visual representation of this zone.
`public Q_INVOKABLE void `[`setPaintedItem`](#classCellulo_1_1CelluloZone_1acd24c54985b7d0d3ebadcbe24ee4ecbd)`(`[`CelluloZonePaintedItem`](#classCellulo_1_1CelluloZonePaintedItem)` * newPaintedItem)` | Associates a painted item with this zone so that it can be redrawn if the zone changes.
`public inline Q_INVOKABLE `[`CelluloZonePaintedItem`](#classCellulo_1_1CelluloZonePaintedItem)` * `[`getPaintedItem`](#classCellulo_1_1CelluloZone_1ac28f3c3e1cd508b206b6a8937c5c87fd)`()` | Get painted item associated with this zone so that its properties can be changed.

## Members

#### `{property} bool `[`active`](doc/doc-zone.md#classCellulo_1_1CelluloZone_1adb2c9434ea04be38ddb53c06632ce3db) 

Whether this zone is active, i.e generates `zoneValueChanged` signals on `[CelluloZoneClient](#classCellulo_1_1CelluloZoneClient)`s, default true.

Whether the zone is active.

#### `{property} QString `[`name`](doc/doc-zone.md#classCellulo_1_1CelluloZone_1abb58a78cd5ce7c499a0926710862f188) 

Name of this zone, must be unique, default is `"anonymousZone"`

#### `{property} `[`CelluloZoneTypes::ZoneType`](#classCellulo_1_1CelluloZoneTypes_1acb24a099726e8d59124afd691c86f9cf)` `[`type`](#classCellulo_1_1CelluloZone_1a703f7329dc9e335356e62ff90f6a3228) 

Type of this zone, read-only.

#### `public Q_INVOKABLE float `[`calculate`](#classCellulo_1_1CelluloZone_1a404b8449396ad290e001370810b2a62f)`(float xRobot,float yRobot,float thetaRobot)` 

Calculate the zone quantity of this zone according to the robot's pose.

#### Parameters
* `xRobot` x position of the robot 

* `yRobot` y position of the robot 

* `thetaRobot` theta position of the robot

#### Returns
Zone quantity for this zone and this robot's pose

#### `public Q_INVOKABLE bool `[`isMouseInside`](#classCellulo_1_1CelluloZone_1ae58727d9928c7ed7085902cd46bcfdd0)`(QVector2D mousePosition,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Get if the mouse position is inside the zone or not.

#### Parameters
* `mousePosition` (x,y) coordinates of the mouse in pixels 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

#### Returns
Whether the mouse position is inside the zone or not

#### `public Q_INVOKABLE `[`CelluloZonePaintedItem`](#classCellulo_1_1CelluloZonePaintedItem)` * `[`createPaintedItem`](#classCellulo_1_1CelluloZone_1a305df5424bddb23ddb7f0935561b3206)`(QQuickItem * parent,QColor color,qreal physicalPlaygroundWidth,qreal physicalPlaygroundHeight)` 

Creates a PaintedItem that is the visual representation of this zone.

#### Parameters
* `parent` Visual QML parent that this item will fill 

* `color` Color to paint with 

* `physicalPlaygroundWidth` Playground width in mm 

* `physicalPlaygroundHeight` Playground height in mm

#### Returns
A PaintedItem that is the visual representation of this zone

#### `public Q_INVOKABLE void `[`setPaintedItem`](#classCellulo_1_1CelluloZone_1acd24c54985b7d0d3ebadcbe24ee4ecbd)`(`[`CelluloZonePaintedItem`](#classCellulo_1_1CelluloZonePaintedItem)` * newPaintedItem)` 

Associates a painted item with this zone so that it can be redrawn if the zone changes.

#### Parameters
* `newPaintedItem` New painted item

#### `public inline Q_INVOKABLE `[`CelluloZonePaintedItem`](#classCellulo_1_1CelluloZonePaintedItem)` * `[`getPaintedItem`](#classCellulo_1_1CelluloZone_1ac28f3c3e1cd508b206b6a8937c5c87fd)`()` 

Get painted item associated with this zone so that its properties can be changed.

#### Returns
The PaintedItem that is the visual representation of this zone

# class `Cellulo::CelluloZoneRectangle` 

```
class Cellulo::CelluloZoneRectangle
  : public Cellulo::CelluloZone
```  

[CelluloZone](#classCellulo_1_1CelluloZone) Base Class for rectangular zones.

This class is **abstract**, you cannot instantiate it directly. Refer to classes derived from it.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} float `[`x`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRectangle_1a5eda2e9d4a29010c745f3547108d4cfb) | X coordinate of the top left corner (mm)
`{property} float `[`y`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRectangle_1ad0e8c8be54bbb4dcf4e8f751993088b8) | Y coordinate of the top left corner (mm)
`{property} float `[`height`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRectangle_1a936828d957424f788e89152b5349b33c) | Width of the rectangle (mm)
`{property} float `[`width`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRectangle_1a02f1b9f0667164115c62cad18109f96d) | Height of the rectangle (mm)

## Members

#### `{property} float `[`x`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRectangle_1a5eda2e9d4a29010c745f3547108d4cfb) 

X coordinate of the top left corner (mm)

#### `{property} float `[`y`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRectangle_1ad0e8c8be54bbb4dcf4e8f751993088b8) 

Y coordinate of the top left corner (mm)

#### `{property} float `[`height`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRectangle_1a936828d957424f788e89152b5349b33c) 

Width of the rectangle (mm)

#### `{property} float `[`width`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRectangle_1a02f1b9f0667164115c62cad18109f96d) 

Height of the rectangle (mm)

# class `Cellulo::CelluloZoneRectangleInner` 

```
class Cellulo::CelluloZoneRectangleInner
  : public Cellulo::CelluloZoneRectangle
```  

[CelluloZone](#classCellulo_1_1CelluloZone) Specific Class for rectangular zones inner determination; calculates whether the client's position is within the rectangle, value is `0.0` or `1.0`.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `Cellulo::CelluloZoneRectangleBorder` 

```
class Cellulo::CelluloZoneRectangleBorder
  : public Cellulo::CelluloZoneRectangle
```  

[CelluloZone](#classCellulo_1_1CelluloZone) Specific Class for rectangular zones border determination; calculates whether the client's position is within **borderThickness** of the zone's border, value is `0.0` or `1.0`.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} qreal `[`borderThickness`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRectangleBorder_1a1f08060c512e11e672f515f3b8d5c66a) | Total thickness of the border (mm)

## Members

#### `{property} qreal `[`borderThickness`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRectangleBorder_1a1f08060c512e11e672f515f3b8d5c66a) 

Total thickness of the border (mm)

The border thickness in mm.

# class `Cellulo::CelluloZoneRectangleDistance` 

```
class Cellulo::CelluloZoneRectangleDistance
  : public Cellulo::CelluloZoneRectangle
```  

[CelluloZone](#classCellulo_1_1CelluloZone) Specific Class for rectangular zones distance determination; calculates the client's distance to the zone's border.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `Cellulo::CelluloZoneTypes` 

```
class Cellulo::CelluloZoneTypes
  : public QObject
```  

`[CelluloZone](#classCellulo_1_1CelluloZone)` type enum and utilities.

This class is **singleton**, you can call `ThisClass.anyFunction()` and use `ThisClass.anyProperty` directly.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`enum `[`ZoneType`](doc/doc-zone.md#classCellulo_1_1CelluloZoneTypes_1acb24a099726e8d59124afd691c86f9cf) | List of possible zones.
`public static Q_INVOKABLE `[`ZoneType`](#classCellulo_1_1CelluloZoneTypes_1acb24a099726e8d59124afd691c86f9cf)` `[`typeFromString`](#classCellulo_1_1CelluloZoneTypes_1a8992c8c7efd4806cd1f32a3a1e7e1e12)`(const QString & typeName)` | Converts the QString to its ZoneType representation.
`public static Q_INVOKABLE `[`CelluloZone`](#classCellulo_1_1CelluloZone)` * `[`newZoneFromType`](#classCellulo_1_1CelluloZoneTypes_1af9c8f3287319c21770cc9766ec1b0da3)`(`[`ZoneType`](#classCellulo_1_1CelluloZoneTypes_1acb24a099726e8d59124afd691c86f9cf)` type)` | Creates a new zone based on the given type.

## Members

#### `enum `[`ZoneType`](doc/doc-zone.md#classCellulo_1_1CelluloZoneTypes_1acb24a099726e8d59124afd691c86f9cf) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
ANGLEDIFFERENCE            | [CelluloZoneAngleDifference](#classCellulo_1_1CelluloZoneAngleDifference).
ANGLEINTERVALINNER            | [CelluloZoneAngleIntervalInner](#classCellulo_1_1CelluloZoneAngleIntervalInner).
ANGLEINTERVALBORDER            | [CelluloZoneAngleIntervalBorder](#classCellulo_1_1CelluloZoneAngleIntervalBorder).
ANGLEINTERVALDISTANCE            | [CelluloZoneAngleIntervalDistance](#classCellulo_1_1CelluloZoneAngleIntervalDistance).
CIRCLEINNER            | [CelluloZoneCircleInner](#classCellulo_1_1CelluloZoneCircleInner).
CIRCLEBORDER            | [CelluloZoneCircleBorder](#classCellulo_1_1CelluloZoneCircleBorder).
CIRCLEDISTANCE            | [CelluloZoneCircleDistance](#classCellulo_1_1CelluloZoneCircleDistance).
RECTANGLEINNER            | [CelluloZoneRectangleInner](doc/doc-zone.md#classCellulo_1_1CelluloZoneRectangleInner).
RECTANGLEBORDER            | [CelluloZoneRectangleBorder](doc/doc-zone.md#classCellulo_1_1CelluloZoneRectangleBorder).
RECTANGLEDISTANCE            | [CelluloZoneRectangleDistance](doc/doc-zone.md#classCellulo_1_1CelluloZoneRectangleDistance).
LINESEGMENTDISTANCE            | [CelluloZoneLineSegmentDistance](#classCellulo_1_1CelluloZoneLineSegmentDistance).
LINEDISTANCESIGNED            | [CelluloZoneLineDistanceSigned](#classCellulo_1_1CelluloZoneLineDistanceSigned).
LINEBORDER            | [CelluloZoneLineBorder](#classCellulo_1_1CelluloZoneLineBorder).
POINTDISTANCE            | [CelluloZonePointDistance](#classCellulo_1_1CelluloZonePointDistance).
RPOLYGONINNER            | [CelluloZoneRegularPolygonInner](#classCellulo_1_1CelluloZoneRegularPolygonInner).
RPOLYGONBORDER            | [CelluloZoneRegularPolygonBorder](#classCellulo_1_1CelluloZoneRegularPolygonBorder).
RPOLYGONDISTANCE            | [CelluloZoneRegularPolygonDistance](#classCellulo_1_1CelluloZoneRegularPolygonDistance).
IRPOLYGONINNER            | [CelluloZoneIrregularPolygonInner](#classCellulo_1_1CelluloZoneIrregularPolygonInner).
IRPOLYGONBORDER            | [CelluloZoneIrregularPolygonBorder](#classCellulo_1_1CelluloZoneIrregularPolygonBorder).
IRPOLYGONDISTANCE            | [CelluloZoneIrregularPolygonDistance](#classCellulo_1_1CelluloZoneIrregularPolygonDistance).
POLYBEZIERCLOSESTT            | [CelluloZonePolyBezierClosestT](#classCellulo_1_1CelluloZonePolyBezierClosestT).
POLYBEZIERXT            | [CelluloZonePolyBezierXT](#classCellulo_1_1CelluloZonePolyBezierXT).
POLYBEZIERYT            | [CelluloZonePolyBezierYT](#classCellulo_1_1CelluloZonePolyBezierYT).
POLYBEZIERDISTANCE            | [CelluloZonePolyBezierDistance](#classCellulo_1_1CelluloZonePolyBezierDistance).
POLYBEZIERBORDER            | [CelluloZonePolyBezierBorder](#classCellulo_1_1CelluloZonePolyBezierBorder).
POLYBEZIERINNER            | [CelluloZonePolyBezierInner](#classCellulo_1_1CelluloZonePolyBezierInner).
ZoneTypeNumElements            | 

List of possible zones.

#### `public static Q_INVOKABLE `[`ZoneType`](#classCellulo_1_1CelluloZoneTypes_1acb24a099726e8d59124afd691c86f9cf)` `[`typeFromString`](#classCellulo_1_1CelluloZoneTypes_1a8992c8c7efd4806cd1f32a3a1e7e1e12)`(const QString & typeName)` 

Converts the QString to its ZoneType representation.

#### Parameters
* `typeName` QString to be converted 

#### Returns
ZoneType Reprensentation of the QString

#### `public static Q_INVOKABLE `[`CelluloZone`](#classCellulo_1_1CelluloZone)` * `[`newZoneFromType`](#classCellulo_1_1CelluloZoneTypes_1af9c8f3287319c21770cc9766ec1b0da3)`(`[`ZoneType`](#classCellulo_1_1CelluloZoneTypes_1acb24a099726e8d59124afd691c86f9cf)` type)` 

Creates a new zone based on the given type.

#### Parameters
* `type` The desired type 

#### Returns
Pointer to the created zone

