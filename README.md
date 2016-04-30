# Mario_Kart
First Year End of Term Project
The aim of this project is to provide an entertaining and interactive, real-life experience that resembles the mechanics 
and race-like quality of the video game Mario Kart. The final product should satisfy the user as a fun game that 
incorporates intricate coding and aesthetically pleasing hardware, as well as a suitable racecourse for the user to 
follow. The basis of this project is to use Bluetooth communication with a Wii remote to control the movements of the 
car.

The goal of the software was to provide a real time communication link between the Wii remote and the NXT brick. To 
achieve this the code was split into multiple functions, each of which only perform one single task. The main function 
had a loop which called each of these tasks in succession. This loop allowed for continuous checking of the bluetooth 
buffer which is a requirement for accurate communication to work as well as continuously checking all the sensors on the 
vehicle. One problem with this software design is there was latency in the control of the robot. This stemmed from the
 fact that the code kept on looping through even when there was no data, and could have been in a different section of the
 code (e.g. colour sensing) when data was ready to be transmitted to the robot. This latency was minimized by not using 
any delays in the code other than a short 50 ms delay to debounce the colour sensor, all other timings used timer instead 
so that the code could continue to run. 


Problem Break-down Functions

char readBluetooth();

reads in a character from the BlueTooth signal and returns it Collaborates with the setMotor(parameters); function.

void comprehend(char character)

calls setMotor(parameters) and sets the motor values depending on the character accepted through the parameter

void setMotor(int leftMotor, int rightMotor)

sets the motor power to each of the motors controlling movement

int launchBall() rotate the ball shooting motor to launch the ball

int checkColour() returns the integer value of the colour from the colour sensor

bool checkTouch() if either front or back touch sensor has a positive signal, returns true, otherwise returns false.

The initialization phase which consists of setting up bluetooth as well as the menu to select the character will run 
before the main game loop.  This phase can be tested by displaying a message to the screen when bluetooth connects and 
the character selection can be tested by using debug mode where the value of the character variable can be seen.

The next phase would consist of the main loop phase where the vehicle is actually moving. This phase would consist of 
reading in a bluetooth message sent from the computer (which got a signal from a Wii remote). This can be tested by 
outputting the received data to the NXT screen. The next part would be taking the message and mapping it to motor 
movement. This can be tested by giving a specific message and making sure that the motors are moving properly. After 
setting the motors, the brick will then check for input from the sensors. It would check from the touch sensors and the 
colour sensor. If a specific input is detected then the robot will act accordingly (e.g. a blue colour is detected and 
the robot would speed up, bump sensor is triggered and the robot would stop moving for a second). These can be tested by 
manually triggering the input and making sure that the appropriate action is taken. The colour sensor function would also 
increment the lap number when it the robot passes over green. A ball shooter function will also occur when the user has a 
shooter power-up and clicks the correct button. This can be tested by making sure that the shooter shoots only when both 
the conditions are satisfied. After three laps the main loop would stop and move onto the final phase.

The final phase will consist of using timers and encoders which were reset that the beginning to output the time taken as 
well as an approximate average speed. This phase can be tested by running the robot along a track which has a known 
distance as well as using a stopwatch. Then some math could be done to calculate the actual data which can then be 
compared.

The original design was to get the functions to do most of the processing, but in the final code, most of the processing 
was done by the main function and passed into the function either by reference or by value depending on what the variable 
was and that allowed all of the functions to be of return type void. This way was chosen because most of the data sent 
through functions was either timings for various events or incremental values. It made the functions easier because most 
of the data common to all the functions could just be calculated once, rather than by the functions each time they run. 
For example, rather than passing in the player to check what the base speed should be, the base speed was calculated in 
main and then passed into the function. 
