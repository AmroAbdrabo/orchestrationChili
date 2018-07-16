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
 * @file PolyBezierTracker.h
 * @brief Makes CelluloRobots track PolyBezier curves
 * @author Ayberk Özgür
 * @date 2018-07-13
 */

#include "PolyBezierTracker.h"

namespace Cellulo{

PolyBezierTracker::PolyBezierTracker(QQuickItem* parent) : QQuickItem(parent) {
    curve = nullptr;
    robot = nullptr;
    setEnabled(false);
}

PolyBezierTracker::~PolyBezierTracker(){
}

void PolyBezierTracker::itemChange(ItemChange change, ItemChangeData const& value){
    if(change == ItemChange::ItemChildRemovedChange){
        PolyBezier* removedChild = qobject_cast<PolyBezier*>(value.item);
        if(removedChild == curve)
            setCurve(nullptr);
    }
    else if(change == ItemChange::ItemChildAddedChange){
        PolyBezier* addedChild = qobject_cast<PolyBezier*>(value.item);
        if(addedChild)
            setCurve(addedChild);
    }
    else if(change == ItemChange::ItemParentHasChanged){
        CelluloRobot* newParent = qobject_cast<CelluloRobot*>(value.item);
        if(newParent)
            setRobot(newParent);
    }

    QQuickItem::itemChange(change, value);
}

void PolyBezierTracker::setCurve(PolyBezier* newCurve){
    if(curve)
        disconnect(curve, SIGNAL(controlPointsChanged()), this, SLOT(updateCurve()));
    curve = newCurve;
    if(curve)
        connect(curve, SIGNAL(controlPointsChanged()), this, SLOT(updateCurve()));
    emit curveChanged();
}

void PolyBezierTracker::setRobot(CelluloRobot* newRobot){
    if(robot)
        disconnect(robot, SIGNAL(nextGoalPoseVelRequested(qreal)), this, SLOT(robotControlLoop(qreal)));
    robot = newRobot;
    if(robot){
        connect(robot, SIGNAL(nextGoalPoseVelRequested(qreal)), this, SLOT(robotControlLoop(qreal)));
        robot->setPoseVelControlPeriod(100); //TODO: MAKE ADJUSTABLE
        robot->setPoseVelControlEnabled(true);
    }
    emit robotChanged();
}

void PolyBezierTracker::trackConstLinearVel(qreal vel, bool goToStart){
    trackingVel = vel;
    goingToStart = goToStart;
    if(!goToStart){
        //TODO: GET CLOSEST T, calculate R
    }
    else{
        currentT = 0.0;
        currentR = 0.0;
    }
    setEnabled(true);
}

void PolyBezierTracker::updateCurve(){



//TODO: RECALCULATE lastR
//TODO: RECALCULATE lastT






}

void PolyBezierTracker::robotControlLoop(qreal deltaTime){
    if(robot && curve){
        if(isEnabled()){

            //TODO: REIMPLEMENT THIS PART IN PURE VIRTUAL FUNCTIONS
            QVector2D currentPos(robot->getX(), robot->getY());
            if(goingToStart){
                QVector2D goalPos = curve->getPoint(0.0);
                QVector2D goalDiff = goalPos - currentPos;
                QVector2D goalDir = goalDiff/(10*GOAL_EPSILON);
                if(goalDir.length() > 1.0)
                    goalDir.normalize();
                QVector2D goalVel = goalDir*trackingVel;

                robot->setGoalPoseAndVelocity(goalPos.x(), goalPos.y(), 0, goalVel.x(), goalVel.y(), 0, true, true, false);

                if(goalDiff.length() <= GOAL_EPSILON){
                    qDebug() << "REACHED BEGIN";
                    goingToStart = false;
                }
            }
            else{
                currentT = curve->getTByArcLengthRatio(currentR);
                QVector2D goalPos = curve->getPoint(currentT);
                QVector2D goalVel;
                if(currentR < 1.0)
                    goalVel = curve->getTangent(currentT).normalized()*trackingVel;
                else{
                    QVector2D goalDir = (curve->getPoint(curve->getTByArcLengthRatio(1.0)) - currentPos)/(10*GOAL_EPSILON);
                    if(goalDir.length() > 1.0)
                        goalDir.normalize();
                    goalVel = goalDir*trackingVel;
                }

                robot->setGoalPoseAndVelocity(goalPos.x(), goalPos.y(), 0, goalVel.x(), goalVel.y(), 0, true, true, false);

                if(currentR < 1.0){
                    currentR += (trackingVel*100.0/1000.0)/curve->getArcLength(); //TODO: GET PERIOD FROM ADJUSTED
                    if(currentR > 1.0)
                        currentR = 1.0;
                }
                else{
                    if(currentPos.distanceToPoint(curve->getPoint(curve->getTByArcLengthRatio(1.0))) <= GOAL_EPSILON){
                        qDebug() << "REACHED END";
                        setEnabled(false);
                    }
                }
            }
        }
        else
            robot->setGoalPoseAndVelocity(0, 0, 0, 0, 0, 0, false, false, false);
    }
    else
        qCritical() << "PolyBezierTracker::robotControlLoop(): Robot or curve not yet set, exiting.";
}

}
