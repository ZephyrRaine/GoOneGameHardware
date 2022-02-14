
// mapping des Input
#define JOY1_X A1 //A0
#define JOY1_Y A0 //A1
#define JOY1_P A6
#define JOY2_X A2
#define JOY2_Y A3
#define JOY2_P A7
#define SFR_R1 A4
#define SFR_R2 A5
#define SFR1 A4 
#define SFR2 A5 
#define HAT_1 0
#define HAT_2 3 //1
#define HAT_3 2
#define HAT_4 1 //3
#define ROND 5 //4
#define TRIANGLE 4 //5
#define CROIX 7 //6
#define CARRE 6 //7
#define BPL1 8
#define BPL2 9
#define SHARE 10
#define OPTION 11
#define MENU 12

#include "IOs.h"
#include "XInput.h"
//#define PRINT_ANALOG 1

const int JoyMax = 32767;  // int16_t max

int led = 13;
Input Joy1p, Joy2p, Hat_1, Hat_2, Hat_3, Hat_4, Rond, Triangle, croix, carre, bpL1, bpL2,Share, Option, Menu; 

//les entrees analogiques
int Joy1X, Joy1Y, Joy2X, Joy2Y, sfr1, sfr2;

void setup() 
{
  Serial.begin(115200);
  pinMode(JOY1_P,INPUT_PULLUP);
  pinMode(JOY2_P,INPUT_PULLUP);
  pinMode(HAT_1,INPUT_PULLUP);
  pinMode(HAT_2,INPUT_PULLUP);
  pinMode(HAT_3,INPUT_PULLUP);
  pinMode(HAT_4,INPUT_PULLUP);
  pinMode(ROND,INPUT_PULLUP);
  pinMode(TRIANGLE,INPUT_PULLUP);
  pinMode(CROIX,INPUT_PULLUP);
  pinMode(CARRE,INPUT_PULLUP);
  pinMode(ROND,INPUT_PULLUP);
  pinMode(BPL1,INPUT_PULLUP);
  pinMode(BPL2,INPUT_PULLUP);
  pinMode(SHARE,INPUT_PULLUP);
  pinMode(OPTION,INPUT_PULLUP);
  pinMode(MENU,INPUT_PULLUP);
  Joy1p = Input();
  Joy2p = Input();
  Hat_1 = Input();
  Hat_2 = Input();
  Hat_3 = Input();
  Hat_4 = Input();
  Rond = Input();
  Triangle = Input();
  croix = Input();
  carre = Input();
  bpL1 = Input();
  bpL2 = Input();
  Share = Input();
  Option= Input();
  Menu = Input();
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  delay(100);
  digitalWrite(led, LOW);
}

