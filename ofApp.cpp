#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(3);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	vector<glm::vec2> location_list;

	for (int i = 0; i < 20; i++) {

		location_list.push_back(glm::vec2(ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.0035), 0, 1, 0, ofGetWidth()), ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.0035), 0, 1, 0, ofGetWidth())));
	}

	for (int i = 0; i < location_list.size(); i++) {

		ofFill();
		ofDrawCircle(location_list[i], 10);
		for (int k = i + 1; k < location_list.size(); k++) {

			auto distance = glm::distance(location_list[i], location_list[k]);
			if (distance < 100) {

				vector<glm::vec2> vertices;
				auto direction_rad = std::atan2(location_list[k].y - location_list[i].y, location_list[k].x - location_list[i].x);
				auto direction_deg = direction_rad * RAD_TO_DEG + 90;


				for (int deg = direction_deg; deg <= direction_deg + 180; deg += 3) {

					vertices.push_back(location_list[i] + glm::vec2(15 * cos(deg * DEG_TO_RAD), 15 * sin(deg * DEG_TO_RAD)));
				}

				for (int deg = direction_deg + 180; deg <= direction_deg + 360; deg += 3) {

					vertices.push_back(location_list[k] + glm::vec2(15 * cos(deg * DEG_TO_RAD), 15 * sin(deg * DEG_TO_RAD)));
				}

				ofNoFill();
				ofBeginShape();
				ofVertices(vertices);
				ofEndShape(true);
			}
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}