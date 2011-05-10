#include "CameraPinhole.h"

//OCVCamPinhole::OCVCamPinhole()
//{
//
//}
//
//OCVCamPinhole::OCVCamPinhole(const std::string matIntrinsicFile, const std::string matExtrinsicFile)
//{
//	mMatIntrinsic = (CvMat*) cvLoad(matIntrinsicFile.c_str());	
//	mMatIntrinsic = (CvMat*) cvLoad(matExtrinsicFile.c_str());	
//}

CameraPinhole::CameraPinhole() :
	ofCamera()
{

}

CameraPinhole::CameraPinhole( int pixelWidth, int pixelHeight, float pixelFocal) :
	ofCamera()
{
	setPerspective( pixelWidth, pixelHeight, pixelFocal, pixelFocal, pixelWidth/2.0f, pixelHeight/2.0f, 0.0f);
}

CameraPinhole::CameraPinhole( int pixelWidth, int pixelHeight, float alphaU, float alphaV, float centerU, float centerV, float ditortionC) :
	ofCamera()
{
	setPerspective( pixelWidth, pixelHeight, alphaU, alphaV, centerU, centerV, ditortionC);
}

//CameraPinhole::CameraPinhole( int pixelWidth, int pixelHeight, Matrix44f matIntrinsic, Matrix44f matExtrinsic) :
//	ofCamera()
//{
//	setPerspective( pixelWidth, pixelHeight, matIntrinsic[0,0], matIntrinsic[1,1], matIntrinsic[0,2], matIntrinsic[1,2], matIntrinsic[0,1]);
//
//}

/*
CameraPinhole::CameraPinhole( int pixelWidth, int pixelHeight, Matrix44f matProjection)
{
	
}
*/

void CameraPinhole::setPerspective( int pixelWidth, int pixelHeight, float alphaU, float alphaV, float centerU, float centerV, float ditortionC)
{
	setFov(2.0f * tan( 2.0f * alphaU / (float)pixelWidth));
	//aspectRatio 	= ( alphaV / alphaU ) * ( pixelWidth / (float)pixelHeight );
	setNearClip(0.1f);
	setFarClip(10000.0f);

	mAlphaU 	= alphaU;
	mAlphaV 	= alphaV;
	mCenterU 	= centerU;
	mCenterV	= centerV;
	mPixelW		= pixelWidth;
	mPixelH		= pixelHeight;

	calcProjection();
}

void CameraPinhole::calcProjection()
{
	matProjection = ofMatrix4x4(
2.0f * mAlphaU / (float) mPixelW,
0.0f,
0.0f,
0.0f,
	
0.0f,
- 2.0f * mAlphaV / (float) mPixelH,
0.0f,	
0.0f,
	
( 2.0f * mCenterU / (float) mPixelW ) - 1.0f,
( ( - 2.0f * mCenterV + 2.0f * mPixelH ) / mPixelH ) - 1.0f,
1.0f,	
1.0f,
	
0.0f,
0.0f,
- nearClip,
0.0f
);
}

void CameraPinhole::begin(ofRectangle viewport)
{
	if(!isActive) ofPushView();
	isActive = true;
	
	ofSetCoordHandedness(OF_RIGHT_HANDED);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(matProjection.getPtr());

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(ofMatrix4x4::getInverseOf(getGlobalTransformMatrix()).getPtr());

	ofViewport(viewport);
	
	//store current matrices
	if (cacheMatrices)
	{
		glGetFloatv(GL_PROJECTION_MATRIX, matProjection.getPtr());
		glGetFloatv(GL_MODELVIEW_MATRIX, matModelView.getPtr());
		hasStoredMatrices = true;
	}
}

void CameraPinhole::end() {
	if (isActive)
	{
		ofPopView();
		isActive = false;
	}
}