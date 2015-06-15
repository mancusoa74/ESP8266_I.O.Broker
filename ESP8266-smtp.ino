#define SSID "wi-fi_login" // ваш SSID
#define PASS "wi-fi_password" // ваш пароль Wi-Fi
 
#define SMTPServer "s02.atomsmtp.com" //smtp сервер
#define SMTPPort "2525" // smtp порт
#define MailLogin "smtp_example@gmail.com" // логин для smtp
#define MailLoginBase64 "dWd1LCBrb25lNG5vCg==" //логин для smtp в Base64
#define MailPasswordBase64 "aHJlbiB0YW0K" // пароль для smtp в Base64
#define MailRelay "example@mail.ru" // промежуточная почта для "отмывания" email
#define PhoneNumber "375290000000" // номер телефона
#define Message "Hello from Arduino!" //сообщение
 
#define SERIAL_RX_BUFFER_SIZE 256
#define SERIAL_TX_BUFFER_SIZE 256
 
void setup()
{
    delay(2000);
    Serial3.begin(115200);
    Serial3.setTimeout(5000);
    Serial.begin(115200); // для отладки
    Serial.println("Init");
    Serial3.println("AT+RST"); // сброс и проверка, что модуль готов
    if(WiteString("Ready", 5000)) {
        while(Serial3.available()) { Serial3.read();}
        Serial.println("WiFi - Module is ready");
    }else{
        Serial.println("Module dosn't respond.");
        while(1);
    }
    delay(100);
 
    Serial3.println(" AT+CIPMODE=0");
    WiteString("OK");
    while(Serial3.available()) { Serial3.read();}
 
    Serial3.println("AT+CIPMUX=1");
    WiteString("OK");
    while(Serial3.available()) { Serial3.read();}
 
    // try to connect to wifi
    boolean connected = false;
    for(int i=0;i<5;i++) {
        if(connectWiFi()) {
            connected = true;
            break;
        }
    }
        if (!connected) {
        while(1);
    }
}
void loop()
{
    String cmd = "AT+CIPSTART=0,\"TCP\",\"";
    cmd += String(SMTPServer);
    cmd += "\"," + String(SMTPPort);
    Serial3.println(cmd);
 
    if(WiteString("Linked", 5000)) {
        while(Serial3.available()) { Serial3.read();}
        Serial.println("Link");
    }
    else {
        Serial.println("Link fail");
        while (1);
    }
 
    if (WiteString("OK", 2000)) {
        while(Serial3.available()) { Serial3.read();}
    }
    else {
        while (1);
    }
  
    Send("HELO 1.2.3.4", true);
    Send("AUTH LOGIN", true);
    Send(MailLoginBase64, true);
    Send(MailPasswordBase64, true);
    Send("MAIL FROM:<" + String(MailLogin) + ">", true);
    Send("RCPT TO:<" + String(MailRelay) + ">", true);
    Send("DATA", true);
    Send("Subject:SMS", false);
    Send("To:\"" + String(PhoneNumber) + "\" <" + String(PhoneNumber) + "@sms.mts.by>", false);
    Send("From: <" + String(MailLogin) + ">", false);
    Send("", false);
    Send(Message, false);
    Send(".", true);
    Send("QUIT", true);
 
    while(1) {};
}
 
boolean connectWiFi()
{
  Serial3.println("AT+CWMODE=1");
  while (!Serial3.available())	{ delay(10);}
  while (Serial3.available()) {Serial3.read();}
  String cmd="AT+CWJAP=\"";
  cmd+=SSID;
  cmd+="\",\"";
  cmd+=PASS;
  cmd+="\"";
  Serial3.println(cmd);
 
  if(WiteString("OK", 8000)){
    Serial.println("Connected to WiFi.");
    return true;
  }else{
    Serial.println("Can not connect to the WiFi.");
    return false;
  }
}
 
bool Send(String S, bool wite) {
    Serial3.print("AT+CIPSEND=0,");
    Serial3.println(S.length()+2);
    while (!Serial3.available()) { delay(10);}
    if(Serial3.find(">")){
    }else{
        Serial3.println("AT+CIPCLOSE=0");
        delay(1000);
        return false;
    }
    Serial3.print(S + "\r\n");//добаяляем перевод строки
    if (WiteString("OK", 15000)) {
        if (wite) {
            WiteString("+IPD", 15000);
            while(Serial3.available()) {
                Serial3.read();}}
        return true;}
    else {
        return false;}
}
 
void WiteString(String S) {
    int L = S.length();
    String T = String(" ");
    while(1) {
        if (Serial3.available()) {
            char c = Serial3.read();
            T = T + String(c);
            if (T.length() > L) T = T.substring(1);
            if (S.charAt(0) == T.charAt(0))
            if (S.compareTo(T) == 0) return;
        }
        else {
            delay(1);
        }
    }
}
 
bool WiteString(String S, int Time) {
    int L = S.length();
    String T = String(" ");
    while(Time>0) {
        if (Serial3.available()) {
            char c = Serial3.read();
            T = T + String(c);
            if (T.length() > L) T = T.substring(1);
            if (S.charAt(0) == T.charAt(0))
            if (S.compareTo(T) == 0) return true;
        }
        else {
            delay(1);
            Time--;
        }
    }
    return false;
}
 
String WiteString(int Time) {
    String T = String("");
    while(Time>0) {
        if (Serial3.available()) {
            char c = Serial3.read();
            T = T + String(c);
        }
        else {
            delay(1);
            Time--;
        }
    }
    return T;
}
