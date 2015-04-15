/* 
 * Copyright (c) 2009, Rui Madeira
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * http://creativecommons.org/licenses/LGPL/2.1/
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

/*
 the contrast and brightness algorithm is taken from the "OpenCV - Processing and Java Library" 
 which can be downloaded here: http://ubaa.net/shared/processing/opencv/
 */

#include "ofxCvBrightnessContrast.h"

ofxCvBrightnessContrast::ofxCvBrightnessContrast(){
	brightnessVal = contrastVal = 0.0f;
}

void ofxCvBrightnessContrast::setContrast(ofxCvImage& img, float amount){
	setBrightnessAndContrast(img, brightnessVal, amount);
}

void ofxCvBrightnessContrast::setBrightness(ofxCvImage& img, float amount){
	setBrightnessAndContrast(img, amount, contrastVal);
}

void ofxCvBrightnessContrast::setBrightnessAndContrast(ofxCvImage& img, float brightnessAmount, float contrastAmount){
	brightnessVal = MAX(-127, MIN(127, brightnessAmount));
	contrastVal = MAX(-127, MIN(127, contrastAmount));
	
	unsigned char data[ 256 ];
	CvMat * matrix;
	double delta, a, b;
	
	matrix = cvCreateMatHeader( 1, 256, CV_8UC1 );
    cvSetData( matrix, data, 0 );
	
	if ( contrastVal>0 ) {
        delta = (127.0f*contrastVal) / 128.0f;
        a = 255.0f / ( 255.0f-(delta*2.0f) );
        b = a * (brightnessVal-delta);
    }
    else {
		delta = (-128.0f*contrastVal) / 128.0f;
		a = ( 256.0f-(delta*2.0f) ) / 255.0f;
		b = ( a*brightnessVal )+delta;
    }
	
	for( int i=0; i<256; i++ ) {
		int value = cvRound( (a*i)+b );
		data[i]	= (unsigned char) min( max(0,value), 255 );
	}
	
    cvLUT( img.getCvImage(), img.getCvImage(), matrix );
	cvReleaseMat( &matrix );
	
}
