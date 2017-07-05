#include "OpenCVFunction.h"
#include "common.h"

class OpenCVBase;

OpenCVContext::OpenCVContext(OpenCVBase *opencv) {
	_opencv = opencv;
}

OpenCVContext::~OpenCVContext() {

}

void OpenCVContext::DoAction(){

	IplImage *ipl;

	_opencv->AlgrithmInterface();
}

OpenCVBase::OpenCVBase(){
	cout << "OpenCVBase" << endl;
}


OpenCVVideo::OpenCVVideo(string video_path) {
	_cap = cvCreateFileCapture(video_path.c_str());

	cout << "OpenCVVideo" << endl;
}


void OpenCVVideo::AlgrithmInterface(){

	if (this->_cap == NULL) {
		cout << "open error!" << endl;
		exit(0);
	}
	IplImage *ipl = cvQueryFrame(_cap);
	if (ipl == NULL) {
		cout << "open error!" << endl;
		exit(0);
	}
	cvNamedWindow("video player");
	while ((char)waitKey(40) != 27) {
		//cvSmooth(ipl, ipl, CV_MEDIAN);
		cvShowImage("video player", ipl);
		ipl = cvQueryFrame(_cap);
	}


}

OpenCVImage::OpenCVImage(string img_path,int algrithm_type) {

	this->_ipl = cvLoadImage(img_path.c_str());
	if (_ipl == NULL) {
		cout << "load img fail" <<endl;
	}
	this->_algrithm_type = algrithm_type;
	cout << "OpenCVImage" <<endl;
}

void OpenCVImage::AlgrithmInterface()
{
	switch (this->_algrithm_type) {
	case 1:
		this->showImage();
		break;
	case 2:
		this->smoothProc();
		break;
	case 3:
		this->doContour();
		break;
	case 4:
		this->doColor();
	default:
		break;
	}
}

void OpenCVImage::showImage() {

	isNULL(_ipl);
	std::cout << "h=" << _ipl->height << endl;
	std::cout << "w=" << _ipl->width << endl;


	cvSetImageROI(_ipl, cvRect(10, 10, 0, 0));

	std::cout << "h=" << _ipl->roi->height << endl;
	std::cout << "w=" << _ipl->roi->width << endl;

	cvAddS(_ipl, cvScalar(150), _ipl);
	cvResetImageROI(_ipl);
	cvNamedWindow("first opencv", 1);
	cvShowImage("roi", _ipl);


}

void OpenCVImage::smoothProc(){
	cout << "smoothProc():enter!" << endl;
	cout << "h=" << _ipl->height << endl;
	cout << "w=" << _ipl->width << endl;


	cvNamedWindow("source img", 1);
	cvMoveWindow("source img", 0, 0);
	cvShowImage("source img", _ipl);

	//简单模糊处理
	IplImage *dst1 = NULL;
	dst1 = cvCreateImage(cvGetSize(_ipl),IPL_DEPTH_8U,3);
	cvSmooth(_ipl, dst1,CV_BLUR);
	cvNamedWindow("simple smooth", 1);
	cvMoveWindow("simple smooth", _ipl->width+0, 0);
	cvShowImage("simple smooth", dst1);

	//简单不带尺度变化的模糊处理
	IplImage *dst2 = NULL;
	dst2 = cvCreateImage(cvGetSize(_ipl), IPL_DEPTH_8U, 3);
	cvSmooth(_ipl, dst2, CV_BLUR_NO_SCALE);
	cvNamedWindow("simple smooth2", 1);
	cvMoveWindow("simple smooth2", 2* _ipl->width+0, 0);
	cvShowImage("simple smooth2", dst2);

	//高斯模糊处理
	/*IplImage *dst3 = NULL;
	dst3 = cvCreateImage(cvGetSize(_ipl), IPL_DEPTH_8U, 3);*/
	cvSmooth(_ipl, dst1, CV_GAUSSIAN);
	cvNamedWindow("gaussian", 1);
	cvMoveWindow("gaussian", 0, _ipl->height+0);
	cvShowImage("gaussian", dst1);

	//中值滤波处理
	/*IplImage *dst3 = NULL;
	dst3 = cvCreateImage(cvGetSize(_ipl), IPL_DEPTH_8U, 3);*/
	cvSmooth(_ipl, dst1, CV_MEDIAN);
	cvNamedWindow("Median", 1);
	cvMoveWindow("Median", _ipl->width + 0, _ipl->height + 0);
	cvShowImage("Median", dst1);

	//腐蚀处理
	cvErode(_ipl,dst1,NULL,2);
	cvNamedWindow("Erode", 1);
	cvMoveWindow("Erode", 2*_ipl->width + 0, _ipl->height + 0);
	cvShowImage("Erode", dst1);

	//膨胀处理
	cvDilate(_ipl,dst1);
	cvNamedWindow("Dilate", 1);
	cvMoveWindow("Dilate", 3 * _ipl->width + 0, _ipl->height + 0);
	cvShowImage("Dilate", dst1);

}

