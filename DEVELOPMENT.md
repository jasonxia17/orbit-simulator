# To-do

Finished! :)

# Ideas

* Provide an option to enforce circular orbits by calculating the initial velocity based on the initial position that the user inputs
* Display the coordinates/distance to star at the point where the mouse is hovering

# Weekly Progress Log

## Week of 5/1/2019

* Displayed gravitational potential energy and kinetic energy
  * Added methods to CelestialBody class for calculating these quantities
* Displayed magnitude of position and velocity
* Changed mass to an ofParameter which can be adjusted by GUI
* Radius calculated as proportional to mass^1/3 in getRadius function
* Allow user to scroll with arrow keys (OF_KEY_LEFT, etc.)
* Display a message with information about how to use the app
* velocity_color has default value, default initial position/velocity were removed from constructor
* Implemented suggestions from code review

## Week of 4/27/2019

* Started working on chaotic orbit simulator (3+ bodies) that extends the OrbitSimulator class
* Restructured code to make it more object oriented
  * Moved mass, radius, colors, and initial ofParameters for position and velocity into the CelestialBody class
  * Moved drawing functions (draw body, trail, and velocity vector) into the CelestialBody class
* Display an error message and halt simulation if planet crashes into star (to avoid unpredictable behavior from extremely large forces)
* Incorporated a GUI for inputting intial parameters (used guiFromParametersExample as an example)
* Displayed numerical information on the screen
(time elapsed, instantaneous position/velocity)
* Added an enum for app states (Welcome/Instructions, User Input, Running, Paused, Crashed)
* Displayed an arrow representing the instantaneous velocity of the planet
  * Combines a line with a triangle that has been rotated and translated
* Traced a path behind the circle
  * Fixed a bug in the expression for the opacity of the trail
* Allowed the user to resize the screen with - and = keys

## Week of 4/20/2019

* Created class to represent a celestial body
  * Stores current velocity and position as 2D vectors
  * updateVelocityAndPosition(time_step) uses Euler's method to calculate the new velocity/position after a time step
  * Getters have signature of this form: const 2Dvec& getPosition() const {}

* Rewrote animation using two-dimensional vectors from GLM

* Transformed the Cartesian coordinates into canvas coordinates

* Replaced the object traveling in circles with actual physics

## Week of 4/13/2019 (Exploratory Work)

I created a simple animation of a point going in circles using the 2D graphics library.

I also found Python code that simulates planetary orbits with the turtle module. This is mainly a proof of concept that
the back-end of the simulation should be feasible. I'll probably use the same mathematical techniques for my simulation.

https://fiftyexamples.readthedocs.io/en/latest/gravity.html

# Ideas for Stretch Goal 

## Electric Field/Potential Tool

* Display the electric potential and field at the point where the mouse is hovering
* Allow the user to first select the position of the charged particle and then select the displacement vector
(no dragging necessary)