//*************************************************************************
// the loop function runs over and over again forever
void loop() 
{
  InputCompute(); 
  
  if(Joy1p.PulseON) XInput.press(BUTTON_L3);
  if(Joy1p.PulseOFF) XInput.release(BUTTON_L3);
  if(Joy2p.PulseON) XInput.press(BUTTON_R3);
  if(Joy2p.PulseOFF) XInput.release(BUTTON_R3);
  
  if(Hat_1.PulseON) XInput.press(DPAD_UP);
  if(Hat_1.PulseOFF) XInput.release(DPAD_UP);
  
  if(Hat_2.PulseON) XInput.press(DPAD_RIGHT);
  if(Hat_2.PulseOFF) XInput.release(DPAD_RIGHT);
  
  if(Hat_3.PulseON) XInput.press(DPAD_DOWN);
  if(Hat_3.PulseOFF) XInput.release(DPAD_DOWN);
  
  if(Hat_4.PulseON) XInput.press(DPAD_LEFT);
  if(Hat_4.PulseOFF) XInput.release(DPAD_LEFT); 
  
  if(Rond.PulseON) XInput.press(BUTTON_B);
  if(Rond.PulseOFF) XInput.release(BUTTON_B);
  if(Triangle.PulseON) XInput.press(BUTTON_Y);
  if(Triangle.PulseOFF) XInput.release(BUTTON_Y);
  if(croix.PulseON) XInput.press(BUTTON_A);
  if(croix.PulseOFF) XInput.release(BUTTON_A);
  if(carre.PulseON) XInput.press(BUTTON_X); 
  if(carre.PulseOFF) XInput.release(BUTTON_X);
  if(bpL1.PulseON) XInput.press(BUTTON_LB);
  if(bpL1.PulseOFF) XInput.release(BUTTON_LB);
  if(bpL2.PulseON) XInput.press(BUTTON_RB);
  if(bpL2.PulseOFF) XInput.release(BUTTON_RB);
  if(Share.PulseON) XInput.press(BUTTON_BACK); 
  if(Share.PulseOFF) XInput.release(BUTTON_BACK); 
  if(Option.PulseON) XInput.press(BUTTON_START);
  if(Option.PulseOFF) XInput.release(BUTTON_START);
  if(Menu.PulseON) XInput.press(BUTTON_LOGO);
  if(Menu.PulseOFF) XInput.release(BUTTON_LOGO); 
  long x = (analogRead(JOY1_X) - 512)*-1;
  long y = (analogRead(JOY1_Y) - 512)*-1;

  float angle = atan2( y, x );                 // in radians, zero is joystick move to right
  float magnitude = sqrt( x*x + y*y);    // Pythagoras
  
  if( magnitude > 512) magnitude = 512;
  
  x = magnitude * cos( angle );
  y = magnitude * sin( angle );
  
  XInput.setJoystickX(JOY_LEFT, map(x, -512, 512, -32767, 32767));
  XInput.setJoystickY(JOY_LEFT, map(y, -512, 512, -32767, 32767));
 
  XInput.setJoystickX(JOY_RIGHT, map(analogRead(JOY2_X), 0, 1023, -32767, 32767));
  XInput.setJoystickY(JOY_RIGHT, map(analogRead(JOY2_Y), 0, 1023, -32767, 32767));
  XInput.setTrigger(TRIGGER_LEFT, map(analogRead(SFR1), 0, 1023, 0, 255));
  XInput.setTrigger(TRIGGER_RIGHT, map(analogRead(SFR2), 0, 1023, 0, 255));
  
  /*
  
  Joy1X=analogRead(JOY1_X); //min=0, centre=512, max=1023
  Joy1Y=analogRead(JOY1_Y); //min=0, centre=512, max=1023
  Joy2X=analogRead(JOY2_X); //min=0, centre=512, max=1023
  Joy2Y=analogRead(JOY2_Y); //min=0, centre=512, max=1023
  sfr1=analogRead(SFR1); //min (relaché)=0, max (pression) =1023
  sfr2=analogRead(SFR2); //min (relaché)=0, max (pression) =1023
  
  */

#ifdef PRINT_ANALOG
  Serial.print(1024);
  Serial.print(" ");
  Serial.print(Joy1X);
  Serial.print(" ");
  Serial.print(Joy1Y);
  Serial.print(" ");
  Serial.print(Joy2X);
  Serial.print(" ");
  Serial.print(Joy2Y);
  Serial.print(" ");
  Serial.print(sfr1);
  Serial.print(" ");
  Serial.print(sfr2);
  Serial.print(" ");
  Serial.println();
#endif

 
  delay(1);
}


void InputCompute()
{
  Joy1p.Compute(!digitalRead(JOY1_P));
  Joy2p.Compute(!digitalRead(JOY2_P));
  bpL1.Compute(!digitalRead(BPL1));
  bpL2.Compute(!digitalRead(BPL2));
  Hat_1.Compute(!digitalRead(HAT_1));
  Hat_2.Compute(!digitalRead(HAT_2));
  Hat_3.Compute(!digitalRead(HAT_3));
  Hat_4.Compute(!digitalRead(HAT_4));
  Rond.Compute(!digitalRead(ROND));
  Triangle.Compute(!digitalRead(TRIANGLE));
  croix.Compute(!digitalRead(CROIX));
  carre.Compute(!digitalRead(CARRE));
  Share.Compute(!digitalRead(SHARE));
  Option.Compute(!digitalRead(OPTION));
  Menu.Compute(!digitalRead(MENU));
}
