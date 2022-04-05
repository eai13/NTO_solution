#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#define NEW_REPORT    0x01
#define NEW_FILL      0x02
#define CHECK_ENABLE  0x03
#define CHECK_WHICH   0x04
#define TECH_NOTIFY   0x05
#define ADD_BONUS     0x06

//#pragma pack(push, 1)
struct user{
  String name;
  String status;
  uint8_t id[7];
  int32_t balance;
};
//#pragma pack(pop)

#define CONTAINER_ID  12
                               //********HERE******
#define REPORT_REQUEST "http://192.168.137.110:8080/report?id=12&"  // Server IP Change
uint8_t GetReportString(uint8_t * servo, uint8_t * rgb, uint8_t * level){
  String request = REPORT_REQUEST;
  for (uint8_t iter = 0; iter < 3; iter++){
    request += "s" + String(iter) + "=" + String(servo[iter]) + 
              "&r" + String(iter) + "=" + String(rgb[iter]) +
              "&l" + String(iter) + "=" + String(level[iter]);
    if (iter != 2) request += "&";
  }
  
  WiFiClient client;
  HTTPClient http;
  http.begin(client, request.c_str());
  if (http.GET() > 0){
    http.end();
    return 1;
  }
  else{
    http.end();
    return 0;
  }
}
                             //********HERE********
#define FILL_REQUEST  "http://192.168.137.110:8080/event/fill?id=12"  // Server IP Change
uint8_t GetFillString(uint8_t * cont){
  String request = FILL_REQUEST;
  for (uint8_t iter = 0; iter < 3; iter++){
    request += "&f" + String(iter) + "=" + String(cont[iter]);
  }

  WiFiClient client;
  HTTPClient http;
  http.begin(client, request.c_str());
  if (http.GET() > 0){
    http.end();
    return 1;
  }
  else{
    http.end();
    return 0;
  }
}
                               //********HERE********
#define ENABLE_REQUEST  "http://192.168.137.110:8080/event/enable?id=12" // Server IP Change
uint8_t GetEnable(void){
  String request = ENABLE_REQUEST;
  String response;
  WiFiClient client;
  HTTPClient http;
  http.begin(client, request.c_str());
  if (http.GET()){
    response = http.getString();
    http.end();
    if (response == "1") return 1;
    else return 0;
  }
  else{
    http.end();
    return 0;
  }
}
                               //********HERE********
#define WHICH_REQUEST   "http://192.168.137.110:8080/event/which?id=12"  // Server IP Change
uint8_t GetWhichString(user * card_id){
  String request = WHICH_REQUEST;
  uint64_t c_id = ((((uint64_t)card_id->id[0]) << 48) | (((uint64_t)card_id->id[1]) << 40) |
                  (((uint64_t)card_id->id[2]) << 32) | (((uint64_t)card_id->id[3]) << 24) | 
                  (((uint64_t)card_id->id[4]) << 16) | (((uint64_t)card_id->id[5]) << 8)  | (((uint64_t)card_id->id[6]) << 0));
  request += "&card_id=" + String(c_id);

  String response;
  WiFiClient client;
  HTTPClient http;
  http.begin(client, request.c_str());
  if (http.GET()){
    response = http.getString();
    http.end();
  }
  else{
    http.end();
    return 0;
  }
//  Serial.println(response);
  if (response == "Tech"){
    card_id->name = "Tech";
    card_id->status = "ADM";
    card_id->balance = -1;
    return 1;
  }
  else if (response == "error"){
    return 0;
  }
  else{
    uint8_t tmp[128] = { 0 };
    if (sscanf(response.c_str(), "%s %s %i User", tmp, tmp + 64, &(card_id->balance)) == 3){
      card_id->name = (const char *)tmp;
      card_id->name += " ";
      card_id->name += (const char *)(tmp + 64);
      card_id->status = "USR";
      return 1;  
    }
    else{
      return 0;
    }
  }
}
                               //********HERE********
#define TECH_REQUEST    "http://192.168.137.110:8080/event/tech?id=12"  // Server IP Change
uint8_t GetTechRequest(void){
  String request = TECH_REQUEST;
  WiFiClient client;
  HTTPClient http;
  http.begin(client, request.c_str());
  if (http.GET()){
    http.end();
    return 1;
  }
  else{
    http.end();
    return 0;
  }
}
                                 //********HERE********
