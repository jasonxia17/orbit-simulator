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
    drawPlanetVelocityVector();
    drawSunAndPlanet();
    drawNumericalInfo();
}

void OrbitSimulator::drawSunAndPlanet() const {
    const double kSunRadius = 0.25;
    const double kPlanetRadius = 0.1;
    const vec2 origin;

    // draws the sun
    ofSetColor(ofColor::yellow);
    ofDrawCircle(getScreenCoordinates(origin), kSunRadius * scale_factor_);

    // draws the orbiting planet
    ofSetColor(ofColor::blue);
    ofDrawCircle(getScreenCoordinates(planet_.getPosition()), kPlanetRadius * scale_factor_);
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

void OrbitSimulator::drawPlanetVelocityVector() const {
    ofSetLineWidth(4);
    ofSetColor(ofColor::orange);

    // A velocity v will show up as a line with length kVectorScaleFactor * v
    const double kVectorScaleFactor = 0.35;
    vec2 vector_head = planet_.getPosition() + kVectorScaleFactor * planet_.getVelocity();
    ofDrawLine(getScreenCoordinates(planet_.getPosition()), getScreenCoordinates(vector_head));

    // Part 2: Draw triangular arrow at vector head

    std::vector<vec2> arrow_coordinates{vec2(0, -0.1), vec2(0, 0.1), vec2(0.2, 0)};
    // Currently, this is an arrow at the origin pointing directly to the right

    float arrow_angle = glm::orientedAngle(vec2(1, 0), glm::normalize(planet_.getVelocity()));
    // signed angle between velocity and positive-x axis, in the interval [-pi, pi]
    // vector parameters need to be normalized when using the orientedAngle function
    // arrow_angle must be a float instead of double to maintain consistent template types

    for (vec2& point : arrow_coordinates) {
        point = glm::rotate(point, arrow_angle); // rotate arrow to be parallel to vector
        point += vector_head;  // translate arrow to vector head
        point = getScreenCoordinates(point);
    }
    
    ofDrawTriangle(arrow_coordinates[0], arrow_coordinates[1], arrow_coordinates[2]);
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
        scale_factor_ /= kZoomFactor;

    } else if (key == '=') {
        scale_factor_ *= kZoomFactor;
    }
}

vec2 OrbitSimulator::getScreenCoordinates(vec2 real_coordinates) const {
    vec2 center(ofGetWindowWidth(), ofGetWindowHeight());
    center /= 2;

    real_coordinates.y *= -1;  // canvas y-coordinates are the reverse of Cartesian y-coordinates

    return scale_factor_ * real_coordinates + center;
}

}  // namespace physicsvisuals