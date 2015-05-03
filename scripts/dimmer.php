$ip = gg("ESP8266009b63a3.wanip");
$channel = 0;
$url = "http://$ip/pwm?ch=0&set=" . gg("EESSPP.pwm" . $channel);
getURL($url, 0);
//say($url);

//$url = getURL("http://$ip/pwmprint", 0);
//say($url);

//$now = getGlobal('EESSPP.pwm');
//echo $now;
//http://192.168.0.45/pwm?ch=0&set=".$now."&flash=1;
//setGlobal("ESP8266009b63a3.pwm0", $now);
