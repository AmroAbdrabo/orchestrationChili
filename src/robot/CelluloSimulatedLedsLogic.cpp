#include "CelluloSimulatedLedsLogic.h"

//gesture features are not implemented
//

//#include <xc.h>
//#include <sys/attribs.h>
//#include "system_definitions.h"
//#include "power.h"
//#include "gesture.h"

#include <QDebug>


celluloSimulatedLedsLogic::celluloSimulatedLedsLogic() {
    then = std::chrono::system_clock::now(); //get current chrono timer for systemMillis
    updateRequested = false;
    sleepRequested = false;
    APP_LED_Initialize();
}

float celluloSimulatedLedsLogic::systemMillis() {
    auto now = std::chrono::system_clock::now();
    auto dur = now-then;
    auto secs = std::chrono::duration_cast<std::chrono::milliseconds>(dur);
    float fSec = secs.count();
    return fSec;
}

void celluloSimulatedLedsLogic::APP_LED_Initialize(){
    ledResponseMode = LEDResponseModeResponsiveIndividual;
    updateRequested = false;
    latched = false;
    sleepRequested = false;
    //prevGesture = GestureNone;

/*    if(bootState != BOOT_STATE_SOFTWARE_RESET && bootState != BOOT_STATE_WATCHDOG_TIMEOUT)
        setVisualEffect(Cellulo::CelluloBluetoothEnums::VisualEffectConstAll,
                        LED_IDLE_BRIGHTNESS*255/4095, LED_IDLE_BRIGHTNESS*255/4095, LED_IDLE_BRIGHTNESS*255/4095, 0);

    //If we reset deliberately (software reset) or by error recovery (watchdog), do not alter the state of the LEDs
    else{*/

        //Dummy colors and effect values
    unsigned int i;
    for(i=0; i<6; i++){
        currentLEDColors[i][0] = LED_IDLE_BRIGHTNESS;
        currentLEDColors[i][1] = LED_IDLE_BRIGHTNESS;
        currentLEDColors[i][2] = LED_IDLE_BRIGHTNESS;
        previousLEDColors[i][0] = LED_IDLE_BRIGHTNESS;
        previousLEDColors[i][1] = LED_IDLE_BRIGHTNESS;
        previousLEDColors[i][2] = LED_IDLE_BRIGHTNESS;
        previousLEDColors[i][0] = LED_IDLE_BRIGHTNESS;
        previousLEDColors[i][1] = LED_IDLE_BRIGHTNESS;
        previousLEDColors[i][2] = LED_IDLE_BRIGHTNESS;


    }
    currentLEDNumber = 0;
    effectCounter1 = 0;
    effectCounter2 = 0;
    effectTransition = false;
    currentEffectValue = 0;
    previousEffectColor[0] = LED_IDLE_BRIGHTNESS;
    previousEffectColor[1] = LED_IDLE_BRIGHTNESS;
    previousEffectColor[2] = LED_IDLE_BRIGHTNESS;   ///< stores the previouS effect color

    effectColor[0] = LED_IDLE_BRIGHTNESS;
    effectColor[1] = LED_IDLE_BRIGHTNESS;
    effectColor[2] = LED_IDLE_BRIGHTNESS;
    visualEffect = Cellulo::CelluloBluetoothEnums::VisualEffectConstAll;
    currentEffectValue = 0;

}

bool celluloSimulatedLedsLogic::transitionLED(unsigned int led, short red, short green, short blue, short inertia){
    //Return whether transition finished
    if(
        (currentLEDColors[led][0] <= red && currentLEDColors[led][0] >= red - inertia) &&
        (currentLEDColors[led][1] <= green && currentLEDColors[led][1] >= green - inertia) &&
        (currentLEDColors[led][2] <= blue && currentLEDColors[led][2] >= blue - inertia)) {
        return true;
    }
    currentLEDColors[led][0] = (inertia*currentLEDColors[led][0] + red)/(inertia + 1);
    currentLEDColors[led][1] = (inertia*currentLEDColors[led][1] + green)/(inertia + 1);
    currentLEDColors[led][2] = (inertia*currentLEDColors[led][2] + blue)/(inertia + 1);
    return false;
}

