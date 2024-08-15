//In the code before void setup() we have initialised the pin numbers for the sensors and Motor drivers
// FOR ULTRASONIC SENSORS
const int SONAR_M_PingPin = 16;
const int SONAR_M_TrigPin = 17;
const int SONAR_L_PingPin = 14;
const int SONAR_L_TrigPin = 15;
const int SONAR_R_PingPin = 18;
const int SONAR_R_TrigPin = 19;

// FOR DC MOTORS CONTROLLERS
const int L298N_F_ENA = 2;
const int L298N_FL_O1 = 6;
const int L298N_FL_O2 = 7;
const int L298N_FR_O4 = 9;
const int L298N_FR_O3 = 8;
const int L298N_F_ENB = 3;

const int L298N_B_ENA = 4; 
const int L298N_BL_O1 = 10;
const int L298N_BL_O2 = 11; 
const int L298N_BR_O4 = 13;
const int L298N_BR_O3 = 12; 
const int L298N_B_ENB = 5;

//Setting 3 different types of speeds for varying the analog speed values out of the maximum 255;
int Forward_Speed = 200; 
int Speed = 150;
int SLOW_Speed=100;


void setup() {
  Serial.begin(9600);//To specify baud rate
  
  //defining the INPUT or OUTPUT functions of the pins to either provide or receive voltages
  pinMode(SONAR_M_PingPin, INPUT);
  pinMode(SONAR_M_TrigPin, OUTPUT);
  pinMode(SONAR_L_PingPin, INPUT);
  pinMode(SONAR_L_TrigPin, OUTPUT);
  pinMode(SONAR_R_PingPin, INPUT);
  pinMode(SONAR_R_TrigPin, OUTPUT);

  pinMode(L298N_F_ENA, OUTPUT);
  pinMode(L298N_FL_O1, OUTPUT);
  pinMode(L298N_FL_O2, OUTPUT);
  pinMode(L298N_FR_O4, OUTPUT);
  pinMode(L298N_FR_O3, OUTPUT);
  pinMode(L298N_F_ENB, OUTPUT);

  pinMode(L298N_B_ENA, OUTPUT);
  pinMode(L298N_BL_O1, OUTPUT);
  pinMode(L298N_BL_O2, OUTPUT);
  pinMode(L298N_BR_O4, OUTPUT);
  pinMode(L298N_BR_O3, OUTPUT);
  pinMode(L298N_B_ENB, OUTPUT);
}

void loop() {
  // Measure distance for the front sensor
  long t1, x;//initialising
  //an initial LOW voltage is provided so that a clean HIGH is produced
  digitalWrite(SONAR_M_TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(SONAR_M_TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(SONAR_M_TrigPin, LOW);
  //calculate the time between sending the signal and receiving
  t1 = pulseIn(SONAR_M_PingPin, HIGH);
  //convert the time to distance using the function microsecondsToCentimeters 
  x = microsecondsToCentimeters(t1);
  Serial.print(x);
  Serial.print(" cm (Front)\n");

  // Measure distance for the left sensor
  //similarly
  long t2, y;
  digitalWrite(SONAR_L_TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(SONAR_L_TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(SONAR_L_TrigPin, LOW);
  t2 = pulseIn(SONAR_L_PingPin, HIGH);
  y = microsecondsToCentimeters(t2);

  Serial.print(y);
  Serial.print(" cm (Left)\n");

  // Measure distance for the right sensor
  long t3, z;
  digitalWrite(SONAR_R_TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(SONAR_R_TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(SONAR_R_TrigPin, LOW);
  t3 = pulseIn(SONAR_R_PingPin, HIGH);
  z = microsecondsToCentimeters(t3);

  Serial.print(z);
  Serial.print(" cm (Right)\n");

  // Decision-making based on sensor readings
  if (x < 100) { // Object is close in front
    if (y > z) { // More space on the left
      rightturn();
    } else { // More space on the right
      leftturn();
    }
  } else { // No obstacle in front
    forward();
  }

  delay(100); // 
}

void forward() {
  //defining code for moving forward
  analogWrite(L298N_F_ENA, Forward_Speed);//analogWrite() function is used to specify speed
  analogWrite(L298N_F_ENB, Forward_Speed);
  digitalWrite(L298N_FL_O1, HIGH);
  digitalWrite(L298N_FL_O2, LOW);//HIGH and LOW is provided to create a potential for current flow
  digitalWrite(L298N_FR_O4, HIGH);
  digitalWrite(L298N_FR_O3, LOW);

  analogWrite(L298N_B_ENA, Forward_Speed);
  analogWrite(L298N_B_ENB, Forward_Speed);
  digitalWrite(L298N_BL_O1, HIGH);
  digitalWrite(L298N_BL_O2, LOW);
  digitalWrite(L298N_BR_O4, HIGH);
  digitalWrite(L298N_BR_O3, LOW);
}

void leftturn() {
  // Code for moving left
  analogWrite(L298N_F_ENA, Speed);
  analogWrite(L298N_F_ENB, Speed);
  digitalWrite(L298N_FL_O1, LOW);//to stop the Front Left motor
  digitalWrite(L298N_FL_O2, LOW);
  digitalWrite(L298N_FR_O4, HIGH);
  digitalWrite(L298N_FR_O3, LOW);

  analogWrite(L298N_B_ENA, SLOW_Speed);//Speed is reduced for the Back Left in order to make a more precise turn
  analogWrite(L298N_B_ENB, Speed);
  digitalWrite(L298N_BL_O1, HIGH);
  digitalWrite(L298N_BL_O2, LOW);
  digitalWrite(L298N_BR_O4, HIGH);
  digitalWrite(L298N_BR_O3, LOW);
}

void rightturn() {
  analogWrite(L298N_F_ENA, Speed);
  analogWrite(L298N_F_ENB, Speed);
  digitalWrite(L298N_FL_O1, HIGH);
  digitalWrite(L298N_FL_O2, LOW);
  digitalWrite(L298N_FR_O4, LOW);
  digitalWrite(L298N_FR_O3, LOW);

  analogWrite(L298N_B_ENA, Speed);
  analogWrite(L298N_B_ENB, SLOW_Speed);
  digitalWrite(L298N_BL_O1, HIGH);
  digitalWrite(L298N_BL_O2, LOW);
  digitalWrite(L298N_BR_O4, HIGH);
  digitalWrite(L298N_BR_O3, LOW);
}

void backward() {

  analogWrite(L298N_F_ENA, Speed);
  analogWrite(L298N_F_ENB, Speed);
  digitalWrite(L298N_FL_O1, LOW);
  digitalWrite(L298N_FL_O2, HIGH);
  digitalWrite(L298N_FR_O4, LOW);
  digitalWrite(L298N_FR_O3, HIGH);

  analogWrite(L298N_B_ENA, Speed);
  analogWrite(L298N_B_ENB, Speed);
  digitalWrite(L298N_BL_O1, LOW);
  digitalWrite(L298N_BL_O2, HIGH);
  digitalWrite(L298N_BR_O4, LOW);
  digitalWrite(L298N_BR_O3, HIGH);
}
//Defining the function for converting microseconds output to Centimeters
long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}