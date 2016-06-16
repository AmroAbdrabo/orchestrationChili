import QtQuick 2.0

//item to compute speed of robot depeding on its distance to the heatZones
Item {
    //ALL VALUE ARE IN MM
    property var robotPosition
    property var heatZones
    property var maxSpeed
    property var minSpeed
    property var sigma
    property var heatPointsDistances: {
        var result = []
        for(var i= 0; i< heatZones.length; i++){
            var heatZone = heatZones[i]
            result.push({name: heatZone.nameHeatZone, d: -1, vMax:heatZone.isHot? maxSpeed: minSpeed})
        }

        return result
    }

    function computeSpeed(){
        var result = 0
        var denominator = 0
        var funcResult = []
        for(var i=0; i< heatPointsDistances.length; i++){
            var d = heatPointsDistances[i].d
            var extraFunctionResult = extraFunction(d, sigma)
            funcResult.push(extraFunctionResult)
            denominator += extraFunctionResult
        }
        for(var j=0; j< heatPointsDistances.length; j++){
            result += (heatPointsDistances[j].vMax * funcResult[j]/denominator)
        }
        return result

    }

    function extraFunction(x, sigma){
        return Math.exp(-0.5* ((x/sigma)*(x/sigma)))
    }

    function changeDistanceForHeatZone(zoneName, distance){
        var zoneNameShorten = zoneName.split("_")[1]
        for(var i =0; i <heatPointsDistances.length; i++){
            if(heatPointsDistances[i].name===zoneNameShorten){
                heatPointsDistances[i].d = distance
            }
        }
        return ({})
    }
}
