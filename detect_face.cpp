// The provided code is a simple example of face detection using C++ and the OpenCV library. Face detection is an important computer vision technique that is used in a variety of applications, such as surveillance systems, biometric authentication, and augmented reality.

// The code starts by loading a pre-trained classifier for detecting frontal faces, which is stored in an XML file named "haarcascade_frontalface_default.xml". This classifier is based on the Haar feature-based cascade classifier, which uses a set of simple Haar-like features to detect objects in an image. The CascadeClassifier class in OpenCV is used to load and store the classifier in memory.

// Next, the code reads an input image from a file named "input.jpg" using the imread() function. If the image cannot be read, the code prints an error message and exits.

// The code then converts the input image to grayscale using the cvtColor() function. This is because the Haar feature-based classifier works better on grayscale images than on color images, and it can help reduce the amount of computation required for face detection.

// The main face detection algorithm is performed using the detectMultiScale() method of the CascadeClassifier class. This method takes as input the grayscale image, a vector to store the detected objects (in this case, faces), a scale factor, a minimum number of neighbors, and some other parameters. The scale factor controls how much the image is resized at each scale, and the minimum number of neighbors specifies how many overlapping rectangles are required for a detection to be considered valid. The detectMultiScale() method returns a vector of Rect objects, where each Rect represents a bounding box around a detected face.

// Finally, the code draws rectangles around the detected faces using the rectangle() function. The Scalar(0, 0, 255) argument specifies the color of the rectangle (in this case, red), and the 2 argument specifies the thickness of the rectangle border.

// The detected faces are then displayed in a new window named "Detected Faces" using the namedWindow(), imshow(), and waitKey() functions.

// The provided code is a simple example of face detection using C++ and the OpenCV library. Face detection is an important computer vision technique that is used in a variety of applications, such as surveillance systems, biometric authentication, and augmented reality.

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main()
{
    // Load the classifier
    CascadeClassifier faceCascade;
    if (!faceCascade.load("haarcascade_frontalface_default.xml"))
    {
        std::cout << "Error: Could not load face classifier" << std::endl;
        return -1;
    }

    // Read the input image
    Mat image = imread("input.jpg");
    if (image.empty())
    {
        std::cout << "Error: Could not read image file" << std::endl;
        return -1;
    }

    // Convert the image to grayscale
    Mat grayImage;
    cvtColor(image, grayImage, COLOR_BGR2GRAY);

    // Detect faces in the image
    std::vector<Rect> faces;
    faceCascade.detectMultiScale(grayImage, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30));

    // Draw rectangles around the detected faces
    for (size_t i = 0; i < faces.size(); i++)
    {
        rectangle(image, faces[i], Scalar(0, 0, 255), 2);
    }

    // Show the detected faces
    namedWindow("Detected Faces", WINDOW_AUTOSIZE);
    imshow("Detected Faces", image);
    waitKey(0);

    return 0;
}
