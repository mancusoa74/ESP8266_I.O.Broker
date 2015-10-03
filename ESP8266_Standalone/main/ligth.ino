void ligth()
{
  uint16_t lux = lightMeter.readLightLevel(); // Чтение датчика освещённости
///Serial.print("Light: "); Serial.print(lux); Serial.println(" lx");
delay(100);

  if (lux>2) {
  if (lux>luxold1 || lux<luxold2) {
    Serial.print("Light: "); Serial.print(lux); Serial.println(" lx");
    }
     luxold1=lux+2; //переменные для снижения чуствительности
     luxold2=lux-2; //переменные для снижения чуствительности
//   if(IR_KEY) {Serial.println(IR_KEY,HEX); IR_KEY = 0;}//выводим код в терминал.
  }
}

