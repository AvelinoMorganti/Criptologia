#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include "ArduinoJson.h"

#define USE_SERIAL Serial
#define SSD "SEU SSD"
#define PASSWORD "SUA SENHA"


ESP8266WiFiMulti WiFiMulti;
DynamicJsonBuffer jsonBuffer;

int i = 0;
int lastbalance = 6693;

void setup() {
  USE_SERIAL.begin(115200);
  //USE_SERIAL.setDebugOutput(true);

  USE_SERIAL.println();
  USE_SERIAL.println();
  USE_SERIAL.println();

  for (uint8_t t = 4; t > 0; t--) {
    USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
    USE_SERIAL.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(SSD, PASSWORD);

  pinMode(D7, OUTPUT);
  digitalWrite(D7, LOW);  
}


void printStatusHTTP(int httpCode){
    switch(httpCode){
      case 100:{
          Serial.println("100 Continue");
          break;
      }      
      case 101:{
          Serial.println("101 Switching Protocols");
          break;
      }      
      case 102:{
          Serial.println("102 Processing");
          break;
      }      
      case 103:{
          Serial.println("103 Early Hints");
          break;
      }      
      case 200:{
          Serial.println("200 OK");
          break;
      }      
      case 201:{
          Serial.println("201 Created");
          break;
      }      
      case 202:{
          Serial.println("202 Accepted");
          break;
      }      
      case 203:{
          Serial.println("203 Non-Authoritative Information");
          break;
      }      
      case 204:{
          Serial.println("204 No Content");
          break;
      }      
      case 205:{
          Serial.println("205 Reset Content");
          break;
      }      
      case 206:{
          Serial.println("206 Partial Content");
          break;
      }      
      case 207:{
          Serial.println("207 Multi-Status");
          break;
      }      
      case 208:{
          Serial.println("208 Already Reported");
          break;
      }      
      case 226:{
          Serial.println("226 IM Used");
          break;
      }      
      case 300:{
          Serial.println("300 Multiple Choices");
          break;
      }      
      case 301:{
          Serial.println("301 Moved Permanently");
          break;
      }      
      case 302:{
          Serial.println("302 Found");
          break;
      }      
      case 303:{
          Serial.println("303 See Other");
          break;
      }      
      case 304:{
          Serial.println("304 Not Modified");
          break;
      }      
      case 305:{
          Serial.println("305 Use Proxy");
          break;
      }      
      case 306:{
          Serial.println("306 Switch Proxy");
          break;
      }      
      case 307:{
          Serial.println("307 Temporary Redirect ");
          break;
      }      
      case 308:{
          Serial.println("308 Permanent Redirect ");
          break;
      }      
      case 400:{
          Serial.println("400 Bad Request");
          break;
      }      
      case 401:{
          Serial.println("401 Unauthorized ");
          break;
      }      
      case 402:{
          Serial.println("402 Payment Required");
          break;
      }      
      case 403:{
          Serial.println("403 Forbidden");
          break;
      }      
      case 404:{
          Serial.println("404 Not Found");
          break;
      }      
      case 405:{
          Serial.println("405 Method Not Allowed");
          break;
      }      
      case 406:{
          Serial.println("406 Not Acceptable");
          break;
      }      
      case 407:{
          Serial.println("407 Proxy Authentication Required ");
          break;
      }      
      case 408:{
          Serial.println("408 Request Timeout");
          break;
      }      
      case 409:{
          Serial.println("409 Conflict");
          break;
      }      
      case 410:{
          Serial.println("410 Gone");
          break;
      }      
      case 411:{
          Serial.println("411 Length Required");
          break;
      }      
      case 412:{
          Serial.println("412 Precondition Failed ");
          break;
      }      
      case 413:{
          Serial.println("413 Payload Too Large");
          break;
      }      
      case 414:{
          Serial.println("414 URI Too Long");
          break;
      }      
      case 415:{
          Serial.println("415 Unsupported Media Type");
          break;
      }      
      case 416:{
          Serial.println("416 Range Not Satisfiable");
          break;
      }      
      case 417:{
          Serial.println("417 Expectation Failed");
          break;
      }      
      case 418:{
          Serial.println("418 I'm a teapot ");
          break;
      }         
      case 420:{
          Serial.println("420 Method Failure");
          break;
      }      
      case 422:{
          Serial.println("422 Unprocessable Entity");
          break;
      }      
      case 423:{
          Serial.println("423 Locked");
          break;
      }      
      case 424:{
          Serial.println("424 Failed Dependency");
          break;
      }      
      case 426:{
          Serial.println("426 Upgrade Required");
          break;
      }      
      case 428:{
          Serial.println("428 Precondition Required ");
          break;
      }      
      case 429:{
          Serial.println("429 Too Many Requests");
          break;
      }      
      case 431:{
          Serial.println("431 Request Header Fields Too Large");
          break;
      }      
      case 440:{
          Serial.println("440 Login Time-out");
          break;
      }      
      case 444:{
          Serial.println("444 No Response");
          break;
      }      
      case 449:{
          Serial.println("449 Retry With");
          break;
      }      
      case 450:{
          Serial.println("450 Blocked by Windows Parental Controls");
          break;
      }      
      case 451:{
          Serial.println("451 Unavailable For Legal Reasons");
          Serial.println("451 Redirect");
          break;
      }       
      case 494:{
          Serial.println("494 Request header too large");
          break;
      }       
      case 495:{
          Serial.println("495 SSL Certificate Error");
          break;
      }       
      case 496:{
          Serial.println("496 SSL Certificate Required");
          break;
      }       
      case 497:{
          Serial.println("497 HTTP Request Sent to HTTPS Port");
          break;
      }     
      case 499:{
          Serial.println("499 Token Required");
          Serial.println("499 Client Closed Request");
          break;
      }      
      case 500:{
          Serial.println("500 Internal Server Error");
          break;
      }      
      case 501:{
          Serial.println("501 Not Implemented");
          break;
      }      
      case 502:{
          Serial.println("502 Bad Gateway");
          break;
      }      
      case 503:{
          Serial.println("503 Service Unavailable");
          break;
      }      
      case 504:{
          Serial.println("504 Gateway Timeout");
          break;
      }      
      case 505:{
          Serial.println("505 HTTP Version Not Supported");
          break;
      }      
      case 506:{
          Serial.println("506 Variant Also Negotiates ");
          break;
      }      
      case 507:{
          Serial.println("507 Insufficient Storage");
          break;
      }      
      case 508:{
          Serial.println("508 Loop Detected ");
          break;
      }      
      case 509:{
          Serial.println("509 Bandwidth Limit Exceeded");
          break;
      }       
      case 510:{
          Serial.println("510 Not Extended");
          break;
      }      
      case 511:{
          Serial.println("511 Network Authentication Required");
          break;
      }      
      case 520:{
          Serial.println("520 Unknown Error");
          break;
      }      
      case 521:{
          Serial.println("521 Web Server Is Down");
          break;
      }       
      case 522:{
          Serial.println("522 Connection Timed Out");
          break;
      }       
      case 523:{
          Serial.println("523 Origin Is Unreachable");
          break;
      }       
      case 524:{
          Serial.println("524 A Timeout Occurred");
          break;
      }       
      case 525:{
          Serial.println("525 SSL Handshake Failed");
          break;
      }       
      case 526:{
          Serial.println("526 Invalid SSL Certificate");
          break;
      }       
      case 527:{
          Serial.println("527 Railgun Error");
          break;
      }       
      case 530:{
          Serial.println("530 Site is frozen");
          break;
      }      
      case 598:{
          Serial.println("598 Network read timeout error");
          Serial.println("530 Origin DNS Error");
          break;
      } 
      default:{
          Serial.print(httpCode);
          Serial.println(" Unknown Error");
          break;
      }    
    }
}



void loop() {
  //wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    HTTPClient http;

    USE_SERIAL.print("[HTTP] BEGIN...\n");
    //http.begin("https://api.blockcypher.com/v1/btc/main/addrs/1CriPTo6QLCLHe6qjzz4dVjUAQm9EnZHQu/balance","0D 2F 90 E5 31 49 63 0C 35 82 A2 00 E5 22 96 44 DA FC C7 CD"); //HTTPS 
    //http.begin("https://api.blockcypher.com/v1/btc/main/addrs/1MMBdLWiAK71oevANJrLHXXKAK8bZrPtqx/balance","0D 2F 90 E5 31 49 63 0C 35 82 A2 00 E5 22 96 44 DA FC C7 CD"); //HTTPS 
    http.begin("https://api.blockcypher.com/v1/btc/main/addrs/18bRpCq7yDccXrhy49ayv18vBQy6TjLtxV/balance","0D 2F 90 E5 31 49 63 0C 35 82 A2 00 E5 22 96 44 DA FC C7 CD"); //HTTPS 
    USE_SERIAL.print("[HTTP] TRYING GET...\n");
    int httpCode = http.GET(); //Começa uma nova conexão e envia um header HTTP

    printStatusHTTP(httpCode);
    
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);
    
      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        //USE_SERIAL.println(payload)
        
        JsonObject& root = jsonBuffer.parseObject((payload));

        const char* address = root["address"];
        long total_received = root["total_received"];
        long total_sent = root["total_sent"]; 
        long balance = root["balance"]; 
        int unconfirmed_balance = root["unconfirmed_balance"]; 
        long final_balance = root["final_balance"]; 
        int n_tx = root["n_tx"]; 
        int unconfirmed_n_tx = root["unconfirmed_n_tx"]; 
        int final_n_tx = root["final_n_tx"];

        //root.printTo(Serial);
        Serial.print("address = ");
        Serial.println(address);
        Serial.print("balance = ");
        Serial.println(balance);
        Serial.print("unconfirmed_balance = ");
        Serial.println(unconfirmed_balance);
        Serial.print("final_balance = ");
        Serial.println(final_balance);
        
        if(final_balance > lastbalance){        
            digitalWrite(D7, HIGH);  
            lastbalance = final_balance;
        }else{
            digitalWrite(D7, LOW);  
        }
        
        //TODO
        //Soa alarme
        //Imprime no display
      }

      
    } else {
      USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      printStatusHTTP(httpCode);
    }
    
    delay(30000);
    http.end();
  }
  delay(1000);
  Serial.println(i);
  i++;
}
