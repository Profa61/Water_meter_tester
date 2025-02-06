#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "GyverEncoder.h"
// #include "Parser.h"       // библиотека парсера
// #include "AsyncStream.h"  // асинхронное чтение сериал
// AsyncStream<50> serial(&Serial, ';');   // указываем обработчик и стоп символ
//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(12, 11); // RX, TX

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































// if ((micros() - lastflash) > 2000000) {  //если сигнала нет больше секунды
//   RPM = 0;
// }

// if (!digitalRead(SW)) {

//   lcd.clear();
//   delay(250);
//   if (state == SETTINGS1) {
//     state = SETTINGS2;
//     return;
//   }
//   if (state == EXPECTATION) {
//     state = SETTINGS1;
//     return;
//   }
//   if (state == START) {
//     state = STOP;
//     return;
//   }
//   if (state == SETTINGS2) {
//     state = START;
//     return;
//   }

//   //Serial.println(state);
// }
// switch (state) {
//   case SETTINGS1:
//     if (enc1.isRight()) speed += 1;
//     if (enc1.isLeft()) speed -= 1;
//     lcd.setCursor(4, 0);
//     lcd.print("Speed:");
//     lcd.setCursor(6, 1);
//     lcd.print(speed);
//     break;

//   case SETTINGS2:
//     //enc1.tick();
//     if (enc1.isRight()) total_rev += 500;
//     if (enc1.isLeft()) total_rev -= 500;
//     lcd.setCursor(4, 0);
//     lcd.print("Liters:");
//     lcd.setCursor(5, 1);
//     lcd.print(total_rev);
//     break;

//   case START:
//     if (enc1.isRight()) speed += 1;
//     if (enc1.isLeft()) speed -= 1;
//     lcd.setCursor(4, 0);
//     //lcd.print("START");
//     analogWrite(9, speed);

//     if (millis() - time > 1000) {
//       time = millis();
//       lcd.clear();
//       lcd.setCursor(0, 0);
//       lcd.print("rpm");
//       lcd.setCursor(4, 0);
//       lcd.print(RPM);
//       lcd.setCursor(0, 1);
//       lcd.print("cnt");
//       lcd.setCursor(4, 1);
//       lcd.print(counter);
//       lcd.setCursor(9, 0);
//       lcd.print("pwr");
//       lcd.setCursor(13, 0);
//       lcd.print(speed);
//     }
//     break;

//   case STOP:
//     //lcd.clear();
//     analogWrite(9, 0);
//     lcd.setCursor(6, 0);
//     lcd.print("STOP!!!");
//     lcd.setCursor(0, 1);
//     lcd.print("CNT:");
//     lcd.setCursor(5, 1);
//     lcd.print(counter);
//     counter = 0;
//     state = EXPECTATION;
//     break;

//   case EXPECTATION:
//     lcd.setCursor(3, 0);
//     //lcd.print("Test OK");
//     //Serial.print("ok");
//     break;
// }  // case

//if (enc1.isTurn()) {  // если был совершён поворот (индикатор поворота в любую сторону)
// Serial.print(speed);
// Serial.print("  ");
// Serial.print(total_rev);
// Serial.println();
// }

// if (counter >= settings.total_rev * 4) {
//   state = STOP;
//   lcd.clear();

// }

// }  // loop
