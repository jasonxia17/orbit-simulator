#include "ofApp.h"

namespace physicstools {

void OrbitSimulator::setup() {
    ofSetWindowTitle("Going in Circles");
    ofBackground(0);
}

void OrbitSimulator::update() {
    theta_ += 0.05;
    std::cout << theta_ << std::endl;
}

void OrbitSimulator::draw() {
    ofDrawCircle(ofGetWindowWidth() / 2 + 100 * cos(theta_), ofGetWindowHeight() / 2 + 100 * sin(theta_), 20);
}

void OrbitSimulator::keyPressed(int key) {
}

void OrbitSimulator::windowResized(int w, int h) {
}
}  // namespace physicstools