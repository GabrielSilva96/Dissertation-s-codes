// Thesis: Modeling of artificial muscles made of nylon wire 
// Author: Gabriel Silva - 82084 - MEEC - IST Lisbon - 2018/2019 
// Description: Distance acquisition for model validation (for pyramid shaped and multilevel random signals)

// Define inputs
#define PWM_PIN 3
#define NR_SAMPLES 10    // Number of samples
#define trigPin 6
#define echoPin 5

// Variables
long duration;
float distance, dist, dist_0;
int calibration = 0;
unsigned long curr_t;
long k=1.0, on_time = 5000, off_time = 150000, start_t = 5000;
float j=0, pwm_value;
float Samples[NR_SAMPLES];
int i;
int n = 1;
int   amp = 0;
float last_dist = 0;
int count = 0;

void setup() { 
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
  pinMode(PWM_PIN, OUTPUT); 
}
void loop() 
{  
  // CALIBRATION
  
  if (calibration == 0){
    // acquire 10 samples
    for (i=0; i< NR_SAMPLES; i++) 
    { 
      Samples[i] = SONAR();    // Acquisition analog value of sonar readings
      delay(50);
    }
  
    // average of the samples
    dist_0 = 0;
    for (i=0; i< NR_SAMPLES; i++) 
    {
      dist_0 += Samples[i];
    }
    dist_0 /= NR_SAMPLES;               // Average of the acquired value
    calibration = 1;
    //Serial.println(dist_0);
    last_dist = dist_0;
  }

  curr_t = millis(); 
  
  // TEST UPON THE ACTUATOR
  
  // STAIR (PYRAMID SHAPED)
  /*
    if (curr_t<= 3000){
        pwm_value = 0; 
   }
    if (3000 < curr_t && curr_t <= 6000){
        pwm_value = 60;    
    }             
    if( 6000 < curr_t && curr_t <= 9000){
        pwm_value = 120; 
    }
    if( 9000 < curr_t && curr_t <= 12000){
       pwm_value = 180;
    }
    if (12000 < curr_t && curr_t <= 15000){
        pwm_value = 220; 
    }
    if (15000 < curr_t && curr_t <= 19000){
        pwm_value = 180; 
    }
    if (19000 < curr_t && curr_t <= 25000){
       pwm_value = 120; 
    }
    if (25000 < curr_t && curr_t <= 33000){
       pwm_value = 60; 
    }
    if (33000 < curr_t && curr_t <= 43000){
       pwm_value = 0; 
    }
  */
  
  // MULTILEVEL RANDOM SIGNAL
  
   if (curr_t<= 5000){
        pwm_value = 0; 
   }
    if (5000 < curr_t && curr_t <= 10000){
        pwm_value = 200;    
    }             
    if( 10000 < curr_t && curr_t <= 15000){
        pwm_value = 50; 
    }
    if( 15000 < curr_t && curr_t <= 20000){
       pwm_value = 235;
    }
    if (20000 < curr_t && curr_t <= 25000){
        pwm_value = 100; 
    }
    if (25000 < curr_t && curr_t <= 30000){
        pwm_value = 150; 
    }
    if (30000 < curr_t && curr_t <= 35000){
       pwm_value = 0; 
    }
    
  analogWrite(PWM_PIN, pwm_value);

  if (curr_t>= 35000) //43000 PYRAMIDE 35000 MULTILEVEL
  {
    analogWrite(PWM_PIN, 0);
    Serial.end();
    Serial.println("END"); 
  }
  
  dist = SONAR();// - dist_0;

  // correction to avoid outlier readings
  if (abs(last_dist - dist)> 0.25){
    Serial.print(curr_t);
    Serial.print("\t"); 
    Serial.print(pwm_value);
    Serial.print("\t");
    Serial.println(last_dist, 4);
  }
  else {

    Serial.print(curr_t);
    Serial.print("\t"); 
    Serial.print(pwm_value);
    Serial.print("\t");
    Serial.println(dist, 4);
    last_dist = dist; 
  }
  
  delay(50);
}

  // SONAR
  
double SONAR(){  
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2000);    

  // Sets the trigPin on HIGH state
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(7000);     
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance= duration*0.034/2;

  return distance;
}
