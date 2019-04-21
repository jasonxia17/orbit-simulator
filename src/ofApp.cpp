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
    drawPlanetTrail();
    drawSunAndPlanet();
    drawNumericalInfo();
}

void OrbitSimulator::drawSunAndPlanet() const {
    const double kSunRadius = 0.25;
    const double kPlanetRadius = 0.1;
    const vec2 origin;

    // draws the sun
    ofSetColor(ofColor::yellow);
    ofDrawCircle(getScreenCoordinates(origin), kSunRadius * scalefactor_);

    // draws the orbiting planet
    ofSetColor(ofColor::blue);
    ofDrawCircle(getScreenCoordinates(planet_.getPosition()), kPlanetRadius * scalefactor_);
}

void OrbitSimulator::drawPlanetTrail() const {
    ofSetLineWidth(3);

    auto trail = planet_.getPositionLog();

    ofColor trail_color = ofColor::blue;
    const double kMaxOpacity = 255;

    if (trail.empty()) {
        return;
        // otherwise trail.size() - 1 = size_t(0) - 1 = huge number --> segfault
    }

    for (size_t i = 0; i < trail.size() - 1; ++i) {
        double opacity_fraction = 1 - (double)i / CelestialBody::kMaxPositionsStored;
        trail_color.a = kMaxOpacity * opacity_fraction;
        // linearly decrease opacity of trail for less recent positions

        ofSetColor(trail_color);
        ofDrawLine(getScreenCoordinates(trail[i]), getScreenCoordinates(trail[i + 1]));
    }
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