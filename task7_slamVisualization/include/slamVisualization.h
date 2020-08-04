#ifndef SLAM_VISUALIZATION_H
#define SLAM_VISUALIZATION_H

#include <eigen3/Eigen/Core>
#include <opencv2/opencv.hpp>
#include <pangolin/pangolin.h>
#include "customStruct.h"

class CSlamVisualization {
    public:
        CSlamVisualization(const int& width = 752, const int& height = 480);

        ~CSlamVisualization();

        void initDraw();

        void activeAllView();

        void drawCubeTest();

        void drawCameraWithPose(const Eigen::Vector3d& pos, const Eigen::Quaterniond& quat);

        void drawCameraTrajectory(const std::vector<Eigen::Vector3d>& traj);

        void drawCameraModel(const float& scale = 1.0);

        void drawCoordinate();

        void displayImage(const cv::Mat& originImg, const cv::Mat& trackImg);

        void displayData(const Eigen::Vector3d& pos, const Eigen::Quaterniond& quat);

        void registerUICallback();

    private:
        pangolin::OpenGlRenderState mRSCam_;
        pangolin::View mVCam_, mVImg_, mVTrack_;
        pangolin::GlTexture mTImgTexture_, mTTrackTexture_;
        pangolin::DataLog mDPoseLog_;

        // control object to save UI board
        std::vector<pangolin::Var<bool>> mvUISet_;
        
        // control object to save data board
        std::vector<pangolin::Var<VecXd>> mvDataSet_;

        // display camera or not
        bool mbCamVisuable_;

        // display trajectory
        bool mbTrajVisuable_;

        // display coordinate or not
        bool mbCoordinateVisuable_;

        // display image or not
        bool mbImageVisuable_;

        // size of window
        int mnWinWidth_;
        int mnWinHeight_;
};


#endif /* SLAM_VISUALIZATION */