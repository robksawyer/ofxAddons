#pragma once

#include "ofxOpenCv.h"
#include "ofxCvBlobWithDefects.h"

class ofxCvConvexityDefects{
public:
	
	ofxCvConvexityDefects();
	virtual ~ofxCvConvexityDefects();
	void findContoursAndDefects( ofxCvGrayscaleImage& input, int minArea, int maxArea, int nConsidered, bool bFindHoles, bool bUseApproximation = true);
	void draw(float x = 0, float y = 0);
	void draw(float x, float y, float width, float height);
	vector<ofxCvBlobWithDefects>& getBlobs();
	
protected:
	vector<ofxCvBlobWithDefects> blobs;
	int width, height;
	ofxCvGrayscaleImage inputCopy;
	CvMemStorage* contourStorage;
	CvMemStorage* storage;
	CvMoments* moments;
	vector<CvSeq*> cvSeqBlobs;
	
	//needed to find convexity defects
	CvSeq *seqHull;
	CvSeq *defectsSeq;
	CvConvexityDefect* defectsArray;
	CvMemStorage *hullStorage;
	CvMemStorage *defectsStorage; 	
	
	void reset();
};
