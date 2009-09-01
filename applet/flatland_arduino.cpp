#include <Wire.h>
#include "nunchuck_funcs.h"


#include "WProgram.h"
void setup();
void loop();
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
        Serial.println((byte)cbut,DEC);
        Serial.print(" ");
        Serial.println();
    }
    loop_cnt++;
    delay(1);
}


int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}

