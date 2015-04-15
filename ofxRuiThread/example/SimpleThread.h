#pragma once

#include "ofMain.h"
#include "ofxRuiThread.h"

class SimpleThread:public ofxRuiThread{
public:
	int count;
	
	SimpleThread(){
		count = -1;
	}
	
	void updateThread(){
		int numIterations = (int)ofRandom(0, 10000);
		for(int i=0; i<numIterations; i++){
			sin(cos(ofRandomuf()));
		}
		count++;
	}
};
