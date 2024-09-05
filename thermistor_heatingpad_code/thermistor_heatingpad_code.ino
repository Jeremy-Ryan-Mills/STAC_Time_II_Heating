int H_TOP_RIGHT = 3;
int H_TOP_LEFT = 11;
int H_BOTTOM_RIGHT = 9;
int H_BOTTOM_LEFT = 5;
int H_SMALL_PLATE = 10;
int T_TOP_RIGHT = A5;
int T_TOP_LEFT = A4;
int T_BOTTOM_RIGHT = A3;
int T_BOTTOM_LEFT = A1;
int T_SMALL_PLATE = A2;

// Analog Equivalents: CRITICAL_TEMP = 530; HIGH_TEMP = 450;
float CRITICAL_TEMP = 530; // 32C
float HIGH_TEMP = 450; // 40C

int active_heater = -1;
float min_temp = 200;
float max_temp = 0;
int last_digital_write = 0;
int count = 0;


int getThermistorPin(int i) {
    if (i == 0) {
      return T_BOTTOM_LEFT;
    }
    else if (i == 1) {
      return T_SMALL_PLATE;
    }
    else if (i == 2) {
      return T_BOTTOM_RIGHT;
    }
    else if (i == 3) {
      return T_TOP_LEFT;
    }
    else if (i == 4) {
      return T_TOP_RIGHT;
    }
}

int getHeaterPin(int i) {
    if (i == 0) {
      return H_BOTTOM_LEFT;
    }
    else if (i == 1) {
      return H_SMALL_PLATE;
    }
    else if (i == 2) {
      return H_BOTTOM_RIGHT;
    }
    else if (i == 3) {
      return H_TOP_LEFT;
    }
    else if (i == 4) {
      return H_TOP_RIGHT;
    }
}

int getDelayValue(int i) {
  if (i == 0) {
      return 30;
    }
    else if (i == 1) {
      return 8;
    }
    else if (i == 2) {
      return 100;
    }
    else if (i == 3) {
      return 30;
    }
    else if (i == 4) {
      return 6;
    }
}

void setup() {
    Serial.begin(9600); // Serial Initialization at 9600 baud rate
}

void loop() {
  

    for(int i = 0; i < 5; i++) {
      float temp = analogRead(getThermistorPin(i));
      Serial.println(temp);
      if (temp > 490) {
        digitalWrite(getHeaterPin(i), HIGH);
        Serial.println(" Below Critical: Turning on heater");
      }
      else {
        digitalWrite(getHeaterPin(i), LOW);
        Serial.println(" Above Critical: Turning off heater");
      }
    }
    /*
    // Feedback Loop Code
    float high_buffer_constant = 40;   // Change depending on how fast or slow it takes the heating pads to turn on and get hot
    float crit_buffer_constant = 5;

    
    for(int i = 0; i < 5; i++) {
        float temp = analogRead(getThermistorPin(i)); // Get current temp
        Serial.println(temp);
        
        if (temp >= HIGH_TEMP + high_buffer_constant && temp <= CRITICAL_TEMP - crit_buffer_constant) {
          // If the temperature is in the desired range, turn the heater pad on and off to maintain temperature
          last_digital_write = 1 - last_digital_write;
          if (count % getDelayValue(i) == 0) {
            digitalWrite(getHeaterPin(i), HIGH);
            count++;
          }
          else {
            digitalWrite(getHeaterPin(i), LOW);
            count++;
          }
          Serial.println(" In Range: Maintaing Temperature");
        }
        else if (temp < HIGH_TEMP + high_buffer_constant) {
          // If the temperature read is more than the max, shut off the heating pads
          digitalWrite(getHeaterPin(i), LOW);
          last_digital_write = 0;
          Serial.println(" Above Critical: Turning off heater");
        }
        else if (temp > CRITICAL_TEMP - crit_buffer_constant) {
          // If the temperature falls below the critical temperature, turn on the heating pad to high
          digitalWrite(getHeaterPin(i), HIGH);
          last_digital_write = 1;
          Serial.println(" Below Critical: Turning on heater");
        }
        


        // Records the min and max temperature that any thermistor gets to
        if (temp < min_temp) {
          min_temp = temp;
        }
        if (temp > max_temp) {
          max_temp = temp;
        }
    }
    */
    
    Serial.println("------------------------------------------");
    delay(1000);
    
    
}

// Relationship between Temperature (Celcius) and Voltage is linear
// Temp = -18.61V + 80.88 where V is voltage
// V = (5analogData / 1024)
float readTemp(int pin) { 
    return  -18.61 * ((5 * analogRead(pin)) / 1024) + 80.88; 
}