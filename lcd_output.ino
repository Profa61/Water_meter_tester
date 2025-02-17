void lcd_start() {
  if (lcd_timeClear()) {
    lcd_timeClear();
    lcd.setCursor(0, 0);
    lcd.print("rpm:");
    lcd.setCursor(4, 0);
    lcd.print(RPM);
    lcd.setCursor(0, 1);
    lcd.print("liter:");
    lcd.setCursor(6, 1);
    lcd.print(counter / settings.turnover_liter);
    lcd.setCursor(9, 0);
    lcd.print("pwr:");
    lcd.setCursor(13, 0);
    lcd.print(settings.speed);
    if (motor_state == LEFT) {
      lcd.setCursor(14, 1);
      lcd.print("<-");
    } else {
      lcd.setCursor(14, 1);
      lcd.print("->");
    }
  }
}  //lcd_start

void lcd_stop() {
  lcd.setCursor(6, 0);
  lcd.print("STOP!!!");
  lcd.setCursor(0, 1);
  lcd.print("LITER:");
  lcd.setCursor(6, 1);
  lcd.print(counter / settings.turnover_liter);
}  //lcd_stop

void lcd_settings1() {
  lcd_timeClear();
  lcd.setCursor(4, 0);
  lcd.print("Speed:");
  lcd.setCursor(6, 1);
  lcd.print(settings.speed);
}  // lcd_settings1

void lcd_settings2() {
  lcd_timeClear();
  lcd.setCursor(4, 0);
  lcd.print("Liters:");
  lcd.setCursor(5, 1);
  lcd.print(settings.total_rev);
}  //lcd_settings2

void lcd_settings3() {
  lcd_timeClear();
  lcd.setCursor(0, 0);
  lcd.print("Turnover Liters:");
  lcd.setCursor(7, 1);
  lcd.print(settings.turnover_liter);
}  //lcd_settings3

bool lcd_timeClear() {
  if (millis() - time_clear > LCD_CLEAR) {
    time_clear = millis();
    lcd.clear();
    return true;
  }
  return false;
}  // lcd_timeClear
