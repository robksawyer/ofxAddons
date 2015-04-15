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
based on the article found here http://www.jhlabs.com/java/tablet/ by Jerry Huxtable 
*/


#include "ofxTabletOSX.h"
#import "Cocoa/Cocoa.h"

static ofxTabletOSX* tabletPtr = NULL;

@interface ofxCocoaTabletEvents: NSApplication
ofPoint oldPenPos;
bool bIsEraser;
bool bIsProximity;
@end

@implementation ofxCocoaTabletEvents

- (id) init{
	if(self = [super init]){
		oldPenPos.x = 0.0f;
		oldPenPos.y = 0.0f;
		bIsEraser = bIsProximity = false;
	}
	return self;
}

- (void) sendEvent:(NSEvent *)theEvent{
	switch( [theEvent type] ){
		case NSTabletProximity:{
			ofxTabletArgs e;
			NSPoint pos = [theEvent locationInWindow];
			e.position.x = pos.x;
			e.position.y = pos.y;
			e.tilt.x = e.tilt.y = e.rotation = e.tangentialPressure = e.pressure = 0.0f;
			e.button = [theEvent buttonMask];
			bIsEraser = [theEvent pointingDeviceType] == NX_TABLET_POINTER_ERASER;
			e.isEraser = bIsEraser;
			bIsProximity = [theEvent isEnteringProximity];
			if(bIsProximity){
				ofNotifyEvent(tabletPtr->penEnter, e, tabletPtr);
			} else {
				ofNotifyEvent(tabletPtr->penLeave, e, tabletPtr);
			}
			break;
		}
			
		case NSMouseMoved:{
			if(bIsProximity){
				NSPoint pos = [theEvent locationInWindow];
				ofxTabletArgs e;
				e.position.x = pos.x;
				e.position.y = ofGetHeight() - pos.y;
				e.button = 0;
				e.rotation = 0;
				e.pressure = 0;
				e.tangentialPressure = 0;
				e.tilt.x = 0;
				e.tilt.y = 0;
				e.isEraser = bIsEraser;
				ofNotifyEvent(tabletPtr->penMove, e, tabletPtr);
			}
			break;
		}
			
		case NSTabletPoint:{
			NSPoint pos = [theEvent locationInWindow];
			NSPoint tilt = [theEvent tilt];
			ofxTabletArgs e;
			e.position.x = pos.x;
			e.position.y = ofGetHeight() - pos.y;
			e.button = [theEvent buttonMask];
			e.rotation = [theEvent rotation];
			e.pressure = [theEvent pressure];
			e.tangentialPressure = [theEvent tangentialPressure];
			e.tilt.x = tilt.x;
			e.tilt.y = tilt.y;
			e.isEraser = bIsEraser;
			ofNotifyEvent(tabletPtr->penDown, e, tabletPtr);
			break;
		}
			
		case NSLeftMouseDragged:{
			if( [theEvent subtype] == NSTabletPointEventSubtype){
				NSPoint pos = [theEvent locationInWindow];
				if(oldPenPos.x == pos.x && oldPenPos.y == pos.y)break;
				NSPoint tilt = [theEvent tilt];
				ofxTabletArgs e;
				e.position.x = pos.x;
				e.position.y = ofGetHeight() - pos.y;
				e.button = [theEvent buttonMask];
				e.rotation = [theEvent rotation];
				e.pressure = [theEvent pressure];
				e.tangentialPressure = [theEvent tangentialPressure];
				e.tilt.x = tilt.x;
				e.tilt.y = tilt.y;
				e.isEraser = bIsEraser;
				ofNotifyEvent(tabletPtr->penDragged, e, tabletPtr);
				oldPenPos.x = pos.x;
				oldPenPos.y = pos.y;
			}
			break;
		}
			
		case NSLeftMouseUp:{
			if( [theEvent subtype] == NSTabletPointEventSubtype){
				NSPoint pos = [theEvent locationInWindow];
				NSPoint tilt = [theEvent tilt];
				ofxTabletArgs e;
				e.position.x = pos.x;
				e.position.y = ofGetHeight() - pos.y;
				e.button = [theEvent buttonMask];
				e.rotation = [theEvent rotation];
				e.pressure = [theEvent pressure];
				e.tangentialPressure = [theEvent tangentialPressure];
				e.tilt.x = tilt.x;
				e.tilt.y = tilt.y;
				e.isEraser = bIsEraser;
				ofNotifyEvent(tabletPtr->penUp, e, tabletPtr);
			}
			break;
		}
		default:
			break;
	}
	[super sendEvent: theEvent];
}
@end

ofxTabletOSX::ofxTabletOSX(){
	tabletPtr = this;
	[ofxCocoaTabletEvents poseAsClass: [NSApplication class]];
}

