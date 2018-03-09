# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`define `[`CELLULO_ENUM_DECL`](#CelluloEnumDecl_8h_1a26ad67159d888e33763906c926827c76)            | 
`define `[`NANOSVG_IMPLEMENTATION`](#CelluloSVGUtil_8cpp_1a13c9addcfac4e47276eb19eca89158a6)            | 
`define `[`NANOSVG_IMPLEMENTATION`](#example1_8c_1a13c9addcfac4e47276eb19eca89158a6)            | 
`define `[`STB_IMAGE_WRITE_IMPLEMENTATION`](#example2_8c_1aefe397a94e8feddc652f92ef40ce9597)            | 
`define `[`NANOSVG_IMPLEMENTATION`](#example2_8c_1a13c9addcfac4e47276eb19eca89158a6)            | 
`define `[`NANOSVGRAST_IMPLEMENTATION`](#example2_8c_1a2e25595d9bb04cdd08698c4c5735296a)            | 
`enum `[`NSVGpaintType`](#nanosvg_8h_1a4aece070768ae0c9f7fdd9527edf6504)            | 
`enum `[`NSVGspreadType`](#nanosvg_8h_1aef9802b566371c370956a08ea4368be7)            | 
`enum `[`NSVGlineJoin`](#nanosvg_8h_1af940ce6fa97441064aa862955f93772d)            | 
`enum `[`NSVGlineCap`](#nanosvg_8h_1a2911ee5855676435dae5766698a5924b)            | 
`enum `[`NSVGfillRule`](#nanosvg_8h_1a1585c32c79f6780b6985ae560fa1055e)            | 
`enum `[`NSVGflags`](#nanosvg_8h_1a442ffb30d60efc73c39713a8f2c819a5)            | 
`public static float `[`distPtSeg`](#example1_8c_1a499adcb2997a3b1749a21bad949c7dbc)`(float x,float y,float px,float py,float qx,float qy)`            | 
`public static void `[`cubicBez`](#example1_8c_1a18cbd50f125049978058130dc944f6c4)`(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4,float tol,int level)`            | 
`public void `[`drawPath`](#example1_8c_1a2e96f10d2180c56e4bec8a9dd7bc7e9c)`(float * pts,int npts,char closed,float tol)`            | 
`public void `[`drawControlPts`](#example1_8c_1a1ce9340a01b52bc4821f5a0f7d6bfbb4)`(float * pts,int npts)`            | 
`public void `[`drawframe`](#example1_8c_1a615a6f7df90385bf58a4025d24c58496)`(GLFWwindow * window)`            | 
`public void `[`resizecb`](#example1_8c_1a6805dd9d7171760401e624d803c28649)`(GLFWwindow * window,int width,int height)`            | 
`public int `[`main`](#example1_8c_1ae66f6b31b5ad750f1fe042a706a4e3d4)`()`            | 
`public int `[`main`](#example2_8c_1ae66f6b31b5ad750f1fe042a706a4e3d4)`()`            | 
`public int `[`stbi_write_png`](#stb__image__write_8h_1aace2f6525144ac808cec21600cfe4498)`(char const * filename,int w,int h,int comp,const void * data,int stride_in_bytes)`            | 
`public int `[`stbi_write_bmp`](#stb__image__write_8h_1adb12037a58d9e12e7a58c479b8e0ab8e)`(char const * filename,int w,int h,int comp,const void * data)`            | 
`public int `[`stbi_write_tga`](#stb__image__write_8h_1a3ae29b478d6da0d99705825591f6d20b)`(char const * filename,int w,int h,int comp,const void * data)`            | 
`public `[`NSVGimage`](#structNSVGimage)` * `[`nsvgParseFromFile`](#nanosvg_8h_1aa48432d73cd5a5ec87642c15cc04f7c4)`(const char * filename,const char * units,float dpi)`            | 
`public `[`NSVGimage`](#structNSVGimage)` * `[`nsvgParse`](#nanosvg_8h_1a144a297a168d0f04b3f25b0d6b121627)`(char * input,const char * units,float dpi)`            | 
`public void `[`nsvgDelete`](#nanosvg_8h_1ae474f7838b9272736a6945cdb73aad1f)`(`[`NSVGimage`](#structNSVGimage)` * image)`            | 
`public NSVGrasterizer * `[`nsvgCreateRasterizer`](#nanosvgrast_8h_1a73136edf2e23b72474802d862a1dcd82)`()`            | 
`public void `[`nsvgRasterize`](#nanosvgrast_8h_1a73d8a67a24e08c96ec8c2b823d8a29b2)`(NSVGrasterizer * r,`[`NSVGimage`](#structNSVGimage)` * image,float tx,float ty,float scale,unsigned char * dst,int w,int h,int stride)`            | 
`public void `[`nsvgDeleteRasterizer`](#nanosvgrast_8h_1ae2ace40cfac53302ba8856d584872734)`(NSVGrasterizer *)`            | 
`namespace `[`Cellulo`](#namespaceCellulo) | 
`class `[`CameraFrameImageProvider`](#classCameraFrameImageProvider) | QImage provider from QByteArray.
`class `[`CelluloBluetooth`](#classCelluloBluetooth) | Bluetooth communicator for a Cellulo robot.
`class `[`CelluloBluetoothEMP`](#classCelluloBluetoothEMP) | 
`class `[`CelluloBluetoothEnums`](#classCelluloBluetoothEnums) | Wrapper containing all the enums of [CelluloBluetooth](#classCelluloBluetooth).
`class `[`CelluloBluetoothPacket`](#classCelluloBluetoothPacket) | Bluetooth communicator for a Cellulo robot.
`class `[`CelluloBluetoothScanner`](#classCelluloBluetoothScanner) | 
`class `[`CelluloCommUtil`](#classCelluloCommUtil) | 
`class `[`CelluloLocalRelayClient`](#classCelluloLocalRelayClient) | 
`class `[`CelluloLocalRelayServer`](#classCelluloLocalRelayServer) | 
`class `[`CelluloMathUtil`](#classCelluloMathUtil) | 
`class `[`CelluloRelayClient`](#classCelluloRelayClient) | 
`class `[`CelluloRelayServer`](#classCelluloRelayServer) | 
`class `[`CelluloRobotPoolClient`](#classCelluloRobotPoolClient) | 
`class `[`CelluloSVGUtil`](#classCelluloSVGUtil) | 
`class `[`CelluloSystemUtil`](#classCelluloSystemUtil) | 
`class `[`CelluloTcpRelayClient`](#classCelluloTcpRelayClient) | 
`class `[`CelluloTcpRelayServer`](#classCelluloTcpRelayServer) | 
`class `[`CelluloUIUtil`](#classCelluloUIUtil) | 
`class `[`CelluloZone`](#classCelluloZone) | [CelluloZone](#classCelluloZone) Base Class for zones.
`class `[`CelluloZoneAngle`](#classCelluloZoneAngle) | Describes a single angle.
`class `[`CelluloZoneAngleDifference`](#classCelluloZoneAngleDifference) | Describes an angular zone sensitive to the client angle difference.
`class `[`CelluloZoneAngleInterval`](#classCelluloZoneAngleInterval) | Describes an angular interval.
`class `[`CelluloZoneAngleIntervalBorder`](#classCelluloZoneAngleIntervalBorder) | Describes an angular zone sensitive to the client angle being on the border of the interval.
`class `[`CelluloZoneAngleIntervalDistance`](#classCelluloZoneAngleIntervalDistance) | Describes an angular zone sensitive to the client orientation distance to the interval.
`class `[`CelluloZoneAngleIntervalInner`](#classCelluloZoneAngleIntervalInner) | Describes an angular zone sensitive to the client angle being in/out of the interval.
`class `[`CelluloZoneCircle`](#classCelluloZoneCircle) | [CelluloZone](#classCelluloZone) Base Class for circular zones.
`class `[`CelluloZoneCircleBorder`](#classCelluloZoneCircleBorder) | [CelluloZone](#classCelluloZone) Specific Class for circular zones border determination.
`class `[`CelluloZoneCircleDistance`](#classCelluloZoneCircleDistance) | [CelluloZone](#classCelluloZone) Specific Class for circular zones distance determination.
`class `[`CelluloZoneCircleInner`](#classCelluloZoneCircleInner) | [CelluloZone](#classCelluloZone) Specific Class for circular zones inner determination.
`class `[`CelluloZoneClient`](#classCelluloZoneClient) | Describes an object with a physical pose (e.g a robot) that may interact with Cellulo zones.
`class `[`CelluloZoneEngine`](#classCelluloZoneEngine) | 
`class `[`CelluloZoneIrregularPolygon`](#classCelluloZoneIrregularPolygon) | [CelluloZone](#classCelluloZone) Base Class for irregular polygonal zones.
`class `[`CelluloZoneIrregularPolygonBorder`](#classCelluloZoneIrregularPolygonBorder) | [CelluloZone](#classCelluloZone) Specific Class for irregular polygonal zones border determination.
`class `[`CelluloZoneIrregularPolygonDistance`](#classCelluloZoneIrregularPolygonDistance) | [CelluloZone](#classCelluloZone) Specific Class for irregular polygonal zones distance determination.
`class `[`CelluloZoneIrregularPolygonInner`](#classCelluloZoneIrregularPolygonInner) | [CelluloZone](#classCelluloZone) Specific Class for irregular polygonal zones inner determination.
`class `[`CelluloZoneJsonHandler`](#classCelluloZoneJsonHandler) | 
`class `[`CelluloZoneLine`](#classCelluloZoneLine) | [CelluloZone](#classCelluloZone) Base Class for line zones.
`class `[`CelluloZoneLineBorder`](#classCelluloZoneLineBorder) | [CelluloZone](#classCelluloZone) Specific Class for determining whether a point is within a distance to an infinite line.
`class `[`CelluloZoneLineDistanceSigned`](#classCelluloZoneLineDistanceSigned) | [CelluloZone](#classCelluloZone) Specific Class for signed line distance determination.
`class `[`CelluloZoneLineSegmentDistance`](#classCelluloZoneLineSegmentDistance) | [CelluloZone](#classCelluloZone) Specific Class for line segment distance determination.
`class `[`CelluloZonePaintedItem`](#classCelluloZonePaintedItem) | A QML compatible QQuickPaintedItem for CelluloZones.
`class `[`CelluloZonePoint`](#classCelluloZonePoint) | [CelluloZone](#classCelluloZone) Base Class for point zones.
`class `[`CelluloZonePointDistance`](#classCelluloZonePointDistance) | [CelluloZone](#classCelluloZone) Specific Class for point zones distance determination.
`class `[`CelluloZonePolyBezier`](#classCelluloZonePolyBezier) | [CelluloZone](#classCelluloZone) Base class for composite cubic Bézier curve.
`class `[`CelluloZonePolyBezierBorder`](#classCelluloZonePolyBezierBorder) | Calculates whether the client is on the border of a composite Bézier curve.
`class `[`CelluloZonePolyBezierClosestT`](#classCelluloZonePolyBezierClosestT) | Calculates the parameter t of the closest point on a composite Bézier curve.
`class `[`CelluloZonePolyBezierDistance`](#classCelluloZonePolyBezierDistance) | Calculates the distance to a composite Bézier curve.
`class `[`CelluloZonePolyBezierInner`](#classCelluloZonePolyBezierInner) | Calculates whether the client is within the composite Bézier curve.
`class `[`CelluloZonePolyBezierXT`](#classCelluloZonePolyBezierXT) | Calculates the parameter t of the point on the composite Bézier curve with the same x coordinate as the client.
`class `[`CelluloZonePolyBezierYT`](#classCelluloZonePolyBezierYT) | Calculates the parameter t of the point on the composite Bézier curve with the same y coordinate as the client.
`class `[`CelluloZonePolygon`](#classCelluloZonePolygon) | [CelluloZone](#classCelluloZone) Base Class for polygonal zones.
`class `[`CelluloZoneRectangle`](#classCelluloZoneRectangle) | [CelluloZone](#classCelluloZone) Base Class for rectangular zones.
`class `[`CelluloZoneRectangleBorder`](#classCelluloZoneRectangleBorder) | [CelluloZone](#classCelluloZone) Specific Class for rectangular zones border determination.
`class `[`CelluloZoneRectangleDistance`](#classCelluloZoneRectangleDistance) | [CelluloZone](#classCelluloZone) Specific Class for rectangular zones distance determination.
`class `[`CelluloZoneRectangleInner`](#classCelluloZoneRectangleInner) | [CelluloZone](#classCelluloZone) Specific Class for rectangular zones inner determination.
`class `[`CelluloZoneRegularPolygon`](#classCelluloZoneRegularPolygon) | 
`class `[`CelluloZoneRegularPolygonBorder`](#classCelluloZoneRegularPolygonBorder) | [CelluloZone](#classCelluloZone) Specific Class for regular polygonal zones border determination.
`class `[`CelluloZoneRegularPolygonDistance`](#classCelluloZoneRegularPolygonDistance) | [CelluloZone](#classCelluloZone) Specific Class for regular polygonal zones distance determination.
`class `[`CelluloZoneRegularPolygonInner`](#classCelluloZoneRegularPolygonInner) | [CelluloZone](#classCelluloZone) Specific Class for regular polygonal zones inner determination.
`class `[`CelluloZoneTypes`](#classCelluloZoneTypes) | 
`class `[`CubicBezier`](#classCubicBezier) | Describes a cubic Bézier curve B(t) = (1 - t)^3*p0 + 3*(1 - t)^2*t*p1 + 3*(1 - t)*t^2*p2 + t^3*p3.
`class `[`TranslationTool`](#classTranslationTool) | Tool to provide translation for entire app.
`struct `[`NSVGgradient`](#structNSVGgradient) | 
`struct `[`NSVGgradientStop`](#structNSVGgradientStop) | 
`struct `[`NSVGimage`](#structNSVGimage) | 
`struct `[`NSVGpaint`](#structNSVGpaint) | 
`struct `[`NSVGpath`](#structNSVGpath) | 
`struct `[`NSVGshape`](#structNSVGshape) | 

## Members

#### `define `[`CELLULO_ENUM_DECL`](#CelluloEnumDecl_8h_1a26ad67159d888e33763906c926827c76) 

#### `define `[`NANOSVG_IMPLEMENTATION`](#CelluloSVGUtil_8cpp_1a13c9addcfac4e47276eb19eca89158a6) 

#### `define `[`NANOSVG_IMPLEMENTATION`](#example1_8c_1a13c9addcfac4e47276eb19eca89158a6) 

#### `define `[`STB_IMAGE_WRITE_IMPLEMENTATION`](#example2_8c_1aefe397a94e8feddc652f92ef40ce9597) 

#### `define `[`NANOSVG_IMPLEMENTATION`](#example2_8c_1a13c9addcfac4e47276eb19eca89158a6) 

#### `define `[`NANOSVGRAST_IMPLEMENTATION`](#example2_8c_1a2e25595d9bb04cdd08698c4c5735296a) 

#### `enum `[`NSVGpaintType`](#nanosvg_8h_1a4aece070768ae0c9f7fdd9527edf6504) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
NSVG_PAINT_NONE            | 
NSVG_PAINT_COLOR            | 
NSVG_PAINT_LINEAR_GRADIENT            | 
NSVG_PAINT_RADIAL_GRADIENT            | 

#### `enum `[`NSVGspreadType`](#nanosvg_8h_1aef9802b566371c370956a08ea4368be7) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
NSVG_SPREAD_PAD            | 
NSVG_SPREAD_REFLECT            | 
NSVG_SPREAD_REPEAT            | 

#### `enum `[`NSVGlineJoin`](#nanosvg_8h_1af940ce6fa97441064aa862955f93772d) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
NSVG_JOIN_MITER            | 
NSVG_JOIN_ROUND            | 
NSVG_JOIN_BEVEL            | 

#### `enum `[`NSVGlineCap`](#nanosvg_8h_1a2911ee5855676435dae5766698a5924b) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
NSVG_CAP_BUTT            | 
NSVG_CAP_ROUND            | 
NSVG_CAP_SQUARE            | 

#### `enum `[`NSVGfillRule`](#nanosvg_8h_1a1585c32c79f6780b6985ae560fa1055e) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
NSVG_FILLRULE_NONZERO            | 
NSVG_FILLRULE_EVENODD            | 

#### `enum `[`NSVGflags`](#nanosvg_8h_1a442ffb30d60efc73c39713a8f2c819a5) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
NSVG_FLAGS_VISIBLE            | 

#### `public static float `[`distPtSeg`](#example1_8c_1a499adcb2997a3b1749a21bad949c7dbc)`(float x,float y,float px,float py,float qx,float qy)` 

#### `public static void `[`cubicBez`](#example1_8c_1a18cbd50f125049978058130dc944f6c4)`(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4,float tol,int level)` 

#### `public void `[`drawPath`](#example1_8c_1a2e96f10d2180c56e4bec8a9dd7bc7e9c)`(float * pts,int npts,char closed,float tol)` 

#### `public void `[`drawControlPts`](#example1_8c_1a1ce9340a01b52bc4821f5a0f7d6bfbb4)`(float * pts,int npts)` 

#### `public void `[`drawframe`](#example1_8c_1a615a6f7df90385bf58a4025d24c58496)`(GLFWwindow * window)` 

#### `public void `[`resizecb`](#example1_8c_1a6805dd9d7171760401e624d803c28649)`(GLFWwindow * window,int width,int height)` 

#### `public int `[`main`](#example1_8c_1ae66f6b31b5ad750f1fe042a706a4e3d4)`()` 

#### `public int `[`main`](#example2_8c_1ae66f6b31b5ad750f1fe042a706a4e3d4)`()` 

#### `public int `[`stbi_write_png`](#stb__image__write_8h_1aace2f6525144ac808cec21600cfe4498)`(char const * filename,int w,int h,int comp,const void * data,int stride_in_bytes)` 

#### `public int `[`stbi_write_bmp`](#stb__image__write_8h_1adb12037a58d9e12e7a58c479b8e0ab8e)`(char const * filename,int w,int h,int comp,const void * data)` 

#### `public int `[`stbi_write_tga`](#stb__image__write_8h_1a3ae29b478d6da0d99705825591f6d20b)`(char const * filename,int w,int h,int comp,const void * data)` 

#### `public `[`NSVGimage`](#structNSVGimage)` * `[`nsvgParseFromFile`](#nanosvg_8h_1aa48432d73cd5a5ec87642c15cc04f7c4)`(const char * filename,const char * units,float dpi)` 

#### `public `[`NSVGimage`](#structNSVGimage)` * `[`nsvgParse`](#nanosvg_8h_1a144a297a168d0f04b3f25b0d6b121627)`(char * input,const char * units,float dpi)` 

#### `public void `[`nsvgDelete`](#nanosvg_8h_1ae474f7838b9272736a6945cdb73aad1f)`(`[`NSVGimage`](#structNSVGimage)` * image)` 

#### `public NSVGrasterizer * `[`nsvgCreateRasterizer`](#nanosvgrast_8h_1a73136edf2e23b72474802d862a1dcd82)`()` 

#### `public void `[`nsvgRasterize`](#nanosvgrast_8h_1a73d8a67a24e08c96ec8c2b823d8a29b2)`(NSVGrasterizer * r,`[`NSVGimage`](#structNSVGimage)` * image,float tx,float ty,float scale,unsigned char * dst,int w,int h,int stride)` 

#### `public void `[`nsvgDeleteRasterizer`](#nanosvgrast_8h_1ae2ace40cfac53302ba8856d584872734)`(NSVGrasterizer *)` 

# namespace `Cellulo` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[`Cellulo::CelluloRobot`](#classCellulo_1_1CelluloRobot) | The main object that represents a Cellulo robot. Inherits from `[CelluloBluetooth](#classCelluloBluetooth)` and has all its functionalities (not listed here).
`class `[`Cellulo::MacAddrSelector`](#classCellulo_1_1MacAddrSelector) | MAC address selection GUI.
`class `[`Cellulo::Toast`](#classCellulo_1_1Toast) | An Android-like timed message text in a box that selfdestroys when finished if desired.
`class `[`Cellulo::ToastManager`](#classCellulo_1_1ToastManager) | Manager that creates Toasts dynamically.

# class `Cellulo::CelluloRobot` 

```
class Cellulo::CelluloRobot
  : public CelluloBluetooth
```  

The main object that represents a Cellulo robot. Inherits from `[CelluloBluetooth](#classCelluloBluetooth)` and has all its functionalities (not listed here).

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} QVector3D `[`vxyw`](#classCellulo_1_1CelluloRobot_1a3ff41aa3eaa381074e5553a126de3ce0) | Robot's estimated velocity in mm/s, mm/s, rad/s, read-only.
`{property} qreal `[`vx`](#classCellulo_1_1CelluloRobot_1a88f98737ed629ece9b4ded6d69f2090d) | Robot's estimated X velocity in mm/s, read-only.
`{property} qreal `[`vy`](#classCellulo_1_1CelluloRobot_1ae34e11c148c9a77dacf1fc94af910153) | Robot's estimated Y velocity in mm/s, read-only.
`{property} qreal `[`w`](#classCellulo_1_1CelluloRobot_1adba256d1ff2391f395d99dacd3111b5f) | Robot's estimated angular velocity in rad/s, read-only.
`{property} bool `[`poseVelControlEnabled`](#classCellulo_1_1CelluloRobot_1a3b59966b09c1f1b81d090aa1239de383) | Whether the simultaneous pose/velocity is enabled, must be set by the user, default false.
`{property} int `[`poseVelControlPeriod`](#classCellulo_1_1CelluloRobot_1ae9623a6305f54063ac903d13aefb49f1) | Desired pose/velocity control period in ms, set to 0 for highest possible frequency, default 20.
`{property} QVector3D `[`poseVelControlKGoalVel`](#classCellulo_1_1CelluloRobot_1afd3187099bb2b39dc99967e0631d4fd2) | Goal velocity coefficients when tracking pose/velocity, default (0.9, 0.9, 0.9), do not change if you don't have a good reason.
`{property} QVector3D `[`poseVelControlKGoalVelErr`](#classCellulo_1_1CelluloRobot_1ad0bd66a4a9b1744517a744e4470ec492) | Goal velocity error coefficients when tracking pose/velocity, default (0.2, 0.2, 0.2), do not change if you don't have a good reason.
`{property} QVector3D `[`poseVelControlKGoalPoseErr`](#classCellulo_1_1CelluloRobot_1a0461ff18bdf125f1587ff616368db7c2) | Goal pose error coefficients when tracking pose/velocity, default (2.0, 2.0, 2.3), do not change if you don't have a good reason.
`{property} QList< bool > `[`keysTouched`](#classCellulo_1_1CelluloRobot_1a93d1d8408926e0be31885b4c57afb768) | Whether the 6 keys are touched.
`{property} QList< bool > `[`keysLongTouched`](#classCellulo_1_1CelluloRobot_1ab2688290d750b53f9bf958c65dd70ff0) | Whether the 6 keys are long touched.
`{signal} public void `[`nextGoalPoseVelRequested`](#classCellulo_1_1CelluloRobot_1a9d942783a095a74edf14065de5e6e529)`(qreal deltaTime)` | Emitted when the controller needs the next goal pose and velocity.
`{slot} public void `[`setGoalPoseAndVelocity`](#classCellulo_1_1CelluloRobot_1a1594ddde1c1acedfa9b75b86da0c6148)`(qreal x,qreal y,qreal theta,qreal Vx,qreal Vy,qreal w,bool xEnabled,bool yEnabled,bool thetaEnabled)` | Sets the simultaneous pose and velocity goal of the robot, i.e the robot tries to be at the pose and move with the desired velocity while there.

## Members

#### `{property} QVector3D `[`vxyw`](#classCellulo_1_1CelluloRobot_1a3ff41aa3eaa381074e5553a126de3ce0) 

Robot's estimated velocity in mm/s, mm/s, rad/s, read-only.

Robot velocities: x,y in mm/s, z in rad/s (representing w)

#### `{property} qreal `[`vx`](#classCellulo_1_1CelluloRobot_1a88f98737ed629ece9b4ded6d69f2090d) 

Robot's estimated X velocity in mm/s, read-only.

#### `{property} qreal `[`vy`](#classCellulo_1_1CelluloRobot_1ae34e11c148c9a77dacf1fc94af910153) 

Robot's estimated Y velocity in mm/s, read-only.

#### `{property} qreal `[`w`](#classCellulo_1_1CelluloRobot_1adba256d1ff2391f395d99dacd3111b5f) 

Robot's estimated angular velocity in rad/s, read-only.

#### `{property} bool `[`poseVelControlEnabled`](#classCellulo_1_1CelluloRobot_1a3b59966b09c1f1b81d090aa1239de383) 

Whether the simultaneous pose/velocity is enabled, must be set by the user, default false.

Whether the simultaneous pose and velocity controller is enabled, must be enabled by the user.

#### `{property} int `[`poseVelControlPeriod`](#classCellulo_1_1CelluloRobot_1ae9623a6305f54063ac903d13aefb49f1) 

Desired pose/velocity control period in ms, set to 0 for highest possible frequency, default 20.

Desired pose/velocity control period in ms, set to 0 for highest possible frequency.

#### `{property} QVector3D `[`poseVelControlKGoalVel`](#classCellulo_1_1CelluloRobot_1afd3187099bb2b39dc99967e0631d4fd2) 

Goal velocity coefficients when tracking pose/velocity, default (0.9, 0.9, 0.9), do not change if you don't have a good reason.

Goal velocity coefficients when tracking pose/velocity.

#### `{property} QVector3D `[`poseVelControlKGoalVelErr`](#classCellulo_1_1CelluloRobot_1ad0bd66a4a9b1744517a744e4470ec492) 

Goal velocity error coefficients when tracking pose/velocity, default (0.2, 0.2, 0.2), do not change if you don't have a good reason.

Goal velocity error coefficients when tracking pose/velocity.

#### `{property} QVector3D `[`poseVelControlKGoalPoseErr`](#classCellulo_1_1CelluloRobot_1a0461ff18bdf125f1587ff616368db7c2) 

Goal pose error coefficients when tracking pose/velocity, default (2.0, 2.0, 2.3), do not change if you don't have a good reason.

Goal pose error coefficients when tracking pose/velocity.

#### `{property} QList< bool > `[`keysTouched`](#classCellulo_1_1CelluloRobot_1a93d1d8408926e0be31885b4c57afb768) 

Whether the 6 keys are touched.

Whether keys are touched.

#### `{property} QList< bool > `[`keysLongTouched`](#classCellulo_1_1CelluloRobot_1ab2688290d750b53f9bf958c65dd70ff0) 

Whether the 6 keys are long touched.

Whether keys are touched.

#### `{signal} public void `[`nextGoalPoseVelRequested`](#classCellulo_1_1CelluloRobot_1a9d942783a095a74edf14065de5e6e529)`(qreal deltaTime)` 

Emitted when the controller needs the next goal pose and velocity.

Upon receiving this signal, [setGoalPoseAndVelocity()](#classCellulo_1_1CelluloRobot_1a1594ddde1c1acedfa9b75b86da0c6148) should be called by the user if a user control loop that cycles on each received pose of the robot is present.

#### Parameters
* `deltaTime` Delta time in milliseconds that should be used if a controller differentiates or integrates in a loop triggered by this signal

#### `{slot} public void `[`setGoalPoseAndVelocity`](#classCellulo_1_1CelluloRobot_1a1594ddde1c1acedfa9b75b86da0c6148)`(qreal x,qreal y,qreal theta,qreal Vx,qreal Vy,qreal w,bool xEnabled,bool yEnabled,bool thetaEnabled)` 

Sets the simultaneous pose and velocity goal of the robot, i.e the robot tries to be at the pose and move with the desired velocity while there.

#### Parameters
* `x` X coordinate (larger than 0mm) 

* `y` Y coordinate (larger than 0mm) 

* `theta` Orientation (between -180 degrees and 180 degrees) 

* `Vx` X velocity (between -185 mm/s and and 185 mm/s) 

* `Vy` Y velocity (between -185 mm/s and and 185 mm/s) 

* `w` Angular velocity (between -7.5 rad/s and 7.5 rad/s) 

* `xEnabled` Whether to enable control on x, default true 

* `yEnabled` Whether to enable control on y, default true 

* `thetaEnabled` Whether to enable control on theta, default true

# class `Cellulo::MacAddrSelector` 

```
class Cellulo::MacAddrSelector
  : public Row
```  

MAC address selection GUI.

TODO: Replace selectedAddress, connectionStatus, connectRequested() and [disconnectRequested()](#classCellulo_1_1MacAddrSelector_1aa22b77041e3d02c3dbc2489b0a1af4a5) with property [CelluloBluetooth](#classCelluloBluetooth) robot: null

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} var `[`addresses`](#classCellulo_1_1MacAddrSelector_1ad027dd1f78e6a8212db4c7e9f43c8a42) | List of possible MAC addresses, set by the user.
`{property} string `[`selectedAddress`](#classCellulo_1_1MacAddrSelector_1a7c34aa5cc712e4f1563ab2dc9f980a92) | Currently selected addresses.
`{property} string `[`selectedLocalAdapterAddress`](#classCellulo_1_1MacAddrSelector_1a48231dcf6a4bd1a7af8d80391c1005e6) | Currently selected local adapter address (only available in Linux)
`{property} var `[`connectionStatus`](#classCellulo_1_1MacAddrSelector_1a90ee86283f522a64ab6e37fe9f6a9086) | Current connection status to display, set by the user.
`{property} bool `[`linux`](#classCellulo_1_1MacAddrSelector_1a7d093d966953210526f323b71a2f58ab) | < Emitted when the disconnect button is pressed
`{property} var `[`localAdapterAddresses`](#classCellulo_1_1MacAddrSelector_1a6f89879452ec59e45cfde26247ccca60) | 
`public void `[`selectAddress`](#classCellulo_1_1MacAddrSelector_1aa40b3137da0f66330b2413cdab749cb0)`(address)` | Selects the given address if it exists in the list of addresses.
`public void `[`selectLocalAdapterAddress`](#classCellulo_1_1MacAddrSelector_1afee2136e8f6fa1a94144d1b627b13ae7)`(address)` | Selects the given local adapter address if it exists in the list of addresses.
`public void `[`em`](#classCellulo_1_1MacAddrSelector_1a67881675d971f56473190336de94d9c4)`(x)` | 
`{signal} public void `[`connectRequested`](#classCellulo_1_1MacAddrSelector_1aa4aaeebaa7f611cb7a8f05c3f3477d16)`()` | 
`{signal} public void `[`disconnectRequested`](#classCellulo_1_1MacAddrSelector_1aa22b77041e3d02c3dbc2489b0a1af4a5)`()` | < Emitted when the connect button is pressed

## Members

#### `{property} var `[`addresses`](#classCellulo_1_1MacAddrSelector_1ad027dd1f78e6a8212db4c7e9f43c8a42) 

List of possible MAC addresses, set by the user.

#### `{property} string `[`selectedAddress`](#classCellulo_1_1MacAddrSelector_1a7c34aa5cc712e4f1563ab2dc9f980a92) 

Currently selected addresses.

This property is read-only

#### `{property} string `[`selectedLocalAdapterAddress`](#classCellulo_1_1MacAddrSelector_1a48231dcf6a4bd1a7af8d80391c1005e6) 

Currently selected local adapter address (only available in Linux)

This property is read-only

#### `{property} var `[`connectionStatus`](#classCellulo_1_1MacAddrSelector_1a90ee86283f522a64ab6e37fe9f6a9086) 

Current connection status to display, set by the user.

#### `{property} bool `[`linux`](#classCellulo_1_1MacAddrSelector_1a7d093d966953210526f323b71a2f58ab) 

< Emitted when the disconnect button is pressed

#### `{property} var `[`localAdapterAddresses`](#classCellulo_1_1MacAddrSelector_1a6f89879452ec59e45cfde26247ccca60) 

#### `public void `[`selectAddress`](#classCellulo_1_1MacAddrSelector_1aa40b3137da0f66330b2413cdab749cb0)`(address)` 

Selects the given address if it exists in the list of addresses.

#### Parameters
* `{string}` address Address to look for in the list of addresses

#### `public void `[`selectLocalAdapterAddress`](#classCellulo_1_1MacAddrSelector_1afee2136e8f6fa1a94144d1b627b13ae7)`(address)` 

Selects the given local adapter address if it exists in the list of addresses.

#### Parameters
* `{string}` address Address to look for in the list of addresses

#### `public void `[`em`](#classCellulo_1_1MacAddrSelector_1a67881675d971f56473190336de94d9c4)`(x)` 

#### `{signal} public void `[`connectRequested`](#classCellulo_1_1MacAddrSelector_1aa4aaeebaa7f611cb7a8f05c3f3477d16)`()` 

#### `{signal} public void `[`disconnectRequested`](#classCellulo_1_1MacAddrSelector_1aa22b77041e3d02c3dbc2489b0a1af4a5)`()` 

< Emitted when the connect button is pressed

# class `Cellulo::Toast` 

```
class Cellulo::Toast
  : public Rectangle
```  

An Android-like timed message text in a box that selfdestroys when finished if desired.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} bool `[`selfDestroying`](#classCellulo_1_1Toast_1a670947dec5e4993ccb5f3224e5808c90) | Whether this [Toast](#classCellulo_1_1Toast) will selfdestroy when it is finished.
`{property} real `[`time`](#classCellulo_1_1Toast_1aea18ccc79916fcdec87b67a3d97081e8) | Private
`{property} real `[`defaultTime`](#classCellulo_1_1Toast_1a54408c5d328293e61f88696c157471b8) | This property is read-only
`{property} real `[`fadeTime`](#classCellulo_1_1Toast_1a334c1084a4073e60e2dacbd1a2cbf6d3) | This property is read-only
`{property} real `[`margin`](#classCellulo_1_1Toast_1ad7c0b5c0adacd33145e9e3d90c62d2a5) | 
`public void `[`show`](#classCellulo_1_1Toast_1ad131e877177697e7e5f594fd6f47cf52)`(text,duration)` | Shows this [Toast](#classCellulo_1_1Toast).

## Members

#### `{property} bool `[`selfDestroying`](#classCellulo_1_1Toast_1a670947dec5e4993ccb5f3224e5808c90) 

Whether this [Toast](#classCellulo_1_1Toast) will selfdestroy when it is finished.

#### `{property} real `[`time`](#classCellulo_1_1Toast_1aea18ccc79916fcdec87b67a3d97081e8) 

Private

#### `{property} real `[`defaultTime`](#classCellulo_1_1Toast_1a54408c5d328293e61f88696c157471b8) 

This property is read-only

#### `{property} real `[`fadeTime`](#classCellulo_1_1Toast_1a334c1084a4073e60e2dacbd1a2cbf6d3) 

This property is read-only

#### `{property} real `[`margin`](#classCellulo_1_1Toast_1ad7c0b5c0adacd33145e9e3d90c62d2a5) 

#### `public void `[`show`](#classCellulo_1_1Toast_1ad131e877177697e7e5f594fd6f47cf52)`(text,duration)` 

Shows this [Toast](#classCellulo_1_1Toast).

Public 
#### Parameters
* `{string}` text Text to show 

* `{real}` duration Duration to show in milliseconds, defaults to 3000

# class `Cellulo::ToastManager` 

```
class Cellulo::ToastManager
  : public Column
```  

Manager that creates Toasts dynamically.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} var `[`toastComponent`](#classCellulo_1_1ToastManager_1a365162dd69e06083b149e6c39ab8b72f) | Private
`public void `[`show`](#classCellulo_1_1ToastManager_1a997ae9eb9d0d6ad7761dc85ca461c296)`(text,duration)` | Shows a [Toast](#classCellulo_1_1Toast).

## Members

#### `{property} var `[`toastComponent`](#classCellulo_1_1ToastManager_1a365162dd69e06083b149e6c39ab8b72f) 

Private

#### `public void `[`show`](#classCellulo_1_1ToastManager_1a997ae9eb9d0d6ad7761dc85ca461c296)`(text,duration)` 

Shows a [Toast](#classCellulo_1_1Toast).

Public 
#### Parameters
* `{string}` text Text to show 

* `{real}` duration Duration to show in milliseconds, defaults to 3000

# class `CameraFrameImageProvider` 

```
class CameraFrameImageProvider
  : public QQuickImageProvider
```  

QImage provider from QByteArray.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CameraFrameImageProvider`](#classCameraFrameImageProvider_1a0cb30c9805d79426a683afe45ec4a4b9)`()` | 
`public QImage `[`requestImage`](#classCameraFrameImageProvider_1a8aa2a18b29502db727a32027c5a839d3)`(QString const & id,QSize * size,QSize const & requestedSize)` | 

## Members

#### `public  `[`CameraFrameImageProvider`](#classCameraFrameImageProvider_1a0cb30c9805d79426a683afe45ec4a4b9)`()` 

#### `public QImage `[`requestImage`](#classCameraFrameImageProvider_1a8aa2a18b29502db727a32027c5a839d3)`(QString const & id,QSize * size,QSize const & requestedSize)` 

# class `CelluloBluetooth` 

```
class CelluloBluetooth
  : public CelluloZoneClient
```  

Bluetooth communicator for a Cellulo robot.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} QString `[`localAdapterMacAddr`](#classCelluloBluetooth_1a7836e15b93cd5cb0756b20d37c81f41d) | MAC address of the local adapter to use when connecting to the robot, only works on Linux.
`{property} bool `[`autoConnect`](#classCelluloBluetooth_1aae68306a7aa2672394054abd3191c5bb) | Whether the socket will try to reconnect every time it drops, will connect when mac address is set.
`{property} QString `[`macAddr`](#classCelluloBluetooth_1a5375cc2f136cc73c5f8c1eb72a8c16e2) | Bluetooth MAC address of the server.
`{property} CelluloBluetoothEnums::ConnectionStatus `[`connectionStatus`](#classCelluloBluetooth_1aa126a939727eb99cbeb450d682e9dd24) | Bluetooth connection status.
`{property} CelluloBluetoothEnums::BatteryState `[`batteryState`](#classCelluloBluetooth_1a4dc33acde1c88ecb77ac95964c673503) | Current battery state.
`{property} float `[`x`](#classCelluloBluetooth_1ac6f0f93ed11198b4a11e054db5b4174d) | Current x position in mm.
`{property} float `[`y`](#classCelluloBluetooth_1a0d630fab04d15fc808d80a3d448cdb11) | Current y position in mm.
`{property} float `[`theta`](#classCelluloBluetooth_1abc03848eb9a0c8d0fa21d825c84fe3e6) | Current orientation in degrees.
`{property} bool `[`kidnapped`](#classCelluloBluetooth_1a1e0bbe55e2fabe69cfbf3587149af647) | Whether currently kidnapped.
`{property} CelluloBluetoothEnums::Gesture `[`gesture`](#classCelluloBluetooth_1a2d07c00994adec97db9f3af6de82b16f) | Current gesture.
`{property} bool `[`timestampingEnabled`](#classCelluloBluetooth_1a60bb98ff051f8b675a9ed46608390f6d) | Whether timestamping along with pose is enabled and idling disabled.
`{property} int `[`lastTimestamp`](#classCelluloBluetooth_1a0ac2d6eeb1b5eb527f6f4c58f84ec4e8) | Latest received onboard timestamp (in milliseconds)
`{property} float `[`framerate`](#classCelluloBluetooth_1a371262b0de0c702a7336b9724a251867) | Framerate calculated over time.
`{property} float `[`cameraImageProgress`](#classCelluloBluetooth_1a6e75d3adb21a479a8dea2d0d0c48bd92) | Camera image streaming progress.
`public  explicit `[`CelluloBluetooth`](#classCelluloBluetooth_1a2cd8c1e2d18b3fa9ecf43c8157e8e5f3)`(QQuickItem * parent)` | Creates a new Cellulo robot communicator.
`public virtual  `[`~CelluloBluetooth`](#classCelluloBluetooth_1aa4f1a76db4147b20c30de7756f60aeb8)`()` | Destroys this Cellulo robot communicator.
`public inline QString `[`getLocalAdapterMacAddr`](#classCelluloBluetooth_1a13d2664a51c278f992560a0594bab58d)`() const` | Get the chosen local adapter's MAC address.
`public inline bool `[`getAutoConnect`](#classCelluloBluetooth_1ac04e5e87de4f43c05a187b61f32be4a9)`()` | Gets whether the socket tries to reconnect when it drops, connects when mac address is set.
`public QVariantList `[`getFrame`](#classCelluloBluetooth_1a525eeb6b7fd43e409595742c2c67d1d2)`() const` | Gets the latest camera frame.
`public inline QString `[`getMacAddr`](#classCelluloBluetooth_1a3674d17d4a2291f8c50037bf679a638b)`()` | Gets the current MAC address.
`public inline CelluloBluetoothEnums::ConnectionStatus `[`getConnectionStatus`](#classCelluloBluetooth_1aff548470566a85ced744efd0ef2c1a68)`()` | Gets current Bluetooth connection status.
`public inline bool `[`getTimestampingEnabled`](#classCelluloBluetooth_1adabe723862d8e6b4a0be145f3653ee1c)`()` | Gets whether timestamping along with pose is currently enabled.
`public inline CelluloBluetoothEnums::BatteryState `[`getBatteryState`](#classCelluloBluetooth_1a96140bdeb8db23192d034d08bf02da02)`()` | Gets the latest battery state.
`public inline float `[`getX`](#classCelluloBluetooth_1a353c584c291379a7bdde2d8d37b88b95)`()` | Gets the latest x position.
`public inline float `[`getY`](#classCelluloBluetooth_1a4316ae671b74aab0aa0cb4ceef371080)`()` | Gets the latest y position.
`public inline float `[`getTheta`](#classCelluloBluetooth_1a9ea419ff52fcc98a2c637669b9e20125)`()` | Gets the latest orientation.
`public inline int `[`getLastTimestamp`](#classCelluloBluetooth_1a21ec48d70902394ca8bce2c03bb5b80f)`()` | Gets the latest available timestamp.
`public inline float `[`getFramerate`](#classCelluloBluetooth_1a1c9efc7143b345513794b8898ef9b1b4)`()` | Gets the localization framerate.
`public inline bool `[`getKidnapped`](#classCelluloBluetooth_1a06690c10ec703437b22aa7844cef9499)`()` | Gets the latest kidnapped state.
`public inline CelluloBluetoothEnums::Gesture `[`getGesture`](#classCelluloBluetooth_1a3c09e7d568ae684a0dc96e8727bf6896)`()` | Gets the current gesture.
`public inline float `[`getCameraImageProgress`](#classCelluloBluetooth_1aa22c4d5d2138f795a6098a6510853560)`()` | Gets the camera image progress.
`{signal} public void `[`localAdapterMacAddrChanged`](#classCelluloBluetooth_1af2382e32dbb8af7d75d4ed7b15c0a659)`()` | Emitted when the desired local adapter changes.
`{signal} public void `[`autoConnectChanged`](#classCelluloBluetooth_1a7c1d9052c6e694395031a94b15a00eaa)`()` | Auto connect strategy changed.
`{signal} public void `[`macAddrChanged`](#classCelluloBluetooth_1a623d1e33bd7474a2151e6a7e6bb648ca)`()` | Emitted when the MAC address changes.
`{signal} public void `[`connectionStatusChanged`](#classCelluloBluetooth_1afa082631e751a3de965ad652199da290)`()` | Emitted when Bluetooth connection status changes.
`{signal} public void `[`bootCompleted`](#classCelluloBluetooth_1a420fd1e4780ae686d57de7ab7f1eaef1)`()` | Emitted when the robot is ready after a power up or a reset.
`{signal} public void `[`shuttingDown`](#classCelluloBluetooth_1afdaded09d3a9a9eeeff84818cc4bc754)`()` | Emitted when the robot is about to sleep (shutdown) due to the user command via touch keys.
`{signal} public void `[`lowBattery`](#classCelluloBluetooth_1acdaf5f8354d9edb628f20518f7f45a30)`()` | Emitted when the robot is about to sleep (shutdown) due to low battery.
`{signal} public void `[`batteryStateChanged`](#classCelluloBluetooth_1a6a8de2995ace189a65092a0778d481a7)`()` | Emitted when the battery state changes.
`{signal} public void `[`touchBegan`](#classCelluloBluetooth_1aed0425f022a3a4cfbbc79142c9428037)`(int key)` | Emitted when a key is touched.
`{signal} public void `[`longTouch`](#classCelluloBluetooth_1a6d19a9c15347b0a0d62a910ccee3e28a)`(int key)` | Emitted when a key is touched for more than the long touch time.
`{signal} public void `[`touchReleased`](#classCelluloBluetooth_1a71b1d0fa9770ae9638b34d6d1f215999)`(int key)` | Emitted when a key is released.
`{signal} public void `[`gestureChanged`](#classCelluloBluetooth_1a6cbf2b03df06d2cb0480250b768bbf9c)`()` | Emitted when the gesture on the robot changes.
`{signal} public void `[`poseChanged_inherited`](#classCelluloBluetooth_1ae97ec0bc62cc48aa65ba7ca05ea908ba)`()` | DO NOT USE EXPLICITLY.
`{signal} public void `[`timestampChanged`](#classCelluloBluetooth_1ab1aa47981bdd88e980b66a7d22afbb57)`()` | A new onboard localization timestamp has been received.
`{signal} public void `[`kidnappedChanged`](#classCelluloBluetooth_1a5ec07a6c47b49f7552aaaa28a50e5ba6)`()` | Emitted when the kidnap state of the robot changes.
`{signal} public void `[`trackingGoalReached`](#classCelluloBluetooth_1a47f03e2b7cc139ade1ee2e3b73c29359)`()` | Emitted when pose/position/orientation goal is reached.
`{signal} public void `[`cameraImageProgressChanged`](#classCelluloBluetooth_1abc66a5a27dcb9662b241c75754c873a8)`()` | Emitted when a new camera image line is received.
`{signal} public void `[`frameReady`](#classCelluloBluetooth_1a0f4d459c4eee87be34dfdd12e2eeb1e2)`()` | Emitted when a camera frame from the robot is ready to read.
`{slot} public void `[`setLocalAdapterMacAddr`](#classCelluloBluetooth_1a575e6b84252f6e4c691043e27b8acee0)`(QString localAdapterMacAddr)` | Sets the MAC address of the local adapter to use when connecting to the robot.
`{slot} public void `[`setAutoConnect`](#classCelluloBluetooth_1aac8c78cd5617b9bd828a3808faddedc9)`(bool autoConnect)` | Sets whether the socket will try to reconnect when it drops, connects when mac address is set.
`{slot} public void `[`setMacAddr`](#classCelluloBluetooth_1a2f64c38944bf67d644a32f734b45779e)`(QString macAddr)` | Sets the MAC address of the server and immediately connects to it.
`{slot} public void `[`connectToServer`](#classCelluloBluetooth_1a84ea50aecaf82b4c6bad18f27f4d5f93)`()` | Creates socket and connects to the current target MAC address.
`{slot} public void `[`disconnectFromServer`](#classCelluloBluetooth_1aa35ba04f5a04974c85e45c6dbf5c74b6)`()` | Disconnects from the currently connected device and destroys the socket if possible.
`{slot} public void `[`setPoseBcastPeriod`](#classCelluloBluetooth_1a86e136276443c4fb7ecddb2f577a6f00)`(unsigned int period)` | Sets the pose broadcast period.
`{slot} public void `[`setTimestampingEnabled`](#classCelluloBluetooth_1a693ede4c55b4a9473dda42696cdaa201)`(bool enabled)` | Enables timestamping along with pose and disables pose idling or vice-versa.
`{slot} public void `[`setMotor1Output`](#classCelluloBluetooth_1aa0c6ff4a156053a1691fcd20e2329f06)`(int output)` | Sets output of motor 1.
`{slot} public void `[`setMotor2Output`](#classCelluloBluetooth_1a982e84f2569ef553b1fdc500ffca8acb)`(int output)` | Sets output of motor 2.
`{slot} public void `[`setMotor3Output`](#classCelluloBluetooth_1a6538d69fdf9a349e4b6317b3a6525011)`(int output)` | Sets output of motor 3.
`{slot} public void `[`setAllMotorOutputs`](#classCelluloBluetooth_1af2e645653bf5f44be38a3a12ad2a7f34)`(int m1output,int m2output,int m3output)` | Sets outputs of all motors.
`{slot} public void `[`setGoalVelocity`](#classCelluloBluetooth_1a45fcd08efd5f54acc9d0d7ac394ee8ae)`(float vx,float vy,float w)` | Sets robot goal velocity in global world frame.
`{slot} public void `[`setGoalPose`](#classCelluloBluetooth_1a1b9e87e13815417da14995af6d4c41c8)`(float x,float y,float theta,float v,float w)` | Sets a pose goal to track.
`{slot} public void `[`setGoalPosition`](#classCelluloBluetooth_1aefcacac8e953c60d0824d7c41b416189)`(float x,float y,float v)` | Sets a position goal to track.
`{slot} public void `[`setGoalXCoordinate`](#classCelluloBluetooth_1a6edd8d42ed8ecaf75c354c4e0ed7517f)`(float x,float v)` | Sets an X coordinate to track.
`{slot} public void `[`setGoalYCoordinate`](#classCelluloBluetooth_1aa3b3e1e3c77a3e331216e5369450c174)`(float y,float v)` | Sets a Y coordinate to track.
`{slot} public void `[`setGoalOrientation`](#classCelluloBluetooth_1abd7ed6fed814e632d2e73cf6f284aa0e)`(float theta,float w)` | Sets a position goal to track.
`{slot} public void `[`setGoalXThetaCoordinate`](#classCelluloBluetooth_1aa0783b43ce5352bb51f78b02407b67d7)`(float x,float theta,float v,float w)` | Sets an X and Theta goal at the same time.
`{slot} public void `[`setGoalYThetaCoordinate`](#classCelluloBluetooth_1a3e7762e1796b547aeffa76568d74f38e)`(float y,float theta,float v,float w)` | Sets a Y and Theta goal at the same time.
`{slot} public void `[`clearTracking`](#classCelluloBluetooth_1a0d4b5c15fd448f53094825b87fbd3f7b)`()` | Clears pose/position/velocity goals.
`{slot} public void `[`simpleVibrate`](#classCelluloBluetooth_1ad704c04dd187e8ee9f2fee20f2fa3845)`(float iX,float iY,float iTheta,unsigned int period,unsigned int duration)` | Constantly vibrates the robot.
`{slot} public void `[`vibrateOnMotion`](#classCelluloBluetooth_1a570f90bb872bbd867d609f1ee192097f)`(float iCoeff,unsigned int period)` | Enables vibration against motion.
`{slot} public void `[`clearHapticFeedback`](#classCelluloBluetooth_1a99cd609933e4305f54dbb698907ee8cc)`()` | Clears all haptic feedbacks.
`{slot} public void `[`ping`](#classCelluloBluetooth_1acf39a7628fd606fd508dfa518e078b86)`()` | Sends a ping, expecting an acknowledge.
`{slot} public void `[`requestFrame`](#classCelluloBluetooth_1abb01f282036d9da5bca947ba2b300448)`()` | Requests a camera frame to be sent.
`{slot} public void `[`setExposureTime`](#classCelluloBluetooth_1a61b49eb96246d87a08946f9f97b5512e)`(int pixels)` | Sets the exposure time for super-fast unkidnap detection for uniform and known paper colors known or enables autoexposure.
`{slot} public void `[`queryBatteryState`](#classCelluloBluetooth_1aebf5bf30f73bba6b36ded05e15e45159)`()` | Sends a battery state query.
`{slot} public void `[`setLEDResponseMode`](#classCelluloBluetooth_1aa947f4da0ebc8773085f94ca280101c7)`(CelluloBluetoothEnums::LEDResponseMode mode)` | Sets the LED response mode, i.e the LED visual response of the robot to touches.
`{slot} public void `[`setLocomotionInteractivityMode`](#classCelluloBluetooth_1a85422447a3e2fe4196943aaece7ed5de)`(CelluloBluetoothEnums::LocomotionInteractivityMode mode)` | Sets the locomotion interactivity mode, i.e the dependance of locomotion to user input.
`{slot} public void `[`setGestureEnabled`](#classCelluloBluetooth_1aaf73d22964f223ec5562fc341c335ac2)`(bool enabled)` | Enables/disables raw touch signal offset querying and processing.
`{slot} public void `[`setCasualBackdriveAssistEnabled`](#classCelluloBluetooth_1a76686c8a966b40696f2bee22dcd3edee)`(bool enabled)` | Enables/disables assist for easy backdriving.
`{slot} public void `[`setHapticBackdriveAssist`](#classCelluloBluetooth_1a34db590212bf9e8550f198a652534e07)`(float xAssist,float yAssist,float thetaAssist)` | Haptic feedback-oriented backdrive assist.
`{slot} public void `[`setVisualEffect`](#classCelluloBluetooth_1a409c8fdc5ddef1ec7c6ed36d697e9fba)`(CelluloBluetoothEnums::VisualEffect effect,QColor color,int value)` | Sets the visual effect on the robot, changing LED illumination.
`{slot} public void `[`polyBezierInit`](#classCelluloBluetooth_1a7ccf2d7537ea578bbcf01a243ea89c46)`(const QVector2D & point0)` | Sends the first control point of the composite Bézier curve for motion tracking.
`{slot} public void `[`polyBezierAppend`](#classCelluloBluetooth_1a20c7612aa3fb9f01f760ad5437226a2e)`(const QVector2D & point1,const QVector2D & point2,const QVector2D & point3)` | Adds a segment to the composite Bézier curve for motion tracking; [polyBezierInit()](#classCelluloBluetooth_1a7ccf2d7537ea578bbcf01a243ea89c46) must be called before.
`{slot} public void `[`polyBezierSetFromZone`](#classCelluloBluetooth_1a1c991b608d73ac95fca4f48949490f25)`(`[`CelluloZone`](#classCelluloZone)` * zone)` | Sends the composite Bézier curve in the zone to the robot.
`{slot} public void `[`setGoalPolyBezier`](#classCelluloBluetooth_1a58c5e750ecdac6f00a7fcdf991b00481)`(float v,float w)` | Starts tracking the previously set composite Bézier curve.
`{slot} public void `[`setGoalPolyBezierAligned`](#classCelluloBluetooth_1aa5df9a58af8b395b4146600dd820766b)`(float v,float theta,float w)` | Starts tracking the previously set composite Bézier curve while keeping orientation aligned to the curve.
`{slot} public void `[`reset`](#classCelluloBluetooth_1a6f60aac2259a6e6e72f221ebfb9a00d4)`()` | Initiates a software reset on the robot.
`{slot} public void `[`shutdown`](#classCelluloBluetooth_1a8115abd66d4acd9aaf7d8e1aeab91fae)`()` | Initiates sleep on the robot.

## Members

#### `{property} QString `[`localAdapterMacAddr`](#classCelluloBluetooth_1a7836e15b93cd5cb0756b20d37c81f41d) 

MAC address of the local adapter to use when connecting to the robot, only works on Linux.

#### `{property} bool `[`autoConnect`](#classCelluloBluetooth_1aae68306a7aa2672394054abd3191c5bb) 

Whether the socket will try to reconnect every time it drops, will connect when mac address is set.

#### `{property} QString `[`macAddr`](#classCelluloBluetooth_1a5375cc2f136cc73c5f8c1eb72a8c16e2) 

Bluetooth MAC address of the server.

#### `{property} CelluloBluetoothEnums::ConnectionStatus `[`connectionStatus`](#classCelluloBluetooth_1aa126a939727eb99cbeb450d682e9dd24) 

Bluetooth connection status.

#### `{property} CelluloBluetoothEnums::BatteryState `[`batteryState`](#classCelluloBluetooth_1a4dc33acde1c88ecb77ac95964c673503) 

Current battery state.

#### `{property} float `[`x`](#classCelluloBluetooth_1ac6f0f93ed11198b4a11e054db5b4174d) 

Current x position in mm.

#### `{property} float `[`y`](#classCelluloBluetooth_1a0d630fab04d15fc808d80a3d448cdb11) 

Current y position in mm.

#### `{property} float `[`theta`](#classCelluloBluetooth_1abc03848eb9a0c8d0fa21d825c84fe3e6) 

Current orientation in degrees.

#### `{property} bool `[`kidnapped`](#classCelluloBluetooth_1a1e0bbe55e2fabe69cfbf3587149af647) 

Whether currently kidnapped.

#### `{property} CelluloBluetoothEnums::Gesture `[`gesture`](#classCelluloBluetooth_1a2d07c00994adec97db9f3af6de82b16f) 

Current gesture.

#### `{property} bool `[`timestampingEnabled`](#classCelluloBluetooth_1a60bb98ff051f8b675a9ed46608390f6d) 

Whether timestamping along with pose is enabled and idling disabled.

#### `{property} int `[`lastTimestamp`](#classCelluloBluetooth_1a0ac2d6eeb1b5eb527f6f4c58f84ec4e8) 

Latest received onboard timestamp (in milliseconds)

#### `{property} float `[`framerate`](#classCelluloBluetooth_1a371262b0de0c702a7336b9724a251867) 

Framerate calculated over time.

#### `{property} float `[`cameraImageProgress`](#classCelluloBluetooth_1a6e75d3adb21a479a8dea2d0d0c48bd92) 

Camera image streaming progress.

#### `public  explicit `[`CelluloBluetooth`](#classCelluloBluetooth_1a2cd8c1e2d18b3fa9ecf43c8157e8e5f3)`(QQuickItem * parent)` 

Creates a new Cellulo robot communicator.

#### Parameters
* `parent` Parent of this QML item

#### `public virtual  `[`~CelluloBluetooth`](#classCelluloBluetooth_1aa4f1a76db4147b20c30de7756f60aeb8)`()` 

Destroys this Cellulo robot communicator.

#### `public inline QString `[`getLocalAdapterMacAddr`](#classCelluloBluetooth_1a13d2664a51c278f992560a0594bab58d)`() const` 

Get the chosen local adapter's MAC address.

#### Returns
Chosen local adapter's MAC address, empty string if using default adapter

#### `public inline bool `[`getAutoConnect`](#classCelluloBluetooth_1ac04e5e87de4f43c05a187b61f32be4a9)`()` 

Gets whether the socket tries to reconnect when it drops, connects when mac address is set.

#### Returns
Whether the socket tries to reconnect when it drops, connects when mac address is set

#### `public QVariantList `[`getFrame`](#classCelluloBluetooth_1a525eeb6b7fd43e409595742c2c67d1d2)`() const` 

Gets the latest camera frame.

#### Returns
The latest camera frame; IMG_WIDTH*IMG_HEIGHT many ints in grayscale, 0 to 255

#### `public inline QString `[`getMacAddr`](#classCelluloBluetooth_1a3674d17d4a2291f8c50037bf679a638b)`()` 

Gets the current MAC address.

#### Returns
The current MAC address

#### `public inline CelluloBluetoothEnums::ConnectionStatus `[`getConnectionStatus`](#classCelluloBluetooth_1aff548470566a85ced744efd0ef2c1a68)`()` 

Gets current Bluetooth connection status.

#### Returns
Current Bluetooth connection status

#### `public inline bool `[`getTimestampingEnabled`](#classCelluloBluetooth_1adabe723862d8e6b4a0be145f3653ee1c)`()` 

Gets whether timestamping along with pose is currently enabled.

#### Returns
Whether timestamping is enabled

#### `public inline CelluloBluetoothEnums::BatteryState `[`getBatteryState`](#classCelluloBluetooth_1a96140bdeb8db23192d034d08bf02da02)`()` 

Gets the latest battery state.

#### Returns
Battery state

#### `public inline float `[`getX`](#classCelluloBluetooth_1a353c584c291379a7bdde2d8d37b88b95)`()` 

Gets the latest x position.

#### Returns
Latest x position in mm

#### `public inline float `[`getY`](#classCelluloBluetooth_1a4316ae671b74aab0aa0cb4ceef371080)`()` 

Gets the latest y position.

#### Returns
Latest y position in mm

#### `public inline float `[`getTheta`](#classCelluloBluetooth_1a9ea419ff52fcc98a2c637669b9e20125)`()` 

Gets the latest orientation.

#### Returns
Latest orientation in degrees

#### `public inline int `[`getLastTimestamp`](#classCelluloBluetooth_1a21ec48d70902394ca8bce2c03bb5b80f)`()` 

Gets the latest available timestamp.

#### Returns
The latest received timestamp in milliseconds

#### `public inline float `[`getFramerate`](#classCelluloBluetooth_1a1c9efc7143b345513794b8898ef9b1b4)`()` 

Gets the localization framerate.

#### Returns
Localization framerate in milliseconds

#### `public inline bool `[`getKidnapped`](#classCelluloBluetooth_1a06690c10ec703437b22aa7844cef9499)`()` 

Gets the latest kidnapped state.

#### Returns
Whether kidnapped or on encoded paper

#### `public inline CelluloBluetoothEnums::Gesture `[`getGesture`](#classCelluloBluetooth_1a3c09e7d568ae684a0dc96e8727bf6896)`()` 

Gets the current gesture.

#### Returns
Current gesture

#### `public inline float `[`getCameraImageProgress`](#classCelluloBluetooth_1aa22c4d5d2138f795a6098a6510853560)`()` 

Gets the camera image progress.

#### Returns
Between 0.0 and 1.0

#### `{signal} public void `[`localAdapterMacAddrChanged`](#classCelluloBluetooth_1af2382e32dbb8af7d75d4ed7b15c0a659)`()` 

Emitted when the desired local adapter changes.

#### `{signal} public void `[`autoConnectChanged`](#classCelluloBluetooth_1a7c1d9052c6e694395031a94b15a00eaa)`()` 

Auto connect strategy changed.

#### `{signal} public void `[`macAddrChanged`](#classCelluloBluetooth_1a623d1e33bd7474a2151e6a7e6bb648ca)`()` 

Emitted when the MAC address changes.

#### `{signal} public void `[`connectionStatusChanged`](#classCelluloBluetooth_1afa082631e751a3de965ad652199da290)`()` 

Emitted when Bluetooth connection status changes.

#### `{signal} public void `[`bootCompleted`](#classCelluloBluetooth_1a420fd1e4780ae686d57de7ab7f1eaef1)`()` 

Emitted when the robot is ready after a power up or a reset.

#### `{signal} public void `[`shuttingDown`](#classCelluloBluetooth_1afdaded09d3a9a9eeeff84818cc4bc754)`()` 

Emitted when the robot is about to sleep (shutdown) due to the user command via touch keys.

#### `{signal} public void `[`lowBattery`](#classCelluloBluetooth_1acdaf5f8354d9edb628f20518f7f45a30)`()` 

Emitted when the robot is about to sleep (shutdown) due to low battery.

#### `{signal} public void `[`batteryStateChanged`](#classCelluloBluetooth_1a6a8de2995ace189a65092a0778d481a7)`()` 

Emitted when the battery state changes.

#### `{signal} public void `[`touchBegan`](#classCelluloBluetooth_1aed0425f022a3a4cfbbc79142c9428037)`(int key)` 

Emitted when a key is touched.

#### Parameters
* `key` The key that is touched

#### `{signal} public void `[`longTouch`](#classCelluloBluetooth_1a6d19a9c15347b0a0d62a910ccee3e28a)`(int key)` 

Emitted when a key is touched for more than the long touch time.

#### Parameters
* `key` The key that is touched

#### `{signal} public void `[`touchReleased`](#classCelluloBluetooth_1a71b1d0fa9770ae9638b34d6d1f215999)`(int key)` 

Emitted when a key is released.

#### Parameters
* `key` The key that is released

#### `{signal} public void `[`gestureChanged`](#classCelluloBluetooth_1a6cbf2b03df06d2cb0480250b768bbf9c)`()` 

Emitted when the gesture on the robot changes.

#### `{signal} public void `[`poseChanged_inherited`](#classCelluloBluetooth_1ae97ec0bc62cc48aa65ba7ca05ea908ba)`()` 

DO NOT USE EXPLICITLY.

Emitted when the base class emits [poseChanged()](#classCelluloZoneClient_1a0ff05b6e35773b4a9a3b83a956f176f6) since NOTIFY cannot be used with inherited signals

#### `{signal} public void `[`timestampChanged`](#classCelluloBluetooth_1ab1aa47981bdd88e980b66a7d22afbb57)`()` 

A new onboard localization timestamp has been received.

#### `{signal} public void `[`kidnappedChanged`](#classCelluloBluetooth_1a5ec07a6c47b49f7552aaaa28a50e5ba6)`()` 

Emitted when the kidnap state of the robot changes.

#### `{signal} public void `[`trackingGoalReached`](#classCelluloBluetooth_1a47f03e2b7cc139ade1ee2e3b73c29359)`()` 

Emitted when pose/position/orientation goal is reached.

#### `{signal} public void `[`cameraImageProgressChanged`](#classCelluloBluetooth_1abc66a5a27dcb9662b241c75754c873a8)`()` 

Emitted when a new camera image line is received.

#### `{signal} public void `[`frameReady`](#classCelluloBluetooth_1a0f4d459c4eee87be34dfdd12e2eeb1e2)`()` 

Emitted when a camera frame from the robot is ready to read.

#### `{slot} public void `[`setLocalAdapterMacAddr`](#classCelluloBluetooth_1a575e6b84252f6e4c691043e27b8acee0)`(QString localAdapterMacAddr)` 

Sets the MAC address of the local adapter to use when connecting to the robot.

Only works on Linux; must be built with bluez.

#### Parameters
* `localAdapterMacAddr` MAC address of the local adapter, must exist; set to empty string to connect with default adapter

#### `{slot} public void `[`setAutoConnect`](#classCelluloBluetooth_1aac8c78cd5617b9bd828a3808faddedc9)`(bool autoConnect)` 

Sets whether the socket will try to reconnect when it drops, connects when mac address is set.

#### Parameters
* `autoReconnect` Whether the socket will try to reconnect when it drops, connects when mac address is set

#### `{slot} public void `[`setMacAddr`](#classCelluloBluetooth_1a2f64c38944bf67d644a32f734b45779e)`(QString macAddr)` 

Sets the MAC address of the server and immediately connects to it.

#### Parameters
* `macAddr` Bluetooth MAC address of the server (robot)

#### `{slot} public void `[`connectToServer`](#classCelluloBluetooth_1a84ea50aecaf82b4c6bad18f27f4d5f93)`()` 

Creates socket and connects to the current target MAC address.

#### `{slot} public void `[`disconnectFromServer`](#classCelluloBluetooth_1aa35ba04f5a04974c85e45c6dbf5c74b6)`()` 

Disconnects from the currently connected device and destroys the socket if possible.

#### `{slot} public void `[`setPoseBcastPeriod`](#classCelluloBluetooth_1a86e136276443c4fb7ecddb2f577a6f00)`(unsigned int period)` 

Sets the pose broadcast period.

#### Parameters
* `period` Desired period in milliseconds

#### `{slot} public void `[`setTimestampingEnabled`](#classCelluloBluetooth_1a693ede4c55b4a9473dda42696cdaa201)`(bool enabled)` 

Enables timestamping along with pose and disables pose idling or vice-versa.

#### Parameters
* `enabled` Whether to enable timestamping

#### `{slot} public void `[`setMotor1Output`](#classCelluloBluetooth_1aa0c6ff4a156053a1691fcd20e2329f06)`(int output)` 

Sets output of motor 1.

#### Parameters
* `output` Value between -0xFFF and 0xFFF

#### `{slot} public void `[`setMotor2Output`](#classCelluloBluetooth_1a982e84f2569ef553b1fdc500ffca8acb)`(int output)` 

Sets output of motor 2.

#### Parameters
* `output` Value between -0xFFF and 0xFFF

#### `{slot} public void `[`setMotor3Output`](#classCelluloBluetooth_1a6538d69fdf9a349e4b6317b3a6525011)`(int output)` 

Sets output of motor 3.

#### Parameters
* `output` Value between -0xFFF and 0xFFF

#### `{slot} public void `[`setAllMotorOutputs`](#classCelluloBluetooth_1af2e645653bf5f44be38a3a12ad2a7f34)`(int m1output,int m2output,int m3output)` 

Sets outputs of all motors.

#### Parameters
* `m1output` Value between -0xFFF and 0xFFF 

* `m2output` Value between -0xFFF and 0xFFF 

* `m3output` Value between -0xFFF and 0xFFF

#### `{slot} public void `[`setGoalVelocity`](#classCelluloBluetooth_1a45fcd08efd5f54acc9d0d7ac394ee8ae)`(float vx,float vy,float w)` 

Sets robot goal velocity in global world frame.

#### Parameters
* `vx` X velocity in mm/s 

* `vy` Y velocity in mm/s 

* `w` Angular velocity in rad/s

#### `{slot} public void `[`setGoalPose`](#classCelluloBluetooth_1a1b9e87e13815417da14995af6d4c41c8)`(float x,float y,float theta,float v,float w)` 

Sets a pose goal to track.

#### Parameters
* `x` X goal in mm 

* `y` Y goal in mm 

* `theta` Theta goal in degrees 

* `v` Maximum linear speed to track pose in mm/s 

* `w` Maximum angular speed to track pose in rad/s

#### `{slot} public void `[`setGoalPosition`](#classCelluloBluetooth_1aefcacac8e953c60d0824d7c41b416189)`(float x,float y,float v)` 

Sets a position goal to track.

#### Parameters
* `x` X goal in mm 

* `y` Y goal in mm 

* `v` Maximum linear speed to track pose in mm/s

#### `{slot} public void `[`setGoalXCoordinate`](#classCelluloBluetooth_1a6edd8d42ed8ecaf75c354c4e0ed7517f)`(float x,float v)` 

Sets an X coordinate to track.

#### Parameters
* `x` X goal in mm 

* `v` Maximum linear speed to track pose in mm/s

#### `{slot} public void `[`setGoalYCoordinate`](#classCelluloBluetooth_1aa3b3e1e3c77a3e331216e5369450c174)`(float y,float v)` 

Sets a Y coordinate to track.

#### Parameters
* `y` Y goal in mm 

* `v` Maximum linear speed to track pose in mm/s

#### `{slot} public void `[`setGoalOrientation`](#classCelluloBluetooth_1abd7ed6fed814e632d2e73cf6f284aa0e)`(float theta,float w)` 

Sets a position goal to track.

#### Parameters
* `theta` Theta goal in degrees 

* `w` Maximum angular speed to track pose in rad/s

#### `{slot} public void `[`setGoalXThetaCoordinate`](#classCelluloBluetooth_1aa0783b43ce5352bb51f78b02407b67d7)`(float x,float theta,float v,float w)` 

Sets an X and Theta goal at the same time.

#### Parameters
* `x` X goal in mm 

* `theta` Theta goal in degrees 

* `v` Maximum linear speed to track pose in mm/s 

* `w` Maximum angular speed to track pose in rad/s

#### `{slot} public void `[`setGoalYThetaCoordinate`](#classCelluloBluetooth_1a3e7762e1796b547aeffa76568d74f38e)`(float y,float theta,float v,float w)` 

Sets a Y and Theta goal at the same time.

#### Parameters
* `y` Y goal in mm 

* `theta` Theta goal in degrees 

* `v` Maximum linear speed to track pose in mm/s 

* `w` Maximum angular speed to track pose in rad/s

#### `{slot} public void `[`clearTracking`](#classCelluloBluetooth_1a0d4b5c15fd448f53094825b87fbd3f7b)`()` 

Clears pose/position/velocity goals.

#### `{slot} public void `[`simpleVibrate`](#classCelluloBluetooth_1ad704c04dd187e8ee9f2fee20f2fa3845)`(float iX,float iY,float iTheta,unsigned int period,unsigned int duration)` 

Constantly vibrates the robot.

#### Parameters
* `iX` X intensity, scale is the same as linear velocity 

* `iY` Y intensity, scale is the same as linear velocity 

* `iTheta` Theta intensity, scale is the same as angular velocity 

* `period` Period of vibration in milliseconds, maximum is 0xFFFF 

* `duration` Duration of vibration in milliseconds, maximum is 0xFFFF, 0 for vibrate forever

#### `{slot} public void `[`vibrateOnMotion`](#classCelluloBluetooth_1a570f90bb872bbd867d609f1ee192097f)`(float iCoeff,unsigned int period)` 

Enables vibration against motion.

#### Parameters
* `iCoeff` Vibration intensity with respect to the drive velocities 

* `period` Period of vibration in milliseconds, maximum is 0xFFFF

#### `{slot} public void `[`clearHapticFeedback`](#classCelluloBluetooth_1a99cd609933e4305f54dbb698907ee8cc)`()` 

Clears all haptic feedbacks.

#### `{slot} public void `[`ping`](#classCelluloBluetooth_1acf39a7628fd606fd508dfa518e078b86)`()` 

Sends a ping, expecting an acknowledge.

#### `{slot} public void `[`requestFrame`](#classCelluloBluetooth_1abb01f282036d9da5bca947ba2b300448)`()` 

Requests a camera frame to be sent.

#### `{slot} public void `[`setExposureTime`](#classCelluloBluetooth_1a61b49eb96246d87a08946f9f97b5512e)`(int pixels)` 

Sets the exposure time for super-fast unkidnap detection for uniform and known paper colors known or enables autoexposure.

460 pixels for the latest white plastic frame and white paper is a good value.

#### Parameters
* `pixels` Exposure time in pixels, must be larger than 260; 0 is a special value that enables autoexposure

#### `{slot} public void `[`queryBatteryState`](#classCelluloBluetooth_1aebf5bf30f73bba6b36ded05e15e45159)`()` 

Sends a battery state query.

#### `{slot} public void `[`setLEDResponseMode`](#classCelluloBluetooth_1aa947f4da0ebc8773085f94ca280101c7)`(CelluloBluetoothEnums::LEDResponseMode mode)` 

Sets the LED response mode, i.e the LED visual response of the robot to touches.

#### Parameters
* `mode` LED resposne mode

#### `{slot} public void `[`setLocomotionInteractivityMode`](#classCelluloBluetooth_1a85422447a3e2fe4196943aaece7ed5de)`(CelluloBluetoothEnums::LocomotionInteractivityMode mode)` 

Sets the locomotion interactivity mode, i.e the dependance of locomotion to user input.

#### Parameters
* `mode` Locomotion interactivity mode

#### `{slot} public void `[`setGestureEnabled`](#classCelluloBluetooth_1aaf73d22964f223ec5562fc341c335ac2)`(bool enabled)` 

Enables/disables raw touch signal offset querying and processing.

#### Parameters
* `enabled` Whether to enable

#### `{slot} public void `[`setCasualBackdriveAssistEnabled`](#classCelluloBluetooth_1a76686c8a966b40696f2bee22dcd3edee)`(bool enabled)` 

Enables/disables assist for easy backdriving.

#### Parameters
* `enabled` Whether to enable

#### `{slot} public void `[`setHapticBackdriveAssist`](#classCelluloBluetooth_1a34db590212bf9e8550f198a652534e07)`(float xAssist,float yAssist,float thetaAssist)` 

Haptic feedback-oriented backdrive assist.

Pass 0 to all parameters to disable. Disables casual backdrive assist upon enabling.

#### Parameters
* `xAssist` X assist with respect to x drive velocity, can be negative 

* `yAssist` Y assist with respect to y drive velocity, can be negative 

* `thetaAssist` Theta assist with respect to w drive, can be negative

#### `{slot} public void `[`setVisualEffect`](#classCelluloBluetooth_1a409c8fdc5ddef1ec7c6ed36d697e9fba)`(CelluloBluetoothEnums::VisualEffect effect,QColor color,int value)` 

Sets the visual effect on the robot, changing LED illumination.

#### Parameters
* `effect` The effect ordinal 

* `color` Color 

* `value` A value possibly meaningful for the effect (between 0 and 255)

#### `{slot} public void `[`polyBezierInit`](#classCelluloBluetooth_1a7ccf2d7537ea578bbcf01a243ea89c46)`(const QVector2D & point0)` 

Sends the first control point of the composite Bézier curve for motion tracking.

#### Parameters
* `point0` The initial point, i.e the first control point of the first segment

#### `{slot} public void `[`polyBezierAppend`](#classCelluloBluetooth_1a20c7612aa3fb9f01f760ad5437226a2e)`(const QVector2D & point1,const QVector2D & point2,const QVector2D & point3)` 

Adds a segment to the composite Bézier curve for motion tracking; [polyBezierInit()](#classCelluloBluetooth_1a7ccf2d7537ea578bbcf01a243ea89c46) must be called before.

The first control point is the last control point of the previously added segment or the initial point.

#### Parameters
* `point1` The second control point for the curve 

* `point2` The third control point for the curve 

* `point3` The fourth control point for the curve

#### `{slot} public void `[`polyBezierSetFromZone`](#classCelluloBluetooth_1a1c991b608d73ac95fca4f48949490f25)`(`[`CelluloZone`](#classCelluloZone)` * zone)` 

Sends the composite Bézier curve in the zone to the robot.

#### Parameters
* `zone` The zone that contains the composite Bézier curve path

#### `{slot} public void `[`setGoalPolyBezier`](#classCelluloBluetooth_1a58c5e750ecdac6f00a7fcdf991b00481)`(float v,float w)` 

Starts tracking the previously set composite Bézier curve.

#### Parameters
* `v` Linear velocity tangent to the curve 

* `w` Angular velocity throughout the traversal

#### `{slot} public void `[`setGoalPolyBezierAligned`](#classCelluloBluetooth_1aa5df9a58af8b395b4146600dd820766b)`(float v,float theta,float w)` 

Starts tracking the previously set composite Bézier curve while keeping orientation aligned to the curve.

#### Parameters
* `v` Linear velocity tangent to the curve 

* `theta` Orientation to track with respect to the curve tangent orientation, in degrees 

* `w` Maximum angular velocity while tracking orientation, in rad/s

#### `{slot} public void `[`reset`](#classCelluloBluetooth_1a6f60aac2259a6e6e72f221ebfb9a00d4)`()` 

Initiates a software reset on the robot.

#### `{slot} public void `[`shutdown`](#classCelluloBluetooth_1a8115abd66d4acd9aaf7d8e1aeab91fae)`()` 

Initiates sleep on the robot.

# class `CelluloBluetoothEMP` 

```
class CelluloBluetoothEMP
  : public QQuickItem
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} bool `[`continuous`](#classCelluloBluetoothEMP_1a57fbcba07a125504001d358ecf2b6e48) | Whether to blast same robots.
`{property} QStringList `[`macAddrToBlast`](#classCelluloBluetoothEMP_1a80301e3720211a0ca339467fd9f556f9) | List of mac addresses that are being blasted.
`{property} QStringList `[`macAddrBlasted`](#classCelluloBluetoothEMP_1a8674de706d8466f9aeb62aabdeb4830f) | List of mac addresses that are confirmed to be blasted.
`public  explicit `[`CelluloBluetoothEMP`](#classCelluloBluetoothEMP_1a07e7c6e15ac3f974aceed7d6786da4a2)`(QQuickItem * parent)` | Creates a new EMP blaster.
`public virtual  `[`~CelluloBluetoothEMP`](#classCelluloBluetoothEMP_1ab3080112b93ad6214c468b9ff77550de)`()` | Destroys this EMP blaster.
`public inline bool `[`getContinuous`](#classCelluloBluetoothEMP_1aa53dc4d25230e7b264b09358cc27b8db)`()` | Gets whether to blast same robots.
`public inline QStringList `[`getMacAddrToBlast`](#classCelluloBluetoothEMP_1a29aba45acbc2fe169c0852c227717238)`() const` | Gets the mac addresses of robots that are waiting to be blasted.
`public inline QStringList `[`getMacAddrBlasted`](#classCelluloBluetoothEMP_1a4a35114a80408b9ffb7b6ed2fc4ad978)`() const` | Gets the mac addresses of robots that are confirmed to be blasted.
`{signal} public void `[`continuousChanged`](#classCelluloBluetoothEMP_1a597015df3660046071aa724cce896ea0)`()` | Whether to blast same robots strategy changed.
`{signal} public void `[`macAddrToBlastChanged`](#classCelluloBluetoothEMP_1a69dec88fba645f57ebaa617a427e02f2)`()` | Emitted when list of mac addresses waiting to be blasted changes.
`{signal} public void `[`macAddrBlastedChanged`](#classCelluloBluetoothEMP_1a558865a1d22781809a5c52f84529fedf)`()` | Emitted when list of mac addresses confirmed to be blasted changes.
`{slot} public void `[`setContinuous`](#classCelluloBluetoothEMP_1a698b6d37c0f91733e9a375b2257608a6)`(bool continuous)` | Sets whether to blast same robots.
`{slot} public void `[`resetLater`](#classCelluloBluetoothEMP_1a57e79f8d43eac34a719a9daea9660403)`(QString macAddr)` | Initiates connection to the robot to reset it when it's connected.
`{slot} public void `[`shutdownLater`](#classCelluloBluetoothEMP_1a15e0cbfa49c37ed7fafbac491dda1a71)`(QString macAddr)` | Initiates connection to the robot to shut it down when it's connected.
`{slot} public void `[`clear`](#classCelluloBluetoothEMP_1af9369395d05fb3fb41fe0a80e156b43b)`()` | Clears both lists, drops all connections.

## Members

#### `{property} bool `[`continuous`](#classCelluloBluetoothEMP_1a57fbcba07a125504001d358ecf2b6e48) 

Whether to blast same robots.

#### `{property} QStringList `[`macAddrToBlast`](#classCelluloBluetoothEMP_1a80301e3720211a0ca339467fd9f556f9) 

List of mac addresses that are being blasted.

#### `{property} QStringList `[`macAddrBlasted`](#classCelluloBluetoothEMP_1a8674de706d8466f9aeb62aabdeb4830f) 

List of mac addresses that are confirmed to be blasted.

#### `public  explicit `[`CelluloBluetoothEMP`](#classCelluloBluetoothEMP_1a07e7c6e15ac3f974aceed7d6786da4a2)`(QQuickItem * parent)` 

Creates a new EMP blaster.

#### Parameters
* `parent` Parent of this QML item

#### `public virtual  `[`~CelluloBluetoothEMP`](#classCelluloBluetoothEMP_1ab3080112b93ad6214c468b9ff77550de)`()` 

Destroys this EMP blaster.

#### `public inline bool `[`getContinuous`](#classCelluloBluetoothEMP_1aa53dc4d25230e7b264b09358cc27b8db)`()` 

Gets whether to blast same robots.

#### Returns
Whether to blast same robots

#### `public inline QStringList `[`getMacAddrToBlast`](#classCelluloBluetoothEMP_1a29aba45acbc2fe169c0852c227717238)`() const` 

Gets the mac addresses of robots that are waiting to be blasted.

#### Returns
Mac addresses of robots that are waiting to be blasted

#### `public inline QStringList `[`getMacAddrBlasted`](#classCelluloBluetoothEMP_1a4a35114a80408b9ffb7b6ed2fc4ad978)`() const` 

Gets the mac addresses of robots that are confirmed to be blasted.

#### Returns
Mac addresses of robots that are confirmed to be blasted

#### `{signal} public void `[`continuousChanged`](#classCelluloBluetoothEMP_1a597015df3660046071aa724cce896ea0)`()` 

Whether to blast same robots strategy changed.

#### `{signal} public void `[`macAddrToBlastChanged`](#classCelluloBluetoothEMP_1a69dec88fba645f57ebaa617a427e02f2)`()` 

Emitted when list of mac addresses waiting to be blasted changes.

#### `{signal} public void `[`macAddrBlastedChanged`](#classCelluloBluetoothEMP_1a558865a1d22781809a5c52f84529fedf)`()` 

Emitted when list of mac addresses confirmed to be blasted changes.

#### `{slot} public void `[`setContinuous`](#classCelluloBluetoothEMP_1a698b6d37c0f91733e9a375b2257608a6)`(bool continuous)` 

Sets whether to blast same robots.

#### Parameters
* `continuous` Whether to blast same robots

#### `{slot} public void `[`resetLater`](#classCelluloBluetoothEMP_1a57e79f8d43eac34a719a9daea9660403)`(QString macAddr)` 

Initiates connection to the robot to reset it when it's connected.

#### `{slot} public void `[`shutdownLater`](#classCelluloBluetoothEMP_1a15e0cbfa49c37ed7fafbac491dda1a71)`(QString macAddr)` 

Initiates connection to the robot to shut it down when it's connected.

#### `{slot} public void `[`clear`](#classCelluloBluetoothEMP_1af9369395d05fb3fb41fe0a80e156b43b)`()` 

Clears both lists, drops all connections.

# class `CelluloBluetoothEnums` 

```
class CelluloBluetoothEnums
  : public QObject
```  

Wrapper containing all the enums of [CelluloBluetooth](#classCelluloBluetooth).

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CONNECTION_STATUS_ENUM_SHARED`](#classCelluloBluetoothEnums_1a4dfe101c28ba4cbd6e184ab5cf195938) | Bluetooth connection status.
`public  `[`BATTERY_STATE_ENUM_SHARED`](#classCelluloBluetoothEnums_1ac53f55593d28af6942db35212195ec99) | Battery state of the robot.
`public  `[`LED_RESPONSE_MODE_ENUM_SHARED`](#classCelluloBluetoothEnums_1a1e353b2ba3f28ea7140b565ef1c0ea10) | LED response mode of the robot.
`public  `[`LOCOMOTION_INTERACTIVITY_MODE_ENUM_SHARED`](#classCelluloBluetoothEnums_1a5464d116ce7ff302203ede72f6812707) | Locomotion interactivity mode of the robot.
`public  `[`VISUAL_EFFECT_ENUM_SHARED`](#classCelluloBluetoothEnums_1a6e305fb02630d6718f3beb5c082bc1eb) | List of possible visual effects.
`public  `[`GESTURE_ENUM_SHARED`](#classCelluloBluetoothEnums_1abfc65d6b5fdbe7a2f97ba8c9a717e5f3) | List of possible getures.
`public  `[`CelluloBluetoothEnums`](#classCelluloBluetoothEnums_1ab23ed55d47492c5286fe784598cbae50)`(QObject * parent)` | 
`public  `[`~CelluloBluetoothEnums`](#classCelluloBluetoothEnums_1a188ffa7d7087b547d82a1747ed374835)`()` | 

## Members

#### `public  `[`CONNECTION_STATUS_ENUM_SHARED`](#classCelluloBluetoothEnums_1a4dfe101c28ba4cbd6e184ab5cf195938) 

Bluetooth connection status.

#### `public  `[`BATTERY_STATE_ENUM_SHARED`](#classCelluloBluetoothEnums_1ac53f55593d28af6942db35212195ec99) 

Battery state of the robot.

#### `public  `[`LED_RESPONSE_MODE_ENUM_SHARED`](#classCelluloBluetoothEnums_1a1e353b2ba3f28ea7140b565ef1c0ea10) 

LED response mode of the robot.

#### `public  `[`LOCOMOTION_INTERACTIVITY_MODE_ENUM_SHARED`](#classCelluloBluetoothEnums_1a5464d116ce7ff302203ede72f6812707) 

Locomotion interactivity mode of the robot.

#### `public  `[`VISUAL_EFFECT_ENUM_SHARED`](#classCelluloBluetoothEnums_1a6e305fb02630d6718f3beb5c082bc1eb) 

List of possible visual effects.

#### `public  `[`GESTURE_ENUM_SHARED`](#classCelluloBluetoothEnums_1abfc65d6b5fdbe7a2f97ba8c9a717e5f3) 

List of possible getures.

#### `public  `[`CelluloBluetoothEnums`](#classCelluloBluetoothEnums_1ab23ed55d47492c5286fe784598cbae50)`(QObject * parent)` 

#### `public  `[`~CelluloBluetoothEnums`](#classCelluloBluetoothEnums_1a188ffa7d7087b547d82a1747ed374835)`()` 

# class `CelluloBluetoothPacket` 

```
class CelluloBluetoothPacket
  : public QObject
```  

Bluetooth communicator for a Cellulo robot.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`COMMAND_PACKET_TYPE_ENUM_SHARED`](#classCelluloBluetoothPacket_1af1efcb5d00e72ea7bf4aea2c830d92e1) | 
`public  `[`EVENT_PACKET_TYPE_ENUM_SHARED`](#classCelluloBluetoothPacket_1a7c673d26671767fa7bbe21d2f6466609) | 
`public  `[`CelluloBluetoothPacket`](#classCelluloBluetoothPacket_1ae54a46b02e8b4e5103e8be1f47a67682)`()` | Creates a new Cellulo Bluetooth message.
`public virtual  `[`~CelluloBluetoothPacket`](#classCelluloBluetoothPacket_1a5b4c083ded7117fdeddc209bec8fd3f2)`()` | Destroys this Cellulo Bluetooth message.
`public `[`CelluloBluetoothPacket`](#classCelluloBluetoothPacket)` * `[`clone`](#classCelluloBluetoothPacket_1a539ed3a2d1614e815cb2abe56b98ca40)`() const` | Creates a new Cellulo Bluetooth message identical to this.
`public  `[`operator QString`](#classCelluloBluetoothPacket_1a11358b3d2218bf87efae6d150d5733bc)`() const` | Prettyprinting.
`public void `[`setCmdPacketType`](#classCelluloBluetoothPacket_1ac055c5f20fd8fee71c4a6a1f4541e1fc)`(CmdPacketType type)` | Sets the outgoing command message type.
`public void `[`setEventPacketType`](#classCelluloBluetoothPacket_1a4356a9710fbbf377cdf835d9a2464472)`(EventPacketType type)` | Sets the outgoing event message type.
`public void `[`clear`](#classCelluloBluetoothPacket_1abb390e0a4253ccc11704cc096af05020)`()` | Clears the payload.
`public void `[`load`](#classCelluloBluetoothPacket_1ac17d22a987670d81dcf3ac820cfc0ca7)`(quint32 num)` | Appends the given number in binary form to the payload.
`public void `[`load24`](#classCelluloBluetoothPacket_1a0a43bddca8482d14903bcc9473ec4b81)`(quint32 num)` | Appends the first 24 bits of the given number in binary form (2's complement) to the payload.
`public void `[`load`](#classCelluloBluetoothPacket_1accf80fd35e0901950f51886030eaa01c)`(quint16 num)` | Appends the given number in binary form to the payload.
`public void `[`load`](#classCelluloBluetoothPacket_1a87f4e8703de34fc6bc97ed15b00db940)`(quint8 num)` | Appends the given number in binary form to the payload.
`public void `[`load`](#classCelluloBluetoothPacket_1a6bca8cdf2b6f73c653e423c28c0f2373)`(qint32 num)` | Appends the given number in binary form to the payload.
`public void `[`load24`](#classCelluloBluetoothPacket_1a92703c63b7ba9d3dbf7b85eb35c40512)`(qint32 num)` | Appends the first 24 bits of the given number in binary form (2's complement) to the payload.
`public void `[`load`](#classCelluloBluetoothPacket_1a21ddcad8f42cabc40de3efd51ee85ac8)`(qint16 num)` | Appends the given number in binary form to the payload.
`public void `[`load`](#classCelluloBluetoothPacket_1ad13c451e11abbf57fb739a7337223966)`(qint8 num)` | Appends the given number in binary form to the payload.
`public void `[`load`](#classCelluloBluetoothPacket_1a2910b846f2a18f691b13b5094d77d1c2)`(float num)` | Appends the given number in binary form to the payload.
`public QByteArray `[`getCmdSendData`](#classCelluloBluetoothPacket_1a8b83a3d9dbe8c8b89a94f33465166653)`() const` | Constructs the command message to be sent.
`public QByteArray `[`getEventSendData`](#classCelluloBluetoothPacket_1a9b1012e6795ee2fd99c4c65cdeedfd64)`() const` | Constructs the event message to be sent.
`public bool `[`loadEventByte`](#classCelluloBluetoothPacket_1a5548f4124f17192a7921b78ea43ee975)`(char c)` | Processes incoming byte belonging to an event packet, determines type if byte is relevant.
`public bool `[`loadCmdByte`](#classCelluloBluetoothPacket_1a4196014bddfa0ee179a68c75694af750)`(char c)` | Processes incoming byte belonging to an command packet, determines type if byte is relevant.
`public inline EventPacketType `[`getEventPacketType`](#classCelluloBluetoothPacket_1a1fc5a8a94d5a2aba43252634cbabd52a)`() const` | Gets the received event packet type if any.
`public inline CmdPacketType `[`getCmdPacketType`](#classCelluloBluetoothPacket_1a8cebb7c941934ba6e2e83d2d24e7a56d)`() const` | Gets the received command packet type if any.
`public quint32 `[`unloadUInt32`](#classCelluloBluetoothPacket_1aefd2ea676f98d207c2e9c3c42e61af8c)`()` | Attempts to unload a 32-bit unsigned integer.
`public quint32 `[`unloadUInt24`](#classCelluloBluetoothPacket_1a38cea1d7ce8bc65dd00aad2088228d5d)`()` | Attempts to unload a 24-bit unsigned integer.
`public quint16 `[`unloadUInt16`](#classCelluloBluetoothPacket_1aa678d808871063185e9585e4a72b029f)`()` | Attempts to unload a 16-bit unsigned integer.
`public quint8 `[`unloadUInt8`](#classCelluloBluetoothPacket_1af82712cc3705014be0ff2fedbcaffdaa)`()` | Attempts to unload an 8-bit unsigned integer.
`public qint32 `[`unloadInt32`](#classCelluloBluetoothPacket_1a3394afd54ee33b8c2a3aa600bbba1bb4)`()` | Attempts to unload a 32-bit signed integer.
`public qint32 `[`unloadInt24`](#classCelluloBluetoothPacket_1a4de3be0183c200247ee24afcd4c29b38)`()` | Attempts to unload a 24-bit signed integer.
`public qint16 `[`unloadInt16`](#classCelluloBluetoothPacket_1a583c6c07724ea219fbf77f0a833175d0)`()` | Attempts to unload a 16-bit signed integer.
`public qint8 `[`unloadInt8`](#classCelluloBluetoothPacket_1a51d32718a24587a3bcc1fb4159a840ca)`()` | Attempts to unload a 8-bit signed integer.
`public float `[`unloadFloat`](#classCelluloBluetoothPacket_1a6c9410399afa448fecd871a0f44b7423)`()` | Attempts to unload a 32-bit floating point number.

## Members

#### `public  `[`COMMAND_PACKET_TYPE_ENUM_SHARED`](#classCelluloBluetoothPacket_1af1efcb5d00e72ea7bf4aea2c830d92e1) 

#### `public  `[`EVENT_PACKET_TYPE_ENUM_SHARED`](#classCelluloBluetoothPacket_1a7c673d26671767fa7bbe21d2f6466609) 

#### `public  `[`CelluloBluetoothPacket`](#classCelluloBluetoothPacket_1ae54a46b02e8b4e5103e8be1f47a67682)`()` 

Creates a new Cellulo Bluetooth message.

#### `public virtual  `[`~CelluloBluetoothPacket`](#classCelluloBluetoothPacket_1a5b4c083ded7117fdeddc209bec8fd3f2)`()` 

Destroys this Cellulo Bluetooth message.

#### `public `[`CelluloBluetoothPacket`](#classCelluloBluetoothPacket)` * `[`clone`](#classCelluloBluetoothPacket_1a539ed3a2d1614e815cb2abe56b98ca40)`() const` 

Creates a new Cellulo Bluetooth message identical to this.

#### Returns
Identical copy of this packet

#### `public  `[`operator QString`](#classCelluloBluetoothPacket_1a11358b3d2218bf87efae6d150d5733bc)`() const` 

Prettyprinting.

#### Returns
String representation of this object

#### `public void `[`setCmdPacketType`](#classCelluloBluetoothPacket_1ac055c5f20fd8fee71c4a6a1f4541e1fc)`(CmdPacketType type)` 

Sets the outgoing command message type.

#### Parameters
* `type` Outgoing message type

#### `public void `[`setEventPacketType`](#classCelluloBluetoothPacket_1a4356a9710fbbf377cdf835d9a2464472)`(EventPacketType type)` 

Sets the outgoing event message type.

#### Parameters
* `type` Outgoing event message type

#### `public void `[`clear`](#classCelluloBluetoothPacket_1abb390e0a4253ccc11704cc096af05020)`()` 

Clears the payload.

#### `public void `[`load`](#classCelluloBluetoothPacket_1ac17d22a987670d81dcf3ac820cfc0ca7)`(quint32 num)` 

Appends the given number in binary form to the payload.

#### Parameters
* `num` The number to append

#### `public void `[`load24`](#classCelluloBluetoothPacket_1a0a43bddca8482d14903bcc9473ec4b81)`(quint32 num)` 

Appends the first 24 bits of the given number in binary form (2's complement) to the payload.

Clamps the value to 24-bits if outside of bounds.

#### Parameters
* `num` The number to append

#### `public void `[`load`](#classCelluloBluetoothPacket_1accf80fd35e0901950f51886030eaa01c)`(quint16 num)` 

Appends the given number in binary form to the payload.

#### Parameters
* `num` The number to append

#### `public void `[`load`](#classCelluloBluetoothPacket_1a87f4e8703de34fc6bc97ed15b00db940)`(quint8 num)` 

Appends the given number in binary form to the payload.

#### Parameters
* `num` The number to append

#### `public void `[`load`](#classCelluloBluetoothPacket_1a6bca8cdf2b6f73c653e423c28c0f2373)`(qint32 num)` 

Appends the given number in binary form to the payload.

#### Parameters
* `num` The number to append

#### `public void `[`load24`](#classCelluloBluetoothPacket_1a92703c63b7ba9d3dbf7b85eb35c40512)`(qint32 num)` 

Appends the first 24 bits of the given number in binary form (2's complement) to the payload.

Clamps the value to 24-bits if outside of bounds.

#### Parameters
* `num` The number to append

#### `public void `[`load`](#classCelluloBluetoothPacket_1a21ddcad8f42cabc40de3efd51ee85ac8)`(qint16 num)` 

Appends the given number in binary form to the payload.

#### Parameters
* `num` The number to append

#### `public void `[`load`](#classCelluloBluetoothPacket_1ad13c451e11abbf57fb739a7337223966)`(qint8 num)` 

Appends the given number in binary form to the payload.

#### Parameters
* `num` The number to append

#### `public void `[`load`](#classCelluloBluetoothPacket_1a2910b846f2a18f691b13b5094d77d1c2)`(float num)` 

Appends the given number in binary form to the payload.

#### Parameters
* `num` The number to append

#### `public QByteArray `[`getCmdSendData`](#classCelluloBluetoothPacket_1a8b83a3d9dbe8c8b89a94f33465166653)`() const` 

Constructs the command message to be sent.

#### Returns
Command message to be sent

#### `public QByteArray `[`getEventSendData`](#classCelluloBluetoothPacket_1a9b1012e6795ee2fd99c4c65cdeedfd64)`() const` 

Constructs the event message to be sent.

#### Returns
Event message to be sent

#### `public bool `[`loadEventByte`](#classCelluloBluetoothPacket_1a5548f4124f17192a7921b78ea43ee975)`(char c)` 

Processes incoming byte belonging to an event packet, determines type if byte is relevant.

#### Parameters
* `c` Incoming event packet byte 

#### Returns
Whether the packet is completely received

#### `public bool `[`loadCmdByte`](#classCelluloBluetoothPacket_1a4196014bddfa0ee179a68c75694af750)`(char c)` 

Processes incoming byte belonging to an command packet, determines type if byte is relevant.

#### Parameters
* `c` Incoming command packet byte 

#### Returns
Whether the packet is completely received

#### `public inline EventPacketType `[`getEventPacketType`](#classCelluloBluetoothPacket_1a1fc5a8a94d5a2aba43252634cbabd52a)`() const` 

Gets the received event packet type if any.

#### Returns
The received event packet type

#### `public inline CmdPacketType `[`getCmdPacketType`](#classCelluloBluetoothPacket_1a8cebb7c941934ba6e2e83d2d24e7a56d)`() const` 

Gets the received command packet type if any.

#### Returns
The received command packet type

#### `public quint32 `[`unloadUInt32`](#classCelluloBluetoothPacket_1aefd2ea676f98d207c2e9c3c42e61af8c)`()` 

Attempts to unload a 32-bit unsigned integer.

#### Returns
Unloaded value if successful

#### `public quint32 `[`unloadUInt24`](#classCelluloBluetoothPacket_1a38cea1d7ce8bc65dd00aad2088228d5d)`()` 

Attempts to unload a 24-bit unsigned integer.

#### Returns
Unloaded value if successful

#### `public quint16 `[`unloadUInt16`](#classCelluloBluetoothPacket_1aa678d808871063185e9585e4a72b029f)`()` 

Attempts to unload a 16-bit unsigned integer.

#### Returns
Unloaded value if successful

#### `public quint8 `[`unloadUInt8`](#classCelluloBluetoothPacket_1af82712cc3705014be0ff2fedbcaffdaa)`()` 

Attempts to unload an 8-bit unsigned integer.

#### Returns
Unloaded value if successful

#### `public qint32 `[`unloadInt32`](#classCelluloBluetoothPacket_1a3394afd54ee33b8c2a3aa600bbba1bb4)`()` 

Attempts to unload a 32-bit signed integer.

#### Returns
Unloaded value if successful

#### `public qint32 `[`unloadInt24`](#classCelluloBluetoothPacket_1a4de3be0183c200247ee24afcd4c29b38)`()` 

Attempts to unload a 24-bit signed integer.

#### Returns
Unloaded value if successful

#### `public qint16 `[`unloadInt16`](#classCelluloBluetoothPacket_1a583c6c07724ea219fbf77f0a833175d0)`()` 

Attempts to unload a 16-bit signed integer.

#### Returns
Unloaded value if successful

#### `public qint8 `[`unloadInt8`](#classCelluloBluetoothPacket_1a51d32718a24587a3bcc1fb4159a840ca)`()` 

Attempts to unload a 8-bit signed integer.

#### Returns
Unloaded value if successful

#### `public float `[`unloadFloat`](#classCelluloBluetoothPacket_1a6c9410399afa448fecd871a0f44b7423)`()` 

Attempts to unload a 32-bit floating point number.

#### Returns
Unloaded value if successful

# class `CelluloBluetoothScanner` 

```
class CelluloBluetoothScanner
  : public QQuickItem
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} bool `[`continuous`](#classCelluloBluetoothScanner_1a14148bced248eb2718eab2761674bfdf) | Whether to continuously scan.
`{property} bool `[`scanning`](#classCelluloBluetoothScanner_1a1a20e2fa83811cdf0a4aa1719e947af5) | 
`{property} QStringList `[`foundRobots`](#classCelluloBluetoothScanner_1ab5bf8c5660aaed4825f1fa56a034e9d4) | List of robot MAC addresses that are found.
`public  `[`CelluloBluetoothScanner`](#classCelluloBluetoothScanner_1aaabcd5a86babbdee4f8b34fce274de34)`(QQuickItem * parent)` | Creates a new Cellulo robot scanner.
`public virtual  `[`~CelluloBluetoothScanner`](#classCelluloBluetoothScanner_1a589f4beeb292795676ddc9d2e0cb7fda)`()` | Destroys this Cellulo robot scanner.
`public bool `[`isScanning`](#classCelluloBluetoothScanner_1ac9b4f45b98b0300c6b3fc6d4f74d11df)`() const` | Gets whether currently scanning.
`public inline QStringList `[`getFoundRobots`](#classCelluloBluetoothScanner_1af535605bcf5d931f2ecf6748625922f4)`() const` | Gets the list of found robot MAC addresses.
`{signal} public void `[`robotDiscovered`](#classCelluloBluetoothScanner_1a793a02b08e02b4d871fd04860ed3944f)`(QString const & macAddr)` | Emitted when a new Cellulo robot is discovered.
`{signal} public void `[`finished`](#classCelluloBluetoothScanner_1a1dd46e5241eed46a317de3ef93298c71)`()` | Emitted when scanning finishes.
`{signal} public void `[`scanningChanged`](#classCelluloBluetoothScanner_1ac7a4a553601681e1b4f1409a0989ef4c)`()` | Emitted when scan stops or starts.
`{signal} public void `[`foundRobotsChanged`](#classCelluloBluetoothScanner_1a205e132b289bec1e783c77e026ba0f38)`()` | Emitted when list of found robot MAC addresses changes.
`{slot} public void `[`start`](#classCelluloBluetoothScanner_1a05cd4bd6e5d5e2ec128a9fdf4139524d)`()` | Starts scanning.
`{slot} public void `[`stop`](#classCelluloBluetoothScanner_1af8647804881f980d27e615fb79b01f60)`()` | Stops scanning.
`{slot} public void `[`clear`](#classCelluloBluetoothScanner_1a1a5039be91a7b554bfec282be915ae70)`()` | Clears the list of found robots.

## Members

#### `{property} bool `[`continuous`](#classCelluloBluetoothScanner_1a14148bced248eb2718eab2761674bfdf) 

Whether to continuously scan.

#### `{property} bool `[`scanning`](#classCelluloBluetoothScanner_1a1a20e2fa83811cdf0a4aa1719e947af5) 

#### `{property} QStringList `[`foundRobots`](#classCelluloBluetoothScanner_1ab5bf8c5660aaed4825f1fa56a034e9d4) 

List of robot MAC addresses that are found.

#### `public  `[`CelluloBluetoothScanner`](#classCelluloBluetoothScanner_1aaabcd5a86babbdee4f8b34fce274de34)`(QQuickItem * parent)` 

Creates a new Cellulo robot scanner.

#### Parameters
* `parent` Parent of this QML item

#### `public virtual  `[`~CelluloBluetoothScanner`](#classCelluloBluetoothScanner_1a589f4beeb292795676ddc9d2e0cb7fda)`()` 

Destroys this Cellulo robot scanner.

#### `public bool `[`isScanning`](#classCelluloBluetoothScanner_1ac9b4f45b98b0300c6b3fc6d4f74d11df)`() const` 

Gets whether currently scanning.

#### Returns
Whether currently scanning

#### `public inline QStringList `[`getFoundRobots`](#classCelluloBluetoothScanner_1af535605bcf5d931f2ecf6748625922f4)`() const` 

Gets the list of found robot MAC addresses.

#### Returns
The list of found robot MAC addresses

#### `{signal} public void `[`robotDiscovered`](#classCelluloBluetoothScanner_1a793a02b08e02b4d871fd04860ed3944f)`(QString const & macAddr)` 

Emitted when a new Cellulo robot is discovered.

#### Parameters
* `macAddr` Mac address of the newly discovered robot

#### `{signal} public void `[`finished`](#classCelluloBluetoothScanner_1a1dd46e5241eed46a317de3ef93298c71)`()` 

Emitted when scanning finishes.

#### `{signal} public void `[`scanningChanged`](#classCelluloBluetoothScanner_1ac7a4a553601681e1b4f1409a0989ef4c)`()` 

Emitted when scan stops or starts.

#### `{signal} public void `[`foundRobotsChanged`](#classCelluloBluetoothScanner_1a205e132b289bec1e783c77e026ba0f38)`()` 

Emitted when list of found robot MAC addresses changes.

#### `{slot} public void `[`start`](#classCelluloBluetoothScanner_1a05cd4bd6e5d5e2ec128a9fdf4139524d)`()` 

Starts scanning.

#### `{slot} public void `[`stop`](#classCelluloBluetoothScanner_1af8647804881f980d27e615fb79b01f60)`()` 

Stops scanning.

#### `{slot} public void `[`clear`](#classCelluloBluetoothScanner_1a1a5039be91a7b554bfec282be915ae70)`()` 

Clears the list of found robots.

# class `CelluloCommUtil` 

```
class CelluloCommUtil
  : public QObject
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CelluloCommUtil`](#classCelluloCommUtil_1af00a865bc2754fb4ae980212622664c9)`(QObject * parent)` | 
`public virtual  `[`~CelluloCommUtil`](#classCelluloCommUtil_1af58ca708188dc6196ca8f2d10b1d8c61)`()` | 
`enum `[`RelayProtocol`](#classCelluloCommUtil_1ad5d3ecb403413a31b98c9d85f9faa32c) | Underlying transfer protocols supported by the relay servers and clients.

## Members

#### `public  `[`CelluloCommUtil`](#classCelluloCommUtil_1af00a865bc2754fb4ae980212622664c9)`(QObject * parent)` 

#### `public virtual  `[`~CelluloCommUtil`](#classCelluloCommUtil_1af58ca708188dc6196ca8f2d10b1d8c61)`()` 

#### `enum `[`RelayProtocol`](#classCelluloCommUtil_1ad5d3ecb403413a31b98c9d85f9faa32c) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
Local            | Unix domain socket.
Tcp            | TCP socket.

Underlying transfer protocols supported by the relay servers and clients.

# class `CelluloLocalRelayClient` 

```
class CelluloLocalRelayClient
  : public CelluloRelayClient
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CelluloLocalRelayClient`](#classCelluloLocalRelayClient_1a1d68e9485d3f5a81a633c1c8f6ce9da1)`(QQuickItem * parent)` | Creates a new [CelluloLocalRelayClient](#classCelluloLocalRelayClient) with the given QML parent.
`public virtual  `[`~CelluloLocalRelayClient`](#classCelluloLocalRelayClient_1a9aa8f1be42c64d796807546d67e77ced)`()` | Destroys this [CelluloLocalRelayClient](#classCelluloLocalRelayClient).

## Members

#### `public  `[`CelluloLocalRelayClient`](#classCelluloLocalRelayClient_1a1d68e9485d3f5a81a633c1c8f6ce9da1)`(QQuickItem * parent)` 

Creates a new [CelluloLocalRelayClient](#classCelluloLocalRelayClient) with the given QML parent.

#### Parameters
* `parent` The QML parent

#### `public virtual  `[`~CelluloLocalRelayClient`](#classCelluloLocalRelayClient_1a9aa8f1be42c64d796807546d67e77ced)`()` 

Destroys this [CelluloLocalRelayClient](#classCelluloLocalRelayClient).

# class `CelluloLocalRelayServer` 

```
class CelluloLocalRelayServer
  : public CelluloRelayServer
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CelluloLocalRelayServer`](#classCelluloLocalRelayServer_1ad998bd5e6f463ce17137b482461e9aa4)`(QQuickItem * parent)` | Creates a new [CelluloLocalRelayServer](#classCelluloLocalRelayServer) with the given QML parent.
`public virtual  `[`~CelluloLocalRelayServer`](#classCelluloLocalRelayServer_1a33b3799ac88aa42f28d2ddfc63970ba1)`()` | Destroys this [CelluloLocalRelayServer](#classCelluloLocalRelayServer).

## Members

#### `public  `[`CelluloLocalRelayServer`](#classCelluloLocalRelayServer_1ad998bd5e6f463ce17137b482461e9aa4)`(QQuickItem * parent)` 

Creates a new [CelluloLocalRelayServer](#classCelluloLocalRelayServer) with the given QML parent.

#### Parameters
* `parent` The QML parent

#### `public virtual  `[`~CelluloLocalRelayServer`](#classCelluloLocalRelayServer_1a33b3799ac88aa42f28d2ddfc63970ba1)`()` 

Destroys this [CelluloLocalRelayServer](#classCelluloLocalRelayServer).

# class `CelluloMathUtil` 

```
class CelluloMathUtil
  : public QObject
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CelluloMathUtil`](#classCelluloMathUtil_1a8b501aa92bcefbea8b81eb83bf12c329)`(QObject * parent)` | 
`public  `[`~CelluloMathUtil`](#classCelluloMathUtil_1a7437d56c0cb18dc50071635cc19934f2)`()` | 

## Members

#### `public  `[`CelluloMathUtil`](#classCelluloMathUtil_1a8b501aa92bcefbea8b81eb83bf12c329)`(QObject * parent)` 

#### `public  `[`~CelluloMathUtil`](#classCelluloMathUtil_1a7437d56c0cb18dc50071635cc19934f2)`()` 

# class `CelluloRelayClient` 

```
class CelluloRelayClient
  : public QQuickItem
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} bool `[`connected`](#classCelluloRelayClient_1a04c4ab11efbd9e1155768fb110f948e8) | 
`{property} QString `[`serverAddress`](#classCelluloRelayClient_1a971dec7154d10d2573f3ead2e6020683) | Server's address, e.g "127.0.0.1".
`{property} int `[`port`](#classCelluloRelayClient_1ab16e05f8895c6621583029d73bb15540) | 
`{property} int `[`autoConnect`](#classCelluloRelayClient_1a443ce2c4020bae476d23491a7db61b47) | 
`{property} QVariantList `[`robots`](#classCelluloRelayClient_1a1566df1bec9695e84651583468dc0141) | 
`public  `[`CelluloRelayClient`](#classCelluloRelayClient_1aa5d3df76b127479580cda28fcc1672d2)`(`[`CelluloCommUtil::RelayProtocol`](#classCelluloCommUtil_1ad5d3ecb403413a31b98c9d85f9faa32c)` protocol,QQuickItem * parent)` | Creates a new [CelluloRelayClient](#classCelluloRelayClient) with the given QML parent.
`public virtual  `[`~CelluloRelayClient`](#classCelluloRelayClient_1a220518075873164bc2199da047a875c7)`()` | Destroys this [CelluloRelayClient](#classCelluloRelayClient).
`public bool `[`isConnected`](#classCelluloRelayClient_1a1f0448aa746ca1d9c5cab7ce9b0ed195)`()` | Gets whether the client is connected to the server.
`public inline bool `[`getAutoConnect`](#classCelluloRelayClient_1a38dfcb11d89db10a6501e14ef1234b9b)`()` | Gets whether the socket tries to reconnect when it drops.
`public void `[`setAutoConnect`](#classCelluloRelayClient_1ae30730ec2839c702c55a0efb35c60b11)`(bool autoConnect)` | Sets whether the socket will try to reconnect when it drops.
`public inline QString `[`getServerAddress`](#classCelluloRelayClient_1a818a29042e7430a670b4a1eabd4e6342)`() const` | Gets the current server's address.
`public void `[`setServerAddress`](#classCelluloRelayClient_1aaf0039b956bdda7034517ca1409cb4c8)`(QString serverAddress)` | Sets the server address to connect to.
`public inline int `[`getPort`](#classCelluloRelayClient_1a80eff6b18307b905c3795ab66c76bad7)`() const` | Gets the current port.
`public void `[`setPort`](#classCelluloRelayClient_1a66ff6a2651ea5a63589b9169870d2361)`(int port)` | Sets the port.
`public QVariantList `[`getRobots`](#classCelluloRelayClient_1ae58443c6de32c353ffe827f9714a3b1e)`() const` | Gets the list of robots belonging to this client.
`{signal} public void `[`connectedChanged`](#classCelluloRelayClient_1ab8235e12a43d95bc2df590d9f3562e9e)`()` | Emitted when connected/disconnected to/from server.
`{signal} public void `[`autoConnectChanged`](#classCelluloRelayClient_1ab803c2b7ffc98424239d9397d0cb3cb9)`()` | Auto connect strategy changed.
`{signal} public void `[`serverAddressChanged`](#classCelluloRelayClient_1a5bd992c77bc94038507cf10ae8628c5e)`()` | Emitted when the server address changes.
`{signal} public void `[`portChanged`](#classCelluloRelayClient_1a3d37db3e79a036f6af85ec4dbb44f846)`()` | Emitted whe the port changes.
`{signal} public void `[`connected`](#classCelluloRelayClient_1aa83e90529db5b28a8004ca585b53d50b)`()` | Emitted when the server socket is connected.
`{signal} public void `[`disconnected`](#classCelluloRelayClient_1a4d69a1bdc018e41c83dd5784a46392f1)`()` | Emitted when the server socket is disconected.
`{signal} public void `[`robotsChanged`](#classCelluloRelayClient_1af5d33a8ed7f225aa3975eef8deb9a428)`()` | Emitted when the robot list changes.
`{signal} public void `[`unknownRobotAtServer`](#classCelluloRelayClient_1ab00116362bf76ce6c838ba371c8a279f)`(QString macAddr)` | Emitted when the server has a robot already connected that is not in the robots list covered by this client.
`{slot} public void `[`connectToServer`](#classCelluloRelayClient_1af22d77704e18200325f2a6742bff80b6)`()` | Initiates a connection to the service on the server.
`{slot} public void `[`disconnectFromServer`](#classCelluloRelayClient_1a7a29e93e4f49f0a64a338f65284b7ae5)`()` | Starts closing the socket.
`{slot} public void `[`addRobot`](#classCelluloRelayClient_1ab3deda55f6440d46c0b48f351d170875)`(`[`CelluloBluetooth`](#classCelluloBluetooth)` * robot,bool select)` | Adds the robot to the robots list, sets the robot's relay client to this object.
`{slot} public void `[`removeRobot`](#classCelluloRelayClient_1aa058c7b7405766a6be8ca862891b22af)`(`[`CelluloBluetooth`](#classCelluloBluetooth)` * robot)` | Removes the robot from the robots list.

## Members

#### `{property} bool `[`connected`](#classCelluloRelayClient_1a04c4ab11efbd9e1155768fb110f948e8) 

#### `{property} QString `[`serverAddress`](#classCelluloRelayClient_1a971dec7154d10d2573f3ead2e6020683) 

Server's address, e.g "127.0.0.1".

#### `{property} int `[`port`](#classCelluloRelayClient_1ab16e05f8895c6621583029d73bb15540) 

#### `{property} int `[`autoConnect`](#classCelluloRelayClient_1a443ce2c4020bae476d23491a7db61b47) 

#### `{property} QVariantList `[`robots`](#classCelluloRelayClient_1a1566df1bec9695e84651583468dc0141) 

#### `public  `[`CelluloRelayClient`](#classCelluloRelayClient_1aa5d3df76b127479580cda28fcc1672d2)`(`[`CelluloCommUtil::RelayProtocol`](#classCelluloCommUtil_1ad5d3ecb403413a31b98c9d85f9faa32c)` protocol,QQuickItem * parent)` 

Creates a new [CelluloRelayClient](#classCelluloRelayClient) with the given QML parent.

#### Parameters
* `protocol` Underlying transfer protocol to use 

* `parent` The QML parent

#### `public virtual  `[`~CelluloRelayClient`](#classCelluloRelayClient_1a220518075873164bc2199da047a875c7)`()` 

Destroys this [CelluloRelayClient](#classCelluloRelayClient).

#### `public bool `[`isConnected`](#classCelluloRelayClient_1a1f0448aa746ca1d9c5cab7ce9b0ed195)`()` 

Gets whether the client is connected to the server.

#### Returns
Whether the client is connected to the server

#### `public inline bool `[`getAutoConnect`](#classCelluloRelayClient_1a38dfcb11d89db10a6501e14ef1234b9b)`()` 

Gets whether the socket tries to reconnect when it drops.

#### Returns
Whether the socket tries to reconnect when it drops

#### `public void `[`setAutoConnect`](#classCelluloRelayClient_1ae30730ec2839c702c55a0efb35c60b11)`(bool autoConnect)` 

Sets whether the socket will try to reconnect when it drops.

#### Parameters
* `autoReconnect` Whether the socket will try to reconnect when it drops

#### `public inline QString `[`getServerAddress`](#classCelluloRelayClient_1a818a29042e7430a670b4a1eabd4e6342)`() const` 

Gets the current server's address.

#### Returns
Current server address, e.g `127.0.0.1` for TCP

#### `public void `[`setServerAddress`](#classCelluloRelayClient_1aaf0039b956bdda7034517ca1409cb4c8)`(QString serverAddress)` 

Sets the server address to connect to.

#### Parameters
* `peer` The new server address, e.g `127.0.0.1` for TCP

#### `public inline int `[`getPort`](#classCelluloRelayClient_1a80eff6b18307b905c3795ab66c76bad7)`() const` 

Gets the current port.

#### Returns
Current port

#### `public void `[`setPort`](#classCelluloRelayClient_1a66ff6a2651ea5a63589b9169870d2361)`(int port)` 

Sets the port.

#### Parameters
* `port` The new port, must be in [0,65535]

#### `public QVariantList `[`getRobots`](#classCelluloRelayClient_1ae58443c6de32c353ffe827f9714a3b1e)`() const` 

Gets the list of robots belonging to this client.

#### Returns
List of robots belonging to this client

#### `{signal} public void `[`connectedChanged`](#classCelluloRelayClient_1ab8235e12a43d95bc2df590d9f3562e9e)`()` 

Emitted when connected/disconnected to/from server.

#### `{signal} public void `[`autoConnectChanged`](#classCelluloRelayClient_1ab803c2b7ffc98424239d9397d0cb3cb9)`()` 

Auto connect strategy changed.

#### `{signal} public void `[`serverAddressChanged`](#classCelluloRelayClient_1a5bd992c77bc94038507cf10ae8628c5e)`()` 

Emitted when the server address changes.

#### `{signal} public void `[`portChanged`](#classCelluloRelayClient_1a3d37db3e79a036f6af85ec4dbb44f846)`()` 

Emitted whe the port changes.

#### `{signal} public void `[`connected`](#classCelluloRelayClient_1aa83e90529db5b28a8004ca585b53d50b)`()` 

Emitted when the server socket is connected.

#### `{signal} public void `[`disconnected`](#classCelluloRelayClient_1a4d69a1bdc018e41c83dd5784a46392f1)`()` 

Emitted when the server socket is disconected.

#### `{signal} public void `[`robotsChanged`](#classCelluloRelayClient_1af5d33a8ed7f225aa3975eef8deb9a428)`()` 

Emitted when the robot list changes.

#### `{signal} public void `[`unknownRobotAtServer`](#classCelluloRelayClient_1ab00116362bf76ce6c838ba371c8a279f)`(QString macAddr)` 

Emitted when the server has a robot already connected that is not in the robots list covered by this client.

#### Parameters
* `macAddr` MAC address of the unknown robot

#### `{slot} public void `[`connectToServer`](#classCelluloRelayClient_1af22d77704e18200325f2a6742bff80b6)`()` 

Initiates a connection to the service on the server.

#### `{slot} public void `[`disconnectFromServer`](#classCelluloRelayClient_1a7a29e93e4f49f0a64a338f65284b7ae5)`()` 

Starts closing the socket.

#### `{slot} public void `[`addRobot`](#classCelluloRelayClient_1ab3deda55f6440d46c0b48f351d170875)`(`[`CelluloBluetooth`](#classCelluloBluetooth)` * robot,bool select)` 

Adds the robot to the robots list, sets the robot's relay client to this object.

#### Parameters
* `robot` New robot 

* `select` Selects the newly added robot as current; pass true if robot is added as a result of an [unknownRobotAtServer()](#classCelluloRelayClient_1ab00116362bf76ce6c838ba371c8a279f) signal

#### `{slot} public void `[`removeRobot`](#classCelluloRelayClient_1aa058c7b7405766a6be8ca862891b22af)`(`[`CelluloBluetooth`](#classCelluloBluetooth)` * robot)` 

Removes the robot from the robots list.

#### Parameters
* `robot` Robot to remove

# class `CelluloRelayServer` 

```
class CelluloRelayServer
  : public QQuickItem
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} QString `[`address`](#classCelluloRelayServer_1abc5bb4b52d5604dea3918aa5116d9ff2) | Host address, e.g "127.0.0.1" for TCP.
`{property} int `[`port`](#classCelluloRelayServer_1a231d9064887546f9b3b6c7c417d44417) | 
`public  `[`CelluloRelayServer`](#classCelluloRelayServer_1a0fd33636ec0ecbff77ab4e30350f54aa)`(`[`CelluloCommUtil::RelayProtocol`](#classCelluloCommUtil_1ad5d3ecb403413a31b98c9d85f9faa32c)` protocol,QQuickItem * parent)` | Creates a new [CelluloRelayServer](#classCelluloRelayServer) with the given QML parent.
`public  `[`~CelluloRelayServer`](#classCelluloRelayServer_1a845c3fa8e623c2c752042051784a499c)`()` | Destroys this [CelluloRelayServer](#classCelluloRelayServer).
`public bool `[`isListening`](#classCelluloRelayServer_1ae2365a6901a3b0eca2d28384f7f0220e)`() const` | Gets whether the server is listening.
`public void `[`setListening`](#classCelluloRelayServer_1a6d57d125c563f335557aa708834b35ad)`(bool enable)` | Enables/disables listening.
`public inline QString `[`getAddress`](#classCelluloRelayServer_1af30edfe0d41ab1ce563192a3369d5467)`() const` | Gets the current host address.
`public void `[`setAddress`](#classCelluloRelayServer_1a076711ad2c93dec691d4195e64538672)`(QString address)` | Sets the host address.
`public inline int `[`getPort`](#classCelluloRelayServer_1a7b1f1d980079e0dd3c8dbb6e792b7eb4)`() const` | Gets the current port.
`public void `[`setPort`](#classCelluloRelayServer_1a82cde258aca0d20443d2e5501842b081)`(int port)` | Sets the port.
`{signal} public void `[`addressChanged`](#classCelluloRelayServer_1a8f96e24229457116a28e53805d5e5140)`()` | Emitted when the host address changes.
`{signal} public void `[`portChanged`](#classCelluloRelayServer_1a4eeb05a798f96c09f490580dec3c6afc)`()` | Emitted whe the port changes.
`{signal} public void `[`clientConnected`](#classCelluloRelayServer_1ac9dcb95002794e8ae6c6eb5432229ca6)`()` | Emitted when a new client connects.
`{signal} public void `[`clientDisconnected`](#classCelluloRelayServer_1acf6e25a38e961463a874eac047f4b0c6)`()` | Emitted when the client disconnects.
`{signal} public void `[`robotAdded`](#classCelluloRelayServer_1ac99a70c736a23a023b24b31c18785dc8)`(QString macAddr)` | Emitted when a new robot is added to the server.
`{signal} public void `[`robotRemoved`](#classCelluloRelayServer_1a9bd76fb184f57283c6b8b14f143735f0)`(QString macAddr)` | Emitted when a robot is removed from the server.
`{slot} public void `[`addRobot`](#classCelluloRelayServer_1aedc9439890646149929f8589b6312eff)`(`[`CelluloBluetooth`](#classCelluloBluetooth)` * robot)` | Adds robot to the robots list, sets the robot's relay server to this object.
`{slot} public void `[`removeRobot`](#classCelluloRelayServer_1ad07138c15ff34f6396365bdaf4562420)`(`[`CelluloBluetooth`](#classCelluloBluetooth)` * robot)` | Removes the robot from the robots list.
`{slot} public void `[`disconnectClient`](#classCelluloRelayServer_1a0b0d7822a00058793f3d717c4db6dfba)`()` | Closes the client's socket.

## Members

#### `{property} QString `[`address`](#classCelluloRelayServer_1abc5bb4b52d5604dea3918aa5116d9ff2) 

Host address, e.g "127.0.0.1" for TCP.

#### `{property} int `[`port`](#classCelluloRelayServer_1a231d9064887546f9b3b6c7c417d44417) 

#### `public  `[`CelluloRelayServer`](#classCelluloRelayServer_1a0fd33636ec0ecbff77ab4e30350f54aa)`(`[`CelluloCommUtil::RelayProtocol`](#classCelluloCommUtil_1ad5d3ecb403413a31b98c9d85f9faa32c)` protocol,QQuickItem * parent)` 

Creates a new [CelluloRelayServer](#classCelluloRelayServer) with the given QML parent.

#### Parameters
* `protocol` Underlying transfer protocol to use 

* `parent` The QML parent

#### `public  `[`~CelluloRelayServer`](#classCelluloRelayServer_1a845c3fa8e623c2c752042051784a499c)`()` 

Destroys this [CelluloRelayServer](#classCelluloRelayServer).

#### `public bool `[`isListening`](#classCelluloRelayServer_1ae2365a6901a3b0eca2d28384f7f0220e)`() const` 

Gets whether the server is listening.

#### Returns
Whether the server is listening

#### `public void `[`setListening`](#classCelluloRelayServer_1a6d57d125c563f335557aa708834b35ad)`(bool enable)` 

Enables/disables listening.

#### Parameters
* `enable` Whether to listen or close the server and stop listening

#### `public inline QString `[`getAddress`](#classCelluloRelayServer_1af30edfe0d41ab1ce563192a3369d5467)`() const` 

Gets the current host address.

#### Returns
Current host address, e.g "127.0.0.1"

#### `public void `[`setAddress`](#classCelluloRelayServer_1a076711ad2c93dec691d4195e64538672)`(QString address)` 

Sets the host address.

#### Parameters
* `host` The new host address, e.g "127.0.0.1"

#### `public inline int `[`getPort`](#classCelluloRelayServer_1a7b1f1d980079e0dd3c8dbb6e792b7eb4)`() const` 

Gets the current port.

#### Returns
Current port

#### `public void `[`setPort`](#classCelluloRelayServer_1a82cde258aca0d20443d2e5501842b081)`(int port)` 

Sets the port.

#### Parameters
* `port` The new port, must be in [0,65535]

#### `{signal} public void `[`addressChanged`](#classCelluloRelayServer_1a8f96e24229457116a28e53805d5e5140)`()` 

Emitted when the host address changes.

#### `{signal} public void `[`portChanged`](#classCelluloRelayServer_1a4eeb05a798f96c09f490580dec3c6afc)`()` 

Emitted whe the port changes.

#### `{signal} public void `[`clientConnected`](#classCelluloRelayServer_1ac9dcb95002794e8ae6c6eb5432229ca6)`()` 

Emitted when a new client connects.

#### `{signal} public void `[`clientDisconnected`](#classCelluloRelayServer_1acf6e25a38e961463a874eac047f4b0c6)`()` 

Emitted when the client disconnects.

#### `{signal} public void `[`robotAdded`](#classCelluloRelayServer_1ac99a70c736a23a023b24b31c18785dc8)`(QString macAddr)` 

Emitted when a new robot is added to the server.

#### Parameters
* `macAddr` MAC address of the added robot

#### `{signal} public void `[`robotRemoved`](#classCelluloRelayServer_1a9bd76fb184f57283c6b8b14f143735f0)`(QString macAddr)` 

Emitted when a robot is removed from the server.

#### Parameters
* `macAddr` MAC address of the removed robot

#### `{slot} public void `[`addRobot`](#classCelluloRelayServer_1aedc9439890646149929f8589b6312eff)`(`[`CelluloBluetooth`](#classCelluloBluetooth)` * robot)` 

Adds robot to the robots list, sets the robot's relay server to this object.

#### Parameters
* `robot` New robot

#### `{slot} public void `[`removeRobot`](#classCelluloRelayServer_1ad07138c15ff34f6396365bdaf4562420)`(`[`CelluloBluetooth`](#classCelluloBluetooth)` * robot)` 

Removes the robot from the robots list.

#### Parameters
* `robot` Existing robot

#### `{slot} public void `[`disconnectClient`](#classCelluloRelayServer_1a0b0d7822a00058793f3d717c4db6dfba)`()` 

Closes the client's socket.

# class `CelluloRobotPoolClient` 

```
class CelluloRobotPoolClient
  : public CelluloLocalRelayClient
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} QJSValue `[`createRobot`](#classCelluloRobotPoolClient_1a3c6d0595b4a283d395c682eeaf1bb78b) | 
`public  `[`CelluloRobotPoolClient`](#classCelluloRobotPoolClient_1ac5602bfae77fb466e45a0980d9d66c77)`(QQuickItem * parent)` | Creates a new [CelluloRobotPoolClient](#classCelluloRobotPoolClient) with the given QML parent.
`public virtual  `[`~CelluloRobotPoolClient`](#classCelluloRobotPoolClient_1a1dfbcdb7eeb2cdef6349b732d7f09a36)`()` | Destroys this [CelluloRobotPoolClient](#classCelluloRobotPoolClient).
`public inline QJSValue `[`getCreateRobot`](#classCelluloRobotPoolClient_1a91659c3e9954f4d210d90fcdc3ec2455)`() const` | Gets the createRobot function.
`public void `[`setCreateRobot`](#classCelluloRobotPoolClient_1a431e4688bdffff39b21c18b584e9c240)`(QJSValue const & function)` | Sets the createRobot function.
`{signal} public void `[`createRobotChanged`](#classCelluloRobotPoolClient_1ab1df06a697039e029d682c26c7ffcefd)`()` | Emitted when the createRobot function changes.

## Members

#### `{property} QJSValue `[`createRobot`](#classCelluloRobotPoolClient_1a3c6d0595b4a283d395c682eeaf1bb78b) 

#### `public  `[`CelluloRobotPoolClient`](#classCelluloRobotPoolClient_1ac5602bfae77fb466e45a0980d9d66c77)`(QQuickItem * parent)` 

Creates a new [CelluloRobotPoolClient](#classCelluloRobotPoolClient) with the given QML parent.

#### Parameters
* `parent` The QML parent

#### `public virtual  `[`~CelluloRobotPoolClient`](#classCelluloRobotPoolClient_1a1dfbcdb7eeb2cdef6349b732d7f09a36)`()` 

Destroys this [CelluloRobotPoolClient](#classCelluloRobotPoolClient).

#### `public inline QJSValue `[`getCreateRobot`](#classCelluloRobotPoolClient_1a91659c3e9954f4d210d90fcdc3ec2455)`() const` 

Gets the createRobot function.

#### Returns
The createRobot function

#### `public void `[`setCreateRobot`](#classCelluloRobotPoolClient_1a431e4688bdffff39b21c18b584e9c240)`(QJSValue const & function)` 

Sets the createRobot function.

#### Parameters
* `function` The createRobot function that takes a string and returns a [CelluloBluetooth](#classCelluloBluetooth) pointer or CelluloBluetooth-derived object pointer

#### `{signal} public void `[`createRobotChanged`](#classCelluloRobotPoolClient_1ab1df06a697039e029d682c26c7ffcefd)`()` 

Emitted when the createRobot function changes.

# class `CelluloSVGUtil` 

```
class CelluloSVGUtil
  : public QObject
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CelluloSVGUtil`](#classCelluloSVGUtil_1adf64961f2be871c8b73ba3ad6f7f8ba2)`(QObject * parent)` | 
`public  `[`~CelluloSVGUtil`](#classCelluloSVGUtil_1a845d491ed398d759ee155f5fba0a0746)`()` | 

## Members

#### `public  `[`CelluloSVGUtil`](#classCelluloSVGUtil_1adf64961f2be871c8b73ba3ad6f7f8ba2)`(QObject * parent)` 

#### `public  `[`~CelluloSVGUtil`](#classCelluloSVGUtil_1a845d491ed398d759ee155f5fba0a0746)`()` 

# class `CelluloSystemUtil` 

```
class CelluloSystemUtil
  : public QObject
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CelluloSystemUtil`](#classCelluloSystemUtil_1a43ff3e8bba32cadab5e6ab290d6e4452)`(QObject * parent)` | 
`public  `[`~CelluloSystemUtil`](#classCelluloSystemUtil_1a78dc0334e629c929987554021fc5483e)`()` | 

## Members

#### `public  `[`CelluloSystemUtil`](#classCelluloSystemUtil_1a43ff3e8bba32cadab5e6ab290d6e4452)`(QObject * parent)` 

#### `public  `[`~CelluloSystemUtil`](#classCelluloSystemUtil_1a78dc0334e629c929987554021fc5483e)`()` 

# class `CelluloTcpRelayClient` 

```
class CelluloTcpRelayClient
  : public CelluloRelayClient
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CelluloTcpRelayClient`](#classCelluloTcpRelayClient_1a425a065be96718d19c4842e741502590)`(QQuickItem * parent)` | Creates a new [CelluloTcpRelayClient](#classCelluloTcpRelayClient) with the given QML parent.
`public virtual  `[`~CelluloTcpRelayClient`](#classCelluloTcpRelayClient_1a84d7fe1961bc3d65c401e5ea97ae9258)`()` | Destroys this [CelluloTcpRelayClient](#classCelluloTcpRelayClient).

## Members

#### `public  `[`CelluloTcpRelayClient`](#classCelluloTcpRelayClient_1a425a065be96718d19c4842e741502590)`(QQuickItem * parent)` 

Creates a new [CelluloTcpRelayClient](#classCelluloTcpRelayClient) with the given QML parent.

#### Parameters
* `parent` The QML parent

#### `public virtual  `[`~CelluloTcpRelayClient`](#classCelluloTcpRelayClient_1a84d7fe1961bc3d65c401e5ea97ae9258)`()` 

Destroys this [CelluloTcpRelayClient](#classCelluloTcpRelayClient).

# class `CelluloTcpRelayServer` 

```
class CelluloTcpRelayServer
  : public CelluloRelayServer
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CelluloTcpRelayServer`](#classCelluloTcpRelayServer_1aa69388909858b45811c75394340d3cd0)`(QQuickItem * parent)` | Creates a new [CelluloTcpRelayServer](#classCelluloTcpRelayServer) with the given QML parent.
`public virtual  `[`~CelluloTcpRelayServer`](#classCelluloTcpRelayServer_1a9462bf717c248280d8a8ca6f90dfd3e7)`()` | Destroys this [CelluloTcpRelayServer](#classCelluloTcpRelayServer).

## Members

#### `public  `[`CelluloTcpRelayServer`](#classCelluloTcpRelayServer_1aa69388909858b45811c75394340d3cd0)`(QQuickItem * parent)` 

Creates a new [CelluloTcpRelayServer](#classCelluloTcpRelayServer) with the given QML parent.

#### Parameters
* `parent` The QML parent

#### `public virtual  `[`~CelluloTcpRelayServer`](#classCelluloTcpRelayServer_1a9462bf717c248280d8a8ca6f90dfd3e7)`()` 

Destroys this [CelluloTcpRelayServer](#classCelluloTcpRelayServer).

# class `CelluloUIUtil` 

```
class CelluloUIUtil
  : public QObject
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CelluloUIUtil`](#classCelluloUIUtil_1ad6799280e5df6f0e7fd871820bde9c9a)`(QObject * parent)` | 
`public  `[`~CelluloUIUtil`](#classCelluloUIUtil_1a393c076decad145b78d6c331abe18244)`()` | 

## Members

#### `public  `[`CelluloUIUtil`](#classCelluloUIUtil_1ad6799280e5df6f0e7fd871820bde9c9a)`(QObject * parent)` 

#### `public  `[`~CelluloUIUtil`](#classCelluloUIUtil_1a393c076decad145b78d6c331abe18244)`()` 

# class `CelluloZone` 

```
class CelluloZone
  : public QQuickItem
```  

[CelluloZone](#classCelluloZone) Base Class for zones.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} bool `[`active`](#classCelluloZone_1a1cb86c87926f59427614c00660bd1448) | Whether the zone is active.
`{property} QString `[`name`](#classCelluloZone_1a8b57709089f40c2ea97d7009a1db6ca7) | Name of the zone.
`{property} `[`CelluloZoneTypes::ZoneType`](#classCelluloZoneTypes_1a40eaca38e1a2988d19a3037515ff19c4)` `[`type`](#classCelluloZone_1a490c46e3151eb487d9d58ae983f782f1) | Type of the zone.
`public  explicit `[`CelluloZone`](#classCelluloZone_1a98c7f1da61fc1a310f260b3e1faf1052)`(QQuickItem * parent)` | Creates a new Cellulo zone.
`public  `[`~CelluloZone`](#classCelluloZone_1ae0a19e2bfb18ade2a276f1ca4b5387f0)`()` | Deletes this zone and its PaintedItem if it exists.
`public inline `[`CelluloZoneTypes::ZoneType`](#classCelluloZoneTypes_1a40eaca38e1a2988d19a3037515ff19c4)` `[`getType`](#classCelluloZone_1a794028ea9138265619271c3f6f608f33)`()` | Get the type of the zone.
`public inline QString `[`getName`](#classCelluloZone_1aa1ae4987f6f5696e2c2724f8893afee5)`()` | Get the name of the zone.
`public void `[`setName`](#classCelluloZone_1a298a7dda330e5e0d91c3ec3953e33f76)`(QString newName)` | Set the name of the zone.
`public inline float `[`isActive`](#classCelluloZone_1a29a1a57c017df11bc5f880437704af58)`()` | Return if the zone is active or not.
`public void `[`setActive`](#classCelluloZone_1ae1d3fe776df4dbe9ae99bbad54363f51)`(float newActive)` | Sets active state.
`public Q_INVOKABLE float `[`calculate`](#classCelluloZone_1a39ace903230c19257453dfe57b61fb55)`(float xRobot,float yRobot,float thetaRobot)` | Calculate the zone quantity of this zone according to the robot's pose.
`public virtual void `[`write`](#classCelluloZone_1ab54e3c290361ae299c6bc783c25f369f)`(QJsonObject & json)` | Write the zone infos to the given json Object.
`public virtual void `[`read`](#classCelluloZone_1a3aeac927017f1f2704803ad4abcae2b7)`(const QJsonObject & json)` | Read the zone infos from the given json Object.
`public void `[`paint`](#classCelluloZone_1a0a7771cd4f3f8bd1a0b79d4e42d15b9d)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Draws this zone onto the painter.
`public Q_INVOKABLE bool `[`isMouseInside`](#classCelluloZone_1aeefefbe734c3ffbc02cac40e21601aa1)`(QVector2D mousePosition,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Get if the mouse position is inside the zone or not.
`public Q_INVOKABLE `[`CelluloZonePaintedItem`](#classCelluloZonePaintedItem)` * `[`createPaintedItem`](#classCelluloZone_1a585293987a8a2d3f31263f61587cb07f)`(QQuickItem * parent,QColor color,qreal physicalPlaygroundWidth,qreal physicalPlaygroundHeight)` | Creates a PaintedItem that is the visual representation of this zone.
`public Q_INVOKABLE void `[`setPaintedItem`](#classCelluloZone_1a9238667164f09ef61e63446a02195eaa)`(`[`CelluloZonePaintedItem`](#classCelluloZonePaintedItem)` * newPaintedItem)` | Associates a painted item with this zone so that it can be redrawn if the zone changes.
`public inline Q_INVOKABLE `[`CelluloZonePaintedItem`](#classCelluloZonePaintedItem)` * `[`getPaintedItem`](#classCelluloZone_1ab5bf229a89f6ef9cd5d2208efb0fae0e)`()` | Get painted item associated with this zone so that its properties can be changed.
`protected void `[`updatePaintedItem`](#classCelluloZone_1a0dc08ce357aab197159dc423b28f02a2)`()` | Repaints the associated PaintedItem (if any)
`{signal} public void `[`activeChanged`](#classCelluloZone_1a26c7b715edfa0095c2b1aa6d19cc7fa7)`()` | Emitted when the active state of the zone changes.
`{signal} public void `[`nameChanged`](#classCelluloZone_1af34f57fa25c7b6ca8fd55a9b5b9c3e1f)`()` | Emitted when the name of the zone changes.
`{signal} public void `[`typeChanged`](#classCelluloZone_1ac91dc2d8867be229ca0532d2460cd9c7)`()` | Emitted when the type of the zone changes.
`{slot} public void `[`onClientPoseChanged`](#classCelluloZone_1adaf286c98ae1aa1f3406d92ee498340d)`(qreal x,qreal y,qreal theta)` | Slot associated to the [CelluloZoneClient](#classCelluloZoneClient) signal poseChanged.

## Members

#### `{property} bool `[`active`](#classCelluloZone_1a1cb86c87926f59427614c00660bd1448) 

Whether the zone is active.

#### `{property} QString `[`name`](#classCelluloZone_1a8b57709089f40c2ea97d7009a1db6ca7) 

Name of the zone.

#### `{property} `[`CelluloZoneTypes::ZoneType`](#classCelluloZoneTypes_1a40eaca38e1a2988d19a3037515ff19c4)` `[`type`](#classCelluloZone_1a490c46e3151eb487d9d58ae983f782f1) 

Type of the zone.

#### `public  explicit `[`CelluloZone`](#classCelluloZone_1a98c7f1da61fc1a310f260b3e1faf1052)`(QQuickItem * parent)` 

Creates a new Cellulo zone.

#### `public  `[`~CelluloZone`](#classCelluloZone_1ae0a19e2bfb18ade2a276f1ca4b5387f0)`()` 

Deletes this zone and its PaintedItem if it exists.

#### `public inline `[`CelluloZoneTypes::ZoneType`](#classCelluloZoneTypes_1a40eaca38e1a2988d19a3037515ff19c4)` `[`getType`](#classCelluloZone_1a794028ea9138265619271c3f6f608f33)`()` 

Get the type of the zone.

#### Returns
Type of the zone

#### `public inline QString `[`getName`](#classCelluloZone_1aa1ae4987f6f5696e2c2724f8893afee5)`()` 

Get the name of the zone.

#### Returns
Name of the zone

#### `public void `[`setName`](#classCelluloZone_1a298a7dda330e5e0d91c3ec3953e33f76)`(QString newName)` 

Set the name of the zone.

#### Parameters
* `newName` new name for the zone

#### `public inline float `[`isActive`](#classCelluloZone_1a29a1a57c017df11bc5f880437704af58)`()` 

Return if the zone is active or not.

#### Returns
Active state

#### `public void `[`setActive`](#classCelluloZone_1ae1d3fe776df4dbe9ae99bbad54363f51)`(float newActive)` 

Sets active state.

#### Parameters
* `newActive` new active state

#### `public Q_INVOKABLE float `[`calculate`](#classCelluloZone_1a39ace903230c19257453dfe57b61fb55)`(float xRobot,float yRobot,float thetaRobot)` 

Calculate the zone quantity of this zone according to the robot's pose.

#### Parameters
* `xRobot` x position of the robot 

* `yRobot` y position of the robot 

* `thetaRobot` theta position of the robot

#### Returns
Zone quantity for this zone and this robot's pose

#### `public virtual void `[`write`](#classCelluloZone_1ab54e3c290361ae299c6bc783c25f369f)`(QJsonObject & json)` 

Write the zone infos to the given json Object.

#### Parameters
* `QJsonObject` Json object to be written

#### `public virtual void `[`read`](#classCelluloZone_1a3aeac927017f1f2704803ad4abcae2b7)`(const QJsonObject & json)` 

Read the zone infos from the given json Object.

#### Parameters
* `json` Json object to be read

#### `public void `[`paint`](#classCelluloZone_1a0a7771cd4f3f8bd1a0b79d4e42d15b9d)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Draws this zone onto the painter.

#### Parameters
* `painter` Object to draw onto 

* `color` Color to paint with 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

#### `public Q_INVOKABLE bool `[`isMouseInside`](#classCelluloZone_1aeefefbe734c3ffbc02cac40e21601aa1)`(QVector2D mousePosition,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Get if the mouse position is inside the zone or not.

#### Parameters
* `mousePosition` (x,y) coordinates of the mouse in pixels 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

#### Returns
Whether the mouse position is inside the zone or not

#### `public Q_INVOKABLE `[`CelluloZonePaintedItem`](#classCelluloZonePaintedItem)` * `[`createPaintedItem`](#classCelluloZone_1a585293987a8a2d3f31263f61587cb07f)`(QQuickItem * parent,QColor color,qreal physicalPlaygroundWidth,qreal physicalPlaygroundHeight)` 

Creates a PaintedItem that is the visual representation of this zone.

#### Parameters
* `parent` Visual QML parent that this item will fill 

* `color` Color to paint with 

* `physicalPlaygroundWidth` Playground width in mm 

* `physicalPlaygroundHeight` Playground height in mm

#### Returns
A PaintedItem that is the visual representation of this zone

#### `public Q_INVOKABLE void `[`setPaintedItem`](#classCelluloZone_1a9238667164f09ef61e63446a02195eaa)`(`[`CelluloZonePaintedItem`](#classCelluloZonePaintedItem)` * newPaintedItem)` 

Associates a painted item with this zone so that it can be redrawn if the zone changes.

#### Parameters
* `newPaintedItem` New painted item

#### `public inline Q_INVOKABLE `[`CelluloZonePaintedItem`](#classCelluloZonePaintedItem)` * `[`getPaintedItem`](#classCelluloZone_1ab5bf229a89f6ef9cd5d2208efb0fae0e)`()` 

Get painted item associated with this zone so that its properties can be changed.

#### Returns
The PaintedItem that is the visual representation of this zone

#### `protected void `[`updatePaintedItem`](#classCelluloZone_1a0dc08ce357aab197159dc423b28f02a2)`()` 

Repaints the associated PaintedItem (if any)

#### `{signal} public void `[`activeChanged`](#classCelluloZone_1a26c7b715edfa0095c2b1aa6d19cc7fa7)`()` 

Emitted when the active state of the zone changes.

#### `{signal} public void `[`nameChanged`](#classCelluloZone_1af34f57fa25c7b6ca8fd55a9b5b9c3e1f)`()` 

Emitted when the name of the zone changes.

#### `{signal} public void `[`typeChanged`](#classCelluloZone_1ac91dc2d8867be229ca0532d2460cd9c7)`()` 

Emitted when the type of the zone changes.

#### `{slot} public void `[`onClientPoseChanged`](#classCelluloZone_1adaf286c98ae1aa1f3406d92ee498340d)`(qreal x,qreal y,qreal theta)` 

Slot associated to the [CelluloZoneClient](#classCelluloZoneClient) signal poseChanged.

Calculates zone quantity for the sender client (must inherit [CelluloZoneClient](#classCelluloZoneClient)) if zone is active

#### Parameters
* `x` New x coordinate of the client 

* `y` New y coordinate of the client 

* `theta` New orientaton of the client

# class `CelluloZoneAngle` 

```
class CelluloZoneAngle
  : public CelluloZone
```  

Describes a single angle.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} float `[`angle`](#classCelluloZoneAngle_1a868ed4c6795e84fa75b93458e9e881e8) | 
`public  `[`CelluloZoneAngle`](#classCelluloZoneAngle_1ae87065050da168bbf4890fe9a6e4c59e)`()` | Creates a new Cellulo angular zone.
`public inline float `[`getAngle`](#classCelluloZoneAngle_1abceeda733b03a8b8532a6afea1d878a5)`()` | Gets the angle.
`public void `[`setAngle`](#classCelluloZoneAngle_1a5f3375fcaa7db65e01da4b410025fed9)`(float newAngle)` | Sets the angle.
`public virtual void `[`write`](#classCelluloZoneAngle_1a17078e937eb1add7a82dbbea6d2af6f2)`(QJsonObject & json)` | Write the zone infos to the given json Object.
`public virtual void `[`read`](#classCelluloZoneAngle_1aa46ecc0e27104f500df90ef72ade6bb3)`(const QJsonObject & json)` | Read the zone infos from the given json Object.
`public virtual void `[`paint`](#classCelluloZoneAngle_1aefddd432c08da08c4105a668319f0c04)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Draws this zone onto the painter.
`public virtual Q_INVOKABLE bool `[`isMouseInside`](#classCelluloZoneAngle_1ad3d245880a51624491512714896be19f)`(QVector2D mousePosition,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Get if the mouse position is inside the zone or not.
`protected qreal `[`angle`](#classCelluloZoneAngle_1a95dd6b06415cd424ae0c390e982ab68a) | The angle.
`{signal} public void `[`angleChanged`](#classCelluloZoneAngle_1a0c73478308e2ff3283edb15a107ff0f6)`()` | Emitted when the angle changes.

## Members

#### `{property} float `[`angle`](#classCelluloZoneAngle_1a868ed4c6795e84fa75b93458e9e881e8) 

#### `public  `[`CelluloZoneAngle`](#classCelluloZoneAngle_1ae87065050da168bbf4890fe9a6e4c59e)`()` 

Creates a new Cellulo angular zone.

[CelluloZoneAngle](#classCelluloZoneAngle)

#### `public inline float `[`getAngle`](#classCelluloZoneAngle_1abceeda733b03a8b8532a6afea1d878a5)`()` 

Gets the angle.

#### Returns
The angle

#### `public void `[`setAngle`](#classCelluloZoneAngle_1a5f3375fcaa7db65e01da4b410025fed9)`(float newAngle)` 

Sets the angle.

#### Parameters
* `newAngle` New angle

#### `public virtual void `[`write`](#classCelluloZoneAngle_1a17078e937eb1add7a82dbbea6d2af6f2)`(QJsonObject & json)` 

Write the zone infos to the given json Object.

#### Parameters
* `QJsonObject` json object to be written

#### `public virtual void `[`read`](#classCelluloZoneAngle_1aa46ecc0e27104f500df90ef72ade6bb3)`(const QJsonObject & json)` 

Read the zone infos from the given json Object.

#### Parameters
* `json` json object to be read

#### `public virtual void `[`paint`](#classCelluloZoneAngle_1aefddd432c08da08c4105a668319f0c04)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Draws this zone onto the painter.

#### Parameters
* `painter` Object to draw onto 

* `color` Color of the paint 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

#### `public virtual Q_INVOKABLE bool `[`isMouseInside`](#classCelluloZoneAngle_1ad3d245880a51624491512714896be19f)`(QVector2D mousePosition,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Get if the mouse position is inside the zone or not.

#### Parameters
* `mousePosition` (x,y) coordinates of the mouse in pixels 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

#### Returns
Whether the mouse position is inside the zone or not

#### `protected qreal `[`angle`](#classCelluloZoneAngle_1a95dd6b06415cd424ae0c390e982ab68a) 

The angle.

#### `{signal} public void `[`angleChanged`](#classCelluloZoneAngle_1a0c73478308e2ff3283edb15a107ff0f6)`()` 

Emitted when the angle changes.

# class `CelluloZoneAngleDifference` 

```
class CelluloZoneAngleDifference
  : public CelluloZoneAngle
```  

Describes an angular zone sensitive to the client angle difference.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CelluloZoneAngleDifference`](#classCelluloZoneAngleDifference_1a78e2d8b1f2e965c06f585a8284758b44)`()` | [CelluloZoneAngleDifference](#classCelluloZoneAngleDifference)
`public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZoneAngleDifference_1ad1f68fe529bb24c0da06c5fab63befa8)`(float xRobot,float yRobot,float thetaRobot)` | Calculate difference (signed) of the client angle.
`public virtual void `[`paint`](#classCelluloZoneAngleDifference_1a505609de1f6faf5371693a8f263e09ea)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Draws this zone onto the painter.

## Members

#### `public  `[`CelluloZoneAngleDifference`](#classCelluloZoneAngleDifference_1a78e2d8b1f2e965c06f585a8284758b44)`()` 

[CelluloZoneAngleDifference](#classCelluloZoneAngleDifference)

#### `public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZoneAngleDifference_1ad1f68fe529bb24c0da06c5fab63befa8)`(float xRobot,float yRobot,float thetaRobot)` 

Calculate difference (signed) of the client angle.

#### Parameters
* `xRobot` UNUSED 

* `yRobot` UNUSED 

* `thetaRobot` Orientation of the client

#### Returns
Difference between the client angle and this zone angle, between -180 (exclusive) and 180 (inclusive)

#### `public virtual void `[`paint`](#classCelluloZoneAngleDifference_1a505609de1f6faf5371693a8f263e09ea)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Draws this zone onto the painter.

#### Parameters
* `painter` Object to draw onto 

* `color` Color of the paint 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

# class `CelluloZoneAngleInterval` 

```
class CelluloZoneAngleInterval
  : public CelluloZone
```  

Describes an angular interval.

The zone is described by the limits fromAngle to toAngle, in that order; e.g if 330 and 30 are provided, the zone interval includes 0 degrees and not 180 degrees.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} float `[`fromAngle`](#classCelluloZoneAngleInterval_1a217bb9cfd62487383ba095607f762136) | 
`{property} float `[`toAngle`](#classCelluloZoneAngleInterval_1a3d99d2483d4c74a2f0c59fb714658db1) | 
`public  `[`CelluloZoneAngleInterval`](#classCelluloZoneAngleInterval_1aa109814561caa582418ea71f9e62c20b)`()` | Creates a new Cellulo angular zone.
`public inline float `[`getFromAngle`](#classCelluloZoneAngleInterval_1a67fb2c07abb96c4f315ce9534de43f51)`()` | Gets the first limit angle.
`public void `[`setFromAngle`](#classCelluloZoneAngleInterval_1a7002a2e65a606bfd7abd29028fcd46ee)`(float newFromAngle)` | Sets the first limit angle.
`public inline float `[`getToAngle`](#classCelluloZoneAngleInterval_1a11e7db7a94bf7b628385c690f288a6af)`()` | Gets the second limit angle.
`public void `[`setToAngle`](#classCelluloZoneAngleInterval_1ac9af734a1f584da4f7d349fa66bf4a35)`(float newToAngle)` | Sets the second limit angle.
`public virtual void `[`write`](#classCelluloZoneAngleInterval_1a03141393c1eccbd00f728f9ac18aa84b)`(QJsonObject & json)` | Write the zone infos to the given json Object.
`public virtual void `[`read`](#classCelluloZoneAngleInterval_1a44fd4a3c7dd15b3bbd16f79fa6f81ad8)`(const QJsonObject & json)` | Read the zone infos from the given json Object.
`public virtual void `[`paint`](#classCelluloZoneAngleInterval_1a691f3f9e797ac765a0e1ed78948f113a)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Draws this zone onto the painter.
`public virtual Q_INVOKABLE bool `[`isMouseInside`](#classCelluloZoneAngleInterval_1a232dac69b745cd8cdb05127679207287)`(QVector2D mousePosition,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Get if the mouse position is inside the zone or not.
`protected qreal `[`fromAngle`](#classCelluloZoneAngleInterval_1a2a5028292206d96c65fa90e307736317) | First limit angle.
`protected qreal `[`toAngle`](#classCelluloZoneAngleInterval_1a1c6d68277cd39873bd8380063ab52f7e) | Second limit angle.
`{signal} public void `[`fromAngleChanged`](#classCelluloZoneAngleInterval_1a92e556e420bd2887182bcca878c238fe)`()` | Emitted when the first limit angle changes.
`{signal} public void `[`toAngleChanged`](#classCelluloZoneAngleInterval_1a0f4921a4d4be04a2d885cbc358e57106)`()` | Emitted when the second limit angle changes.

## Members

#### `{property} float `[`fromAngle`](#classCelluloZoneAngleInterval_1a217bb9cfd62487383ba095607f762136) 

#### `{property} float `[`toAngle`](#classCelluloZoneAngleInterval_1a3d99d2483d4c74a2f0c59fb714658db1) 

#### `public  `[`CelluloZoneAngleInterval`](#classCelluloZoneAngleInterval_1aa109814561caa582418ea71f9e62c20b)`()` 

Creates a new Cellulo angular zone.

[CelluloZoneAngleInterval](#classCelluloZoneAngleInterval)

#### `public inline float `[`getFromAngle`](#classCelluloZoneAngleInterval_1a67fb2c07abb96c4f315ce9534de43f51)`()` 

Gets the first limit angle.

#### Returns
First limit angle

#### `public void `[`setFromAngle`](#classCelluloZoneAngleInterval_1a7002a2e65a606bfd7abd29028fcd46ee)`(float newFromAngle)` 

Sets the first limit angle.

#### Parameters
* `newAngle1` First limit angle

#### `public inline float `[`getToAngle`](#classCelluloZoneAngleInterval_1a11e7db7a94bf7b628385c690f288a6af)`()` 

Gets the second limit angle.

#### Returns
Second limit angle

#### `public void `[`setToAngle`](#classCelluloZoneAngleInterval_1ac9af734a1f584da4f7d349fa66bf4a35)`(float newToAngle)` 

Sets the second limit angle.

#### Parameters
* `newAngle1` Second limit angle

#### `public virtual void `[`write`](#classCelluloZoneAngleInterval_1a03141393c1eccbd00f728f9ac18aa84b)`(QJsonObject & json)` 

Write the zone infos to the given json Object.

#### Parameters
* `QJsonObject` json object to be written

#### `public virtual void `[`read`](#classCelluloZoneAngleInterval_1a44fd4a3c7dd15b3bbd16f79fa6f81ad8)`(const QJsonObject & json)` 

Read the zone infos from the given json Object.

#### Parameters
* `json` json object to be read

#### `public virtual void `[`paint`](#classCelluloZoneAngleInterval_1a691f3f9e797ac765a0e1ed78948f113a)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Draws this zone onto the painter.

#### Parameters
* `painter` Object to draw onto 

* `color` Color of the paint 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

#### `public virtual Q_INVOKABLE bool `[`isMouseInside`](#classCelluloZoneAngleInterval_1a232dac69b745cd8cdb05127679207287)`(QVector2D mousePosition,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Get if the mouse position is inside the zone or not.

#### Parameters
* `mousePosition` (x,y) coordinates of the mouse in pixels 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

#### Returns
Whether the mouse position is inside the zone or not

#### `protected qreal `[`fromAngle`](#classCelluloZoneAngleInterval_1a2a5028292206d96c65fa90e307736317) 

First limit angle.

#### `protected qreal `[`toAngle`](#classCelluloZoneAngleInterval_1a1c6d68277cd39873bd8380063ab52f7e) 

Second limit angle.

#### `{signal} public void `[`fromAngleChanged`](#classCelluloZoneAngleInterval_1a92e556e420bd2887182bcca878c238fe)`()` 

Emitted when the first limit angle changes.

#### `{signal} public void `[`toAngleChanged`](#classCelluloZoneAngleInterval_1a0f4921a4d4be04a2d885cbc358e57106)`()` 

Emitted when the second limit angle changes.

# class `CelluloZoneAngleIntervalBorder` 

```
class CelluloZoneAngleIntervalBorder
  : public CelluloZoneAngleInterval
```  

Describes an angular zone sensitive to the client angle being on the border of the interval.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} qreal `[`borderThickness`](#classCelluloZoneAngleIntervalBorder_1a12d0eab53d6f2e3795a3134f18eef302) | The border thickness in degrees.
`public  `[`CelluloZoneAngleIntervalBorder`](#classCelluloZoneAngleIntervalBorder_1a5b20b1ac3379fdc8d6a68f205d0da04d)`()` | CelluloZoneAngleBorder
`public inline qreal `[`getBorderThickness`](#classCelluloZoneAngleIntervalBorder_1a799d32c772850469e211bf2f9ca7fadc)`()` | Gets the border thickness.
`public void `[`setBorderThickness`](#classCelluloZoneAngleIntervalBorder_1ad00cefc79b2dfee381608a8100b39787)`(qreal newThickness)` | Sets the new border thickness.
`public virtual void `[`write`](#classCelluloZoneAngleIntervalBorder_1ad6163cdcce5db969d90055a112ff022d)`(QJsonObject & json)` | Write the zone infos to the given json Object.
`public virtual void `[`read`](#classCelluloZoneAngleIntervalBorder_1af228926cbf11cc0095c0c53c7e495314)`(const QJsonObject & json)` | Read the zone infos from the given json Object.
`public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZoneAngleIntervalBorder_1a420e1532327572c46bb402e7a2a525aa)`(float xRobot,float yRobot,float thetaRobot)` | Calculate whether the robot lies on the border of this angular zone.
`public virtual void `[`paint`](#classCelluloZoneAngleIntervalBorder_1a9e73388b2d20825196b03d22294046c5)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Draws this zone onto the painter.
`{signal} public void `[`borderThicknessChanged`](#classCelluloZoneAngleIntervalBorder_1a4a0e23a19d394d801ed94d752e48626c)`()` | Emitted when border thickness changes.

## Members

#### `{property} qreal `[`borderThickness`](#classCelluloZoneAngleIntervalBorder_1a12d0eab53d6f2e3795a3134f18eef302) 

The border thickness in degrees.

#### `public  `[`CelluloZoneAngleIntervalBorder`](#classCelluloZoneAngleIntervalBorder_1a5b20b1ac3379fdc8d6a68f205d0da04d)`()` 

CelluloZoneAngleBorder

#### `public inline qreal `[`getBorderThickness`](#classCelluloZoneAngleIntervalBorder_1a799d32c772850469e211bf2f9ca7fadc)`()` 

Gets the border thickness.

#### Returns
Border thickness in degrees

#### `public void `[`setBorderThickness`](#classCelluloZoneAngleIntervalBorder_1ad00cefc79b2dfee381608a8100b39787)`(qreal newThickness)` 

Sets the new border thickness.

#### Parameters
* `newThickness` New thickness in degrees

#### `public virtual void `[`write`](#classCelluloZoneAngleIntervalBorder_1ad6163cdcce5db969d90055a112ff022d)`(QJsonObject & json)` 

Write the zone infos to the given json Object.

#### Parameters
* `QJsonObject` json object to be written

#### `public virtual void `[`read`](#classCelluloZoneAngleIntervalBorder_1af228926cbf11cc0095c0c53c7e495314)`(const QJsonObject & json)` 

Read the zone infos from the given json Object.

#### Parameters
* `json` json object to be read

#### `public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZoneAngleIntervalBorder_1a420e1532327572c46bb402e7a2a525aa)`(float xRobot,float yRobot,float thetaRobot)` 

Calculate whether the robot lies on the border of this angular zone.

#### Parameters
* `xRobot` UNUSED 

* `yRobot` UNUSED 

* `thetaRobot` Orientation of the robot in degrees

#### Returns
1 if the robot is on the border of this angular zone, 0 otherwise

#### `public virtual void `[`paint`](#classCelluloZoneAngleIntervalBorder_1a9e73388b2d20825196b03d22294046c5)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Draws this zone onto the painter.

#### Parameters
* `painter` Object to draw onto 

* `color` Color of the paint 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

#### `{signal} public void `[`borderThicknessChanged`](#classCelluloZoneAngleIntervalBorder_1a4a0e23a19d394d801ed94d752e48626c)`()` 

Emitted when border thickness changes.

# class `CelluloZoneAngleIntervalDistance` 

```
class CelluloZoneAngleIntervalDistance
  : public CelluloZoneAngleInterval
```  

Describes an angular zone sensitive to the client orientation distance to the interval.

Always calculates the shortest distance to the interval

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CelluloZoneAngleIntervalDistance`](#classCelluloZoneAngleIntervalDistance_1a9797cf721ec6e4431ca3918d893ddf46)`()` | CelluloZoneAngleDistance
`public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZoneAngleIntervalDistance_1ab654d689e606d45f597d21ea3e22831c)`(float xRobot,float yRobot,float thetaRobot)` | Calculate the distance between the robot orientation and one of the zone limits.
`public virtual void `[`paint`](#classCelluloZoneAngleIntervalDistance_1aaa7e57551f9e69297e7782abd0d34fb6)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Draws this zone onto the painter.

## Members

#### `public  `[`CelluloZoneAngleIntervalDistance`](#classCelluloZoneAngleIntervalDistance_1a9797cf721ec6e4431ca3918d893ddf46)`()` 

CelluloZoneAngleDistance

#### `public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZoneAngleIntervalDistance_1ab654d689e606d45f597d21ea3e22831c)`(float xRobot,float yRobot,float thetaRobot)` 

Calculate the distance between the robot orientation and one of the zone limits.

#### Parameters
* `xRobot` UNUSED 

* `yRobot` UNUSED 

* `thetaRobot` Orientation of the robot

#### Returns
The distance between the robot orientation and the limits of this zone; 0 if inside the zone

#### `public virtual void `[`paint`](#classCelluloZoneAngleIntervalDistance_1aaa7e57551f9e69297e7782abd0d34fb6)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Draws this zone onto the painter.

#### Parameters
* `painter` Object to draw onto 

* `color` Color of the paint 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

# class `CelluloZoneAngleIntervalInner` 

```
class CelluloZoneAngleIntervalInner
  : public CelluloZoneAngleInterval
```  

Describes an angular zone sensitive to the client angle being in/out of the interval.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CelluloZoneAngleIntervalInner`](#classCelluloZoneAngleIntervalInner_1a71b322fd600408796136d35dc209476c)`()` | [CelluloZoneAngleIntervalInner](#classCelluloZoneAngleIntervalInner)
`public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZoneAngleIntervalInner_1ad1d685c5f93259a9994fbdafd970714b)`(float xRobot,float yRobot,float thetaRobot)` | Calculate whether the robot lies inside this angle zone.
`public virtual void `[`paint`](#classCelluloZoneAngleIntervalInner_1ae86eca6d0b631d44d9903dc0b7491b1d)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Draws this zone onto the painter.

## Members

#### `public  `[`CelluloZoneAngleIntervalInner`](#classCelluloZoneAngleIntervalInner_1a71b322fd600408796136d35dc209476c)`()` 

[CelluloZoneAngleIntervalInner](#classCelluloZoneAngleIntervalInner)

#### `public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZoneAngleIntervalInner_1ad1d685c5f93259a9994fbdafd970714b)`(float xRobot,float yRobot,float thetaRobot)` 

Calculate whether the robot lies inside this angle zone.

#### Parameters
* `xRobot` UNUSED 

* `yRobot` UNUSED 

* `thetaRobot` Orientation of the robot

#### Returns
1 if the robot is between the zone's angles, 0 otherwise

#### `public virtual void `[`paint`](#classCelluloZoneAngleIntervalInner_1ae86eca6d0b631d44d9903dc0b7491b1d)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Draws this zone onto the painter.

#### Parameters
* `painter` Object to draw onto 

* `color` Color of the paint 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

# class `CelluloZoneCircle` 

```
class CelluloZoneCircle
  : public CelluloZone
```  

[CelluloZone](#classCelluloZone) Base Class for circular zones.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} float `[`x`](#classCelluloZoneCircle_1a705fb4f7375ac4e978ddbd2353b2721b) | x position of circle's center
`{property} float `[`y`](#classCelluloZoneCircle_1a18ed76e6e7ee7eeb944aed8e192cbfca) | y position of circle's center
`{property} float `[`r`](#classCelluloZoneCircle_1ab2ffe2639de9caf2ffdbcc69b30c1dad) | r the radius of the circle
`public  `[`CelluloZoneCircle`](#classCelluloZoneCircle_1aa58d82d4955390ba56f4987f7755aedf)`()` | Creates a new Cellulo circular zone.
`public inline float `[`getX`](#classCelluloZoneCircle_1a1bf6d927181e5696cd2927988b4cd93e)`()` | Gets the x position of circle's center.
`public void `[`setX`](#classCelluloZoneCircle_1a930b36bac260797b309ba6c816fb1123)`(float newX)` | Updates the x position of circle's center.
`public inline float `[`getY`](#classCelluloZoneCircle_1a24aab67c0fc0f211a102d09c87e5b2a7)`()` | Gets the y position of circle's center.
`public void `[`setY`](#classCelluloZoneCircle_1ab419aa7780a488f4beb89273779735e0)`(float newY)` | Updates the y position of circle's center.
`public inline float `[`getR`](#classCelluloZoneCircle_1acd532b085cf3c2d3437131bcc2338d3f)`()` | Gets the radius of the circle.
`public void `[`setR`](#classCelluloZoneCircle_1abea48a5c8c608ffc4d1ee8b0bd7c1e4e)`(float newR)` | Updates the radius of circle.
`public virtual void `[`write`](#classCelluloZoneCircle_1a3ad60247867aaec009f955baf0391b92)`(QJsonObject & json)` | Write the zone infos to the given json Object.
`public virtual void `[`read`](#classCelluloZoneCircle_1a666114ce8bb84d4498e0fa222d0bd069)`(const QJsonObject & json)` | Read the zone infos from the given json Object.
`public virtual void `[`paint`](#classCelluloZoneCircle_1a56db5a88e8ca5a6dca3766401c6a3602)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Draws this zone onto the painter.
`public virtual Q_INVOKABLE bool `[`isMouseInside`](#classCelluloZoneCircle_1a8829798ac6da245019579e82776ecfc4)`(QVector2D mousePosition,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Get if the mouse position is inside the zone or not.
`protected bool `[`isPointInside`](#classCelluloZoneCircle_1ab6188fe77fe860ea9b36c2f90056844a)`(float pointX,float pointY)` | Get if the point is inside the zone or not.
`{signal} public void `[`xChanged`](#classCelluloZoneCircle_1acbb327a6e6d6e9d8d9fdc99a6584a333)`()` | Emitted when the x position of circular zone's center changes.
`{signal} public void `[`yChanged`](#classCelluloZoneCircle_1a59ee838a4068608de375d60c79ea7fcd)`()` | Emitted when the y position of circular zone's center changes.
`{signal} public void `[`rChanged`](#classCelluloZoneCircle_1aed5f95b8f455f76cbf1444971f98c2ce)`()` | Emitted when r the radius of the circular zone changes.

## Members

#### `{property} float `[`x`](#classCelluloZoneCircle_1a705fb4f7375ac4e978ddbd2353b2721b) 

x position of circle's center

#### `{property} float `[`y`](#classCelluloZoneCircle_1a18ed76e6e7ee7eeb944aed8e192cbfca) 

y position of circle's center

#### `{property} float `[`r`](#classCelluloZoneCircle_1ab2ffe2639de9caf2ffdbcc69b30c1dad) 

r the radius of the circle

#### `public  `[`CelluloZoneCircle`](#classCelluloZoneCircle_1aa58d82d4955390ba56f4987f7755aedf)`()` 

Creates a new Cellulo circular zone.

[CelluloZoneCircle](#classCelluloZoneCircle)

#### `public inline float `[`getX`](#classCelluloZoneCircle_1a1bf6d927181e5696cd2927988b4cd93e)`()` 

Gets the x position of circle's center.

#### Returns
X position of circle's center

#### `public void `[`setX`](#classCelluloZoneCircle_1a930b36bac260797b309ba6c816fb1123)`(float newX)` 

Updates the x position of circle's center.

#### Parameters
* `newX` New x position in mm

#### `public inline float `[`getY`](#classCelluloZoneCircle_1a24aab67c0fc0f211a102d09c87e5b2a7)`()` 

Gets the y position of circle's center.

#### Returns
Y position of circle's center

#### `public void `[`setY`](#classCelluloZoneCircle_1ab419aa7780a488f4beb89273779735e0)`(float newY)` 

Updates the y position of circle's center.

#### Parameters
* `newY` New y position in mm

#### `public inline float `[`getR`](#classCelluloZoneCircle_1acd532b085cf3c2d3437131bcc2338d3f)`()` 

Gets the radius of the circle.

#### Returns
R the radius of the circle

#### `public void `[`setR`](#classCelluloZoneCircle_1abea48a5c8c608ffc4d1ee8b0bd7c1e4e)`(float newR)` 

Updates the radius of circle.

#### Parameters
* `newR` New radius in mm

#### `public virtual void `[`write`](#classCelluloZoneCircle_1a3ad60247867aaec009f955baf0391b92)`(QJsonObject & json)` 

Write the zone infos to the given json Object.

#### Parameters
* `QJsonObject` json object to be written

#### `public virtual void `[`read`](#classCelluloZoneCircle_1a666114ce8bb84d4498e0fa222d0bd069)`(const QJsonObject & json)` 

Read the zone infos from the given json Object.

#### Parameters
* `json` json object to be read

#### `public virtual void `[`paint`](#classCelluloZoneCircle_1a56db5a88e8ca5a6dca3766401c6a3602)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Draws this zone onto the painter.

#### Parameters
* `painter` Object to draw onto 

* `color` Color of the paint 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

#### `public virtual Q_INVOKABLE bool `[`isMouseInside`](#classCelluloZoneCircle_1a8829798ac6da245019579e82776ecfc4)`(QVector2D mousePosition,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Get if the mouse position is inside the zone or not.

#### Parameters
* `mousePosition` (x,y) coordinates of the mouse in pixels 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

#### Returns
Whether the mouse position is inside the zone or not

#### `protected bool `[`isPointInside`](#classCelluloZoneCircle_1ab6188fe77fe860ea9b36c2f90056844a)`(float pointX,float pointY)` 

Get if the point is inside the zone or not.

#### Parameters
* `pointX` x coordinate of the point in mm 

* `pointY` y coordinate of the point in mm

#### Returns
Whether the point is inside the zone or not

#### `{signal} public void `[`xChanged`](#classCelluloZoneCircle_1acbb327a6e6d6e9d8d9fdc99a6584a333)`()` 

Emitted when the x position of circular zone's center changes.

#### `{signal} public void `[`yChanged`](#classCelluloZoneCircle_1a59ee838a4068608de375d60c79ea7fcd)`()` 

Emitted when the y position of circular zone's center changes.

#### `{signal} public void `[`rChanged`](#classCelluloZoneCircle_1aed5f95b8f455f76cbf1444971f98c2ce)`()` 

Emitted when r the radius of the circular zone changes.

# class `CelluloZoneCircleBorder` 

```
class CelluloZoneCircleBorder
  : public CelluloZoneCircle
```  

[CelluloZone](#classCelluloZone) Specific Class for circular zones border determination.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} qreal `[`borderThickness`](#classCelluloZoneCircleBorder_1ae32dbef8d3319d76ad4535ed06417947) | The border thickness in mm.
`public  `[`CelluloZoneCircleBorder`](#classCelluloZoneCircleBorder_1a3eb54014a5e1318a9f88ab6db2428ea0)`()` | [CelluloZoneCircleBorder](#classCelluloZoneCircleBorder)
`public inline qreal `[`getBorderThickness`](#classCelluloZoneCircleBorder_1a2dc44f28b36234efe2cb10c39c33ecb4)`()` | Gets the border thickness.
`public void `[`setBorderThickness`](#classCelluloZoneCircleBorder_1a2353493d731ad2cc9e8b2c441a0b6122)`(qreal newThickness)` | Sets the new border thickness.
`public virtual void `[`write`](#classCelluloZoneCircleBorder_1aabcbafdb1cd8981a6cbe615b5ad0cf75)`(QJsonObject & json)` | Write the zone infos to the given json Object.
`public virtual void `[`read`](#classCelluloZoneCircleBorder_1a10efcb9966299975075f730d1fae6c58)`(const QJsonObject & json)` | Read the zone infos from the given json Object.
`public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZoneCircleBorder_1a936ef8ac34195e681e0578288c3d905e)`(float xRobot,float yRobot,float thetaRobot)` | Calculate whether the robot lies on the border of this circular zone (given the zone's margin)
`public virtual void `[`paint`](#classCelluloZoneCircleBorder_1a0f2b59cff26ce2e6875717fbb59f17e1)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Draws this zone onto the painter.
`{signal} public void `[`borderThicknessChanged`](#classCelluloZoneCircleBorder_1a1e317f6efbf38063981aa6b15747195f)`()` | Emitted when border thickness changes.

## Members

#### `{property} qreal `[`borderThickness`](#classCelluloZoneCircleBorder_1ae32dbef8d3319d76ad4535ed06417947) 

The border thickness in mm.

#### `public  `[`CelluloZoneCircleBorder`](#classCelluloZoneCircleBorder_1a3eb54014a5e1318a9f88ab6db2428ea0)`()` 

[CelluloZoneCircleBorder](#classCelluloZoneCircleBorder)

#### `public inline qreal `[`getBorderThickness`](#classCelluloZoneCircleBorder_1a2dc44f28b36234efe2cb10c39c33ecb4)`()` 

Gets the border thickness.

#### Returns
Border thickness in mm

#### `public void `[`setBorderThickness`](#classCelluloZoneCircleBorder_1a2353493d731ad2cc9e8b2c441a0b6122)`(qreal newThickness)` 

Sets the new border thickness.

#### Parameters
* `newThickness` New thickness in mm

#### `public virtual void `[`write`](#classCelluloZoneCircleBorder_1aabcbafdb1cd8981a6cbe615b5ad0cf75)`(QJsonObject & json)` 

Write the zone infos to the given json Object.

#### Parameters
* `QJsonObject` json object to be written

#### `public virtual void `[`read`](#classCelluloZoneCircleBorder_1a10efcb9966299975075f730d1fae6c58)`(const QJsonObject & json)` 

Read the zone infos from the given json Object.

#### Parameters
* `json` json object to be read

#### `public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZoneCircleBorder_1a936ef8ac34195e681e0578288c3d905e)`(float xRobot,float yRobot,float thetaRobot)` 

Calculate whether the robot lies on the border of this circular zone (given the zone's margin)

#### Parameters
* `xRobot` x position of the robot 

* `yRobot` y position of the robot 

* `thetaRobot` theta position of the robot

#### Returns
1 if the robot is on the border of this circular zone (given the zone's margin) 0 otherwise

#### `public virtual void `[`paint`](#classCelluloZoneCircleBorder_1a0f2b59cff26ce2e6875717fbb59f17e1)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Draws this zone onto the painter.

#### Parameters
* `painter` Object to draw onto 

* `color` Color of the paint 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

#### `{signal} public void `[`borderThicknessChanged`](#classCelluloZoneCircleBorder_1a1e317f6efbf38063981aa6b15747195f)`()` 

Emitted when border thickness changes.

# class `CelluloZoneCircleDistance` 

```
class CelluloZoneCircleDistance
  : public CelluloZoneCircle
```  

[CelluloZone](#classCelluloZone) Specific Class for circular zones distance determination.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CelluloZoneCircleDistance`](#classCelluloZoneCircleDistance_1a00fd9fbfe74e799bd494d9e7d638ffc1)`()` | [CelluloZoneCircleDistance](#classCelluloZoneCircleDistance)
`public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZoneCircleDistance_1a0b7787da86b9785ef2cedb5e3f6279e6)`(float xRobot,float yRobot,float thetaRobot)` | Calculate the distance between the robot pose and the border of this circular zone.
`public virtual void `[`paint`](#classCelluloZoneCircleDistance_1a9bb92b69c197ecf74e6801d08be55dd2)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Draws this zone onto the painter.

## Members

#### `public  `[`CelluloZoneCircleDistance`](#classCelluloZoneCircleDistance_1a00fd9fbfe74e799bd494d9e7d638ffc1)`()` 

[CelluloZoneCircleDistance](#classCelluloZoneCircleDistance)

#### `public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZoneCircleDistance_1a0b7787da86b9785ef2cedb5e3f6279e6)`(float xRobot,float yRobot,float thetaRobot)` 

Calculate the distance between the robot pose and the border of this circular zone.

#### Parameters
* `xRobot` x position of the robot 

* `yRobot` y position of the robot 

* `thetaRobot` theta position of the robot

#### Returns
the distance between the robot pose and the border of this circular zone

#### `public virtual void `[`paint`](#classCelluloZoneCircleDistance_1a9bb92b69c197ecf74e6801d08be55dd2)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Draws this zone onto the painter.

#### Parameters
* `painter` Object to draw onto 

* `color` Color of the paint 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

# class `CelluloZoneCircleInner` 

```
class CelluloZoneCircleInner
  : public CelluloZoneCircle
```  

[CelluloZone](#classCelluloZone) Specific Class for circular zones inner determination.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CelluloZoneCircleInner`](#classCelluloZoneCircleInner_1ae5c069e6f93427186c9cf5c147746d31)`()` | [CelluloZoneCircleInner](#classCelluloZoneCircleInner)
`public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZoneCircleInner_1a1f79e2dfa47703ed524fef974f5a0b52)`(float xRobot,float yRobot,float thetaRobot)` | Calculate whether the robot lies inside this circular zone.
`public virtual void `[`paint`](#classCelluloZoneCircleInner_1ad21d12bb6c84ae3cf6f8b3b6a81336a3)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Draws this zone onto the painter.

## Members

#### `public  `[`CelluloZoneCircleInner`](#classCelluloZoneCircleInner_1ae5c069e6f93427186c9cf5c147746d31)`()` 

[CelluloZoneCircleInner](#classCelluloZoneCircleInner)

#### `public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZoneCircleInner_1a1f79e2dfa47703ed524fef974f5a0b52)`(float xRobot,float yRobot,float thetaRobot)` 

Calculate whether the robot lies inside this circular zone.

#### Parameters
* `xRobot` x position of the robot 

* `yRobot` y position of the robot 

* `thetaRobot` theta position of the robot

#### Returns
1 if the robot is inside this circular zone 0 otherwise

#### `public virtual void `[`paint`](#classCelluloZoneCircleInner_1ad21d12bb6c84ae3cf6f8b3b6a81336a3)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Draws this zone onto the painter.

#### Parameters
* `painter` Object to draw onto 

* `color` Color of the paint 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

# class `CelluloZoneClient` 

```
class CelluloZoneClient
  : public QQuickItem
```  

Describes an object with a physical pose (e.g a robot) that may interact with Cellulo zones.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`CelluloZoneClient`](#classCelluloZoneClient_1ad0713af6744e8526130a30e6dc4fd70d)`(QQuickItem * parent)` | Creates a new zone client.
`{signal} public void `[`zoneValueChanged`](#classCelluloZoneClient_1a124ea5ab47b0e0f4fe7e26021bf5b949)`(QObject * zone,qreal value)` | Emitted when a zone's value with respect to this object changes.
`{signal} public void `[`poseChanged`](#classCelluloZoneClient_1a0ff05b6e35773b4a9a3b83a956f176f6)`(qreal x,qreal y,qreal theta)` | Emitted when the physical pose of the object changes.

## Members

#### `public  explicit `[`CelluloZoneClient`](#classCelluloZoneClient_1ad0713af6744e8526130a30e6dc4fd70d)`(QQuickItem * parent)` 

Creates a new zone client.

#### Parameters
* `parent` Qt parent

#### `{signal} public void `[`zoneValueChanged`](#classCelluloZoneClient_1a124ea5ab47b0e0f4fe7e26021bf5b949)`(QObject * zone,qreal value)` 

Emitted when a zone's value with respect to this object changes.

#### Parameters
* `zone` Zone whose value has changed 

* `value` The new value

#### `{signal} public void `[`poseChanged`](#classCelluloZoneClient_1a0ff05b6e35773b4a9a3b83a956f176f6)`(qreal x,qreal y,qreal theta)` 

Emitted when the physical pose of the object changes.

#### Parameters
* `x` New x coordinate in mm 

* `y` New y coordinate in mm 

* `theta` New orientation in degrees

# class `CelluloZoneEngine` 

```
class CelluloZoneEngine
  : public QQuickItem
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} bool `[`active`](#classCelluloZoneEngine_1af21a16833754b157912485b259c2db86) | Whether clients' poseChanged events are connected to zones; true by default.
`public  explicit `[`CelluloZoneEngine`](#classCelluloZoneEngine_1a48381a96a922d8dd2f7724bba9157b4a)`(QQuickItem * parent)` | Creates a new Cellulo zone engine.
`public virtual  `[`~CelluloZoneEngine`](#classCelluloZoneEngine_1a66739bbd66c2c35f19207f94ca47dbe9)`()` | Destroys this Cellulo robot communicator.
`public Q_INVOKABLE QStringList `[`getAllZoneNames`](#classCelluloZoneEngine_1a9c4ae51e0ffb6400a76641a72724b4b9)`()` | Get list of names of all zones handled by this engine.
`public Q_INVOKABLE QObject * `[`getZoneByName`](#classCelluloZoneEngine_1ad41cf8bb47adcd841becfed21d5a9162)`(QString name)` | Get zone handled by this engine having the corresponding name.
`public Q_INVOKABLE QVariantList `[`getZonesList`](#classCelluloZoneEngine_1afab204ec4f52c77fb0ed4e394eb94067)`()` | Returns the list of all zones in this engine.
`public void `[`addNewZones`](#classCelluloZoneEngine_1aa0f28df700ff362c02a0d65a48b3f6ce)`(QList< `[`CelluloZone`](#classCelluloZone)` *> newZones)` | Adds the given list of zones to the already existing zones.
`public Q_INVOKABLE void `[`addNewZones`](#classCelluloZoneEngine_1adfce795d81ad76bd1fc43b374cf57baa)`(QVariantList newZones)` | Adds the given list of zones to the alreadt existing zones.
`{signal} public void `[`activeChanged`](#classCelluloZoneEngine_1a915c7b1ab1636388eb4e95845e3bc03d)`()` | Emitted when active changes.
`{slot} public inline bool `[`getActive`](#classCelluloZoneEngine_1aaa809ab5c5d984835a0eff09f6ab308b)`()` | Gets whether currently active.
`{slot} public void `[`setActive`](#classCelluloZoneEngine_1a910b3f32fd956bebbf6935e0e5b08b48)`(bool newActive)` | Sets whether the engine is active.
`{slot} public void `[`addNewClient`](#classCelluloZoneEngine_1ab8cb88c248e2e88f6c9dd445a033b793)`(`[`CelluloZoneClient`](#classCelluloZoneClient)` * newClient)` | Adds a new client to the engine, binds to all existing zones.
`{slot} public void `[`addNewZone`](#classCelluloZoneEngine_1a8b3413271ed79534774bfb589200349a)`(`[`CelluloZone`](#classCelluloZone)` * newZone)` | Adds a new zone to the engine, binds to all existing clients.
`{slot} public void `[`clearZones`](#classCelluloZoneEngine_1a6ee190936d4110ac856ace0b198d9863)`()` | Deletes all zones.

## Members

#### `{property} bool `[`active`](#classCelluloZoneEngine_1af21a16833754b157912485b259c2db86) 

Whether clients' poseChanged events are connected to zones; true by default.

#### `public  explicit `[`CelluloZoneEngine`](#classCelluloZoneEngine_1a48381a96a922d8dd2f7724bba9157b4a)`(QQuickItem * parent)` 

Creates a new Cellulo zone engine.

#### Parameters
* `parent` Parent of this QML item

#### `public virtual  `[`~CelluloZoneEngine`](#classCelluloZoneEngine_1a66739bbd66c2c35f19207f94ca47dbe9)`()` 

Destroys this Cellulo robot communicator.

#### `public Q_INVOKABLE QStringList `[`getAllZoneNames`](#classCelluloZoneEngine_1a9c4ae51e0ffb6400a76641a72724b4b9)`()` 

Get list of names of all zones handled by this engine.

#### Returns
Names of the zones handled by this engine

#### `public Q_INVOKABLE QObject * `[`getZoneByName`](#classCelluloZoneEngine_1ad41cf8bb47adcd841becfed21d5a9162)`(QString name)` 

Get zone handled by this engine having the corresponding name.

#### Parameters
* `name` Lookup name for the zone 

#### Returns
First zone handled by this engine to have this name or NULL if not found

#### `public Q_INVOKABLE QVariantList `[`getZonesList`](#classCelluloZoneEngine_1afab204ec4f52c77fb0ed4e394eb94067)`()` 

Returns the list of all zones in this engine.

#### Returns
The list of all zones

#### `public void `[`addNewZones`](#classCelluloZoneEngine_1aa0f28df700ff362c02a0d65a48b3f6ce)`(QList< `[`CelluloZone`](#classCelluloZone)` *> newZones)` 

Adds the given list of zones to the already existing zones.

#### Parameters
* `newZones` New zones

#### `public Q_INVOKABLE void `[`addNewZones`](#classCelluloZoneEngine_1adfce795d81ad76bd1fc43b374cf57baa)`(QVariantList newZones)` 

Adds the given list of zones to the alreadt existing zones.

#### Parameters
* `newZones` New zones (QML-compatible)

#### `{signal} public void `[`activeChanged`](#classCelluloZoneEngine_1a915c7b1ab1636388eb4e95845e3bc03d)`()` 

Emitted when active changes.

#### `{slot} public inline bool `[`getActive`](#classCelluloZoneEngine_1aaa809ab5c5d984835a0eff09f6ab308b)`()` 

Gets whether currently active.

#### Returns
Whether currently active

#### `{slot} public void `[`setActive`](#classCelluloZoneEngine_1a910b3f32fd956bebbf6935e0e5b08b48)`(bool newActive)` 

Sets whether the engine is active.

#### Parameters
* `newActive` Whether the engine should be active

#### `{slot} public void `[`addNewClient`](#classCelluloZoneEngine_1ab8cb88c248e2e88f6c9dd445a033b793)`(`[`CelluloZoneClient`](#classCelluloZoneClient)` * newClient)` 

Adds a new client to the engine, binds to all existing zones.

#### Parameters
* `newClient` Client to add

#### `{slot} public void `[`addNewZone`](#classCelluloZoneEngine_1a8b3413271ed79534774bfb589200349a)`(`[`CelluloZone`](#classCelluloZone)` * newZone)` 

Adds a new zone to the engine, binds to all existing clients.

#### Parameters
* `newZone` Zone to add

#### `{slot} public void `[`clearZones`](#classCelluloZoneEngine_1a6ee190936d4110ac856ace0b198d9863)`()` 

Deletes all zones.

# class `CelluloZoneIrregularPolygon` 

```
class CelluloZoneIrregularPolygon
  : public CelluloZonePolygon
```  

[CelluloZone](#classCelluloZone) Base Class for irregular polygonal zones.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public virtual void `[`paint`](#classCelluloZoneIrregularPolygon_1a6ecbdbc352ed7110c38b8a6387c533d3)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Draws this zone onto the painter.
`public virtual void `[`write`](#classCelluloZoneIrregularPolygon_1a21998264e8137d8834ff31443cabbba9)`(QJsonObject & json)` | Write the zone infos to the given json Object.
`public virtual void `[`read`](#classCelluloZoneIrregularPolygon_1a35cef94fb424112a67ef4ea8e475c232)`(const QJsonObject & json)` | Read the zone infos from the given json Object.

## Members

#### `public virtual void `[`paint`](#classCelluloZoneIrregularPolygon_1a6ecbdbc352ed7110c38b8a6387c533d3)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Draws this zone onto the painter.

#### Parameters
* `painter` Object to draw onto 

* `color` Color of the paint 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

#### `public virtual void `[`write`](#classCelluloZoneIrregularPolygon_1a21998264e8137d8834ff31443cabbba9)`(QJsonObject & json)` 

Write the zone infos to the given json Object.

#### Parameters
* `QJsonObject` json object to be written

[CelluloZoneIrregularPolygon](#classCelluloZoneIrregularPolygon)

#### `public virtual void `[`read`](#classCelluloZoneIrregularPolygon_1a35cef94fb424112a67ef4ea8e475c232)`(const QJsonObject & json)` 

Read the zone infos from the given json Object.

#### Parameters
* `json` json object to be read

# class `CelluloZoneIrregularPolygonBorder` 

```
class CelluloZoneIrregularPolygonBorder
  : public CelluloZoneIrregularPolygon
```  

[CelluloZone](#classCelluloZone) Specific Class for irregular polygonal zones border determination.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} qreal `[`borderThickness`](#classCelluloZoneIrregularPolygonBorder_1a00fc598be1c1ab381494fc1aca170125) | The border thickness in mm.
`public  `[`CelluloZoneIrregularPolygonBorder`](#classCelluloZoneIrregularPolygonBorder_1a9b0040aec43d7292282960cf6bd96f9d)`()` | [CelluloZoneIrregularPolygonBorder](#classCelluloZoneIrregularPolygonBorder)
`public inline qreal `[`getBorderThickness`](#classCelluloZoneIrregularPolygonBorder_1a7f27f6bfccbdcc664ea47d4ce7f09f63)`()` | Gets the border thickness.
`public void `[`setBorderThickness`](#classCelluloZoneIrregularPolygonBorder_1ab4ee96c3f315f44a631b8e1d9ef184a2)`(qreal newThickness)` | Sets the new border thickness.
`public virtual void `[`write`](#classCelluloZoneIrregularPolygonBorder_1a2aa5615c8dd3a89d9db0b179420230b3)`(QJsonObject & json)` | Write the zone infos to the given json Object.
`public virtual void `[`read`](#classCelluloZoneIrregularPolygonBorder_1a39f7b08ae8883d1c60aa2c7fbcc09480)`(const QJsonObject & json)` | Read the zone infos from the given json Object.
`public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZoneIrregularPolygonBorder_1ab588207c4a5b4f8252055cbed191be96)`(float xRobot,float yRobot,float thetaRobot)` | Calculate whether the robot lies on the border of this irregular polygonal zone (given the zone's margin)
`public virtual void `[`paint`](#classCelluloZoneIrregularPolygonBorder_1a2e6c9191e045767e52652fe4f0d08e74)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Draws this zone onto the painter.
`{signal} public void `[`borderThicknessChanged`](#classCelluloZoneIrregularPolygonBorder_1a7da87dcd5e7ec8b5e098bf92d59badfc)`()` | Emitted when border thickness changes.

## Members

#### `{property} qreal `[`borderThickness`](#classCelluloZoneIrregularPolygonBorder_1a00fc598be1c1ab381494fc1aca170125) 

The border thickness in mm.

#### `public  `[`CelluloZoneIrregularPolygonBorder`](#classCelluloZoneIrregularPolygonBorder_1a9b0040aec43d7292282960cf6bd96f9d)`()` 

[CelluloZoneIrregularPolygonBorder](#classCelluloZoneIrregularPolygonBorder)

#### `public inline qreal `[`getBorderThickness`](#classCelluloZoneIrregularPolygonBorder_1a7f27f6bfccbdcc664ea47d4ce7f09f63)`()` 

Gets the border thickness.

#### Returns
Border thickness in mm

#### `public void `[`setBorderThickness`](#classCelluloZoneIrregularPolygonBorder_1ab4ee96c3f315f44a631b8e1d9ef184a2)`(qreal newThickness)` 

Sets the new border thickness.

#### Parameters
* `newThickness` New thickness in mm

#### `public virtual void `[`write`](#classCelluloZoneIrregularPolygonBorder_1a2aa5615c8dd3a89d9db0b179420230b3)`(QJsonObject & json)` 

Write the zone infos to the given json Object.

#### Parameters
* `QJsonObject` json object to be written

#### `public virtual void `[`read`](#classCelluloZoneIrregularPolygonBorder_1a39f7b08ae8883d1c60aa2c7fbcc09480)`(const QJsonObject & json)` 

Read the zone infos from the given json Object.

#### Parameters
* `json` json object to be read

#### `public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZoneIrregularPolygonBorder_1ab588207c4a5b4f8252055cbed191be96)`(float xRobot,float yRobot,float thetaRobot)` 

Calculate whether the robot lies on the border of this irregular polygonal zone (given the zone's margin)

#### Parameters
* `xRobot` x position of the robot 

* `yRobot` y position of the robot 

* `thetaRobot` theta position of the robot

#### Returns
1 if the robot is on the border of this irregular polygonal zone (given the zone's margin) 0 otherwise

#### `public virtual void `[`paint`](#classCelluloZoneIrregularPolygonBorder_1a2e6c9191e045767e52652fe4f0d08e74)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Draws this zone onto the painter.

#### Parameters
* `painter` Object to draw onto 

* `color` Color of the paint 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

#### `{signal} public void `[`borderThicknessChanged`](#classCelluloZoneIrregularPolygonBorder_1a7da87dcd5e7ec8b5e098bf92d59badfc)`()` 

Emitted when border thickness changes.

# class `CelluloZoneIrregularPolygonDistance` 

```
class CelluloZoneIrregularPolygonDistance
  : public CelluloZoneIrregularPolygon
```  

[CelluloZone](#classCelluloZone) Specific Class for irregular polygonal zones distance determination.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CelluloZoneIrregularPolygonDistance`](#classCelluloZoneIrregularPolygonDistance_1ab6e7944339e1b2af23252dd6a7803c3c)`()` | [CelluloZoneIrregularPolygonDistance](#classCelluloZoneIrregularPolygonDistance)
`public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZoneIrregularPolygonDistance_1a436219f5830de214f7db1de32728fe48)`(float xRobot,float yRobot,float thetaRobot)` | Calculate the distance between the robot pose and the border of this irregular polygonal zone.
`public virtual void `[`paint`](#classCelluloZoneIrregularPolygonDistance_1ad394317429b1ea376460e994fae5c782)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Draws this zone onto the painter.

## Members

#### `public  `[`CelluloZoneIrregularPolygonDistance`](#classCelluloZoneIrregularPolygonDistance_1ab6e7944339e1b2af23252dd6a7803c3c)`()` 

[CelluloZoneIrregularPolygonDistance](#classCelluloZoneIrregularPolygonDistance)

#### `public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZoneIrregularPolygonDistance_1a436219f5830de214f7db1de32728fe48)`(float xRobot,float yRobot,float thetaRobot)` 

Calculate the distance between the robot pose and the border of this irregular polygonal zone.

#### Parameters
* `xRobot` x position of the robot 

* `yRobot` y position of the robot 

* `thetaRobot` theta position of the robot

#### Returns
the distance between the robot pose and the border of this irregular polygonal zone

#### `public virtual void `[`paint`](#classCelluloZoneIrregularPolygonDistance_1ad394317429b1ea376460e994fae5c782)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Draws this zone onto the painter.

#### Parameters
* `painter` Object to draw onto 

* `color` Color of the paint 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

# class `CelluloZoneIrregularPolygonInner` 

```
class CelluloZoneIrregularPolygonInner
  : public CelluloZoneIrregularPolygon
```  

[CelluloZone](#classCelluloZone) Specific Class for irregular polygonal zones inner determination.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CelluloZoneIrregularPolygonInner`](#classCelluloZoneIrregularPolygonInner_1aadaf07558e19b43d49bea50e1087469f)`()` | [CelluloZoneIrregularPolygonInner](#classCelluloZoneIrregularPolygonInner)
`public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZoneIrregularPolygonInner_1a8ec7813441aeb784d412122d89ca0b1e)`(float xRobot,float yRobot,float thetaRobot)` | Calculate whether the robot lies inside this irregular polygonal zone.
`public virtual void `[`paint`](#classCelluloZoneIrregularPolygonInner_1acb457154579bb072fc53d23ce8886c5e)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Draws this zone onto the painter.

## Members

#### `public  `[`CelluloZoneIrregularPolygonInner`](#classCelluloZoneIrregularPolygonInner_1aadaf07558e19b43d49bea50e1087469f)`()` 

[CelluloZoneIrregularPolygonInner](#classCelluloZoneIrregularPolygonInner)

#### `public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZoneIrregularPolygonInner_1a8ec7813441aeb784d412122d89ca0b1e)`(float xRobot,float yRobot,float thetaRobot)` 

Calculate whether the robot lies inside this irregular polygonal zone.

#### Parameters
* `xRobot` x position of the robot 

* `yRobot` y position of the robot 

* `thetaRobot` theta position of the robot

#### Returns
1 if the robot is inside this irregular polygonal zone 0 otherwise

#### `public virtual void `[`paint`](#classCelluloZoneIrregularPolygonInner_1acb457154579bb072fc53d23ce8886c5e)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Draws this zone onto the painter.

#### Parameters
* `painter` Object to draw onto 

* `color` Color of the paint 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

# class `CelluloZoneJsonHandler` 

```
class CelluloZoneJsonHandler
  : public QObject
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CelluloZoneJsonHandler`](#classCelluloZoneJsonHandler_1a93e2d01482ee5165de0d4c8457c03da4)`(QObject * parent)` | 
`public  `[`~CelluloZoneJsonHandler`](#classCelluloZoneJsonHandler_1ae98bc265c2aad2fca0489e1acb736f80)`()` | 

## Members

#### `public  `[`CelluloZoneJsonHandler`](#classCelluloZoneJsonHandler_1a93e2d01482ee5165de0d4c8457c03da4)`(QObject * parent)` 

#### `public  `[`~CelluloZoneJsonHandler`](#classCelluloZoneJsonHandler_1ae98bc265c2aad2fca0489e1acb736f80)`()` 

# class `CelluloZoneLine` 

```
class CelluloZoneLine
  : public CelluloZone
```  

[CelluloZone](#classCelluloZone) Base Class for line zones.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} float `[`x1`](#classCelluloZoneLine_1a4c50d03a48199c41839c6db608e8bc1c) | X coordinate of the line's first point.
`{property} float `[`y1`](#classCelluloZoneLine_1a3262164d0c953e2fcd6d6fbfa69dc77a) | Y coordinate of the line's first point.
`{property} float `[`x2`](#classCelluloZoneLine_1af2fd3966196e24a0e5d513ec78a2f236) | X coordinate of the line's second point.
`{property} float `[`y2`](#classCelluloZoneLine_1a537e30d65290c1960d0bf27e68b415ac) | Y coordinate of the line's second point.
`public  `[`CelluloZoneLine`](#classCelluloZoneLine_1a8aa88590e0808e150b68f4a85cde2702)`()` | Creates a new Cellulo line zone.
`public inline float `[`getX1`](#classCelluloZoneLine_1a50be061ca8bea8f73bce830c63df7499)`()` | Gets the x position of the line's first point.
`public void `[`setX1`](#classCelluloZoneLine_1a74b061b6363feaa9a7ce609bf6c5b10b)`(float newX1)` | Updates the x position of the line first point.
`public inline float `[`getY1`](#classCelluloZoneLine_1ac19d67e49fb940e4ddba8c587f4f0342)`()` | Gets the y position of the line's first point.
`public void `[`setY1`](#classCelluloZoneLine_1ac4c056ea7cb7658a75e7edd7406b52fa)`(float newY1)` | Updates the y position of the line first point.
`public inline float `[`getX2`](#classCelluloZoneLine_1a4143ce0ec1fecfaf0999864d1a61f7f9)`()` | Gets the x position of the line's second point.
`public void `[`setX2`](#classCelluloZoneLine_1ada64b86787ea846c2933b287e949bb4c)`(float newX2)` | Updates the x position of the line second point.
`public inline float `[`getY2`](#classCelluloZoneLine_1a81b3385d9f5a25412ee7b6266574bdd2)`()` | Gets the y position of the line's second point.
`public void `[`setY2`](#classCelluloZoneLine_1a80aa6455cb47edc768edce8c58002556)`(float newY2)` | Updates the y position of the line second point.
`public virtual void `[`write`](#classCelluloZoneLine_1ae38831e18ed28fc78f8e244e9a8eb75a)`(QJsonObject & json)` | Write the zone infos to the given json Object.
`public virtual void `[`read`](#classCelluloZoneLine_1a18b334c3ba39d6da90a1317d94ca264d)`(const QJsonObject & json)` | Read the zone infos from the given json Object.
`public virtual void `[`paint`](#classCelluloZoneLine_1a61dd3bd3b59d5ccb5830aa18a2a070fc)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Draws this zone onto the painter.
`public virtual Q_INVOKABLE bool `[`isMouseInside`](#classCelluloZoneLine_1afbf648c660d996b30789204f81777e76)`(QVector2D mousePosition,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Get if the mouse position is inside the zone or not.
`{signal} public void `[`x1Changed`](#classCelluloZoneLine_1ab6c26833f4e2bc4b5595c1abe6099b6d)`()` | Emitted when the X coordinate of the line's first point changes.
`{signal} public void `[`y1Changed`](#classCelluloZoneLine_1a676fb695243d02b732756d1861f030af)`()` | Emitted when the Y coordinate of the line's first point changes.
`{signal} public void `[`x2Changed`](#classCelluloZoneLine_1a59efb078f533fc0749e76d2c8220d9d6)`()` | Emitted when the X coordinate of the line's second point changes.
`{signal} public void `[`y2Changed`](#classCelluloZoneLine_1a74cbc9d170b87ff7be92050859e4bdc4)`()` | Emitted when the Y coordinate of the line's second point changes.

## Members

#### `{property} float `[`x1`](#classCelluloZoneLine_1a4c50d03a48199c41839c6db608e8bc1c) 

X coordinate of the line's first point.

#### `{property} float `[`y1`](#classCelluloZoneLine_1a3262164d0c953e2fcd6d6fbfa69dc77a) 

Y coordinate of the line's first point.

#### `{property} float `[`x2`](#classCelluloZoneLine_1af2fd3966196e24a0e5d513ec78a2f236) 

X coordinate of the line's second point.

#### `{property} float `[`y2`](#classCelluloZoneLine_1a537e30d65290c1960d0bf27e68b415ac) 

Y coordinate of the line's second point.

#### `public  `[`CelluloZoneLine`](#classCelluloZoneLine_1a8aa88590e0808e150b68f4a85cde2702)`()` 

Creates a new Cellulo line zone.

[CelluloZoneLine](#classCelluloZoneLine)

#### `public inline float `[`getX1`](#classCelluloZoneLine_1a50be061ca8bea8f73bce830c63df7499)`()` 

Gets the x position of the line's first point.

#### Returns
X position of the line's first point

#### `public void `[`setX1`](#classCelluloZoneLine_1a74b061b6363feaa9a7ce609bf6c5b10b)`(float newX1)` 

Updates the x position of the line first point.

#### Parameters
* `newx1` New x position in mm

#### `public inline float `[`getY1`](#classCelluloZoneLine_1ac19d67e49fb940e4ddba8c587f4f0342)`()` 

Gets the y position of the line's first point.

#### Returns
Y position of the line's first point

#### `public void `[`setY1`](#classCelluloZoneLine_1ac4c056ea7cb7658a75e7edd7406b52fa)`(float newY1)` 

Updates the y position of the line first point.

#### Parameters
* `newx1` New y position in mm

#### `public inline float `[`getX2`](#classCelluloZoneLine_1a4143ce0ec1fecfaf0999864d1a61f7f9)`()` 

Gets the x position of the line's second point.

#### Returns
X position of the line's second point

#### `public void `[`setX2`](#classCelluloZoneLine_1ada64b86787ea846c2933b287e949bb4c)`(float newX2)` 

Updates the x position of the line second point.

#### Parameters
* `newX2` New x position in mm

#### `public inline float `[`getY2`](#classCelluloZoneLine_1a81b3385d9f5a25412ee7b6266574bdd2)`()` 

Gets the y position of the line's second point.

#### Returns
Y position of the line's second point

#### `public void `[`setY2`](#classCelluloZoneLine_1a80aa6455cb47edc768edce8c58002556)`(float newY2)` 

Updates the y position of the line second point.

#### Parameters
* `newY1` New y position in mm

#### `public virtual void `[`write`](#classCelluloZoneLine_1ae38831e18ed28fc78f8e244e9a8eb75a)`(QJsonObject & json)` 

Write the zone infos to the given json Object.

#### Parameters
* `QJsonObject` json object to be written

#### `public virtual void `[`read`](#classCelluloZoneLine_1a18b334c3ba39d6da90a1317d94ca264d)`(const QJsonObject & json)` 

Read the zone infos from the given json Object.

#### Parameters
* `json` json object to be read

#### `public virtual void `[`paint`](#classCelluloZoneLine_1a61dd3bd3b59d5ccb5830aa18a2a070fc)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Draws this zone onto the painter.

#### Parameters
* `painter` Object to draw onto 

* `color` Color of the paint 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

#### `public virtual Q_INVOKABLE bool `[`isMouseInside`](#classCelluloZoneLine_1afbf648c660d996b30789204f81777e76)`(QVector2D mousePosition,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Get if the mouse position is inside the zone or not.

#### Parameters
* `mousePosition` (x,y) coordinates of the mouse in pixels 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

#### Returns
Whether the mouse position is inside the zone or not

#### `{signal} public void `[`x1Changed`](#classCelluloZoneLine_1ab6c26833f4e2bc4b5595c1abe6099b6d)`()` 

Emitted when the X coordinate of the line's first point changes.

#### `{signal} public void `[`y1Changed`](#classCelluloZoneLine_1a676fb695243d02b732756d1861f030af)`()` 

Emitted when the Y coordinate of the line's first point changes.

#### `{signal} public void `[`x2Changed`](#classCelluloZoneLine_1a59efb078f533fc0749e76d2c8220d9d6)`()` 

Emitted when the X coordinate of the line's second point changes.

#### `{signal} public void `[`y2Changed`](#classCelluloZoneLine_1a74cbc9d170b87ff7be92050859e4bdc4)`()` 

Emitted when the Y coordinate of the line's second point changes.

# class `CelluloZoneLineBorder` 

```
class CelluloZoneLineBorder
  : public CelluloZoneLine
```  

[CelluloZone](#classCelluloZone) Specific Class for determining whether a point is within a distance to an infinite line.

The two points of [CelluloZoneLine](#classCelluloZoneLine) are taken as the two points that this infinite line passes through

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} qreal `[`borderThickness`](#classCelluloZoneLineBorder_1a646ff86bca057885cca7c617367bf4d4) | The border thickness in mm.
`public  `[`CelluloZoneLineBorder`](#classCelluloZoneLineBorder_1acc6e76f092342e3a9052caec21b611ed)`()` | [CelluloZoneLineBorder](#classCelluloZoneLineBorder)
`public inline qreal `[`getBorderThickness`](#classCelluloZoneLineBorder_1a216a4fb825875356e013b41d5b8492cd)`()` | Gets the border thickness.
`public void `[`setBorderThickness`](#classCelluloZoneLineBorder_1a3e3194e4c8a6ee00af3141d0b9328374)`(qreal newThickness)` | Sets the new border thickness.
`public virtual void `[`write`](#classCelluloZoneLineBorder_1af60fb3ef49d568e93ade0fadaacee513)`(QJsonObject & json)` | Write the zone infos to the given json Object.
`public virtual void `[`read`](#classCelluloZoneLineBorder_1aa4e4c2a03873b7dfb4d154a000829956)`(const QJsonObject & json)` | Read the zone infos from the given json Object.
`public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZoneLineBorder_1a7999427a8095f0dc1e8ed8ac04acd127)`(float xRobot,float yRobot,float thetaRobot)` | Calculate whether the distance between the robot position and line is below the border thickness.
`public virtual void `[`paint`](#classCelluloZoneLineBorder_1a9e586639c3b0b9a483a66d470ef3f192)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Draws this zone onto the painter.
`{signal} public void `[`borderThicknessChanged`](#classCelluloZoneLineBorder_1ae2eeb25b410430b60679711773905a22)`()` | Emitted when border thickness changes.

## Members

#### `{property} qreal `[`borderThickness`](#classCelluloZoneLineBorder_1a646ff86bca057885cca7c617367bf4d4) 

The border thickness in mm.

#### `public  `[`CelluloZoneLineBorder`](#classCelluloZoneLineBorder_1acc6e76f092342e3a9052caec21b611ed)`()` 

[CelluloZoneLineBorder](#classCelluloZoneLineBorder)

#### `public inline qreal `[`getBorderThickness`](#classCelluloZoneLineBorder_1a216a4fb825875356e013b41d5b8492cd)`()` 

Gets the border thickness.

#### Returns
Border thickness in mm

#### `public void `[`setBorderThickness`](#classCelluloZoneLineBorder_1a3e3194e4c8a6ee00af3141d0b9328374)`(qreal newThickness)` 

Sets the new border thickness.

#### Parameters
* `newThickness` New thickness in mm

#### `public virtual void `[`write`](#classCelluloZoneLineBorder_1af60fb3ef49d568e93ade0fadaacee513)`(QJsonObject & json)` 

Write the zone infos to the given json Object.

#### Parameters
* `QJsonObject` json object to be written

#### `public virtual void `[`read`](#classCelluloZoneLineBorder_1aa4e4c2a03873b7dfb4d154a000829956)`(const QJsonObject & json)` 

Read the zone infos from the given json Object.

#### Parameters
* `json` json object to be read

#### `public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZoneLineBorder_1a7999427a8095f0dc1e8ed8ac04acd127)`(float xRobot,float yRobot,float thetaRobot)` 

Calculate whether the distance between the robot position and line is below the border thickness.

#### Parameters
* `xRobot` x position of the robot 

* `yRobot` y position of the robot 

* `thetaRobot` theta position of the robot

#### Returns
1 if within border, 0 if outside

#### `public virtual void `[`paint`](#classCelluloZoneLineBorder_1a9e586639c3b0b9a483a66d470ef3f192)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Draws this zone onto the painter.

#### Parameters
* `painter` Object to draw onto 

* `color` Color of the paint 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

#### `{signal} public void `[`borderThicknessChanged`](#classCelluloZoneLineBorder_1ae2eeb25b410430b60679711773905a22)`()` 

Emitted when border thickness changes.

# class `CelluloZoneLineDistanceSigned` 

```
class CelluloZoneLineDistanceSigned
  : public CelluloZoneLine
```  

[CelluloZone](#classCelluloZone) Specific Class for signed line distance determination.

The two points of [CelluloZoneLine](#classCelluloZoneLine) are taken as the two points that this infinite line passes through

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CelluloZoneLineDistanceSigned`](#classCelluloZoneLineDistanceSigned_1a8c317b11e792cbc9000e7211d26ddb88)`()` | [CelluloZoneLineSegmentDistance](#classCelluloZoneLineSegmentDistance)
`public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZoneLineDistanceSigned_1a8e6a08172f47af2bb03e36d2f3440688)`(float xRobot,float yRobot,float thetaRobot)` | Calculate the distance between the robot position and line.
`public virtual void `[`paint`](#classCelluloZoneLineDistanceSigned_1a88974d01e84248fc08df17c4aee277b9)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Draws this zone onto the painter.

## Members

#### `public  `[`CelluloZoneLineDistanceSigned`](#classCelluloZoneLineDistanceSigned_1a8c317b11e792cbc9000e7211d26ddb88)`()` 

[CelluloZoneLineSegmentDistance](#classCelluloZoneLineSegmentDistance)

#### `public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZoneLineDistanceSigned_1a8e6a08172f47af2bb03e36d2f3440688)`(float xRobot,float yRobot,float thetaRobot)` 

Calculate the distance between the robot position and line.

#### Parameters
* `xRobot` x position of the robot 

* `yRobot` y position of the robot 

* `thetaRobot` theta position of the robot

#### Returns
The distance between the robot position and this line, negative if point is below the line

#### `public virtual void `[`paint`](#classCelluloZoneLineDistanceSigned_1a88974d01e84248fc08df17c4aee277b9)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Draws this zone onto the painter.

#### Parameters
* `painter` Object to draw onto 

* `color` Color of the paint 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

# class `CelluloZoneLineSegmentDistance` 

```
class CelluloZoneLineSegmentDistance
  : public CelluloZoneLine
```  

[CelluloZone](#classCelluloZone) Specific Class for line segment distance determination.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CelluloZoneLineSegmentDistance`](#classCelluloZoneLineSegmentDistance_1ac945cd4f906e899f5354e00c52ac038f)`()` | [CelluloZoneLineSegmentDistance](#classCelluloZoneLineSegmentDistance)
`public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZoneLineSegmentDistance_1af3416f95ab0711553ee45bd8d868261a)`(float xRobot,float yRobot,float thetaRobot)` | Calculate the distance between the robot position and this line segment.
`public virtual void `[`paint`](#classCelluloZoneLineSegmentDistance_1ae67b9757804684362256d594af8e4268)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Draws this zone onto the painter.

## Members

#### `public  `[`CelluloZoneLineSegmentDistance`](#classCelluloZoneLineSegmentDistance_1ac945cd4f906e899f5354e00c52ac038f)`()` 

[CelluloZoneLineSegmentDistance](#classCelluloZoneLineSegmentDistance)

#### `public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZoneLineSegmentDistance_1af3416f95ab0711553ee45bd8d868261a)`(float xRobot,float yRobot,float thetaRobot)` 

Calculate the distance between the robot position and this line segment.

#### Parameters
* `xRobot` x position of the robot 

* `yRobot` y position of the robot 

* `thetaRobot` theta position of the robot

#### Returns
the distance between the robot position and this line segment

#### `public virtual void `[`paint`](#classCelluloZoneLineSegmentDistance_1ae67b9757804684362256d594af8e4268)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Draws this zone onto the painter.

#### Parameters
* `painter` Object to draw onto 

* `color` Color of the paint 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

# class `CelluloZonePaintedItem` 

```
class CelluloZonePaintedItem
  : public QQuickPaintedItem
```  

A QML compatible QQuickPaintedItem for CelluloZones.

Visually covers the parent (from (0,0) to (parent.width,parent.height)) and draws the zone at the appropriate place

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} QColor `[`color`](#classCelluloZonePaintedItem_1aa99cb5543765c49b504c29d50e125056) | Color of the paint.
`{property} `[`CelluloZone`](#classCelluloZone)` `[`associatedZone`](#classCelluloZonePaintedItem_1a96e43b85c209ec5806d94731259fa9ac) | 
`{property} qreal `[`physicalPlaygroundWidth`](#classCelluloZonePaintedItem_1aeeafdc5387f4da57a80d04fb2318c461) | Physical playground width in mm.
`{property} qreal `[`physicalPlaygroundHeight`](#classCelluloZonePaintedItem_1a8d65d16f12c37bade8929d4d10bf42ba) | Physical playground height in mm.
`public  explicit `[`CelluloZonePaintedItem`](#classCelluloZonePaintedItem_1a7cba25d52ac17bca1ccabe15117d1055)`(QQuickItem * parent)` | Creates a new [CelluloZonePaintedItem](#classCelluloZonePaintedItem).
`public inline QColor `[`getColor`](#classCelluloZonePaintedItem_1a365deef2de6690c0d2e92426d22e2ce5)`()` | Gets the color to paint with.
`public void `[`setColor`](#classCelluloZonePaintedItem_1adf508b60818fd2c26062628e3c452b84)`(QColor newColor)` | Updates the color to paint with.
`public void `[`setAssociatedZone`](#classCelluloZonePaintedItem_1a6aa878da2ae69bcd3a08a1fd2ad0cb76)`(`[`CelluloZone`](#classCelluloZone)` * zone)` | Sets the associated zone.
`public inline `[`CelluloZone`](#classCelluloZone)` * `[`getAssociatedZone`](#classCelluloZonePaintedItem_1a256f6a5ffba98b83535d7817f415663e)`()` | Gets the associated zone.
`public void `[`setPhysicalPlaygroundWidth`](#classCelluloZonePaintedItem_1ab8f649e71c144335c1b7554d464f6856)`(qreal newWidth)` | Changes the physical playground width.
`public inline qreal `[`getPhysicalPlaygroundWidth`](#classCelluloZonePaintedItem_1a75880df9fd8e691efdbf567553f1c44f)`()` | Gets the physical playground width.
`public void `[`setPhysicalPlaygroundHeight`](#classCelluloZonePaintedItem_1a42b23e8353ca07f0e78b349bc022c2b9)`(qreal newHeight)` | Changes the physical playground height.
`public inline qreal `[`getPhysicalPlaygroundHeight`](#classCelluloZonePaintedItem_1a466bd4058fa74ffa5b567cabe1c7ce56)`()` | Gets the physical playground height.
`public void `[`paint`](#classCelluloZonePaintedItem_1a15e91f10d7dea78f026e9b9ae419f4b5)`(QPainter * painter)` | Implementation of pure virtual function in QQuickPaintedItem.
`{signal} public void `[`colorChanged`](#classCelluloZonePaintedItem_1a6684d718fd4c0c147a1a02dcaaeba95c)`()` | Emitted when the paint color changes.
`{signal} public void `[`associatedZoneChanged`](#classCelluloZonePaintedItem_1a1cbdc3a02a4a64212d8b670f865eaf39)`()` | Emitted when the associated zone changes.
`{signal} public void `[`physicalPlaygroundWidthChanged`](#classCelluloZonePaintedItem_1a9ad16334d18f5c2594006e935b0d127a)`()` | Emitted when the physical playground width changes.
`{signal} public void `[`physicalPlaygroundHeightChanged`](#classCelluloZonePaintedItem_1a29a48a62c24680d20be6be0381482047)`()` | Emitted when the physical playground height changes.

## Members

#### `{property} QColor `[`color`](#classCelluloZonePaintedItem_1aa99cb5543765c49b504c29d50e125056) 

Color of the paint.

#### `{property} `[`CelluloZone`](#classCelluloZone)` `[`associatedZone`](#classCelluloZonePaintedItem_1a96e43b85c209ec5806d94731259fa9ac) 

#### `{property} qreal `[`physicalPlaygroundWidth`](#classCelluloZonePaintedItem_1aeeafdc5387f4da57a80d04fb2318c461) 

Physical playground width in mm.

#### `{property} qreal `[`physicalPlaygroundHeight`](#classCelluloZonePaintedItem_1a8d65d16f12c37bade8929d4d10bf42ba) 

Physical playground height in mm.

#### `public  explicit `[`CelluloZonePaintedItem`](#classCelluloZonePaintedItem_1a7cba25d52ac17bca1ccabe15117d1055)`(QQuickItem * parent)` 

Creates a new [CelluloZonePaintedItem](#classCelluloZonePaintedItem).

#### Parameters
* `parent` QML parent

#### `public inline QColor `[`getColor`](#classCelluloZonePaintedItem_1a365deef2de6690c0d2e92426d22e2ce5)`()` 

Gets the color to paint with.

#### Returns
The paint color

#### `public void `[`setColor`](#classCelluloZonePaintedItem_1adf508b60818fd2c26062628e3c452b84)`(QColor newColor)` 

Updates the color to paint with.

#### Parameters
* `newColor` The new paint color

#### `public void `[`setAssociatedZone`](#classCelluloZonePaintedItem_1a6aa878da2ae69bcd3a08a1fd2ad0cb76)`(`[`CelluloZone`](#classCelluloZone)` * zone)` 

Sets the associated zone.

#### Parameters
* `associatedZone` The [CelluloZone](#classCelluloZone) that will take care of painting

#### `public inline `[`CelluloZone`](#classCelluloZone)` * `[`getAssociatedZone`](#classCelluloZonePaintedItem_1a256f6a5ffba98b83535d7817f415663e)`()` 

Gets the associated zone.

#### Returns
The [CelluloZone](#classCelluloZone) that takes care of painting

#### `public void `[`setPhysicalPlaygroundWidth`](#classCelluloZonePaintedItem_1ab8f649e71c144335c1b7554d464f6856)`(qreal newWidth)` 

Changes the physical playground width.

#### Parameters
* `newWidth` New width in millimeters

#### `public inline qreal `[`getPhysicalPlaygroundWidth`](#classCelluloZonePaintedItem_1a75880df9fd8e691efdbf567553f1c44f)`()` 

Gets the physical playground width.

#### Returns
The physical playground width in mm

#### `public void `[`setPhysicalPlaygroundHeight`](#classCelluloZonePaintedItem_1a42b23e8353ca07f0e78b349bc022c2b9)`(qreal newHeight)` 

Changes the physical playground height.

#### Parameters
* `newWidth` New height in millimeters

#### `public inline qreal `[`getPhysicalPlaygroundHeight`](#classCelluloZonePaintedItem_1a466bd4058fa74ffa5b567cabe1c7ce56)`()` 

Gets the physical playground height.

#### Returns
The physical playground height in mm

#### `public void `[`paint`](#classCelluloZonePaintedItem_1a15e91f10d7dea78f026e9b9ae419f4b5)`(QPainter * painter)` 

Implementation of pure virtual function in QQuickPaintedItem.

#### Parameters
* `painter` Object to paint on

#### `{signal} public void `[`colorChanged`](#classCelluloZonePaintedItem_1a6684d718fd4c0c147a1a02dcaaeba95c)`()` 

Emitted when the paint color changes.

#### `{signal} public void `[`associatedZoneChanged`](#classCelluloZonePaintedItem_1a1cbdc3a02a4a64212d8b670f865eaf39)`()` 

Emitted when the associated zone changes.

#### `{signal} public void `[`physicalPlaygroundWidthChanged`](#classCelluloZonePaintedItem_1a9ad16334d18f5c2594006e935b0d127a)`()` 

Emitted when the physical playground width changes.

#### `{signal} public void `[`physicalPlaygroundHeightChanged`](#classCelluloZonePaintedItem_1a29a48a62c24680d20be6be0381482047)`()` 

Emitted when the physical playground height changes.

# class `CelluloZonePoint` 

```
class CelluloZonePoint
  : public CelluloZone
```  

[CelluloZone](#classCelluloZone) Base Class for point zones.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} float `[`x`](#classCelluloZonePoint_1ac79737f1c2d4e88536654a820fd491c2) | X position of the point.
`{property} float `[`y`](#classCelluloZonePoint_1abf4d12be1b909ab1b7c5f44744ebf7c6) | Y position of the point.
`public  `[`CelluloZonePoint`](#classCelluloZonePoint_1a9e6500dc2222acef6cbf88e0500bcda0)`()` | Creates a new Cellulo point zone.
`public inline float `[`getX`](#classCelluloZonePoint_1a505263df25be7e7c1f07b9138c531eaf)`()` | Gets the x position of the point.
`public void `[`setX`](#classCelluloZonePoint_1a46bdc2471d4e38548024e1728ee78087)`(float newX)` | Updates the x position of the point.
`public inline float `[`getY`](#classCelluloZonePoint_1a49b0416bd5b17fd284c1270803220caa)`()` | Gets the y position of the point.
`public void `[`setY`](#classCelluloZonePoint_1a83723ebc1cfcc78e29ca7689d060df5a)`(float newY)` | Updates the y position of the point.
`public virtual void `[`write`](#classCelluloZonePoint_1aff238e470ff6fd25f9adefa4e1910049)`(QJsonObject & json)` | Write the zone infos to the given json Object.
`public virtual void `[`read`](#classCelluloZonePoint_1aad64d6a886816f8d53e354c0ab9599ed)`(const QJsonObject & json)` | Read the zone infos from the given json Object.
`public virtual void `[`paint`](#classCelluloZonePoint_1af02d2d735c87f507da9f2aadfef37d4d)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Draws this zone onto the painter.
`public virtual Q_INVOKABLE bool `[`isMouseInside`](#classCelluloZonePoint_1adbdbbbbe4ff43965f58125571d5cfb1e)`(QVector2D mousePosition,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Get if the mouse position is inside the zone or not.
`{signal} public void `[`xChanged`](#classCelluloZonePoint_1a94976892ffb81eb74ce74eeeec41f10c)`()` | Emitted when the X position of the point changes.
`{signal} public void `[`yChanged`](#classCelluloZonePoint_1a514d325346c9c7d2ba14fe1c0c73e003)`()` | Emitted when the Y position of the point changes.

## Members

#### `{property} float `[`x`](#classCelluloZonePoint_1ac79737f1c2d4e88536654a820fd491c2) 

X position of the point.

#### `{property} float `[`y`](#classCelluloZonePoint_1abf4d12be1b909ab1b7c5f44744ebf7c6) 

Y position of the point.

#### `public  `[`CelluloZonePoint`](#classCelluloZonePoint_1a9e6500dc2222acef6cbf88e0500bcda0)`()` 

Creates a new Cellulo point zone.

[CelluloZonePoint](#classCelluloZonePoint)

#### `public inline float `[`getX`](#classCelluloZonePoint_1a505263df25be7e7c1f07b9138c531eaf)`()` 

Gets the x position of the point.

#### Returns
X position of the point

#### `public void `[`setX`](#classCelluloZonePoint_1a46bdc2471d4e38548024e1728ee78087)`(float newX)` 

Updates the x position of the point.

#### Parameters
* `newX` New x position in mm

#### `public inline float `[`getY`](#classCelluloZonePoint_1a49b0416bd5b17fd284c1270803220caa)`()` 

Gets the y position of the point.

#### Returns
Y position of the point

#### `public void `[`setY`](#classCelluloZonePoint_1a83723ebc1cfcc78e29ca7689d060df5a)`(float newY)` 

Updates the y position of the point.

#### Parameters
* `newY` New y position in mm

#### `public virtual void `[`write`](#classCelluloZonePoint_1aff238e470ff6fd25f9adefa4e1910049)`(QJsonObject & json)` 

Write the zone infos to the given json Object.

#### Parameters
* `json` json object to be written

#### `public virtual void `[`read`](#classCelluloZonePoint_1aad64d6a886816f8d53e354c0ab9599ed)`(const QJsonObject & json)` 

Read the zone infos from the given json Object.

#### Parameters
* `json` json object to be read

#### `public virtual void `[`paint`](#classCelluloZonePoint_1af02d2d735c87f507da9f2aadfef37d4d)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Draws this zone onto the painter.

#### Parameters
* `painter` Object to draw onto 

* `color` Color of the paint 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

#### `public virtual Q_INVOKABLE bool `[`isMouseInside`](#classCelluloZonePoint_1adbdbbbbe4ff43965f58125571d5cfb1e)`(QVector2D mousePosition,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Get if the mouse position is inside the zone or not.

#### Parameters
* `mousePosition` (x,y) coordinates of the mouse in pixels 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

#### Returns
Whether the mouse position is inside the zone or not

#### `{signal} public void `[`xChanged`](#classCelluloZonePoint_1a94976892ffb81eb74ce74eeeec41f10c)`()` 

Emitted when the X position of the point changes.

#### `{signal} public void `[`yChanged`](#classCelluloZonePoint_1a514d325346c9c7d2ba14fe1c0c73e003)`()` 

Emitted when the Y position of the point changes.

# class `CelluloZonePointDistance` 

```
class CelluloZonePointDistance
  : public CelluloZonePoint
```  

[CelluloZone](#classCelluloZone) Specific Class for point zones distance determination.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CelluloZonePointDistance`](#classCelluloZonePointDistance_1a5d4d2a448d6b222b9e3c02f518b2b9c3)`()` | [CelluloZonePointDistance](#classCelluloZonePointDistance)
`public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZonePointDistance_1a1d4999de4484d86ceb008b47e475fdcb)`(float xRobot,float yRobot,float thetaRobot)` | Calculate the distance between the robot pose and this point zone.
`public virtual void `[`paint`](#classCelluloZonePointDistance_1a7bb1218753afa6e9f204c08d1a3b2e1c)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Draws this zone onto the painter.

## Members

#### `public  `[`CelluloZonePointDistance`](#classCelluloZonePointDistance_1a5d4d2a448d6b222b9e3c02f518b2b9c3)`()` 

[CelluloZonePointDistance](#classCelluloZonePointDistance)

#### `public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZonePointDistance_1a1d4999de4484d86ceb008b47e475fdcb)`(float xRobot,float yRobot,float thetaRobot)` 

Calculate the distance between the robot pose and this point zone.

#### Parameters
* `xRobot` x position of the robot 

* `yRobot` y position of the robot 

* `thetaRobot` theta position of the robot

#### Returns
the distance between the robot pose and this point zone

#### `public virtual void `[`paint`](#classCelluloZonePointDistance_1a7bb1218753afa6e9f204c08d1a3b2e1c)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Draws this zone onto the painter.

#### Parameters
* `painter` Object to draw onto 

* `color` Color of the paint 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

# class `CelluloZonePolyBezier` 

```
class CelluloZonePolyBezier
  : public CelluloZone
```  

[CelluloZone](#classCelluloZone) Base class for composite cubic Bézier curve.

The curve is composed of continuous cubic Bézier curve segments, as seen in [https://en.wikipedia.org/wiki/Composite_B%C3%A9zier_curve](https://en.wikipedia.org/wiki/Composite_B%C3%A9zier_curve) The curve is compliant with the SVG standard of continuous cubic Bézier segments.

It is composed of 3n+1 control points where the points at indices [3k, 3k+1, 3k+2, 3k+3] correspond to a Bézier curve.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} QVariantList `[`controlPoints`](#classCelluloZonePolyBezier_1a531370613ef66861cebd20d70b3a8414) | 
`public  `[`CelluloZonePolyBezier`](#classCelluloZonePolyBezier_1a634e95d44d6dddeac9ea31532a1f911e)`()` | Creates a new Cellulo composite Bézier curve.
`public QVariantList `[`getControlPoints`](#classCelluloZonePolyBezier_1abf829086650405cb957cc260247ad055)`()` | Gets the curve's control points.
`public void `[`setControlPoints`](#classCelluloZonePolyBezier_1a1f5b22ab257439a91819c7e1d2ca0da6)`(const QVariantList & newControlPoints)` | Sets the curve's control points.
`public virtual void `[`paint`](#classCelluloZonePolyBezier_1a658b83b4f22d1c577c41ff765a98044b)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Draws this zone onto the painter.
`public virtual void `[`write`](#classCelluloZonePolyBezier_1a0a818dde7e05f24e34680111ec156859)`(QJsonObject & json)` | Write the zone infos to the given json Object.
`public virtual void `[`read`](#classCelluloZonePolyBezier_1a3f9bb123e74fab30ea54c697f5807385)`(const QJsonObject & json)` | Read the zone infos from the given json Object.
`public virtual Q_INVOKABLE bool `[`isMouseInside`](#classCelluloZonePolyBezier_1a6be9dedcbfa3e244d5f467bd293330a6)`(QVector2D mousePosition,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Get if the mouse position is inside the zone or not.
`protected QList< `[`CubicBezier`](#classCubicBezier)` > `[`segments`](#classCelluloZonePolyBezier_1a2d7f921cc80779f05f156dc31238291e) | Consecutive Bézier curve segments.
`protected qreal `[`minX`](#classCelluloZonePolyBezier_1ab9c1d15f2e406f1998359f669ed1179a) | Minimal x bound for the curve.
`protected qreal `[`maxX`](#classCelluloZonePolyBezier_1af7440532ea2b2b3315fc8b410561df04) | Maximum x bound for the curve.
`protected qreal `[`minY`](#classCelluloZonePolyBezier_1a46065875570acaed9eed991cf9c71f5b) | Minimum y bound for the curve.
`protected qreal `[`maxY`](#classCelluloZonePolyBezier_1a67c6845a017c818a070181defd458af0) | Maximum y bound for the curve.
`protected int `[`getSegmentIndex`](#classCelluloZonePolyBezier_1a5da77d05f6f892270f72260b2cb0d563)`(qreal & t)` | Gets the segment index from the given parameter t, pulls t to [0,1].
`protected qreal `[`getClosest`](#classCelluloZonePolyBezier_1a24c2afc9dddef5f4cfa87a21c242a458)`(const QVector2D & m,QVector2D & closestPoint,qreal & closestDist)` | Gets the closest point on the curve to the given point.
`protected void `[`calculateBoundingBox`](#classCelluloZonePolyBezier_1a8dfea288db10f845b9fa3ba0e731f219)`()` | Updates the bounding rectangle from the new list of vertices.
`protected bool `[`inBoundingBox`](#classCelluloZonePolyBezier_1a4a5bc6acf63c1370c593395071e29bb4)`(const QVector2D & m)` | Calculates whether the given point is in the bounding box of this curve.
`protected bool `[`isPointInside`](#classCelluloZonePolyBezier_1ac62b651ee4abf1e35105417e6849a279)`(float pointX,float pointY)` | Get if the point is inside the zone or not.
`{signal} public void `[`controlPointsChanged`](#classCelluloZonePolyBezier_1a8c773f1f8fd5133f5ff39dc7332ffd9f)`()` | Emitted when the control points change.
`{slot} public void `[`sendPathToRobot`](#classCelluloZonePolyBezier_1ab959206fd9258eec7b53726abbd7c892)`(`[`CelluloBluetooth`](#classCelluloBluetooth)` * robot) const` | Sends this path to the given robot in order to be followed.
`{slot} public QVector2D `[`getPoint`](#classCelluloZonePolyBezier_1a15339ea0f6bd20cb81df5680fdd1ac9c)`(qreal t)` | Gets the point on the curve corresponding to the given parameter.
`{slot} public QVector2D `[`getTangent`](#classCelluloZonePolyBezier_1a034e00a0746bc42c1062114e9248b417)`(qreal t)` | Gets the tangent direction of point on the curve corresponding to the given parameter.
`{slot} public QVector2D `[`getNormal`](#classCelluloZonePolyBezier_1abb696b58eae88a5014602fbd3d75998f)`(qreal t)` | Gets the normal direction of point on the curve corresponding to the given parameter.

## Members

#### `{property} QVariantList `[`controlPoints`](#classCelluloZonePolyBezier_1a531370613ef66861cebd20d70b3a8414) 

#### `public  `[`CelluloZonePolyBezier`](#classCelluloZonePolyBezier_1a634e95d44d6dddeac9ea31532a1f911e)`()` 

Creates a new Cellulo composite Bézier curve.

#### `public QVariantList `[`getControlPoints`](#classCelluloZonePolyBezier_1abf829086650405cb957cc260247ad055)`()` 

Gets the curve's control points.

#### Returns
List of curve's control points, contains 3n+1 points where points at indices [3k, 3k+1, 3k+2, 3k+3] correspond to a Bézier curve

#### `public void `[`setControlPoints`](#classCelluloZonePolyBezier_1a1f5b22ab257439a91819c7e1d2ca0da6)`(const QVariantList & newControlPoints)` 

Sets the curve's control points.

#### Parameters
* `newVertices` List of curve's control points, must contain 3n+1 points where points at indices [3k, 3k+1, 3k+2, 3k+3] correspond to a Bézier curve

#### `public virtual void `[`paint`](#classCelluloZonePolyBezier_1a658b83b4f22d1c577c41ff765a98044b)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Draws this zone onto the painter.

#### Parameters
* `painter` Object to draw onto 

* `color` Color of the paint 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

#### `public virtual void `[`write`](#classCelluloZonePolyBezier_1a0a818dde7e05f24e34680111ec156859)`(QJsonObject & json)` 

Write the zone infos to the given json Object.

#### Parameters
* `QJsonObject` json object to be written

#### `public virtual void `[`read`](#classCelluloZonePolyBezier_1a3f9bb123e74fab30ea54c697f5807385)`(const QJsonObject & json)` 

Read the zone infos from the given json Object.

#### Parameters
* `json` json object to be read

#### `public virtual Q_INVOKABLE bool `[`isMouseInside`](#classCelluloZonePolyBezier_1a6be9dedcbfa3e244d5f467bd293330a6)`(QVector2D mousePosition,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Get if the mouse position is inside the zone or not.

#### Parameters
* `mousePosition` (x,y) coordinates of the mouse in pixels 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

#### Returns
Whether the mouse position is inside the zone or not

#### `protected QList< `[`CubicBezier`](#classCubicBezier)` > `[`segments`](#classCelluloZonePolyBezier_1a2d7f921cc80779f05f156dc31238291e) 

Consecutive Bézier curve segments.

#### `protected qreal `[`minX`](#classCelluloZonePolyBezier_1ab9c1d15f2e406f1998359f669ed1179a) 

Minimal x bound for the curve.

#### `protected qreal `[`maxX`](#classCelluloZonePolyBezier_1af7440532ea2b2b3315fc8b410561df04) 

Maximum x bound for the curve.

#### `protected qreal `[`minY`](#classCelluloZonePolyBezier_1a46065875570acaed9eed991cf9c71f5b) 

Minimum y bound for the curve.

#### `protected qreal `[`maxY`](#classCelluloZonePolyBezier_1a67c6845a017c818a070181defd458af0) 

Maximum y bound for the curve.

#### `protected int `[`getSegmentIndex`](#classCelluloZonePolyBezier_1a5da77d05f6f892270f72260b2cb0d563)`(qreal & t)` 

Gets the segment index from the given parameter t, pulls t to [0,1].

#### Parameters
* `t` [in/out] Parameter t in [0,numSegments], changes to segment parameter that is in [0,1] 

#### Returns
Segment index

#### `protected qreal `[`getClosest`](#classCelluloZonePolyBezier_1a24c2afc9dddef5f4cfa87a21c242a458)`(const QVector2D & m,QVector2D & closestPoint,qreal & closestDist)` 

Gets the closest point on the curve to the given point.

#### Parameters
* `m` Given point 

* `closestPoint` [out] Returns the closest point 

* `closestDist` [out] Returns the closest distance 

#### Returns
Returns the parameter t corresponding to the closest point

#### `protected void `[`calculateBoundingBox`](#classCelluloZonePolyBezier_1a8dfea288db10f845b9fa3ba0e731f219)`()` 

Updates the bounding rectangle from the new list of vertices.

#### `protected bool `[`inBoundingBox`](#classCelluloZonePolyBezier_1a4a5bc6acf63c1370c593395071e29bb4)`(const QVector2D & m)` 

Calculates whether the given point is in the bounding box of this curve.

#### Parameters
* `m` The point to check 

#### Returns
Whether this point is in the bounding box

#### `protected bool `[`isPointInside`](#classCelluloZonePolyBezier_1ac62b651ee4abf1e35105417e6849a279)`(float pointX,float pointY)` 

Get if the point is inside the zone or not.

#### Parameters
* `pointX` x coordinate of the point in mm 

* `pointY` y coordinate of the point in mm

#### Returns
Whether the point is inside the zone or not

#### `{signal} public void `[`controlPointsChanged`](#classCelluloZonePolyBezier_1a8c773f1f8fd5133f5ff39dc7332ffd9f)`()` 

Emitted when the control points change.

#### `{slot} public void `[`sendPathToRobot`](#classCelluloZonePolyBezier_1ab959206fd9258eec7b53726abbd7c892)`(`[`CelluloBluetooth`](#classCelluloBluetooth)` * robot) const` 

Sends this path to the given robot in order to be followed.

#### Parameters
* `robot` The robot to send the path to

#### `{slot} public QVector2D `[`getPoint`](#classCelluloZonePolyBezier_1a15339ea0f6bd20cb81df5680fdd1ac9c)`(qreal t)` 

Gets the point on the curve corresponding to the given parameter.

#### Parameters
* `t` Given parameter t in [0,numSegments] 

#### Returns
Point on curve corresponding to t

#### `{slot} public QVector2D `[`getTangent`](#classCelluloZonePolyBezier_1a034e00a0746bc42c1062114e9248b417)`(qreal t)` 

Gets the tangent direction of point on the curve corresponding to the given parameter.

#### Parameters
* `m` Given parameter t in [0,numSegments] 

#### Returns
Tangent direction of the point on curve corresponding to t

#### `{slot} public QVector2D `[`getNormal`](#classCelluloZonePolyBezier_1abb696b58eae88a5014602fbd3d75998f)`(qreal t)` 

Gets the normal direction of point on the curve corresponding to the given parameter.

#### Parameters
* `m` Given parameter t in [0,numSegments] 

#### Returns
Normal direction of the point on curve corresponding to t

# class `CelluloZonePolyBezierBorder` 

```
class CelluloZonePolyBezierBorder
  : public CelluloZonePolyBezier
```  

Calculates whether the client is on the border of a composite Bézier curve.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} qreal `[`borderThickness`](#classCelluloZonePolyBezierBorder_1a6ec5bab6ac9fa3bb38232abd64f41381) | The border thickness in mm.
`public  `[`CelluloZonePolyBezierBorder`](#classCelluloZonePolyBezierBorder_1a497cef4d07d54d5b54bb1ab1c5de9ef3)`()` | [CelluloZonePolyBezierBorder](#classCelluloZonePolyBezierBorder)
`public inline qreal `[`getBorderThickness`](#classCelluloZonePolyBezierBorder_1ae37386a1a56929372ee85d0894322a91)`()` | Gets the border thickness.
`public void `[`setBorderThickness`](#classCelluloZonePolyBezierBorder_1a190ee6019b3e4b6131ad28f3f6e60b53)`(qreal newThickness)` | Sets the new border thickness.
`public virtual void `[`write`](#classCelluloZonePolyBezierBorder_1a30e4a77f0c692389553d6d2ac2be613c)`(QJsonObject & json)` | Write the zone infos to the given json Object.
`public virtual void `[`read`](#classCelluloZonePolyBezierBorder_1aa115e6322ec2485e1c489a3ab302f5e8)`(const QJsonObject & json)` | Read the zone infos from the given json Object.
`public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZonePolyBezierBorder_1a577e4b2ed5df90c64ed44c9f6ef9e06b)`(float xRobot,float yRobot,float thetaRobot)` | Calculate whether the robot is within the border.
`public virtual void `[`paint`](#classCelluloZonePolyBezierBorder_1a3ef2c22aa2a0b661c054bfa7e21f13da)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Draws this zone onto the painter.
`{signal} public void `[`borderThicknessChanged`](#classCelluloZonePolyBezierBorder_1aa11687d122eb4c5ac48091e1451392e5)`()` | Emitted when border thickness changes.

## Members

#### `{property} qreal `[`borderThickness`](#classCelluloZonePolyBezierBorder_1a6ec5bab6ac9fa3bb38232abd64f41381) 

The border thickness in mm.

#### `public  `[`CelluloZonePolyBezierBorder`](#classCelluloZonePolyBezierBorder_1a497cef4d07d54d5b54bb1ab1c5de9ef3)`()` 

[CelluloZonePolyBezierBorder](#classCelluloZonePolyBezierBorder)

#### `public inline qreal `[`getBorderThickness`](#classCelluloZonePolyBezierBorder_1ae37386a1a56929372ee85d0894322a91)`()` 

Gets the border thickness.

#### Returns
Border thickness in mm

#### `public void `[`setBorderThickness`](#classCelluloZonePolyBezierBorder_1a190ee6019b3e4b6131ad28f3f6e60b53)`(qreal newThickness)` 

Sets the new border thickness.

#### Parameters
* `newThickness` New thickness in mm

#### `public virtual void `[`write`](#classCelluloZonePolyBezierBorder_1a30e4a77f0c692389553d6d2ac2be613c)`(QJsonObject & json)` 

Write the zone infos to the given json Object.

#### Parameters
* `QJsonObject` json object to be written

#### `public virtual void `[`read`](#classCelluloZonePolyBezierBorder_1aa115e6322ec2485e1c489a3ab302f5e8)`(const QJsonObject & json)` 

Read the zone infos from the given json Object.

#### Parameters
* `json` json object to be read

#### `public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZonePolyBezierBorder_1a577e4b2ed5df90c64ed44c9f6ef9e06b)`(float xRobot,float yRobot,float thetaRobot)` 

Calculate whether the robot is within the border.

#### Parameters
* `xRobot` x position of the robot 

* `yRobot` y position of the robot 

* `thetaRobot` theta position of the robot

#### Returns
Whether the robot is within the border

#### `public virtual void `[`paint`](#classCelluloZonePolyBezierBorder_1a3ef2c22aa2a0b661c054bfa7e21f13da)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Draws this zone onto the painter.

#### Parameters
* `painter` Object to draw onto 

* `color` Color of the paint 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

#### `{signal} public void `[`borderThicknessChanged`](#classCelluloZonePolyBezierBorder_1aa11687d122eb4c5ac48091e1451392e5)`()` 

Emitted when border thickness changes.

# class `CelluloZonePolyBezierClosestT` 

```
class CelluloZonePolyBezierClosestT
  : public CelluloZonePolyBezier
```  

Calculates the parameter t of the closest point on a composite Bézier curve.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CelluloZonePolyBezierClosestT`](#classCelluloZonePolyBezierClosestT_1a5846ab702a2dde6cba18a1dd6ab5e9f1)`()` | [CelluloZonePolyBezierClosestT](#classCelluloZonePolyBezierClosestT)
`public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZonePolyBezierClosestT_1ae5f6338d27782d56cdd141af8411fede)`(float xRobot,float yRobot,float thetaRobot)` | Calculate the parameter t of the closest point on the composite curve to the robot.
`public virtual void `[`paint`](#classCelluloZonePolyBezierClosestT_1af26ee2fbca91650cb6212569acedd435)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Draws this zone onto the painter.

## Members

#### `public  `[`CelluloZonePolyBezierClosestT`](#classCelluloZonePolyBezierClosestT_1a5846ab702a2dde6cba18a1dd6ab5e9f1)`()` 

[CelluloZonePolyBezierClosestT](#classCelluloZonePolyBezierClosestT)

#### `public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZonePolyBezierClosestT_1ae5f6338d27782d56cdd141af8411fede)`(float xRobot,float yRobot,float thetaRobot)` 

Calculate the parameter t of the closest point on the composite curve to the robot.

#### Parameters
* `xRobot` x position of the robot 

* `yRobot` y position of the robot 

* `thetaRobot` theta position of the robot

#### Returns
Parameter t in [0,numSegments]

#### `public virtual void `[`paint`](#classCelluloZonePolyBezierClosestT_1af26ee2fbca91650cb6212569acedd435)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Draws this zone onto the painter.

#### Parameters
* `painter` Object to draw onto 

* `color` Color of the paint 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

# class `CelluloZonePolyBezierDistance` 

```
class CelluloZonePolyBezierDistance
  : public CelluloZonePolyBezierClosestT
```  

Calculates the distance to a composite Bézier curve.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CelluloZonePolyBezierDistance`](#classCelluloZonePolyBezierDistance_1af262014ca57d0da077a374cc7b172d01)`()` | [CelluloZonePolyBezierDistance](#classCelluloZonePolyBezierDistance)
`public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZonePolyBezierDistance_1a1d42d0b7b5700cebdd54de6a98312ccb)`(float xRobot,float yRobot,float thetaRobot)` | Calculate the closest distance of the composite curve to the robot.
`public virtual void `[`paint`](#classCelluloZonePolyBezierDistance_1ad9c7e9e865cbe148c4a2ccd2dafe2d89)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Draws this zone onto the painter.

## Members

#### `public  `[`CelluloZonePolyBezierDistance`](#classCelluloZonePolyBezierDistance_1af262014ca57d0da077a374cc7b172d01)`()` 

[CelluloZonePolyBezierDistance](#classCelluloZonePolyBezierDistance)

#### `public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZonePolyBezierDistance_1a1d42d0b7b5700cebdd54de6a98312ccb)`(float xRobot,float yRobot,float thetaRobot)` 

Calculate the closest distance of the composite curve to the robot.

#### Parameters
* `xRobot` x position of the robot 

* `yRobot` y position of the robot 

* `thetaRobot` theta position of the robot

#### Returns
Closest distance to any curve among the segments

#### `public virtual void `[`paint`](#classCelluloZonePolyBezierDistance_1ad9c7e9e865cbe148c4a2ccd2dafe2d89)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Draws this zone onto the painter.

#### Parameters
* `painter` Object to draw onto 

* `color` Color of the paint 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

# class `CelluloZonePolyBezierInner` 

```
class CelluloZonePolyBezierInner
  : public CelluloZonePolyBezier
```  

Calculates whether the client is within the composite Bézier curve.

The first and last points of the curve are assumed to be connected with a line segment in order to ensure the curve is closed.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CelluloZonePolyBezierInner`](#classCelluloZonePolyBezierInner_1a836f884d1930befc54bbee22061bff07)`()` | [CelluloZonePolyBezierInner](#classCelluloZonePolyBezierInner)
`public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZonePolyBezierInner_1ac755abd2f1c637f0914aa93a8434c6a7)`(float xRobot,float yRobot,float thetaRobot)` | Calculate whether the robot lies inside this composite Bézier curve.
`public virtual void `[`paint`](#classCelluloZonePolyBezierInner_1a1d0671bbf32876b99b7cf8ec4447b60b)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Draws this zone onto the painter.

## Members

#### `public  `[`CelluloZonePolyBezierInner`](#classCelluloZonePolyBezierInner_1a836f884d1930befc54bbee22061bff07)`()` 

[CelluloZonePolyBezierInner](#classCelluloZonePolyBezierInner)

#### `public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZonePolyBezierInner_1ac755abd2f1c637f0914aa93a8434c6a7)`(float xRobot,float yRobot,float thetaRobot)` 

Calculate whether the robot lies inside this composite Bézier curve.

#### Parameters
* `xRobot` x position of the robot 

* `yRobot` y position of the robot 

* `thetaRobot` theta position of the robot

#### Returns
1 if the robot is inside this zone 0 otherwise

#### `public virtual void `[`paint`](#classCelluloZonePolyBezierInner_1a1d0671bbf32876b99b7cf8ec4447b60b)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Draws this zone onto the painter.

#### Parameters
* `painter` Object to draw onto 

* `color` Color of the paint 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

# class `CelluloZonePolyBezierXT` 

```
class CelluloZonePolyBezierXT
  : public CelluloZonePolyBezierClosestT
```  

Calculates the parameter t of the point on the composite Bézier curve with the same x coordinate as the client.

Assumes that the curve is 1-to-1 along the x axis, i.e it is of the form y = f(t).

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CelluloZonePolyBezierXT`](#classCelluloZonePolyBezierXT_1af155b06a6321046c3dc4d0dfc9102489)`()` | [CelluloZonePolyBezierXT](#classCelluloZonePolyBezierXT)
`public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZonePolyBezierXT_1a379c540fe94ae3c36f0b0adb090457e6)`(float xRobot,float yRobot,float thetaRobot)` | Calculates the parameter t of the point on the composite curve with the same x coordinate as the client.
`public virtual void `[`paint`](#classCelluloZonePolyBezierXT_1a42f1dbd89e5f0a2665c1aea7b61101ab)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Draws this zone onto the painter.

## Members

#### `public  `[`CelluloZonePolyBezierXT`](#classCelluloZonePolyBezierXT_1af155b06a6321046c3dc4d0dfc9102489)`()` 

[CelluloZonePolyBezierXT](#classCelluloZonePolyBezierXT)

#### `public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZonePolyBezierXT_1a379c540fe94ae3c36f0b0adb090457e6)`(float xRobot,float yRobot,float thetaRobot)` 

Calculates the parameter t of the point on the composite curve with the same x coordinate as the client.

Assumes that the curve is 1-to-1 along the x axis, i.e it is of the form y = f(t).

#### Parameters
* `xRobot` x position of the robot 

* `yRobot` UNUSED 

* `thetaRobot` UNUSED

#### Returns
Parameter t in [0,numSegments]

#### `public virtual void `[`paint`](#classCelluloZonePolyBezierXT_1a42f1dbd89e5f0a2665c1aea7b61101ab)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Draws this zone onto the painter.

#### Parameters
* `painter` Object to draw onto 

* `color` Color of the paint 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

# class `CelluloZonePolyBezierYT` 

```
class CelluloZonePolyBezierYT
  : public CelluloZonePolyBezierClosestT
```  

Calculates the parameter t of the point on the composite Bézier curve with the same y coordinate as the client.

Assumes that the curve is 1-to-1 along the y axis, i.e it is of the form x = f(t).

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CelluloZonePolyBezierYT`](#classCelluloZonePolyBezierYT_1a87752657e3492554c7255cee28814fc9)`()` | [CelluloZonePolyBezierYT](#classCelluloZonePolyBezierYT)
`public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZonePolyBezierYT_1ad9fea9f9fc3da35d3422641096be8515)`(float xRobot,float yRobot,float thetaRobot)` | Calculates the parameter t of the point on the composite curve with the same y coordinate as the client.
`public virtual void `[`paint`](#classCelluloZonePolyBezierYT_1ad14b0475cf51f440ebeb95f1b79a2139)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Draws this zone onto the painter.

## Members

#### `public  `[`CelluloZonePolyBezierYT`](#classCelluloZonePolyBezierYT_1a87752657e3492554c7255cee28814fc9)`()` 

[CelluloZonePolyBezierYT](#classCelluloZonePolyBezierYT)

#### `public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZonePolyBezierYT_1ad9fea9f9fc3da35d3422641096be8515)`(float xRobot,float yRobot,float thetaRobot)` 

Calculates the parameter t of the point on the composite curve with the same y coordinate as the client.

Assumes that the curve is 1-to-1 along the y axis, i.e it is of the form x = f(t).

#### Parameters
* `xRobot` UNUSED 

* `yRobot` y position of the robot 

* `thetaRobot` UNUSED

#### Returns
Parameter t in [0,numSegments]

#### `public virtual void `[`paint`](#classCelluloZonePolyBezierYT_1ad14b0475cf51f440ebeb95f1b79a2139)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Draws this zone onto the painter.

#### Parameters
* `painter` Object to draw onto 

* `color` Color of the paint 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

# class `CelluloZonePolygon` 

```
class CelluloZonePolygon
  : public CelluloZone
```  

[CelluloZone](#classCelluloZone) Base Class for polygonal zones.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} QList< QVariant > `[`vertices`](#classCelluloZonePolygon_1ab2e36e066d90ce10fdeb8904ce2bd4d4) | 
`public  `[`CelluloZonePolygon`](#classCelluloZonePolygon_1af9d751ccbf397cbd35f7c1573710be56)`()` | Creates a new Cellulo polygonal zone.
`public inline QList< QVariant > `[`getVerticesAsVariants`](#classCelluloZonePolygon_1aa0fd54a86c0a1873806a4ae63f6cdc5d)`()` | Gets the polygon's vertices in their QVariant representation.
`public inline Q_INVOKABLE void `[`setVerticesAsVariants`](#classCelluloZonePolygon_1ae51d9039bf1d450caea75091531487d0)`(QList< QVariant > newVerticesAsVariants)` | Sets the polygon's vertices in their QVariant representation.
`public inline const QList< QVector2D > & `[`getVertices`](#classCelluloZonePolygon_1a31f569ee3b1051b0f3a2aafb8ace05c6)`()` | Gets the polygon's vertices.
`public virtual void `[`setVertices`](#classCelluloZonePolygon_1ae383cd758016659f1444d3e21c547fd6)`(const QList< QVector2D > & newVertices)` | Sets the polygon's vertices.
`public virtual void `[`paint`](#classCelluloZonePolygon_1a94bc441dcf9bac04da612c54ba06a294)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Draws this zone onto the painter.
`public virtual Q_INVOKABLE bool `[`isMouseInside`](#classCelluloZonePolygon_1ad7c4a9f02b3cd316b0789541804b0a7e)`(QVector2D mousePosition,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Get if the mouse position is inside the zone or not.
`protected QList< QVector2D > `[`vertices`](#classCelluloZonePolygon_1a393ceef0b3ebf24a6bd6ebe11ebec461) | Vertices of the polygon.
`protected float `[`minX`](#classCelluloZonePolygon_1aebb421e7ec2b1ad053f11b7015b18bae) | Minimal x bound for the polygon.
`protected float `[`maxX`](#classCelluloZonePolygon_1a7380df8292d3fd99edffc2af817958a9) | Maximum x bound for the polygon.
`protected float `[`minY`](#classCelluloZonePolygon_1ab9803f4fb7314106ffd2e5b3f06ae924) | Minimum y bound for the polygon.
`protected float `[`maxY`](#classCelluloZonePolygon_1ade2c9d5f72d0ff1a1499ee2fa99ec154) | Maximum y bound for the polygon.
`protected void `[`updateBounds`](#classCelluloZonePolygon_1afdfb8fc26db50a9ab8efbd978bc61b1f)`()` | Updates the bounding rectangle from the new list of vertices.
`protected QList< QVector2D > `[`convertQVariantToQVector2D`](#classCelluloZonePolygon_1ae7ba835102ded7f336d6cedc8aec4537)`(QList< QVariant > newVerticesAsVariants)` | Convert QVariant vertices to QVector2D vertices.
`protected bool `[`isPointInside`](#classCelluloZonePolygon_1a1a9cff58aa8f68f15e8299c72bf77e66)`(float pointX,float pointY)` | Get if the point is inside the zone or not.
`{signal} public void `[`verticesChanged`](#classCelluloZonePolygon_1aeec660b17f7964e97595960ba93fb689)`()` | Emitted when the vertices change.

## Members

#### `{property} QList< QVariant > `[`vertices`](#classCelluloZonePolygon_1ab2e36e066d90ce10fdeb8904ce2bd4d4) 

#### `public  `[`CelluloZonePolygon`](#classCelluloZonePolygon_1af9d751ccbf397cbd35f7c1573710be56)`()` 

Creates a new Cellulo polygonal zone.

[CelluloZonePolygon](#classCelluloZonePolygon)

#### `public inline QList< QVariant > `[`getVerticesAsVariants`](#classCelluloZonePolygon_1aa0fd54a86c0a1873806a4ae63f6cdc5d)`()` 

Gets the polygon's vertices in their QVariant representation.

#### Returns
List of polygon's vertices in their QVariant representation

#### `public inline Q_INVOKABLE void `[`setVerticesAsVariants`](#classCelluloZonePolygon_1ae51d9039bf1d450caea75091531487d0)`(QList< QVariant > newVerticesAsVariants)` 

Sets the polygon's vertices in their QVariant representation.

#### Parameters
* `newVertices` List of new vertices in their QVariant representation

#### `public inline const QList< QVector2D > & `[`getVertices`](#classCelluloZonePolygon_1a31f569ee3b1051b0f3a2aafb8ace05c6)`()` 

Gets the polygon's vertices.

#### Returns
List of polygon's vertices

#### `public virtual void `[`setVertices`](#classCelluloZonePolygon_1ae383cd758016659f1444d3e21c547fd6)`(const QList< QVector2D > & newVertices)` 

Sets the polygon's vertices.

#### Parameters
* `newVertices` List of new vertices

#### `public virtual void `[`paint`](#classCelluloZonePolygon_1a94bc441dcf9bac04da612c54ba06a294)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Draws this zone onto the painter.

#### Parameters
* `painter` Object to draw onto 

* `color` Color of the paint 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

#### `public virtual Q_INVOKABLE bool `[`isMouseInside`](#classCelluloZonePolygon_1ad7c4a9f02b3cd316b0789541804b0a7e)`(QVector2D mousePosition,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Get if the mouse position is inside the zone or not.

#### Parameters
* `mousePosition` (x,y) coordinates of the mouse in pixels 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

#### Returns
Whether the mouse position is inside the zone or not

#### `protected QList< QVector2D > `[`vertices`](#classCelluloZonePolygon_1a393ceef0b3ebf24a6bd6ebe11ebec461) 

Vertices of the polygon.

#### `protected float `[`minX`](#classCelluloZonePolygon_1aebb421e7ec2b1ad053f11b7015b18bae) 

Minimal x bound for the polygon.

#### `protected float `[`maxX`](#classCelluloZonePolygon_1a7380df8292d3fd99edffc2af817958a9) 

Maximum x bound for the polygon.

#### `protected float `[`minY`](#classCelluloZonePolygon_1ab9803f4fb7314106ffd2e5b3f06ae924) 

Minimum y bound for the polygon.

#### `protected float `[`maxY`](#classCelluloZonePolygon_1ade2c9d5f72d0ff1a1499ee2fa99ec154) 

Maximum y bound for the polygon.

#### `protected void `[`updateBounds`](#classCelluloZonePolygon_1afdfb8fc26db50a9ab8efbd978bc61b1f)`()` 

Updates the bounding rectangle from the new list of vertices.

#### `protected QList< QVector2D > `[`convertQVariantToQVector2D`](#classCelluloZonePolygon_1ae7ba835102ded7f336d6cedc8aec4537)`(QList< QVariant > newVerticesAsVariants)` 

Convert QVariant vertices to QVector2D vertices.

#### `protected bool `[`isPointInside`](#classCelluloZonePolygon_1a1a9cff58aa8f68f15e8299c72bf77e66)`(float pointX,float pointY)` 

Get if the point is inside the zone or not.

#### Parameters
* `pointX` x coordinate of the point in mm 

* `pointY` y coordinate of the point in mm

#### Returns
Whether the point is inside the zone or not

#### `{signal} public void `[`verticesChanged`](#classCelluloZonePolygon_1aeec660b17f7964e97595960ba93fb689)`()` 

Emitted when the vertices change.

# class `CelluloZoneRectangle` 

```
class CelluloZoneRectangle
  : public CelluloZone
```  

[CelluloZone](#classCelluloZone) Base Class for rectangular zones.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} float `[`x`](#classCelluloZoneRectangle_1a2ea1144b3f054b50deb9a600b7fd5338) | x position of the upper left corner of the rectangle
`{property} float `[`y`](#classCelluloZoneRectangle_1a9efb991d21747d7a16dd006e12865269) | y position of the upper left corner of the rectangle
`{property} float `[`height`](#classCelluloZoneRectangle_1a0969fdcacfcefc9e7d71b61e7a0ea688) | height of the rectangle
`{property} float `[`width`](#classCelluloZoneRectangle_1a8a4f148f51e23d29544b47c802d180b8) | width of the rectangle
`public  `[`CelluloZoneRectangle`](#classCelluloZoneRectangle_1a33ea5c2a85bc35e4aabc54e7333e80fd)`()` | Creates a new Cellulo rectangular zone.
`public inline float `[`getX`](#classCelluloZoneRectangle_1aab8a9e1e333c8f562df65474a73ef2ed)`()` | Gets the x position of upper left corner of the rectangle.
`public void `[`setX`](#classCelluloZoneRectangle_1a7834fd5e3330ed91c2ae14d35c505175)`(float newX)` | Updates the rectangle's left edge x position.
`public inline float `[`getY`](#classCelluloZoneRectangle_1ab8578464334ec5500400236e638b4d42)`()` | Gets the y position of upper left corner of the rectangle.
`public void `[`setY`](#classCelluloZoneRectangle_1ac8dbbcde024e882a6da45ec3e43bbb23)`(float newY)` | Updates the rectangle's top edge y position.
`public inline float `[`getHeight`](#classCelluloZoneRectangle_1ad1f0904823101fa05b6d799cbd191d00)`()` | Gets the height of the rectangle.
`public void `[`setHeight`](#classCelluloZoneRectangle_1ad3e1b05955315085c3569216fbc80de2)`(float newHeight)` | Updates the rectangle's height.
`public inline float `[`getWidth`](#classCelluloZoneRectangle_1ad580ac4d8ae8f19ec5f7229e5ab77ee0)`()` | Gets the width of the rectangle.
`public void `[`setWidth`](#classCelluloZoneRectangle_1ae860bd8981fba688463d7e63c1007034)`(float newWidth)` | Updates the rectangle's width.
`public virtual void `[`write`](#classCelluloZoneRectangle_1a7e8908725479268446181c354bbe6b8c)`(QJsonObject & json)` | Write the zone infos to the given json Object.
`public virtual void `[`read`](#classCelluloZoneRectangle_1a02da873db519eaf34eda6f0dce629106)`(const QJsonObject & json)` | Read the zone infos from the given json Object.
`public virtual void `[`paint`](#classCelluloZoneRectangle_1a6ca7869f37a18a6c91b9a333f1dd3fd5)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Draws this zone onto the painter.
`public virtual Q_INVOKABLE bool `[`isMouseInside`](#classCelluloZoneRectangle_1a3a038d7f8141b103e676a7512d40b19a)`(QVector2D mousePosition,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Get if the mouse position is inside the zone or not.
`protected bool `[`isPointInside`](#classCelluloZoneRectangle_1a832aa1541428f4e85d04f22fb57a0edf)`(float pointX,float pointY)` | Get if the point is inside the zone or not.
`{signal} public void `[`xChanged`](#classCelluloZoneRectangle_1a2609a059bd1fc5e81942dd9c12886822)`()` | Emitted when the x position of the upper left corner of the rectangular zone's center changes.
`{signal} public void `[`yChanged`](#classCelluloZoneRectangle_1ab6a60bce20ae8951c8ad5cb7eaa6710d)`()` | Emitted when the y postion of the upper left corner of the rectangular zone's center changes.
`{signal} public void `[`heightChanged`](#classCelluloZoneRectangle_1a5e8b78d36d4edefd6d695f08f3886bdf)`()` | Emitted when the height of the rectangular zone changes.
`{signal} public void `[`widthChanged`](#classCelluloZoneRectangle_1a44dec24df99cec2a5171306c26a4a529)`()` | Emitted when the height of the rectangular zone changes.

## Members

#### `{property} float `[`x`](#classCelluloZoneRectangle_1a2ea1144b3f054b50deb9a600b7fd5338) 

x position of the upper left corner of the rectangle

#### `{property} float `[`y`](#classCelluloZoneRectangle_1a9efb991d21747d7a16dd006e12865269) 

y position of the upper left corner of the rectangle

#### `{property} float `[`height`](#classCelluloZoneRectangle_1a0969fdcacfcefc9e7d71b61e7a0ea688) 

height of the rectangle

#### `{property} float `[`width`](#classCelluloZoneRectangle_1a8a4f148f51e23d29544b47c802d180b8) 

width of the rectangle

#### `public  `[`CelluloZoneRectangle`](#classCelluloZoneRectangle_1a33ea5c2a85bc35e4aabc54e7333e80fd)`()` 

Creates a new Cellulo rectangular zone.

[CelluloZoneRectangle](#classCelluloZoneRectangle)

#### `public inline float `[`getX`](#classCelluloZoneRectangle_1aab8a9e1e333c8f562df65474a73ef2ed)`()` 

Gets the x position of upper left corner of the rectangle.

#### Returns
X position of upper left corner of the rectangle

#### `public void `[`setX`](#classCelluloZoneRectangle_1a7834fd5e3330ed91c2ae14d35c505175)`(float newX)` 

Updates the rectangle's left edge x position.

#### Parameters
* `newX` New x position in mm

#### `public inline float `[`getY`](#classCelluloZoneRectangle_1ab8578464334ec5500400236e638b4d42)`()` 

Gets the y position of upper left corner of the rectangle.

#### Returns
Y position of upper left corner of the rectangle

#### `public void `[`setY`](#classCelluloZoneRectangle_1ac8dbbcde024e882a6da45ec3e43bbb23)`(float newY)` 

Updates the rectangle's top edge y position.

#### Parameters
* `newY` New y position in mm

#### `public inline float `[`getHeight`](#classCelluloZoneRectangle_1ad1f0904823101fa05b6d799cbd191d00)`()` 

Gets the height of the rectangle.

#### Returns
Height of the rectangle

#### `public void `[`setHeight`](#classCelluloZoneRectangle_1ad3e1b05955315085c3569216fbc80de2)`(float newHeight)` 

Updates the rectangle's height.

#### Parameters
* `newHeight` New height in mm

#### `public inline float `[`getWidth`](#classCelluloZoneRectangle_1ad580ac4d8ae8f19ec5f7229e5ab77ee0)`()` 

Gets the width of the rectangle.

#### Returns
Width of the rectangle

#### `public void `[`setWidth`](#classCelluloZoneRectangle_1ae860bd8981fba688463d7e63c1007034)`(float newWidth)` 

Updates the rectangle's width.

#### Parameters
* `newHeight` New width in mm

#### `public virtual void `[`write`](#classCelluloZoneRectangle_1a7e8908725479268446181c354bbe6b8c)`(QJsonObject & json)` 

Write the zone infos to the given json Object.

#### Parameters
* `QJsonObject` json object to be written

#### `public virtual void `[`read`](#classCelluloZoneRectangle_1a02da873db519eaf34eda6f0dce629106)`(const QJsonObject & json)` 

Read the zone infos from the given json Object.

#### Parameters
* `json` json object to be read

#### `public virtual void `[`paint`](#classCelluloZoneRectangle_1a6ca7869f37a18a6c91b9a333f1dd3fd5)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Draws this zone onto the painter.

#### Parameters
* `painter` Object to draw onto 

* `color` Color of the paint 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

#### `public virtual Q_INVOKABLE bool `[`isMouseInside`](#classCelluloZoneRectangle_1a3a038d7f8141b103e676a7512d40b19a)`(QVector2D mousePosition,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Get if the mouse position is inside the zone or not.

#### Parameters
* `mousePosition` (x,y) coordinates of the mouse in pixels 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

#### Returns
Whether the mouse position is inside the zone or not

#### `protected bool `[`isPointInside`](#classCelluloZoneRectangle_1a832aa1541428f4e85d04f22fb57a0edf)`(float pointX,float pointY)` 

Get if the point is inside the zone or not.

#### Parameters
* `pointX` x coordinate of the point in mm 

* `pointY` y coordinate of the point in mm

#### Returns
Whether the point is inside the zone or not

#### `{signal} public void `[`xChanged`](#classCelluloZoneRectangle_1a2609a059bd1fc5e81942dd9c12886822)`()` 

Emitted when the x position of the upper left corner of the rectangular zone's center changes.

#### `{signal} public void `[`yChanged`](#classCelluloZoneRectangle_1ab6a60bce20ae8951c8ad5cb7eaa6710d)`()` 

Emitted when the y postion of the upper left corner of the rectangular zone's center changes.

#### `{signal} public void `[`heightChanged`](#classCelluloZoneRectangle_1a5e8b78d36d4edefd6d695f08f3886bdf)`()` 

Emitted when the height of the rectangular zone changes.

#### `{signal} public void `[`widthChanged`](#classCelluloZoneRectangle_1a44dec24df99cec2a5171306c26a4a529)`()` 

Emitted when the height of the rectangular zone changes.

# class `CelluloZoneRectangleBorder` 

```
class CelluloZoneRectangleBorder
  : public CelluloZoneRectangle
```  

[CelluloZone](#classCelluloZone) Specific Class for rectangular zones border determination.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} qreal `[`borderThickness`](#classCelluloZoneRectangleBorder_1a9ef595b329e0ee3b2399c83c5ff64885) | The border thickness in mm.
`public  `[`CelluloZoneRectangleBorder`](#classCelluloZoneRectangleBorder_1a3e189c7e1831a04a81e55439bc6dff51)`()` | [CelluloZoneRectangleBorder](#classCelluloZoneRectangleBorder)
`public inline qreal `[`getBorderThickness`](#classCelluloZoneRectangleBorder_1a01384e24bc1802f27f50627a3409fb2c)`()` | Gets the border thickness.
`public void `[`setBorderThickness`](#classCelluloZoneRectangleBorder_1a1cd54acc1af058fb761089940ef76c46)`(qreal newThickness)` | Sets the new border thickness.
`public virtual void `[`write`](#classCelluloZoneRectangleBorder_1a6007ef186fef3c0ae07d5d9ba7c45045)`(QJsonObject & json)` | Write the zone infos to the given json Object.
`public virtual void `[`read`](#classCelluloZoneRectangleBorder_1ae69333b911235f88cf86472abdb78277)`(const QJsonObject & json)` | Read the zone infos from the given json Object.
`public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZoneRectangleBorder_1a1d1815a8bf590a9c52d9f456aa7015b9)`(float xRobot,float yRobot,float thetaRobot)` | Calculate whether the robot lies on the border of this rectangular zone (given the zone's margin)
`public virtual void `[`paint`](#classCelluloZoneRectangleBorder_1a7708039ffb9d4997d18eefa338cbabf3)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Draws this zone onto the painter.
`{signal} public void `[`borderThicknessChanged`](#classCelluloZoneRectangleBorder_1a6e418ea2641849ecd3c3cfbd681b3bc2)`()` | Emitted when border thickness changes.

## Members

#### `{property} qreal `[`borderThickness`](#classCelluloZoneRectangleBorder_1a9ef595b329e0ee3b2399c83c5ff64885) 

The border thickness in mm.

#### `public  `[`CelluloZoneRectangleBorder`](#classCelluloZoneRectangleBorder_1a3e189c7e1831a04a81e55439bc6dff51)`()` 

[CelluloZoneRectangleBorder](#classCelluloZoneRectangleBorder)

#### `public inline qreal `[`getBorderThickness`](#classCelluloZoneRectangleBorder_1a01384e24bc1802f27f50627a3409fb2c)`()` 

Gets the border thickness.

#### Returns
Border thickness in mm

#### `public void `[`setBorderThickness`](#classCelluloZoneRectangleBorder_1a1cd54acc1af058fb761089940ef76c46)`(qreal newThickness)` 

Sets the new border thickness.

#### Parameters
* `newThickness` New thickness in mm

#### `public virtual void `[`write`](#classCelluloZoneRectangleBorder_1a6007ef186fef3c0ae07d5d9ba7c45045)`(QJsonObject & json)` 

Write the zone infos to the given json Object.

#### Parameters
* `QJsonObject` json object to be written

#### `public virtual void `[`read`](#classCelluloZoneRectangleBorder_1ae69333b911235f88cf86472abdb78277)`(const QJsonObject & json)` 

Read the zone infos from the given json Object.

#### Parameters
* `json` json object to be read

#### `public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZoneRectangleBorder_1a1d1815a8bf590a9c52d9f456aa7015b9)`(float xRobot,float yRobot,float thetaRobot)` 

Calculate whether the robot lies on the border of this rectangular zone (given the zone's margin)

#### Parameters
* `xRobot` x position of the robot 

* `yRobot` y position of the robot 

* `thetaRobot` theta position of the robot

#### Returns
1 if the robot is on the border of this rectangular zone (given the zone's margin) 0 otherwise

#### `public virtual void `[`paint`](#classCelluloZoneRectangleBorder_1a7708039ffb9d4997d18eefa338cbabf3)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Draws this zone onto the painter.

#### Parameters
* `painter` Object to draw onto 

* `color` Color of the paint 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

#### `{signal} public void `[`borderThicknessChanged`](#classCelluloZoneRectangleBorder_1a6e418ea2641849ecd3c3cfbd681b3bc2)`()` 

Emitted when border thickness changes.

# class `CelluloZoneRectangleDistance` 

```
class CelluloZoneRectangleDistance
  : public CelluloZoneRectangle
```  

[CelluloZone](#classCelluloZone) Specific Class for rectangular zones distance determination.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CelluloZoneRectangleDistance`](#classCelluloZoneRectangleDistance_1ab5d55e2f6eb15077e0f2e11d4d337396)`()` | [CelluloZoneRectangleDistance](#classCelluloZoneRectangleDistance)
`public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZoneRectangleDistance_1a3a5c70fa5b0f00270dbe4b148b59acdb)`(float xRobot,float yRobot,float thetaRobot)` | Calculate the distance between the robot pose and the border of this rectangular zone.
`public virtual void `[`paint`](#classCelluloZoneRectangleDistance_1a9dbffd8c89d0d6822c81c93a34e5a55d)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Draws this zone onto the painter.

## Members

#### `public  `[`CelluloZoneRectangleDistance`](#classCelluloZoneRectangleDistance_1ab5d55e2f6eb15077e0f2e11d4d337396)`()` 

[CelluloZoneRectangleDistance](#classCelluloZoneRectangleDistance)

#### `public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZoneRectangleDistance_1a3a5c70fa5b0f00270dbe4b148b59acdb)`(float xRobot,float yRobot,float thetaRobot)` 

Calculate the distance between the robot pose and the border of this rectangular zone.

#### Parameters
* `xRobot` x position of the robot 

* `yRobot` y position of the robot 

* `thetaRobot` theta position of the robot

#### Returns
the distance between the robot pose and the border of this rectangular zone

#### `public virtual void `[`paint`](#classCelluloZoneRectangleDistance_1a9dbffd8c89d0d6822c81c93a34e5a55d)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Draws this zone onto the painter.

#### Parameters
* `painter` Object to draw onto 

* `color` Color of the paint 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

# class `CelluloZoneRectangleInner` 

```
class CelluloZoneRectangleInner
  : public CelluloZoneRectangle
```  

[CelluloZone](#classCelluloZone) Specific Class for rectangular zones inner determination.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CelluloZoneRectangleInner`](#classCelluloZoneRectangleInner_1a51aeae67b7e7e7719c9f8b736bc8cc0e)`()` | [CelluloZoneRectangleInner](#classCelluloZoneRectangleInner)
`public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZoneRectangleInner_1a299a9c9645fdf569b7e7c5c33224ef7a)`(float xRobot,float yRobot,float thetaRobot)` | Calculate whether the robot lies inside this rectangular zone.
`public virtual void `[`paint`](#classCelluloZoneRectangleInner_1af8c925ccf990ee3f2fc5fd0bdfd646b9)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Draws this zone onto the painter.

## Members

#### `public  `[`CelluloZoneRectangleInner`](#classCelluloZoneRectangleInner_1a51aeae67b7e7e7719c9f8b736bc8cc0e)`()` 

[CelluloZoneRectangleInner](#classCelluloZoneRectangleInner)

#### `public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZoneRectangleInner_1a299a9c9645fdf569b7e7c5c33224ef7a)`(float xRobot,float yRobot,float thetaRobot)` 

Calculate whether the robot lies inside this rectangular zone.

#### Parameters
* `xRobot` x position of the robot 

* `yRobot` y position of the robot 

* `thetaRobot` theta position of the robot

#### Returns
1 if the robot is inside this rectangular zone 0 otherwise

#### `public virtual void `[`paint`](#classCelluloZoneRectangleInner_1af8c925ccf990ee3f2fc5fd0bdfd646b9)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Draws this zone onto the painter.

#### Parameters
* `painter` Object to draw onto 

* `color` Color of the paint 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

# class `CelluloZoneRegularPolygon` 

```
class CelluloZoneRegularPolygon
  : public CelluloZonePolygon
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} int `[`numEdges`](#classCelluloZoneRegularPolygon_1aafdcab500930e271d16f38fc7da62746) | 
`{property} float `[`x`](#classCelluloZoneRegularPolygon_1abdd09e6ad368c41081c9aba2b2134b72) | x position of regular polygon defined circle's center
`{property} float `[`y`](#classCelluloZoneRegularPolygon_1a72cbdd13f51858c9aa94f902cf7596c5) | y position of regular polygon defined circle's center
`{property} float `[`r`](#classCelluloZoneRegularPolygon_1a185a8eb5ec322bf9947bfe95ef7347b0) | radius of the regular polygon defined circle
`{property} float `[`rotAngle`](#classCelluloZoneRegularPolygon_1a7f6d41a02e9873b7b9015260fe79e40e) | rotational angle of the regular polygon
`public  `[`CelluloZoneRegularPolygon`](#classCelluloZoneRegularPolygon_1ad0da1105638c1bcabe040cd07a5118e5)`()` | Creates a new Cellulo regular polygonal zone.
`public virtual void `[`setVertices`](#classCelluloZoneRegularPolygon_1afe90ac30f8bc07441c43c0bad0c3bc69)`(const QList< QVector2D > & newVertices)` | Disables modifying vertices directly.
`public inline int `[`getNumEdges`](#classCelluloZoneRegularPolygon_1a99c6f60f88aab43b1ff0dc15f38deb2f)`()` | Gets the number of edges of the regular polygon.
`public void `[`setNumEdges`](#classCelluloZoneRegularPolygon_1ab2383a66067e34500edf989376e438be)`(int newNumEdge)` | Sets the number of edges.
`public inline float `[`getX`](#classCelluloZoneRegularPolygon_1aa66d98ecb4301bb758b836f11511d046)`()` | Gets the x position of regular polygon definer circle's center.
`public void `[`setX`](#classCelluloZoneRegularPolygon_1a2dce5b2c2fdd540c293259f29ac78671)`(float newX)` | Sets the x position of the center of the regular polygon.
`public inline float `[`getY`](#classCelluloZoneRegularPolygon_1a091c4cdae5ca2de8b41aa66302a84cf5)`()` | Gets the y position of regular polygon definer circle's center.
`public void `[`setY`](#classCelluloZoneRegularPolygon_1a8aee5d8f8aabfa4d4f6ec22a4c873591)`(float newY)` | Sets the y position of the center of the regular polygon.
`public inline float `[`getR`](#classCelluloZoneRegularPolygon_1a535ee10ffc0485a521beeda7d53b13e0)`()` | Gets the radius of the regular polygon definer circle.
`public void `[`setR`](#classCelluloZoneRegularPolygon_1a92839f40ae6e7c89c3bcc1fe73ecc36e)`(float newR)` | Sets the radius of the outer circle of the regular polygon.
`public inline float `[`getRotAngle`](#classCelluloZoneRegularPolygon_1a86dbd25c0b02acf1870986f0936e16c6)`()` | Gets the rotational angle of the regular polygon.
`public void `[`setRotAngle`](#classCelluloZoneRegularPolygon_1a292ad574b120a2caff0a8c91d78328f5)`(float newRotAngle)` | Sets the orientation of the regular polygon.
`public virtual void `[`write`](#classCelluloZoneRegularPolygon_1a78ecb2bc983e75b66e84f4aa9be49bdf)`(QJsonObject & json)` | Write the zone infos to the given json Object.
`public virtual void `[`read`](#classCelluloZoneRegularPolygon_1a8442f57b77f524e8dbc07cc2dedeaabd)`(const QJsonObject & json)` | Read the zone infos from the given json Object.
`public virtual void `[`paint`](#classCelluloZoneRegularPolygon_1a76e91e03787e96b4ca3b2394cc79ba94)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Draws this zone onto the painter.
`protected float `[`numEdges`](#classCelluloZoneRegularPolygon_1aadf03dfe5df7dc0afddb02f4a859b51e) | number of edges of the regular polygon
`{signal} public void `[`numEdgesChanged`](#classCelluloZoneRegularPolygon_1a85002c62e721d8184c9281b20918fd9d)`()` | Emitted when the number of edges of the regular polygonal zone changes.
`{signal} public void `[`xChanged`](#classCelluloZoneRegularPolygon_1a5d7acbdb2cb6ca698fd659e8bba2be13)`()` | Emitted when the x position of regular polygon defined circle's center of the regular polygonal zone changes.
`{signal} public void `[`yChanged`](#classCelluloZoneRegularPolygon_1a42faf04dac60aa416e0f048867293209)`()` | Emitted when the y position of regular polygon defined circle's center of the regular polygonal zone changes.
`{signal} public void `[`rChanged`](#classCelluloZoneRegularPolygon_1adf6a4e0c21f4a3ec902cb34735f516f8)`()` | Emitted when the radius of the regular polygon defined circle of the regular polygonal zone changes.
`{signal} public void `[`rotAngleChanged`](#classCelluloZoneRegularPolygon_1a90a1629c7c12725363f3406231903723)`()` | Emitted when the rotational angle of the regular polygonal zone changes.

## Members

#### `{property} int `[`numEdges`](#classCelluloZoneRegularPolygon_1aafdcab500930e271d16f38fc7da62746) 

#### `{property} float `[`x`](#classCelluloZoneRegularPolygon_1abdd09e6ad368c41081c9aba2b2134b72) 

x position of regular polygon defined circle's center

#### `{property} float `[`y`](#classCelluloZoneRegularPolygon_1a72cbdd13f51858c9aa94f902cf7596c5) 

y position of regular polygon defined circle's center

#### `{property} float `[`r`](#classCelluloZoneRegularPolygon_1a185a8eb5ec322bf9947bfe95ef7347b0) 

radius of the regular polygon defined circle

#### `{property} float `[`rotAngle`](#classCelluloZoneRegularPolygon_1a7f6d41a02e9873b7b9015260fe79e40e) 

rotational angle of the regular polygon

#### `public  `[`CelluloZoneRegularPolygon`](#classCelluloZoneRegularPolygon_1ad0da1105638c1bcabe040cd07a5118e5)`()` 

Creates a new Cellulo regular polygonal zone.

[CelluloZoneRegularPolygon](#classCelluloZoneRegularPolygon)

#### `public virtual void `[`setVertices`](#classCelluloZoneRegularPolygon_1afe90ac30f8bc07441c43c0bad0c3bc69)`(const QList< QVector2D > & newVertices)` 

Disables modifying vertices directly.

#### Parameters
* `newVertices` Don't care

#### `public inline int `[`getNumEdges`](#classCelluloZoneRegularPolygon_1a99c6f60f88aab43b1ff0dc15f38deb2f)`()` 

Gets the number of edges of the regular polygon.

#### Returns
The number of edges of the regular polygon

#### `public void `[`setNumEdges`](#classCelluloZoneRegularPolygon_1ab2383a66067e34500edf989376e438be)`(int newNumEdge)` 

Sets the number of edges.

#### Parameters
* `newNumEdge` New number of edges, must be greater than 2

#### `public inline float `[`getX`](#classCelluloZoneRegularPolygon_1aa66d98ecb4301bb758b836f11511d046)`()` 

Gets the x position of regular polygon definer circle's center.

#### Returns
X position of regular polygon definer circle's center

#### `public void `[`setX`](#classCelluloZoneRegularPolygon_1a2dce5b2c2fdd540c293259f29ac78671)`(float newX)` 

Sets the x position of the center of the regular polygon.

#### Parameters
* `newX` Center x position in mm

#### `public inline float `[`getY`](#classCelluloZoneRegularPolygon_1a091c4cdae5ca2de8b41aa66302a84cf5)`()` 

Gets the y position of regular polygon definer circle's center.

#### Returns
Y position of regular polygon definer circle's center

#### `public void `[`setY`](#classCelluloZoneRegularPolygon_1a8aee5d8f8aabfa4d4f6ec22a4c873591)`(float newY)` 

Sets the y position of the center of the regular polygon.

#### Parameters
* `newY` Center y position in mm

#### `public inline float `[`getR`](#classCelluloZoneRegularPolygon_1a535ee10ffc0485a521beeda7d53b13e0)`()` 

Gets the radius of the regular polygon definer circle.

#### Returns
R the radius of the regular polygon definer circle

#### `public void `[`setR`](#classCelluloZoneRegularPolygon_1a92839f40ae6e7c89c3bcc1fe73ecc36e)`(float newR)` 

Sets the radius of the outer circle of the regular polygon.

#### Parameters
* `newR` Radius of the outer circle in mm

#### `public inline float `[`getRotAngle`](#classCelluloZoneRegularPolygon_1a86dbd25c0b02acf1870986f0936e16c6)`()` 

Gets the rotational angle of the regular polygon.

#### Returns
The rotational angle of the regular polygon

#### `public void `[`setRotAngle`](#classCelluloZoneRegularPolygon_1a292ad574b120a2caff0a8c91d78328f5)`(float newRotAngle)` 

Sets the orientation of the regular polygon.

#### Parameters
* `newRotAngle` The

#### `public virtual void `[`write`](#classCelluloZoneRegularPolygon_1a78ecb2bc983e75b66e84f4aa9be49bdf)`(QJsonObject & json)` 

Write the zone infos to the given json Object.

#### Parameters
* `QJsonObject` json object to be written

#### `public virtual void `[`read`](#classCelluloZoneRegularPolygon_1a8442f57b77f524e8dbc07cc2dedeaabd)`(const QJsonObject & json)` 

Read the zone infos from the given json Object.

#### Parameters
* `json` json object to be read

#### `public virtual void `[`paint`](#classCelluloZoneRegularPolygon_1a76e91e03787e96b4ca3b2394cc79ba94)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Draws this zone onto the painter.

#### Parameters
* `painter` Object to draw onto 

* `color` Color of the paint 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

#### `protected float `[`numEdges`](#classCelluloZoneRegularPolygon_1aadf03dfe5df7dc0afddb02f4a859b51e) 

number of edges of the regular polygon

#### `{signal} public void `[`numEdgesChanged`](#classCelluloZoneRegularPolygon_1a85002c62e721d8184c9281b20918fd9d)`()` 

Emitted when the number of edges of the regular polygonal zone changes.

#### `{signal} public void `[`xChanged`](#classCelluloZoneRegularPolygon_1a5d7acbdb2cb6ca698fd659e8bba2be13)`()` 

Emitted when the x position of regular polygon defined circle's center of the regular polygonal zone changes.

#### `{signal} public void `[`yChanged`](#classCelluloZoneRegularPolygon_1a42faf04dac60aa416e0f048867293209)`()` 

Emitted when the y position of regular polygon defined circle's center of the regular polygonal zone changes.

#### `{signal} public void `[`rChanged`](#classCelluloZoneRegularPolygon_1adf6a4e0c21f4a3ec902cb34735f516f8)`()` 

Emitted when the radius of the regular polygon defined circle of the regular polygonal zone changes.

#### `{signal} public void `[`rotAngleChanged`](#classCelluloZoneRegularPolygon_1a90a1629c7c12725363f3406231903723)`()` 

Emitted when the rotational angle of the regular polygonal zone changes.

# class `CelluloZoneRegularPolygonBorder` 

```
class CelluloZoneRegularPolygonBorder
  : public CelluloZoneRegularPolygon
```  

[CelluloZone](#classCelluloZone) Specific Class for regular polygonal zones border determination.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} qreal `[`borderThickness`](#classCelluloZoneRegularPolygonBorder_1ab7ae50700e63f7d32154640bb1d0019a) | The border thickness in mm.
`public  `[`CelluloZoneRegularPolygonBorder`](#classCelluloZoneRegularPolygonBorder_1a7b4cea63a42b536b6ff6461367ea8e53)`()` | [CelluloZoneRegularPolygonBorder](#classCelluloZoneRegularPolygonBorder)
`public inline qreal `[`getBorderThickness`](#classCelluloZoneRegularPolygonBorder_1aa583f8789d9cc2e055e88e5e0419646c)`()` | Gets the border thickness.
`public void `[`setBorderThickness`](#classCelluloZoneRegularPolygonBorder_1a62a2f8b101f6315b1054933d043e768e)`(qreal newThickness)` | Sets the new border thickness.
`public virtual void `[`write`](#classCelluloZoneRegularPolygonBorder_1add98c8052ba48e99bad76c93ed1173eb)`(QJsonObject & json)` | Write the zone infos to the given json Object.
`public virtual void `[`read`](#classCelluloZoneRegularPolygonBorder_1a4418626ae45982ed12b7daecfb14b619)`(const QJsonObject & json)` | Read the zone infos from the given json Object.
`public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZoneRegularPolygonBorder_1a80e038dd3c98fec5f806c11d2c3fa266)`(float xRobot,float yRobot,float thetaRobot)` | Calculate whether the robot lies on the border of this regular polygonal zone (given the zone's margin)
`public virtual void `[`paint`](#classCelluloZoneRegularPolygonBorder_1ae9f4cd4a0095eb669482c9c76b07376b)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Draws this zone onto the painter.
`{signal} public void `[`borderThicknessChanged`](#classCelluloZoneRegularPolygonBorder_1aba2436b3eefbddb98c8f2c192d9a5271)`()` | Emitted when border thickness changes.

## Members

#### `{property} qreal `[`borderThickness`](#classCelluloZoneRegularPolygonBorder_1ab7ae50700e63f7d32154640bb1d0019a) 

The border thickness in mm.

#### `public  `[`CelluloZoneRegularPolygonBorder`](#classCelluloZoneRegularPolygonBorder_1a7b4cea63a42b536b6ff6461367ea8e53)`()` 

[CelluloZoneRegularPolygonBorder](#classCelluloZoneRegularPolygonBorder)

#### `public inline qreal `[`getBorderThickness`](#classCelluloZoneRegularPolygonBorder_1aa583f8789d9cc2e055e88e5e0419646c)`()` 

Gets the border thickness.

#### Returns
Border thickness in mm

#### `public void `[`setBorderThickness`](#classCelluloZoneRegularPolygonBorder_1a62a2f8b101f6315b1054933d043e768e)`(qreal newThickness)` 

Sets the new border thickness.

#### Parameters
* `newThickness` New thickness in mm

#### `public virtual void `[`write`](#classCelluloZoneRegularPolygonBorder_1add98c8052ba48e99bad76c93ed1173eb)`(QJsonObject & json)` 

Write the zone infos to the given json Object.

#### Parameters
* `QJsonObject` json object to be written

#### `public virtual void `[`read`](#classCelluloZoneRegularPolygonBorder_1a4418626ae45982ed12b7daecfb14b619)`(const QJsonObject & json)` 

Read the zone infos from the given json Object.

#### Parameters
* `json` json object to be read

#### `public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZoneRegularPolygonBorder_1a80e038dd3c98fec5f806c11d2c3fa266)`(float xRobot,float yRobot,float thetaRobot)` 

Calculate whether the robot lies on the border of this regular polygonal zone (given the zone's margin)

#### Parameters
* `xRobot` x position of the robot 

* `yRobot` y position of the robot 

* `thetaRobot` theta position of the robot

#### Returns
1 if the robot is on the border of this regular polygonal zone (given the zone's margin) 0 otherwise

#### `public virtual void `[`paint`](#classCelluloZoneRegularPolygonBorder_1ae9f4cd4a0095eb669482c9c76b07376b)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Draws this zone onto the painter.

#### Parameters
* `painter` Object to draw onto 

* `color` Color of the paint 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

#### `{signal} public void `[`borderThicknessChanged`](#classCelluloZoneRegularPolygonBorder_1aba2436b3eefbddb98c8f2c192d9a5271)`()` 

Emitted when border thickness changes.

# class `CelluloZoneRegularPolygonDistance` 

```
class CelluloZoneRegularPolygonDistance
  : public CelluloZoneRegularPolygon
```  

[CelluloZone](#classCelluloZone) Specific Class for regular polygonal zones distance determination.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CelluloZoneRegularPolygonDistance`](#classCelluloZoneRegularPolygonDistance_1aaa142b4751bf99ed1abe505925a4afd0)`()` | [CelluloZoneRegularPolygonDistance](#classCelluloZoneRegularPolygonDistance)
`public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZoneRegularPolygonDistance_1a5389dc2bc67049457d9ddd0840f587c7)`(float xRobot,float yRobot,float thetaRobot)` | Calculate the distance between the robot pose and the border of this regular polygonal zone.
`public virtual void `[`paint`](#classCelluloZoneRegularPolygonDistance_1a5df393ffd546659c323e857fe24c2dee)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Draws this zone onto the painter.

## Members

#### `public  `[`CelluloZoneRegularPolygonDistance`](#classCelluloZoneRegularPolygonDistance_1aaa142b4751bf99ed1abe505925a4afd0)`()` 

[CelluloZoneRegularPolygonDistance](#classCelluloZoneRegularPolygonDistance)

#### `public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZoneRegularPolygonDistance_1a5389dc2bc67049457d9ddd0840f587c7)`(float xRobot,float yRobot,float thetaRobot)` 

Calculate the distance between the robot pose and the border of this regular polygonal zone.

#### Parameters
* `xRobot` x position of the robot 

* `yRobot` y position of the robot 

* `thetaRobot` theta position of the robot

#### Returns
the distance between the robot pose and the border of this regular polygonal zone

#### `public virtual void `[`paint`](#classCelluloZoneRegularPolygonDistance_1a5df393ffd546659c323e857fe24c2dee)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Draws this zone onto the painter.

#### Parameters
* `painter` Object to draw onto 

* `color` Color of the paint 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

# class `CelluloZoneRegularPolygonInner` 

```
class CelluloZoneRegularPolygonInner
  : public CelluloZoneRegularPolygon
```  

[CelluloZone](#classCelluloZone) Specific Class for regular polygonal zones inner determination.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CelluloZoneRegularPolygonInner`](#classCelluloZoneRegularPolygonInner_1a1dfc4ded10e530a977514f09a95a908b)`()` | [CelluloZoneRegularPolygonInner](#classCelluloZoneRegularPolygonInner)
`public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZoneRegularPolygonInner_1a86aad95fb2c2a13c51bcea47aab575a7)`(float xRobot,float yRobot,float thetaRobot)` | Calculate whether the robot lies inside this regular polygonal zone.
`public virtual void `[`paint`](#classCelluloZoneRegularPolygonInner_1afe9c5a06c9d25441e2266521834afddf)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` | Draws this zone onto the painter.

## Members

#### `public  `[`CelluloZoneRegularPolygonInner`](#classCelluloZoneRegularPolygonInner_1a1dfc4ded10e530a977514f09a95a908b)`()` 

[CelluloZoneRegularPolygonInner](#classCelluloZoneRegularPolygonInner)

#### `public virtual Q_INVOKABLE float `[`calculate`](#classCelluloZoneRegularPolygonInner_1a86aad95fb2c2a13c51bcea47aab575a7)`(float xRobot,float yRobot,float thetaRobot)` 

Calculate whether the robot lies inside this regular polygonal zone.

#### Parameters
* `xRobot` x position of the robot 

* `yRobot` y position of the robot 

* `thetaRobot` theta position of the robot

#### Returns
1 if the robot is inside this regular polygonal zone 0 otherwise

#### `public virtual void `[`paint`](#classCelluloZoneRegularPolygonInner_1afe9c5a06c9d25441e2266521834afddf)`(QPainter * painter,QColor color,qreal canvasWidth,qreal canvasHeight,qreal physicalWidth,qreal physicalHeight)` 

Draws this zone onto the painter.

#### Parameters
* `painter` Object to draw onto 

* `color` Color of the paint 

* `canvasWidth` Screen width of the canvas in pixels 

* `canvasHeight` Screen height of the canvas in pixels 

* `physicalWidth` Physical width of the canvas in mm 

* `physicalHeight` Physical height of the canvas in mm

# class `CelluloZoneTypes` 

```
class CelluloZoneTypes
  : public QObject
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CelluloZoneTypes`](#classCelluloZoneTypes_1a572dbf6364700dd331ce1a88ea8d8287)`(QObject * parent)` | 
`public  `[`~CelluloZoneTypes`](#classCelluloZoneTypes_1a7b66397d5cbb2d55be8dd43d28fc597e)`()` | 
`enum `[`ZoneType`](#classCelluloZoneTypes_1a40eaca38e1a2988d19a3037515ff19c4) | List of possible zones.

## Members

#### `public  `[`CelluloZoneTypes`](#classCelluloZoneTypes_1a572dbf6364700dd331ce1a88ea8d8287)`(QObject * parent)` 

#### `public  `[`~CelluloZoneTypes`](#classCelluloZoneTypes_1a7b66397d5cbb2d55be8dd43d28fc597e)`()` 

#### `enum `[`ZoneType`](#classCelluloZoneTypes_1a40eaca38e1a2988d19a3037515ff19c4) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
ANGLEDIFFERENCE            | 
ANGLEINTERVALINNER            | 
ANGLEINTERVALBORDER            | 
ANGLEINTERVALDISTANCE            | 
CIRCLEINNER            | 
CIRCLEBORDER            | 
CIRCLEDISTANCE            | 
RECTANGLEINNER            | 
RECTANGLEBORDER            | 
RECTANGLEDISTANCE            | 
LINESEGMENTDISTANCE            | 
LINEDISTANCESIGNED            | 
LINEBORDER            | 
POINTDISTANCE            | 
RPOLYGONINNER            | 
RPOLYGONBORDER            | 
RPOLYGONDISTANCE            | 
IRPOLYGONINNER            | 
IRPOLYGONBORDER            | 
IRPOLYGONDISTANCE            | 
POLYBEZIERCLOSESTT            | 
POLYBEZIERXT            | 
POLYBEZIERYT            | 
POLYBEZIERDISTANCE            | 
POLYBEZIERBORDER            | 
POLYBEZIERINNER            | 
ZoneTypeNumElements            | 

List of possible zones.

# class `CubicBezier` 

Describes a cubic Bézier curve B(t) = (1 - t)^3*p0 + 3*(1 - t)^2*t*p1 + 3*(1 - t)*t^2*p2 + t^3*p3.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CubicBezier`](#classCubicBezier_1a0dfc2ebbe48d9b5e405f0b45ca3cb495)`(const QVector2D & p0,const QVector2D & p1,const QVector2D & p2,const QVector2D & p3)` | Creates a new cubic Bézier curve with provided control points, calculates the lookup tables.
`public  `[`CubicBezier`](#classCubicBezier_1aec1372399c1d1bf2c758015e9311f5ff)`()` | Creates a new cubic Bézier curve with undefined control points.
`public `[`CubicBezier`](#classCubicBezier)` & `[`dumbClone`](#classCubicBezier_1a67d3d9c71f78fc7e36d54a5c66857cfa)`()` | Creates a clone of this with just the control points with all lazy calculations invalidated.
`public void `[`setControlPoints`](#classCubicBezier_1a20bb0aed63e69c119f1b1aa4ed100a1e)`(const QVector2D & p0,const QVector2D & p1,const QVector2D & p2,const QVector2D & p3)` | Sets all control points.
`public QVector2D `[`getControlPoint`](#classCubicBezier_1afdaeb2297a909b3ed2967c6acac6e107)`(unsigned char i) const` | Gets a control point.
`public void `[`translate`](#classCubicBezier_1aa7a4ed23d2935d3dd7a11ee728af0ac9)`(const QVector2D & t)` | Translates the entire curve, i.e the control points, by t.
`public qreal `[`getClosest`](#classCubicBezier_1a320316c2a1cd105b18763c78f8ecb327)`(const QVector2D & m,QVector2D & closestPoint,qreal & closestDist)` | Gets the closest point on the curve to the given point.
`public QVector2D `[`getPoint`](#classCubicBezier_1a3944bc0e98bf40cede5b56ad748a3ffc)`(qreal t)` | Calculates the point on the curve corresponding to the given parameter.
`public qreal `[`getPointX`](#classCubicBezier_1abd8e30d956adf9b0eb3c326302c9ee1b)`(qreal t)` | Calculates the x coordinate of the point on the curve corresponding to the given parameter.
`public qreal `[`getPointY`](#classCubicBezier_1ae008db23fed54b8cd7e3aff23a781eca)`(qreal t)` | Calculates the y coordinate of the point on the curve corresponding to the given parameter.
`public bool `[`side`](#classCubicBezier_1a99cbdfb53c4d4cb1233cafac283d2934)`(const QVector2D & m)` | Calculates which side of the curve the given point is located.
`public QVector2D `[`getDerivative`](#classCubicBezier_1a9bdcdce09d498aa013fa8c488cc27957)`(qreal t)` | Calculates the direction vector of the tangent line to the curve at the given parameter.
`public void `[`split`](#classCubicBezier_1abc502f675833211c9eca2843f4612c51)`(qreal t,`[`CubicBezier`](#classCubicBezier)` & left,`[`CubicBezier`](#classCubicBezier)` & right)` | Splits the curve into two parts which make up this curve.
`public void `[`getBoundingBox`](#classCubicBezier_1af5d02d55ba20c2eddda730b4e4ab0d6a)`(qreal & minXOut,qreal & maxXOut,qreal & minYOut,qreal & maxYOut)` | Gets the coordinates of the bounding box.
`public bool `[`inBoundingBox`](#classCubicBezier_1a94a6967d46eeb78c353e611260dc2945)`(const QVector2D & m)` | Calculates whether the given point is in the bounding box of this curve.
`public qreal `[`getDistToBoundingBox`](#classCubicBezier_1a4a7def6b27efcdafeb5c86f721e8f5bc)`(const QVector2D & m)` | Calculates the distance to the bounding box of the given point.
`public int `[`getNumCrossings`](#classCubicBezier_1abafdc82c7ccf1c1bcb3ca01124d51f57)`(const QVector2D & m)` | Get how many times a horizontal ray from m to +infinity crosses this curve.

## Members

#### `public  `[`CubicBezier`](#classCubicBezier_1a0dfc2ebbe48d9b5e405f0b45ca3cb495)`(const QVector2D & p0,const QVector2D & p1,const QVector2D & p2,const QVector2D & p3)` 

Creates a new cubic Bézier curve with provided control points, calculates the lookup tables.

#### Parameters
* `p0` First control point 

* `p1` Second control point 

* `p2` Third control point 

* `p3` Fourth control point

#### `public  `[`CubicBezier`](#classCubicBezier_1aec1372399c1d1bf2c758015e9311f5ff)`()` 

Creates a new cubic Bézier curve with undefined control points.

#### `public `[`CubicBezier`](#classCubicBezier)` & `[`dumbClone`](#classCubicBezier_1a67d3d9c71f78fc7e36d54a5c66857cfa)`()` 

Creates a clone of this with just the control points with all lazy calculations invalidated.

#### Returns
New clone of this object, without the lazy calculations done

#### `public void `[`setControlPoints`](#classCubicBezier_1a20bb0aed63e69c119f1b1aa4ed100a1e)`(const QVector2D & p0,const QVector2D & p1,const QVector2D & p2,const QVector2D & p3)` 

Sets all control points.

#### Parameters
* `p0` First control point 

* `p1` Second control point 

* `p2` Third control point 

* `p3` Fourth control point

#### `public QVector2D `[`getControlPoint`](#classCubicBezier_1afdaeb2297a909b3ed2967c6acac6e107)`(unsigned char i) const` 

Gets a control point.

#### Parameters
* `i` Index: 0, 1, 2 or 3

#### `public void `[`translate`](#classCubicBezier_1aa7a4ed23d2935d3dd7a11ee728af0ac9)`(const QVector2D & t)` 

Translates the entire curve, i.e the control points, by t.

#### Parameters
* `t` Translation vector

#### `public qreal `[`getClosest`](#classCubicBezier_1a320316c2a1cd105b18763c78f8ecb327)`(const QVector2D & m,QVector2D & closestPoint,qreal & closestDist)` 

Gets the closest point on the curve to the given point.

#### Parameters
* `m` Given point 

* `closestPoint` [out] Returns the closest point 

* `closestDist` [out] Returns the closest distance 

#### Returns
Returns the parameter t corresponding to the closest point

#### `public QVector2D `[`getPoint`](#classCubicBezier_1a3944bc0e98bf40cede5b56ad748a3ffc)`(qreal t)` 

Calculates the point on the curve corresponding to the given parameter.

#### Parameters
* `t` Curve parameter in [0,1] 

#### Returns
Point corresponding to t

#### `public qreal `[`getPointX`](#classCubicBezier_1abd8e30d956adf9b0eb3c326302c9ee1b)`(qreal t)` 

Calculates the x coordinate of the point on the curve corresponding to the given parameter.

#### Parameters
* `t` Curve parameter in [0,1] 

#### Returns
Point x coordinate corresponding to t

#### `public qreal `[`getPointY`](#classCubicBezier_1ae008db23fed54b8cd7e3aff23a781eca)`(qreal t)` 

Calculates the y coordinate of the point on the curve corresponding to the given parameter.

#### Parameters
* `t` Curve parameter in [0,1] 

#### Returns
Point y coordinate corresponding to t

#### `public bool `[`side`](#classCubicBezier_1a99cbdfb53c4d4cb1233cafac283d2934)`(const QVector2D & m)` 

Calculates which side of the curve the given point is located.

#### Parameters
* `m` Given point 

#### Returns
True if the point is on the right (clockwise) false if the point is on the left (counter-clockwise)

#### `public QVector2D `[`getDerivative`](#classCubicBezier_1a9bdcdce09d498aa013fa8c488cc27957)`(qreal t)` 

Calculates the direction vector of the tangent line to the curve at the given parameter.

#### Parameters
* `t` Parameter 

#### Returns
The direction vector of the tangent line to the curve

#### `public void `[`split`](#classCubicBezier_1abc502f675833211c9eca2843f4612c51)`(qreal t,`[`CubicBezier`](#classCubicBezier)` & left,`[`CubicBezier`](#classCubicBezier)` & right)` 

Splits the curve into two parts which make up this curve.

#### Parameters
* `t` Split point, must be in [0,1] 

* `left` [out] First part 

* `right` [out] Second part

#### `public void `[`getBoundingBox`](#classCubicBezier_1af5d02d55ba20c2eddda730b4e4ab0d6a)`(qreal & minXOut,qreal & maxXOut,qreal & minYOut,qreal & maxYOut)` 

Gets the coordinates of the bounding box.

#### Parameters
* `minXOut` [out] Left coordinate 

* `maxXOut` [out] Right coordinate 

* `minYOut` [out] Top coordinate 

* `maxYOut` [out] Bottom coordinate

#### `public bool `[`inBoundingBox`](#classCubicBezier_1a94a6967d46eeb78c353e611260dc2945)`(const QVector2D & m)` 

Calculates whether the given point is in the bounding box of this curve.

#### Parameters
* `m` The point to check 

#### Returns
Whether this point is in the bounding box

#### `public qreal `[`getDistToBoundingBox`](#classCubicBezier_1a4a7def6b27efcdafeb5c86f721e8f5bc)`(const QVector2D & m)` 

Calculates the distance to the bounding box of the given point.

#### Parameters
* `m` Given point 

#### Returns
Distance to bounding box, 0 if inside the bounding box

#### `public int `[`getNumCrossings`](#classCubicBezier_1abafdc82c7ccf1c1bcb3ca01124d51f57)`(const QVector2D & m)` 

Get how many times a horizontal ray from m to +infinity crosses this curve.

#### Parameters
* `m` The origin of the ray 

#### Returns
Number of times the ray crosses the curve

# class `TranslationTool` 

```
class TranslationTool
  : public QObject
```  

Tool to provide translation for entire app.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} QVariantMap `[`languageList`](#classTranslationTool_1a8d0d5f85e80b526f1269fe5293740817) | Language (QString) to translation file (QString) list.
`{property} QString `[`estr`](#classTranslationTool_1ab9f343269a7d8c6d19b4b57e56ef5568) | 
`public  `[`TranslationTool`](#classTranslationTool_1a4285c7a132dad75af7266675c2dd88a7)`(QObject * parent)` | Creates new translation tool and QTranslator and attaches it to this object.
`public  `[`~TranslationTool`](#classTranslationTool_1a818b1776c3a8ea7c367991279d01175d)`()` | Destroys the translation tool and the QTranslator.
`public void `[`setLanguageList`](#classTranslationTool_1a43de37cb29035c7c29d1323e4e81ca64)`(const QVariantMap & newList)` | Sets the language-translation file map.
`public inline QVariantMap `[`getLanguageList`](#classTranslationTool_1a88937a8d77b3915ec6ccd4700d8eb148)`()` | Gets the language list.
`public inline QString `[`getEmptyString`](#classTranslationTool_1a6cdb45b169fc3857204bb78e37d086fe)`()` | Gets an empty string (hack to dynamically update texts in the UI)
`{signal} public void `[`languageListChanged`](#classTranslationTool_1aa82a9045031e7003f18813536d4ecd96)`()` | Emitted when the language to translation file list changes.
`{signal} public void `[`languageChanged`](#classTranslationTool_1ac748441dfefe41f8a0588a0f87498b30)`()` | Emitted when language has changed.
`{slot} public Q_INVOKABLE void `[`selectLanguage`](#classTranslationTool_1a5c9e2ba2870138b31cb4c20f734b5ec2)`(const QString & language)` | Chooses language.

## Members

#### `{property} QVariantMap `[`languageList`](#classTranslationTool_1a8d0d5f85e80b526f1269fe5293740817) 

Language (QString) to translation file (QString) list.

#### `{property} QString `[`estr`](#classTranslationTool_1ab9f343269a7d8c6d19b4b57e56ef5568) 

#### `public  `[`TranslationTool`](#classTranslationTool_1a4285c7a132dad75af7266675c2dd88a7)`(QObject * parent)` 

Creates new translation tool and QTranslator and attaches it to this object.

#### `public  `[`~TranslationTool`](#classTranslationTool_1a818b1776c3a8ea7c367991279d01175d)`()` 

Destroys the translation tool and the QTranslator.

#### `public void `[`setLanguageList`](#classTranslationTool_1a43de37cb29035c7c29d1323e4e81ca64)`(const QVariantMap & newList)` 

Sets the language-translation file map.

#### Parameters
* `newList` New map from language (QString) to translation file (QString)

#### `public inline QVariantMap `[`getLanguageList`](#classTranslationTool_1a88937a8d77b3915ec6ccd4700d8eb148)`()` 

Gets the language list.

#### Returns
Map from language (QString) to translation file (QString)

#### `public inline QString `[`getEmptyString`](#classTranslationTool_1a6cdb45b169fc3857204bb78e37d086fe)`()` 

Gets an empty string (hack to dynamically update texts in the UI)

#### Returns
""

#### `{signal} public void `[`languageListChanged`](#classTranslationTool_1aa82a9045031e7003f18813536d4ecd96)`()` 

Emitted when the language to translation file list changes.

#### `{signal} public void `[`languageChanged`](#classTranslationTool_1ac748441dfefe41f8a0588a0f87498b30)`()` 

Emitted when language has changed.

#### `{slot} public Q_INVOKABLE void `[`selectLanguage`](#classTranslationTool_1a5c9e2ba2870138b31cb4c20f734b5ec2)`(const QString & language)` 

Chooses language.

#### Parameters
* `language` Language as provided to the translation list or "default" to uninstall translator

# struct `NSVGgradient` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public float `[`xform`](#structNSVGgradient_1aa3f41bbeafbf866b27a7bc00692627fd) | 
`public char `[`spread`](#structNSVGgradient_1ad0ca9ce76308864dbb28c25a9746ec78) | 
`public float `[`fx`](#structNSVGgradient_1acab1f454612d5c1b7842829fe53b3765) | 
`public float `[`fy`](#structNSVGgradient_1a2a2ba27a56ad6eb78c494cdae665247a) | 
`public int `[`nstops`](#structNSVGgradient_1ac9e36f37d0cb087a0e599d966956f212) | 
`public `[`NSVGgradientStop`](#structNSVGgradientStop)` `[`stops`](#structNSVGgradient_1afbfa3c24c71e8b02ee1e56bd9c2101a8) | 

## Members

#### `public float `[`xform`](#structNSVGgradient_1aa3f41bbeafbf866b27a7bc00692627fd) 

#### `public char `[`spread`](#structNSVGgradient_1ad0ca9ce76308864dbb28c25a9746ec78) 

#### `public float `[`fx`](#structNSVGgradient_1acab1f454612d5c1b7842829fe53b3765) 

#### `public float `[`fy`](#structNSVGgradient_1a2a2ba27a56ad6eb78c494cdae665247a) 

#### `public int `[`nstops`](#structNSVGgradient_1ac9e36f37d0cb087a0e599d966956f212) 

#### `public `[`NSVGgradientStop`](#structNSVGgradientStop)` `[`stops`](#structNSVGgradient_1afbfa3c24c71e8b02ee1e56bd9c2101a8) 

# struct `NSVGgradientStop` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public unsigned int `[`color`](#structNSVGgradientStop_1ab27a56ac1f6bbf9e60d8b6247c1a9cc8) | 
`public float `[`offset`](#structNSVGgradientStop_1af6bb631bbcac76b8217595e3ad3ae979) | 

## Members

#### `public unsigned int `[`color`](#structNSVGgradientStop_1ab27a56ac1f6bbf9e60d8b6247c1a9cc8) 

#### `public float `[`offset`](#structNSVGgradientStop_1af6bb631bbcac76b8217595e3ad3ae979) 

# struct `NSVGimage` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public float `[`width`](#structNSVGimage_1a09e04e73bf36578099e2f678494aba64) | 
`public float `[`height`](#structNSVGimage_1a1940399638cc3a962fa9255c10e3daf4) | 
`public `[`NSVGshape`](#structNSVGshape)` * `[`shapes`](#structNSVGimage_1af1c994285b47d78661b631f9ce43d7c8) | 

## Members

#### `public float `[`width`](#structNSVGimage_1a09e04e73bf36578099e2f678494aba64) 

#### `public float `[`height`](#structNSVGimage_1a1940399638cc3a962fa9255c10e3daf4) 

#### `public `[`NSVGshape`](#structNSVGshape)` * `[`shapes`](#structNSVGimage_1af1c994285b47d78661b631f9ce43d7c8) 

# struct `NSVGpaint` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public char `[`type`](#structNSVGpaint_1a02ed7245e1a22db72952427801dbfa9f) | 
`public unsigned int `[`color`](#structNSVGpaint_1a5efac6877bc96d83d6a80f0c081a7286) | 
`public `[`NSVGgradient`](#structNSVGgradient)` * `[`gradient`](#structNSVGpaint_1ac0c406cd769a715148aa1aecd63816bf) | 
`public union NSVGpaint::@0 `[`@1`](#structNSVGpaint_1a6b82cbbf7b61c8d990083a18a0a7afdf) | 

## Members

#### `public char `[`type`](#structNSVGpaint_1a02ed7245e1a22db72952427801dbfa9f) 

#### `public unsigned int `[`color`](#structNSVGpaint_1a5efac6877bc96d83d6a80f0c081a7286) 

#### `public `[`NSVGgradient`](#structNSVGgradient)` * `[`gradient`](#structNSVGpaint_1ac0c406cd769a715148aa1aecd63816bf) 

#### `public union NSVGpaint::@0 `[`@1`](#structNSVGpaint_1a6b82cbbf7b61c8d990083a18a0a7afdf) 

# struct `NSVGpath` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public float * `[`pts`](#structNSVGpath_1a1ee7c57cdb0d1af644617ebe66594677) | 
`public int `[`npts`](#structNSVGpath_1a45f685f06ac09e453f64b558c7b4562d) | 
`public char `[`closed`](#structNSVGpath_1a23aa888bcee2377a97258eb8abe3cf3f) | 
`public float `[`bounds`](#structNSVGpath_1ac39f3994b2a616ad40ad7e02fb669cc1) | 
`public struct `[`NSVGpath`](#structNSVGpath)` * `[`next`](#structNSVGpath_1aa0bfc833298d4d05cfb34a9d814a2c2d) | 

## Members

#### `public float * `[`pts`](#structNSVGpath_1a1ee7c57cdb0d1af644617ebe66594677) 

#### `public int `[`npts`](#structNSVGpath_1a45f685f06ac09e453f64b558c7b4562d) 

#### `public char `[`closed`](#structNSVGpath_1a23aa888bcee2377a97258eb8abe3cf3f) 

#### `public float `[`bounds`](#structNSVGpath_1ac39f3994b2a616ad40ad7e02fb669cc1) 

#### `public struct `[`NSVGpath`](#structNSVGpath)` * `[`next`](#structNSVGpath_1aa0bfc833298d4d05cfb34a9d814a2c2d) 

# struct `NSVGshape` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public char `[`id`](#structNSVGshape_1ae6409e68a9b7a8ae7ba2575d057a3889) | 
`public `[`NSVGpaint`](#structNSVGpaint)` `[`fill`](#structNSVGshape_1a5741cd24ca46bda26921a4b424dda507) | 
`public `[`NSVGpaint`](#structNSVGpaint)` `[`stroke`](#structNSVGshape_1a9ce1be2a34fc2a25998655ae40c36ef9) | 
`public float `[`opacity`](#structNSVGshape_1a567034b8608af2b18febdc81eb4e9a3d) | 
`public float `[`strokeWidth`](#structNSVGshape_1a8b5dc96a27d2e94ae4dca2f9a3e437cd) | 
`public float `[`strokeDashOffset`](#structNSVGshape_1a9bc2082e3bb0e309b775933c7010b9c3) | 
`public float `[`strokeDashArray`](#structNSVGshape_1a89c6bb334c11d2c8cb56f91e6bb6446a) | 
`public char `[`strokeDashCount`](#structNSVGshape_1a54d24fbca317b2cabf3dbeafb4b807ef) | 
`public char `[`strokeLineJoin`](#structNSVGshape_1a83344de4b3cd3aa9a6e30004b6562725) | 
`public char `[`strokeLineCap`](#structNSVGshape_1a4f9950969b100e84e12dc451155cf55a) | 
`public char `[`fillRule`](#structNSVGshape_1ab3098343e41518b060040de3d439196f) | 
`public unsigned char `[`flags`](#structNSVGshape_1a9aa4edfee40c4a3558bb34af06de4943) | 
`public float `[`bounds`](#structNSVGshape_1ac88e2f7af799bc9736956cd637933586) | 
`public `[`NSVGpath`](#structNSVGpath)` * `[`paths`](#structNSVGshape_1a15b1de5a99ff8fe3e5597e95080be87f) | 
`public struct `[`NSVGshape`](#structNSVGshape)` * `[`next`](#structNSVGshape_1a72513ada67dc08af8a484f024b44d485) | 

## Members

#### `public char `[`id`](#structNSVGshape_1ae6409e68a9b7a8ae7ba2575d057a3889) 

#### `public `[`NSVGpaint`](#structNSVGpaint)` `[`fill`](#structNSVGshape_1a5741cd24ca46bda26921a4b424dda507) 

#### `public `[`NSVGpaint`](#structNSVGpaint)` `[`stroke`](#structNSVGshape_1a9ce1be2a34fc2a25998655ae40c36ef9) 

#### `public float `[`opacity`](#structNSVGshape_1a567034b8608af2b18febdc81eb4e9a3d) 

#### `public float `[`strokeWidth`](#structNSVGshape_1a8b5dc96a27d2e94ae4dca2f9a3e437cd) 

#### `public float `[`strokeDashOffset`](#structNSVGshape_1a9bc2082e3bb0e309b775933c7010b9c3) 

#### `public float `[`strokeDashArray`](#structNSVGshape_1a89c6bb334c11d2c8cb56f91e6bb6446a) 

#### `public char `[`strokeDashCount`](#structNSVGshape_1a54d24fbca317b2cabf3dbeafb4b807ef) 

#### `public char `[`strokeLineJoin`](#structNSVGshape_1a83344de4b3cd3aa9a6e30004b6562725) 

#### `public char `[`strokeLineCap`](#structNSVGshape_1a4f9950969b100e84e12dc451155cf55a) 

#### `public char `[`fillRule`](#structNSVGshape_1ab3098343e41518b060040de3d439196f) 

#### `public unsigned char `[`flags`](#structNSVGshape_1a9aa4edfee40c4a3558bb34af06de4943) 

#### `public float `[`bounds`](#structNSVGshape_1ac88e2f7af799bc9736956cd637933586) 

#### `public `[`NSVGpath`](#structNSVGpath)` * `[`paths`](#structNSVGshape_1a15b1de5a99ff8fe3e5597e95080be87f) 

#### `public struct `[`NSVGshape`](#structNSVGshape)` * `[`next`](#structNSVGshape_1a72513ada67dc08af8a484f024b44d485) 

Generated by [Moxygen](https://sourcey.com/moxygen)