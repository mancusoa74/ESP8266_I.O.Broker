/* 
  FSWebServer - Example WebServer with SPIFFS backend for esp8266
  Copyright (c) 2015 Hristo Gochkov. All rights reserved.
  This file is part of the ESP8266WebServer library for Arduino environment.
 
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
  upload the contents of the data folder with MkSPIFFS Tool ("ESP8266 Sketch Data Upload" in Tools menu in Arduino IDE)
  !!! This will erase any previous SPIFFS data you may have!
  !!! Make Backups First !!!
  if you do not have it, get it at : <<<FILL THIS
  access the sample web page at http://esp8266fs.local
  edit the page by going to http://esp8266fs.local/edit
*/
///#include <WiFiServer.h>
///#include <ESP8266WiFi.h>
///#include <WiFiClient.h>
///#include <ESP8266WebServer.h>
///#include <ESP8266mDNS.h>


#define DBG_OUTPUT_PORT Serial

///const char* ssid = "RT50";
///const char* password = "zyxel2011";
///const char* host = "esp_1";


//holds the current upload
////File fsUploadFile;

//format bytes
String formatBytes(size_t bytes){
  if (bytes < 1024){
    return String(bytes)+"B";
  } else if(bytes < (1024 * 1024)){
    return String(bytes/1024.0)+"KB";
  } else if(bytes < (1024 * 1024 * 1024)){
    return String(bytes/1024.0/1024.0)+"MB";
  } else {
    return String(bytes/1024.0/1024.0/1024.0)+"GB";
  }
}

String getContentType(String filename){
  if(server.hasArg("download")) return "application/octet-stream";
  else if(filename.endsWith(".htm")) return "text/html";
  else if(filename.endsWith(".html")) return "text/html";
  else if(filename.endsWith(".css")) return "text/css";
  else if(filename.endsWith(".js")) return "application/javascript";
  else if(filename.endsWith(".png")) return "image/png";
  else if(filename.endsWith(".gif")) return "image/gif";
  else if(filename.endsWith(".jpg")) return "image/jpeg";
  else if(filename.endsWith(".ico")) return "image/x-icon";
  else if(filename.endsWith(".xml")) return "text/xml";
  else if(filename.endsWith(".pdf")) return "application/x-pdf";
  else if(filename.endsWith(".zip")) return "application/x-zip";
  else if(filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}

bool handleFileRead(String path){
  if(path.endsWith("/")) path += "index.htm";
  String contentType = getContentType(path);
  String pathWithGz = path + ".gz";
  
  if(SPIFFS.exists(pathWithGz) || 
    SPIFFS.exists(path)){
    if(SPIFFS.exists(pathWithGz))
      path += ".gz";
    Serial.println("handleFileRead: " + path);
    File file = SPIFFS.open(path, "r");
    server.streamFile(file, contentType);
    Serial.println("streamFile done");
    file.close();
    return true;
  }
  return false;
}

void handleFileUpdate(){
  if(server.uri() != "/edit") return;
  HTTPUpload& upload = server.upload();
  if(upload.status == UPLOAD_FILE_START){
    String filename = upload.filename;
    DBG_OUTPUT_PORT.print("Upload Name: "); DBG_OUTPUT_PORT.println(filename);
    fsUploadFile = SPIFFS.open(filename, "w");
    filename = String();
  } else if(upload.status == UPLOAD_FILE_WRITE){
    //DBG_OUTPUT_PORT.print("Upload Data: "); DBG_OUTPUT_PORT.println(upload.currentSize);
    if(fsUploadFile)
      fsUploadFile.write(upload.buf, upload.currentSize);
  } else if(upload.status == UPLOAD_FILE_END){
    if(fsUploadFile)
      fsUploadFile.close();
    DBG_OUTPUT_PORT.print("Upload Size: "); DBG_OUTPUT_PORT.println(upload.totalSize);
  }
}

void handleFileDelete(){
  if(server.args() == 0) return server.send(500, "text/plain", "BAD ARGS");
  String path = server.arg(0);
  if(path == "/")
    return server.send(500, "text/plain", "BAD PATH");
  if(!SPIFFS.exists(path))
    return server.send(404, "text/plain", "FileNotFound");
  SPIFFS.remove(path);
  server.send(200, "text/plain", "");
  path = String();
}

void handleFileCreate(){
  if(server.args() == 0)
    return server.send(500, "text/plain", "BAD ARGS");
  String path = server.arg(0);
  if(path == "/")
    return server.send(500, "text/plain", "BAD PATH");
  if(SPIFFS.exists(path))
    return server.send(500, "text/plain", "FILE EXISTS");
  File file = SPIFFS.open(path, "w");
  if(file)
    file.close();
  else
    return server.send(500, "text/plain", "CREATE FAILED");
  server.send(200, "text/plain", "");
  path = String();
}

void handleFileList() {
  if(!server.hasArg("dir")) {server.send(500, "text/plain", "BAD ARGS"); return;}
  
  String path = server.arg("dir");
  Dir dir = SPIFFS.openDir(path);
  path = String();

  String output = "[";
  while(dir.next()){
    File entry = dir.openFile("r");
    if (!entry) break;
    if (output != "[") output += ',';
    bool isDir = false;
    output += "{\"type\":\"";
    output += (isDir)?"dir":"file";
    output += "\",\"name\":\"";
    output += String(entry.name()).substring(1);
    output += "\"}";
    entry.close();
  }
  
  output += "]";
  server.send(200, "text/json", output);
}

///void setup(void){
 /// DBG_OUTPUT_PORT.begin(115200);
 /// DBG_OUTPUT_PORT.print("\n");
 /// Serial.setDebugOutput(true);
 /// SPIFFS.begin();
  //SPIFFS INIT
//  DBG_OUTPUT_PORT.printf("\n==== SPIFFS Info ====\n");
//  DBG_OUTPUT_PORT.printf("FS Mount: %d\n", FS.mount());
//  DBG_OUTPUT_PORT.printf("FS Size: %s\n", formatBytes(FS.size()));
//  DBG_OUTPUT_PORT.printf("FS Bytes: total: %s, used: %s\n", formatBytes(FS.totalBytes()), formatBytes(FS.usedBytes()));
//  DBG_OUTPUT_PORT.printf("FS Blocks: total: %d, free: %d, size: %s\n", FS.totalBlocks(), FS.freeBlocks(), formatBytes(FS.blockSize()));
//  DBG_OUTPUT_PORT.printf("FS Pages: allocated: %d, deleted: %d, size: %s\n", FS.allocatedPages(), FS.deletedPages(), formatBytes(FS.pageSize()));
  ///{
   /// Dir dir = SPIFFS.openDir("/");
   /// while (dir.next()) {
      
   ///   String fileName = dir.fileName();
   ///   size_t fileSize = dir.fileSize();
    ///  DBG_OUTPUT_PORT.printf("FS File: %s, type: %s, size: %s\n", fileName.c_str(), "file", formatBytes(fileSize).c_str());
   /// }
   /// DBG_OUTPUT_PORT.printf("\n");
 /// }
  

 
  
///}
 
////void loop(void){
 /////////// server.handleClient();
/////////////}
