

/*  --------- ОПИСАНИЕ ПРОТОКОЛА -----------
   Скорость шим - s0-255            Ждет от 0 до 255
   Счетчик литров - t0-65036        Ждет от 0 до 65036
   Запустить тест - a
   Остановить тест  b
   Включить пресет  p1              0 - Выключить, 1 - Включить
   Выключить пресет p0
   Обнулить счетчик r0
   Сменить направление вращения с1  По часовой
   Сменить направление вращения с0  Против часовой  
  
   */

void serial() {

  if (Serial.available() > 1) {
    char key = Serial.read();
    int val = Serial.parseInt();
    switch (key) {
      case 's':
        settings.speed = val;
        break;

      case 't':
        settings.total_rev = val;
        break;

      case 'a':
        state = START;
        break;

      case 'b':
        state = STOP;
        break;

      case 'p':
        settings.reverse = val;
        break;

      case 'r':
        counter = val;
        break;

      case 'c':
        change_direction_left = val;
        break;

      case 'k':
        Serial.print(settings.total_rev);

        break;
    }
  }
}  // void uart()
