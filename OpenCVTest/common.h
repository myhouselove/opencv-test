#pragma once
#include <iostream>
using namespace std;


enum {
	OPENCV_FAIL=-2,
	OPENCV_NULL=-1,
	OPENCV_SUCCUESS=0
};



enum colorType {
	read =0,
	green,
	blue,


};

int isNULL(void *in) {
	if(in == NULL){
		cout << "pointer is null!" << endl;
		return OPENCV_NULL;
	}
	else{
		return OPENCV_SUCCUESS;
	}
}