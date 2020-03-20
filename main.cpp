#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat srcImage = imread("/Users/suikajy/vscode-workspace/LearnCmake/res/in_leaves.jpg");
    if (!srcImage.data) {
        cout << "Image not loaded";
        return -1;
    }

    imshow("[img]", srcImage);
    waitKey(0);

    return 0;
}
