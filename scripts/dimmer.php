<?php
$ip = gg("ESP8266009b63a3.wanip");
$channel = 0;
$url = "http://$ip/pwm?ch=0&set=" . gg("EESSPP.pwm" . $channel);
getURL($url, 0);
$pwm=gg("EESSPP.pwm".$channel);
if ($pwm >= 1) {
setGlobal(("EESSPP.Switch"),1);
}
?>
