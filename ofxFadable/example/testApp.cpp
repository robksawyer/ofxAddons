#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(255, 255, 255);
	cam.initGrabber(320, 240);
	cam.setFadeSeconds(5.0f);
	rect.setFadeSeconds(2.0f);
	rect.setUnitColor(1.0f, 0.0f, 0.0f);
}

//--------------------------------------------------------------
void testApp::update(){
	cam.update();
	cam.updateFade();
	rect.updateFade();
}

//--------------------------------------------------------------
void testApp::draw(){
	cam.draw(20, 20);
	rect.draw(300, 300, 300, 300);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	switch(key){
		case 'i':
			cam.fadeIn();
			rect.fadeIn();
			printf("fading in");
			break;
		case 'o':
			cam.fadeOut();
			rect.fadeOut();
			printf("fading out");
			break;
	}
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

