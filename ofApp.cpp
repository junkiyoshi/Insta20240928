#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);

	ofNoFill();
	ofSetLineWidth(2);

	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	ofColor color;
	for (int i = 0; i < 48; i++) {

		auto noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));
		color.setHsb(ofMap(i, 0, 48, 0, 255), 200, 200);

		for (int k = 0; k < 8; k++) {

			auto location = glm::vec2(
				ofMap(ofNoise(noise_seed.x, k * 0.0065 + ofGetFrameNum() * 0.005), 0, 1, -600, 600),
				ofMap(ofNoise(noise_seed.y, k * 0.0065 + ofGetFrameNum() * 0.005), 0, 1, -600, 600));
			auto next = glm::vec2(
				ofMap(ofNoise(noise_seed.x, (k + 1) * 0.0065 + ofGetFrameNum() * 0.005), 0, 1, -600, 600),
				ofMap(ofNoise(noise_seed.y, (k + 1) * 0.0065 + ofGetFrameNum() * 0.005), 0, 1, -600, 600));

			auto velocity = next - location;


			ofSetColor(color);

			ofPushMatrix();
			ofTranslate(location);

			ofRotateY(velocity.y * 100);
			ofRotateX(velocity.x * 100);

			ofDrawCircle(glm::vec2(), k * 2);

			ofPopMatrix();
		}

	}

	/*
	int start = 50;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}