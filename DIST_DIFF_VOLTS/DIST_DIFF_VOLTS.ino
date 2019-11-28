// Thesis: Modeling of artificial muscles made of nylon wire 
// Author: Gabriel Silva - 82084 - MEEC - IST Lisbon - 2018/2019 
// Description: Distance acquisition for different voltages

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
long k=1.0, on_time = 10000, off_time = 30000;
float j=0, pwm_value;
float Samples[NR_SAMPLES];
int i;
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

  if (curr_t<= on_time*k + off_time*(k-1.0))
  {
    pwm_value = 0;
    if (curr_t>= on_time + off_time){
      pwm_value =  100+25*(j-1);
    } 
   if (pwm_value == 250){
      pwm_value = 245;
   }
  }
  else
  { 
    pwm_value = 0;
    if (curr_t>= on_time*k + off_time*k)
    {
      k += 1.0;  
      j += 1;
    }
  }
  analogWrite(PWM_PIN, pwm_value);

  if (curr_t>= on_time*8 + off_time*8) //7
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
