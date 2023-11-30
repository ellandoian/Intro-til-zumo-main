#include <Wire.h>
#include <Zumo32U4.h>
Zumo32U4LineSensors lineSensors;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4IMU imu;
Zumo32U4OLED display;
#include "TurnSensor.h"


void turn90(int x)//x er antal rotasjoner,
{
    int i = 1;
    while (i <= x) // ekke helt sikker på hvofor denne  er nødvendig, men funker ikke uten
    {
        motors.setSpeeds(-100, 100);
        while ((int32_t)turnAngle < (turnAngle1 * (87))) // stopper her helt til den har truffet 90*, det virker som hva som hva som er 90 endres fra dag til dag
        {
            turnSensorUpdate();
        }
        turnSensorReset(); // reseter gyroskop dataen
        motors.setSpeeds(0, 0);
        i++;
    }
}

void lineCalibrate(){
    turn90(4);
    lineSensors.calibrate();
}

void setup()
{
    turnSensorSetup();
    lineCalibrate();
}

void loop()
{
    turn90(4);
    delay(500);
}