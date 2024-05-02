#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <opencv2/opencv.hpp>
#include <unistd.h>
#include <ctime>
#include <omp.h>
#include <vector>
#include <cmath>
#include <cfloat>
#include <cstdlib>

using namespace std;
using namespace cv; 

#define TOLERANCE 0.2


// Argument parser function
pair<int, int> argparser(int argc, char* argv[]) {
    int K = -1;
    int max_iterations = -1;
    int opt;

    while ((opt = getopt(argc, argv, "k:i:")) != -1) {
        switch (opt) {
            case 'k':
                K = atoi(optarg);
                break;
            case 'i':
                max_iterations = atoi(optarg);
                break;
            default:
                cerr << "Usage: " << argv[0] << " -k <Kmeans size> -i <Max Iterations>" << endl;
                exit(EXIT_FAILURE);
        }
    }

    if (K == -1 || max_iterations == -1) {
        cerr << "Both -k and -i options are required." << endl;
        exit(EXIT_FAILURE);
    }

    return make_pair(K, max_iterations);
}

// Function to read data from a file
void readDataFromFile(const string& filename, Mat& matrix) {
  
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return; // Return empty matrix if file cannot be opened
    }

    // Leemos los píxeles hiperespectrales uno a uno
    string line;
    unsigned int row = 0, col = 0;
    while (getline(file, line)) {
        istringstream iss(line);
        string element;
        while (getline(iss, element, ',')) {

            float value;
            stringstream(element) >> value;
            matrix.at<float>(row, col) = value;
  

            ++col;
            if (col >= matrix.size().width) {
                col = 0;
                ++row;
            }

            if (row >= matrix.size().height)
                break;
        }
    }

    file.close();
    return;
}

int kmeans(const Mat& data, int K, int max_iterations, Mat& labels, Mat& centers) {
    // Inicializamos los centroides
    centers = Mat(K, data.cols, data.type());
    #pragma omp parallel for
    for (int i = 0; i < K; ++i) {
        int random_index = rand() % data.rows;
        data.row(random_index).copyTo(centers.row(i));
    }

    // Inicializamos las etiquetas
    labels = Mat(data.rows, 1, CV_32S);

    // K-means algorithm
    int iteration;
    for (iteration = 0; iteration < max_iterations; ++iteration) {
        
        #pragma omp parallel for // Paralelice el bucle externo
        for (int i = 0; i < data.rows; ++i) {
            float min_distance = FLT_MAX;
            int label = 0;
            for (int j = 0; j < K; ++j) {
                float distance = norm(data.row(i), centers.row(j));
                if (distance < min_distance) {
                    min_distance = distance;
                    label = j;
                }
            }
            labels.at<int>(i) = label;
        }

        // Update centers
        Mat new_centers = Mat::zeros(centers.size(), centers.type());
        vector<int> counts(K, 0);

        #pragma omp parallel for
        for (int i = 0; i < data.rows; ++i) {
            int label = labels.at<int>(i);
            #pragma omp critical
            {
                new_centers.row(label) += data.row(i); // Critical para evitar condiciones de carrera
                counts[label]++;
            }
        }

        #pragma omp parallel for
        for (int i = 0; i < K; ++i) {
            if (counts[i] > 0) {
                new_centers.row(i) /= counts[i];
            }
        }

        // Comprobamos la convergencia
        if (norm(new_centers, centers) < TOLERANCE) {
            break;
        }

        centers = new_centers;
    }
    return iteration;
}


time_t run_kmeans(const Mat& data, int K, int max_iterations, Mat& labels, Mat& centers) {
    time_t start, end;
    int iterations = 0;
    time(&start);
    iterations = kmeans(data, K, max_iterations, labels, centers);
    time(&end);
    cout << "K-means completed in " << iterations << " iterations" << endl;
    return difftime(end, start);
}

int main(int argc, char* argv[]) {
    auto args = argparser(argc, argv);
    int K = args.first;
    int max_iterations = args.second;

    // Data loading
    string filename = "pavia.txt";
    Mat data(783640, 102, CV_32F); // Data with 783640 points and 102 features
    readDataFromFile(filename, data);

    // Custom K-means call
    Mat labels, centers;

    time_t time;
    time = run_kmeans(data, K, max_iterations, labels, centers);

    cout << "Time taken to read data: " << time << " seconds" << endl;

    cout << "Clustered data:" << endl;
    cout << "Labels size: " << labels.size() << endl;
    cout << "Centers size: " << centers.size() << endl;

    labels = labels.reshape(1, 715);
    cout << "label size after reshape: " << labels.size() << endl;

    cout << "centers size: " << centers.size() << endl;

    Mat cluster_map(715, 1096, CV_8U);
    cout << "cluster map size: " << cluster_map.size() << endl;

    int index = 0;
    int prev_label = 0;

    for (int i = 0; i < cluster_map.rows; ++i) {
        for (int j = 0; j < cluster_map.cols; ++j) {
            int l = cluster_map.at<uchar>(i, j) = labels.at<int>(i, j);
            if (prev_label != cluster_map.at<unsigned char>(i, j)){
                prev_label = cluster_map.at<uchar>(i, j);
            }
        }
    }

    cout << "Reshaped matrix size: " << cluster_map.size() << endl;

    Mat result_image(715, 1096, CV_8UC3);

    const Vec<uchar, 3> colors[] = {
        Vec<uchar, 3>(0, 0, 255),   // Red
        Vec<uchar, 3>(0, 255, 0),   // Green
        Vec<uchar, 3>(255, 0, 0),   // Blue
        Vec<uchar, 3>(255, 255, 0), // Yellow
        Vec<uchar, 3>(255, 0, 255), // Magenta
        Vec<uchar, 3>(0, 255, 255), // Cyan
        Vec<uchar, 3>(255, 255, 255), // White
        Vec<uchar, 3>(0, 0, 0),     // Black
        Vec<uchar, 3>(128, 128, 128), // Gray
        Vec<uchar, 3>(64, 64, 64) // Gray
    };

    index = 0;
    for (int i = 0; i < result_image.rows; ++i) {
        for (int j = 0; j < result_image.cols; ++j) {
            uchar cluster_index = cluster_map.at<unsigned char>(index++);
            result_image.at<Vec3b>(i, j) = colors[cluster_index];
        }
    }

    Mat resultT;
    transpose(result_image, resultT);
    imshow("Clustered Image", resultT);
    imwrite("paviakmeanscpp.jpg", resultT);
    waitKey(0);

    return 0;
}