void OpenCVImage::doContour() {
	Mat src = imread("res/apple.jpg");
	Mat dst = imread("res/apple1.jpg");
	cvNamedWindow("Contour0", 1);
	cvMoveWindow("Contour0", 100, 100);
	cvShowImage("Contour0", &(IplImage(src)));

	cvNamedWindow("Contour1", 1);
	cvMoveWindow("Contour1", 100, 100);
	cvShowImage("Contour1", &(IplImage(dst)));


	IplImage* img = cvLoadImage("res/apple.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* img_temp = cvCreateImage(cvGetSize(img), 8, 1);
	cvThreshold(img, img,128,255,CV_THRESH_BINARY);
	//Mat thresh = (src > 252)&(src <= 255);
	//cvDilate(&(IplImage(thresh)), &(IplImage(thresh)), NULL, 4);
	//cvErode(&(IplImage(thresh)), &(IplImage(thresh)), NULL, 6);
	//vector< vector<Point2i> > contours1;
	CvMemStorage *contours  = cvCreateMemStorage(0);
	CvSeq *first_contour = NULL, *c = NULL;
	img_temp = cvCloneImage(img);
	cvFindContours(img_temp, contours, &first_contour, sizeof(CvContour),
		CV_RETR_CCOMP);// , sizeof(CvContour), CV_RETR_CCOMP);

	//cvZero(img_temp);
	cvDrawContours(
		img_temp,
		first_contour,
		cvScalar(100),
		cvScalar(100),
		1
		);

	cvNamedWindow("Contour3", 1);
	cvMoveWindow("Contour3", 100, 100);
	cvShowImage("Contour3", img_temp);

	Mat g_dex = src - dst;


	cvNamedWindow("Contour2", 1);
	cvMoveWindow("Contour2", 100, 100);
	cvShowImage("Contour2", &(IplImage(g_dex)));

	Mat thresh1 = (dst > 10)&(dst < 308);
	cvNamedWindow("Contourdst", 1);
	cvMoveWindow("Contourdst", 100, 100);
	cvShowImage("Contourdst", &(IplImage(thresh1)));

//	cvDilate(&img, &img, NULL, 4);
	//cvErode(&img, &img, NULL, 7);
	//


}
void OpenCVImage::doColor() {
	Mat src = imread("res/blue.png", CV_LOAD_IMAGE_COLOR);
	int color_type = 0;
	relizeColor(src, color_type);
	cout << "the color type is :" << color_type<<endl;
}
//识别图像中的颜色
int OpenCVImage::relizeColor(Mat src, int &color_type) {

	Mat hsv;
	Mat imgThresholded;


	cvtColor(src, hsv, COLOR_BGR2HSV);

	const Scalar hsvRedLo(0, 40, 40);
	const Scalar hsvRedHi(7, 255, 255);

	const Scalar hsvYellowLo(20, 40, 40);
	const Scalar hsvYellowHi(40, 255, 255);

	const Scalar hsvGreenLo(50, 40, 40);
	const Scalar hsvGreenHi(70, 255, 255);

	const Scalar hsvBlueLo(75, 40, 40);
	const Scalar hsvBlueHi(140, 255, 255);

	const Scalar hsvDeepRedLo(150, 40, 40);
	const Scalar hsvDeepRedHi(180, 255, 255);

	vector<Scalar> hsvLo{ hsvRedLo,hsvYellowLo, hsvGreenLo, hsvBlueLo,hsvDeepRedLo };
	vector<Scalar> hsvHi{ hsvRedHi,hsvYellowHi, hsvGreenHi, hsvBlueHi,hsvDeepRedHi };



	for (int colorIdx = 0; colorIdx < hsvLo.size(); colorIdx++) {
		inRange(hsv, hsvLo[colorIdx], hsvHi[colorIdx], imgThresholded);
		cvNamedWindow("hsv", 1);
		cvShowImage("hsv", &(IplImage(imgThresholded)));
		Mat imgThresholded1;
		// 转换成二值图
		threshold(imgThresholded, imgThresholded1, 1, 255, THRESH_BINARY);

		vector<vector<Point> > contours0;
		vector<Vec4i> hierarchy;
		findContours(imgThresholded1, contours0, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

		for (int idx = 0; idx < contours0.size(); idx++)
		{
			Rect bound = boundingRect(Mat(contours0[idx]));
			Point bc = Point(bound.x + bound.width / 2,
				bound.y + bound.height / 2);
			uchar x = imgThresholded.at<uchar>(bc);
			if (x > 0)
			{
				cout << "the color is :" <<colorIdx<< endl;
				color_type = colorIdx;
				return 0;
			}
		}
	}
	return 1;
}


