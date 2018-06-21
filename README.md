# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---
## 1. Compilation
The code is successfully compiled, with instructions appended below (quoted from original README file).

## 2. Implementation
The PID procedure follows what was taught in the lessons. The PID.cpp and lines in main.cpp are implemented based on the knowledge taught in class. 

## 3. Reflection
3.1 Describe the effect each of the P,I,D components had in your implementation.
The proportional gain, Kp, was firstly tuned. A very low Kp will not compensate the error and the system is not stable. A medium Kp value will lead to an oscillated response, and a higher Kp value will make system perform better, but too high Kp will make the system out of control.

The Kd value is the second to be tuned, and it controls the derivative of error. A low Kd gain will lead the system remain underdamped and the car behaves oscillation. A high Kd value will make the system overdamped, but the time to reach steady state will be longer. So a good Kd will make the system around critically damped, which has a better response.

The Ki part is the last tuned one, which helped compensate the steady-state error. A low Ki value will use longer time to reach the steady-state, and a very high Ki value will make the system over-reacted and unstable. So a good value of Ki will help eliminate the steady-state error while perform a quick response.

3.2 Describe how the final hyperparameters were chosen.
Specifically referring to reference below, which reminds me some previous tuning experience before, I have tuned the PID controller by first tuning the p part. I first increased Kp to be critically stable. In the first straight part on the track, in the simulator, it was seen that the car was oscillating (Although it could fail during sharp turn). After 1st step, Kp = 0.2.

Then increase the Kd value. Increasing Kd value makes the system till overdamped, showing smaller oscillation during test making the test successfully finished possible. Starting from Kd = 1.0, 1.5, and the system kept failed or almost failed. Then Kd was increased to 3.0,and the result looked much better, and max error sharply decreased. Then Kd was increased to 4.0 and the results was further better. Then after that since the max error did not show obvious drop I just use Kd = 4.0. This procedure is summarized in the table below. <br />

Kp | Kd | Ki | result (in simulation) | max error 
---|----|----|------------------------|----------
0.2 | 1.5 | 0 | almost fail | 5.0812
0.2 | 3.0 | 0 | much better than above | 1.9479
0.2 | 4.0 | 0 | better result than above | 1.9189

Then the last step is to find a good Ki value, although the previous result is also visually acceptable. Starting from a relative small value of Ki, such as 0.01 and 0.001, the response on the simulation does not show good result at all. The response was too sharp and overshoot was too high. After dropped down Ki to 0.0001, the system returned to stable and max error was smaller than before. Then I have tried a few options around this number and finally use Ki = 0.00035. <br />

Kp | Kd | Ki | result (in simulation) | max error 
---|----|----|------------------------|----------
0.2 | 1.5 | 0.0001 | stable, a little better than PD control only | 1.8415
0.2 | 3.0 | 0.0002 | very stable | 1.9479
0.2 | 4.0 | 0.00035 | very stable | 1.6000
0.2 | 4.0 | 0.0005 | very stable | 1.6606
0.2 | 4.0 | 0.00065 | stable, but sometimes over-reacted | 1.6555

I think some numbers around 0.0003 - 0.0006 should be within the optimal solution range. Sometimes when Ki >= 0.00065, the overshoot increases and especially during sharp turns (the last 1 and 2 turns in simulation), the car was over-reacted so I did not use that big number for Ki. The final choice is Kp = 0.2, Kp = 4.0, and Ki = 0.00035.

Reference:
https://robotics.stackexchange.com/questions/167/what-are-good-strategies-for-tuning-pid-loops

## 4. Simulation
The vehicle is successfully driven a lap around the track. A short video was also recorded and uploaded in this repo. Please refer to it as a quick access of the result.


## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1(mac, linux), 3.81(Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

There's an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

Tips for setting up your environment can be found [here](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/f758c44c-5e40-4e01-93b5-1a82aa4e044f/concepts/23d376c7-0195-4276-bdf0-e02f1f3c665d)

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562)
for instructions and the project rubric.

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./

## How to write a README
A well written README file can enhance your project and portfolio.  Develop your abilities to create professional README files by completing [this free course](https://www.udacity.com/course/writing-readmes--ud777).

