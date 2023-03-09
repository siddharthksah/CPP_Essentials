// This code uses the OpenCV library to perform real-time face detection using a webcam. It first loads a pre-trained classifier for detecting frontal faces, which is stored in an XML file named "haarcascade_frontalface_default.xml". It then opens the default webcam using the VideoCapture class and creates a window named "Webcam" to display the video feed.

// The main loop of the program reads each frame from the webcam using the >> operator of the VideoCapture class. It then converts the frame to grayscale using the cvtColor() function, detects faces in the grayscale frame using the detectMultiScale() method of the CascadeClassifier class, and draws rectangles around the detected faces using the rectangle() function. The imshow() function is used to display the processed frame in the "Webcam" window, and the waitKey() function waits for a keyboard event and returns the ASCII code of the pressed key. The loop continues until the user presses the 'q' key to quit, at which point the webcam is released using the release() method of the VideoCapture class.

// The provided code is a simple example of face detection using C++ and the OpenCV library. Face detection is an important computer vision technique that is used in a variety of applications, such as surveillance systems, biometric authentication, and augmented reality.

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    // Load the face detection classifier
    CascadeClassifier faceCascade;
    if (!faceCascade.load("haarcascade_frontalface_default.xml"))
    {
        std::cout << "Error: Could not load face detection classifier" << std::endl;
        return -1;
    }

    // Open the webcam
    VideoCapture cap(0);
    if (!cap.isOpened())
    {
        std::cout << "Error: Could not open the webcam" << std::endl;
        return -1;
    }

    // Create a window to display the video feed
    namedWindow("Webcam", WINDOW_NORMAL);

    // Process each frame of the video feed
    while (true)
    {
        // Read a frame from the webcam
        Mat frame;
        cap >> frame;

        // Convert the frame to grayscale
        Mat grayFrame;
        cvtColor(frame, grayFrame, COLOR_BGR2GRAY);

        // Detect faces in the frame
        std::vector<Rect> faces;
        faceCascade.detectMultiScale(grayFrame, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30));

        // Draw rectangles around the detected faces
        for (const auto& face : faces)
        {
            rectangle(frame, face, Scalar(0, 0, 255), 2);
        }

        // Display the frame
        imshow("Webcam", frame);

        // Check if the user pressed the 'q' key to quit
        if (waitKey(1) == 'q')
        {
            break;
        }
    }

    // Release the webcam
    cap.release();

    return 0;
}
