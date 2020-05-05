#ifndef CELLULOSIMULATEDLEDSLOGIC_H
#define CELLULOSIMULATEDLEDSLOGIC_H


#include "../comm/CelluloBluetoothEnums.h"
#include <chrono>
#include <QTimer>


//I dont think we can control brightness in simulator
#define LED_IDLE_BRIGHTNESS 0x600 //
#define LED_TOUCH_RESPONSE_EXTRA_BRIGHTNESS 0x800
#define LED_IDLE_MODE_BRIGHTNESS_DIVISOR 2
#define LED_WAITING_TURN_SPEED 13
#define LED_TRANSITION_INERTIA_DEFAULT 10 //Higher this value, the more time it takes for transitioning
#define LED_ALERT_FLASH_MILLIS 300
#define LED_BLINK_FLASH_DEFAULT_VALUE 15
#define LED_BLINK_FLASH_MILLIS_MULTIPLIER 20
#define LED_BREATHE_BRIGHTNESS_DIVISOR 4
#define LED_BREATHE_LOW_MILLIS 2000
#define LED_BREATHE_HIGH_MILLIS 400
#define LED_TRANSITION_INERTIA_PULSE 25

#define LOW_NIBBLE_MASK 0x000F
#define LOW_BYTE_MASK 0x00FF

#define LED_XLAT_PORT_CHANNEL PORT_CHANNEL_C
#define LED_XLAT_PORT_BIT_POS PORTS_BIT_POS_14

typedef LED_RESPONSE_MODE_ENUM_SHARED LEDResponseMode;
typedef Cellulo::CelluloBluetoothEnums::VisualEffect VisualEffect;


class celluloSimulatedLedsLogic {

public:

    unsigned short currentLEDColors[6][3];                   ///< Current colors of the LEDs: [led number in 0, 1, 2, 3, 4 or 5][red, green or blue in 0, 1 or 2]
    //Gesture prevGesture; //exists in gesture.h(not sure what what this is yet so just removed all gestures features for now)


    celluloSimulatedLedsLogic();
    /**
     * Initializes user interface LED functionality
     */
    void APP_LED_Initialize();

    /**
     * Performs regular user interface LED tasks
     */
    void APP_LED_Tasks();

    /**
     * @brief Suspends LED operation for sleep
     */
    void suspendLEDsSleep();

    /**
     * @brief Suspends LED operation for idle mode
     */
    void suspendLEDsIdle();

    /**
     * @brief Resumes LED operation (after waking up from sleep)
     */
    void resumeLEDsSleep();

    /**
     * @brief Resumes LED operation after idle mode
     */
    void resumeLEDsIdle();

    /**
     * @brief Plays a low battery animation with LEDs and suspends LED functionality off again
     */
    void lowBatteryAnimation();

    /**
     * @brief Sets the new LED response mode
     *
     * @param newMode The new LED response mode
     */
    void setLEDResponseMode(LEDResponseMode newMode);

    /**
     * @brief Sets the new visual effect
     * @param newEffect The new visual effect
     * @param red 0 to 255
     * @param green 0 to 255
     * @param blue 0 to 255
     * @param value A value relevant to the desired effect
     */
    void setVisualEffect(VisualEffect newEffect, unsigned char red, unsigned char green, unsigned char blue, int value);

    /**
     * @brief Makes LED respond to key touch, if currently relevant and allowed
     *
     * @param key 0, 1, 2, 3, 4 or 5
     * @param touched Whether touched or released
     */
    void keyTouched(unsigned int key, bool touched);

    /**
     * @brief Sets the LED brightness, does not get updated immediately
     *
     * @param led 0, 1, 2, 3, 4 or 5
     * @param red Red brightness, 0 to 4095
     * @param green Green brightness, 0 to 4095
     * @param blue Blue brightness, 0 to 4095
     */
    void setLED(unsigned int led, unsigned short red, unsigned short green, unsigned short blue);

    /**
     * @brief Requests update for all LEDs in the next cycle
     */
    void requestLEDUpdate();
public slots:
    void timer3Handler();
private:
    unsigned short currentLEDColorGoals[6][3];               ///< stores goals for leds
    unsigned short previousLEDColorGoals[6][3];              ///< stores prvious goals for leds
    unsigned short previousLEDColors[6][3];                  ///< stores the previous led colors
    LEDResponseMode ledResponseMode;                         ///< led response mode
    unsigned int currentBufferIndex;                         ///< stores bufferindex(however this is useless here it was only necesary in the firmware)
    bool updateRequested;                                    ///< indicates if a update of the led color is requestes
    bool latched;                                            ///
    bool sleepRequested;                                     //exists in power.h(for now just have it alawys set to false)
    VisualEffect visualEffect;                               ///< stores the current visual effect
    VisualEffect previousVisualEffect;                       ///< stores the previous visual effect
    unsigned int effectColor[3];                             ///color for the effect
    unsigned int previousEffectColor[3];                     ///< stores the previouS effect color
    unsigned int previousEffectValue;                        ///< stores value of previous effect
    unsigned int currentEffectValue;                         ///<stores the value for the currentEffect
    unsigned int currentLEDNumber;
    unsigned int effectCounter1, effectCounter2;             ///<used as a counters for the effects
    bool effectTransition;                                   ///<indicates if we currently in an effectTransition

    std::chrono::time_point<std::chrono::system_clock> then; ///<Use as start value of compute clock milliseconds since system turned on

    /**
     * @brief Ensures a smooth transition of led lights
     * @param led
     * @param red
     * @param green
     * @param blue
     * @param inertia
     * @return
     */
    bool transitionLED(unsigned int led, short red, short green, short blue, short inertia);
    /**
     * @brief return time elapsed since start of system in milliseconds
     * @return
     */
    float systemMillis();
};

#endif // CELLULOSIMULATEDLEDSLOGIC_H
