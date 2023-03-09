// This code uses the OpenCV library to perform face recognition using the Eigenfaces algorithm. It first loads a set of face images from the "faces" directory and their corresponding labels. The face images are stored in a vector of Mat objects, and their labels are stored in a vector of integers.

// The code then creates a face recognizer using the EigenFaceRecognizer::create() method. This method creates an instance of the EigenFaceRecognizer class, which implements the Eigenfaces algorithm for face recognition.

// The code then trains the face recognizer on the face images and labels using the train() method of the EigenFaceRecognizer class.

// The code then loads a test image from the "faces" directory and predicts its label using the predict() method of the EigenFaceRecognizer class. The predict() method takes as input a test image and outputs its predicted label and confidence. The predicted label is an integer that corresponds to the label of the closest matching face image in the training set, and the confidence is a measure of the similarity between the test image and the closest matching face image.

// Finally, the code prints the predicted label and confidence to the console using the std::cout statement.



#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    // Load the face images and labels
    std::vector<Mat> images;
    std::vector<int> labels;
    for (int i = 1; i <= 10; i++)
    {
        for (int j = 1; j <= 5; j++)
        {
            std::string filename = "faces/s" + std::to_string(i) + "/" + std::to_string(j) + ".pgm";
            Mat image = imread(filename, IMREAD_GRAYSCALE);
            if (!image.empty())
            {
                images.push_back(image);
                labels.push_back(i);
            }
        }
    }

    // Create the face recognizer using the Eigenfaces algorithm
    Ptr<FaceRecognizer> recognizer = EigenFaceRecognizer::create();

    // Train the face recognizer on the face images and labels
    recognizer->train(images, labels);

    // Load a test image and predict its label
    Mat testImage = imread("faces/s4/7.pgm", IMREAD_GRAYSCALE);
    int predictedLabel = -1;
    double confidence = 0.0;
    recognizer->predict(testImage, predictedLabel, confidence);

    // Print the predicted label and confidence
    std::cout << "Predicted label = " << predictedLabel << std::endl;
    std::cout << "Confidence = " << confidence << std::endl;

    return 0;
}
