#include <pangolin/pangolin.h>
#include "slamVisualization.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
using namespace std;
using namespace cv;

int main(int argc, char** argv) {

    ifstream fp_gt("/home/ypc/xiaoc/dataset/EUROC/MH_01_easy/state_groundtruth_estimate0/data.csv");
    ifstream fp_img("/home/ypc/xiaoc/dataset/EUROC/MH_01_easy/cam0/data.csv");
    if (!fp_gt.is_open() || !fp_img.is_open()) {
        cout << "Failed to open file." << endl;
        return -1;
    }
    // create a visulization
    CSlamVisualization visualizer(1504, 960);

    // jump the first line
    string imgLine;
    getline(fp_img, imgLine);

    vector<double> vImgTimestamps;
    vector<string> vImgFileNames;
    while (getline(fp_img, imgLine)) {
        stringstream ss(imgLine);

        string filename;
        getline(ss, filename, ',');
        ulong timestamp = atoi(filename.c_str());
        // cout << timestamp << endl;
        vImgTimestamps.push_back(timestamp);

        filename = "/home/ypc/xiaoc/dataset/EUROC/MH_01_easy/cam0/data/" + filename + ".png";
        // Mat img1 = imread(filename, CV_LOAD_IMAGE_COLOR);
        // imshow("img", img1);
        // waitKey(0);
        vImgFileNames.push_back(filename);
    }
    // camera pose 
    vector<Eigen::Vector3d> traj;
    ulong timeStamp(0);
    double px(0.), py(0.), pz(0.);
    double qw(0.), qx(0.), qy(0.), qz(0.);
    double vx(0.), vy(0.), vz(0.);
    double bwx(0.), bwy(0.), bwz(0.), bax(0.), bay(0.), baz(0.);

    // jump the first line of ground truth
    string line;
    getline(fp_gt, line);

    // initialize view window
    visualizer.initDraw();
    int index = 0;
    while (getline(fp_gt, line)) {
        // clear color and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        visualizer.activeAllView();
        visualizer.registerUICallback();
        // read camera pose from gt file
        stringstream ss(line);
        vector<string> result;
        string tempLine;
        while (getline(ss, tempLine, ',')) {
            result.push_back(tempLine);
        }
        // construct pose
        timeStamp = atoi(result[0].c_str());
        px = atof(result[1].c_str());
        py = atof(result[2].c_str());
        pz = atof(result[3].c_str());
        qw = atof(result[4].c_str());
        qx = atof(result[5].c_str());
        qy = atof(result[6].c_str());
        qz = atof(result[7].c_str());
        Eigen::Quaterniond quat(qw, qx, qy, qz);
        Eigen::Vector3d pos(px, py, pz);
        traj.push_back(pos);
        // display data
        visualizer.displayData(pos, quat);
        // draw coordinate
        visualizer.drawCoordinate();
        // draw camera
        visualizer.drawCameraWithPose(pos, quat);
        // draw camera trajectory
        visualizer.drawCameraTrajectory(traj);
        double imuTime, imgTime;
        imuTime = (double)timeStamp / 1e9;
        imgTime = vImgTimestamps[index] / 1e9;
        cout << "imuTime = " << imuTime << endl;
        cout << "imgTime = " << imgTime << endl;
        if (imuTime > imgTime) {
            index++;
        }
        Mat imgOrigin, imgTrack; 
        string imgFile = vImgFileNames[index];
        imgOrigin = imread(imgFile, CV_LOAD_IMAGE_COLOR);
        // imshow("imgOrigin", imgOrigin);
        // waitKey(0);
        if (vImgFileNames.size() > 1) {
            string imgFileTrack = vImgFileNames[index + 1];
            imgTrack = imread(imgFileTrack, CV_LOAD_IMAGE_COLOR);
        }
        visualizer.displayImage(imgOrigin, imgTrack);
        
        pangolin::FinishFrame();

        if (pangolin::ShouldQuit()) {
            break;
        }
    }
    cout << "Finished drawing..." << endl;
    

    return 0;
}