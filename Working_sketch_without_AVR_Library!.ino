//Выкладываю рабочий скетч для управления МР-3 щита от любого совместимого инфракрасного пульта управления.
//Например от телевизора. уровень громкости выбирается цифровыми клавишами на пульте. музыка проигрывается в
//случайном порядке с карты памяти. уровень громкости при включении установлен на минимум.
#include <MP3.h> 
 // коды клавиш ИК пульта )Коды указаны условно.сюда нужно вписать коды, полученные в терминале при отладке  из 19 строки 
 #define PAUSE           0x00000000    //ИГРА-ПАУЗА 
 #define NEXT            0x40BF807F    //СЛЕДУЩАЯ 
 #define STOP            0x0000011B    //СТОП 
 #define PLAY_SD         0x0A000B11    //ИГРАЕМ С КАРТЫ 
 #define PLAY_USB_DISK   0xA00001B1    //ИГРАЕМ С ЮСБ-ФЛЕШКИ 
 #define VOLUME_10       0x40BF00FF    //ГРОМКОСТЬ 10 % 
 #define VOLUME_20       0xAAAAAAAA    //ГРОМКОСТЬ 20 % 
 #define VOLUME_30       0xAAAA1AAA    //ГРОМКОСТЬ 30 % 
 #define VOLUME_40       0xAAA1AAAA    //ГРОМКОСТЬ 40 % 
 #define VOLUME_50       0x1AAAAAAA    //ГРОМКОСТЬ 50 % 
 #define VOLUME_60       0xAAAAAAA1    //ГРОМКОСТЬ 60 % 
 #define VOLUME_70       0xAAAAAA1A    //ГРОМКОСТЬ 70 % 
 #define VOLUME_80       0xAAAAA1AA    //ГРОМКОСТЬ 80 % 
 #define VOLUME_90       0xAA11AAAA    //ГРОМКОСТЬ 90 % 
 #define VOLUME_100      0xAAAAA11A    //ГРОМКОСТЬ 100 % 
 MP3 mp3; 
 volatile unsigned long IR_KEY;  //код кнопки на пульте 
 int inByte = 0; 
 void setup() { 
     /** begin function */ 
    mp3.begin(); 
    /** set volum to the MAX */ 
    mp3.volume(0x06); 
    /** set MP3 Shield CYCLE mode */ 
    mp3.set_mode(MP3::CYCLE); 
    /** play music in sd */ 
    mp3.play_sd(0x0001);    
    /** play music in USB-disk */   
   // mp3.play_usb_disk(0x0001); 
    //Serial.begin(9600); 
    pinMode(2, INPUT);    // ИК приемник подключим сюда 
    IR_KEY = 0; 
    attachInterrupt(0,IRinterrupt,FALLING); // назначим прерывание 
 } 

  
