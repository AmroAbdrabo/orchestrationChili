







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
