#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char **args)
{
    Mat srcImg = imread("/Users/butter/VscodeProjects/OpenCVCppDemo/res/sculpture.jpg");
    cvtColor(srcImg,srcImg, COLOR_BGR2GRAY);
    Mat result;
    threshold(srcImg, result,170,255,THRESH_BINARY);
    imshow("image", srcImg);

    imshow("二值化后的图像1",result);
    waitKey(0);
    destroyAllWindows();
    return 0;
}