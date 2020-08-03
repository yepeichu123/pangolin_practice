#include <pangolin/pangolin.h>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char** argv) {

    // create window
    pangolin::CreateWindowAndBind("Main", 640, 480);

    // data log object
    pangolin::DataLog log;

    // set labels
    vector<string> labels;
    labels.push_back(string("sin(t)"));
    labels.push_back(string("cos(t)"));
    labels.push_back(string("sin(t)+cos(t)"));
    log.SetLabels(labels);

    const float tinc = 0.01f;

    // opengl view of data
    pangolin::Plotter plotter(&log, 0.0f, 4.0f*(float)M_PI/tinc, -4.0f, 4.0f, (float)M_PI/(4*tinc), 0.5f);
    plotter.SetBounds(0.0, 1.0, 0.0, 1.0);
    plotter.Track("$i");


    pangolin::DisplayBase().AddDisplay(plotter);

    float t = 0;
    while (!pangolin::ShouldQuit()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        log.Log(sin(t), cos(t), sin(t)+cos(t));
        t += tinc;

        pangolin::FinishFrame();
    }


    return 0;
}