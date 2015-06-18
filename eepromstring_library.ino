/*I haven't compiled this into a library yet or setup a github project, 
but I wrote some functions to make it easier to save code into eeprom.
Instead of allocating a random amount of memory space for each variable
saved into eeprom, i made a set of functions that will dynamically expand/contract
the memory used for each variable. Basically it works similar to a URL encoding, 
storing the variable names and values in eeprom separated by & and =. 
It's a work in progress, but if anyone is struggling with using eeprom, give this a shot. */

void eepromSet(String name, String value){
  Serial.println("eepromSet");
 
  String list=eepromDelete(name);
  String nameValue="&" + name + "=" + value;
  //Serial.println(list);
  //Serial.println(nameValue);
  list+=nameValue;
  for (int i = 0; i < list.length(); ++i){
    EEPROM.write(i,list.charAt(i));
  }
  EEPROM.commit();
  Serial.print(name);
  Serial.print(":");
  Serial.println(value);
}
String eepromDelete(String name){
  Serial.println("eepromDelete");
 
  int nameOfValue;
  String currentName="";
  String currentValue="";
  int foundIt=0;
  char letter;
  String newList="";
  for (int i = 0; i < 512; ++i){
      letter= char(EEPROM.read(i));
      if (letter=='\n'){
        if (foundIt==1){
        }else if (newList.length()>0){
           newList+="=" + currentValue;
        }
        break;
      } else if (letter=='&'){
        nameOfValue=0;
        currentName="";
        if (foundIt==1){
          foundIt=0;
        }else if (newList.length()>0){
           newList+="=" + currentValue;
        }
     
       
      } else if (letter=='='){
        if (currentName==name){
           foundIt=1;
        }else{
           foundIt=0;
           newList+="&" + currentName;
        }
        nameOfValue=1;
        currentValue="";
      }
      else{
        if (nameOfValue==0){
          currentName+=letter;
        }else{
          currentValue+=letter;
        }
      }
  }
  for (int i = 0; i < 512; ++i){
    EEPROM.write(i,'\n');
  }
  EEPROM.commit();
  for (int i = 0; i < newList.length(); ++i){
    EEPROM.write(i,newList.charAt(i));
  }
  EEPROM.commit();
  Serial.println(name);
  Serial.println(newList);
  return newList;
}
void eepromClear(){
  Serial.println("eepromClear");
  for (int i = 0; i < 512; ++i){
    EEPROM.write(i,'\n');
  }
}
String eepromList(){
  Serial.println("eepromList");
  char letter;
  String list="";
  for (int i = 0; i < 512; ++i){
      letter= char(EEPROM.read(i));
      if (letter=='\n'){
        break;
      }else{
        list+=letter;
      }
  }
  Serial.println(list);
  return list;
}
String eepromGet(String name){
  Serial.println("eepromGet");
 
  int nameOfValue;
  String currentName="";
  String currentValue="";
  int foundIt=0;
  String value="";
  char letter;
  for (int i = 0; i < 512; ++i){
      letter= char(EEPROM.read(i));
      if (letter=='\n'){
        if (foundIt==1){
          value=currentValue;
        }
        break;
      } else if (letter=='&'){
        nameOfValue=0;
        currentName="";
        if (foundIt==1){
          value=currentValue;
          break;
        }
      } else if (letter=='='){
        if (currentName==name){
           foundIt=1;
        }else{
        }
        nameOfValue=1;
        currentValue="";
      }
      else{
        if (nameOfValue==0){
          currentName+=letter;
        }else{
          currentValue+=letter;
        }
      }
  }
  Serial.print(name);
  Serial.print(":");
  Serial.println(value);
  return value;
}
