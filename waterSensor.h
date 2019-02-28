#include "Arduino.h"
#include "AppDebug.h"
#include "ESP8266WiFi.h"
#include "ESP8266WebServer.h"
#include "ESP8266mDNS.h"
#include "ArduinoJson.h"
#include "Ticker.h"
#include "EEPROM.h"
#include "DallasTemperature.h"
#include "OneWire.h"
#include <ESP8266HTTPClient.h>


#define LED_TEST_AP 2 // D4 onchip GPIO2
#define PIN_CONFIG D3       // D3 flash GPIO0
#define PIN_WATER 4


#define RESPONSE_LENGTH 512     //do dai data nhan ve tu tablet
#define EEPROM_WIFI_SSID_START 0
#define EEPROM_WIFI_SSID_END 32
#define EEPROM_WIFI_MAX_CLEAR 512
#define EEPROM_WIFI_PASS_START 33
#define EEPROM_WIFI_PASS_END 64
#define EEPROM_WIFI_IP_START 65
#define EEPROM_WIFI_IP_END 95
#define EEPROM_WIFI_IP_SEND_START 96
#define EEPROM_WIFI_IP_SEND_END 125


#define SSID_PRE_AP_MODE "AvyInterior-"
#define PASSWORD_AP_MODE "123456789"

#define HTTP_PORT 80

#define CONFIG_HOLD_TIME 3000
#define TIME_RESEND 1000
#define TIME_KEEP_SENDING 5000

ESP8266WebServer server(HTTP_PORT);
 



//normal mode
void handleOk();
void handleRoot();
void getStatus();
void SetupNomalMode();
void SetupNetwork();
void StartNormalSever();
void tickerupdate();


//Config Mode
void SetupConfigMode();             //phat wifi
void StartConfigServer();           //thiet lap sever
void ConfigMode();                  //nhan data tu app
void setLedApMode();                //hieu ung led
String GetFullSSID();
bool connectToWifi(String nssid, String npass, String ip, String ipsend);
bool testWifi(String esid, String epass);
void detachIP(String ip);
void setupIP();
unsigned long ConfigTimeout;
uint8_t first_octet;
uint8_t second_octet;
uint8_t third_octet;
uint8_t fourth_octet;
uint8_t red_before, red_after;
uint8_t green_before, green_after;
uint8_t blue_before, blue_after;
uint32_t Time = 0;


String esid, epass, eip, eipSend;
bool Flag_Normal_Mode = true;
bool isHaveWater = false;
bool isCanSending = true;
// unsigned long Pul_Motor;
// unsigned long test_time, time_start_speed;


Ticker tickerSetApMode(setLedApMode, 200, 0);   //every 200ms
