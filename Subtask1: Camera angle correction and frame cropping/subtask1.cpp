#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

vector<Point2f> points;
vector<Point2f> fixpoints = { {472 , 52}, {800 , 52}, {800 , 830}, {472 , 830 } };
bool GettingPoints = true;

Mat crop(Mat img) {
    Rect four(472, 52, 328, 778);
    return img(four);
}

void findPoints(int event, int x, int y, int flags, void* userdata)
{
    if (event == EVENT_LBUTTONDOWN and points.size() < 4) {

        cout << "Point - position (" << x << ", " << y << ")" << endl;
        points.push_back(Point2f(x, y));
        if(points.size() >= 4){
            cout<<"Click space to see Transformated view"<<endl;
        }
    }
}

int main(int argc, char** argv)
{    
    if (argc!=2){
        cout << "Error : You need to give Imagefile name also"<<endl;
        return 0;
    }
    // Read image from file
    string ImagePath = argv[1];
    Mat Img = imread(ImagePath);
    //if fail to read the image
    if (Img.empty())
    {
        cout << "Error : loading the image" << endl;
        return -1;
    }

    // Convert the Original image to grayscale image.
    cvtColor(Img,Img, COLOR_BGR2GRAY);
    Mat PerspectiveImg;

    //Create a window
    namedWindow("Original Image", WINDOW_NORMAL);

    //showing the Original image
    imshow("Original Image", Img);
    cout<<"Find Four points in image with mouse"<<endl;
    setMouseCallback("Original Image", findPoints, NULL);
    waitKey(0);

    //Check if we select four point in Img
    if(points.size() != 4){
        cout<<"Error: Four Points are not selected in Img"<<endl;
        return -1;
    }

    // Calculate the perspective matrix from the found points in the image
    Mat perspectiveMatrix = getPerspectiveTransform(points, fixpoints);

    // Apply the perspective transformatin on the image
    warpPerspective(Img, PerspectiveImg, perspectiveMatrix, Img.size());

    // Show PerspectiveImg
    imshow("Transformated view", PerspectiveImg);
    waitKey(0);
    cout<<"Click space to see Cropped Transformated view"<<endl;

    // Calculate the Crop image from the found points in the image
    Mat croppedPerspectiveImg= crop(PerspectiveImg);


    // Show Croped perspecImg
    imshow("Cropped Transformated View", croppedPerspectiveImg);
    waitKey(0);
    cout<<"Click space to end the program"<<endl;
    
    // writing the perspecImg to a defined location as JPEG
    imwrite("Transformed_"+ImagePath, PerspectiveImg);
    
    // writing the croppedImg to a defined location as JPEG
    imwrite("Croppedtransformed_"+ImagePath, croppedPerspectiveImg);  
    return 0;

}
