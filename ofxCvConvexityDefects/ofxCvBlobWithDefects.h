#pragma once

#include "ofxCvblob.h"

class ofxCvDefect{
public:
	ofxCvDefect( const ofPoint& _start, const ofPoint& _end, const ofPoint& _depth, float _depthVal):
	startPoint(_start), endPoint(_end), depthPoint(_depth), depth(_depthVal){}
	
	ofPoint startPoint, endPoint, depthPoint;
	float depth;
};

class ofxCvBlobWithDefects: public ofxCvBlob{
public:
	
	void drawDefects(){
		ofSetColor(255, 0, 255);
		ofNoFill();
		for(vector<ofxCvDefect>::iterator it = defects.begin(); it != defects.end(); ++it){
			ofxCvDefect& defect = *it;
			ofTriangle( defect.startPoint.x, defect.startPoint.y, defect.endPoint.x, defect.endPoint.y, defect.depthPoint.x, defect.depthPoint.y);
		}
	}
	
	vector<ofxCvDefect> defects;
protected:
	
};