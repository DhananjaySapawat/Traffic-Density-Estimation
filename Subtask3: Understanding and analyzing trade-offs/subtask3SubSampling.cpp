
#include <opencv2/opencv.hpp>
#include <iostream>
#include<fstream>
#include <chrono>
using namespace std;
using namespace cv;
using namespace chrono;


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
    Mat1f empty;
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
     
    if (argc != 3){
        cout << "You need to pass three parameters: ./queue_sub_sampling.exe, <video_file_name>, <frames_drop>\n";
        return -1;
    }
    int frameDropNo = stoi(argv[2]);
    string VideoPath = argv[1];
    VideoCapture traffic(VideoPath);
    
    if (traffic.isOpened() == false )
    {
     
        cout << "Could not load file or file not of mp4 format, please check the file and try again :("<<endl;
        cin.ignore();
        return -1;
    }
    double fps = traffic.get(CAP_PROP_FPS);
    Mat perspecframe;
    Mat Referenceframe;
    Referenceframe = imread("background.jpg");
    //if fail to read the image
    if (Referenceframe.empty())
    {
        cout << "Error loading the image" << endl;
        return -1;
    }
    cvtColor(Referenceframe, Referenceframe, COLOR_BGR2GRAY);
    Mat CropReferenceframe = PerspectiveAndCrop(Referenceframe);
    Mat Currframe;
    Mat CropCurrframe;
    int frameNum = 0;
    ofstream answer;
    ofstream answer2;
    double Qdensity = 0;
    string out = "analysis/SubSampling/outputsubsampling"+to_string(frameDropNo)+".txt";
    answer.open(out);
    auto start = high_resolution_clock::now();
    frameDropNo++;
    cout << 0<< ',' << 0.0  << endl;
    //below part stores output in out.txt
    answer << 0 << ',' << 0.0<<endl;
    while (true) {
     
        
        
        Currframe = Grayframe(traffic);
        // If the frame is empty, break immediately
        if (Currframe.empty()) {
            break;
        }
        if(frameNum%frameDropNo!=0){
            ++frameNum;
        double time = frameNum * 1.0 / fps;
        cout << time << ',' << Qdensity << endl;
        //below part stores output in out.txt
        answer << time << ',' << Qdensity<<endl;
        
        continue;
        }
        CropCurrframe = PerspectiveAndCrop(Currframe);
     
        Mat queue = FindDensity(CropReferenceframe,CropCurrframe);
        Mat thresholdQueue;
        
        threshold(queue, thresholdQueue, 30, 255, THRESH_BINARY);
        Qdensity = FindSum(thresholdQueue);
        ++frameNum;
        double time = frameNum * 1.0 / fps;
        cout << time << ',' << Qdensity << endl;
        //below part stores output in out.txt
        answer << time << ',' << Qdensity<<endl;

    }
     frameDropNo--;
    answer.close();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    
    cout << "Time taken by function: "
        << duration.count()/1000000 << " Seconds" << endl;

    string file = "outputsubsampling"+to_string(frameDropNo);
    string time = "Time.txt";
    answer2.open(time,fstream::app);
    answer2<<file<<" Completion Time :"<<duration.count()/1000000<<endl;
    answer2.close();
    fstream ti;
    string outerr = "analysis/SubSampling/SubsamplingTime.txt";
    ti.open(outerr, ios::out | ios::app);
    ti <<frameDropNo <<","<< duration.count()/1000000<<endl;
    ti.close();
    return 0;
}