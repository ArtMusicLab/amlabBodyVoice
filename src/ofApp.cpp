#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	frameRate = 30;
	ofSetFrameRate(frameRate);
	gui.setup("settings");
	
	
	// opencv ..........................
	bThreshWithOpenCV = true;
	gui.add(switchVoiceControl.set("lidar control", true));
	gui.add(minArea.set("Min area", 10, 1, 100));
	gui.add(maxArea.set("Max area", 200, 1, 500));
	gui.add(threshold.set("Threshold", 128, 0, 255));
	gui.add(holes.set("Holes", false));
	
	// syphon client ..............................
	syphonClient.setup();
	//	syphonClient.setServerName("Video");
	syphonClient.setServerName("Composition");
	
	
	// audio ..........................
	sampleRate = 48000;
	
	amplitude = 0.5;
	frequency = 440;
	phase = 0.0;
	phaseInc = frequency * TWO_PI / (float)sampleRate;
	
	bufferSize = 256;
	
	inputBuffer.resize(bufferSize);
	
	gui.add(amplitudeGui.set("amplitude",0.1,0.05,1.0));
	gui.add(phaseGui.set("phase",0.0,TWO_PI/20,TWO_PI));
	gui.add(frequencyGui.set("frequency",20,100,20000));
	
	
	
	
	
	if (!ofFile("settings.xml"))
		gui.saveToFile("settings.xml");
	
	gui.loadFromFile("settings.xml");
	
	soundStream.printDeviceList();
	// which sound card to use +++++++++++++++++
	soundStream.setDeviceID(0);
	
	//	cout << (bufferSize * 2/(float)sampleRate) * 1000.f << endl;
	
	// very end of setup init
	int inChennals = 1;
	int outChennals = 2;
	// set input and output in system settings
	ofSoundStreamSetup(outChennals, inChennals, sampleRate, bufferSize, 4);
	// set input and output manually
	//	soundStream.setup(this, outChennals, inChennals, sampleRate, bufferSize, 4);
	
	
	
}

//--------------------------------------------------------------
void ofApp::update(){
	// get syphon image
	ofTexture tempTex = syphonClient.getTexture();
	ofImage tempImg;
	ofPixels tempPixels;
	tempTex.readToPixels(tempPixels);
	tempImg.setFromPixels(tempPixels);
	
	contourFinder.setMinAreaRadius(minArea.get());
	contourFinder.setMaxAreaRadius(maxArea.get());
	contourFinder.setThreshold(threshold.get());
	contourFinder.setFindHoles(holes.get());
	
	contourFinder.findContours(tempImg);
	
	for (int i = 0; i < contourFinder.getBoundingRects().size(); i++) {
		int x = contourFinder.getBoundingRects().at(i).x;
		int y = contourFinder.getBoundingRects().at(i).y;
		int w = contourFinder.getBoundingRects().at(i).width;
		int h = contourFinder.getBoundingRects().at(i).height;
		// for debug .............................................###
		ofDrawRectangle(x * scale, y * scale, w * scale, h * scale);
		
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	
	
	
	gui.draw();
	
}
//--------------------------------------------------------------

void ofApp::exit(){
	ofSoundStreamClose();
}
//--------------------------------------------------------------

void ofApp::audioIn(float * input,int bufferSize,int nChannel){
	for(int i = 0;i < bufferSize;i++){
		inputBuffer[i] = input[i];
	}
}

//--------------------------------------------------------------

void ofApp::audioOut(float *buffer, int bufferSize, int nChannel){
	
	
	// use lidar to control
	if(!switchVoiceControl.get()){
		
		for (int i = 0; i < bufferSize; i++) {
			float currentSample;
			currentSample = sin(phase + phaseGui.get()) * amplitudeGui.get() * inputBuffer[i];
			phaseInc = frequencyGui.get() * TWO_PI / (float)sampleRate;
			
			phase += phaseInc;
			buffer[i * nChannel + 0] = currentSample; // left
			buffer[i * nChannel + 1] = currentSample; // right
			
			
			//			float inputSample;
			//			inputSample = inputBuffer[i];
			//
			//			currentSample = inputSample;
			//			buffer[i * nChannel + 0] = currentSample; // left
			//			buffer[i * nChannel + 1] = currentSample; // right
			
		}
	}
	// use opencv to control
	else{
		for (int i = 0; i < bufferSize; i++) {
			float currentSample;
			currentSample = sin(phase + phaseGui.get()) * amplitudeGui.get() * inputBuffer[i];
			phaseInc = frequencyGui.get() * TWO_PI / (float)sampleRate;
			
			phase += phaseInc;
			buffer[i * nChannel + 0] = currentSample; // left
			buffer[i * nChannel + 1] = currentSample; // right
			
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	//	frequency = ofMap(x, 0, ofGetWidth(), 40, 2000);
	//	phaseInc = TWO_PI * frequency / (float) sampleRate;
	//	amplitude = ofMap(y, 0, ofGetHeight(), 1.0, 0);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
	
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
	
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
	
}
