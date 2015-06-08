 #include <Wire.h>
#include <BH1750.h>
BH1750 lightMeter;
volatile unsigned long IR_KEY;   //код кнопки на пульте
//int luxold=0; //переменная для уменьшения чуствительности датчика света
int luxold1=0;
int luxold2=0;
int a=0; // переменная переключения режима, при нажатии кнопки она принимает значение +1
int b=0; //
int c=0; //
int d=0; //
int e=0; //
int f=0; //
int g=0; //
int ir_sens=0; //ПЕРЕМЕННАЯ ДЛЯ СЧИТЫВАНИЯ ПОКАЗАНИЙ ик-дАТЧИКА 
unsigned int pwm1=0;
unsigned int pwm2=0;
unsigned int pwm3=0;
unsigned int pwm=0;

void setup() {                
 Serial.begin(9600);
 IR_KEY = 0; //переменная для получения кода кнопки с ИК-пульта
 attachInterrupt(0,IRinterrupt,CHANGE); // назначим прерывание на появление импульсов с ИК-приёмника
 attachInterrupt(1, ir_sensor, CHANGE); // Прерывания для распознавания сигнала с ИК Датчика
 pinMode(2,INPUT_PULLUP); // Вход ИК приёмника
 pinMode(3,INPUT_PULLUP); // Вход с ИК датчика 
 pinMode(13, OUTPUT);
 //pinMode(11, OUTPUT);
 //pinMode(10, OUTPUT); // назначаем пины как выходы
 pinMode(4, OUTPUT);
 pinMode(6, OUTPUT);
 pinMode(7, OUTPUT);
 lightMeter.begin();
 IncrementPWM(); //вызов функции плавного включения света
 Serial.println("Running...");
 }
void loop() {
 uint16_t lux = lightMeter.readLightLevel(); // Чтение датчика освещённости
  if (lux>3) {  
  if (lux>luxold1 || lux<luxold2) {Serial.print("Light: "); Serial.print(lux); Serial.println(" lx");}
     luxold1=lux+1; //переменные для снижения чуствительности
     luxold2=lux-1; //переменные для снижения чуствительности
} 
  if(IR_KEY) {
   Serial.println(IR_KEY,HEX); //выводим код в терминал.
   IR_KEY = 0;
 }
}// Конец цикла

void IRinterrupt(){ //прерывание для обработки импусльво с ик ПРИЁМНИКА
  static unsigned long key, prevTime;
  unsigned long currTime, d_ir;
  currTime = micros();
  d_ir = currTime - prevTime;
  if(d_ir < 110) return;        // "дребезг"
  if(d_ir < 1000){               // "0"
    key = key << 1;
    prevTime = currTime;
    return; }
  if(d_ir < 2400){               // "1"
    key = key << 1;
    key++;
    prevTime = currTime;
    return;}
  if(d_ir < 13000) IR_KEY = key; // код кнопки получен
  prevTime = currTime;
 
if (IR_KEY == 0xC000305) {if (pwm1<=247) {pwm1=pwm1+7;analogWrite(10, pwm1);}}// увеличение значения pwm1 на 7
if (IR_KEY == 0xC003105) {if (pwm1>=7) {pwm1=pwm1-7;analogWrite(10, pwm1);} else {pwm1=0;analogWrite(10, pwm1);}}// уменьшение значения pwm1 на 7
if (IR_KEY == 0xC000D05) {if (pwm2<=247) {pwm2=pwm2+7;analogWrite(11, pwm2);}}// увеличение значения pwm2 на 7
if (IR_KEY == 0x3000F05) {if (pwm2>=7) {pwm2=pwm2-7;analogWrite(11, pwm2);} else {pwm2=0;analogWrite(11, pwm2);}}// уменьшение значения pwm2 на 7
if (IR_KEY == 0xC000905) {if (pwm3<=247) {pwm3=pwm3+7;analogWrite(5, pwm3);}}// увеличение значения pwm3 на 7
if (IR_KEY == 0xC002505) {if (pwm3>=7) {pwm3=pwm3-7;analogWrite(5, pwm3);} else {pwm3=0;analogWrite(5, pwm3);}}
if (IR_KEY == 0x3030D05) {pwm=0;IncrementPWM();}

}// уменьшение значения pwm3 на 5
// начинаем включать светодиоды на пинах
//if (a==1){digitalWrite(11, LOW);} else {digitalWrite(11, HIGH); a=0;} // действие после нажатия кнопки, если переменная стала равна 1 то
//if (b==1){digitalWrite(10, HIGH);} else {digitalWrite(10, LOW); b=0;} // произвести переключение пина в режим HIGH, если же нет то вернуть переменную в исходное состояние

void ir_sensor(){ //Функция прерывания для считывания показаний с ИК Датчика
ir_sens=digitalRead(3);
if (ir_sens==1) digitalWrite(6, HIGH); //Включение светодиоад
if (ir_sens==0) digitalWrite(6, LOW); //Отключение светодиода
//Serial.println(ir_sens);
}
void IncrementPWM(){ // Функция плавного включения света
 do {
  analogWrite(10, pwm);
  analogWrite(11, pwm);
  analogWrite(5, pwm);
  delay(50); 
  pwm=pwm+1;
  pwm1=pwm1+1;
  pwm2=pwm2+1;
  pwm3=pwm3+1;
  } while(pwm<=252);
}
