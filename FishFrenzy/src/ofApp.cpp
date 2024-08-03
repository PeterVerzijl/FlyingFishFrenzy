///////////////////////////////////////////////////////
///// Programming with Structures Module 6 CreaTe /////
/////  Created by Peter Verzijl and Gege Zhang    /////
/////                    2015                     /////
/////         Flocking based on flocking		  /////
/////     created by Jeffrey Crouse on 3/30/10    /////
///////////////////////////////////////////////////////

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetVerticalSync(true);			// Set graphics so it runs smoothly
	//ofSetLogLevel(OF_LOG_NOTICE);		// Debug level

//----------------------------KINECT SETUP----------------------

	kinect.setRegistration(true);		// Registrate depth checking
	kinect.init(false, false);			// Disables video image (faster fps)
	kinect.open();						// Opens first available kinect
	kinectAngle = 10;					// Level kinect at startup
	kinect.setCameraTiltAngle(kinectAngle);
	// Populate and init image with correct image size
	grayImage.allocate(kinect.width, kinect.height);
	useThreshold = true;				// Tell openCV to use threshold values
	nearThreshold = 255;				// Check as near as possible
	farThreshold = 243;					// Optimal for fist tracking

	// Load sound
	explode.loadSound("explosion.wav");
	soundtrack.loadSound("soundtrack.mp3");
	naturesounds.loadSound("naturesound.wav");
	soundtrack.play();
	naturesounds.play();

	// Set box2d parameters
	box2d.init();
	box2d.setGravity(0, 0);				// Set a vector2 for the gravity to 0 initially
	box2d.createBounds();				// Create the bounds of the box2d world
	box2d.setFPS(30.0);					// Set the physics update rate

//----------------------------PLAYERS--------------------------
	// Add two 'hands'
	// Player left
	playerLeft = ofPtr<PlayerOne>(new PlayerOne);
	playerLeft->setPhysics(3.0, 0.53, 0);
	playerLeft->setup(box2d.getWorld(), ofGetWidth() * 0.25f, ofGetHeight() * 0.5f, 190, 21);
//	playerLeft->setFixedRotation(true);
	playerLeft->fixture.filter.groupIndex = 1;	// Fixture collision mask

	// Player right
	playerRight = ofPtr<PlayerTwo>(new PlayerTwo);
	playerRight->setPhysics(3.0, 0.53, 0.1);
	playerRight->setup(box2d.getWorld(), ofGetWidth() * 0.75f, ofGetHeight() * 0.5f, 190, 21);
//	playerRight->setFixedRotation(true);
	playerRight->fixture.filter.groupIndex = 1;	// Fixture collision mask
	b2Filter filter;

//----------------------------FISHES---------------------------
	//generating new fishes (20) for both players
	for (int i = 0; i < 20; i++)
	{
		ofPtr<FishOne> fish1 = ofPtr<FishOne>(new FishOne(0, 0));
		fish1->setPhysics(3.0, 0.53, 0.1);
		fish1->setup(box2d.getWorld(), ofRandomWidth(), ofGetHeight() * 0.75f, fish1->size.x, fish1->size.y);
		fish1->fixture.filter.groupIndex = -1;
		fishOneList.push_back(fish1);

		ofPtr<FishTwo> fish2 = ofPtr<FishTwo>(new FishTwo(0, 0));
		fish2->setPhysics(3.0, 0.53, 0.1);
		fish2->setup(box2d.getWorld(), ofRandomWidth(), ofGetHeight() * 0.75f, fish2->size.x, fish2->size.y);
		fish2->fixture.filter.groupIndex = -1;
		fishTwoList.push_back(fish2);
	}

//----------------------------FONT/IMAGES----------------------
	// Fight font
	fightFont.loadFont("FightFont.ttf", 20, false, false, false, 1.0);

	// Load background image
	background.loadImage("Background.png");

	// Gore images
	fishOneGore1.loadImage("FishPiece3.png");;
	fishOneGore2.loadImage("FishPiece4.png");;
	fishOneGore3.loadImage("FishPiece5.png");
	fishTwoGore1.loadImage("FishPiece1.png");
	fishTwoGore2.loadImage("FishPiece2.png");
	fishBones.loadImage("Fishbone.png");
	
	//set framerate seeking 60fps
	ofSetFrameRate(60);	
}

