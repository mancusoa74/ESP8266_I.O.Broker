//урок от Дмитрия Осипова - управление arduino ИК пультом
#include <IRremote.h> // это скачанная библиотека
#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;

int RECV_PIN = 11; //вход ИК приемника
IRrecv irrecv(RECV_PIN);
decode_results results;
int a=0; // переменная переключения режима, при нажатии кнопки она принимает значение +1
int b=0; //
int c=0; //
int d=0; //
int e=0; //
int f=0; //
int g=0; //
 

void setup()
{
irrecv.enableIRIn(); // включить приемник

pinMode(13, OUTPUT);
pinMode(2, OUTPUT);
pinMode(3, OUTPUT); // назначаем пины как выходы
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
pinMode(6, OUTPUT);
pinMode(7, OUTPUT);

//////////////////////////
Serial.begin(9600);
  lightMeter.begin();
  Serial.println("Running...");
  //////////////////////////////////////////

} 

void loop() {
/////////////////////////////////////////////////////////////
uint16_t lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  delay(10);
  ////////////////////////////////////////////////////////////
 if (irrecv.decode(&results)) {
delay(3); // задержка перед выполнением определения кнопок, чтобы избежать быстрое двойное нажатие

if (results.value == 0x55173B8B) {a=a+1;} // обработка нажитя клавиши, здесь переменная принимает значение +1
if (results.value == 0xF6A075A7) {a=a+1;} // обработка нажитя клавиши, здесь переменная принимает значение +1
if (results.value == 0x1008889) {b=b+1;} //ВАЖНО !!! ( 1008889 ) это код кнопки №2 - моего пульта от телевизора Panasonic - у вашего пульта будет другой код - замените на свой
if (results.value == 0x1004849) {c=c+1;}
if (results.value == 0x100C8C9) {d=d+1;}
if (results.value == 0x1002829) {e=e+1;}
if (results.value == 0x100A8A9) {f=f+1;}
if (results.value == 0x1006869) {g=g+1;}

// начинаем включать светодиоды на пинах
if (a==1){digitalWrite(2, HIGH);} else {digitalWrite(2, LOW); a=0;} // действие после нажатия кнопки, если переменная стала равна 1 то
if (a==1){digitalWrite(13, HIGH);} else {digitalWrite(13, LOW); a=0;} // действие после нажатия кнопки, если переменная стала равна 1 то
//if (b==1){digitalWrite(2, HIGH);} else {digitalWrite(2, LOW); b=0;} // произвести переключение пина в режим HIGH, если же нет то вернуть переменную в исходное состояние
if (c==1){digitalWrite(3, HIGH);} else {digitalWrite(3, LOW); c=0;} // Дествие может быть другим
if (d==1){digitalWrite(4, HIGH);} else {digitalWrite(4, LOW); d=0;} // действие после нажатия кнопки
if (e==1){digitalWrite(5, HIGH);} else {digitalWrite(5, LOW); e=0;} // действие после нажатия кнопки
if (f==1){digitalWrite(6, HIGH);} else {digitalWrite(6, LOW); f=0;} // действие после нажатия кнопки
if (g==1){digitalWrite(7, HIGH);} else {digitalWrite(7, LOW); g=0;} // действие после нажатия кнопки


{ //
delay(10); //пауза между повторами //
} //
irrecv.resume(); // 

}

}
