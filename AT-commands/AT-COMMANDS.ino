String incomingCommand = ""; 
bool blinkingState = false; 
int blinkPeriod = 1000; 

void setup() {
  Serial.begin(9600); 
  pinMode(LED_BUILTIN, OUTPUT); 
  digitalWrite(LED_BUILTIN, LOW); 
  Serial.println("Hello Arduino\n");
}

void loop() {
  if (Serial.available() > 0) { 
    incomingCommand = Serial.readStringUntil('\r'); 
    incomingCommand.trim();
    
    if (incomingCommand == "AT") {
      Serial.println("OK\r\n"); 
    } 
    
    else if (incomingCommand == "LED=ON") {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("OK\r\n");
    }
    
    else if (incomingCommand == "LED=OFF") {
      digitalWrite(LED_BUILTIN, LOW); 
      Serial.println("OK\r\n");
    } 
    
    else if (incomingCommand == "BLINKING=ON") {
      blinkingState = true; 
      Serial.println("OK\r\n");
    } 
    
    else if (incomingCommand == "BLINKING=OFF") {
      blinkingState = false; 
      Serial.println("OK\r\n");
    } 
    
    else if (incomingCommand.startsWith("PERIOD=")) {
      int equalsPosition = incomingCommand.indexOf('=');
      String periodValue = incomingCommand.substring(equalsPosition + 1);
      blinkPeriod = periodValue.toInt(); 
      Serial.print(periodValue);
      Serial.println("-OK\r\n");
    } 
    
    else if (incomingCommand == "STATUS?") {
      if (blinkingState) {
        Serial.print("BLINKING, PERIOD=");
        Serial.print(blinkPeriod);
        Serial.println("-OK\r\n");
      } else {
        if (digitalRead(LED_BUILTIN) == HIGH) {
          Serial.println("ON\r\n");
        } else {
          Serial.println("OFF\r\n");
        }
      }
    } else {
      Serial.println("Command not recognized\r\n");
    }
  }

  if (blinkingState) {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); 
    delay(blinkPeriod);
  }
}
