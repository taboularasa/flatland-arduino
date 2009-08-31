#include <Wire.h>
#include "nunchuck_funcs.h"


int loop_cnt=0;

byte accx,accy,zbut,cbut;
int ledPin = 13;


void setup()
{
    Serial.begin(115200);
    nunchuck_setpowerpins();
    nunchuck_init(); // send the initilization handshake
}

void loop()
{
    if( loop_cnt > 100 ) { // every 100 msecs get new data
        loop_cnt = 0;

        nunchuck_get_data();

        accx  = nunchuck_accelx(); // ranges from approx 70 - 182
        accy  = nunchuck_accely(); // ranges from approx 65 - 173
        zbut = nunchuck_zbutton();
        cbut = nunchuck_cbutton(); 
        
        Serial.print((byte)accx,DEC);
        Serial.print(" ");
        Serial.print((byte)accy,DEC);
        Serial.print(" ");
        Serial.print((byte)zbut,DEC);
        Serial.print(" ");
        //Serial.print("\tcbut: "); 
        //Serial.println((byte)cbut,DEC);
        Serial.println();
    }
    loop_cnt++;
    delay(1);
}

