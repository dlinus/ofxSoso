/*
 *  ofxTextureObject.cpp
 *  openFrameworks
 *
 *  Created by Eric Gunther on 11/8/09.
 *  Copyright 2009 Sosolimited. All rights reserved.
 *
 */

#include "ofxTextureObject.h"

using namespace cinder;

ofxTextureObject::ofxTextureObject(int w, int h)
{
	gl::Texture::Format format;
	format.setInternalFormat( GL_RGBA );
	texture = gl::Texture::create( w, h, format );

	width = w;
	height = h;
	isCentered = false;
	
	renderDirty = true; //eg 070112
}

void ofxTextureObject::render()
{	
    //eg 070112 Added display lists.
    if(renderDirty){
        
        glDeleteLists(displayList, 1);
        glNewList(displayList, GL_COMPILE_AND_EXECUTE);

        //For when iLoadNow=false is used in constructor
        if(width==0 || height==0){
            width = texture->getWidth();
            height = texture->getHeight();
        }
        
        if(isCentered){
					gl::pushModelView();
					gl::translate(-width/2, -height/2, 0);
        }
        
        glNormal3f(0,0,1);
				gl::draw( texture );
        if(isCentered){
					gl::popModelView();
        }
        
        glEndList();
        renderDirty = false;
    }else{
		glCallList(displayList);
    }
}


void ofxTextureObject::setCentered(bool iEnable)
{
	isCentered = iEnable;
    renderDirty = true;
}


void ofxTextureObject::clear()
{
	texture.reset();
  renderDirty = true;
}