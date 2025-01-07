#include <Wire.h>
#define RXD2 17    
#define TXD2 16 
#define SerialAT Serial1
#define TINY_GSM_MODEM_SIM7600

// oled display

//#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
// oled display



//max30102
#include "MAX30105.h"
#include "heartRate.h"

MAX30105 particleSensor;

const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred

float beatsPerMinute;
int beatAvg;
//max30102



unsigned long previousMillis = 0;  // Stores the last time the first function was run
const long interval = 5000;   

TaskHandle_t Task1;
TaskHandle_t Task2;



//blynk
#define BLYNK_TEMPLATE_ID "TMPL3NlzabQD-"
#define BLYNK_TEMPLATE_NAME "sensor data"
#define BLYNK_AUTH_TOKEN "5gztGAF60XlQWHBl3dGJYdLL_qfaHB4D"


#include <BlynkSimpleTinyGSM.h>
char auth[] = BLYNK_AUTH_TOKEN;
String rxString;
//blynk


//SIM_7672


char apn[]  = "";
char user[] = "";
char pass[] = "";

TinyGsm modem(SerialAT);
int rx = -1;
//SIM_7672

//MAX30205 
#include "Protocentral_MAX30205.h"
MAX30205 tempSensor;
//MAX30205 


// Variables for sensor data
float temperature = 0.0;
int avgheartRate = 0;
int spo2 = 0;