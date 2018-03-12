# group `zone` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[`Cellulo::CelluloZoneRectangle`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRectangle) | [CelluloZone](#classCellulo_1_1CelluloZone) Base Class for rectangular zones.
`class `[`Cellulo::CelluloZoneRectangleInner`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRectangleInner) | [CelluloZone](#classCellulo_1_1CelluloZone) Specific Class for rectangular zones inner determination; calculates whether the client's position is within the rectangle, value is `0.0` or `1.0`.
`class `[`Cellulo::CelluloZoneRectangleBorder`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRectangleBorder) | [CelluloZone](#classCellulo_1_1CelluloZone) Specific Class for rectangular zones border determination; calculates whether the client's position is within **borderThickness** of the zone's border, value is `0.0` or `1.0`.
`class `[`Cellulo::CelluloZoneRectangleDistance`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRectangleDistance) | [CelluloZone](#classCellulo_1_1CelluloZone) Specific Class for rectangular zones distance determination; calculates the client's distance to the zone's border.
`class `[`Cellulo::CelluloZoneTypes`](doc/doc-zone.md#classCellulo_1_1CelluloZoneTypes) | `[CelluloZone](#classCellulo_1_1CelluloZone)` type enum and utilities.

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
`public virtual Q_INVOKABLE bool `[`isMouseInside`](#classCellulo_1_1CelluloZoneRectangle_1a875fdd669c61b19de646fa090e48bb3f)`(QVector2D mousePosition,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Get if the mouse position is inside the zone or not.

## Members

#### `{property} float `[`x`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRectangle_1a5eda2e9d4a29010c745f3547108d4cfb) 

X coordinate of the top left corner (mm)

#### `{property} float `[`y`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRectangle_1ad0e8c8be54bbb4dcf4e8f751993088b8) 

Y coordinate of the top left corner (mm)

#### `{property} float `[`height`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRectangle_1a936828d957424f788e89152b5349b33c) 

Width of the rectangle (mm)

#### `{property} float `[`width`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRectangle_1a02f1b9f0667164115c62cad18109f96d) 

Height of the rectangle (mm)

#### `public virtual Q_INVOKABLE bool `[`isMouseInside`](#classCellulo_1_1CelluloZoneRectangle_1a875fdd669c61b19de646fa090e48bb3f)`(QVector2D mousePosition,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Get if the mouse position is inside the zone or not.

#### Parameters
* `mousePosition` (x,y) coordinates of the mouse in pixels 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

#### Returns
Whether the mouse position is inside the zone or not

# class `Cellulo::CelluloZoneRectangleInner` 

```
class Cellulo::CelluloZoneRectangleInner
  : public Cellulo::CelluloZoneRectangle
```  

[CelluloZone](#classCellulo_1_1CelluloZone) Specific Class for rectangular zones inner determination; calculates whether the client's position is within the rectangle, value is `0.0` or `1.0`.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public virtual Q_INVOKABLE float `[`calculate`](#classCellulo_1_1CelluloZoneRectangleInner_1a0a12226191bcdd77f6c3b29ea713a5a7)`(float xRobot,float yRobot,float thetaRobot)` | Calculate whether the robot lies inside this rectangular zone.

## Members

#### `public virtual Q_INVOKABLE float `[`calculate`](#classCellulo_1_1CelluloZoneRectangleInner_1a0a12226191bcdd77f6c3b29ea713a5a7)`(float xRobot,float yRobot,float thetaRobot)` 

Calculate whether the robot lies inside this rectangular zone.

This function is normally called automatically, but can be manually called as well.

#### Parameters
* `xRobot` x position of the robot 

* `yRobot` y position of the robot 

* `thetaRobot` theta position of the robot

#### Returns
1 if the robot is inside this rectangular zone 0 otherwise

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
`public virtual Q_INVOKABLE float `[`calculate`](#classCellulo_1_1CelluloZoneRectangleBorder_1abfaa27e1faf1dcf4c8fcc1892fbd2b14)`(float xRobot,float yRobot,float thetaRobot)` | Calculate whether the robot lies on the border of this rectangular zone (given the zone's margin)

## Members

#### `{property} qreal `[`borderThickness`](doc/doc-zone.md#classCellulo_1_1CelluloZoneRectangleBorder_1a1f08060c512e11e672f515f3b8d5c66a) 

Total thickness of the border (mm)

The border thickness in mm.

#### `public virtual Q_INVOKABLE float `[`calculate`](#classCellulo_1_1CelluloZoneRectangleBorder_1abfaa27e1faf1dcf4c8fcc1892fbd2b14)`(float xRobot,float yRobot,float thetaRobot)` 

Calculate whether the robot lies on the border of this rectangular zone (given the zone's margin)

This function is normally called automatically, but can be manually called as well.

#### Parameters
* `xRobot` x position of the robot 

* `yRobot` y position of the robot 

* `thetaRobot` theta position of the robot

#### Returns
1 if the robot is on the border of this rectangular zone (given the zone's margin) 0 otherwise

# class `Cellulo::CelluloZoneRectangleDistance` 

```
class Cellulo::CelluloZoneRectangleDistance
  : public Cellulo::CelluloZoneRectangle
```  

[CelluloZone](#classCellulo_1_1CelluloZone) Specific Class for rectangular zones distance determination; calculates the client's distance to the zone's border.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public virtual Q_INVOKABLE float `[`calculate`](#classCellulo_1_1CelluloZoneRectangleDistance_1a50d401b7841ca7b50a5affaa54400d71)`(float xRobot,float yRobot,float thetaRobot)` | Calculate the distance between the robot pose and the border of this rectangular zone.

## Members

#### `public virtual Q_INVOKABLE float `[`calculate`](#classCellulo_1_1CelluloZoneRectangleDistance_1a50d401b7841ca7b50a5affaa54400d71)`(float xRobot,float yRobot,float thetaRobot)` 

Calculate the distance between the robot pose and the border of this rectangular zone.

This function is normally called automatically, but can be manually called as well.

#### Parameters
* `xRobot` x position of the robot 

* `yRobot` y position of the robot 

* `thetaRobot` theta position of the robot

#### Returns
the distance between the robot pose and the border of this rectangular zone

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

