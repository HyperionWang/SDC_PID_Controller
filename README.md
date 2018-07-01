# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

[//]: # (Image References)
[image1]: ./PID_DriveThroughResult.gif

## Overview

This project is to implement the PID controller with tuning on the P, I, and D paramters to make the car driving along the planned path smoothly. 

The PID controller is a simple but powerful control system to realize the control on the car's speed and steering angle. Two PID controllers have been designed and optimized. One PID controller is for speed control, and the other PID controller is for the steering angle control so to minimize the cross track error (CTE).

The process flow is:
1. System send back the current state of car (cte, speed, and angle). 
2. Two PID controllers calculate the feedback control in throttle value and steering angle.
3. Send to the system as the control command until the updated state. Then, repeat the first step in the flow.

## PID control model

The PID controller keeps looking at the input error and feedback the control output based on the current error (P factor), error over all time (I factor), and the error change (D factor). 

Therefore, the feedback from the PID controller is:

feedback = - Kp * error(t) - Ki * sum(error(0), error(1),...,error(t)) - Kd * (error(t) - error(t-1))

Two PID controllers (speed PID and CTE PID) used the same architect, but different parameter values on Kp, Ki, and Kd. 


### Speed PID Controller
For speed PID controller, I start with Ki = 0, and with Kd more than 10 time of Kp (0.1 and 1). And I found this combination with too much overshoot and stability is not very good. Therefore, I keep increasing the Kd from 1 to 5, and intentionally make the controller a little over damped. Then, I changed Ki from 0 to 0.0001, so that in long term the offset of the speed would be corrected. The reason for using relative large Kd is the car supposes to reach to the expected speed smoothly without the overshoot (meaning over acceleration to make the speed limit exceed the speed set). It is because the speed over-shoot would affect the performance of the PID controller on the steering angle correction.

### Steering Angle PID Controller

For steering angle PID controller, the PID parameters highly depend on the speed set. With speed set to be 30 MPH, the PID number of Kp = 0.1, Kd = 10, and Ki = 0.01 worked. However, as the speed increases from 30 MPH to 60 MPH, the PID controller needs faster response to the CTE increases due to the turn. Therefore, I start from Ki = 0, Kd down to 5, and increase Kp from 0.1 to 0.13 with step of 0.01. And I found that as the Kp increases, although the car response to the turn (CTE increases) faster, the car start to move left to right and left (oscillating), which indicates the instability of the feedback system and need more damping. Therefore, I kept the Kp being 0.13, and started to increase the Kd from 5 to 12, with step of 1 for each. And I found 11 - 12 is good with Ki being 0. At this time, the car is able to handle the small turn pretty well, but it cannot keep the steering for longer time in the larger turn. This means the PID controller need more correction on the CTE error in long term. Therefore, I started to add Ki from 0 to 0.01. However, with large Kd and large Ki, the car's response slowed down. Therefore, I need to reduce the Kd and Ki, but still keep the ability of long correction on large turn. And finally I found a pretty good combination of Kp, Kd, and Ki being 0.13, 5, and 0.0005 for speed between 50 - 60.

## Results and Summary

In this project, the speed PID controller and steering angle PID controller have been designed, implemented, and tuned, in order to enable the car drives at speed of 50 - 60 MPH. The PID feedback system for car's motion control and the effect of Kp, Kd, and Ki have been studied. And the final optimized PID controller could drive the car to pass through the lake routine smoothly and safely. As show in the following gif.

![PID Controller Results][image1]

In the future, some improvements could be made on the PID controllers. 
1. Since the PID parameters are highly depending on the car's current speed. A speed factor (which equivalent to the relative update rate) could be taken into the calculation of the error (for example, error = CTE * speed instead of error = CTE). Or, change the Kp and Kd based on the current speed. 

2. The system need also take the system control latency into consideration. It means the control may be falling lag behind the current state of car. To solve this issue, the car's motion model could be added, in order to predict the CTE error in a near future. Also, the looking-forward factor could also be added into the feedback system to compensate the phase lag of the system. 