/*
 * Copyright (C) 2016 EPFL
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/.
 */

/**
 * @file CelluloBluetoothSharedDefs.h
 * @brief c (exclusive) header for definitions shared with the robot
 * @author Ayberk Özgür
 * @date 2016-06-07
 */

#ifndef CELLULOBLUETOOTHSHAREDDEFS_H
#define CELLULOBLUETOOTHSHAREDDEFS_H

#define PACKET_START_CHAR_SHARED 0x01 ///< First character of all packets
#define IMG_WIDTH_SHARED (752/4)      ///< Width of localization camera image
#define IMG_HEIGHT_SHARED (480/4)     ///< Height of localization camera image
#define GOAL_POSE_FACTOR_SHARED 100   ///< Goal pose elements are multiplied by this before being sent over comm. channel
#define GOAL_VEL_FACTOR_SHARED 100    ///< Goal velocity elements are multiplied by this before being sent over comm. channel
#define DOTS_GRID_SPACING 0.508f      ///< Average distance between two grid lines in localization dots grid

/**
 * @brief Battery states
 */
#define BATTERY_STATE_ENUM_SHARED enum BatteryState { \
        BatteryStateDischarging = 0, /** No charger present, battery draining */ \
        BatteryStateLow = 1,         /** No charger present, battery low, will shut down */ \
        BatteryStateCharging = 2,    /** Charger present, battery charging */ \
        BatteryStateCharged = 3,     /** Charger present, battery full */ \
        BatteryStateShutdown = 4,    /** Charger charging disabled, voltage too low or battery not present */ \
        BatteryStateError = 5,       /** Thermal fault or charge timeout */ \
        BatteryStateNumElements \
}

/**
 * @brief LED response modes
 */
#define LED_RESPONSE_MODE_ENUM_SHARED enum LEDResponseMode { \
        LEDResponseModeResponsiveIndividual = 0, /** LEDs respond to touches by slightly increasing brightness */ \
        LEDResponseModeAbsolute = 1,             /** LEDs don't respond to touches */ \
        LEDResponseModeResponsiveHold = 2,       /** LEDs respond to hold by all changing color */ \
        LEDResponseModeNumElements \
}

/**
 * @brief Locomotion response modes
 */
#define LOCOMOTION_INTERACTIVITY_MODE_ENUM_SHARED enum LocomotionInteractivityMode { \
        LocomotionInteractivityModeNormal = 0,       /** Robot moves normally */ \
        LocomotionInteractivityModeRequiresHold = 1, /** Robot requires Hold gesture */ \
        LocomotionInteractivityModeNumElements \
}

/**
 * @brief Visual effect types
 */
#define VISUAL_EFFECT_ENUM_SHARED enum VisualEffect { \
        VisualEffectConstAll = 0,    /** Set all LED colors (value unused) */ \
        VisualEffectConstSingle = 1, /** Set one LED color (value is LED index) */ \
        VisualEffectAlertAll = 2,    /** Alert animation for all LEDs (value unused) */ \
        VisualEffectAlertSingle = 3, /** Alert animation for one LED (value is LED index) */ \
        VisualEffectProgress = 4,    /** Static progress circularly (value 0-255 maps to 0-100%) */ \
        VisualEffectWaiting = 5,     /** Circular waiting/processing animation (value unused) */ \
        VisualEffectDirection = 6,   /** Point toward one direction (value 0-255 maps to 0-360 degrees) */ \
        VisualEffectBlink = 7,       /** Alert forever (value*20 is LED on time in milliseconds) */ \
        VisualEffectBreathe = 8,     /** Breathe animation (value unused) */ \
        VisualEffectPulse = 9,       /** Slower breathe-like animation (value unused) */ \
        VisualEffectNumElements \
}

/**
 * @brief App to robot message types
 */
