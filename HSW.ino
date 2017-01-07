#include "ClickButton.h"
#include "U8glib.h" 
#include <SoftwareSerial.h>

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_FAST); // Dev 0, Fast I2C / TWI

const byte buttonPin1=9; //MenuButton
int buttonPushCounter1 = 0;   // counter for the number of button presses
int buttonState1 = 0;         // current state of the button
int lastButtonState1 = 0;     // previous state of the button

const byte buttonPin2=8; //SelectButton
int buttonPushCounter2 = 0;   // counter for the number of button presses 
int buttonState2 = 0;         // current state of the button
int lastButtonState2 = 0;     // previous state of the button


ClickButton button1(buttonPin1, LOW, CLICKBTN_PULLUP);
ClickButton button2(buttonPin2, LOW, CLICKBTN_PULLUP);

float volt, voltage;

int voltPin1 = A0;

int Vibe = 3;
int BLE = 2;
String inputString="";
String inputString2="";
String inputStringB="";
String inputStringDay="";
String inputStringMonth="";
String inputStringYear="";
char junk;

extern uint8_t bootScreen[];
extern uint8_t TEST01[];
extern uint8_t cellphone[];
extern uint8_t cellphoneICO[];
extern uint8_t message[];
extern uint8_t messageICO[];
extern uint8_t BLEICO[];
extern uint8_t menuItem1[];
extern uint8_t menuItem2[];
extern uint8_t menuItem3[];
extern uint8_t menuItem4[];
int hourTime = 00;
int minTime = 00;
int vibeStat = 0;
int vibeStat2 = 0;

int incommingCall = 0;
int inMessage = 0;
int extraZero = 0;
int extraZeroM = 0;
int extraZeroH = 0;
byte iYear = 16;
byte iMonth = 12;
byte iDay = 31;
byte iWeek = 1;    // 1: SUN, MON, TUE, WED, THU, FRI,SAT
byte iAmPm = 0;    // 0:AM, 1:PM
byte iHour = 23;
byte iMinutes = 59;
byte iSecond = 0;
byte iSecond2 = 0;
String iCall="";
String iMessage="";
String dots = ":";
String stripe = "-";
String iZero = "0";
unsigned long previousMillis = 0; 
const long interval = 1000;  

String hourTimeS = "";
String minTimeS = "";
char TimeC[6];
char TimeC2[4];
char DateC[11];
char callC[12];
char messageC[12];
String TimeB = "";
String TimeB2 = "";
String DateB = "";

byte iMissedCall = 0;
byte iMissedMSG = 0;
byte BLEcon = 0;
byte BLEstat = 1;
byte BOOT = 1;
SoftwareSerial BLEserial(10, 11); // RX, TX

//Menu
int Menu = 0; //Menu active
int selectedItem = 1; //Menu item selected

void drawBOOT(){  
  u8g.drawBitmapP( 0, 0, 16, 64, bootScreen);
  BOOT = 0;
}


void draw(){  
  u8g.drawLine(0, 20, 128, 20);
  u8g.drawLine(70, 0, 70, 20);
}




void setup() {
  
   u8g.firstPage();  
  do {
     drawBOOT();
  } while( u8g.nextPage() );
    delay(3000);
    
  Serial.begin(9600);
BLEserial.begin(9600);
Serial.print("HammerIT | SmartWatch | Firmware v.0.0.1");
pinMode(Vibe, OUTPUT);
pinMode(BLE, OUTPUT);
  
}



  
void loop() {
  if (BLEstat == 1){
   digitalWrite(BLE, HIGH);
  }else{
    digitalWrite(BLE, LOW);
  }
 unsigned long currentMillis = millis();


if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
  updateTime();
}

    if (digitalRead(buttonPin1) == LOW) {
      buttonPushCounter1++;
Serial.println(buttonPushCounter1);
 }

  if (digitalRead(buttonPin2) == LOW) {
      buttonPushCounter2++;
Serial.println(buttonPushCounter2);
 }

 if (buttonPushCounter1 == 1){
 iMissedCall = 0;
 iMissedMSG = 0;
 BLEcon = 0;
 }
 
 if (buttonPushCounter1 > 0){
  if (buttonPushCounter1 == 1){
  buttonPushCounter1=0;
  }
 }

  if (buttonPushCounter2 == 1){
Menu = 1;
 }
 
 if (buttonPushCounter2 > 0){
  if (buttonPushCounter2 == 1){
  buttonPushCounter2=0;
  }
 }

