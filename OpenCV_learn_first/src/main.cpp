#include <iostream>
#include <opencv2/opencv.hpp>
#include <algorithm>

cv::Mat letterbox(const cv::Mat &img, int t_w, int t_h)
{
    int w = img.cols;
    int h = img.rows;

    float r = std::min((float)t_w / w, (float)t_h / h);

    int new_w = (int)std::round(w * r);
    int new_h = (int)std::round(h * r);

    cv::Mat re_img;
    cv::resize(img, re_img, cv::Size(new_w, new_h), 0, 0, cv::INTER_LINEAR);

    int dw = w - new_w;
    int dh = h - new_h;
    int top = dh / 8;
    int bottom = dh / 8;
    int left = dw / 8;
    int right = dw / 8;

    cv::Mat out;
    cv::copyMakeBorder(re_img, out, top, bottom, left, right, cv::BORDER_CONSTANT, cv::Scalar(114, 114, 114));

    return out;
}

int main()
{

    cv::Mat img = cv::imread("3.jpg");

    if (img.empty())
    {
        std::cout << "没有找到该图片" << std::endl;
        return -1;
    }
    cv::Mat re_img;

    // cv::resize(img, re_img, cv::Size(640, 640), 0, 0, cv::INTER_LINEAR);

    re_img = letterbox(img, 640, 640);

    cv::Mat gray_img;
    cv::cvtColor(re_img, gray_img, cv::COLOR_BGR2GRAY);

    cv::Mat bin_img;
    cv::threshold(gray_img, bin_img, 200, 255, cv::THRESH_BINARY);

    std::cout << "宽度：" << re_img.cols << std::endl;
    std::cout << "高度：" << re_img.rows << std::endl;
    std::cout << "通道数：" << re_img.channels() << std::endl;

    // 蓝色提取
    // cv::Mat hsv, mask;
    // cv::cvtColor(re_img, hsv, cv::COLOR_BGR2HSV);
    // cv::inRange(hsv, cv::Scalar(85, 125, 200), cv::Scalar(135, 255, 255), mask);
    // cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    // cv::morphologyEx(mask, mask, cv::MORPH_OPEN, kernel);

    // 红色提取
    cv::Mat hsv, mask1, mask2, mask;
    cv::cvtColor(re_img, hsv, cv::COLOR_BGR2HSV);
    cv::inRange(hsv, cv::Scalar(0, 125, 200), cv::Scalar(30, 255, 255), mask1);
    cv::inRange(hsv, cv::Scalar(170, 125, 200), cv::Scalar(180, 255, 255), mask2);

    cv::bitwise_or(mask1, mask2, mask);

    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(4, 4));
    cv::morphologyEx(bin_img, bin_img, cv::MORPH_OPEN, kernel);
    cv::morphologyEx(mask, mask, cv::MORPH_OPEN, kernel);

    cv::imshow("原图", img);
    cv::imshow("letterbox效果", re_img);
    cv::imshow("灰度效果", gray_img);
    cv::imshow("二值化效果", bin_img);
    cv::imshow("处理效果", mask);

    cv::waitKey(0);

    std::cout << "OpenCV 的版本为：" << CV_VERSION << std::endl;

    return 0;
}