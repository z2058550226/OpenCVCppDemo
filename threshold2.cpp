#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char **args)
{
    Mat srcImg;
    int threshval = 70;
    Mat result;
    Mat bw = srcImg;
    srcImg = imread("/Users/butter/VscodeProjects/OpenCVCppDemo/res/sculpture.jpg");
    imshow("image", srcImg);
    bw = threshval < 100 ? (srcImg < 160) : (srcImg > 160);
    
    imshow("binary image", bw);
    waitKey(0);
    destroyAllWindows();
    return 0;
}