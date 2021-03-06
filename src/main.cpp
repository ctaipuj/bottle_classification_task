#include "../include/perception.h"
#include "../include/detection.h"
#include "../include/test.h"
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

void properties();

static void usage(){
    std::cerr << "Usage of perception capabilites evaluator 1.0\n" //<< argv[0] << " <option(s)> SOURCES"
              << "Options:\n\n"
              << "\t1. Argument: -d for detection data -p for position data\n"
              << "\t\tWhen position data is used. 1 bottle per type in the frame is allowed\n\n"
              << "\t2. Argument: number of the first photo to evaluate\n"
              << "\t3. Argument: number of the last photo to evaluate\n\n"
              << "\tData is saved to cv_detection_data.txt in the parent directory when -d mode is activated. cv_position_data.txt otherwise\n"
              << "Press a key to exit\n"
              << "The images MUST be in the ../images/test directory\n\n\n"
              << "To use the software correctly it is needed both RGB and DEPTH frames\n\n\n"
              << "\t\t\t\tCTAI-PUJ 2017-NICO\n"
              << std::endl;
}

int main(int argc, char* argv[]){
	
	/////////////////////SEGMENTO DIFERENTE/////////////////////////////
	if (argc!=4){
		usage();
		return 0;
	}
	int band;
	string a=argv[2];
	int fi=atoi(a.c_str());
	string b=argv[3];
	int li=atoi(b.c_str());
	ofstream file;
	string arg1=argv[1];
	if (arg1=="-d"||arg1=="-D"){	
		band=1;
		file.open("../cv_detection_data.txt",ios::app);
	}else if(arg1=="-p"||arg1=="-P"){
		band=2;
		file.open("../cv_position_data.txt",ios::app);
	}else{
		usage();
		return 0;
	}
	/////////////////////////////////////////////////

	double fx=1.0466649972613395e+03;//9.8560256011624597e+02;//mm/px
	double fy=1.0466649972613395e+03;//9.8560256011624597e+02;//mm/px
	double cx=640.0;
	double cy=512.0;
	
	int max_detection=100;
	
	space s;
	polycolor c;
	test t;
	cv::Mat image; // siempre la matriz image carga la imagen
	cv::Mat depth;
	///////////////////////////////////////////////////////////////
	//SEGMENTO DE CODIGO DIFERENTE//
	std::stringstream colordir;
	std::stringstream depthdir;
	std::string color_path="../images/rgb_picture_";
	std::string depth_path="../images/depth_picture_";
	std::string ending=".tiff";
	std::string color_directory;
	std::string depth_directory;
	
	for(int i=fi;i<=li;i++){
		//int i =1;
	
		colordir<<color_path<<i<<ending;
		depthdir<<depth_path<<i<<ending;
	
		color_directory=colordir.str();
		depth_directory=depthdir.str();
	
		colordir.str("");
		depthdir.str("");
	
		image=cv::imread(color_directory); // siempre la matriz image carga la imagen
		depth=cv::imread(depth_directory,CV_16UC1);
	
		////////////////////////////////////////////////////////////
		
		cv::Mat image2=image.clone();
		cv::Mat image3=image.clone();
		//cv::imshow("ghjk",depth);
		cv::Mat imageblurred;
		cv::Mat hsv;
    
		cv::GaussianBlur(image,imageblurred,cv::Size(31,31),0); /
		cv::cvtColor(imageblurred,hsv,CV_BGR2HSV); 
		vector<cv::Mat> canaleshsv; 
		vector<cv::Mat> canalesycrcb;
	
		vector<cv::Point> colorpoints;
		vector<cv::Point> greenpoints;
		vector<cv::Point> whitepoints;
	
		vector<cv::Point> colorpoints_depth;
		vector<cv::Point> greenpoints_depth;
		vector<cv::Point> whitepoints_depth;
	
		vector<vector<cv::Point> > data_color;
		vector<vector<cv::Point> > data_green;
		vector<vector<cv::Point> > data_white;
	
		vector<vector<double> > color_coordinates;
		vector<vector<double> > green_coordinates;
		vector<vector<double> > white_coordinates;
	
	
		cv::namedWindow("Colores Segmentada", CV_WINDOW_NORMAL );
		cv::namedWindow("Verde Segmentada", CV_WINDOW_NORMAL );
		cv::namedWindow("Blancos Segmentada", CV_WINDOW_NORMAL );
	
		cv::split(hsv,canaleshsv);
	
		data_color=c.findcontours(c.findcolors(c.getwhite(hsv,25,133),c.getred(canaleshsv[0],50,130),c.getgreen(canaleshsv[0],55,96),c.getblue(canaleshsv[0],95,130),c.getvalue(canaleshsv[2],90,144)),90,670,max_detection);//110 para no detectar manijas. 90 u 88 detecta tapas
	
		data_green=c.findcontours(c.findgreen(c.getgreen(canaleshsv[0],55,88),c.getwhite(hsv,25,133),c.getvalue(canaleshsv[2],72,144)),193,515,max_detection);//minimo 88 400

		data_white=c.findcontours(c.findwhite(c.getwhite(hsv,25,133),c.getvalue(canaleshsv[2],90,144)),110,705,max_detection);		
	
		if(data_color.size()!=0){
			colorpoints=s.getpoints(data_color);
			colorpoints_depth=s.scale(colorpoints,image.cols,image.rows,depth.cols,depth.rows);
			color_coordinates=s.xyz_coord(s.find_depth(colorpoints_depth,colorpoints,depth,data_color),fx,fy,cx,cy);
			cv::imshow("Colores Segmentada",c.drawcontors(image,data_color,255,127,80));//110 para no detectar manijas. 90 u 88 detecta tapas


		}
		if(data_green.size()!=0){
			greenpoints=s.getpoints(data_green);
			greenpoints_depth=s.scale(greenpoints,image.cols,image.rows,depth.cols,depth.rows);
			green_coordinates=s.xyz_coord(s.find_depth(greenpoints_depth,greenpoints,depth,data_green),fx,fy,cx,cy);
			cv::imshow("Verde Segmentada",c.drawcontors(image,data_green,0,206,209));//400

		}
		if(data_white.size()!=0){
			whitepoints=s.getpoints(data_white);
			whitepoints_depth=s.scale(whitepoints,image.cols,image.rows,depth.cols,depth.rows);
			white_coordinates=s.xyz_coord(s.find_depth(whitepoints_depth,whitepoints,depth,data_white),fx,fy,cx,cy);
			cv::imshow("Blancos Segmentada",c.drawcontors(image,data_white,255,218,185));
		
	}
		
		vector<vector<double> > p; //data_to_ros;
			
		p= s.push_data(s.getgeometrydata(color_coordinates,data_color,1,fx,fy,1),s.getgeometrydata(green_coordinates,data_green,2,fx,fy,1),s.getgeometrydata(white_coordinates,data_white,3,fx,fy,1));
	
		//data_to_ros=p;
	
		for (int j=0;j<p.size();j++){
			
			cout<<" X "<<p[j][0]<<" Y "<<p[j][1]<<" Z "<<p[j][2]<<" w "<<p[j][3]<<" x "<<p[j][4]<<" y "<<p[j][5]<<" z "<<p[j][6]<<" Height "<<p[j][7]<<" Width "<<p[j][8]<<" Type "<<p[j][9]<<"\n";
		
			file<<" X "<<p[j][0]<<" Y "<<p[j][1]<<" Z "<<p[j][2]<<" w "<<p[j][3]<<" x "<<p[j][4]<<" y "<<p[j][5]<<" z "<<p[j][6]<<" Height "<<p[j][7]<<" Width "<<p[j][8]<<" Type "<<p[j][9]<<"\n";
		}
		
	cv::waitKey(0);
	std::string save;
	std::stringstream savve;
	savve<<"/home/ctai/algorithm/processed/processed"<<i<<".tiff";
	save=savve.str();
	cv::imwrite(save,image);
	savve.str("");
	}
	file.close();
	cv::waitKey(0); //OJO AL WAITKEY 0 VS 27
	return 0;
}
