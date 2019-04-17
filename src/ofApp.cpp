#include "ofApp.h"

namespace physicstools {

void OrbitSimulator::setup() {
    ofSetWindowTitle("Going in Circles");
    ofBackground(0);
}

void OrbitSimulator::update() {
    planet.updateVelocityAndPosition(0.01);
}

void OrbitSimulator::draw() {
    // draws the sun
    ofSetColor(255, 255, 0);
    ofDrawCircle(getScreenCoordinates(vec2(0, 0)), 30);

    // draws the orbiting planet
    ofSetColor(0, 0, 255);
    ofDrawCircle(getScreenCoordinates(planet.getPosition()), 10);
}

void OrbitSimulator::keyPressed(int key) {
}

void OrbitSimulator::windowResized(int w, int h) {
}

vec2 OrbitSimulator::getScreenCoordinates(vec2 real_coordinates) {
    vec2 center(ofGetWindowWidth(), ofGetWindowHeight());
    center /= 2;

    real_coordinates.y *= -1; // canvas y-coordinates are the reverse of Cartesian y-coordinates

    const double kScaleFactor = 200;
    return kScaleFactor * real_coordinates  +  center;
}

}  // namespace physicstools