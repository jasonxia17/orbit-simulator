#include "ofApp.hpp"

namespace physicsvisuals {

void OrbitSimulator::setup() {
    ofSetWindowTitle("Going in Circles");
    ofBackground(ofColor::black);
}

void OrbitSimulator::update() {
    const double kTimeStep = 0.01;
    planet_.updateVelocityAndPosition(kTimeStep);
    time_elapsed_ += kTimeStep;
}

void OrbitSimulator::draw() {
    drawSunAndPlanet();
    drawNumericalInfo();
}

void OrbitSimulator::drawSunAndPlanet() const {
    const double kSunRadius = 0.15;
    const double kPlanetRadius = 0.05;
    const vec2 origin;

    // draws the sun
    ofSetColor(ofColor::yellow);
    ofDrawCircle(getScreenCoordinates(origin), kSunRadius * scalefactor_);

    // draws the orbiting planet
    ofSetColor(ofColor::blue);
    ofDrawCircle(getScreenCoordinates(planet_.getPosition()), kPlanetRadius * scalefactor_);
}

void OrbitSimulator::drawNumericalInfo() const {
    ofSetColor(ofColor::white);
    ofTrueTypeFont myfont;
    myfont.load("../fonts/Liberation-Mono-Regular.ttf", 20);
    myfont.drawString(ofToString(time_elapsed_), 100, 100);
}

void OrbitSimulator::keyPressed(int key) {
    const double kZoomFactor = 1.03;
    if (key == '-') {
        scalefactor_ /= kZoomFactor;

    } else if (key == '=') {
        scalefactor_ *= kZoomFactor;
    }
}

vec2 OrbitSimulator::getScreenCoordinates(vec2 real_coordinates) const {
    vec2 center(ofGetWindowWidth(), ofGetWindowHeight());
    center /= 2;

    real_coordinates.y *= -1;  // canvas y-coordinates are the reverse of Cartesian y-coordinates

    return scalefactor_ * real_coordinates + center;
}

}  // namespace physicsvisuals