#include <pangolin/pangolin.h>
#include <string>
#include <thread>
#include <iostream>

using namespace std;

string window_name = "HelloPangolinThreads";

void setup() {
    // create a window and bind its context to the main thread
    pangolin::CreateWindowAndBind(window_name, 640, 480);

    // enable depth
    glEnable(GL_DEPTH_TEST);

    // unset the current context for the current thread
    pangolin::GetBoundWindow()->RemoveCurrent();
}

void run() {
    // fetch the context and bind it to this thread
    pangolin::BindToContext(window_name);

    // we manually need to restore the properties of the context
    glEnable(GL_DEPTH_TEST);

    // define projection and initial ModelView matrix
    pangolin::OpenGlRenderState s_cam(
        pangolin::ProjectionMatrix(640, 480, 420, 420, 320, 320, 0.2, 100),
        pangolin::ModelViewLookAt(-2, 2, -2,  0, 0, 0, pangolin::AxisY)
    );

    // create interactive view in window
    pangolin::Handler3D handler(s_cam);
    pangolin::View& d_cam = pangolin::CreateDisplay().SetBounds(0.0, 1.0, 0.0, 1.0, -640.0f/480.0f).SetHandler(&handler);

    while (!pangolin::ShouldQuit()) {
        // clear screen and activate view to render into 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        d_cam.Activate(s_cam);

        // render OpenGL Cube
        pangolin::glDrawColouredCube();

        // swap frames and process evnets
        pangolin::FinishFrame();
    }

    // unset the current context for the current thread
    pangolin::GetBoundWindow()->RemoveCurrent();
}


int main(int argc, char** argv) {

    // create window and context in the main thread
    setup();

    // use the context in a separate rendering thread
    cout << "\nEnter another thread..." << endl;
    thread render_loop;
    render_loop = thread(run);
    render_loop.join();

    cout << "Enter main thread..." << endl;
    for (int i = 0; i < 10; ++i) {
        cout << "i = " << i << endl;
    }
    return 0;
}