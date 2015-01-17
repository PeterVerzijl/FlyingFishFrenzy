#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "ofxBox2d.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		// Kinect parameters
		ofxKinect kinect;
		float kinectAngle;

		// OpenCV parameters
		ofxCvGrayscaleImage grayImage;
		ofxCvContourFinder contourFinder;

		bool useThreshold;
		int nearThreshold;
		int farThreshold;

		// Box2D parameters
		ofxBox2d box2d;
		vector<ofPtr<ofxBox2dCircle>> circles;
		vector<ofPtr<ofxBox2dRect>> boxes;

		ofPtr<ofxBox2dRect> playerLeft;
		ofPtr<ofxBox2dRect> playerRight;
};
