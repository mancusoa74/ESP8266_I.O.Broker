$ip=gg("ESP8266009b63a3.wanip");
$sw=gg("EESSPP.Switch");
//say($sw);
if ($sw==1){
//say($sw);
//////////
$url="http://$ip/";
$value=0; 
for($i=0;$i<46;++$i) { 
$value+=5;
getURL($url."pwm?ch=0&set=".$value,0);
getURL($url."pwm?ch=1&set=".$value,0);
getURL($url."pwm?ch=2&set=".$value,0);
sleep(0.195); }
//$url0="http://$ip/pwm?ch=0&set=255";
//say($url0);
//getURL($url0,0);
///////$url1="http://$ip/pwm?ch=1&set=255";
///getURL($url1,0);
///////$url2="http://$ip/pwm?ch=2&set=255";
///getURL($url2,0);
};
//esle;
if ($sw==0) { 
//say($sw);
$url0="http://$ip/pwm?ch=0&set=0";
//say($url0);
getURL($url0,0);
$url1="http://$ip/pwm?ch=1&set=0";
getURL($url1,0);
$url2="http://$ip/pwm?ch=2&set=0";
getURL($url2,0);}

 