void celluloSimulatedLedsLogic::suspendLEDsSleep(){
    //T3CONbits.ON = 0;
}

void celluloSimulatedLedsLogic::suspendLEDsIdle(){
    unsigned int i;
    for(i=0; i<6; i++)
        /*setLEDTemporary(i,
                        currentLEDColors[i][0]/LED_IDLE_MODE_BRIGHTNESS_DIVISOR,
                        currentLEDColors[i][1]/LED_IDLE_MODE_BRIGHTNESS_DIVISOR,
                        currentLEDColors[i][2]/LED_IDLE_MODE_BRIGHTNESS_DIVISOR);*/
    requestLEDUpdate();

    i = 0;
    while(!latched){
        i++;
        if(i>10000000)
            break;
    }
    //T3CONbits.ON = 0;
}

void celluloSimulatedLedsLogic::resumeLEDsSleep(){
    //Block until LEDs light up
    setVisualEffect(Cellulo::CelluloBluetoothEnums::VisualEffectConstAll, LED_IDLE_BRIGHTNESS*255/4095, LED_IDLE_BRIGHTNESS*255/4095, LED_IDLE_BRIGHTNESS*255/4095, 0);
    unsigned int i;
    while(effectTransition)
        if(!updateRequested){
            effectTransition = false;
            for(i=0; i<6; i++)
                if(!transitionLED(i, effectColor[0], effectColor[1], effectColor[2], LED_TRANSITION_INERTIA_DEFAULT))
                    effectTransition = true;
            if(effectTransition)
                requestLEDUpdate();
        }
}

void celluloSimulatedLedsLogic::resumeLEDsIdle(){
    //Restore brightness
    unsigned int i;
    for(i=0; i<6; i++)
        /*setLEDTemporary(i,
                        currentLEDColors[i][0],
                        currentLEDColors[i][1],
                        currentLEDColors[i][2]);*/
    requestLEDUpdate();
}

void celluloSimulatedLedsLogic::lowBatteryAnimation(){

    //Block until animation is complete
    effectCounter1 = systemMillis();
    effectCounter2 = 0;
    unsigned int i;
    for(i=0; i<6; i++)
        setLED(i, 0x800, 0, 0);
    requestLEDUpdate();
    while(true){

        //Alert going on
        if(systemMillis() > LED_ALERT_FLASH_MILLIS + effectCounter1){
            effectCounter1 = systemMillis();
            effectCounter2++;

            //Alert ended
            if(effectCounter2 >= 6)
                break;

            //Alert going on, time to toggle
            else{
                if(effectCounter2 % 2)
                    for(i=0; i<6; i++)
                        setLED(i,0,0,0);
                else
                    for(i=0; i<6; i++)
                        setLED(i, 0x800, 0, 0);

                requestLEDUpdate();
            }
        }
    }

    //Turn timer off, we're going back to sleep
   // T3CONbits.ON = 0;
}

