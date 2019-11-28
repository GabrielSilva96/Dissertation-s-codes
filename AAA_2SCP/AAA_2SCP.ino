// Thesis: Modeling of artificial muscles made of nylon wire 
// Author: Gabriel Silva - 82084 - MEEC - IST Lisbon - 2018/2019 
// Description: Angle variation acquisition with the AAA using 2 SCP actuators

// Define inputs
#define PWM_PIN 3
#define PWM_PIN_ANTA 9

// Variables
unsigned long curr_t;
long k=1.0, on_time = 5000, off_time = 20000;
float j=0, pwm_value;

void setup() { 
  Serial.begin(9600);
  pinMode(PWM_PIN, OUTPUT); 
}
void loop() 
{  
  curr_t = millis();   
  
  Serial.print(curr_t);
  Serial.print("\t"); 
  
  if (curr_t>= on_time*3 + off_time*3)
  {
    analogWrite(PWM_PIN, 0);
    analogWrite(PWM_PIN_ANTA, 0);
    Serial.end();
    Serial.println("END"); 
  }

  // TEST UPON THE AAA
  
  if (curr_t<= on_time*k + off_time*(k-1.0))
  {
    pwm_value =  0;
    if (curr_t>= on_time + off_time){
      pwm_value =  225;
    }
    analogWrite(PWM_PIN, pwm_value);
    analogWrite(PWM_PIN_ANTA, 0);
    Serial.print(pwm_value);
    Serial.print("\t"); 
    Serial.println("AGON");
  }
  else
  { 
    pwm_value = 0;
    if (k>1){
      pwm_value =  225;
    }
    if (curr_t>= on_time*k + off_time*k)
    {
      k += 1.0;  
      j += 1;
    }
    analogWrite(PWM_PIN_ANTA, pwm_value);
    analogWrite(PWM_PIN, 0);
    Serial.print(pwm_value);
    Serial.print("\t"); 
    Serial.println("ANTA");
  }
}
