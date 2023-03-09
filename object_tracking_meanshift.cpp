// This code uses the OpenCV library to perform object tracking using the meanshift algorithm. It first loads a video from a file named "video.mp4" using the VideoCapture class. If the video cannot be loaded, the code prints an error message and exits.

// The code then reads the first frame from the video and defines a region of interest (ROI) for tracking. The ROI is a rectangular region with top-left corner at (250, 150) and width and height of 100 pixels. The code extracts the ROI from the first frame and converts it to the HSV color space using the cvtColor() function.

// The code then extracts the histogram of the ROI in the H channel using the calcHist() function. The histogram has 16 bins in the H channel, and its range is from 0 to 180. The code normalizes the histogram using the normalize() function.

// The code then enters a loop that reads each frame from the video, converts it to the HSV color space, calculates the back projection of the histogram onto the frame using the `calcBackProject()` function, performs meanshift on the back projection to find the new location of the object, and draws a rectangle around the tracked object in the frame. The meanshift algorithm is used to find the peak in the probability distribution of the back projection, which corresponds to the location of the object in the current frame.

// The code displays the result in a window named "Object Tracking" using the imshow() function and waits for a keyboard event using the waitKey() function. The loop continues until the video ends or the user presses the 'q' key to quit.

// Finally, the video capture is released using the release() method of the VideoCapture class.


#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    // Load the input video
    VideoCapture cap("video.mp4");
    if (!cap.isOpened())
    {
        std::cout << "Error loading video" << std::endl;
        return -1;
    }

    // Read the first frame from the video
    Mat frame;
    cap >> frame;

    // Define a region of interest (ROI) for tracking
    Rect roi(250, 150, 100, 100);
    Mat roiImage = frame(roi);

    // Convert the ROI to HSV color space
    Mat hsvImage;
    cvtColor(roiImage, hsvImage, COLOR_BGR2HSV);

    // Extract the histogram of the ROI in the H channel
    Mat hist;
    int hbins = 16, sbins = 16;
    int histSize[] = {hbins};
    float hranges[] = {0, 180};
    const float* ranges[] = {hranges};
    int channels[] = {0};
    calcHist(&hsvImage, 1, channels, Mat(), hist, 1, histSize, ranges);

    // Normalize the histogram
    normalize(hist, hist, 0, 255, NORM_MINMAX);

    // Perform object tracking using meanshift
    Mat backProj, dst;
    TermCriteria criteria(TermCriteria::EPS | TermCriteria::COUNT, 10, 1);
    while (true)
    {
        // Read a frame from the video
        cap >> frame;
        if (frame.empty())
        {
            break;
        }

        // Convert the frame to HSV color space
        cvtColor(frame, hsvImage, COLOR_BGR2HSV);

        // Calculate the back projection of the histogram onto the frame
        calcBackProject(&hsvImage, 1, channels, hist, backProj, ranges);

        // Perform meanshift to find the new location of the object
        meanShift(backProj, roi, criteria);

        // Draw a rectangle around the tracked object
        rectangle(frame, roi, Scalar(0, 255, 0), 2);

        // Display the result
        imshow("Object Tracking", frame);

        // Check if the user pressed the 'q' key to quit
        if (waitKey(1) == 'q')
        {
            break;
        }
    }

    // Release the video capture
    cap.release();

    return 0;
}
