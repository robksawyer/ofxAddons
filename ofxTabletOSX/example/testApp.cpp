#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0,0,0);
	ofSetBackgroundAuto(true);
	bDoDraw = false;
	position.set(0,0);
	radius = 0;
	ofAddListener(tablet.penDragged, this, &testApp::onPenDragged);
	ofAddListener(tablet.penUp, this, &testApp::onPenUp);
	ofAddListener(tablet.penDown, this, &testApp::onPenDown);
	ofAddListener(tablet.penEnter, this, &testApp::onPenEnter);
	ofAddListener(tablet.penLeave, this, &testApp::onPenLeave);
	ofAddListener(tablet.penMove, this, &testApp::onPenMove);
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	if(bDoDraw){
		ofCircle(position.x, position.y, radius + 10);
	}
}

void testApp::onPenDragged(ofxTabletArgs& e){
	position = e.position;
	radius = e.pressure * 100;
}

void testApp::onPenUp(ofxTabletArgs& e){
	position = e.position;
	radius = e.pressure * 100;
	ofSetColor(100, 100, 100);
}

void testApp::onPenDown(ofxTabletArgs& e){
	position = e.position;
	radius = e.pressure * 100;
	if(e.isEraser){
		ofSetColor(0,0,0);
	} else {
		ofSetColor(255, 255, 255);
	}
}

void testApp::onPenEnter(ofxTabletArgs& e){
	position = e.position;
	radius = 0;
	bDoDraw = true;
	ofSetColor(100, 100, 100);
}

void testApp::onPenLeave(ofxTabletArgs& e){
	position = e.position;
	radius = 0;
	bDoDraw = false;
}

void testApp::onPenMove(ofxTabletArgs& e){
	position = e.position;
	radius = 0;
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

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

