#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    cv::Mat img;
    int num = 0;
    cv::VideoCapture cap(0);

    if (!cap.isOpened())
    {
        std::cout << "无法打开摄像头！";
        return -1;
    }

    std::cout << "按'ESC'退出" << std::endl;

    while (true)
    {

        cap.read(img);

        if (img.empty())
        {
            std::cout << "画面读取失败！" << std::endl;
            break;
        }

        cv::Mat hsv, mask;
        cv::cvtColor(img, hsv, cv::COLOR_BGR2HSV);
        // 提取蓝色
        cv::inRange(hsv, cv::Scalar(100, 43, 46), cv::Scalar(124, 255, 255), mask);
        // 形态学过滤
        cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
        cv::morphologyEx(mask, mask, cv::MORPH_OPEN, kernel);

        cv::Mat re_img;
        cv::Mat bin_img;
        cv::cvtColor(img, re_img, cv::COLOR_BGR2GRAY);
        cv::threshold(re_img, bin_img, 144, 255, cv::THRESH_BINARY);

        cv::imshow("原图", img);
        cv::imshow("蓝色提取", mask);
        if (cv::waitKey(1) == 27)
        {
            break;
        }

        num++;
        if (num % 30 == 0)
        {
            std::cout << num << std::endl;
        }
    }
    std::cout << "结束力 " << std::endl;
}