#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "GyverEncoder.h"


#define CLK 3
#define DT 5
#define SW 6

#define LCD_CLEAR 1000
//#define TURNOVER_LITER 4
#define MOTOR_LEFT 9
#define MOTOR_RIGHT 10
#define BRIGHTNESS 11

uint32_t time_clear;
uint32_t time_speed_reduction;
uint32_t lastflash;
volatile uint16_t RPM;
volatile uint32_t counter;
bool change_direction_left = false;
bool change_direction_right = false;


struct {
  uint8_t turnover_liter = 4;
  uint8_t speed = 30;
  uint16_t total_rev = 500;
  uint8_t reverse = 0;
  uint16_t time_revers = 5000;
} settings;


enum { SETTINGS1,
       SETTINGS2,
       SETTINGS3,
       START,
       STOP,
       EXPECTATION
} state;


enum { BREAK,
       LEFT,
       RIGHT,
       REVERS
} motor_state;


LiquidCrystal_I2C lcd(0x27, 16, 2);  
Encoder enc1(CLK, DT, SW);

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(5);
  //mySerial.begin(9600);

  attachInterrupt(0, sens, RISING);  //подключить прерывание на 2 пин при повышении сигнала
  attachInterrupt(1, rotate, CHANGE);
  enc1.setType(TYPE2);  // тип энкодера TYPE1 одношаговый, TYPE2 двухшаговый
  enc1.setFastTimeout(100);

  lcd.init();  // initialize the lcd
  analogWrite(11, 100);
  pinMode(SW, INPUT);
  lcd.backlight();
  lcd.setCursor(2, 0);
  lcd.print("TEST BETAR");
  delay(1000);
  lcd.clear();
  state = SETTINGS1;
  

}  // setup

/* Обработка прерываний  */
void sens() {
  RPM = 60 / ((float)(micros() - lastflash) / 1000000);  //расчет
  lastflash = micros();                                  //запомнить время последнего оборота
  counter++;
}  //sens

void rotate() {
  enc1.tick();
}  //rotate


void loop() {
  //Serial.println(counter);
  //Serial.println(RPM);
  //Serial.println(settings.total_rev);

  enc1.tick();
  logics();
  autos();
  motor_direction();
  serial();

}  // loop