void celluloSimulatedLedsLogic::APP_LED_Tasks(){
    unsigned int i;

    //Turn off LEDs if sleep mode requested
    if(sleepRequested)
        setVisualEffect(Cellulo::CelluloBluetoothEnums::VisualEffectConstAll,0,0,0,0);

    //Gesture-related jobs
    /*if(gestureEnabled){
        if(currentGesture != prevGesture){

            if(ledResponseMode == LEDResponseModeResponsiveHold){
                switch(currentGesture){
                    case GestureHold:
                        previousVisualEffect = visualEffect;
                        previousEffectColor[0] = effectColor[0]*255/4095;
                        previousEffectColor[1] = effectColor[1]*255/4095;
                        previousEffectColor[2] = effectColor[2]*255/4095;
                        previousEffectValue = currentEffectValue;
                        setVisualEffect(VisualEffectConstAll, 0, 128, 0, 0);
                        break;

                    case GestureNone:
                        setVisualEffect(previousVisualEffect, previousEffectColor[0], previousEffectColor[1], previousEffectColor[2], previousEffectValue);
                        break;

                    default:
                        break;
                }
            }

            prevGesture = currentGesture;
        }
    }*/

    //Perform non-immediate visual effects here
    switch(visualEffect){
        case Cellulo::CelluloBluetoothEnums::VisualEffect::VisualEffectBreathe:

            //Time to change goal
            if(systemMillis() > (effectCounter2 ? LED_BREATHE_HIGH_MILLIS : LED_BREATHE_LOW_MILLIS) + effectCounter1){
                effectCounter1 = systemMillis();
                effectCounter2 = (effectCounter2 + 1) % 2;
                if(effectCounter2)
                    for(i=0; i<6; i++){
                        currentLEDColorGoals[i][0] = effectColor[0];
                        currentLEDColorGoals[i][1] = effectColor[1];
                        currentLEDColorGoals[i][2] = effectColor[2];
                    }
                else
                    for(i=0; i<6; i++){
                        currentLEDColorGoals[i][0] = effectColor[0]/LED_BREATHE_BRIGHTNESS_DIVISOR;
                        currentLEDColorGoals[i][1] = effectColor[1]/LED_BREATHE_BRIGHTNESS_DIVISOR;
                        currentLEDColorGoals[i][2] = effectColor[2]/LED_BREATHE_BRIGHTNESS_DIVISOR;
                    }
                effectTransition = true;
            }

            //Make transition
            if(!updateRequested && effectTransition){
                effectTransition = false;
                for(i=0; i<6; i++)
                    if(!transitionLED(i, currentLEDColorGoals[i][0], currentLEDColorGoals[i][1], currentLEDColorGoals[i][2], LED_TRANSITION_INERTIA_DEFAULT))
                        effectTransition = true;
                if(effectTransition)
                    requestLEDUpdate();
            }
            break;

        case Cellulo::CelluloBluetoothEnums::VisualEffect::VisualEffectConstSingle:
        case Cellulo::CelluloBluetoothEnums::VisualEffect::VisualEffectConstAll:
        case Cellulo::CelluloBluetoothEnums::VisualEffect::VisualEffectProgress:
        case Cellulo::CelluloBluetoothEnums::VisualEffect:: VisualEffectDirection:
            if(!updateRequested && effectTransition){
                effectTransition = false;
                for(i=0; i<6; i++) {
                    bool finishedTransition = transitionLED(i, currentLEDColorGoals[i][0], currentLEDColorGoals[i][1], currentLEDColorGoals[i][2], LED_TRANSITION_INERTIA_DEFAULT);
                    if(!finishedTransition) {
                        effectTransition = true;
                    }
                    else {
                    }
                }
                if(effectTransition)
                    requestLEDUpdate();
            }
            break;

        case Cellulo::CelluloBluetoothEnums::VisualEffect::VisualEffectAlertAll:
            if(!updateRequested){

                //Alert ended and previous colors were restored
                if(effectCounter2 >= currentEffectValue)
                    setVisualEffect(previousVisualEffect, previousEffectColor[0], previousEffectColor[1], previousEffectColor[2], previousEffectValue);

                //Alert going on
                else if(systemMillis() > LED_ALERT_FLASH_MILLIS + effectCounter1){
                    effectCounter1 = systemMillis();
                    effectCounter2++;

                    //Alert ended, restore previous colors
                    if(effectCounter2 >= currentEffectValue){

                        //Special treatment for waiting effect because it looks better with direct transition
                        if(previousVisualEffect == Cellulo::CelluloBluetoothEnums::VisualEffect::VisualEffectWaiting)
                            break;

                        for(i=0; i<6; i++){
                            currentLEDColorGoals[i][0] = previousLEDColorGoals[i][0];
                            currentLEDColorGoals[i][1] = previousLEDColorGoals[i][1];
                            currentLEDColorGoals[i][2] = previousLEDColorGoals[i][2];
                            setLED(i, previousLEDColors[i][0], previousLEDColors[i][1], previousLEDColors[i][2]);
                        }
                        requestLEDUpdate();
                    }

                    //Alert going on, time to toggle
                    else{
                        if(effectCounter2 % 2)
                            for(i=0; i<6; i++)
                                setLED(i, previousLEDColors[i][0], previousLEDColors[i][1], previousLEDColors[i][2]);
                        else
                            for(i=0; i<6; i++)
                                setLED(i, effectColor[0], effectColor[1], effectColor[2]);
                        requestLEDUpdate();
                    }
                }
            }
            break;

        case Cellulo::CelluloBluetoothEnums::VisualEffect::VisualEffectAlertSingle:
            if(!updateRequested){

                //Alert ended and previous colors were restored
                if(effectCounter2 >= currentEffectValue)
                    setVisualEffect(previousVisualEffect, previousEffectColor[0], previousEffectColor[1], previousEffectColor[2], previousEffectValue);

                //Alert going on
                else if(systemMillis() > LED_ALERT_FLASH_MILLIS + effectCounter1){
                    effectCounter1 = systemMillis();
                    effectCounter2++;

                    //Alert ended, restore previous colors
                    if(effectCounter2 >= currentEffectValue){

                        //Special treatment for waiting effect because it looks better with direct transition
                        if(previousVisualEffect == Cellulo::CelluloBluetoothEnums::VisualEffect::VisualEffectWaiting)
                            break;

                        for(i=0; i<6; i++){
                            currentLEDColorGoals[i][0] = previousLEDColorGoals[i][0];
                            currentLEDColorGoals[i][1] = previousLEDColorGoals[i][1];
                            currentLEDColorGoals[i][2] = previousLEDColorGoals[i][2];
                            setLED(i, previousLEDColors[i][0], previousLEDColors[i][1], previousLEDColors[i][2]);
                        }
                        requestLEDUpdate();
                    }

                    //Alert going on, time to toggle
                    else{
                        if(effectCounter2 % 2)
                            setLED(currentLEDNumber, previousLEDColors[currentLEDNumber][0], previousLEDColors[currentLEDNumber][1], previousLEDColors[currentLEDNumber][2]);
                        else
                            setLED(currentLEDNumber, effectColor[0], effectColor[1], effectColor[2]);
                        requestLEDUpdate();
                    }
                }
            }
            break;

        case Cellulo::CelluloBluetoothEnums::VisualEffect::VisualEffectWaiting:
            if(!updateRequested){
                for(i=0; i<effectCounter2; i++)
                    transitionLED(i, 0, 0, 0, LED_TRANSITION_INERTIA_DEFAULT);
                transitionLED(effectCounter2,
                              (LED_WAITING_TURN_SPEED - effectCounter1)*effectColor[0]/LED_WAITING_TURN_SPEED,
                              (LED_WAITING_TURN_SPEED - effectCounter1)*effectColor[1]/LED_WAITING_TURN_SPEED,
                              (LED_WAITING_TURN_SPEED - effectCounter1)*effectColor[2]/LED_WAITING_TURN_SPEED, LED_TRANSITION_INERTIA_DEFAULT);
                transitionLED((effectCounter2 + 1)%6,
                              effectCounter1*effectColor[0]/LED_WAITING_TURN_SPEED,
                              effectCounter1*effectColor[1]/LED_WAITING_TURN_SPEED,
                              effectCounter1*effectColor[2]/LED_WAITING_TURN_SPEED, LED_TRANSITION_INERTIA_DEFAULT);
                for(i=effectCounter2 + 2; i<6; i++)
                    transitionLED(i, 0, 0, 0, LED_TRANSITION_INERTIA_DEFAULT);

                if(effectTransition)
                    requestLEDUpdate();

                effectCounter1++;
                if(effectCounter1 > LED_WAITING_TURN_SPEED){
                    effectCounter1 = 0;
                    effectCounter2++;
                    if(effectCounter2 > 5)
                        effectCounter2 = 0;
                }
            }
            break;

        case Cellulo::CelluloBluetoothEnums::VisualEffect::VisualEffectBlink:
            if(!updateRequested){

                //Time to toggle
                if(systemMillis() > currentEffectValue*LED_BLINK_FLASH_MILLIS_MULTIPLIER + effectCounter1){
                    effectCounter1 = systemMillis();
                    effectCounter2 = (effectCounter2 + 1) % 2;
                    if(effectCounter2)
                        for(i=0; i<6; i++)
                            setLED(i,0,0,0);
                    else
                        for(i=0; i<6; i++)
                            setLED(i, effectColor[0], effectColor[1], effectColor[2]);
                    requestLEDUpdate();
                }
            }
            break;

        case Cellulo::CelluloBluetoothEnums::VisualEffect::VisualEffectPulse:
            if(!updateRequested){

                //Time to toggle if transition is complete
                if(!effectTransition){
                    effectCounter2 = !effectCounter2;

                    if(effectCounter2)
                        for(i=0; i<6; i++){
                            currentLEDColorGoals[i][0] = previousLEDColors[i][0];
                            currentLEDColorGoals[i][1] = previousLEDColors[i][1];
                            currentLEDColorGoals[i][2] = previousLEDColors[i][2];
                        }
                    else
                        for(i=0; i<6; i++){
                            currentLEDColorGoals[i][0] = effectColor[0];
                            currentLEDColorGoals[i][1] = effectColor[1];
                            currentLEDColorGoals[i][2] = effectColor[2];
                        }
                    effectTransition = true;
                }
            }

            //Make slower than usual transition
            if(!updateRequested && effectTransition){
                effectTransition = false;
                for(i=0; i<6; i++)
                    if(!transitionLED(i, currentLEDColorGoals[i][0], currentLEDColorGoals[i][1], currentLEDColorGoals[i][2], LED_TRANSITION_INERTIA_PULSE))
                        effectTransition = true;
                if(effectTransition)
                    requestLEDUpdate();
            }
            break;

        default:
            break;
    }

    if(sleepRequested){

        //Wait until current update finishes
        i = 0;
        while(!latched){
            i++;
            if(i>10000000)
                break;
        }
    }
}

