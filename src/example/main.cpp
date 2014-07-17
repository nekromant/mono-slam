#include <opencv2/opencv.hpp>
#include <ctime>
#include "vslamRansac.hpp"
#include <fstream>
#include <string>



int main(int argc, char** argv)
{
    
    

	std::cout << "Starting monoslam_exec" << std::endl;
    
    
    std::ofstream ofile;
    ofile.open("/Volumes/HD2/out.txt");
    
    
	cv::Mat frame;
	VSlamFilter slam("/Volumes/HD2/img/conf.cfg");
    
    std::ifstream fimgs;
    fimgs.open("/Volumes/HD2/img/data/d1/t.tex");
    

    double old_time = 0;
	
    for (int i = 0 ;; i++) {
        
        std::string imgpath;

        fimgs >> imgpath;
        if (imgpath == "") {
            break;
        }

        
        std::stringstream ss(imgpath);
        std::string word;
        while( getline(ss, word, '/') );
        

        std::stringstream sw2(word);
        double time;
        sw2 >> time;

        cv::Mat frame = cv::imread(imgpath);
        
        slam.processNewFrame(frame, time);
        slam.drawPrediction();
        ofile << slam.getState().transpose().segment(3, 4) << std::endl;
        std::cout << slam.getState().transpose().segment(3, 4) << std::endl;
	}
    
    return 0;
}

