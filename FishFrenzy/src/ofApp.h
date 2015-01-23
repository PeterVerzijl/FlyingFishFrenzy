#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "ofxBox2d.h"

#include "flock\Boid.h"
#include "flock\FishOne.h"
#include "flock\FishTwo.h"

#include "particleSystem\ParticleSystem.h"

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
		ofSoundPlayer explode;

		// Box2D parameters
		ofxBox2d box2d;
		
		vector<ofPtr<Boid>> fishOneList;
		vector<ofPtr<Boid>> fishTwoList;
		
		ofPtr<ofxBox2dRect> playerLeft;
		ofPtr<ofxBox2dRect> playerRight;

		ofVec2f playerOnePos;
		ofVec2f playerTwoPos;

		vector<ofPtr<ParticleSystem>> particleSystems;

		int screenShakeDuration;	// In frames

		ofTrueTypeFont fightFont;

		ofImage background;
		ofImage fishOneGore1;
		ofImage fishOneGore2;
		ofImage fishOneGore3;
		ofImage fishTwoGore1;
		ofImage fishTwoGore2;
		ofImage fishBones;

		int fishKilled;
};
