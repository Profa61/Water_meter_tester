void autos() {
  switch (state) {
    case SETTINGS1:
      enc1.tick();
      counter = 0;
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
      if ((counter / TURNOVER_LITER) >= settings.total_rev) {
        state = STOP;
      }
      
      if (enc1.isRight()) settings.speed += 1;
      if (enc1.isLeft()) settings.speed -= 1;
      if (change_direction_left) {
        motor_state = RIGHT;
      } else {
        motor_state = LEFT;
      }
      lcd_start();
      break;

    case STOP:
      motor_state = BREAK;
      lcd.clear();
      lcd_stop();
      //counter = 0;
      state = EXPECTATION;
      break;

    case EXPECTATION:
      //Serial.print("ok");

      break;
  }  // switch (state)


  switch (settings.reverse) {
    case 1:
      if ((time_increment()) && (state == START)) {
        settings.speed--;
        if (RPM == 0) settings.reverse = 2;
      }

      break;
    case 2:
      change_direction_left = true;
      if ((time_increment()) && (state == START)) {
        settings.speed++;
        if (RPM >= 250) settings.reverse = 3;
      }

      break;
    case 3:
      if ((time_increment()) && (state == START)) {
        settings.speed--;
        if (RPM == 0) settings.reverse = 4;
      }

      break;
    case 4:
      change_direction_left = false;
      if ((time_increment()) && (state == START)) {
        settings.speed++;
        if (RPM >= 250) settings.reverse = 1;
      }

      break;
  }  //switch (settings.reverse)
     // Serial.println(settings.reverse);
}