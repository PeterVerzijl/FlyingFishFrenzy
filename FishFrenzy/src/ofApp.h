#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "ofxBox2d.h"

#include "flock\Boid.h"
#include "flock\FishOne.h"
#include "flock\FishTwo.h"

#include "PlayerOne.h"
#include "PlayerTwo.h"

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
		
	private:
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
		ofSoundPlayer soundtrack;
		ofSoundPlayer naturesounds;

		// Box2D parameters
		ofxBox2d box2d;

		// vectors of pointers of fishes
		vector<ofPtr<Boid>> fishOneList;
		vector<ofPtr<Boid>> fishTwoList;
		
		//pointers of players
		ofPtr<PlayerOne> playerLeft;
		ofPtr<PlayerTwo> playerRight;

		//playerposition vectors
		ofVec2f playerOnePos;
		ofVec2f playerTwoPos;

		//particle system
		vector<ofPtr<ParticleSystem>> particleSystems;

		//load font
		ofTrueTypeFont fightFont;

		//pictures
		ofImage background;
		ofImage fishOneGore1;
		ofImage fishOneGore2;
		ofImage fishOneGore3;
		ofImage fishTwoGore1;
		ofImage fishTwoGore2;
		ofImage fishBones;

		int screenShakeDuration;	// In frames
		int fishKilled;
};
