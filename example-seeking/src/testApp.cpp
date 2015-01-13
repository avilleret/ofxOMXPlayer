#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup()
{
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetLogLevel("ofThread", OF_LOG_ERROR);
		
	
	string videoPath = ofToDataPath("../../../video/Timecoded_Big_bunny_1.mov", true);

	
	ofDirectory currentVideoDirectory(ofToDataPath("/home/pi/videos/current", true));
	if (currentVideoDirectory.exists()) 
	{
		currentVideoDirectory.listDir();
		currentVideoDirectory.sort();
		vector<ofFile> files = currentVideoDirectory.getFiles();
		if (files.size()>0) 
		{
			videoPath = files[0].path();
		}		
	}
		
	//Somewhat like ofFboSettings we may have a lot of options so this is the current model
	ofxOMXPlayerSettings settings;
	settings.videoPath = videoPath;
	settings.useHDMIForAudio	= true;		//default true
	settings.enableTexture		= true;		//default true
	settings.enableLooping		= true;		//default true
	settings.enableAudio		= true;		//default true, save resources by disabling
	//settings.doFlipTexture = true;		//default false
	
	if (!settings.enableTexture) 
	{
		/*
		 We have the option to pass in a rectangle
		 to be used for a non-textured player to use (as opposed to the default full screen)
		 */
		settings.displayRect.width = 400;
		settings.displayRect.height = 300;
		settings.displayRect.x = 440;
		settings.displayRect.y = 200;
	}
	
	
	//so either pass in the settings
	omxPlayer.setup(settings);
	
	consoleListener.setup(this);
}

bool doSeek = false;
bool didSeek = false;
//--------------------------------------------------------------
void testApp::update()
{
	if(doSeek)
    {
        omxPlayer.seekToPosition(ofRandom(2, 220));
        doSeek = false;
        didSeek = true;
       
    }
    if(didSeek && omxPlayer.isFrameNew())
    {
        //omxPlayer.setPaused(true);
    }
	
}


//--------------------------------------------------------------
void testApp::draw()
{
	
	omxPlayer.draw(0, 0, ofGetWidth(), ofGetHeight());
	
	ofDrawBitmapStringHighlight(omxPlayer.getInfo(), 60, 60, ofColor(ofColor::black, 90), ofColor::yellow);
  
    
}

void testApp::keyPressed(int key)
{
    ofLog(OF_LOG_VERBOSE, "%c keyPressed", key);
	if (key == 'p') 
	{
		omxPlayer.setPaused(!omxPlayer.isPaused());
	}
	if (key == 'r') 
	{
        doSeek = true;
        
	}
}

void testApp::onCharacterReceived(KeyListenerEventData& e)
{
	keyPressed((int)e.character);
}