#define BONUS_ADD_REQUEST "http://192.168.137.110:8080/event/bonus_add?id=12"  // Server IP Change
uint8_t GetBonusAddString(uint8_t * card_id, int8_t bonuses){
  String request = BONUS_ADD_REQUEST;
  uint64_t c_id = ((((uint64_t)card_id[0]) << 48) | (((uint64_t)card_id[1]) << 40) |
                  (((uint64_t)card_id[2]) << 32) | (((uint64_t)card_id[3]) << 24) | 
                  (((uint64_t)card_id[4]) << 16) | (((uint64_t)card_id[5]) << 8)  | (((uint64_t)card_id[6]) << 0));
  
  request += "&card_id=" + String(c_id) + "&value=" + String(bonuses);
  String resp;
  WiFiClient client;
  HTTPClient http;
  http.begin(client, request.c_str());
  if (http.GET()){
    resp = http.getString();
    http.end();
    if (resp == "ok"){
      return 1;
    }
    else{
      return 0;
    }
  }
  else{
    return 0;
  }
}

const char * ssid = "MyNetwork";  // << Input your Network SSID
const char * password = "MyNetworkPassword"; // << Input your Network Password

uint64_t lastTime = 0;
uint64_t timerDelay = 5000;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
  }
}

uint8_t servo[3] = { 0, 0, 0 };
uint8_t rgb[3] = { 0, 0, 0 };
uint8_t level[3] = { 0, 0, 0 };

uint8_t fill[3] = { 0xFF, 0xFF, 0xFF };

user user_data = {
  .name = "NONE",
  .status = "NONE",
  .id = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
  .balance = -1
};

int8_t bonus_add = 0;
uint8_t answer = 0;
uint8_t name_len = 0;
uint8_t cmd = 0;
uint8_t buffer[7] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

void loop() {
      START_LABEL:
    if(WiFi.status()== WL_CONNECTED){

      cmd = 0;
      Serial.readBytes(&cmd, 1);
      if ((cmd > 0x06) || (cmd < 0x01)) goto START_LABEL;
      
      if (cmd == NEW_REPORT){
        if (Serial.readBytes(servo, 3) != 3) goto START_LABEL;
        if (Serial.readBytes(rgb, 3) != 3) goto START_LABEL;
        if (Serial.readBytes(level, 3) != 3) goto START_LABEL;

        if (GetReportString(servo, rgb, level)){
          answer = 1;
        }
        else{
          answer = 0;
        }
        Serial.write(&answer, 1);
      }
      else if (cmd == NEW_FILL){
        if (Serial.readBytes(fill, 3) != 3) goto START_LABEL;

        if (GetFillString(fill)){
          answer = 1;
        }
        else{
          answer = 0;
        }
        Serial.write(&answer, 1);
      }
      else if (cmd == CHECK_ENABLE){
        if (GetEnable()){
          answer = 1;
        }
        else{
          answer = 0;
        }
        Serial.write(&answer, 1);
      }
      else if (cmd == CHECK_WHICH){
        if (Serial.readBytes(buffer, 7) != 7) goto START_LABEL;
        
        memcpy(user_data.id, buffer, 7);
        
        if (GetWhichString(&user_data)){
          answer = 1;
          name_len = user_data.name.length();
          Serial.write(&answer, 1);
          Serial.write(&name_len, 1);
          Serial.write(user_data.name.c_str(), name_len);
          Serial.write((uint8_t *)&(user_data.balance), 4);
        }
        else{
          answer = 0;
          Serial.write(&answer, 1);
        }
      }
      else if (cmd == TECH_NOTIFY){
        if (GetTechRequest()){
          answer = 1;
        }
        else{
          answer = 0;
        }
        Serial.write(&answer, 1);
      }
      else if (cmd == ADD_BONUS){
        if (Serial.readBytes(buffer, 7) != 7) goto START_LABEL;
        if (Serial.readBytes((uint8_t *)&bonus_add, 4) != 4) goto START_LABEL;
        
        memcpy(user_data.id, buffer, 7);
        
        if (GetBonusAddString(user_data.id, bonus_add)){
          answer = 1;
        }
        else{
          answer = 0;
        }
        Serial.write(&answer, 1);
      }
    }
    else {
      
    }

}
