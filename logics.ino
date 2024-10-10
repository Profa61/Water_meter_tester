void logics() {
  if ((micros() - lastflash) > 2000000) {  //если сигнала нет больше секунды
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

  // if (counter >= settings.total_rev * 4) {
  //   state = STOP;
  //   lcd.clear();
  // }

 
}  //logics