
void setup() {
  Serial.begin(115200);
  vTaskDelay(500 / portTICK_PERIOD_MS);

  SerialAT.begin(115200, SERIAL_8N1, RXD2, TXD2);
  vTaskDelay(500 / portTICK_PERIOD_MS);

  
  //SIM_7672
  Serial.println("Modem Reset, Please Wait");
  SerialAT.println("AT+CRESET");
  vTaskDelay(1000 / portTICK_PERIOD_MS);

  Serial.println("Echo Off");
  SerialAT.println("ATE0");   

  rxString = SerialAT.readString();
  Serial.print("Got: ");
  Serial.println(rxString);
  rx = rxString.indexOf("OK");
  if (rx != -1)
    Serial.println("Modem Ready");
  delay(1000);

  Serial.println("SIM card check");
  SerialAT.println("AT+CPIN?"); //9s
  rxString = SerialAT.readString();
  Serial.print("Got: ");
  Serial.println(rxString);
  rx = rxString.indexOf("+CPIN: READY");
  if (rx != -1)
    Serial.println("SIM Card Ready");
  delay(1000);

  String name = modem.getModemName();
  delay(500);
  Serial.println("Modem Name: " + name);

  vTaskDelay(1000 / portTICK_PERIOD_MS);
  //SIM_7672

  //blynk
  Blynk.begin(auth, modem, apn, user, pass);
  //blynk


  //oled display
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;) ; // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  display.setTextSize(4);             // Draw 4X-scale text
  display.setTextColor(SSD1306_WHITE);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  delay(2000);
  //oled display

  // //heart max30102
  Serial.println("Initializing...");
  

  // Initialize sensor
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST, 0x57)) //Use default I2C port, 400kHz speed
  {
    
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }
  Serial.println("Place your index finger on the sensor with steady pressure.");

  particleSensor.setup(); //Configure sensor with default settings
  //particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
  //particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED
  //heart max30102


  // Create tasks
  xTaskCreatePinnedToCore(sensorRead, "Read Heart Rate", 2048, NULL, 1, &Task1,0);
  delay(500); 

  xTaskCreatePinnedToCore(displayTask, "Display Heart Rate", 4096, NULL, 1, &Task2,1);
  delay(500); 

}





