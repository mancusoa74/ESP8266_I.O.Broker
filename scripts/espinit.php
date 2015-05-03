<?php
if ($params['idesp'] == "") { 
  return;
}

addClass("ESP8266"); //Создаем класс ESP8266
addClassObject("ESP8266", $params['idesp']); //Создаем в классе ESP8266 объект где в качестве имени 
addClassProperty("ESP8266", "vdd", 90); //Создаёт свойство класса и указывает, что необходимо хранить историю значений 90 дней
addClassProperty("ESP8266", "pwm0", 90); //Создаёт свойство класса и указывает, что необходимо хранить историю значений 90 дней
addClassProperty("ESP8266", "pwm1", 90); //Создаёт свойство класса и указывает, что необходимо хранить историю значений 90 дней
addClassProperty("ESP8266", "pwm2", 90); //Создаёт свойство класса и указывает, что необходимо хранить историю значений 90 дней
addClassProperty("ESP8266", "wanip", 90); //Создаёт свойство класса и указывает, что необходимо хранить историю значений 90 дней

//Распихиваем всё по свойствам. Если полученное значение пустое, то свойство не записываем
$properties = array(
  "bmpp", "bmpt", "counter", "dhth1", "dhth2", "dhtt1", "dhtt2", "dsw1", "dsw2", "dsw2", "dsw3", "dsw4", "dsw5",
  "freemem", "hostname", "light", "uptime", "vdd", "ver", "pwm0", "pwm1", "pwm2", "wanip",
);

foreach ($properties as $k => $property) {
  if (!empty($params[$property])) {
    sg(($params['idesp'] . "." . $property), $params[$property]);
  }
}

sg(($params['idesp'] . ".idesp"), $params['idesp']);
setGlobal(($idesp . ".ver"), $params['ver']);
