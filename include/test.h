#ifndef TEST_CLASS
#define TEST_CLASS

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>
#include<math.h>

class test{
	private:
	
	public:
	
	test();	
	
	std::vector<double> get_data(int cols,int rows,std::vector<std::vector<cv::Point> > contornos,int band);
	
	std::vector<double> get_data_to_print(std::vector<double> color,std::vector<double> green, std::vector<double> white, int image,int band);

};
#endif
