#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0,0,0);
	cam.initGrabber(CAM_W, CAM_H);
	camImg.allocate(CAM_W, CAM_H);
}

//--------------------------------------------------------------
void testApp::update(){
	cam.grabFrame();
	if(cam.isFrameNew()){
		camImg.setFromPixels(cam.getPixels(), CAM_W, CAM_H);
		brightnessContrast.setBrightnessAndContrast(camImg, brightness, contrast);
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	string info = "brightness:" + ofToString(brightness) + "\n" + 
				  "contrast:" + ofToString(contrast) + "\n" +
				  "press 'q'/'a' to increase/decrease brightness\n" +
			      "press 'w'/'s' to increate/decrease contrast";
	
	ofDrawBitmapString(info, 20, 20);
	cam.draw(20, 70, 320, 240);
	camImg.draw(360, 70, 320, 240);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	switch(key){
		case 'q':
			if(brightness < 127){
				brightness++;
			}
			break;
		case 'a':
			if(brightness > -127){
				brightness--;
			}
			break;
		case 'w':
			if(contrast < 127){
				contrast++;
			}
			break;
		case 's':
			if(contrast > -127){
				contrast--;
			}
			break;
	}
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

