#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    cv::Mat srcImage = cv::imread("/Users/suikajy/vscode-workspace/LearnCmake/res/sculpture.jpg");
    if (!srcImage.data)
    {
        std::cout << "Image not loaded";
        return -1;
    }

    cv::Rect rectangle(200, 0, 350, 750);
    cv::Mat result;
    cv::Mat bgModel, fgModel;
    double tt = cv::getTickCount();

    cv::grabCut(srcImage, result, rectangle, bgModel, fgModel, 1, cv::GC_INIT_WITH_RECT);
    tt = cv::getTickCount() - tt;
    printf("算法执行时间:%g ms\n", tt / cv::getTickFrequency() * 1000);

    cv::compare(result, cv::GC_PR_FGD, result, cv::CMP_EQ);

    cv::Mat foreground(srcImage.size(), CV_8UC3, cv::Scalar(255, 255, 255));

    srcImage.copyTo(foreground, result);

    cv::imshow("[img]", foreground);
    cv::waitKey(0);

    return 0;
}