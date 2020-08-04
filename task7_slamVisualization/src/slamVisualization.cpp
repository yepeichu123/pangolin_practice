#include "slamVisualization.h"


CSlamVisualization::CSlamVisualization(const int& width, const int& height) {
    mnWinWidth_ = width;
    mnWinHeight_ = height;
}

CSlamVisualization::~CSlamVisualization() {

}

void CSlamVisualization::initDraw() {
    pangolin::CreateWindowAndBind("cameraPose", mnWinWidth_, mnWinHeight_);
    glEnable(GL_DEPTH_TEST);

    // create a camera 
    mRSCam_ = pangolin::OpenGlRenderState(
        pangolin::ProjectionMatrix(mnWinWidth_, mnWinHeight_, 420, 420, 320, 240, 0.1, 1000),
        pangolin::ModelViewLookAt(5, -3, 5, 0, 0, 0, pangolin::AxisZ)
    );
    int PANEL_WIDTH = mnWinWidth_ / 4;
    int PANEL_HEIGHT = mnWinHeight_ / 4;


    // window to display trajectory
    mVCam_ = pangolin::CreateDisplay()
        .SetBounds(0., 1., pangolin::Attach::Pix(PANEL_WIDTH), 1., -(float)mnWinWidth_/(float)mnWinHeight_)
        .SetHandler(new pangolin::Handler3D(mRSCam_));
    
    // create control board
    pangolin::CreatePanel("ui")
        .SetBounds(pangolin::Attach::Pix(3.0f * PANEL_HEIGHT), 1.0, 0.0, pangolin::Attach::Pix(PANEL_WIDTH), (float)mnWinWidth_/(float)mnWinHeight_);
    

    // reset UI 
    mvUISet_.clear();
    pangolin::Var<bool> showCam("ui.showCam", true, true);
    mvUISet_.push_back(showCam);

    pangolin::Var<bool> showTraj("ui.showTraj", true, true);
    mvUISet_.push_back(showTraj);
    
    pangolin::Var<bool> showImg("ui.showImg", true, true);
    mvUISet_.push_back(showImg);

    pangolin::Var<bool> showCoordinate("ui.showCoordinate", true, true);
    mvUISet_.push_back(showCoordinate);

    pangolin::Var<bool> saveMap("ui.saveMap", false, false);
    mvUISet_.push_back(saveMap);

    pangolin::Var<bool> saveWin("ui.saveWin", false, false);
    mvUISet_.push_back(saveWin);

    
    // display data
    pangolin::CreatePanel("data")
        .SetBounds(pangolin::Attach::Pix(2.0f*PANEL_HEIGHT), pangolin::Attach::Pix(3.0f*PANEL_HEIGHT),
            0., pangolin::Attach::Pix(PANEL_WIDTH), (float)mnWinWidth_/(float)mnWinHeight_);
    
    
    // reset data
    mvDataSet_.clear();
    pangolin::Var<VecXd> currPos("dataPos", VecXd());
    mvDataSet_.push_back(currPos);

    pangolin::Var<VecXd> currAtt("dataEulerAngle", VecXd());
    mvDataSet_.push_back(currAtt);

    // display image
    mVImg_ = pangolin::CreateDisplay()
        .SetBounds(pangolin::Attach::Pix(1.0f*PANEL_HEIGHT), pangolin::Attach::Pix(2.0f*PANEL_HEIGHT),
            0., pangolin::Attach::Pix(PANEL_WIDTH), (float)mnWinWidth_/(float)mnWinHeight_)
        .SetLock(pangolin::LockLeft, pangolin::LockBottom);
    mTImgTexture_ = pangolin::GlTexture(752, 480, GL_RGB, false, 0, GL_BGR, GL_UNSIGNED_BYTE);
    
    // display tracking image
    mVTrack_ = pangolin::CreateDisplay()
        .SetBounds(0., pangolin::Attach::Pix(1.0f*PANEL_HEIGHT), 
            0., pangolin::Attach::Pix(1.0f*PANEL_WIDTH), (float)mnWinWidth_/(float)mnWinHeight_)
        .SetLock(pangolin::LockLeft, pangolin::LockBottom);
    mTTrackTexture_ = pangolin::GlTexture(752, 480, GL_RGB, false, 0, GL_BGR, GL_UNSIGNED_BYTE);
}

void CSlamVisualization::activeAllView() {
    mVCam_.Activate(mRSCam_);
}

void CSlamVisualization::drawCubeTest() {
    // render some stuff 
    glColor3f(1.0f, 0.0f, 1.0f);

    pangolin::glDrawColouredCube();
}

