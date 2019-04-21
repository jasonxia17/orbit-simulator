# To-do

* Display numerical information on the screen (time elapsed, instantaneous position/velocity)
* Add enum for app states (Instructions, User Input, Running, Paused, Crash)
* Incorperate a UI similar to the one shown below (see guiFromParametersExample for example code):

![](https://66.media.tumblr.com/94326685206eb2e5d02264c550d5c5d0/tumblr_inline_p7djm2RWdI1sbgmkt_540.gif)

# Ideas

* Display gravitational potential energy and kinetic energy, add methods to
CelestialBody class for calculating these quantities
* Display error message if planet crashes into sun (to avoid a divide-by-0 error)
* Display the coordinates/distance to sun at the point where the mouse is hovering

# Weekly Progress Log

## Week of 4/27/2019

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

I also found Python code simulates planetary orbits with the turtle module. This is mainly a proof of concept that
the back-end of the simulation should be feasible. I'll probably use the same mathematical techniques for my simulation.

https://fiftyexamples.readthedocs.io/en/latest/gravity.html

# Ideas for Stretch Goal 

## Multiplanet Chaotic Simulation

* accumulateNetForce(CelestialBody other) adds gravitational force caused by "other" to the net force


## Electric Field/Potential Tool

* Display the electric potential and field at the point where the mouse is hovering
* Allow the user to first select the position of the charged particle and then select the displacement vector
(no dragging necessary)
