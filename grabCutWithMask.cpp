#include <iostream>
#include <opencv2/opencv.hpp>
#include "algorithm/util.cpp"

using namespace std;

const bool isScale = true;

void showMask(const cv::Mat &mask, const string &title = "mask")
{
    cv::Mat factorMat(mask.rows, mask.cols, CV_8UC1, cv::Scalar(80));
    cv::Mat displayMat(mask.rows, mask.cols, CV_8UC1);
    cv::multiply(mask, factorMat, displayMat);
    cv::imshow(title, displayMat);
}

int main()
{
    cv::Mat srcImage = cv::imread("/Users/butter/VscodeProjects/OpenCVCppDemo/res/sculpture.jpg");
    if (!srcImage.data)
    {
        cout << "Image not loaded";
        return -1;
    }

    cv::Rect rectangle(200, 0, 350, 750);
    cv::Mat bgModel, fgModel;
    cv::Mat result1 = cv::Mat(srcImage.rows, srcImage.cols, CV_8UC1, cv::Scalar(cv::GC_BGD));
    cv::Mat roi(result1, rectangle);
    roi = cv::Scalar(cv::GC_PR_FGD); // 这里相当于将4-pixel的result1 mask赋值为3

    cv::Mat new_mask(srcImage.rows, srcImage.cols, CV_8UC1, cv::Scalar(255));
    new_mask(cv::Range(75, 80), cv::Range(457, 463)) = 1;
    new_mask(cv::Range(90, 110), cv::Range(610, 630)) = 0;

    for (size_t row = 0; row < srcImage.rows; row++)
    {
        for (size_t col = 0; col < srcImage.cols; col++)
        {
            uchar gray = new_mask.at<uchar>(row, col);
            if (gray == 1 || gray == 0)
            {
                result1.at<uchar>(row, col) = gray;
            }
        }
    }

    showMask(result1, "result1");
    double tt = cv::getTickCount();

    if (isScale)
    {
        double scaleFactor = 0.5;
        cv::Size scaledSize(srcImage.rows * scaleFactor, srcImage.cols * scaleFactor);
        cv::Mat scaledMat(srcImage.rows, srcImage.cols, CV_8UC3, cv::Scalar::all(0));
        cv::Mat scaledMask(srcImage.rows, srcImage.cols, CV_8UC3, cv::Scalar::all(0));
        cv::resize(srcImage, scaledMat, scaledSize, 0, 0, cv::INTER_AREA);
        cv::resize(result1, scaledMask, scaledSize, 0, 0, cv::INTER_LINEAR);
        showMask(scaledMask, "scaled mask");

        cv::grabCut(scaledMat, scaledMask, rectangle, bgModel, fgModel, 1, cv::GC_INIT_WITH_MASK);
        tt = cv::getTickCount() - tt;
        printf("算法执行时间:%g ms\n", tt / cv::getTickFrequency() * 1000);

        showMask(scaledMask, "#1");
        cv::Mat probableBGD(scaledMask.rows, scaledMask.cols, CV_8UC1, cv::Scalar(0));
        cv::compare(scaledMask, cv::GC_PR_BGD, probableBGD, cv::CMP_EQ);
        cv::subtract(scaledMask, probableBGD, scaledMask);

        cv::resize(scaledMask, result1, result1.size(), 0, 0, cv::INTER_CUBIC);

        cv::Mat maskFactor = cv::Mat::ones(result1.size(), CV_8UC1) * 85;
        cv::multiply(result1, maskFactor, result1);
        cv::blur(result1, result1, cv::Size(8, 8));

        cv::imshow("#1 result1", result1);

        cv::Mat foreground(srcImage.size(), CV_8UC3, cv::Scalar(0, 0, 0, 0));
        au::multiplyAsAlpha(srcImage, result1, foreground);
        cv::imshow("[img_with_mask]", foreground);
    }
    else
    {
        cv::grabCut(srcImage, result1, rectangle, bgModel, fgModel, 5, cv::GC_INIT_WITH_MASK);
        tt = cv::getTickCount() - tt;
        printf("算法执行时间:%g ms\n", tt / cv::getTickFrequency() * 1000);

        cv::Mat probableBGD(result1.rows, result1.cols, CV_8UC1, cv::Scalar(0));
        cv::compare(result1, cv::GC_PR_BGD, probableBGD, cv::CMP_EQ);
        cv::subtract(result1, probableBGD, result1);
        cv::Mat foreground(srcImage.size(), CV_8UC3, cv::Scalar(0, 0, 0, 0));
        srcImage.copyTo(foreground, result1);
        cv::imshow("[img_with_mask]", foreground);
    }
    cv::waitKey(0);

    return 0;
}