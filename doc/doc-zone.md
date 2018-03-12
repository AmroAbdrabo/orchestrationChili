# group `zone` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[`Cellulo::CelluloZoneTypes`](doc/doc-zone.md#classCellulo_1_1CelluloZoneTypes) | `[CelluloZone](#classCellulo_1_1CelluloZone)` type enum and utilities.

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
RECTANGLEINNER            | [CelluloZoneRectangleInner](#classCellulo_1_1CelluloZoneRectangleInner).
RECTANGLEBORDER            | [CelluloZoneRectangleBorder](#classCellulo_1_1CelluloZoneRectangleBorder).
RECTANGLEDISTANCE            | [CelluloZoneRectangleDistance](#classCellulo_1_1CelluloZoneRectangleDistance).
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

