#pragma once
#include "OpenCVFunction.h"

class ImageTransform : public OpenCVBase
{
public:
	ImageTransform();
	virtual ~ImageTransform();

private:
	Mat kernel;

};

class Convolution : public ImageTransform {
public:
	Convolution();
	virtual ~Convolution();




};