void celluloSimulatedLedsLogic::setLEDResponseMode(LEDResponseMode newMode){
    ledResponseMode = newMode;
}

void celluloSimulatedLedsLogic::setVisualEffect(VisualEffect newEffect, unsigned char red, unsigned char green, unsigned char blue, int value){
    unsigned int i;

   /* if(newEffect == Cellulo::CelluloBluetoothEnums::VisualEffectConstAll) {
        currentLEDColors[0][0] = red;
        currentLEDColors[0][1] = green;
        currentLEDColors[0][2] = blue;
    }*/
    //Set immediate parts of effects here
    switch(newEffect){
        case Cellulo::CelluloBluetoothEnums::VisualEffect::VisualEffectConstSingle:
            currentLEDColorGoals[value][0] = red*4095/255;
            currentLEDColorGoals[value][1] = green*4095/255;
            currentLEDColorGoals[value][2] = blue*4095/255;
            effectTransition = true;
            break;

        case Cellulo::CelluloBluetoothEnums::VisualEffect::VisualEffectConstAll:
            for(i=0; i<6; i++){
                currentLEDColorGoals[i][0] = red*4095/255;
                currentLEDColorGoals[i][1] = green*4095/255;
                currentLEDColorGoals[i][2] = blue*4095/255;
            }
            effectTransition = true;
            break;

        case Cellulo::CelluloBluetoothEnums::VisualEffect::VisualEffectProgress: {
            unsigned int progressAsSumOfColors = value*6;

            //Fully bright LEDs
            i = 0;
            while(progressAsSumOfColors > 255){
                currentLEDColorGoals[i][0] = red*4095/255;
                currentLEDColorGoals[i][1] = green*4095/255;
                currentLEDColorGoals[i][2] = blue*4095/255;
                progressAsSumOfColors -= 255;
                i++;
            }

            //Possibly semi-bright led
            currentLEDColorGoals[i][0] = red*4095/255*progressAsSumOfColors/255;
            currentLEDColorGoals[i][1] = green*4095/255*progressAsSumOfColors/255;
            currentLEDColorGoals[i][2] = blue*4095/255*progressAsSumOfColors/255;

            //Off LEDs
            i++;
            for(; i<6; i++){
                currentLEDColorGoals[i][0] = 0;
                currentLEDColorGoals[i][1] = 0;
                currentLEDColorGoals[i][2] = 0;
            }

            effectTransition = true;
            break;
        }

        case Cellulo::CelluloBluetoothEnums::VisualEffect::VisualEffectDirection: {
            unsigned int ledBefore = value*6/256;      //LED before specified angle
            unsigned int ledAfter = (ledBefore + 1)%6; //LED after specified angle

            //Turn off all LEDs except the ones that are touching the angle
            for(i=(ledAfter + 1)%6; i != ledBefore; i = (i + 1)%6){
                currentLEDColorGoals[i][0] = 0;
                currentLEDColorGoals[i][1] = 0;
                currentLEDColorGoals[i][2] = 0;
            }

            //LED before the angle
            i = (60 - (value*360/256 - ledBefore*60));
            currentLEDColorGoals[ledBefore][0] = red*4095/255*i/60;
            currentLEDColorGoals[ledBefore][1] = green*4095/255*i/60;
            currentLEDColorGoals[ledBefore][2] = blue*4095/255*i/60;

            //LED after the angle
            i = (value*360/256 - ledBefore*60);
            currentLEDColorGoals[ledBefore][0] = red*4095/255*i/60;
            currentLEDColorGoals[ledBefore][1] = green*4095/255*i/60;
            currentLEDColorGoals[ledBefore][2] = blue*4095/255*i/60;

            effectTransition = true;
            break;
        }

        case Cellulo::CelluloBluetoothEnums::VisualEffect:: VisualEffectAlertAll:
            if(visualEffect != Cellulo::CelluloBluetoothEnums::VisualEffect::VisualEffectAlertAll &&
               visualEffect != Cellulo::CelluloBluetoothEnums::VisualEffect::VisualEffectAlertSingle){
                effectCounter1 = systemMillis();
                effectCounter2 = 0;

                previousVisualEffect = visualEffect;
                previousEffectColor[0] = effectColor[0]*255/4095;
                previousEffectColor[1] = effectColor[1]*255/4095;
                previousEffectColor[2] = effectColor[2]*255/4095;
                for(i=0; i<6; i++){
                    previousLEDColors[i][0] = currentLEDColors[i][0];
                    previousLEDColors[i][1] = currentLEDColors[i][1];
                    previousLEDColors[i][2] = currentLEDColors[i][2];
                    previousLEDColorGoals[i][0] = currentLEDColorGoals[i][0];
                    previousLEDColorGoals[i][1] = currentLEDColorGoals[i][1];
                    previousLEDColorGoals[i][2] = currentLEDColorGoals[i][2];
                }
                previousEffectValue = currentEffectValue;

                effectColor[0] = red;
                effectColor[0] = effectColor[0]*4095/255;
                effectColor[1] = green;
                effectColor[1] = effectColor[1]*4095/255;
                effectColor[2] = blue;
                effectColor[2] = effectColor[2]*4095/255;
                visualEffect = newEffect;
                currentEffectValue = value;
                if(currentEffectValue < 1) //Guard against zero
                    currentEffectValue = 1;
                currentEffectValue = currentEffectValue*2 - 1;

                for(i=0; i<6; i++)
                    setLED(i, effectColor[0], effectColor[1], effectColor[2]);
                requestLEDUpdate();
            }
            return;

        case Cellulo::CelluloBluetoothEnums::VisualEffect::VisualEffectAlertSingle:
            if(visualEffect != Cellulo::CelluloBluetoothEnums::VisualEffect::VisualEffectAlertAll &&
               visualEffect != Cellulo::CelluloBluetoothEnums::VisualEffect::VisualEffectAlertSingle){
                effectCounter1 =  systemMillis();
                effectCounter2 = 0;

                previousVisualEffect = visualEffect;
                previousEffectColor[0] = effectColor[0]*255/4095;
                previousEffectColor[1] = effectColor[1]*255/4095;
                previousEffectColor[2] = effectColor[2]*255/4095;
                for(i=0; i<6; i++){
                    previousLEDColors[i][0] = currentLEDColors[i][0];
                    previousLEDColors[i][1] = currentLEDColors[i][1];
                    previousLEDColors[i][2] = currentLEDColors[i][2];
                    previousLEDColorGoals[i][0] = currentLEDColorGoals[i][0];
                    previousLEDColorGoals[i][1] = currentLEDColorGoals[i][1];
                    previousLEDColorGoals[i][2] = currentLEDColorGoals[i][2];
                }
                previousEffectValue = currentEffectValue;

                effectColor[0] = red;
                effectColor[0] = effectColor[0]*4095/255;
                effectColor[1] = green;
                effectColor[1] = effectColor[1]*4095/255;
                effectColor[2] = blue;
                effectColor[2] = effectColor[2]*4095/255;
                visualEffect = newEffect;

                currentEffectValue = value/16; //High nibble
                if(currentEffectValue < 1)     //Guard against zero
                    currentEffectValue = 1;
                currentEffectValue = currentEffectValue*2 - 1;

                currentLEDNumber = value%16; //Low nibble

                setLED(currentLEDNumber, effectColor[0], effectColor[1], effectColor[2]);
                requestLEDUpdate();
            }
            return;

        case Cellulo::CelluloBluetoothEnums::VisualEffect:: VisualEffectWaiting:
            effectTransition = true;
            effectCounter1 = 0;
            effectCounter2 = 0;
            break;

        case Cellulo::CelluloBluetoothEnums::VisualEffect::VisualEffectBlink:
            effectCounter1 = systemMillis();
            effectCounter2 = 0;

            effectColor[0] = red;
            effectColor[0] = effectColor[0]*4095/255;
            effectColor[1] = green;
            effectColor[1] = effectColor[1]*4095/255;
            effectColor[2] = blue;
            effectColor[2] = effectColor[2]*4095/255;
            visualEffect = newEffect;
            if(value <= 0)
                currentEffectValue = LED_BLINK_FLASH_DEFAULT_VALUE;
            else
                currentEffectValue = value;

            for(i=0; i<6; i++)
                setLED(i, effectColor[0], effectColor[1], effectColor[2]);
            requestLEDUpdate();
            return;

        case Cellulo::CelluloBluetoothEnums::VisualEffect::VisualEffectBreathe:
            effectTransition = true;
            effectCounter1 = systemMillis();
            effectCounter2 = 0;

            for(i=0; i<6; i++){
                currentLEDColorGoals[i][0] = red*4095/255/LED_BREATHE_BRIGHTNESS_DIVISOR;
                currentLEDColorGoals[i][1] = green*4095/255/LED_BREATHE_BRIGHTNESS_DIVISOR;
                currentLEDColorGoals[i][2] = blue*4095/255/LED_BREATHE_BRIGHTNESS_DIVISOR;
            }
            break;

        case Cellulo::CelluloBluetoothEnums::VisualEffect::VisualEffectPulse:
            effectCounter2 = 0;

            previousVisualEffect = visualEffect;
            previousEffectColor[0] = effectColor[0]*255/4095;
            previousEffectColor[1] = effectColor[1]*255/4095;
            previousEffectColor[2] = effectColor[2]*255/4095;
            for(i=0; i<6; i++){
                previousLEDColors[i][0] = currentLEDColors[i][0];
                previousLEDColors[i][1] = currentLEDColors[i][1];
                previousLEDColors[i][2] = currentLEDColors[i][2];
                previousLEDColorGoals[i][0] = currentLEDColorGoals[i][0];
                previousLEDColorGoals[i][1] = currentLEDColorGoals[i][1];
                previousLEDColorGoals[i][2] = currentLEDColorGoals[i][2];
            }
            previousEffectValue = currentEffectValue;

            effectColor[0] = red;
            effectColor[0] = effectColor[0]*4095/255;
            effectColor[1] = green;
            effectColor[1] = effectColor[1]*4095/255;
            effectColor[2] = blue;
            effectColor[2] = effectColor[2]*4095/255;
            visualEffect = newEffect;
            currentEffectValue = value;
            if(currentEffectValue < 1) //Guard against zero
                currentEffectValue = 1;
            currentEffectValue = currentEffectValue*2 - 1;

            for(i=0; i<6; i++){
                currentLEDColorGoals[i][0] = effectColor[0];
                currentLEDColorGoals[i][1] = effectColor[1];
                currentLEDColorGoals[i][2] = effectColor[2];
            }
            effectTransition = true;
            return;

        default:
            break;
    }

    effectColor[0] = red;
    effectColor[0] = effectColor[0]*4095/255;
    effectColor[1] = green;
    effectColor[1] = effectColor[1]*4095/255;
    effectColor[2] = blue;
    effectColor[2] = effectColor[2]*4095/255;
    visualEffect = newEffect;
    currentEffectValue = value;
}

