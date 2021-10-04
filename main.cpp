#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat rgbImg = cv::imread("/Users/eldarkurbanov/CLionProjects/circleContourServer/img12.jpeg", cv::IMREAD_COLOR);

    cv::Mat hsvImg;
    cv::cvtColor(rgbImg, hsvImg, cv::COLOR_BGR2HSV);

    std::vector<cv::Mat> chans;
    cv::split(hsvImg, chans);
    cv::threshold(255 - chans[2], chans[2], 200, 255, cv::THRESH_BINARY);

    std::vector<cv::Vec4i> linesP;
    cv::HoughLinesP(chans[2], linesP, 1, CV_PI/180, 50, chans[2].rows / 4, 10);
    for (auto l : linesP)
    {
        cv::line(chans[2], cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar::all(0), 3, cv::LINE_AA);
    }
    cv::dilate(chans[2], chans[2], cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3)), cv::Point(-1, -1), 4);
    cv::erode(chans[2], chans[2], cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3)), cv::Point(-1, -1), 3);

    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(chans[2], contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    for (size_t i = 0; i < contours.size(); i++)
    {
        if (contours[i].size() > 4)
        {
            cv::ellipse(rgbImg, cv::fitEllipse(contours[i]), cv::Scalar(255, 0, 255), 2);
        }
    }

    cv::imshow("rgbImg", rgbImg);
    cv::waitKey(0);
    return 0;
}
