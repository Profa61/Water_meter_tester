void logics() {
  if ((micros() - lastflash) > 3000000) {  //если сигнала нет больше секунды

    RPM = 0;
  }

  if (!digitalRead(SW)) {

    lcd.clear();
    delay(250);
    if (state == SETTINGS1) {
      state = SETTINGS2;
      return;
    }
    if (state == EXPECTATION) {
      state = SETTINGS1;
      return;
    }
    if (state == START) {
      state = STOP;
      return;
    }
    if (state == SETTINGS2) {
      state = START;
      return;
    }

    //Serial.println(state);
  }
}  //logics


void motor_direction() {

  if (motor_state == BREAK) {
    analogWrite(MOTOR_LEFT, 0);
    analogWrite(MOTOR_RIGHT, 0);
  }
  if (motor_state == LEFT) {
    analogWrite(MOTOR_LEFT, settings.speed);
    analogWrite(MOTOR_RIGHT, 0);
  }
  if (motor_state == RIGHT) {
    analogWrite(MOTOR_LEFT, 0);
    analogWrite(MOTOR_RIGHT, settings.speed);
  }

}  //motor_direction

bool time_increment(){
    if (millis() - time_speed_reduction > settings.time_revers) {
      time_speed_reduction = millis();
      return true;
    }
    return false;
  } //time_increment()
