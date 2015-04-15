#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	for(int i=0; i<NUM_THREADS; i++){
		threads[i].initAndSleep();
	}
}

//--------------------------------------------------------------
void testApp::update(){
	for(int i=0; i<NUM_THREADS; i++){
	//	threads[i].updateOnce();
	}
	
	for(int i=0; i<NUM_THREADS; i++){
		threads[i].waitToFinish();
	}
	
	string info = "main thread:" + ofToString(ofGetFrameNum(), 0) + " ";
	for(int i=0; i<NUM_THREADS; i++){
		info += "thread:" + ofToString(i,0) + ":" + ofToString(threads[i].count, 0) + " ";
	}
	info += "\n";
	cout << info << endl;
}

//--------------------------------------------------------------
void testApp::draw(){
	
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

