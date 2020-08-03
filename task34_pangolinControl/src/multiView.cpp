#include <pangolin/pangolin.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv) {

    // create window
    pangolin::CreateWindowAndBind("Main", 640, 480);

    // start depth measurement
    glEnable(GL_DEPTH_TEST);

    // setup camera 
    pangolin::OpenGlRenderState s_cam(
        pangolin::ProjectionMatrix(752, 480, 420, 420, 320, 320, 0.1, 1000),
        pangolin::ModelViewLookAt(-2, 0, -2, 0, 0, 0, pangolin::AxisY)
    );

    // create 3 view images
    pangolin::View& d_cam = pangolin::Display("cam")
        .SetBounds(0.0, 1.0, 0.0, 1.0, -752/480.)
        .SetHandler(new pangolin::Handler3D(s_cam));

    pangolin::View& cv_img_1 = pangolin::Display("image_1")
        .SetBounds(2/3.0f, 1.0, 0., 1/3.0f, 752/480.)
        .SetLock(pangolin::LockLeft, pangolin::LockTop);

    pangolin::View& cv_img_2 = pangolin::Display("image_2")
        .SetBounds(0, 1/3.0f, 2/3.0f, 1.0, 752/480.);

    // create glTexture container to read images
    pangolin::GlTexture imgTexture1(752, 480, GL_RGB, false, 0, GL_BGR, GL_UNSIGNED_BYTE);
    pangolin::GlTexture imgTexture2(752, 480, GL_RGB, false, 0, GL_BGR, GL_UNSIGNED_BYTE);


    while (!pangolin::ShouldQuit()) {
        // clear color and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // activate camera 
        d_cam.Activate(s_cam);

        // add cube
        glColor3f(1.0f, 1.0f, 1.0f);
        pangolin::glDrawColouredCube();

        // read image from file
        Mat img1 = imread("../data/img1.png");
        Mat img2 = imread("../data/img2.png");

        // load image into GPU
        imgTexture1.Upload(img1.data, GL_BGR, GL_UNSIGNED_BYTE);
        imgTexture2.Upload(img2.data, GL_BGR, GL_UNSIGNED_BYTE);

        // display image 
        cv_img_1.Activate();
        glColor3f(1.0f, 1.0f, 1.0f);
        imgTexture1.RenderToViewportFlipY();

        cv_img_2.Activate();
        glColor3f(1.0f, 1.0f, 1.0f);
        imgTexture2.RenderToViewportFlipY();

        pangolin::FinishFrame();
    }
    return 0;
}