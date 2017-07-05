#include "OpenCVFunction.h"
using namespace std;
using namespace cv;

int main() {
	// 读入一张图片（游戏原画）    
//	Mat img = imread("pic.png");
	// 创建一个名为 "游戏原画"窗口    
	//IplImage *iplimage = cvLoadImage("pic.png");
	int select = 0;
	string img_path = "res/noise.png";
	string video_path = "res/test.avi";

	OpenCVContext *oc= NULL;
	cout << "OpenCV Example Test case!" << endl;
	cout << "1.Show a image and set interest ROI Region!" <<endl;
	cout << "2.Show a Video And Deal something" <<endl;
	cout << "Please Input your Choose:" << endl;
	cin >> select;
	switch (select) {
	case 1:
		oc = new OpenCVContext(new OpenCVImage(img_path,1));
		break;
	case 2:
		oc = new OpenCVContext(new OpenCVVideo(video_path));
		break;
	case 3:
		oc = new OpenCVContext(new OpenCVImage(img_path,2));
		break;
	case 4:
		oc = new OpenCVContext(new OpenCVImage(img_path, 3));
		break;
	case 5:
		oc = new OpenCVContext(new OpenCVImage(img_path, 4));
		break;
	default:
		break;
	}
	if(oc != NULL)
		oc->DoAction();


	cvWaitKey();
	cvDestroyAllWindows();
	cin>>select;
}


