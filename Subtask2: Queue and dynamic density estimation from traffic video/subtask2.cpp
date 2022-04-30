#include <opencv2/opencv.hpp>
#include <iostream>
#include<fstream>

using namespace std;
using namespace cv;

vector<Point2f> points = { {984,204},{1290,216},{1565,1068},{650,1068} };
vector<Point2f> fixpoints = { {472 , 52}, {800 , 52}, {800 , 830}, {472 , 830 } };
Mat crop(Mat img) {
    Rect four(472, 52, 328, 778);
    return img(four);
}

Mat Grayframe(VideoCapture& video)
{
    Mat frame;
    //empty matrix
    Mat empty;
    if (video.read(frame))
    {
        cvtColor(frame, frame, COLOR_BGR2GRAY);
        return frame;
    }
    else {
        return empty;
    }
}
Mat PerspectiveAndCrop(Mat frame) {
    Mat perspectiveFrame;
    // Calculate the perspective matrix from the found points in the image
    Mat perspectiveMatrix = getPerspectiveTransform(points, fixpoints);
    // Apply the perspective transformatin on the image
    warpPerspective(frame, perspectiveFrame, perspectiveMatrix, frame.size());
    // Calculate the Crop image from the found points in the image
    Mat CropAndPerspectiveFrame = crop(perspectiveFrame);
    return CropAndPerspectiveFrame;
}
Mat FindDensity(Mat frame1, Mat frame2)
{
    Mat Threshframe = Mat::zeros(778, 328,CV_8UC1);
    absdiff(frame1, frame2, Threshframe);
    return Threshframe;
}
double FindSum(Mat& frame) {

    long double sum = 0;
    for (int i = 0; i < frame.rows; i++) {
        for (int j = 0; j < frame.cols; j++) {
            sum = sum + frame.at<uchar>(i, j);
        }
    }
    int a = frame.cols;
    int b = frame.rows;
    int c = a * b*255;
    double totalsum = sum / c;
    return totalsum;
}
int main(int argc, char* argv[]) {
    if (argc!=2){
        cout << "You need to give video name to"<<endl;
        return -1;
    }
    string VideoPath = argv[1];
    VideoCapture traffic(VideoPath);
    if (traffic.isOpened() == false )
    {
        cout << "Could not load Video file"<<endl;
        return -1;
    }
    double fps = traffic.get(CAP_PROP_FPS);
    Mat perspectiveframe;
    Mat Referenceframe;
    Referenceframe = imread("background.jpg");
    //if fail to read the image
    if (Referenceframe.empty())
    {
        cout << "Error in loading the background image "<<endl;
        return -1;
    }
    cvtColor(Referenceframe, Referenceframe, COLOR_BGR2GRAY);
    Mat CropReferenceframe = PerspectiveAndCrop(Referenceframe);
    Mat Currentframe;
    Mat CropCurrentframe;
    Mat Firstframe = Grayframe(traffic);
    Mat Previousframe = PerspectiveAndCrop(Firstframe);
    int frameNum = 0;
    ofstream out;
    
    out.open("out.txt");
    double time = 0 ;
    while (true) {
     
        ++frameNum;
        Currentframe = Grayframe(traffic);
        // If the frame is empty, break immediately
        if (Currentframe.empty()) {
            break;
        }
        CropCurrentframe = PerspectiveAndCrop(Currentframe);
     
        Mat queue = FindDensity(CropReferenceframe,CropCurrentframe);

        Mat flow(Previousframe.size(), CV_32FC2);
        calcOpticalFlowFarneback(Previousframe, CropCurrentframe, flow, 0.5, 3, 15, 3, 5, 1.2, 0);
        // visualization
        Mat flow_parts[2];
        split(flow, flow_parts);
        Mat magnitude, angle, magn_norm;
        cartToPolar(flow_parts[0], flow_parts[1], magnitude, angle, true);
        normalize(magnitude, magn_norm, 0.0f, 1.0f, NORM_MINMAX);
        angle *= ((1.f / 360.f) * (180.f / 255.f));
        //build hsv image
        Mat _hsv[3], hsv, hsv8, bgr;
        _hsv[0] = angle;
        _hsv[1] = Mat::ones(angle.size(), CV_32F);
        _hsv[2] = magn_norm;
        merge(_hsv, 3, hsv);
        hsv.convertTo(hsv8, CV_8U, 255.0);
        cvtColor(hsv8, bgr, COLOR_HSV2BGR);
        cvtColor(bgr, flow, COLOR_BGR2GRAY);
        Mat flow_binary;
        Mat threshqueue;
        threshold(queue, threshqueue,15, 255, THRESH_BINARY);
        threshold(flow, flow_binary, 10, 255, THRESH_BINARY);
        double Qdensity = FindSum(threshqueue);
        double Ddensity = FindSum(flow_binary);
        time = frameNum * 1.0 / fps;
        cout << time << ',' << Qdensity << ',' << Ddensity << endl;
      
        
        //below part stores output in out.txt
        out << time << ',' << Qdensity <<',' << Ddensity <<endl;
      
        imshow("video", CropCurrentframe);
        waitKey(1);
        Previousframe = CropCurrentframe;
    }
    out.close();

    return 0;
}