#define COMMAND_PACKET_TYPE_ENUM_SHARED enum CmdPacketType { \
        CmdPacketTypePing = 0,                       /** Ping robot, which will send an acknowledge event */ \
        CmdPacketTypeSetBcastPeriod,                 /** Set pose broadcast period */ \
        CmdPacketTypeTimestampEnable,                /** Enable/disable sending timestamp along with pose */ \
        CmdPacketTypeFrameRequest,                   /** Request a camera image frame */ \
        CmdPacketTypeBatteryStateRequest,            /** Request battery state */ \
        CmdPacketTypeSetLEDResponseMode,             /** Set LED response mode */ \
        CmdPacketTypeSetLocomotionInteractivityMode, /** Set the locomotion interactivity mode */ \
        CmdPacketTypeGestureEnable,                  /** Enable/disable querying and processing raw touch signals */ \
        CmdPacketTypeCasualBackdriveAssistEnable,    /** Enable/disable backdrive assist for just easy backdriving */ \
        CmdPacketTypeHapticBackdriveAssist,          /** Backdrive assist for specific haptic feedback */ \
        CmdPacketTypeSetVisualEffect,                /** Set visual effect */ \
        CmdPacketTypeSetMotorOutput,                 /** Set output of one motor */ \
        CmdPacketTypeSetAllMotorOutputs,             /** Set output of all motors */ \
        CmdPacketTypeSetGoalVelocity,                /** Set goal global velocity */ \
        CmdPacketTypeSetGoalPose,                    /** Set goal pose */ \
        CmdPacketTypeSetGoalPosition,                /** Set goal position */ \
        CmdPacketTypeSetGoalXCoordinate,             /** Set goal x coordinate */ \
        CmdPacketTypeSetGoalYCoordinate,             /** Set goal y coordinate */ \
        CmdPacketTypeSetGoalOrientation,             /** Set goal orientation */ \
        CmdPacketTypeSetGoalXThetaCoordinate,        /** Set goal x and theta coordinate */ \
        CmdPacketTypeSetGoalYThetaCoordinate,        /** Set goal y and theta coordinate */ \
        CmdPacketTypeClearTracking,                  /** Clears goal pose/position/velocity */ \
        CmdPacketTypeSimpleVibrate,                  /** Simple vibration haptic feedback */ \
        CmdPacketTypeVibrateOnMotion,                /** Vibration with intensity proportional to drive velocities*/ \
        CmdPacketTypeClearHapticFeedback,            /** Clears all haptic feedbacks */ \
        CmdPacketTypePolyBezierInit,                 /** Sets the first control point of the composite Bézier curve for tracking */ \
        CmdPacketTypePolyBezierAppend,               /** Appends 3 control points to the composite Bézier curve for tracking */ \
        CmdPacketTypeSetGoalPolyBezier,              /** Starts tracking the previously set composite Bézier curve */ \
        CmdPacketTypeReset,                          /** Request reset */ \
        CmdPacketTypeShutdown,                       /** Request shutdown */ \
        CmdPacketTypeNumElements, \
}

/*
 * @brief App to robot message identifiers
 */
#define COMMAND_PACKET_STR_SHARED { \
        "P", /** CmdPacketTypePing */ \
        "D", /** CmdPacketTypeSetBcastPeriod */ \
        "T", /** CmdPacketTypeTimestampEnable */ \
        "F", /** CmdPacketTypeFrameRequest */ \
        "B", /** CmdPacketTypeBatteryStateRequest */ \
        "L", /** CmdPacketTypeSetLEDResponseMode */ \
        "I", /** CmdPacketTypeSetLocomotionInteractivityMode */ \
        "U", /** CmdPacketTypeGestureEnable */ \
        "K", /** CmdPacketTypeCasualBackdriveAssistEnable */ \
        "Y", /** CmdPacketTypeHapticBackdriveAssist */ \
        "E", /** CmdPacketTypeSetVisualEffect */ \
        "M", /** CmdPacketTypeSetMotorOutput */ \
        "A", /** CmdPacketTypeSetAllMotorOutputs */ \
        "C", /** CmdPacketTypeSetGoalVelocity */ \
        "G", /** CmdPacketTypeSetGoalPose */ \
        "N", /** CmdPacketTypeSetGoalPosition */ \
        "-", /** CmdPacketTypeSetGoalXCoordinate */ \
        "|", /** CmdPacketTypeSetGoalYCoordinate */ \
        "O", /** CmdPacketTypeSetGoalOrientation */ \
        "\\",/** CmdPacketTypeSetGoalXThetaCoordinate */ \
        "/", /** CmdPacketTypeSetGoalYThetaCoordinate */ \
        "X", /** CmdPacketTypeClearTracking */ \
        "V", /** CmdPacketTypeSimpleVibrate */ \
        "Z", /** CmdPacketTypeVibrateOnMotion */ \
        "H", /** CmdPacketTypeClearHapticFeedback */ \
        ".", /** CmdPacketTypePolyBezierInit */ \
        "~", /** CmdPacketTypePolyBezierAppend */ \
        "J", /** CmdPacketTypeSetGoalPolyBezier */ \
        "R", /** CmdPacketTypeReset */ \
        "S"  /** CmdPacketTypeShutdown */ \
}

