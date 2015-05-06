<?php
if ($params['idesp']=="") { return; }
addClass('ESP8266'); //Создаем класс ESP8266
addClassObject('ESP8266',$params['idesp']); //Создаем в классе ESP8266 объект где в качестве имени 
addClassProperty('ESP8266', 'vdd', 90); //Создаёт свойство класса и указывает, что необходимо хранить историю значений 90 дней
addClassProperty('ESP8266', 'pwm0', 90); //Создаёт свойство класса и указывает, что необходимо хранить историю значений 90 дней
addClassProperty('ESP8266', 'pwm1', 90); //Создаёт свойство класса и указывает, что необходимо хранить историю значений 90 дней
addClassProperty('ESP8266', 'pwm2', 90); //Создаёт свойство класса и указывает, что необходимо хранить историю значений 90 дней
addClassProperty('ESP8266', 'wanip', 90); //Создаёт свойство класса и указывает, что необходимо хранить историю значений 90 дней

//Распихиваем всё по свойствам. Если полученное значение пустое, то свойство не записываем
if ($params['bmpp']!="") { sg(($params['idesp'].".bmpp"),$params['bmpp']); } //Данные с датчика BMP (давление)
if ($params['bmpt']!="") { sg(($params['idesp'].".bmpt"),$params['bmpt']); } //Данные с датчика BMP (температура)
if ($params['counter']!="") { sg(($params['idesp'].".counter"),$params['counter']); } //Количество импульсов со счетчика
if ($params['dhth1']!="") { sg(($params['idesp'].".dhth1"),$params['dhth1']); } //Данные с первого датчика DHT (влажность)
if ($params['dhth2']!="") { sg(($params['idesp'].".dhth2"),$params['dhth2']); } //Данные со второго датчика DHT (влажность)
if ($params['dhtt1']!="") { sg(($params['idesp'].".dhtt1"),$params['dhtt1']); } //Данные с первого датчика DHT (температура)
if ($params['dhtt2']!="") { sg(($params['idesp'].".dhtt2"),$params['dhtt2']); } //Данные со второго датчика DHT (температура)
if ($params['dsw1']!="") { sg(($params['idesp'].".dsw1"),$params['dsw1']); } //Данные с датчика DS18B20 №1
if ($params['dsw2']!="") { sg(($params['idesp'].".dsw2"),$params['dsw2']); } //Данные с датчика DS18B20 №2
if ($params['dsw3']!="") { sg(($params['idesp'].".dsw3"),$params['dsw3']); } //Данные с датчика DS18B20 №3
if ($params['dsw4']!="") { sg(($params['idesp'].".dsw4"),$params['dsw4']); } //Данные с датчика DS18B20 №4
if ($params['dsw5']!="") { sg(($params['idesp'].".dsw5"),$params['dsw5']); } //Данные с датчика DS18B20 №5
if ($params['freemem']!="") { sg(($params['idesp'].".freemem"),$params['freemem']); } //Объем свободной памяти модуля
if ($params['hostname']!="") { sg(($params['idesp'].".hostname"),$params['hostname']); } //Имя модуля
if ($params['light']!="") { sg(($params['idesp'].".light"),$params['light']); } //Данные с датчика BH1750
if ($params['uptime']!="") { sg(($params['idesp'].".uptime"),$params['uptime']); } //Время непрерывной работы модуля
if ($params['vdd']!="") { sg(($params['idesp'].".vdd"),$params['vdd']); } //Напряжение на модуле
if ($params['ver']!="") { sg(($params['idesp'].".ver"),$params['ver']); } //Версия прошивки
if ($params['pwm0']!="") { sg(($params['idesp'].".pwm0"),$params['pwm0']); } //Состояние PWM 0
if ($params['pwm1']!="") { sg(($params['idesp'].".pwm1"),$params['pwm1']); } //Состояние PWM 1
if ($params['pwm2']!="") { sg(($params['idesp'].".pwm2"),$params['pwm2']); } //Состояние PWM 2
if ($params['wanip']!="") { sg(($params['idesp'].".wanip"),$params['wanip']); } //Данные IP
sg(($params['idesp'].".idesp"),$params['idesp']);  //
$ver=$params['ver'];
setGlobal(($idesp.".ver"),$ver);
?>
