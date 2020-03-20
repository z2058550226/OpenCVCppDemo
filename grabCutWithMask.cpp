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
    cv::Mat bgModel, fgModel;
    cv::Mat result1 = cv::Mat(srcImage.rows, srcImage.cols, CV_8UC1, cv::Scalar(cv::GC_BGD));
    cv::Mat roi(result1, rectangle);
    roi = cv::Scalar(cv::GC_PR_FGD); // 这里相当于将4-pixel的result1 mask赋值为3

    double tt = cv::getTickCount();
    cv::grabCut(srcImage, result1, rectangle, bgModel, fgModel, 1, cv::GC_INIT_WITH_MASK);
    tt = cv::getTickCount() - tt;
    printf("算法执行时间:%g ms\n", tt / cv::getTickFrequency() * 1000);

    cv::compare(result1, cv::GC_PR_FGD, result1, cv::CMP_EQ);

    cv::Mat foreground(srcImage.size(), CV_8UC3, cv::Scalar(255, 255, 255));

    srcImage.copyTo(foreground, result1);

    cv::imshow("[img_with_mask]", foreground);
    cv::waitKey(0);

    return 0;
}