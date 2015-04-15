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


#pragma once

#include "ofxOpenCv.h"

class ofxCvBrightnessContrast{
public:
	ofxCvBrightnessContrast();
	void setContrast(ofxCvImage& img, float amount);
	void setBrightness(ofxCvImage& img, float amount);
	void setBrightnessAndContrast(ofxCvImage& img, float brightnessAmount,float contrastAmount);
	
protected:
	float brightnessVal, contrastVal;
};

