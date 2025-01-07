void loop() {} 

//Task1code
void sensorRead( void * pvParameters )
{
  while(1){

    unsigned long startTime = millis();

    while(millis() - startTime< 10000)
    {
      long irValue = particleSensor.getIR();
      if (checkForBeat(irValue) == true)
      {
        //We sensed a beat!
        long delta = millis() - lastBeat;
        lastBeat = millis();
        beatsPerMinute = 60 / (delta / 1000.0);

        if (beatsPerMinute < 255 && beatsPerMinute > 20)
        {
          rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
          rateSpot %= RATE_SIZE; //Wrap variable

          //Take average of readings 
          beatAvg = 0;
          for (byte x = 0 ; x < RATE_SIZE ; x++)
            beatAvg += rates[x];
          beatAvg /= RATE_SIZE;
        } 
      } 
      avgheartRate = beatAvg;
      // vTaskDelay(250/portTICK_PERIOD_MS);
      if (irValue < 50000){
        Serial.print(" No finger?");
        Serial.println();
      }
    }
    // Serial.print(avgheartRate);               
    // Serial.println("BPM111111111111");


    unsigned long startTime2 = millis();

    while(millis() - startTime2 < 10000)
    {
    float tempC = tempSensor.getTemperature();               // Read temperature in Celsius
    temperature = tempC * 9.0 / 5.0 + 32.0;                  // Convert to Fahrenheit
    // Serial.print(temperature, 2);                                  // Print temperature in Fahrenheit
    // Serial.println("'F");
    }

    // Serial.print(temperature, 2);                                  // Print temperature in Fahrenheit
    // Serial.println("'F1111111111111111111");


  }
}

  
void displayTask( void * pvParameters ){
  while(1){

    Blynk.run();

    Serial.print(avgheartRate);                               
    Serial.println("BPM");
    vTaskDelay(100 / portTICK_PERIOD_MS); 
    Blynk.virtualWrite(V0, avgheartRate); // Send count to Virtual Pin V0 in Blynk
    

    display.clearDisplay(); // Clear the display
    display.setTextSize(2); // Set text size
    display.setCursor(0, 0); // Set cursor position

    display.print("Heart_Rate ");
    display.print(avgheartRate);
    display.print(" BPM");
    display.display(); // Update the display
    vTaskDelay(5000 / portTICK_PERIOD_MS); // Refresh every 2 seconds


    //
    Serial.print(temperature, 2);   
    Serial.println("'F");
    vTaskDelay(100 / portTICK_PERIOD_MS); // Refresh every 2 seconds
    Blynk.virtualWrite(V1, temperature); // Send count to Virtual Pin V0 in Blynk

    display.clearDisplay(); // Clear the display
    display.setTextSize(2); // Set text size
    display.setCursor(0, 0); // Set cursor position

    display.print("Temp ");
    display.print(temperature);
    display.print(" F");
    display.display(); // Update the display
    vTaskDelay(5000 / portTICK_PERIOD_MS); // Refresh every 2 seconds
  
  }
 }

