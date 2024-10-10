void autos() {
  switch (state) {
    case SETTINGS1:
      enc1.tick();
      if (enc1.isRight()) settings.speed += 1;
      if (enc1.isLeft()) settings.speed -= 1;
      if (enc1.isFastR()) settings.speed += 10;  // если был быстрый поворот направо, увеличиваем на 10
      if (enc1.isFastL()) settings.speed -= 10;  // если был быстрый поворот налево, уменьшаем на 10
      lcd_settings1();

      break;

    case SETTINGS2:
      //enc1.tick();
      if (enc1.isRight()) settings.total_rev += 500;
      if (enc1.isLeft()) settings.total_rev -= 500;
      lcd_settings2();

      break;

    case START:
      if (counter >= settings.total_rev * TURNOVER_LITER) {
        state = STOP;
        lcd.clear();
      }
      if (enc1.isRight()) settings.speed += 1;
      if (enc1.isLeft()) settings.speed -= 1;
      analogWrite(9, settings.speed);
      lcd_start();

      break;

    case STOP:
      analogWrite(9, 0);
      lcd_stop();
      counter = 0;
      state = EXPECTATION;
      break;

    case EXPECTATION:
      //Serial.print("ok");

      break;
  }  // case
}