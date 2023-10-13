#include <filesystem>
#include <fstream>
#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <string>

using namespace cv;
using namespace std;

int main() {
    VideoCapture capture("loli.mp4"); // 替换为您的视频文件路径
    if (!capture.isOpened()) {
        cout << "无法打开视频文件" << endl;
        return -1;
    }

    int frameWidth = capture.get(CAP_PROP_FRAME_WIDTH);
    int frameHeight = capture.get(CAP_PROP_FRAME_HEIGHT);

    // 如果文件夹不存在 创建 ASCII 文件夹
    string outputFolder = "ASCII";
    // 使用文件系统库检查文件夹是否存在，如果不存在则创建它
    if (!filesystem::exists(outputFolder)) {
        filesystem::create_directory(outputFolder);
    }

    Mat frame;
    int frameCount = 1;

    while (true) {
        capture >> frame;

        if (frame.empty()) {
            break;
        }

        // 将每一帧转换为灰度图像
        cvtColor(frame, frame, COLOR_BGR2GRAY);

        // 缩小图像以适应终端大小
        resize(frame, frame, Size(193, 54));

        // 创建ASCII字符集
        string asciiChars = ":M7Xi,. ";

        // 将图像像素映射到ASCII字符
        string asciiImage;
        for (int i = 0; i < frame.rows; i++) {
            for (int j = 0; j < frame.cols; j++) {
                uchar pixelValue = frame.at<uchar>(i, j);
                int index = pixelValue * (asciiChars.length() - 1) / 255;
                asciiImage += asciiChars[index];
            }
            asciiImage += '\n';
        }

        // 生成文件名并保存ASCII图像
        string fileName = "ASCII/Loli-" + to_string(frameCount) + ".txt";
        ofstream file(fileName);
        file << asciiImage;
        file.close();
        frameCount++;
    }

    return 0;
}