/*
 * @brief App to robot message payload lengths
 */
#define COMMAND_PACKET_PAYLOAD_LEN_SHARED { \
        0,                 /** CmdPacketTypePing */ \
        2,                 /** CmdPacketTypeSetBcastPeriod: uint16 periodMillis */ \
        1,                 /** CmdPacketTypeTimestampEnable: uint8 bool */ \
        0,                 /** CmdPacketTypeFrameRequest */ \
        0,                 /** CmdPacketTypeBatteryStateRequest */ \
        1,                 /** CmdPacketTypeSetLEDResponseMode: uint8 mode */ \
        1,                 /** CmdPacketTypeSetLocomotionInteractivityMode: uint8 mode */ \
        1,                 /** CmdPacketTypeGestureEnable: uint8 bool */ \
        1,                 /** CmdPacketTypeCasualBackdriveAssistEnable: uint8 bool */ \
        2 + 2 + 2,         /** CmdPacketTypeHapticBackdriveAssist: int16 xassist, int16 yassist, int16 thetaassist */ \
        1 + 1 + 1 + 1 + 1, /** CmdPacketTypeSetVisualEffect: uint8 effect, uint8 red, uint8 green, uint8 blue, uint8 value */ \
        1 + 2,             /** CmdPacketTypeSetMotorOutput: uint8 motorIndex, int16 output (-0xFFF to 0xFFF) */ \
        2 + 2 + 2,         /** CmdPacketTypeSetAllMotorOutputs: int16 m1Output, int16 m2Output, int16 m3Output (-0xFFF to 0xFFF) */ \
        2 + 2 + 2,         /** CmdPacketTypeSetGoalVelocity: int16 vx, int16 vy, int16 w */ \
        4 + 4 + 2 + 2 + 2, /** CmdPacketTypeSetGoalPose: uint32 x, uint32 y, uint16 theta, uint16 vMax, uint6 wMax */ \
        4 + 4 + 2,         /** CmdPacketTypeSetGoalPosition: uint32 x, uint32 y, uint16 vMax */ \
        4 + 2,             /** CmdPacketTypeSetGoalXCoordinate: uint32 x, uint16 vMax */ \
        4 + 2,             /** CmdPacketTypeSetGoalYCoordinate: uint32 y, uint16 vMax */ \
        2 + 2,             /** CmdPacketTypeSetGoalOrientation: uint16 theta, uint16 wMax */ \
        4 + 2 + 2 + 2,     /** CmdPacketTypeSetGoalXThetaCoordinate: uint32 x, uint16 theta, uint16 vMax, uint6 wMax */ \
        4 + 2 + 2 + 2,     /** CmdPacketTypeSetGoalYThetaCoordinate: uint32 y, uint16 theta, uint16 vMax, uint6 wMax */ \
        0,                 /** CmdPacketTypeClearTracking */ \
        2 + 2 + 2 + 2 + 2, /** CmdPacketTypeSimpleVibrate: uint16 ix, uint16 iy, uint16 itheta, uint16 period, uint16 duration */ \
        2 + 2,             /** CmdPacketTypeVibrateOnMotion: uint16 icoeff, uint16 period */ \
        0,                 /** CmdPacketTypeClearHapticFeedback */ \
        4 + 4,             /** CmdPacketTypePolyBezierInit: float x0, float y0 */ \
        3*(4 + 4),         /** CmdPacketTypePolyBezierAppend: float x1, float y1, float x2, float y2, float x3, float y3 */ \
        2,                 /** CmdPacketTypeSetGoalPolyBezier: uint16 v */ \
        0,                 /** CmdPacketTypeReset */ \
        0                  /** CmdPacketTypeShutdown */ \
}

