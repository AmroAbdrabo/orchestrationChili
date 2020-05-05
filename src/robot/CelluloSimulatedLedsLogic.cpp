#include "CelluloSimulatedLedsLogic.h"

//gesture features are not implemented
//

//#include <xc.h>
//#include <sys/attribs.h>
//#include "system_definitions.h"
//#include "power.h"
//#include "gesture.h"

#include <chrono>
#include <QDebug>
#include <time.h>
#include "../util/system/CelluloSystemUtil.h"

LEDObject leds;
unsigned int currentBufferIndex;
bool updateRequested;
bool latched;

unsigned short currentLEDColorGoals[6][3];
unsigned short previousLEDColorGoals[6][3];
unsigned short previousLEDColors[6][3];
LEDResponseMode ledResponseMode;

VisualEffect visualEffect;
VisualEffect previousVisualEffect;
unsigned int effectColor[3];
unsigned int previousEffectColor[3];
unsigned int previousEffectValue;
unsigned int currentEffectValue;
unsigned int currentLEDNumber;
unsigned int effectCounter1, effectCounter2;
bool effectTransition;



//Gesture prevGesture; //exists in gesture.h(not sure what what this is yet so just removed all gestures features for now)
//TODO REMOVE ME
//float systemMillis = 0;
// systeMillis was replace using chrono exists in timer.h (we will use C++ timers insteads)
bool sleepRequested; //exists in power.h(for now just have it alawys set to false)
std::chrono::time_point<std::chrono::system_clock> then;

celluloSimulatedLedsLogic::celluloSimulatedLedsLogic() {
    timer3 = new QTimer(this);
    //connect(timer3, SIGNAL(timeout()), this, SLOT(APP_LED_Tasks()));
    then = std::chrono::system_clock::now(); //get current chrono timer for systemMillis

    connect(timer3, SIGNAL(timeout()), this, SLOT(timer3Handler()));
    timer3->start(100);
    updateRequested = false;
    APP_LED_Initialize();
}

inline float systemMillis() {
    auto now = std::chrono::system_clock::now();
    auto dur = now-then;
    auto secs = std::chrono::duration_cast<std::chrono::milliseconds>(dur);
    float fSec = secs.count();
    return fSec;
}

inline void setLED0(unsigned short red, unsigned short green, unsigned short blue){
    leds.leds.led0red = red;
    leds.leds.led0green = green;
    leds.leds.led0blue_high_nibble = blue >> 8;
    leds.leds.led0blue_low_byte = blue & LOW_BYTE_MASK;
}

inline void setLED1(unsigned short red, unsigned short green, unsigned short blue){
    leds.leds.led1red = red;
    leds.leds.led1green = green;
    leds.leds.led1blue_low_nibble = blue & LOW_NIBBLE_MASK;
    leds.leds.led1blue_high_byte = blue >> 4;
}

inline void setLED2(unsigned short red, unsigned short green, unsigned short blue){
    leds.leds.led2red = red;
    leds.leds.led2green = green;
    leds.leds.led2blue = blue;
}

inline void setLED3(unsigned short red, unsigned short green, unsigned short blue){
    leds.leds.led3red = red;
    leds.leds.led3green_low_byte = green & LOW_BYTE_MASK;
    leds.leds.led3green_high_nibble = green >> 8;
    leds.leds.led3blue = blue;
}

inline void setLED4(unsigned short red, unsigned short green, unsigned short blue){
    leds.leds.led4red = red;
    leds.leds.led4green_high_byte = green >> 4;
    leds.leds.led4green_low_nibble = green & LOW_NIBBLE_MASK;
    leds.leds.led4blue = blue;
}

inline void setLED5(unsigned short red, unsigned short green, unsigned short blue){
    leds.leds.led5red = red;
    leds.leds.led5green = green;
    leds.leds.led5blue = blue;
}

