
#include <opencv2/opencv.hpp>
#include <iostream>
#include<fstream>
#include <chrono>



using namespace std;
using namespace cv;
using namespace std::chrono;


vector<Point2f> points = { {984,204},{1290,216},{1565,1068},{650,1068} };
vector<Point2f> fixpoints = { {472 , 52}, {800 , 52}, {800 , 830}, {472 , 830 } };

Mat crop(Mat img, int factor) {
    Rect four(472/factor, 52/factor, 328/factor, 778/factor);
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
vector<Point2f> factorer(vector<Point2f>point, int factor) {
     
    vector<Point2f> answer = { {472 , 52}, {800 , 52}, {800 , 830}, {472 , 830 } };
    for (int i = 0; i < 4; i++) {
        answer[i].x = point[i].x/factor;
        answer[i].y = point[i].y/factor;
    }
    return answer;
}
Mat PerspectiveAndCrop(Mat frame, int factor) {
    vector<Point2f> factorpoints = factorer(points, factor);
    vector<Point2f> factorfixpoints = factorer(fixpoints, factor);
    Mat perspectiveFrame;
    // Calculate the perspective matrix from the found points in the image
    Mat perspectiveMatrix = getPerspectiveTransform(factorpoints, factorfixpoints);
    // Apply the perspective transformatin on the image
    warpPerspective(frame, perspectiveFrame, perspectiveMatrix, frame.size());
    // Calculate the Crop image from the found points in the image
    Mat CropAndPerspectiveFrame = crop(perspectiveFrame, factor);
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
    int factor = stoi(argv[2]);
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
    int col = Referenceframe.cols / factor;
    int row = Referenceframe.rows / factor;
    resize(Referenceframe, Referenceframe, Size(col, row));
    cvtColor(Referenceframe, Referenceframe, COLOR_BGR2GRAY);
    Mat CropReferenceframe = PerspectiveAndCrop(Referenceframe,factor);
    Mat Currframe;
    Mat CropCurrframe;
    int frameNum = 0;
    ofstream answer;
    ofstream answer2;
    string out = "analysis/Resolution/outputresolution"+to_string(factor)+".txt";
    answer.open(out);
    auto start = high_resolution_clock::now();
    while (true) {
     
        ++frameNum;
        Currframe = Grayframe(traffic);
        // If the frame is empty, break immediately
        if (Currframe.empty()) {
            break;
        }
        resize(Currframe, Currframe, Size(col, row));
        CropCurrframe = PerspectiveAndCrop(Currframe,factor);
     
        Mat queue = FindDensity(CropReferenceframe,CropCurrframe);
        Mat thresholdQueue;
    
        threshold(queue,thresholdQueue, 30, 255, THRESH_BINARY);
        double Qdensity = FindSum(thresholdQueue);
        
        double time = frameNum * 1.0 / fps;
        cout << time << ',' << Qdensity << endl;
        //below part stores output in out.txt
        answer << time << ',' << Qdensity<<endl;
        
    }
    answer.close();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Time taken by function: "
        << duration.count()/1000000 << " Seconds" << endl;
    string file = "outputresolution"+to_string(factor);
    string time = "Time.txt";
    answer2.open(time,fstream::app);
    answer2<<file<<" Completion Time :"<<duration.count()/1000000<<endl;
    answer2.close();
    fstream ti;
    string outerr = "analysis/Resolution/ResolutionTime.txt";
    ti.open(outerr, ios::out | ios::app);
    ti <<factor <<","<< duration.count()/1000000<<endl;
    ti.close();
    return 0;
}

