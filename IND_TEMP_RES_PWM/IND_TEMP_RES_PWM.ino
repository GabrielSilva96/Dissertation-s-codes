// Thesis: Modeling of artificial muscles made of nylon wire 
// Author: Gabriel Silva - 82084 - MEEC - IST Lisbon - 2018/2019 
// Description: Measure actuator resistance, to compute its temperature indirectly, with PWM drive circuit

// Define inputs
#define INPUT_PIN A0      // Analog input pin
#define ENABLE_MES 13     // enable recuitment
#define PWM_PIN 9

// Variables
float pwm_value;
unsigned long curr_t;
float volts, volts_acq;
int i = 1;

void setup()
{
  pinMode(ENABLE_MES, OUTPUT); 
  pinMode(PWM_PIN, OUTPUT); 
  Serial.begin(9600);
}

void loop()
{
  curr_t = millis();
  Serial.print(curr_t);
  Serial.print("\t");
  
    
  if (curr_t >= 20000)
  {
    digitalWrite(ENABLE_MES, HIGH);
    Serial.println("END");  
    Serial.end();
  }

 // TEST UPON THE ACTUATOR
   
  else{
    if (curr_t >= 2000 && curr_t < 20000) 
    {
      digitalWrite(ENABLE_MES, LOW);

      pwm_value =  0;
      analogWrite(PWM_PIN, pwm_value);
      
      volts_acq = analogRead(INPUT_PIN);      // Acquisition analog value of voltage
      delay(10);
      volts = (5.00 * volts_acq) / 1023.00;   // Conversion to voltage 
      Serial.print("ON");
      Serial.print("\t");
      Serial.println(volts, 4);
    }
    if (curr_t < 2000) 
    {
      digitalWrite(ENABLE_MES, HIGH);
      
      pwm_value =  255;
      analogWrite(PWM_PIN, pwm_value);
      
      volts_acq = analogRead(INPUT_PIN);      // Acquisition analog value of voltage
      delay(10);
      volts = (5.00 * volts_acq) / 1023.00;   // Conversion to voltage 
      Serial.print("OFF");
      Serial.print("\t");
      Serial.println(volts, 4);
    }
  }
}