void setLEDTemporary(unsigned int led, unsigned short red, unsigned short green, unsigned short blue){
    if(red > 4095)
        red = 4095;
    if(green > 4095)
        green = 4095;
    if(blue > 4095)
        blue = 4095;

    switch(led){
        case 0:
            setLED0(red,green,blue);
            break;
        case 1:
            setLED1(red,green,blue);
            break;
        case 2:
            setLED2(red,green,blue);
            break;
        case 3:
            setLED3(red,green,blue);
            break;
        case 4:
            setLED4(red,green,blue);
            break;
        case 5:
            setLED5(red,green,blue);
            break;
        default:
            break;
    }
}


void celluloSimulatedLedsLogic::APP_LED_Initialize(){
    ledResponseMode = LEDResponseModeResponsiveIndividual;
    qDebug() << "app_led_init";
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
            setLEDTemporary(i,currentLEDColors[i][0],currentLEDColors[i][1],currentLEDColors[i][2]);
        }
        effectColor[0] = LED_IDLE_BRIGHTNESS;
        effectColor[1] = LED_IDLE_BRIGHTNESS;
        effectColor[2] = LED_IDLE_BRIGHTNESS;
        visualEffect = Cellulo::CelluloBluetoothEnums::VisualEffectConstAll;
        currentEffectValue = 0;
   // }


    //Timer 3 will take care of regular LED data sending
    /*T3CON = 0;
    T3CONbits.TCS = 0;       //Use peripheral bus clock 3 (100MHz)
    T3CONbits.TCKPS = 0b110; //1:64 prescaler
    PR3 = 15625;             //100Hz update

    SYS_INT_VectorPrioritySet(INT_VECTOR_T3, INT_PRIORITY_LEVEL1);
    SYS_INT_VectorSubprioritySet(INT_VECTOR_T3, INT_SUBPRIORITY_LEVEL1);
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_TIMER_3);
    SYS_INT_SourceEnable(INT_SOURCE_TIMER_3);

    T3CONbits.ON = 1;*/

    //Timer 4 will take care of LED latch delay
    /*T4CON = 0;
    T4CONbits.TCS = 0;       //Use peripheral bus clock 3 (100MHz)
    T4CONbits.TCKPS = 0b000; //1:1 prescaler

    SYS_INT_VectorPrioritySet(INT_VECTOR_T4, INT_PRIORITY_LEVEL1);
    SYS_INT_VectorSubprioritySet(INT_VECTOR_T4, INT_SUBPRIORITY_LEVEL2);
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_TIMER_4);
    SYS_INT_SourceEnable(INT_SOURCE_TIMER_4);*/
}

bool celluloSimulatedLedsLogic::transitionLED(unsigned int led, short red, short green, short blue, short inertia){
    //Return whether transition finished
    if(
        (currentLEDColors[led][0] <= red && currentLEDColors[led][0] >= red - inertia) &&
        (currentLEDColors[led][1] <= green && currentLEDColors[led][1] >= green - inertia) &&
        (currentLEDColors[led][2] <= blue && currentLEDColors[led][2] >= blue - inertia)) {
        qDebug() << "transition finished: final state" << led << " is " << currentLEDColors[led][0];
        return true;
    }
    currentLEDColors[led][0] = (inertia*currentLEDColors[led][0] + red)/(inertia + 1);
    currentLEDColors[led][1] = (inertia*currentLEDColors[led][1] + green)/(inertia + 1);
    currentLEDColors[led][2] = (inertia*currentLEDColors[led][2] + blue)/(inertia + 1);
    setLEDTemporary(led, currentLEDColors[led][0], currentLEDColors[led][1], currentLEDColors[led][2]);
    return false;
}

void celluloSimulatedLedsLogic::suspendLEDsSleep(){
    //T3CONbits.ON = 0;
}

