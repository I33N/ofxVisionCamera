#pragma once

#include "ofCamera.h"

//#include "cv.h"
//#include "cxcore.h"
//
//class OCVCamPinhole
//{
//
//public:
//
//	OCVCamPinhole();
//	OCVCamPinhole(const std::string matIntrinsicFile, const std::string matExtrinsicFile);
//	
//protected:
//
//	CvMat* mMatIntrinsic;
//	CvMat* mMatExtrinsic;	
//	
//
//};

class CameraPinhole : public ofCamera
{

public:

	CameraPinhole();
	CameraPinhole( int pixelWidth, int pixelHeight, float alphaU, float alphaV, float centerU, float centerV, float ditortionC = 0);
	CameraPinhole( int pixelWidth, int pixelHeight, float pixelFocal);
	//CameraPinhole( int pixelWidth, int pixelHeight, Matrix44f matIntrinsic, Matrix44f matExtrinsic);
	//CameraPinhole( int pixelWidth, int pixelHeight, Matrix44f matProjection);

	void setPerspective(int pixelWidth, int pixelHeight, float alphaU, float alphaV, float centerU, float centerV, float ditortionC = 0);

	//virtual bool            isPersp() const { return true; }
	
	virtual void begin(ofRectangle viewport = ofGetCurrentViewport());
	virtual void end();
	
protected:
	
	virtual void calcProjection();
	
	float 	mAlphaU;
	float 	mAlphaV;
	float	mCenterU;
	float 	mCenterV;
	int 	mPixelW;
	int 	mPixelH;
};
