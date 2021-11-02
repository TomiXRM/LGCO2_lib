/***************************************************************************
   This is a library for the LGCO2 module (MH-Z19 CO2 sensor)

   tomix reqport blog
   If you have any question, visit my twitter and giveme DM
   ------> https://twitter.com/tomixrm/

   These sensors use I2C to communicate, 2 pins are required to interface.

   Written by tomixrm for e-Kagaku.

   MIT license, all text above must be included in any redistribution
***************************************************************************/
#include <LGCO2.h>
#include <Wire.h>

LGCO2::LGCO2(){
}

/* initializer */
void LGCO2::init(){
        Wire.begin();
        delay(500);
}

void LGCO2::getValue(){
        Wire.requestFrom(8, 3);// request 1 bytes from Slave ID #8
        while (Wire.available()) {
                sensorStatus = Wire.read();
                uint8_t MSB = Wire.read();
                uint8_t LSB = Wire.read();
                CO2 = sensorStatus == 'B' || sensorStatus == 'C' ? 0 : (MSB << 8) | LSB;
                #ifdef _DEBUG_CO2_
                Serial.print("status:");
                switch (sensorStatus) {//センサーの状態
                case 'A'://センサーは使用可能です
                        Serial.print(F("usable")); break;
                case 'B'://センサーは起動中です。1分お待ちください
                        Serial.print(F("waiting...")); break;
                case 'E'://センサーにエラーあり。接続確認とセンサーが壊れていないか確認してください。
                        Serial.print(F("comunication error")); break;
                default:
                        break;
                }
                Serial.print(F(" CO2:"));
                Serial.println(CO2);
                #endif
        }
}

bool LGCO2::available(){
        return sensorStatus == 'A' ? true : false;
}

char LGCO2::getStatus(){
        return sensorStatus;
}

int LGCO2::read(){
        /********************************************************
           return == 0 → CO2センサが起動中　もしくはエラー
           return != 0 → 正常運転中。二酸化炭素濃度が取得できます。
        ********************************************************/
        getValue();
        return CO2;
}

__attribute__((always_inline)) LGCO2::operator int(){
        return read();
}