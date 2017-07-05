#ifndef _OPENCVFUNCTION_H_
#define _OPENCVFUNCTION_H_
#include <iostream>

#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

class OpenCVBase;

class OpenCVContext
{
public:
	OpenCVContext(OpenCVBase *opencv);
	virtual ~OpenCVContext();
	void DoAction();
private:
	OpenCVBase *_opencv;
	IplImage *_ipl;

};


class OpenCVBase {
	public:
		OpenCVBase();
		virtual ~OpenCVBase() {}
		virtual void AlgrithmInterface() = 0;
	private:
		

};

class OpenCVVideo : public OpenCVBase {
public:
	OpenCVVideo(string video_path);
	virtual ~OpenCVVideo() {}
	void AlgrithmInterface();

private:
	CvCapture *_cap;
	Mat frame;
	

};

class OpenCVImage : public OpenCVBase {
public:
	OpenCVImage(string img_path,int algrithm_type);
	virtual ~OpenCVImage() {}
	void AlgrithmInterface();
private:
	IplImage *_ipl;
	int _algrithm_type;

	void showImage();
	void smoothProc();
	void doContour();
	void doColor();

	int relizeColor(Mat src,int &color_type);

};

#endif