#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// Algorithm Utils
namespace au
{

// it doesn't work
void mergeAsAlpha(const Mat &src, const Mat &alpha, const Mat &dst)
{
    vector<Mat> channels;
    Mat blueChannel, greenChannel, redChannel;
    split(src, channels);
    blueChannel = channels[0];
    greenChannel = channels[1];
    redChannel = channels[2];

    channels.push_back(alpha);

    cout << channels.size() << endl;

    imshow("merge b", blueChannel);
    imshow("merge g", greenChannel);
    imshow("merge r", redChannel);
    imshow("merge a", alpha);

    Mat mergeImg(alpha.size(), CV_8UC4);
    merge(channels, mergeImg);
    cout << mergeImg.channels() << endl;
    imshow("merged image", mergeImg);

    cvtColor(mergeImg, dst, COLOR_BGRA2BGR);
}

void multiplyAsAlpha(const Mat &src, const Mat &alpha, Mat &dst)
{
    for (size_t row = 0; row < src.rows; row++)
    {
        for (size_t col = 0; col < src.cols; col++)
        {
            Vec3b scalar = src.at<Vec3b>(row, col);
            uchar alphaGray = alpha.at<uchar>(row, col);
            dst.at<Vec3b>(row, col)[0] = (int)(scalar[0] * 1.0f * alphaGray / 255);
            dst.at<Vec3b>(row, col)[1] = (int)(scalar[1] * 1.0f * alphaGray / 255);
            dst.at<Vec3b>(row, col)[2] = (int)(scalar[2] * 1.0f * alphaGray / 255);
        }
    }
}

} // namespace au