if (Menu == 0){
   if (incommingCall == 0 and inMessage == 0){
 u8g.firstPage();  
  do {
    drawTime();
    draw();
  } while( u8g.nextPage() );
  delay(50);
   }
}

      if (incommingCall == 1){
 u8g.firstPage();  
  do {
    drawCall();
  } while( u8g.nextPage() );
  delay(100);
   }


      if (inMessage == 1){
 u8g.firstPage();  
  do {
    drawMessage();
  } while( u8g.nextPage() );
  delay(100);
   }

    if (Menu == 1){
      
 u8g.firstPage();  
  do {
    drawMenu1();
  } while( u8g.nextPage() );
  delay(100);

   if (digitalRead(buttonPin1) == LOW) {
      buttonPushCounter1++;
Serial.println(buttonPushCounter1);
 }

  if (digitalRead(buttonPin2) == LOW) {
      buttonPushCounter2++;
Serial.println(buttonPushCounter2);
 }

 if (buttonPushCounter1 == 1){
  selectedItem = 1;
  u8g.firstPage();  
  do {
    drawMenu1();
  } while( u8g.nextPage() );
  delay(100);
 }

 if (buttonPushCounter1 == 2){
    selectedItem = 2;
  u8g.firstPage();  
  do {
    drawMenu2();
  } while( u8g.nextPage() );
  delay(100);
 }

 if (buttonPushCounter1 == 3){
    selectedItem = 3;
  u8g.firstPage();  
  do {
    drawMenu3();
  } while( u8g.nextPage() );
  delay(100);
 }

 if (buttonPushCounter1 == 4){
    selectedItem = 4;
  u8g.firstPage();  
  do {
    drawMenu4();
  } while( u8g.nextPage() );
  delay(100);
 }
 
 if (buttonPushCounter1 > 0){
  if (buttonPushCounter1 == 4){
  buttonPushCounter1=0;
  }
 }

  if (buttonPushCounter2 == 1){
  if (selectedItem == 1){
    
  }

  if (selectedItem == 2){
    
  }

  if (selectedItem == 3){
    
  }

  if (selectedItem == 4){
    Menu = 0;
  }
 }
 
 if (buttonPushCounter2 > 0){
  if (buttonPushCounter2 == 1){
  buttonPushCounter2=0;
  }
 }

 
   }


