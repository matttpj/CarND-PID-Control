# **PID Controller**

## Writeup by Matthew Jones

### Project: CarND-PID-Control

---

**PID Controller Project**

The major steps taken to complete this project included:
* Reviewing **PID Controller** project instructions and previous **Behavior Cloning** project
* Getting familiar with the commands needed in the Udacity workspace to compile project code and launch the driving simulator
* Writing my code in __main.cpp__ and __PID.cpp__ to enable my car to drive around the track  
* Adapting my code to ensure that my car does not violate any of the requirements defined in the [project rubric](https://review.udacity.com/#!/rubrics/1972/view){target="_blank"}  
* Adjusting the hyper-parameters so that my car can successfully drive one lap of the track
* Describing the effects of the P,I,D components in my implementation and how final hyper-parameters were chosen **_[see below](#Reflection)_**


[//]: # (Image References)
__Screenshot and video from the driving simulator__    
<img src="./pid_control.jpg" width=60% height=60%>  
[download video](https://github.com/matttpj/CarND-PID-Control/raw/master/pid_control_success.mp4)

---
### Writeup / README
Here is a link to my [project code](https://github.com/matttpj/CarND-PID-Control){target="_blank"}   

---
### Files Submitted

#### Submission includes all files required to run my car in the driving simulator

Key files are in source directory __src/*__:
 * Connects to the simulator and initiates PID control: __main.cpp__   
 * Class file for the PID controller class and error calculating methods: __PID.cpp__
 * Header file for the PID controller class: __pid.h__
 * Manipulate JSON format data structures and messages:  __json.hpp__

---
### Compilation
The above source code compiles successfully in the Udacity workspace.

---
### Implementation
| Criteria       		|     Specification	        					|    
|:---------------------:|:-------------------------------:|
| The PID procedure follows what was taught in the lessons. 	| It's encouraged to be creative, particularly around hyperparameter tuning/optimization. However, the base algorithm should follow what's presented in the lessons.	|


---
### Reflection
The code for PID Control is included in file **_main.cpp_** from **line 33** onwards and **_PID.cpp_** from **line 11** onwards. An explanation of how the code works is provided below.

| Criteria       		|     Specification	        					|
|:---------------------:|:-------------------------------:|
| Describe the effect each of the P, I, D components had in your implementation. 	| Student describes the effect of the P, I, D component of the PID algorithm in their implementation. Is it what you expected? Visual aids are encouraged, i.e. record of a small video of the car in the simulator and describe what each component is set to.	|
| Describe how the final hyperparameters were chosen. | Student discusses how they chose the final hyperparameters (P, I, D coefficients). This could be have been done through manual tuning, twiddle, SGD, or something else, or a combination!	|

__Proportional Error >>__  This is the Cross Track Error (cte) provided by the simulator.  **cte** error is the distance from the centre of my car to the centre of the track.
__Integral Error >>__  This is the cumulative value of **cte** error over previous time periods.
__Differential Error >>__  This is the difference value between current time period **cte** and previous time period **prev_cte**.  
__Total Error >>__ This is the sum of **P,I,D** errors each multiplied by their respective hyper-parameter **Kp, Ki, Kd** which are initialised in **main.cpp, line 41**.
__Best Error >>__ This is the smallest value of **cte** achieved during a simulation run.
__Steer Value >>__ This is the steering value sent as input to the simulator and is calculated as current steering value less the Total Error calculated by the PID class.

I tuned the hyper-parameters **Kp, Ki, Kd** manually over successive simulation rounds until I was able to get my car to successfully drive 1 lap around the track.
Here is a log of my tuning settings.

**Kp: 0.0 | Ki: 0.0 | Kd: 0.0**  
CTE: 21.7944 | Steering Value: 0  
Best Error: 1.4822e-323  
Car drives in straight line off the track  

**Kp: 1.0 | Ki: 0.0 | Kd: 0.0**  
CTE: 27.2635 | Steering Value: 0  
Best Error: 6.95195e-310  
Car drives in straight line off the track  

**Kp: 0.0 | Ki: 0.0 | Kd: 1.0**  
CTE: 5.6722 | Steering Value: 0  
Best Error: 1.4822e-323  
Car moves close to centre line but can't adjust fast enough to get round corner and gets stuck on the kerb  

**Kp: 0.0 | Ki: 0.0 | Kd: 2.0**  
CTE: 12.1598 | Steering Value: -0.171  
Best Error: 6.94208e-310  
Car gets slightly further round the corner than previous begins to oscillate and then still goes off road  

**Kp: 0.0 | Ki: 0.0 | Kd: 3.0**  
CTE: 7.1254 | Steering Value: 0.0057  
Best Error: 6.93927e-310  
Car gets further round the corner then goes off road and follows road off from outside the track  

**Kp: 0.5 | Ki: 0.0 | Kd: 3.0**  
CTE: -0.0673 | Steering Value: 0.01955  
Best Error: -1.3209  
Car gets round first corner crosses bridge and round subsequent corners until about 1/2 way but oscillations get quite pronounced just before car goes off at corner.  

**Kp: 0.3 | Ki: 0.0 | Kd: 3.0**  
CTE: 0.0593 | Steering Value: -0.01869  
Best Error: -1.427  
Car gets all the way round the track!!!  

**Kp: 0.25 | Ki: 0.0 | Kd: 2.5**  
CTE: 0.182 Steering Value: 0.1195
Best Error: -1.6664
Car gets all the way around the track with slightly less wild oscillations.  

I found that to successively drive around the track it was not necessary to tune the Integral Error hyper-parameter to meet the project rubric.  If I had continued to experiment I would have adjusted my TotalError algorithm to use Twiddle; whereby the **Ki** is multiplied by -2.

I also experimented with adding a PID controller to modify the vehicle throttle as suggested in the starter code.  However, after multiple rounds of experimentation I was unable to improve on above performance; hence I have omitted this code from project submission.  I would appreciate feedback from the reviewer as to how best to utilise **speed** and **steering_angle** successfully in a PID Control implementation.

### Simulation
| Criteria       		|     Specification	        					|    Status  |
|:---------------------:|:-------------------------------:|:--------:|
| The vehicle must successfully drive a lap around the track.	| No tire may leave the drivable portion of the track surface. The car may not pop up onto ledges or roll over any surfaces that would otherwise be considered unsafe (if humans were in the vehicle). |  PASS |  

Follow the link to [download video](https://github.com/matttpj/CarND-PID-Control/raw/master/pid_control_success.mp4)