//--------------------------------------------------------------
void ofApp::update(){

//----------------------------KINECT----------------------------
	kinect.update();					// Update kinect first to get images

	if (kinect.isFrameNew())			// Update code only when kinect has new data
	{
		grayImage.setFromPixels(kinect.getDepthPixels().begin(), kinect.width, kinect.height);		// Load greyscale depth images
		grayImage.resize(ofGetWidth(), ofGetHeight());										// Set the image so that it covers the whole screen
		grayImage.mirror(false, true);														// For some reason the image is mirrored :S so we mirror it back!

		// Do treshold!
		unsigned char *pixels = grayImage.getPixels().begin();
		int numPixels = grayImage.getWidth() * grayImage.getHeight();
		for (int i = 0; i < numPixels; i++)
		{
			pixels[i] = (pixels[i] < nearThreshold && pixels[i] > farThreshold) ? 255 : 0;	// Change the pixels to white and black so we can see them better later
		}
		grayImage.flagImageChanged();														// Tells open CV that the image was updated
		contourFinder.findContours(grayImage, 30, (kinect.width * kinect.height) * 0.5f, 20, false); // Find contours
	}

//----------------------------BLOBFINDER-----------------------
// Now we have the blobs from findContours, iterate trough them
	for (int i = 0; i < contourFinder.blobs.size(); i++) 
	{
		ofxCvBlob blob = contourFinder.blobs.at(i);
		ofVec2f blobPos = ofVec2f(blob.centroid.x, blob.centroid.y);

		if (blobPos.x < ofGetWidth() * 0.5f)												//find blob on left side
		{
			float distance = playerLeft->getPosition().distance(blobPos);
			ofVec2f force = (blobPos - playerLeft->getPosition()).normalized();
			playerLeft->setVelocity(force * 0.1f * distance);
			playerOnePos = blobPos;
		}
		else																				//find blob on right side
		{
			float distance = playerRight->getPosition().distance(blobPos);
			ofVec2f force = (blobPos - playerRight->getPosition()).normalized();
			playerRight->setVelocity(force * 0.1f * distance);
			playerTwoPos = blobPos;
		}
	}

//--------------------------FISH-MOVEMENT-UPDATE----------------
	//update movement of fish 1
	for (int i = 0; i < fishOneList.size(); i++) 
	{
		ofPtr<Boid> boid = fishOneList.at(i);

		boid->avoid(playerTwoPos, 1.0f);
		boid->seek(playerOnePos, 1.0f);
		boid->updateBoid(fishOneList);

		if (boid->getPosition().y < ofGetHeight() * 0.5f)
		{
			boid->acc += ofVec2f(0, 1) * 50.0f;
			boid->UpdateLife();										// run update life (lifespan --)
		}
		else
		{
			boid->age = 0;
			boid->friction = 0;
		}

		if (boid->isDead)
		{
			fishOneList.erase(fishOneList.begin() + i);				// if the fish is dead - erase that fish
			explode.play();

			// Create particle system
			ofPtr<ParticleSystem> ps = ofPtr<ParticleSystem>(new ParticleSystem);	// Create new particle system
			ofPtr<Particle> p;														// Create 20 new particles
			for (int i = 0; i < 20; i++)
			{
				p = ofPtr<Particle>(new Particle(boid->getPosition().x, boid->getPosition().y));
				ps->particles.push_back(p);											// Add to the list
			}
			// Add gore (blood, fish pieces etc.)
			p = ofPtr<Particle>(new Particle(boid->getPosition().x, boid->getPosition().y, fishOneGore1));
			ps->particles.push_back(p);
			p = ofPtr<Particle>(new Particle(boid->getPosition().x, boid->getPosition().y, fishOneGore2));
			ps->particles.push_back(p);
			p = ofPtr<Particle>(new Particle(boid->getPosition().x, boid->getPosition().y, fishOneGore3));
			ps->particles.push_back(p);
			p = ofPtr<Particle>(new Particle(boid->getPosition().x, boid->getPosition().y, fishBones));
			ps->particles.push_back(p);

			ps->emit();
			particleSystems.push_back(ps);											// Add particle sytem to our ps list

			// Do screenshake
			screenShakeDuration = 10;
		}
	}

	// Update movement of fishes 2
	for (int i = 0; i < fishTwoList.size(); i++) 
	{
		ofPtr<Boid> boid = fishTwoList.at(i);
		boid->avoid(playerOnePos, 1.0f);
		boid->seek(playerTwoPos, 1.0f);
		boid->updateBoid(fishTwoList);

		if (boid->getPosition().y < ofGetHeight() * 0.5f)
		{
			boid->acc += ofVec2f(0, 1) * 50.0f;
			boid->UpdateLife();									// run update life (lifespan --)
		}
		else
		{
			boid->age = 0;
			boid->friction = 0;
		}

		if (boid->isDead)
		{
			fishTwoList.erase(fishTwoList.begin() + i);			// erase that fish
			explode.play();

			// Create particle system
			ofPtr<ParticleSystem> ps = ofPtr<ParticleSystem>(new ParticleSystem);	// Create new particle system
			ofPtr<Particle> p;														// Create 20 new particles
			for (int i = 0; i < 20; i++)
			{
				p = ofPtr<Particle>(new Particle(boid->getPosition().x, boid->getPosition().y));
				ps->particles.push_back(p);											// Add to the list
			}
			// Add gore
			p = ofPtr<Particle>(new Particle(boid->getPosition().x, boid->getPosition().y, fishTwoGore1));
			ps->particles.push_back(p);
			p = ofPtr<Particle>(new Particle(boid->getPosition().x, boid->getPosition().y, fishTwoGore2));
			ps->particles.push_back(p);
			p = ofPtr<Particle>(new Particle(boid->getPosition().x, boid->getPosition().y, fishBones));
			ps->particles.push_back(p);

			ps->emit();
			particleSystems.push_back(ps);						// Add particle sytem to our ps list

			// Do screenshake
			screenShakeDuration = 10;
		}
	}

	// After everything is done
	box2d.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
//---------------------------SCREENSHAKE------------------------
	ofPushMatrix();

	if (screenShakeDuration > 0)										// Screenshake
	{
		screenShakeDuration--;
		ofTranslate(ofPoint(ofRandom(-1, 1), ofRandom(-1, 1)) * 10 );	//random translation / shake
	}
	else 
	{
		ofTranslate(0, 0);
	}

	ofSetColor(255);
	background.draw(0, 0, ofGetWidth(), ofGetHeight());

	// ofSetColor(150, 50);											// Set default background color a nice shade of gray
	// grayImage.draw(0, 0, grayImage.width, grayImage.height);		// Draw threshold image

//----------------------------DRAW-STUFF------------------------
	// Draw players
	ofFill();
	ofSetColor(0, 0, 255);
	playerLeft->draw();
	ofSetColor(255, 0, 0);
	playerRight->draw();

	// Draw fishes
	ofSetColor(255, 255, 255);
	for (int i = 0; i < fishOneList.size(); i++) 
	{
		fishOneList.at(i)->draw();
	}
	for (int i = 0; i < fishTwoList.size(); i++) 
	{
		fishTwoList.at(i)->draw();
	}

	// Draw particles
	for (ofPtr<ParticleSystem> ps : particleSystems) 
	{
		ps->update();
	}

	// Draw water
	fishKilled = (float)(((float)fishOneList.size() + (float)fishTwoList.size()) / 40.0f) * 255;
	ofSetColor(255 - fishKilled, 0, fishKilled, 150); 
	ofRect(0, ofGetHeight() * 0.5f, ofGetWidth(), ofGetHeight() * 0.5f);

	ofNoFill();
	ofRect(100, 100, ofGetWidth() - 200, ofGetHeight() - 200);

	ofPopMatrix();

	contourFinder.draw(0, 0, grayImage.width, grayImage.height);	// Draw the found contours

	// UI counters
	ofDrawBitmapString(ofToString(ofGetFrameRate())+"fps", 10,15);
	ofSetColor(255, 255, 255);
	ostringstream p1text;
	p1text << "Player 1: " << fishOneList.size() << " / 20";
	ostringstream p2text;
	p2text << "Player 2: " << fishTwoList.size() << " / 20";
	fightFont.drawString(p1text.str(), ofGetWidth()*0.1f, 100);
	fightFont.drawString(p2text.str(), ofGetWidth()*0.6f, 100);

	if (fishTwoList.size() <= 0) {
		ostringstream text;
		text << "Player one WON!" << endl;
		fightFont.drawString(text.str(), ofGetWidth() * 0.3f, ofGetHeight() * 0.5f);
	} 
	else if (fishOneList.size() <= 0) {
		ostringstream text;
		text << "Player two WON!" << endl;
		fightFont.drawString(text.str(), ofGetWidth() * 0.3f, ofGetHeight() * 0.5f);
	}
}

//--------------------------------------------------------------
void ofApp::exit() 
{
	kinect.setCameraTiltAngle(0); // zero the tilt on exit
	kinect.close();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
	box2d.createBounds(0, 0, w, h);				// Create the bounds of the box2d world
	box2d.checkBounds(true);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{ 

}
