# Dissertation-s-codes
Main files used for several experiments along the dissertation

These files were loaded to the Arduino to execute the majority of the experiments described along the dissertation.
There is also a MATLAB file that was created in order to acquire the data, from the Arduino, so it could be processed.

ARDUINO files:

File name --------- Description --------------------------------- chapter ------------------------- 

REV_COUNTER 	    - Motor revolution counter 			- twisting and coiling

PWM_INCREMENTS    - PWM increments until maximum value		- durability tests

PWM_INC_DEC	      - Continuous PWM increments until the maximum - acquisition methods
		    value, followed by decrements 		

PWM_INC_ZERO  	  - Continuous PWM increments, followed by      - acquisition methods
		    return to 0 PWM		
		
DIST_DIFF_WEIGHTS - Distance acquisition for different weights	- elasticity tests

DIST_DIFF_VOLTS   - Distance acquisition for different voltages	- elasticity tests

TRAIN		          - Training stage				- annealing and training

DIST_TM 	        - Distance acquisition for the TM model	- acquiring and processing data

TEMP_TE 	        - Temperature acquisition for the TE model	- acquiring and processing data

MODEL_VALID 	    - Distance acquisition for model validation   - model validation
		    (for pyramid shaped and multilevel random 
		    signals)  

AAA_1SCP 	        - Angle variation acquisition with the AAA    - contraction/expansion enhancement
		    using 1 SCP actuator 
		
AAA_2SCP 	        - Angle variation acquisition with the AAA    - contraction/expansion enhancement 
		    using 2 SCP actuators 
 		
IND_TEMP_RES 	    - Measure actuator resistance, to compute its - acquisition methods
		    temperature indirectly	

AAA_ANG_TRACK 	  - Verification tests upon the AAA: angle      - verification: real system
		    tracking performance 

-----------------------------------------------------------------------------------------------------
