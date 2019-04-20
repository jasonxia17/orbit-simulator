#include "ofApp.hpp"

namespace physicsvisuals {

void OrbitSimulator::setup() {
    ofSetWindowTitle("Going in Circles");
    ofBackground(ofColor::black);
}

void OrbitSimulator::update() {
    planet_.updateVelocityAndPosition(0.01);  // rename planet with underscore
}

void OrbitSimulator::draw() {
    const double kSunRadius = 0.15;
    const double kPlanetRadius = 0.05;
    
    // draws the sun
    ofSetColor(ofColor::yellow);
    ofDrawCircle(getScreenCoordinates(vec2(0, 0)), kSunRadius * scale_factor);

    // draws the orbiting planet
    ofSetColor(ofColor::blue);
    ofDrawCircle(getScreenCoordinates(planet_.getPosition()), kPlanetRadius * scale_factor);
}

void OrbitSimulator::keyPressed(int key) {
    const double kZoomFactor = 1.03;
    if (key == '-') {
        scale_factor /= kZoomFactor;

    } else if (key == '=') {
        scale_factor *= kZoomFactor;
    }
}

vec2 OrbitSimulator::getScreenCoordinates(vec2 real_coordinates) {
    vec2 center(ofGetWindowWidth(), ofGetWindowHeight());
    center /= 2;

    real_coordinates.y *= -1;  // canvas y-coordinates are the reverse of Cartesian y-coordinates

    return scale_factor * real_coordinates + center;
}

}  // namespace physicsvisuals