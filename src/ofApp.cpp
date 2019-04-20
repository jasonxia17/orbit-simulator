#include "ofApp.hpp"

namespace physicsvisuals {

void OrbitSimulator::setup() {
    ofSetWindowTitle("Going in Circles");
    ofBackground(ofColor::black);
}

void OrbitSimulator::update() {
    planet_.updateVelocityAndPosition(0.01); // rename planet with underscore
}

void OrbitSimulator::draw() {
    // draws the sun
    ofSetColor(ofColor::yellow);
    ofDrawCircle(getScreenCoordinates(vec2(0, 0)), 30);

    // draws the orbiting planet
    ofSetColor(ofColor::blue);
    ofDrawCircle(getScreenCoordinates(planet_.getPosition()), 10);
}

void OrbitSimulator::keyPressed(int key) {
    // implement zooming in and out
}

vec2 OrbitSimulator::getScreenCoordinates(vec2 real_coordinates) {
    vec2 center(ofGetWindowWidth(), ofGetWindowHeight());
    center /= 2;

    real_coordinates.y *= -1; // canvas y-coordinates are the reverse of Cartesian y-coordinates

    const double kScaleFactor = 200;
    return kScaleFactor * real_coordinates  +  center;
}

}  // namespace physicsvisuals