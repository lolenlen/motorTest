#define IN1 4  // PD4 
#define IN2 2  // PD2 
#define ENA 3  // PD3
#define IN3 7  // PD7
#define IN4 8  // PD8 
#define ENB 6  // PD6 
#define LED 13 // Built-in LED
  
int motorSpeedA = 0;
int motorSpeedB = 0;
int trigPin = 9; //trigger
int echoPin =10; //echo
long duration, cm;
unsigned long previousMillis = 0;
long interval = 1; //interval at which scan milliseconds

void Stop() {
  digitalWrite(LED, HIGH);    
  digitalWrite(IN1, HIGH); 
  digitalWrite(IN2, LOW);      
  digitalWrite(IN3, HIGH);     
  digitalWrite(IN4, LOW);       
  analogWrite(ENA, 0);       
  analogWrite(ENB, 0);
  digitalWrite(LED, LOW);  
}

void Forward() {
  // motor speed 100% 255 to 0% 0
  digitalWrite(LED, HIGH);    
  digitalWrite(IN1, HIGH); 
  digitalWrite(IN2, LOW);      
  digitalWrite(IN3, HIGH);     
  digitalWrite(IN4, LOW);       
  analogWrite(ENA, 255);       
  analogWrite(ENB, 255);
  digitalWrite(LED, LOW);   
}

void Backward() {
  digitalWrite(LED, HIGH);   
  digitalWrite(IN1, LOW);      // Backward direction (swap IN1/IN2 - IN3/IN4)
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);     
  digitalWrite(IN4, HIGH);    
  analogWrite(ENA, 255);       
  analogWrite(ENB, 255); 
  digitalWrite(LED, LOW);  
}

void Right() {
  digitalWrite(LED, HIGH);   
  digitalWrite(IN1, HIGH);      // Turn the motors' direction in to opposites
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);     
  digitalWrite(IN4, HIGH);    
  analogWrite(ENA, 125);       
  analogWrite(ENB, 170); 
  digitalWrite(LED, LOW);     
}

void Left() {
  digitalWrite(LED, HIGH);   
  digitalWrite(IN1, LOW);     
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);     
  digitalWrite(IN4, LOW);    
  analogWrite(ENA, 170);       
  analogWrite(ENB, 125); 
  digitalWrite(LED, LOW); 
}

// initializing pins
void setup() {
  //motor pins
  pinMode(IN1, OUTPUT);  
  pinMode(IN2, OUTPUT);  
  pinMode(IN3, OUTPUT);  
  pinMode(IN4, OUTPUT); 
  // PWM pins for motor speed 
  pinMode(ENA, OUTPUT);  
  pinMode(ENB, OUTPUT);
  // LED pin for indicator
  pinMode(LED, OUTPUT); 

  // ultrasonic pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) 
  {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
}
cm = (duration/2) / 29.1;
//cm is set at 1196 if no signal is received by the echopin due to one of the sensors being covered in a way that makes it impossible for the wave to go through
   if(cm > 30)
   {
    Forward();
    //stop digitalWrite(, LOW)
   }
   else
   {
    Stop();
    Left();

    //drive forward digitalWrite(,HIGH)

   }
   Serial.print(cm);
   Serial.print('\n');

}

