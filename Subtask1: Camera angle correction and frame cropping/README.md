# Camera Angle Correction and Frame Cropping
## How to Run the Code:
1 Launch the terminal and give the command make run.
2 Put the image for which you want the transform and cropped view (Some sample images are present).
3 Run the following commands in the terminal from the directory of the project folder.
 make
 ./subtask1 (imageName)(imageName is name of file of which you want the Cropped Perpestive view.).
4.If everything has gone will then you will be able to see the image in window.Now Choose the four points of the image you want to project and click in following way:
- TopLeft-->TopRight-->BottomRight-->BottomLeft.
- Press Space to see Project Image.
- Again Press Space to see Croped Project Image.
- Again Press Space to save Project Image and Croped Project Image.
## Goal for Code:
>> OpenCV algorithms work best on rectangular frames. But when a camera is deployed on a real road, it is very hard to position the camera so that the road to be monitored is a perfect rectangle, and the camera gets a top view of that rectangle. Typically the road to be monitored is at an arbitrary angle to the camera, and many additional objects are part of the frame. For useful tasks like traffic density estimation on a particular road stretch, it is therefore important to first correct the camera angle in software, and crop the image to remove the additional objects. This is the goal of the first assignment Subtask1.
## Description of the code:
The Code will take an image and four point in image from the user and return the images transform view and cropped transform view.
## References:
	https://docs.opencv.org/master/d9/dab/tutorial_homography.html
	https://learnopencv.com/homography-examples-using-opencv-python-c/