if(Serial.available()){
  while(Serial.available())
    {
      char inChar = (char)Serial.read(); //read the input
      inputString += inChar;        //make a string of the characters coming on serial
    }
    Serial.println(inputString);
    while (Serial.available() > 0)  
    { junk = Serial.read() ; }      // clear the serial buffer


if (inputString ==  "VibeON"){
    digitalWrite(Vibe, HIGH);
    Serial.print("OK | Vibe ON");
    vibeStat = 1;
  }

  if (inputString == "VibeOFF"){
    digitalWrite(Vibe, LOW);
     Serial.print("OK | Vibe OFF");
     vibeStat = 0;
  }

  if (inputString.startsWith("Time:")){
    inputString.remove(0,5);
    inputString.remove(2,1);
    inputStringB = inputString;
    inputStringB.remove(2,2);
    Serial.print(inputStringB);
    inputString.remove(0,2);
    Serial.print(inputString);
    iHour = inputStringB.substring(0, 2).toInt();
    iMinutes = inputString.substring(0, 2).toInt();
    Serial.print(iHour + dots + iMinutes);
  }


  if (inputString.startsWith("Date:")){
    inputString.remove(0,5);
    inputString.remove(2,1);
    inputStringDay = inputString;
    inputStringDay.remove(2,5);
    Serial.print(inputStringDay);
    inputString.remove(0,2);
    inputStringMonth = inputString;
    inputStringMonth.remove(2,3);
    Serial.print(inputStringMonth);
    inputString.remove(0,3);
    inputStringYear = inputString;
    Serial.print(inputStringYear);
    iDay = inputStringDay.substring(0, 2).toInt();
    iMonth = inputStringMonth.substring(0, 2).toInt();
    iYear = inputStringYear.substring(0, 2).toInt();
        Serial.print(iDay + stripe + iMonth + stripe + iYear);
  }

  if (inputString.startsWith("Call:")){
          iSecond2 = 0;
    incommingCall = 1;
    inputString.remove(0,5);
    Serial.print(inputString);
    iCall = iZero + inputString.substring(0, 12).toInt();
    Serial.print(iCall);
    delay(50);
  }

  if (inputString.startsWith("GetVolt")){
       volt= analogRead(voltPin1);
  String voltage = String(volt* (3.7 * 11 / 1023) * 10 );
  String accu = String(volt* (3.7 * 11 / 1023) / 3.7 * 100);
    Serial.println(voltage);
    Serial.println(accu + "%");
    
  }


if (inputString.startsWith("MSG:")){
      iSecond2 = 0;
    inMessage = 1;
    Serial.print(inputString);
    inputString.remove(0,4);
    iMessage = inputString;
    Serial.print(iMessage);
  }
  
inputString = "";
 }

 if(BLEserial.available()){
  while(BLEserial.available())
    {
      char inChar = (char)BLEserial.read(); //read the input
      inputString2 += inChar;        //make a string of the characters coming on serial
    }
    BLEserial.println(inputString2);
    while (BLEserial.available() > 0)  
    { junk = BLEserial.read() ; }      // clear the serial buffer


if (inputString2 ==  "VibeON"){
    digitalWrite(Vibe, HIGH);
    Serial.print("OK | Vibe ON");
    vibeStat = 1;
  }

  if (inputString2 == "VibeOFF"){
    digitalWrite(Vibe, LOW);
     BLEserial.print("OK | Vibe OFF");
     vibeStat = 0;
  }

  if (inputString2.startsWith("Time:")){
    inputString2.remove(0,5);
    inputString2.remove(2,1);
    inputStringB = inputString2;
    inputStringB.remove(2,2);
    inputString2.remove(0,2);
    iHour = inputStringB.substring(0, 2).toInt();
    iMinutes = inputString2.substring(0, 2).toInt();
    Serial.print(iHour + dots + iMinutes);
  }


  if (inputString2.startsWith("Date:")){
    inputString2.remove(0,5);
    inputString2.remove(2,1);
    inputStringDay = inputString2;
    inputStringDay.remove(2,5);
    inputString2.remove(0,2);
    inputStringMonth = inputString2;
    inputStringMonth.remove(2,3);
    inputString2.remove(0,3);
    inputStringYear = inputString2;
    iDay = inputStringDay.substring(0, 2).toInt();
    iMonth = inputStringMonth.substring(0, 2).toInt();
    iYear = inputStringYear.substring(0, 2).toInt();
    Serial.print(iDay + stripe + iMonth + stripe + iYear);
  }

   if (inputString2.startsWith("Call:")){
    iSecond2 = 0;
    incommingCall = 1;
    Serial.print(inputString2);
    inputString2.remove(0,8);
    iCall = iZero + inputString2.substring(0, 12).toInt();
    Serial.print(iCall);
  }

  if (inputString2.startsWith("MSG:")){
    iSecond2 = 0;
    inMessage = 1;
    Serial.print(inputString2);
    inputString2.remove(0,4);
    iMessage = inputString2;
    Serial.print(iMessage);
  }

  if (inputString2.startsWith("BLE")){
    BLEcon = 1;
  }

inputString2 = "";
 }


 if (extraZero == 1){
   String Time2 = String(dots + iZero + iSecond);
    TimeB2 = Time2;
 }
 else{
   String Time2 = String(dots + iSecond);
    TimeB2 = Time2;
 }


if (extraZeroH == 1 and extraZeroM == 1){
 String Time = String(iZero +iHour + dots + iZero + iMinutes);
     TimeB = Time;
}
else if (extraZeroH == 1 and extraZeroM == 0){
 String Time = String(iZero + iHour + dots + iMinutes);
     TimeB = Time;
}
else if (extraZeroH == 0 and extraZeroM == 1){
 String Time = String(iHour + dots + iZero + iMinutes);
     TimeB = Time;
 }
