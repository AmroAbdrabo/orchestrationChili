import QtQuick 2.5

import Cellulo 1.0

/**
 * @brief Cellulo robot object
 */
CelluloBluetooth{

    /**
     * Public
     */

    property bool poseVelControlEnabled: false              ///< Whether the simultaneous pose and velocity controller is enabled, must be enabled by the user
    property int poseVelControlPeriod: 20                   ///< Desired pose/velocity control period in ms, set to 0 for highest possible frequency
    property vector3d vxyw: Qt.vector3d(0,0,0)              ///< Robot's estimated velocity in mm/s, mm/s, rad/s; must not be set by the user

    property vector3d kGoalVel: Qt.vector3d(0.9,0.9,0.9)    ///< Goal velocity coefficients when tracking pose/velocity, do not change if you don't have a good reason
    property vector3d kGoalVelErr: Qt.vector3d(0.2,0.2,0.2) ///< Goal velocity error coefficients when tracking pose/velocity, do not change if you don't have a good reason
    property vector3d kGoalPoseErr: Qt.vector3d(2,2,2.3)

    /**
     * @brief Sets the simultaneous pose and velocity goal of the robot, i.e the robot tries to be at the pose and move with the desired velocity while there
     *
     * @param {real} x X coordinate (larger than 0mm)
     * @param {real} y Y coordinate (larger than 0mm)
     * @param {real} theta Orientation (between -180 degrees and 180 degrees)
     * @param {real} Vx X velocity (between -185 mm/s and and 185 mm/s)
     * @param {real} Vy Y velocity (between -185 mm/s and and 185 mm/s)
     * @param {real} w Angular velocity (between -7.5 rad/s and 7.5 rad/s)
     */
    function setGoalPoseAndVelocity(x, y, theta, Vx, Vy, w){
        goalPose = Qt.vector3d(x,y,theta);
        goalVel = Qt.vector3d(Vx,Vy,w);
        if(!poseVelControlEnabled)
            console.log("CelluloRobot.setGoalPoseAndVelocity(): Warning, setGoalPoseAndVelocity() called but poseVelControlEnabled is not true, nothing will happen.")
    }

    signal nextGoalPoseVelRequested()   ///< Emitted when the controller needs the next goal pose and velocity; setGoalPoseAndVelocity() should be called by the user upon receiving this signal if a user control loop that cycles on each received pose of the robot is present

    /**
     * Private
     */

    id: root


    property vector3d goalPose: Qt.vector3d(0,0,0)                      ///< Latest x, y, theta goal
    property vector3d goalVel: Qt.vector3d(0,0,0)                       ///< Latest Vx, Vy, w goal
    property bool velEstimateNeedsReset: true                           ///< If true, velocity estimate variables will be reset in the next cycle
    property vector3d lastPose: Qt.vector3d(0,0,0)                      ///< Previous robot pose
    property real lastTime: 0                                           ///< Previous timestamp

    readonly property real bcastPeriodMin: poseVelControlPeriod - 50    ///< Pose broadcast with less than this period will be discarded when calculating the velocity
    readonly property real bcastPeriodMax: poseVelControlPeriod + 100   ///< Pose broadcast with more than this period will be discarded when calculating the velocity
    readonly property real maxEstimatedXYVel: 1000                      ///< Clamp limit for the estimated linear robot velocity, in mm/s
    readonly property real maxEstimatedW: 50                            ///< Clamp limit for the estimated angular robot velocity, in rad/s
    readonly property real vMu: 0                                       ///< Smoothing coefficient for velocity estimate

    /**
     * @brief Initializes the robot to the settings necessary to run the controllers, initializes controllers
     */
    function init(){
        if(connectionStatus === CelluloBluetoothEnums.ConnectionStatusConnected){
            setPoseBcastPeriod(poseVelControlPeriod);
            setTimestampingEnabled(true);

            velEstimateNeedsReset = true;
            lastPose = Qt.vector3d(0,0,0);
            lastTime = 0;

            nextGoalPoseVelRequested();
        }
    }

    onBootCompleted: init()
    onPoseVelControlPeriodChanged: init()
    onConnectionStatusChanged: init()
    onPoseVelControlEnabledChanged: init()

    onKidnappedChanged: velEstimateNeedsReset = true

    /**
     * @brief Estimates the robot velocity
     */
    function estimateVel(){
        var newTime = lastTimestamp;
        var deltaTime = newTime - lastTime;
        var newPose = Qt.vector3d(x,y,theta);

        var newVxyw = newPose.minus(lastPose);
        while(newVxyw.z <= -180)
            newVxyw.z += 360;
        while(newVxyw.z > 180)
            newVxyw.z -= 360;
        newVxyw.z = newVxyw.z*Math.PI/180;

        newVxyw = newVxyw.times(1000/deltaTime);
        if(bcastPeriodMin < deltaTime && deltaTime < bcastPeriodMax){
            if(velEstimateNeedsReset){
                velEstimateNeedsReset = false;
                vxyw = newVxyw;
            }
            else
                vxyw = vxyw.times(vMu).plus(newVxyw.times(1 - vMu));
        }
        else if(bcastPeriodMax <= deltaTime){
            velEstimateNeedsReset = true;
            vxyw = newVxyw;
        }
        else
            velEstimateNeedsReset = true;

        if(vxyw.x > maxEstimatedXYVel)
            vxyw.x = maxEstimatedXYVel;
        else if(vxyw.x < -maxEstimatedXYVel)
            vxyw.x = -maxEstimatedXYVel;
        if(vxyw.y > maxEstimatedXYVel)
            vxyw.y = maxEstimatedXYVel;
        else if(vxyw.y < -maxEstimatedXYVel)
            vxyw.y = -maxEstimatedXYVel;
        if(vxyw.z > maxEstimatedW)
            vxyw.z = maxEstimatedW;
        else if(vxyw.z < -maxEstimatedW)
            vxyw.z = -maxEstimatedW;

        lastPose = newPose;
        lastTime = newTime;
    }

    /**
     * @brief Calculates goal velocities to simultaneously reach pose and velocity goals
     */
    function commandVel(){
        nextGoalPoseVelRequested();

        //Goal velocity component
        var commandVel = goalVel.times(kGoalVel);

        //Goal velocity error component
        var velErr = goalVel.minus(vxyw);
        commandVel = commandVel.plus(velErr.times(kGoalVelErr));

        //Goal pose error component
        var poseErr = goalPose.minus(Qt.vector3d(x,y,theta));
        while(poseErr.z > 180)
            poseErr.z -= 360;
        while(poseErr.z <= -180)
            poseErr.z += 360;
        poseErr.z = poseErr.z/180*Math.PI;
        commandVel = commandVel.plus(poseErr.times(kGoalPoseErr));

        //Clamp goal velocity
        if(commandVel.x > 200)
            commandVel.x = 200;
        else if(commandVel.x < -200)
            commandVel.x = -200;
        if(commandVel.y > 200)
            commandVel.y = 200;
        else if(commandVel.y < -200)
            commandVel.y = -200;
        if(commandVel.z > 10)
            commandVel.z = 10;
        else if(commandVel.z < -10)
            commandVel.z = -10;

        setGoalVelocity(commandVel.x, commandVel.y, commandVel.z);
    }

    onPoseChanged: {
        estimateVel();
        if(poseVelControlEnabled)
            commandVel();
    }
}
