# To-do

* Create class to represent a celestial body
  * Stores net force, current velocity, and position as 2D vectors
  * accumulateNetForce(Body other) adds gravitational force caused by "other" to the net force
  * updateVelocityAndPosition(time_step) uses Euler's method to calculate the new velocity/position after a time step
  * Getters should have signature of this form: const 2Dvec& getPosition() const {}

* Rewrite the "going in circles" animation using vectors from GLM
* Trace a path behind the circle
* Replace the circle with  actual physics

# Ideas

* Display error message if planet crashes into sun (to avoid a divide-by-0 error)
* Display the coordinates/distance to sun at the point where the mouse is hovering
* Allow the user to select the units of measurement (meters/AU, kilograms/earth masses, seconds/days/years)

# Weekly Progress Log

## Week of 4/13/2019 (Exploratory Work)

I created a simple animation of a point going in circles using the 2D graphics library.

I also found Python code simulates planetary orbits with the turtle module. This is mainly a proof of concept that
the back-end of the simulation should be feasible. I'll probably use the same mathematical techniques for my simulation.

https://fiftyexamples.readthedocs.io/en/latest/gravity.html

# Ideas for Stretch Goal (Electric Field/Potential Tool)

* Display the electric potential and field at the point where the mouse is hovering
* Allow the user to first select the position of the charged particle and then select the displacement vector
(no dragging necessary)