void celluloSimulatedLedsLogic::suspendLEDsIdle(){
    unsigned int i;
    for(i=0; i<6; i++)
        setLEDTemporary(i,
                        currentLEDColors[i][0]/LED_IDLE_MODE_BRIGHTNESS_DIVISOR,
                        currentLEDColors[i][1]/LED_IDLE_MODE_BRIGHTNESS_DIVISOR,
                        currentLEDColors[i][2]/LED_IDLE_MODE_BRIGHTNESS_DIVISOR);
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
    /*T3CON = 0;
    T3CONbits.TCS = 0;       //Use peripheral bus clock 3 (100MHz)
    T3CONbits.TCKPS = 0b110; //1:64 prescaler
    PR3 = 15625;             //100Hz update
    T3CONbits.ON = 1;*/

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
    /*T3CON = 0;
    T3CONbits.TCS = 0;       //Use peripheral bus clock 3 (100MHz)
    T3CONbits.TCKPS = 0b110; //1:64 prescaler
    PR3 = 15625;             //100Hz update
    T3CONbits.ON = 1;*/

    //Restore brightness
    unsigned int i;
    for(i=0; i<6; i++)
        setLEDTemporary(i,
                        currentLEDColors[i][0],
                        currentLEDColors[i][1],
                        currentLEDColors[i][2]);
    requestLEDUpdate();
}

void celluloSimulatedLedsLogic::lowBatteryAnimation(){
   /* T3CON = 0;
    T3CONbits.TCS = 0;       //Use peripheral bus clock 3 (100MHz)
    T3CONbits.TCKPS = 0b110; //1:64 prescaler
    PR3 = 15625;             //100Hz update
    T3CONbits.ON = 1;*/

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
                     qDebug() << "BEOFRE ENTERING TRANSITION CODE:: " << currentLEDColors[i][0];
                    bool finishedTransition = transitionLED(i, currentLEDColorGoals[i][0], currentLEDColorGoals[i][1], currentLEDColorGoals[i][2], LED_TRANSITION_INERTIA_DEFAULT);
                    if(!finishedTransition) {
                        effectTransition = true;
                        qDebug() << "EXITED RUNNING TRANSITION STATE red:: " << currentLEDColors[i][0];
                    }
                    else {
                       qDebug() << "EXITED FINISHED TRANSITION STATE red:: " << currentLEDColors[i][0];
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

/*inline void latchLEDData(){
    PLIB_PORTS_PinSet(PORTS_ID_0, LED_XLAT_PORT_CHANNEL, LED_XLAT_PORT_BIT_POS);
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); //Wait 30ns
    PLIB_PORTS_PinClear(PORTS_ID_0, LED_XLAT_PORT_CHANNEL, LED_XLAT_PORT_BIT_POS);
    latched = true;
}

inline void loadLatchTimer(){

    //We wait 40 microseconds: 32 bits take ~32 microseconds to travel to the
    //LED driver on a 1Mhz clock, we add some room for error
    PR4 = 4000;
    T4CONbits.ON = 1;
}*/

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

            setLEDTemporary(key, red, green, blue);
        }
    }
    else
        setLEDTemporary(key,
                        currentLEDColors[key][0],
                        currentLEDColors[key][1],
                        currentLEDColors[key][2]);
    requestLEDUpdate();
}

void celluloSimulatedLedsLogic::setLED(unsigned int led, unsigned short red, unsigned short green, unsigned short blue){
    setLEDTemporary(led, red, green, blue);
    qDebug() << "IN SET LED";
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
        //maybe need actualyCurrentLeds array and we update them here!
        updateRequested = false;
    }
}

/*void __ISR(_TIMER_3_VECTOR, ipl1AUTO) _Timer3Handler(void){
    if(updateRequested){
        currentBufferIndex = 0;
        SPI1BUF = leds.buffer[currentBufferIndex];
        currentBufferIndex++;
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_SPI_1_TRANSMIT);
        SYS_INT_SourceEnable(INT_SOURCE_SPI_1_TRANSMIT);
        updateRequested = false;
    }

    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_TIMER_3);
}

void __ISR(_SPI1_TX_VECTOR, ipl2AUTO) _IntHandlerSPITxInstance0(void){
    SPI1BUF = leds.buffer[currentBufferIndex];
    currentBufferIndex++;
    if(currentBufferIndex == 7){
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_SPI_1_TRANSMIT);
        SYS_INT_SourceDisable(INT_SOURCE_SPI_1_TRANSMIT);

        loadLatchTimer();
    }
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_SPI_1_TRANSMIT);
}

void __ISR(_TIMER_4_VECTOR, ipl1AUTO) _Timer4Handler(void){
    T4CONbits.ON = 0;
    latchLEDData();

    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_TIMER_4);
}
*/
