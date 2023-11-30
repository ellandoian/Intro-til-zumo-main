#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4OLED display;
Zumo32U4IMU imu;

#include "TurnSensor.h"

int circleMillis, zigzagMillis;

void turn90b()
{
    motors.setSpeeds(-100, 100);
    while ((int32_t)turnAngle < (turnAngle1 * 88))
    {
        turnSensorUpdate();
    }
    turnSensorReset();
    motors.setSpeeds(0, 0);
    delay(500);
}

void gyroCal(){
    turnSensorSetup();
}

void turn90(int x)
{
    int i = 1;
    while (i <= x)//ekke helt sikker på hvofor denne  er nødvendig, men funker ikke uten
    {
        motors.setSpeeds(-100, 100); 
        while ((int32_t)turnAngle < (turnAngle1 * 88)) //stopper her helt til den har truffet 90*, det virker som hva som hva som er 90 endres fra dag til dag
        {
            turnSensorUpdate(); 
        }
        turnSensorReset(); //reseter gyroskop dataen
        motors.setSpeeds(0, 0);
        i++;
    }
}

void square()
{
    unsigned long time = millis();
    for (int i = 0; i <= 4; i)  //vil kjøre frem i, 2,5 sekunder, rotere 90*, dette repeteres fire ganger slik at bilen vil kjøre i en firkant
    {
        motors.setSpeeds(150, 150);
        if ((millis() - 2500) > time)
        {
            motors.setSpeeds(0, 0);
            delay(100);
            turn90(1);
            time = millis();
            i++;
        }
    }
}

void circle()
{
    motors.setSpeeds(200, 100);
    if (millis() - circleMillis >= 5000)
    {
        motors.setSpeeds(0, 0);
        buttonA.waitForButton();
        circleMillis = millis(); // last 2 lines can be replaced with break in a switch case
    }
}

void zigzag()
{
    if (millis() - zigzagMillis >= 2300)
    {
        motors.setSpeeds(100, 200);
    }
    else
        motors.setSpeeds(200, 100);

    if (millis() - zigzagMillis >= 4600)
    {
        zigzagMillis = millis();
        motors.setSpeeds(200, 100);
    }
}

void setup()
{
    buttonB.waitForButton();
    zigzagMillis = millis();
    turnSensorSetup();
}

void loop()
{
square();
}