void celluloSimulatedLedsLogic::keyTouched(unsigned int key, bool touched){
    if(touched){
        if(ledResponseMode == LEDResponseModeResponsiveIndividual){
            short red = currentLEDColors[key][0] + LED_TOUCH_RESPONSE_EXTRA_BRIGHTNESS;
            short green = currentLEDColors[key][1] + LED_TOUCH_RESPONSE_EXTRA_BRIGHTNESS;
            short blue = currentLEDColors[key][2] + LED_TOUCH_RESPONSE_EXTRA_BRIGHTNESS;

            if(red > 0xFFF && green > 0xFFF && blue > 0xFFF){
                red = currentLEDColors[key][0] - LED_TOUCH_RESPONSE_EXTRA_BRIGHTNESS;
                if(red < 0)
                    red = 0;
                green = currentLEDColors[key][1] - LED_TOUCH_RESPONSE_EXTRA_BRIGHTNESS;
                if(green < 0)
                    green = 0;
                blue = currentLEDColors[key][2] - LED_TOUCH_RESPONSE_EXTRA_BRIGHTNESS;
                if(blue < 0)
                    blue = 0;
            }
            else if(red > 0xFFF)
                red = 0xFFF;
            else if(green > 0xFFF)
                green = 0xFFF;
            else if(blue > 0xFFF)
                blue = 0xFFF;

            //setLEDTemporary(key, red, green, blue);
        }
    }
    else
        /*setLEDTemporary(key,
                        currentLEDColors[key][0],
                        currentLEDColors[key][1],
                        currentLEDColors[key][2]);*/
    requestLEDUpdate();
}

void celluloSimulatedLedsLogic::setLED(unsigned int led, unsigned short red, unsigned short green, unsigned short blue){
   // setLEDTemporary(led, red, green, blue);
    currentLEDColors[led][0] = red;
    currentLEDColors[led][1] = green;
    currentLEDColors[led][2] = blue;
}

inline void celluloSimulatedLedsLogic::requestLEDUpdate(){
    latched = false;
    updateRequested = true;
}

void celluloSimulatedLedsLogic::timer3Handler() {
    if(updateRequested) {
        //now we use the currentLedColors and this is close enough to approximate the leds the real robot
        //we dont need set the registers like the real robot does, so here just set updateRequested to false
        updateRequested = false;
    }
}
