# group `robot` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[`Cellulo::CelluloRobot`](doc/doc-robot.md#classCellulo_1_1CelluloRobot) | The main object that represents a [Cellulo](#namespaceCellulo) robot. Inherits from `[CelluloBluetooth](#classCellulo_1_1CelluloBluetooth)` and has all its functionalities (not listed here).

# class `Cellulo::CelluloRobot` 

```
class Cellulo::CelluloRobot
  : public Cellulo::CelluloBluetooth
```  

The main object that represents a [Cellulo](#namespaceCellulo) robot. Inherits from `[CelluloBluetooth](#classCellulo_1_1CelluloBluetooth)` and has all its functionalities (not listed here).

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} QVector3D `[`vxyw`](doc/doc-robot.md#classCellulo_1_1CelluloRobot_1a3ff41aa3eaa381074e5553a126de3ce0) | Robot's estimated velocity in mm/s, mm/s, rad/s, read-only.
`{property} qreal `[`vx`](doc/doc-robot.md#classCellulo_1_1CelluloRobot_1a88f98737ed629ece9b4ded6d69f2090d) | Robot's estimated X velocity in mm/s, read-only.
`{property} qreal `[`vy`](doc/doc-robot.md#classCellulo_1_1CelluloRobot_1ae34e11c148c9a77dacf1fc94af910153) | Robot's estimated Y velocity in mm/s, read-only.
`{property} qreal `[`w`](doc/doc-robot.md#classCellulo_1_1CelluloRobot_1adba256d1ff2391f395d99dacd3111b5f) | Robot's estimated angular velocity in rad/s, read-only.
`{property} bool `[`poseVelControlEnabled`](doc/doc-robot.md#classCellulo_1_1CelluloRobot_1a3b59966b09c1f1b81d090aa1239de383) | Whether the simultaneous pose/velocity is enabled, must be set by the user, default false.
`{property} int `[`poseVelControlPeriod`](doc/doc-robot.md#classCellulo_1_1CelluloRobot_1ae9623a6305f54063ac903d13aefb49f1) | Desired pose/velocity control period in ms, set to 0 for highest possible frequency, default 20.
`{property} QVector3D `[`poseVelControlKGoalVel`](doc/doc-robot.md#classCellulo_1_1CelluloRobot_1afd3187099bb2b39dc99967e0631d4fd2) | Goal velocity coefficients when tracking pose/velocity, default (0.9, 0.9, 0.9), do not change if you don't have a good reason.
`{property} QVector3D `[`poseVelControlKGoalVelErr`](doc/doc-robot.md#classCellulo_1_1CelluloRobot_1ad0bd66a4a9b1744517a744e4470ec492) | Goal velocity error coefficients when tracking pose/velocity, default (0.2, 0.2, 0.2), do not change if you don't have a good reason.
`{property} QVector3D `[`poseVelControlKGoalPoseErr`](doc/doc-robot.md#classCellulo_1_1CelluloRobot_1a0461ff18bdf125f1587ff616368db7c2) | Goal pose error coefficients when tracking pose/velocity, default (2.0, 2.0, 2.3), do not change if you don't have a good reason.
`{property} QList< bool > `[`keysTouched`](doc/doc-robot.md#classCellulo_1_1CelluloRobot_1a93d1d8408926e0be31885b4c57afb768) | Whether the 6 keys are touched.
`{property} QList< bool > `[`keysLongTouched`](doc/doc-robot.md#classCellulo_1_1CelluloRobot_1ab2688290d750b53f9bf958c65dd70ff0) | Whether the 6 keys are long touched.
`{signal} public void `[`nextGoalPoseVelRequested`](#classCellulo_1_1CelluloRobot_1a9d942783a095a74edf14065de5e6e529)`(qreal deltaTime)` | Emitted when the controller needs the next goal pose and velocity.
`{slot} public void `[`setGoalPoseAndVelocity`](#classCellulo_1_1CelluloRobot_1a1594ddde1c1acedfa9b75b86da0c6148)`(qreal x,qreal y,qreal theta,qreal Vx,qreal Vy,qreal w,bool xEnabled,bool yEnabled,bool thetaEnabled)` | Sets the simultaneous pose and velocity goal of the robot, i.e the robot tries to be at the pose and move with the desired velocity while there.

## Members

#### `{property} QVector3D `[`vxyw`](doc/doc-robot.md#classCellulo_1_1CelluloRobot_1a3ff41aa3eaa381074e5553a126de3ce0) 

Robot's estimated velocity in mm/s, mm/s, rad/s, read-only.

Robot velocities: x,y in mm/s, z in rad/s (representing w)

#### `{property} qreal `[`vx`](doc/doc-robot.md#classCellulo_1_1CelluloRobot_1a88f98737ed629ece9b4ded6d69f2090d) 

Robot's estimated X velocity in mm/s, read-only.

#### `{property} qreal `[`vy`](doc/doc-robot.md#classCellulo_1_1CelluloRobot_1ae34e11c148c9a77dacf1fc94af910153) 

Robot's estimated Y velocity in mm/s, read-only.

#### `{property} qreal `[`w`](doc/doc-robot.md#classCellulo_1_1CelluloRobot_1adba256d1ff2391f395d99dacd3111b5f) 

Robot's estimated angular velocity in rad/s, read-only.

#### `{property} bool `[`poseVelControlEnabled`](doc/doc-robot.md#classCellulo_1_1CelluloRobot_1a3b59966b09c1f1b81d090aa1239de383) 

Whether the simultaneous pose/velocity is enabled, must be set by the user, default false.

Whether the simultaneous pose and velocity controller is enabled, must be enabled by the user.

#### `{property} int `[`poseVelControlPeriod`](doc/doc-robot.md#classCellulo_1_1CelluloRobot_1ae9623a6305f54063ac903d13aefb49f1) 

Desired pose/velocity control period in ms, set to 0 for highest possible frequency, default 20.

Desired pose/velocity control period in ms, set to 0 for highest possible frequency.

#### `{property} QVector3D `[`poseVelControlKGoalVel`](doc/doc-robot.md#classCellulo_1_1CelluloRobot_1afd3187099bb2b39dc99967e0631d4fd2) 

Goal velocity coefficients when tracking pose/velocity, default (0.9, 0.9, 0.9), do not change if you don't have a good reason.

Goal velocity coefficients when tracking pose/velocity.

#### `{property} QVector3D `[`poseVelControlKGoalVelErr`](doc/doc-robot.md#classCellulo_1_1CelluloRobot_1ad0bd66a4a9b1744517a744e4470ec492) 

Goal velocity error coefficients when tracking pose/velocity, default (0.2, 0.2, 0.2), do not change if you don't have a good reason.

Goal velocity error coefficients when tracking pose/velocity.

#### `{property} QVector3D `[`poseVelControlKGoalPoseErr`](doc/doc-robot.md#classCellulo_1_1CelluloRobot_1a0461ff18bdf125f1587ff616368db7c2) 

Goal pose error coefficients when tracking pose/velocity, default (2.0, 2.0, 2.3), do not change if you don't have a good reason.

Goal pose error coefficients when tracking pose/velocity.

#### `{property} QList< bool > `[`keysTouched`](doc/doc-robot.md#classCellulo_1_1CelluloRobot_1a93d1d8408926e0be31885b4c57afb768) 

Whether the 6 keys are touched.

Whether keys are touched.

#### `{property} QList< bool > `[`keysLongTouched`](doc/doc-robot.md#classCellulo_1_1CelluloRobot_1ab2688290d750b53f9bf958c65dd70ff0) 

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

