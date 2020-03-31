#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "iostream"

int main(int argc, char **argv)
{
    cv::namedWindow("Example3", cv::WINDOW_AUTOSIZE);
    cv::VideoCapture cap;
    cap.open("/Users/butter/VscodeProjects/OpenCVCppDemo/res/color_space_test_video.mp4");
    cv::Mat frame;
    for (;;)
    {
        cap >> frame;
        if (frame.empty())
            break;
        cv::imshow("Example3", frame);
        if (cv::waitKey(33) >= 0)
            break;
    }
    return 0;
}