void CSlamVisualization::drawCameraWithPose(const Eigen::Vector3d& pos, const Eigen::Quaterniond& quat) {
    if (!mbCamVisuable_) {
        return;
    }
    Eigen::Matrix3d R = quat.toRotationMatrix();
    glPushMatrix();
    std::vector<GLdouble> Twc = {
        R(0, 0), R(1, 0), R(2, 0), 0.,
        R(0, 1), R(1, 1), R(2, 1), 0.,
        R(0, 2), R(1, 2), R(2, 2), 1.,
        pos.x(), pos.y(), pos.z(), 1.0,
    };
    glMultMatrixd(Twc.data());
    drawCameraModel();
    glPopMatrix();
}

void CSlamVisualization::drawCameraTrajectory(const std::vector<Eigen::Vector3d>& traj) {
    if (!mbTrajVisuable_) {
        return;
    }

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3f(0.f, 1.0f, 0.f);
    for (size_t i = 0; i < traj.size() - 1; ++i) {
        glVertex3f(traj[i].x(), traj[i].y(), traj[i].z());
        glVertex3f(traj[i + 1].x(), traj[i + 1].y(), traj[i + 1].z());
    }
    glEnd();
}

void CSlamVisualization::drawCameraModel(const float& scale) {
    if (scale < 0) {
        std::cerr << "scale should be positive! \n";
        return;
    }

    const float w = 0.2 * scale;
    const float h = w * 0.75;
    const float z = w * 0.6;

    glLineWidth(2 * scale);
    // draw camera model
    glBegin(GL_LINES);
    glColor3f(0.0f, 1.0f, 1.0f);
        glVertex3f(0, 0, 0);    glVertex3f(w, h, z);
        glVertex3f(0, 0, 0);    glVertex3f(w, -h, z);
        glVertex3f(0, 0, 0);    glVertex3f(-w, -h, z);
        glVertex3f(0, 0, 0);    glVertex3f(-w, h, z);
        glVertex3f(w, h, z);    glVertex3f(w, -h, z);
        glVertex3f(-w, h, z);   glVertex3f(-w, -h, z);
        glVertex3f(-w, h, z);   glVertex3f(w, h, z);
        glVertex3f(-w, -h, z);    glVertex3f(w, -h, z);
    glEnd();

    return;
}

void CSlamVisualization::drawCoordinate() {
    if (!mbCoordinateVisuable_) {
        return;
    }

    glLineWidth(3);
    glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(0, 0, 0);    glVertex3f(1, 0, 0);
        glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3f(0, 0, 0);    glVertex3f(0, 1, 0);
        glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f(0, 0, 0);    glVertex3f(0, 0, 1);
    glEnd();

}

void CSlamVisualization::displayImage(const cv::Mat& originImg, const cv::Mat& trackImg) {
    if (!mbImageVisuable_) {
        return;
    }

    mTImgTexture_.Upload(originImg.data, GL_BGR, GL_UNSIGNED_BYTE);
    // display image 
    mVImg_.Activate();
    glColor3f(1.0f, 1.0f, 1.0f);
    mTTrackTexture_.RenderToViewportFlipY();

    mTTrackTexture_.Upload(trackImg.data, GL_BGR, GL_UNSIGNED_BYTE);
    // display image
    mVTrack_.Activate();
    glColor3f(1.0f, 1.0f, 1.0f);
    mTTrackTexture_.RenderToViewportFlipY();
}

void CSlamVisualization::displayData(const Eigen::Vector3d& pos, const Eigen::Quaterniond& quat) {
    VecXd tempPose, tempEuler;
    tempPose.vec_ = pos;
    tempEuler.vec_ = quat.matrix().eulerAngles(2, 1, 0);
    tempEuler.vec_ *= (180 / M_PI);
    mvDataSet_[0] = tempPose;
    mvDataSet_[1] = tempEuler;
}

void CSlamVisualization::registerUICallback() {
    mbCamVisuable_ = mvUISet_[0] ? true : false;
    mbTrajVisuable_ = mvUISet_[1] ? true : false;
    mbImageVisuable_ = mvUISet_[2] ? true : false;
    mbCoordinateVisuable_ = mvUISet_[3] ? true : false;

    if (pangolin::Pushed(mvUISet_[4])) {
        mVCam_.SaveOnRender("map");
    }

    if (pangolin::Pushed(mvUISet_[5])) {
        pangolin::SaveWindowOnRender("win");
    }
}