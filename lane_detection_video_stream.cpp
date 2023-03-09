// This code is a C++ program that uses the OpenCV library to perform lane detection on a video stream. It reads in frames from a video file named "video.mp4" using the VideoCapture class, and processes each frame to detect lane markings using the Line Segment Detector (LSD) algorithm.

// The program first checks if the video stream was successfully opened using the isOpened() method of the VideoCapture class. If the video stream cannot be opened, the program prints an error message and exits.

// The program then defines a region of interest (ROI) for lane detection using the Rect class. The ROI is a rectangular area defined by the top-left corner coordinates (0, 200), width 640, and height 280.

// The program then creates an instance of the LineSegmentDetector class using the createLineSegmentDetector() function, with the parameter LSD_REFINE_STD indicating that the LSD algorithm should be run with standard refinement.

// The program then enters a loop to process each frame in the video stream. For each frame, the program applies a perspective transform using the getPerspectiveTransform() function to obtain a top-down view of the image. This is useful for lane detection, as it simplifies the problem of detecting parallel lines that may be curved or angled in the original image.

// The program then converts the top-down view image to grayscale using the cvtColor() function and applies the Canny edge detection algorithm using the Canny() function. The result is an edge image that highlights the edges of the lane markings.

// The program then applies the ROI to the edge image using the Mat::operator() function to obtain a smaller sub-image containing only the relevant edges.

// The program then applies the LSD algorithm using the detect() method of the LineSegmentDetector class, with the ROI edges image as input. The result is a vector of line segments that represent the detected lane markings.

// The program then draws the detected lane markings on the top-down view image using the line() function. The line() function takes as input the image on which to draw the line, the endpoints of the line segment, the line color (in BGR format), and the line thickness.

// The program then applies an inverse perspective transform using the getPerspectiveTransform() function to map the line image back to the original image perspective. This results in a final lane detection image that shows the detected lane markings overlaid on the original image.

// Finally, the program displays the lane detection result using the imshow() function and waits for a keyboard event using the waitKey() function. The loop continues until the user presses the "q" key, at which point the program releases the video stream using the release() method of the VideoCapture class and exits.

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    // Open the video stream
    VideoCapture cap("video.mp4");
    if (!cap.isOpened())
    {
        std::cout << "Error: Could not open video stream" << std::endl;
        return -1;
    }

    // Define the ROI for lane detection
    Rect roi(0, 200, 640, 280);

    // Create the lane detector
    Ptr<LineSegmentDetector> lsd = createLineSegmentDetector(LSD_REFINE_STD);

    // Loop over the frames in the video stream
    while (true)
    {
        // Read the next frame from the video stream
        Mat frame;
        if (!cap.read(frame))
        {
            std::cout << "End of video stream" << std::endl;
            break;
        }

        // Apply a perspective transform to the frame to obtain a top-down view
        Mat perspective;
        Mat transform = getPerspectiveTransform(
            { Point2f(265, 150), Point2f(380, 150), Point2f(0, 280), Point2f(640, 280) },
            { Point2f(0, 0), Point2f(640, 0), Point2f(0, 480), Point2f(640, 480) });
        warpPerspective(frame, perspective, transform, { 640, 480 });

        // Convert the perspective-transformed frame to grayscale
        Mat gray;
        cvtColor(perspective, gray, COLOR_BGR2GRAY);

        // Apply Canny edge detection
        Mat edges;
        Canny(gray, edges, 50, 200, 3);

        // Apply the ROI to the edges image
        Mat roiEdges = edges(roi);

        // Detect lines in the ROI using the LineSegmentDetector
        std::vector<Vec4f> lines;
        lsd->detect(roiEdges, lines);

        // Draw the lines on the perspective-transformed frame
        Mat lineImage = Mat::zeros(perspective.size(), CV_8UC3);
        for (size_t i = 0; i < lines.size(); i++)
        {
            Vec4f line = lines[i];
            line[0] += roi.x;
            line[1] += roi.y;
            line[2] += roi.x;
            line[3] += roi.y;
            lineImage += perspective.clone();
            line(lineImage, line, Scalar(0, 0, 255), 3);
        }

        // Apply an inverse perspective transform to the line image
        Mat inverseTransform = getPerspectiveTransform(
            { Point2f(0, 0), Point2f(640, 0), Point2f(0, 480), Point2f(640, 480) },
            { Point2f(265, 150), Point2f(380, 150), Point2f(0, 280), Point2f(640, 280) });
        warpPerspective(lineImage, lineImage, inverseTransform, { frame.cols, frame.rows });

        // Display the lane detection result
        imshow("Lane Detection", lineImage);

        // Wait for a keyboard event
        if (waitKey(1) == 'q')
        {
            break;
        }
    }

    // Release the video stream
    cap.release();

    return 0;
}
