#include "ofxCvConvexityDefects.h"


bool __sort_carea_compare( const CvSeq* a, const CvSeq* b) {
	float areaa = fabs(cvContourArea(a, CV_WHOLE_SEQ));
	float areab = fabs(cvContourArea(b, CV_WHOLE_SEQ));
	return (areaa > areab);
}


ofxCvConvexityDefects::ofxCvConvexityDefects(){
	width = 0;
	height = 0;
	moments = (CvMoments*)malloc( sizeof(CvMoments) );
	reset();
}

ofxCvConvexityDefects::~ofxCvConvexityDefects(){
	free( moments );
}

void ofxCvConvexityDefects::findContoursAndDefects(ofxCvGrayscaleImage& input, int minArea, int maxArea, int nConsidered, bool bFindHoles, bool bUseApproximation){
	IplImage* img = input.getCvImage();
	width = img->width;
	height = img->height;
	
	reset();
	
	if(inputCopy.getWidth() != width || inputCopy.getHeight() ){
		inputCopy.clear();
		inputCopy.setUseTexture(false);
		inputCopy.allocate( width, height );
	}
	
	inputCopy.setROI( input.getROI() );
	inputCopy = input;
	
	CvSeq* contourList = NULL;
	contourStorage = cvCreateMemStorage( 1000 );
	storage = cvCreateMemStorage( 1000 );
	
	hullStorage = cvCreateMemStorage( 1000 );
	defectsStorage = cvCreateMemStorage( 1000 );
	
	CvContourRetrievalMode retrieveMode = (bFindHoles) ? CV_RETR_LIST : CV_RETR_EXTERNAL;
	
	cvFindContours( inputCopy.getCvImage(), contourStorage, &contourList, sizeof(CvContour), retrieveMode, bUseApproximation ? CV_CHAIN_APPROX_SIMPLE : CV_CHAIN_APPROX_NONE);
	CvSeq* contourPtr = contourList;
	
	while( contourPtr ){
		float area = fabs( cvContourArea( contourPtr, CV_WHOLE_SEQ ) );
		if( area > minArea && area < maxArea ){
			cvSeqBlobs.push_back( contourPtr );
		}
		contourPtr = contourPtr->h_next;
	}
	
	if(cvSeqBlobs.size() > 1){
		sort( cvSeqBlobs.begin(), cvSeqBlobs.end(), __sort_carea_compare);
	}
	
	
	int minNumBlobs = MIN( nConsidered, cvSeqBlobs.size() );
	
	for(vector<CvSeq*>::iterator seqIt = cvSeqBlobs.begin(); seqIt != cvSeqBlobs.end(); ++seqIt){
		if(minNumBlobs <= 0) break;
		--minNumBlobs;
		CvSeq* cvSeq = *seqIt;
		float area = cvContourArea( cvSeq, CV_WHOLE_SEQ );
		CvRect rect = cvBoundingRect( cvSeq, 0 );
		cvMoments( cvSeq, moments );
		
		blobs.push_back( ofxCvBlobWithDefects() );
		ofxCvBlobWithDefects& blob = blobs.back();
		blob.area = fabs( area );
		blob.hole = area < 0;
		blob.length = cvArcLength( cvSeq );
		blob.boundingRect.x = rect.x;
		blob.boundingRect.y = rect.y;
		blob.boundingRect.width = rect.width;
		blob.boundingRect.height = rect.height;
		blob.centroid.x = (moments->m10 / moments->m00);
		blob.centroid.y = (moments->m01 / moments->m00);
		
		CvPoint pt;
		CvSeqReader reader;
		cvStartReadSeq( cvSeq, &reader, 0 );
		
		for(int j=0; j<cvSeq->total; ++j){
			CV_READ_SEQ_ELEM( pt, reader );
			blob.pts.push_back( ofPoint( (float)pt.x, (float)pt.y ) );
		}
		blob.nPts = blob.pts.size();
		
		seqHull = cvConvexHull2( cvSeq, hullStorage, CV_COUNTER_CLOCKWISE, 0 );
		defectsSeq = cvConvexityDefects( cvSeq, seqHull, NULL );
		
		CvConvexityDefect defect;
		cvStartReadSeq( defectsSeq, &reader, 0 );
		int numDefects = defectsSeq->total;
		for(int i=0; i<numDefects; ++i){
			CV_READ_SEQ_ELEM( defect, reader );
			CvPoint& startPt = *(defect.start);
			CvPoint& endPt = *(defect.end);
			CvPoint& depthPt = *(defect.depth_point);
			blob.defects.push_back( ofxCvDefect( ofPoint( startPt.x, startPt.y ), ofPoint( endPt.x, endPt.y ), ofPoint(depthPt.x, depthPt.y), (float)defect.depth ) );
		}
		cout << blob.defects.size() << endl;
		
	}	
	
	
	if( contourStorage ) cvReleaseMemStorage( &contourStorage );
	if( storage ) cvReleaseMemStorage( &storage );
	
	if( hullStorage ) cvReleaseMemStorage( &hullStorage );
	if( defectsStorage ) cvReleaseMemStorage( &defectsStorage );
}

void ofxCvConvexityDefects::draw(float x, float y){
	draw(x, y, width, height);
}

void ofxCvConvexityDefects::draw(float x, float y, float width, float height){
	float scaleX = width / this->width;
	float scaleY = height / this->height;
	
	ofSetColor( 0xDD00CC );
	glPushMatrix();
	glTranslatef( x, y, 0.0f );
	glScalef(scaleX, scaleY, 1.0f);
	
	for(vector<ofxCvBlobWithDefects>::iterator blobIt = blobs.begin(); blobIt != blobs.end(); ++blobIt){
		blobIt->draw();
		blobIt->drawDefects();
	}
	glPushMatrix();
}

vector<ofxCvBlobWithDefects>& ofxCvConvexityDefects::getBlobs(){
	return blobs;
}

void ofxCvConvexityDefects::reset(){
	cvSeqBlobs.clear();
	blobs.clear();
}
