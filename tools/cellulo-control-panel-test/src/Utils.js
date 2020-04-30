function createZones(){
    /*fruitzones = CelluloZoneJsonHandler.loadZonesQML(":/assets/orangefruits.json");

    for(var l=0;l<fruitzones.length;l++){
        fruitzones[l].active = true;
        zoneEngine.addNewZone(fruitzones[l])
    }*/
    fruitzones = CelluloZoneJsonHandler.loadZonesQML(":/assets/orangefruits.json");
    for(var l=0;l<fruitzones.length;l++){
        fruitzones[l].active = true;
        zoneEngine.addNewZone(fruitzones[l])
    }
    //console.log("fruits zone length "+fruitzones.length)

    innerzones = CelluloZoneJsonHandler.loadZonesQML(":/assets/orangeinner.json");
    for(var i=0;i<innerzones.length;i++){
        innerzones[i].active = true;
        zoneEngine.addNewZone(innerzones[i])
    }
    for(var p=0;p<innerzones.length;p++){
        crossedBorder[p]=false;
    }
    //console.log("zone length "+innerzones.length)

    closestzones = CelluloZoneJsonHandler.loadZonesQML(":/assets/orangeclosest.json");
    for(var k=0;k<closestzones.length;k++){
        closestzones[k].active = true;
    }
    //console.log("closest zone length "+closestzones.length)
    zoneEngine.addNewZones(closestzones)

    distancezones = CelluloZoneJsonHandler.loadZonesQML(":/assets/orangedistance.json");
    for(var j=0;j<distancezones.length;j++){
        distancezones[j].active = true;
    }
    //console.log("distance zone length "+distancezones.length)
    zoneEngine.addNewZones(distancezones)


    borderlinezones = CelluloZoneJsonHandler.loadZonesQML(":/assets/orangelinesborder.json");
    for(var s=0;s<borderlinezones.length;s++){
        borderlinezones[s].active = true;
        inLineBorder[s]=false; //what is this? what are distance zones ect...
    }
    //console.log("zone length "+borderlinezones.length)
    zoneEngine.addNewZones(borderlinezones)

    rectzones = CelluloZoneJsonHandler.loadZonesQML(":/assets/orangerect.json");
    for(var x=0;x<rectzones.length;x++){
        rectzones[x].active = true;
        zoneEngine.addNewZone(rectzones[x])
    }
    //console.log("rect zone length "+rectzones.length)
    //wallBetweenTwoRobotsArray=new Array(rectzones.length) //had to remove this
}