/**
 * @brief Robot to app message types
 */
#define EVENT_PACKET_TYPE_ENUM_SHARED enum EventPacketType { \
        EventPacketTypeBootComplete = 0,       /** Boot completed after reset */ \
        EventPacketTypeShuttingDown,           /** About to shut down */ \
        EventPacketTypeLowBattery,             /** Battery is low, about to shut down */ \
        EventPacketTypeBatteryStateChanged,    /** Battery state is changed */ \
        EventPacketTypeTouchBegan,             /** Key was touched */ \
        EventPacketTypeTouchLongPressed,       /** Key was touched for a time */ \
        EventPacketTypeTouchReleased,          /** Key was released */ \
        EventPacketTypePoseChanged,            /** Pose changed */ \
        EventPacketTypePoseChangedTimestamped, /** Pose changed, timestamp attached to message */ \
        EventPacketTypeKidnapChanged,          /** Kidnap state changed */ \
        EventPacketTypeTrackingGoalReached,    /** Pose/position/angle tracking goal reached */ \
        EventPacketTypeAcknowledged,           /** Acknowledged */ \
        EventPacketTypeFrameLine,              /** Camera frame line is sent */ \
        EventPacketTypeDebug,                  /** Debug message */ \
        EventPacketTypeNumElements \
}

/**
 * @brief Robot to app message identifiers
 */
#define EVENT_PACKET_STR_SHARED { \
        "O", /** EventPacketTypeBootComplete */ \
        "D", /** EventPacketTypeShuttingDown */ \
        "W", /** EventPacketTypeLowBattery */ \
        "B", /** EventPacketTypeBatteryStateChanged */ \
        "T", /** EventPacketTypeTouchBegan */ \
        "L", /** EventPacketTypeTouchLongPressed */ \
        "R", /** EventPacketTypeTouchReleased */ \
        "P", /** EventPacketTypePoseChanged */ \
        "S", /** EventPacketTypePoseChangedTimestamped */ \
        "K", /** EventPacketTypeKidnapChanged */ \
        "G", /** EventPacketTypeTrackingGoalReached */ \
        "A", /** EventPacketTypeAcknowledged */ \
        "C", /** EventPacketTypeFrameLine */ \
        "E"  /** EventPacketTypeDebug */ \
}

/**
 * @brief Robot to app message payload lengths
 */
#define EVENT_PACKET_PAYLOAD_LEN_SHARED { \
        0,                    /** EventPacketTypeBootComplete */ \
        0,                    /** EventPacketTypeShuttingDown */ \
        0,                    /** EventPacketTypeLowBattery */ \
        1,                    /** EventPacketTypeBatteryStateChanged: uint8 batteryState */ \
        1,                    /** EventPacketTypeTouchBegan: uint8 keyIndex */ \
        1,                    /** EventPacketTypeTouchLongPressed: uint8 keyIndex */ \
        1,                    /** EventPacketTypeTouchReleased: uint8 keyIndex */ \
        4 + 4 + 2,            /** EventPacketTypePoseChanged: uint32 x, uint32 y, uint16 theta */ \
        4 + 4 + 2 + 4,        /** EventPacketTypePoseChangedTimestamped uint32 x, uint32 y, uint16 theta, uint32 timestamp */ \
        1,                    /** EventPacketTypeKidnapChanged: uint8 kidnappedBool */ \
        0,                    /** EventPacketTypeTrackingGoalReached */ \
        0,                    /** EventPacketTypeAcknowledged */ \
        2 + IMG_WIDTH_SHARED, /** EventPacketTypeFrameLine: uint16 currentLineIndex, IMG_WIDTH*uint8 grayscalePixel */ \
        12                     /** EventPacketTypeDebug */ \
}

#endif // CELLULOBLUETOOTHSHAREDDEFS_H
