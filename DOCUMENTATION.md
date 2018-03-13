

#### CelluloZoneAngleDifference

Calculates the signed difference of the client orientation angles to the zone's angle, value is in `]-180, 180]`.

**Properties:**

>  - **angle** : `real` - Zone's angle (deg)




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
