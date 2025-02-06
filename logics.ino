void logics() {
  if ((micros() - lastflash) > 3000000) {  //если сигнала нет больше секунды
                                           //lastflash = micros();

    RPM = 0;
  }

  if (!digitalRead(SW)) {

    lcd.clear();
    delay(250);
    switch (state) {
      case SETTINGS1:
        state = SETTINGS2;
        return;

      case SETTINGS2:
        state = SETTINGS3;
        return;

      case SETTINGS3:
        state = START;
        return;

      case START:
        state = STOP;
        return;

      case EXPECTATION:
        state = SETTINGS1;
        return;
    }

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

bool time_increment() {
  if (millis() - time_speed_reduction > settings.time_revers) {
    time_speed_reduction = millis();
    return true;
  }
  return false;
}  //time_increment()
