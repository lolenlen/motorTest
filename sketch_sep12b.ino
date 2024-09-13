#define IN1 2  // PD2 
#define IN2 3  // PD3 
#define ENA 6  // PD6 
#define LED 13 // Built-in LED

// Initialize pins
void setup() {
  pinMode(IN1, OUTPUT);  // Motor pin
  pinMode(IN2, OUTPUT);  // Motor pin
  pinMode(ENA, OUTPUT);  // PWM pin for motor speed
  pinMode(LED, OUTPUT);  // LED pin for indicator
}

void loop() {
  // Motor "Forward" Half speed
  digitalWrite(LED, HIGH);     // LED ON
  digitalWrite(IN1, HIGH);     // Forward direction
  digitalWrite(IN2, LOW);      
  analogWrite(ENA, 128);       // 50% speed (PWM 0-255)
  delay(1000);
  digitalWrite(LED, LOW);      // LED OFF

  // Motor Stop
  analogWrite(ENA, 0);
  delay(1000);          

  // Motor "Forward" Top speed
  digitalWrite(LED, HIGH);    
  digitalWrite(IN1, HIGH);     // Forward direction
  digitalWrite(IN2, LOW);     
  analogWrite(ENA, 255);       // 100% speed
  delay(1000);
  digitalWrite(LED, LOW);   

  // Motor Stop
  analogWrite(ENA, 0);
  delay(2000);  

  // Motor "Reverse" Half speed
  digitalWrite(LED, HIGH);    
  digitalWrite(IN1, LOW);      // Reverse direction (swap IN1/IN2)
  digitalWrite(IN2, HIGH);     
  analogWrite(ENA, 128);       // 50% speed
  delay(3000);
  digitalWrite(LED, LOW);     

  // Motor Stop
  analogWrite(ENA, 0);
  delay(1000);          

  // Motor "Reverse" Top speed
  digitalWrite(LED, HIGH);   
  digitalWrite(IN1, LOW);      // Reverse direction (swap IN1/IN2)
  digitalWrite(IN2, HIGH);    
  analogWrite(ENA, 255);       // 100% speed
  delay(3000);
  digitalWrite(LED, LOW);     

  // Motor Stop
  analogWrite(ENA, 0); 
  delay(1000);        
}
