#define IN1 4  // PD4 
#define IN2 2  // PD2 
#define ENA 3  // PD3
#define IN3 7  // PD7
#define IN4 8  // PD8 
#define ENB 6  // PD6 
#define LED 13 // Built-in LED

int motorSpeedA = 0;
int motorSpeedB = 0;

// initializing pins
void setup() {
  // motor pins
  pinMode(IN1, OUTPUT);  
  pinMode(IN2, OUTPUT);  
  pinMode(IN3, OUTPUT);  
  pinMode(IN4, OUTPUT); 
  // PWM pins for motor speed 
  pinMode(ENA, OUTPUT);  
  pinMode(ENB, OUTPUT);
  // LED pin for indicator
  pinMode(LED, OUTPUT);

  // Ensure all motors are stopped at the beginning
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);  // Motor A speed = 0
  analogWrite(ENB, 0);  // Motor B speed = 0
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  int xAxis = analogRead(A1); // Read x-axis
  int yAxis = analogRead(A2); // Read y-axis

  // Y axis used to drive forward and backward
  if (yAxis < 470) {
    // Motor backward
    digitalWrite(LED, HIGH);    
    digitalWrite(IN1, LOW);    
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);     
    digitalWrite(IN4, HIGH);
    digitalWrite(LED, LOW); 
    // Convert the declining Y-axis readings for going backward from
    // 470 to 0 into 0 to 255 value for the PWM signal for increasing the motor speed
    motorSpeedA = map(yAxis, 470, 0, 0, 255);
    motorSpeedB = map(yAxis, 470, 0, 0, 255);
  } else if (yAxis > 550) {
    // motor forward
    digitalWrite(LED, HIGH); 
    digitalWrite(IN1, HIGH); 
    digitalWrite(IN2, LOW);      
    digitalWrite(IN3, HIGH);     
    digitalWrite(IN4, LOW);      
    digitalWrite(LED, LOW);
    // Convert the increasing Y-axis readings for going forward from
    // 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed
    motorSpeedA = map(yAxis, 550, 1023, 0, 255);
    motorSpeedB = map(yAxis, 550, 1023, 0, 255);
  } else {
    // if joystick is at the center

    // motor stops
    motorSpeedA = 0;
    motorSpeedB = 0;
  }

  // x axis used for left and right controls

  // turning left
  if (xAxis < 470) {
    // Convert the declining X-axis readings from 470 to 0 into increasing 0 to 255 value
    int xMapped = map(xAxis, 470, 0, 0, 255);
    // Move to left - decrease left motor speed, increase right motor speed
    motorSpeedA = motorSpeedA - xMapped;
    motorSpeedB = motorSpeedB + xMapped;
    // Confine the range from 0 to 255
    if (motorSpeedA < 0) {
      motorSpeedA = 0;
    }
    if (motorSpeedB > 255) {
      motorSpeedB = 255;
    }
  }
 
  // turning right
  if (xAxis > 550 ) {
    // Convert the increasing X-axis readings from 550 to 1023 into increasing 0 to 255 value
    int xMapped = map(xAxis, 550, 1023, 0, 255);
    // Move to right - increase left motor speed, decrease right motor speed
    motorSpeedA = motorSpeedA + xMapped;
    motorSpeedB = motorSpeedB - xMapped;
    // Confine the range from 0 to 255
    if (motorSpeedA > 255) {
      motorSpeedA = 255;
    }
    if (motorSpeedB < 0) {
      motorSpeedB = 0;
    }
  }

  // Prevent buzzing at low speeds
  if (motorSpeedA < 70) {
    motorSpeedA = 0;
  }
  if (motorSpeedB < 70) {
    motorSpeedB = 0;
  }
  
  // Send PWM signals to motors
  analogWrite(ENA, motorSpeedA); //send PWM to motor A
  analogWrite(ENB, motorSpeedB); //send PWM to motor B
}