else if (extraZeroH == 0 and extraZeroM == 0){
 String Time = String(iHour +  dots +  iMinutes);
     TimeB = Time;
} 



 String Date = String(iDay + stripe + iMonth + stripe + iYear);
 DateB = Date;
 
}

void updateTime(){
   if(iSecond >= 0) {
      iSecond++; 
      iSecond2++;       
      if(iSecond >= 60) {
        iSecond = 0;
        iMinutes++;
      if(iMinutes >= 60) {
        iMinutes = 0;
        iHour++;  
        if(iHour >= 23) {
          iHour = 0;
          iDay++;
            if(iDay >= 31){
              iDay = 1;
            iMonth++;
            if(iMonth >= 12){ 
              iMonth = 1;
              iYear++;
          }
        }
      }
   }
}
   }

 


if(iSecond <= 9) {
        extraZero = 1; 
}
else{
  extraZero = 0; 
}

 if(iMinutes <= 9) {
        extraZeroM = 1;    
 }
else{
  extraZeroM = 0; 
}
 if(iHour <= 9) {
        extraZeroH = 1;  
 }
 else{
  extraZeroH = 0; 
}

if(iSecond2 >= 15) {
        incommingCall = 0;
        inMessage = 0;
        vibeStat2 = 0;
}

if(iSecond2 >= 5) {
        vibeStat2 = 1;
}
}



void drawTime(){
TimeB.toCharArray(TimeC, 6);
TimeB2.toCharArray(TimeC2, 4);
DateB.toCharArray(DateC, 11);
if (iMissedCall == 1){
      u8g.drawBitmapP(0, 0, 16, 64, cellphoneICO);
}

if (iMissedMSG == 1){
      u8g.drawBitmapP(0, 0, 16, 64, messageICO);
}

if (BLEcon == 1){
      u8g.drawBitmapP(0, 0, 16, 64, BLEICO);
}
    u8g.setFont(u8g_font_freedoomr25n);
    u8g.drawStr(7, 55, TimeC);
     u8g.setFont(u8g_font_freedoomr10r);
     u8g.drawStr(95, 55, TimeC2);
     u8g.drawStr(7, 15, DateC);
}

void drawCall(){
  u8g.drawBitmapP(0, 0, 16, 64, cellphone);
  u8g.drawFrame(5,5,121,50);
  iCall.toCharArray(callC, 12);
    u8g.setFont(u8g_font_freedoomr10r);
    u8g.drawStr(10, 25, "TELEFOON");
     u8g.setFont(u8g_font_freedoomr10r);
     u8g.drawStr(10, 50, callC);
       if (vibeStat2 == 1){
        vibeEngine();
       }
     iMissedCall = 0;
     iMissedCall++;  
}


void drawMessage(){
  u8g.drawBitmapP(0, 0, 16, 64, message);
  u8g.drawFrame(5,5,121,50);
  iMessage.toCharArray(messageC, 12);
    u8g.setFont(u8g_font_freedoomr10r);
    u8g.drawStr(10, 25, "BERICHT");
     u8g.setFont(u8g_font_freedoomr10r);
     u8g.drawStr(10, 50, messageC);
     if (vibeStat2 == 1){
        vibeEngine();
       }
     iMissedMSG = 0;
     iMissedMSG++;  
     
}

void vibeEngine(){
  digitalWrite(Vibe, HIGH);
  delay(500);
  digitalWrite(Vibe, LOW);
    digitalWrite(Vibe, LOW);
}

void drawMenu1(){
u8g.drawBitmapP(0, 0, 16, 64, menuItem1);
}
void drawMenu2(){
u8g.drawBitmapP(0, 0, 16, 64, menuItem2);
}
void drawMenu3(){
u8g.drawBitmapP(0, 0, 16, 64, menuItem3);
}
void drawMenu4(){
u8g.drawBitmapP(0, 0, 16, 64, menuItem4);
}
