# Tools for learning physics

My goal is to make tool(s) that help students with learning physics.

## Background

I've already made one such tool in the past
using Javascript. It demonstrates the Lorentz Transformation, which basically dictates how events appear in a relativistic
frame of reference.

https://github.com/jasonxia17/PhysicsPlayground

## Project Goals

I would like to extend this collection by developing more tools using Open Frameworks. The first tool I'll try to
create is a simulation of planetary motion. This is inherently hard to set up in a laboratory setting, but I think
it's still a valuable experience for students to have hands-on experience experimenting with the behavior of planets.

I know that a lot of planet simulations already exist out on the web, but I want to try to provide something
more unique in my application: an easy way to change parameters (initial position and velocity) and an easy way
to measure data at any time (e.g. distance and instantaneous velocity). I believe this provides pedagogical value, because
it allows students to use this tool as if it were a real laboratory experiment.

Hopefully, experimenting with planets in this app will solidify students' understandings of Kepler's Laws and
the transition between circular, elliptical, parabolic, and hyporbolic orbits (which is related to the energy
of the planet).

## Stretch Goals

If I have time, I'll consider including additional tools in my final project. For example, I might want to make a tool for visualizing electric field and potential.

## Libraries

* OpenGL Mathematics: Provides vector classes, which I can use to store/manipulate position and velocity
* 2D graphics: Draw planets and display measurements on the screen
* ofxGui: Allow the user to input parameters before the simulation starts
* 3D graphics: This might be useful if I want to do something with magnetism (because cross products require three dimensions). However, I probably won't need to use this library.
