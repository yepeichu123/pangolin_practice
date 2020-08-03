#include <pangolin/pangolin.h>

int main(int argc, char** argv) {

    // create display window that size if 640*480
    pangolin::CreateWindowAndBind("Main", 640, 480);

    // start depth measurement
    glEnable(GL_DEPTH_TEST);


    // create a camera viewpoint
    pangolin::OpenGlRenderState s_cam(
        pangolin::ProjectionMatrix(640, 480, 420, 420, 320, 320, 0.2, 100),
        pangolin::ModelViewLookAt(2, 0, 2,  0, 0, 0,  pangolin::AxisY)
    );

    // create an interactive viewpoint
    pangolin::Handler3D handler(s_cam);
    pangolin::View& d_cam = pangolin::CreateDisplay().SetBounds(0.0, 1.0, 0.0, 1.0,  -640.0f/480.0f).SetHandler(&handler);


    while (!pangolin::ShouldQuit()) {
        
        // clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        d_cam.Activate(s_cam);

        // create a box
        pangolin::glDrawColouredCube();

        // draw axis
        glLineWidth(3);
        glBegin(GL_LINES);
        glColor3f(0.8f, 0.f, 0.f);
        glVertex3f(-3, -3, -3);
        glVertex3f(0, -3, -3);
        glColor3f(0.f, 0.8f, 0.f);
        glVertex3f(-3, -3, -3);
        glVertex3f(-3, 0, -3);
        glColor3f(0.2f, 0.2f, 1.f);
        glVertex3f(-3, -3, -3);
        glVertex3f(-3, -3, 0);
        glEnd();

        // flash frames
        pangolin::FinishFrame();
    }

    
    return 0;
}