# group `zone` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[`Cellulo::CelluloZone`](doc/doc-zone.md#classCellulo_1_1CelluloZone) | [CelluloZone](doc/doc-zone.md#classCellulo_1_1CelluloZone) Base Class for zones.
`class `[`Cellulo::CelluloZoneAngle`](doc/doc-zone.md#classCellulo_1_1CelluloZoneAngle) | Describes a single angle.
`class `[`Cellulo::CelluloZoneAngleDifference`](doc/doc-zone.md#classCellulo_1_1CelluloZoneAngleDifference) | Describes an angular zone sensitive to the client angle difference.
`class `[`Cellulo::CelluloZoneAngleInterval`](doc/doc-zone.md#classCellulo_1_1CelluloZoneAngleInterval) | [CelluloZone](doc/doc-zone.md#classCellulo_1_1CelluloZone) Base for angular interval zones.
`class `[`Cellulo::CelluloZoneAngleIntervalInner`](doc/doc-zone.md#classCellulo_1_1CelluloZoneAngleIntervalInner) | Describes an angular zone sensitive to the client angle being in/out of the interval.
`class `[`Cellulo::CelluloZoneAngleIntervalBorder`](doc/doc-zone.md#classCellulo_1_1CelluloZoneAngleIntervalBorder) | Describes an angular zone sensitive to the client angle being on the border of the interval.
`class `[`Cellulo::CelluloZoneAngleIntervalDistance`](doc/doc-zone.md#classCellulo_1_1CelluloZoneAngleIntervalDistance) | Describes an angular zone sensitive to the client orientation distance to the interval.
`class `[`Cellulo::CelluloZoneCircle`](doc/doc-zone.md#classCellulo_1_1CelluloZoneCircle) | [CelluloZone](doc/doc-zone.md#classCellulo_1_1CelluloZone) Base Class for circular zones.
`class `[`Cellulo::CelluloZoneCircleInner`](doc/doc-zone.md#classCellulo_1_1CelluloZoneCircleInner) | [CelluloZone](doc/doc-zone.md#classCellulo_1_1CelluloZone) Specific Class for circular zones inner determination.
`class `[`Cellulo::CelluloZoneCircleBorder`](doc/doc-zone.md#classCellulo_1_1CelluloZoneCircleBorder) | [CelluloZone](doc/doc-zone.md#classCellulo_1_1CelluloZone) Specific Class for circular zones border determination.
`class `[`Cellulo::CelluloZoneCircleDistance`](doc/doc-zone.md#classCellulo_1_1CelluloZoneCircleDistance) | [CelluloZone](doc/doc-zone.md#classCellulo_1_1CelluloZone) Specific Class for circular zones distance determination.
`class `[`Cellulo::CelluloZoneClient`](doc/doc-zone.md#classCellulo_1_1CelluloZoneClient) | Describes an object with a physical pose (e.g a robot) that may interact with [Cellulo](#namespaceCellulo) zones.
`class `[`Cellulo::CelluloZoneEngine`](doc/doc-zone.md#classCellulo_1_1CelluloZoneEngine) | Object that ensures `[CelluloZone](#classCellulo_1_1CelluloZone)` and `[CelluloZoneClient](#classCellulo_1_1CelluloZoneClient)` interaction.
`class `[`Cellulo::CelluloZoneJsonHandler`](doc/doc-zone.md#classCellulo_1_1CelluloZoneJsonHandler) | Utilities to load/save `[CelluloZone](doc/doc-zone.md#classCellulo_1_1CelluloZone)`s to to/from files in JSON format.
`class `[`Cellulo::CelluloZoneLine`](doc/doc-zone.md#classCellulo_1_1CelluloZoneLine) | [CelluloZone](doc/doc-zone.md#classCellulo_1_1CelluloZone) Base Class for line zones.
`class `[`Cellulo::CelluloZoneLineSegmentDistance`](doc/doc-zone.md#classCellulo_1_1CelluloZoneLineSegmentDistance) | [CelluloZone](doc/doc-zone.md#classCellulo_1_1CelluloZone) Specific Class for line segment distance determination.
`class `[`Cellulo::CelluloZoneLineDistanceSigned`](doc/doc-zone.md#classCellulo_1_1CelluloZoneLineDistanceSigned) | [CelluloZone](doc/doc-zone.md#classCellulo_1_1CelluloZone) Specific Class for signed line distance determination.
`class `[`Cellulo::CelluloZoneLineBorder`](doc/doc-zone.md#classCellulo_1_1CelluloZoneLineBorder) | [CelluloZone](doc/doc-zone.md#classCellulo_1_1CelluloZone) Specific Class for determining whether a point is within a distance to an infinite line.
`class `[`Cellulo::CelluloZonePaintedItem`](doc/doc-zone.md#classCellulo_1_1CelluloZonePaintedItem) | A QML compatible QQuickPaintedItem for CelluloZones.
`class `[`Cellulo::CelluloZonePoint`](doc/doc-zone.md#classCellulo_1_1CelluloZonePoint) | [CelluloZone](doc/doc-zone.md#classCellulo_1_1CelluloZone) Base Class for point zones.
`class `[`Cellulo::CelluloZonePointDistance`](doc/doc-zone.md#classCellulo_1_1CelluloZonePointDistance) | [CelluloZone](doc/doc-zone.md#classCellulo_1_1CelluloZone) Specific Class for point zones distance determination.
`class `[`Cellulo::CelluloZonePolygon`](doc/doc-zone.md#classCellulo_1_1CelluloZonePolygon) | [CelluloZone](doc/doc-zone.md#classCellulo_1_1CelluloZone) Base Class for polygonal zones.
`class `[`Cellulo::CelluloZoneIrregularPolygon`](doc/doc-zone.md#classCellulo_1_1CelluloZoneIrregularPolygon) | [CelluloZone](doc/doc-zone.md#classCellulo_1_1CelluloZone) Base Class for irregular polygonal zones.
`class `[`Cellulo::CelluloZoneIrregularPolygonInner`](doc/doc-zone.md#classCellulo_1_1CelluloZoneIrregularPolygonInner) | [CelluloZone](doc/doc-zone.md#classCellulo_1_1CelluloZone) Specific Class for irregular polygonal zones inner determination.
`class `[`Cellulo::CelluloZoneIrregularPolygonBorder`](doc/doc-zone.md#classCellulo_1_1CelluloZoneIrregularPolygonBorder) | [CelluloZone](doc/doc-zone.md#classCellulo_1_1CelluloZone) Specific Class for irregular polygonal zones border determination.
`class `[`Cellulo::CelluloZoneIrregularPolygonDistance`](doc/doc-zone.md#classCellulo_1_1CelluloZoneIrregularPolygonDistance) | [CelluloZone](doc/doc-zone.md#classCellulo_1_1CelluloZone) Specific Class for irregular polygonal zones distance determination.
`class `[`Cellulo::CelluloZoneRegularPolygon`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRegularPolygon) | Base class for regular polygon zones.
`class `[`Cellulo::CelluloZoneRegularPolygonInner`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRegularPolygonInner) | [CelluloZone](doc/doc-zone.md#classCellulo_1_1CelluloZone) Specific Class for regular polygonal zones inner determination.
`class `[`Cellulo::CelluloZoneRegularPolygonBorder`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRegularPolygonBorder) | [CelluloZone](doc/doc-zone.md#classCellulo_1_1CelluloZone) Specific Class for regular polygonal zones border determination.
`class `[`Cellulo::CelluloZoneRegularPolygonDistance`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRegularPolygonDistance) | [CelluloZone](doc/doc-zone.md#classCellulo_1_1CelluloZone) Specific Class for regular polygonal zones distance determination.
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
`{property} bool `[`active`](doc/doc-zone.md#classCellulo_1_1CelluloZone_1adb2c9434ea04be38ddb53c06632ce3db) | Whether this zone is active, i.e generates `zoneValueChanged` signals on `[CelluloZoneClient](doc/doc-zone.md#classCellulo_1_1CelluloZoneClient)`s, default true.
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

# class `Cellulo::CelluloZoneAngle` 

```
class Cellulo::CelluloZoneAngle
  : public Cellulo::CelluloZone
```  

Describes a single angle.

This class is **abstract**, you cannot instantiate it directly. Refer to classes derived from it.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} float `[`angle`](#group__zone_1ga27b340a93612c7f287afee2b47e6fe68) | Angle that this zone is concerned with (deg)

## Members

#### `{property} float `[`angle`](#group__zone_1ga27b340a93612c7f287afee2b47e6fe68) 

Angle that this zone is concerned with (deg)

# class `Cellulo::CelluloZoneAngleDifference` 

```
class Cellulo::CelluloZoneAngleDifference
  : public Cellulo::CelluloZoneAngle
```  

Describes an angular zone sensitive to the client angle difference.

Calculates the signed difference of the client orientation angles to the zone's angle, value is in `]-180, 180]`.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `Cellulo::CelluloZoneAngleInterval` 

```
class Cellulo::CelluloZoneAngleInterval
  : public Cellulo::CelluloZone
```  

[CelluloZone](#classCellulo_1_1CelluloZone) Base for angular interval zones.

The zone is described by the limits fromAngle to toAngle, in that order; e.g if 330 and 30 are provided, the zone interval includes 0 degrees and not 180 degrees.

This class is **abstract**, you cannot instantiate it directly. Refer to classes derived from it.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} float `[`fromAngle`](doc/doc-zone.md#classCellulo_1_1CelluloZoneAngleInterval_1ae53f35485ff46c07d6e2128957a6b67c) | Beginning of this zone (deg)
`{property} float `[`toAngle`](doc/doc-zone.md#classCellulo_1_1CelluloZoneAngleInterval_1a8b405d1a360070b5350368feec11c0e4) | End of this zone (deg)

## Members

#### `{property} float `[`fromAngle`](doc/doc-zone.md#classCellulo_1_1CelluloZoneAngleInterval_1ae53f35485ff46c07d6e2128957a6b67c) 

Beginning of this zone (deg)

#### `{property} float `[`toAngle`](doc/doc-zone.md#classCellulo_1_1CelluloZoneAngleInterval_1a8b405d1a360070b5350368feec11c0e4) 

End of this zone (deg)

# class `Cellulo::CelluloZoneAngleIntervalInner` 

```
class Cellulo::CelluloZoneAngleIntervalInner
  : public Cellulo::CelluloZoneAngleInterval
```  

Describes an angular zone sensitive to the client angle being in/out of the interval.

Calculates whether the client's orientation is within the zone's angle interval, value is `0.0` or `1.0`. The zone is described by the limits **fromAngle** to **toAngle**, in that order; e.g if `330` and `30` are provided, the zone interval includes `0` degrees and not `180` degrees.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `Cellulo::CelluloZoneAngleIntervalBorder` 

```
class Cellulo::CelluloZoneAngleIntervalBorder
  : public Cellulo::CelluloZoneAngleInterval
```  

Describes an angular zone sensitive to the client angle being on the border of the interval.

Calculates whether the client's orientation is within **borderThickness** of the zone's angle interval limits, value is `0.0` or `1.0`

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} qreal `[`borderThickness`](doc/doc-zone.md#classCellulo_1_1CelluloZoneAngleIntervalBorder_1a34ac0856ce5ef641b0ee37861d91f077) | Total thickness of the border (deg)

## Members

#### `{property} qreal `[`borderThickness`](doc/doc-zone.md#classCellulo_1_1CelluloZoneAngleIntervalBorder_1a34ac0856ce5ef641b0ee37861d91f077) 

Total thickness of the border (deg)

The border thickness in degrees.

# class `Cellulo::CelluloZoneAngleIntervalDistance` 

```
class Cellulo::CelluloZoneAngleIntervalDistance
  : public Cellulo::CelluloZoneAngleInterval
```  

Describes an angular zone sensitive to the client orientation distance to the interval.

Calculates the client's angular distance to the zone's angle interval. The zone is described by the limits **fromAngle** to **toAngle**, in that order; e.g if `330` and `30` are provided, the zone interval includes `0` degrees and not `180` degrees. Always calculates the shortest distance to the interval.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `Cellulo::CelluloZoneCircle` 

```
class Cellulo::CelluloZoneCircle
  : public Cellulo::CelluloZone
```  

[CelluloZone](#classCellulo_1_1CelluloZone) Base Class for circular zones.

This class is **abstract**, you cannot instantiate it directly. Refer to classes derived from it.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} float `[`x`](doc/doc-zone.md#classCellulo_1_1CelluloZoneCircle_1a645768a86591f37a6bd00ed80f494313) | Center x coordinate of the circle (mm)
`{property} float `[`y`](doc/doc-zone.md#classCellulo_1_1CelluloZoneCircle_1a1ada06cba763ed0dd9bc835d109782d8) | Center y coordinate of the circle (mm)
`{property} float `[`r`](doc/doc-zone.md#classCellulo_1_1CelluloZoneCircle_1ade7234cb3d3fa818aef69bdfb0f67ab8) | Radius of the circle (mm)

## Members

#### `{property} float `[`x`](doc/doc-zone.md#classCellulo_1_1CelluloZoneCircle_1a645768a86591f37a6bd00ed80f494313) 

Center x coordinate of the circle (mm)

#### `{property} float `[`y`](doc/doc-zone.md#classCellulo_1_1CelluloZoneCircle_1a1ada06cba763ed0dd9bc835d109782d8) 

Center y coordinate of the circle (mm)

#### `{property} float `[`r`](doc/doc-zone.md#classCellulo_1_1CelluloZoneCircle_1ade7234cb3d3fa818aef69bdfb0f67ab8) 

Radius of the circle (mm)

# class `Cellulo::CelluloZoneCircleInner` 

```
class Cellulo::CelluloZoneCircleInner
  : public Cellulo::CelluloZoneCircle
```  

[CelluloZone](#classCellulo_1_1CelluloZone) Specific Class for circular zones inner determination.

Calculates whether the client's position is within the circle, value is `0.0` or `1.0`.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `Cellulo::CelluloZoneCircleBorder` 

```
class Cellulo::CelluloZoneCircleBorder
  : public Cellulo::CelluloZoneCircle
```  

[CelluloZone](#classCellulo_1_1CelluloZone) Specific Class for circular zones border determination.

Calculates whether the client's position is within **borderThickness** of the zone's border, value is `0.0` or `1.0`.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} qreal `[`borderThickness`](doc/doc-zone.md#classCellulo_1_1CelluloZoneCircleBorder_1ad780c284026f14d45812b74310dd4b7e) | Total thickness of the border (deg)

## Members

#### `{property} qreal `[`borderThickness`](doc/doc-zone.md#classCellulo_1_1CelluloZoneCircleBorder_1ad780c284026f14d45812b74310dd4b7e) 

Total thickness of the border (deg)

The border thickness in mm.

# class `Cellulo::CelluloZoneCircleDistance` 

```
class Cellulo::CelluloZoneCircleDistance
  : public Cellulo::CelluloZoneCircle
```  

[CelluloZone](#classCellulo_1_1CelluloZone) Specific Class for circular zones distance determination.

Calculates the client's distance to the zone's border.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `Cellulo::CelluloZoneClient` 

```
class Cellulo::CelluloZoneClient
  : public QQuickItem
```  

Describes an object with a physical pose (e.g a robot) that may interact with [Cellulo](#namespaceCellulo) zones.

Abstract object that interacts with `[CelluloZone](#classCellulo_1_1CelluloZone)`s through a `[CelluloZoneEngine](#classCellulo_1_1CelluloZoneEngine)`. Inherit from this object (i.e if being used from QML, create the `YourObject.qml` file with `[CelluloZoneClient](#classCellulo_1_1CelluloZoneClient)` as the top object) to have your custom object interact with `[CelluloZone](#classCellulo_1_1CelluloZone)`s. For example, `[CelluloBluetooth](#classCellulo_1_1CelluloBluetooth)` already inherits from this object.

This class is **abstract**, you cannot instantiate it directly. Refer to classes derived from it.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{signal} public void `[`zoneValueChanged`](#classCellulo_1_1CelluloZoneClient_1a127e357850b2448f7addc79bab0168f5)`(QObject * zone,qreal value)` | Emitted when a zone's value with respect to this object changes.
`{signal} public void `[`poseChanged`](#classCellulo_1_1CelluloZoneClient_1abaf30200131353c16cde52b53aa68409)`(qreal x,qreal y,qreal theta)` | User is responsible for emitting this signal when this client's pose (in mm, mm, deg) changes.

## Members

#### `{signal} public void `[`zoneValueChanged`](#classCellulo_1_1CelluloZoneClient_1a127e357850b2448f7addc79bab0168f5)`(QObject * zone,qreal value)` 

Emitted when a zone's value with respect to this object changes.

#### Parameters
* `zone` Zone whose value has changed 

* `value` The new value

#### `{signal} public void `[`poseChanged`](#classCellulo_1_1CelluloZoneClient_1abaf30200131353c16cde52b53aa68409)`(qreal x,qreal y,qreal theta)` 

User is responsible for emitting this signal when this client's pose (in mm, mm, deg) changes.

#### Parameters
* `x` New x coordinate in mm 

* `y` New y coordinate in mm 

* `theta` New orientation in degrees

# class `Cellulo::CelluloZoneEngine` 

```
class Cellulo::CelluloZoneEngine
  : public QQuickItem
```  

Object that ensures `[CelluloZone](#classCellulo_1_1CelluloZone)` and `[CelluloZoneClient](#classCellulo_1_1CelluloZoneClient)` interaction.

All `[CelluloZoneClient](#classCellulo_1_1CelluloZoneClient)`s in this engine have their `zoneValueChanged()` signals emitted when the value of a `[CelluloZone](#classCellulo_1_1CelluloZone)` (within this engine) with respect to the client changes.

`[CelluloZone](#classCellulo_1_1CelluloZone)`s instantiated as children of a `[CelluloZoneEngine](#classCellulo_1_1CelluloZoneEngine)` will be automatically added to it. `[CelluloZoneClient](#classCellulo_1_1CelluloZoneClient)`s must be manually added.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} bool `[`active`](doc/doc-zone.md#classCellulo_1_1CelluloZoneEngine_1a1e2587b08c68a365d8c6dc390499589f) | Whether the zones in this engine are active, default true.
`public Q_INVOKABLE QStringList `[`getAllZoneNames`](#classCellulo_1_1CelluloZoneEngine_1a413681bb7c91dbcf200ac969ef0ae99a)`()` | Get list of names of all zones handled by this engine.
`public Q_INVOKABLE QObject * `[`getZoneByName`](#classCellulo_1_1CelluloZoneEngine_1a861ca939c835d2cf1dde8dcfe9e6a78e)`(QString name)` | Get zone handled by this engine having the corresponding name.
`public Q_INVOKABLE QVariantList `[`getZonesList`](#classCellulo_1_1CelluloZoneEngine_1a9515cf7877d12c7515012f382cc4f6a0)`()` | Returns the list of all zones in this engine.
`public Q_INVOKABLE void `[`addNewZones`](#classCellulo_1_1CelluloZoneEngine_1a9f79e986a9d71058904fe51ab563eaf6)`(QVariantList newZones)` | Adds the given list of zones to the already existing zones.
`{slot} public void `[`addNewClient`](#classCellulo_1_1CelluloZoneEngine_1af38e21f7dcad9cbfdce597144b45a7c7)`(`[`CelluloZoneClient`](#classCellulo_1_1CelluloZoneClient)` * newClient)` | Adds a new client to the engine, binds to all existing zones.
`{slot} public void `[`addNewZone`](#classCellulo_1_1CelluloZoneEngine_1a82cd4f0be60e28d5dfc28e62ad336066)`(`[`CelluloZone`](#classCellulo_1_1CelluloZone)` * newZone)` | Adds a new zone to the engine, binds to all existing clients.
`{slot} public void `[`clearZones`](#classCellulo_1_1CelluloZoneEngine_1ac350f0f16d642b3144cdbbc23588ba6a)`()` | Deletes all zones.

## Members

#### `{property} bool `[`active`](doc/doc-zone.md#classCellulo_1_1CelluloZoneEngine_1a1e2587b08c68a365d8c6dc390499589f) 

Whether the zones in this engine are active, default true.

Whether clients' poseChanged events are connected to zones; true by default.

#### `public Q_INVOKABLE QStringList `[`getAllZoneNames`](#classCellulo_1_1CelluloZoneEngine_1a413681bb7c91dbcf200ac969ef0ae99a)`()` 

Get list of names of all zones handled by this engine.

#### Returns
Names of the zones handled by this engine

#### `public Q_INVOKABLE QObject * `[`getZoneByName`](#classCellulo_1_1CelluloZoneEngine_1a861ca939c835d2cf1dde8dcfe9e6a78e)`(QString name)` 

Get zone handled by this engine having the corresponding name.

#### Parameters
* `name` Lookup name for the zone 

#### Returns
First zone handled by this engine to have this name or NULL if not found

#### `public Q_INVOKABLE QVariantList `[`getZonesList`](#classCellulo_1_1CelluloZoneEngine_1a9515cf7877d12c7515012f382cc4f6a0)`()` 

Returns the list of all zones in this engine.

#### Returns
The list of all zones

#### `public Q_INVOKABLE void `[`addNewZones`](#classCellulo_1_1CelluloZoneEngine_1a9f79e986a9d71058904fe51ab563eaf6)`(QVariantList newZones)` 

Adds the given list of zones to the already existing zones.

#### Parameters
* `newZones` New zones (QML-compatible)

#### `{slot} public void `[`addNewClient`](#classCellulo_1_1CelluloZoneEngine_1af38e21f7dcad9cbfdce597144b45a7c7)`(`[`CelluloZoneClient`](#classCellulo_1_1CelluloZoneClient)` * newClient)` 

Adds a new client to the engine, binds to all existing zones.

#### Parameters
* `newClient` Client to add

#### `{slot} public void `[`addNewZone`](#classCellulo_1_1CelluloZoneEngine_1a82cd4f0be60e28d5dfc28e62ad336066)`(`[`CelluloZone`](#classCellulo_1_1CelluloZone)` * newZone)` 

Adds a new zone to the engine, binds to all existing clients.

#### Parameters
* `newZone` Zone to add

#### `{slot} public void `[`clearZones`](#classCellulo_1_1CelluloZoneEngine_1ac350f0f16d642b3144cdbbc23588ba6a)`()` 

Deletes all zones.

# class `Cellulo::CelluloZoneJsonHandler` 

```
class Cellulo::CelluloZoneJsonHandler
  : public QObject
```  

Utilities to load/save `[CelluloZone](#classCellulo_1_1CelluloZone)`s to to/from files in JSON format.

This class is **singleton**, you can call `ThisClass.anyFunction()` and use `ThisClass.anyProperty` directly.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public static Q_INVOKABLE void `[`saveZones`](#classCellulo_1_1CelluloZoneJsonHandler_1a8d1de072d692173999dde8748aef5850)`(const QVariantList & zones,QString path)` | Save zones in JSON file.
`public static Q_INVOKABLE QVariantList `[`loadZonesQML`](#classCellulo_1_1CelluloZoneJsonHandler_1a5f7aeb79df9bcd76770f4661ed2b086e)`(QString path)` | Load zones from JSON file.

## Members

#### `public static Q_INVOKABLE void `[`saveZones`](#classCellulo_1_1CelluloZoneJsonHandler_1a8d1de072d692173999dde8748aef5850)`(const QVariantList & zones,QString path)` 

Save zones in JSON file.

#### Parameters
* `zones` Zones to be saved (QML-compatible) 

* `path` Path of the JSON file where to save the zones

#### `public static Q_INVOKABLE QVariantList `[`loadZonesQML`](#classCellulo_1_1CelluloZoneJsonHandler_1a5f7aeb79df9bcd76770f4661ed2b086e)`(QString path)` 

Load zones from JSON file.

#### Parameters
* `path` Path of the JSON file where to load the zones 

#### Returns
List of zones (QML-compatible)

# class `Cellulo::CelluloZoneLine` 

```
class Cellulo::CelluloZoneLine
  : public Cellulo::CelluloZone
```  

[CelluloZone](#classCellulo_1_1CelluloZone) Base Class for line zones.

This class is **abstract**, you cannot instantiate it directly. Refer to classes derived from it.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} float `[`x1`](doc/doc-zone.md#classCellulo_1_1CelluloZoneLine_1ac45f2632a93c3b15c876ce5465d42437) | X coordinate of the first line segment end (mm)
`{property} float `[`y1`](doc/doc-zone.md#classCellulo_1_1CelluloZoneLine_1a6d508b6f2a00934d56181c4b38555483) | Y coordinate of the first line segment end (mm)
`{property} float `[`x2`](doc/doc-zone.md#classCellulo_1_1CelluloZoneLine_1a42be2206fdbddbebc610bf2165f60b14) | X coordinate of the second line segment end (mm)
`{property} float `[`y2`](doc/doc-zone.md#classCellulo_1_1CelluloZoneLine_1a97392501f00154b302e80eb6e1ee71d1) | Y coordinate of the second line segment end (mm)

## Members

#### `{property} float `[`x1`](doc/doc-zone.md#classCellulo_1_1CelluloZoneLine_1ac45f2632a93c3b15c876ce5465d42437) 

X coordinate of the first line segment end (mm)

#### `{property} float `[`y1`](doc/doc-zone.md#classCellulo_1_1CelluloZoneLine_1a6d508b6f2a00934d56181c4b38555483) 

Y coordinate of the first line segment end (mm)

#### `{property} float `[`x2`](doc/doc-zone.md#classCellulo_1_1CelluloZoneLine_1a42be2206fdbddbebc610bf2165f60b14) 

X coordinate of the second line segment end (mm)

#### `{property} float `[`y2`](doc/doc-zone.md#classCellulo_1_1CelluloZoneLine_1a97392501f00154b302e80eb6e1ee71d1) 

Y coordinate of the second line segment end (mm)

# class `Cellulo::CelluloZoneLineSegmentDistance` 

```
class Cellulo::CelluloZoneLineSegmentDistance
  : public Cellulo::CelluloZoneLine
```  

[CelluloZone](#classCellulo_1_1CelluloZone) Specific Class for line segment distance determination.

Calculates the client's distance to the zone that is a line segment.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `Cellulo::CelluloZoneLineDistanceSigned` 

```
class Cellulo::CelluloZoneLineDistanceSigned
  : public Cellulo::CelluloZoneLine
```  

[CelluloZone](#classCellulo_1_1CelluloZone) Specific Class for signed line distance determination.

Calculates the client's (signed) distance to the zone that is an infinite line. The two points of [CelluloZoneLine](#classCellulo_1_1CelluloZoneLine) are taken as the two points that this infinite line passes through.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `Cellulo::CelluloZoneLineBorder` 

```
class Cellulo::CelluloZoneLineBorder
  : public Cellulo::CelluloZoneLine
```  

[CelluloZone](#classCellulo_1_1CelluloZone) Specific Class for determining whether a point is within a distance to an infinite line.

Calculates whether the client's position is within **borderThickness** of the zone's border, value is `0.0` or `1.0`. The two points of [CelluloZoneLine](#classCellulo_1_1CelluloZoneLine) are taken as the two points that this infinite line passes through.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} qreal `[`borderThickness`](doc/doc-zone.md#classCellulo_1_1CelluloZoneLineBorder_1a476a512012471cfdb5b54b1366d017b6) | Total thickness of the border (mm)

## Members

#### `{property} qreal `[`borderThickness`](doc/doc-zone.md#classCellulo_1_1CelluloZoneLineBorder_1a476a512012471cfdb5b54b1366d017b6) 

Total thickness of the border (mm)

The border thickness in mm.

# class `Cellulo::CelluloZonePaintedItem` 

```
class Cellulo::CelluloZonePaintedItem
  : public QQuickPaintedItem
```  

A QML compatible QQuickPaintedItem for CelluloZones.

Visual representation of a `[CelluloZone](#classCellulo_1_1CelluloZone)`; can be used to draw `[CelluloZone](#classCellulo_1_1CelluloZone)`s in e.g `Rectangle`s. Visually covers its parent (from `[0, 0]` to `[parent.width, parent.height]`), using it as a canvas and drawing the zone at the appropriate place.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} QColor `[`color`](doc/doc-zone.md#classCellulo_1_1CelluloZonePaintedItem_1a35a9316c516107c7c8f980bf89bed7aa) | The color of the drawn zone.
`{property} `[`CelluloZone`](#classCellulo_1_1CelluloZone)` `[`associatedZone`](#classCellulo_1_1CelluloZonePaintedItem_1af25ac35a56fbcfa0fa5e44d4b6bfcf30) | Associated zone.
`{property} qreal `[`physicalPlaygroundWidth`](doc/doc-zone.md#classCellulo_1_1CelluloZonePaintedItem_1afe3fb2f45c9dee29c66a8b7fc278381f) | Physical playground width that the canvas represents (in mm)
`{property} qreal `[`physicalPlaygroundHeight`](doc/doc-zone.md#classCellulo_1_1CelluloZonePaintedItem_1ae80f5f415506e5bb2f582aac41185034) | Physical playground height that the canvas represents (in mm)

## Members

#### `{property} QColor `[`color`](doc/doc-zone.md#classCellulo_1_1CelluloZonePaintedItem_1a35a9316c516107c7c8f980bf89bed7aa) 

The color of the drawn zone.

Color of the paint.

#### `{property} `[`CelluloZone`](#classCellulo_1_1CelluloZone)` `[`associatedZone`](#classCellulo_1_1CelluloZonePaintedItem_1af25ac35a56fbcfa0fa5e44d4b6bfcf30) 

Associated zone.

#### `{property} qreal `[`physicalPlaygroundWidth`](doc/doc-zone.md#classCellulo_1_1CelluloZonePaintedItem_1afe3fb2f45c9dee29c66a8b7fc278381f) 

Physical playground width that the canvas represents (in mm)

Physical playground width in mm.

#### `{property} qreal `[`physicalPlaygroundHeight`](doc/doc-zone.md#classCellulo_1_1CelluloZonePaintedItem_1ae80f5f415506e5bb2f582aac41185034) 

Physical playground height that the canvas represents (in mm)

Physical playground height in mm.

# class `Cellulo::CelluloZonePoint` 

```
class Cellulo::CelluloZonePoint
  : public Cellulo::CelluloZone
```  

[CelluloZone](#classCellulo_1_1CelluloZone) Base Class for point zones.

This class is **abstract**, you cannot instantiate it directly. Refer to classes derived from it.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} float `[`x`](doc/doc-zone.md#classCellulo_1_1CelluloZonePoint_1a77446bf66d11c3da82fdfd40d67cbb45) | X coordinate of the point (mm)
`{property} float `[`y`](doc/doc-zone.md#classCellulo_1_1CelluloZonePoint_1a9e11d95c422eb7e78bbbfd3c7e7826be) | Y coordinate of the point (mm)

## Members

#### `{property} float `[`x`](doc/doc-zone.md#classCellulo_1_1CelluloZonePoint_1a77446bf66d11c3da82fdfd40d67cbb45) 

X coordinate of the point (mm)

#### `{property} float `[`y`](doc/doc-zone.md#classCellulo_1_1CelluloZonePoint_1a9e11d95c422eb7e78bbbfd3c7e7826be) 

Y coordinate of the point (mm)

# class `Cellulo::CelluloZonePointDistance` 

```
class Cellulo::CelluloZonePointDistance
  : public Cellulo::CelluloZonePoint
```  

[CelluloZone](#classCellulo_1_1CelluloZone) Specific Class for point zones distance determination.

Calculates the client's distance to the zone.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `Cellulo::CelluloZonePolygon` 

```
class Cellulo::CelluloZonePolygon
  : public Cellulo::CelluloZone
```  

[CelluloZone](#classCellulo_1_1CelluloZone) Base Class for polygonal zones.

This class is **abstract**, you cannot instantiate it directly. Refer to classes derived from it.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} QList< QVariant > `[`vertices`](doc/doc-zone.md#classCellulo_1_1CelluloZonePolygon_1ad5fc1b6e859473d220237d98169f7ffe) | List of vertices, polygon has an edge between every `i`th and `i+1`th vertex.

## Members

#### `{property} QList< QVariant > `[`vertices`](doc/doc-zone.md#classCellulo_1_1CelluloZonePolygon_1ad5fc1b6e859473d220237d98169f7ffe) 

List of vertices, polygon has an edge between every `i`th and `i+1`th vertex.

# class `Cellulo::CelluloZoneIrregularPolygon` 

```
class Cellulo::CelluloZoneIrregularPolygon
  : public Cellulo::CelluloZonePolygon
```  

[CelluloZone](#classCellulo_1_1CelluloZone) Base Class for irregular polygonal zones.

This class is **abstract**, you cannot instantiate it directly. Refer to classes derived from it.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `Cellulo::CelluloZoneIrregularPolygonInner` 

```
class Cellulo::CelluloZoneIrregularPolygonInner
  : public Cellulo::CelluloZoneIrregularPolygon
```  

[CelluloZone](#classCellulo_1_1CelluloZone) Specific Class for irregular polygonal zones inner determination.

Calculates whether the client's position is within the irregular polygon, value is `0.0` or `1.0`.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `Cellulo::CelluloZoneIrregularPolygonBorder` 

```
class Cellulo::CelluloZoneIrregularPolygonBorder
  : public Cellulo::CelluloZoneIrregularPolygon
```  

[CelluloZone](#classCellulo_1_1CelluloZone) Specific Class for irregular polygonal zones border determination.

Calculates whether the client's position is within **borderThickness** of the zone's border, value is `0.0` or `1.0`.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} qreal `[`borderThickness`](doc/doc-zone.md#classCellulo_1_1CelluloZoneIrregularPolygonBorder_1a41cb42ea031f9c135e9807a04aea5118) | Total thickness of the border (mm)

## Members

#### `{property} qreal `[`borderThickness`](doc/doc-zone.md#classCellulo_1_1CelluloZoneIrregularPolygonBorder_1a41cb42ea031f9c135e9807a04aea5118) 

Total thickness of the border (mm)

The border thickness in mm.

# class `Cellulo::CelluloZoneIrregularPolygonDistance` 

```
class Cellulo::CelluloZoneIrregularPolygonDistance
  : public Cellulo::CelluloZoneIrregularPolygon
```  

[CelluloZone](#classCellulo_1_1CelluloZone) Specific Class for irregular polygonal zones distance determination.

Calculates the client's distance to the zone's border.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `Cellulo::CelluloZoneRegularPolygon` 

```
class Cellulo::CelluloZoneRegularPolygon
  : public Cellulo::CelluloZonePolygon
```  

Base class for regular polygon zones.

This class is **abstract**, you cannot instantiate it directly. Refer to classes derived from it.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} int `[`numEdges`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRegularPolygon_1a9dbd4d94ab5325108fe0b257dc74a1b4) | Number of edges.
`{property} float `[`x`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRegularPolygon_1a835d0a798a7234fe9006026efd1a5ae8) | X coordinate of the center (mm)
`{property} float `[`y`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRegularPolygon_1a0e4a9bd9bafad92febf227f2a8bc7c9c) | Y coordinate of the center (mm)
`{property} float `[`r`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRegularPolygon_1ae22f178d345bedaeb2653fa433b28f4c) | Radius of the enclosing circle (mm)
`{property} float `[`rotAngle`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRegularPolygon_1a45d92afd34af8621c79a1a9ef2e668f0) | Extra rotation from the initial orientation (deg)

## Members

#### `{property} int `[`numEdges`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRegularPolygon_1a9dbd4d94ab5325108fe0b257dc74a1b4) 

Number of edges.

#### `{property} float `[`x`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRegularPolygon_1a835d0a798a7234fe9006026efd1a5ae8) 

X coordinate of the center (mm)

#### `{property} float `[`y`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRegularPolygon_1a0e4a9bd9bafad92febf227f2a8bc7c9c) 

Y coordinate of the center (mm)

#### `{property} float `[`r`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRegularPolygon_1ae22f178d345bedaeb2653fa433b28f4c) 

Radius of the enclosing circle (mm)

#### `{property} float `[`rotAngle`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRegularPolygon_1a45d92afd34af8621c79a1a9ef2e668f0) 

Extra rotation from the initial orientation (deg)

# class `Cellulo::CelluloZoneRegularPolygonInner` 

```
class Cellulo::CelluloZoneRegularPolygonInner
  : public Cellulo::CelluloZoneRegularPolygon
```  

[CelluloZone](#classCellulo_1_1CelluloZone) Specific Class for regular polygonal zones inner determination.

Calculates whether the client's position is within the regular polygon, value is `0.0` or `1.0`.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `Cellulo::CelluloZoneRegularPolygonBorder` 

```
class Cellulo::CelluloZoneRegularPolygonBorder
  : public Cellulo::CelluloZoneRegularPolygon
```  

[CelluloZone](#classCellulo_1_1CelluloZone) Specific Class for regular polygonal zones border determination.

Calculates whether the client's position is within **borderThickness** of the zone's border, value is `0.0` or `1.0`.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} qreal `[`borderThickness`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRegularPolygonBorder_1af85d56687917e2d58d9b90c5c79fe814) | Total thickness of the border (mm)

## Members

#### `{property} qreal `[`borderThickness`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRegularPolygonBorder_1af85d56687917e2d58d9b90c5c79fe814) 

Total thickness of the border (mm)

The border thickness in mm.

# class `Cellulo::CelluloZoneRegularPolygonDistance` 

```
class Cellulo::CelluloZoneRegularPolygonDistance
  : public Cellulo::CelluloZoneRegularPolygon
```  

[CelluloZone](#classCellulo_1_1CelluloZone) Specific Class for regular polygonal zones distance determination.

Calculates the client's distance to the zone's border.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

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
ANGLEDIFFERENCE            | [CelluloZoneAngleDifference](doc/doc-zone.md#classCellulo_1_1CelluloZoneAngleDifference).
ANGLEINTERVALINNER            | [CelluloZoneAngleIntervalInner](doc/doc-zone.md#classCellulo_1_1CelluloZoneAngleIntervalInner).
ANGLEINTERVALBORDER            | [CelluloZoneAngleIntervalBorder](doc/doc-zone.md#classCellulo_1_1CelluloZoneAngleIntervalBorder).
ANGLEINTERVALDISTANCE            | [CelluloZoneAngleIntervalDistance](doc/doc-zone.md#classCellulo_1_1CelluloZoneAngleIntervalDistance).
CIRCLEINNER            | [CelluloZoneCircleInner](doc/doc-zone.md#classCellulo_1_1CelluloZoneCircleInner).
CIRCLEBORDER            | [CelluloZoneCircleBorder](doc/doc-zone.md#classCellulo_1_1CelluloZoneCircleBorder).
CIRCLEDISTANCE            | [CelluloZoneCircleDistance](doc/doc-zone.md#classCellulo_1_1CelluloZoneCircleDistance).
RECTANGLEINNER            | [CelluloZoneRectangleInner](doc/doc-zone.md#classCellulo_1_1CelluloZoneRectangleInner).
RECTANGLEBORDER            | [CelluloZoneRectangleBorder](doc/doc-zone.md#classCellulo_1_1CelluloZoneRectangleBorder).
RECTANGLEDISTANCE            | [CelluloZoneRectangleDistance](doc/doc-zone.md#classCellulo_1_1CelluloZoneRectangleDistance).
LINESEGMENTDISTANCE            | [CelluloZoneLineSegmentDistance](doc/doc-zone.md#classCellulo_1_1CelluloZoneLineSegmentDistance).
LINEDISTANCESIGNED            | [CelluloZoneLineDistanceSigned](doc/doc-zone.md#classCellulo_1_1CelluloZoneLineDistanceSigned).
LINEBORDER            | [CelluloZoneLineBorder](doc/doc-zone.md#classCellulo_1_1CelluloZoneLineBorder).
POINTDISTANCE            | [CelluloZonePointDistance](doc/doc-zone.md#classCellulo_1_1CelluloZonePointDistance).
RPOLYGONINNER            | [CelluloZoneRegularPolygonInner](doc/doc-zone.md#classCellulo_1_1CelluloZoneRegularPolygonInner).
RPOLYGONBORDER            | [CelluloZoneRegularPolygonBorder](doc/doc-zone.md#classCellulo_1_1CelluloZoneRegularPolygonBorder).
RPOLYGONDISTANCE            | [CelluloZoneRegularPolygonDistance](doc/doc-zone.md#classCellulo_1_1CelluloZoneRegularPolygonDistance).
IRPOLYGONINNER            | [CelluloZoneIrregularPolygonInner](doc/doc-zone.md#classCellulo_1_1CelluloZoneIrregularPolygonInner).
IRPOLYGONBORDER            | [CelluloZoneIrregularPolygonBorder](doc/doc-zone.md#classCellulo_1_1CelluloZoneIrregularPolygonBorder).
IRPOLYGONDISTANCE            | [CelluloZoneIrregularPolygonDistance](doc/doc-zone.md#classCellulo_1_1CelluloZoneIrregularPolygonDistance).
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

