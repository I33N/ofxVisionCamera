#include "CameraPinhole.h"

OCVCamPinhole::OCVCamPinhole()
{

}

OCVCamPinhole::OCVCamPinhole(const std::string matIntrinsicFile, const std::string matExtrinsicFile)
{
	mMatIntrinsic = (CvMat*) cvLoad(matIntrinsicFile.c_str());	
	mMatIntrinsic = (CvMat*) cvLoad(matExtrinsicFile.c_str());	
}

namespace cinder{

CameraPinhole::CameraPinhole() :
	CameraPersp()
{

}

CameraPinhole::CameraPinhole( int pixelWidth, int pixelHeight, float pixelFocal) :
	CameraPersp()
{
	setPerspective( pixelWidth, pixelHeight, pixelFocal, pixelFocal, pixelWidth/2.0f, pixelHeight/2.0f, 0.0f);
}

CameraPinhole::CameraPinhole( int pixelWidth, int pixelHeight, float alphaU, float alphaV, float centerU, float centerV, float ditortionC) :
	CameraPersp()
{
	setPerspective( pixelWidth, pixelHeight, alphaU, alphaV, centerU, centerV, ditortionC);
}

CameraPinhole::CameraPinhole( int pixelWidth, int pixelHeight, Matrix44f matIntrinsic, Matrix44f matExtrinsic) :
	CameraPersp()
{
	setPerspective( pixelWidth, pixelHeight, matIntrinsic[0,0], matIntrinsic[1,1], matIntrinsic[0,2], matIntrinsic[1,2], matIntrinsic[0,1]);

}

/*
CameraPinhole::CameraPinhole( int pixelWidth, int pixelHeight, Matrix44f matProjection)
{
	
}
*/

void CameraPinhole::setPerspective( int pixelWidth, int pixelHeight, float alphaU, float alphaV, float centerU, float centerV, float ditortionC)
{
	mFov		= 2.0f * math<float>::tan( 2.0f * alphaU / (float)pixelWidth);
	mAspectRatio 	= ( alphaV / alphaU ) * ( pixelWidth / (float)pixelHeight );
	mNearClip 	= 0.1f;
	mFarClip	= 10000.0f;

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
	float *m = mProjectionMatrix.m;
	m[ 0] =  2.0f * mAlphaU / (float) mPixelW;
	m[ 4] =  0.0f;
	m[ 8] =  ( 2.0f * mCenterU / (float) mPixelW ) - 1.0f;
	m[12] =  0.0f;

	m[ 1] =  0.0f;
	m[ 5] =  - 2.0f * mAlphaV / (float) mPixelH;
	m[ 9] =  ( ( - 2.0f * mCenterV + 2.0f * mPixelH ) / mPixelH ) - 1.0f;
	m[13] =  0.0f;

	m[ 2] =  0.0f;
	m[ 6] =  0.0f;
	m[10] =  1.0f;
	m[14] =  - mNearClip;

	m[ 3] =  0.0f;
	m[ 7] =  0.0f;
	m[11] = 1.0f;
	m[15] =  0.0f;
/*
	m = mInverseProjectionMatrix.m;
	m[ 0] =  0.0f;
	m[ 4] =  0.0f;
	m[ 8] =  0.0f;
	m[12] =  0.0f;

	m[ 1] =  0.0f;
	m[ 5] =  0.0f;
	m[ 9] =  0.0f;
	m[13] =  0.0f;

	m[ 2] =  0.0f;
	m[ 6] =  0.0f;
	m[10] =  0.0f;
	m[14] =  0.0f;

	m[ 3] =  0.0f;
	m[ 7] =  0.0f;
	m[11] =  0.0f;
	m[15] =  0.0f;
*/
}

} // namespace cinder
