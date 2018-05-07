#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxMidi.h"
#include "ofxSyphon.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"

using namespace ofxCv;
using namespace cv;

class ofApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
	void exit();
	
	ofSoundStream 			soundStream;

	
	void audioOut(float * buffer,int bufferSize,int nChannel);
	void audioIn(float * input,int bufferSize,int nChannel);
	
	float		frequency;
	int			sampleRate;
	int			bufferSize;
	double		phase;
	double 		phaseInc;
	float		amplitude;
	int			frameRate;
	vector<float>	inputBuffer;
	
	ofxPanel			gui;
	// switch opencv or lidar driving sound/voice 
	ofParameter<bool>	switchVoiceControl;
	
	
	ofParameter<float>	amplitudeGui;
	ofParameter<float>	phaseGui;
	ofParameter<float>	frequencyGui;
	
	// opencv
	bool 			bThreshWithOpenCV;
	ofxCv::ContourFinder contourFinder;
	ofParameter<float> minArea, maxArea, threshold;
	ofParameter<bool> holes;
	
	
	// syphon
	ofFbo				syphonFbo;
	ofxSyphonClient 	syphonClient;
	
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
};
