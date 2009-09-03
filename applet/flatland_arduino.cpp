#include <Wire.h>
#include "nunchuck_funcs.h"


#include "WProgram.h"
void setup();
void loop();
void sendRawData();
void sendArea();
void defineAreas();
void findArea();
int loop_cnt=0;

byte accx,accy,zbut,cbut;

float north = 183;
float south = 80;
float east = 80; 
float west = 183;

int numAreas = 9;
float areaSize;
int screenSize = 800;



int areas[9][2];
int activeArea = 0;
int lastArea = 0;

//this is to hold the map result of raw data to the rectified coordinate space
int newPos[2];

boolean firstLoop = true;
void setup()
{
  areaSize = screenSize/3;

  Serial.begin(115200);
  nunchuck_setpowerpins();
  nunchuck_init(); // send the initilization handshake

  defineAreas();
}

void loop()
{
  // every 100 msecs get new data
  if( loop_cnt > 1 ) 
  { 
    loop_cnt = 0;

    nunchuck_get_data();

    accx  = nunchuck_accelx(); // ranges from approx 70 - 182
    accy  = nunchuck_accely(); // ranges from approx 65 - 173
    zbut = nunchuck_zbutton();
    cbut = nunchuck_cbutton(); 


    //figure out what area the acc is in
    newPos[0] = map(accx,east,west,0,800);
    newPos[1] = map(accy,south,north,800,0);


    //send absolute positions
    //sendRawData();

    //send just the area
    findArea();
    if(lastArea != activeArea) sendArea();
    
  }
  loop_cnt++;
  delay(1);

}

void sendRawData()
{
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

void sendArea()
{
  Serial.print((byte)activeArea, DEC);
  Serial.print(" ");
  Serial.println();
}

void defineAreas()
{
  int k = 0;
  for(int y =0; y< screenSize-screenSize/3; y+=screenSize/3)
  {
    for(int x = 0; x < screenSize-screenSize/3; x+=screenSize/3)
    {
      areas[k][0] = x;
      areas[k][1] = y;
      Serial.print(areas[k][0]);
      Serial.print(" ");
      Serial.print(areas[k][1]);
      Serial.println();
      k++;
    }

  }
}

void findArea()
{
  lastArea = activeArea;
  for (int i=0;i<numAreas;i++)
  {
    //find if the rectified position of acc is within an area
    if(newPos[0] < areas[i][0]+areaSize && newPos[1] < areas[i][1] + areaSize)
    {
      activeArea = i;
      break;
    }
  }
}



int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}

