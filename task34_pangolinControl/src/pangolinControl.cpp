#include <pangolin/pangolin.h>
#include <string>
#include <iostream>

using namespace std;

void SampleMethod() {
    cout << "You typed ctrl-r or pushed reset." << std::endl;
}

int main(int argc, char** argv) {

    // create window
    pangolin::CreateWindowAndBind("Main", 640, 480);

    // start depth measurement
    glEnable(GL_DEPTH_TEST);


    // create camera 
    pangolin::OpenGlRenderState s_cam(
        pangolin::ProjectionMatrix(640, 480, 420, 420, 320, 240, 0.2, 1000),
        pangolin::ModelViewLookAt(-0, 0.5, -3, 0, 0, 0, pangolin::AxisY)
    );

    // divide view window
    const int UI_WIDTH = 180;

    // show view window in the right
    pangolin::View& d_cam = pangolin::CreateDisplay()
        .SetBounds(0.0, 1.0, pangolin::Attach::Pix(UI_WIDTH), 1.0, -640.0f/480.0f)
        .SetHandler(new pangolin::Handler3D(s_cam));

    // creat control board in the left
    pangolin::CreatePanel("ui")
        .SetBounds(0.0, 1.0, 0.0, pangolin::Attach::Pix(UI_WIDTH));

    // create control
    // bool means checkbox or button, checkbox if the last paramete is true 
    // and button if the last parameter is false
    pangolin::Var<bool> A_Button("ui.a_button", false, false);
    pangolin::Var<bool> A_Checkbox("ui.a_checkbox", false, true);

    // double/int/float means slider
    pangolin::Var<double> Double_Slider("ui.a_slider", 3, 0, 5);
    pangolin::Var<int> Int_Slider("ui.b_slider", 2, 0, 5);
    pangolin::Var<string> A_string("ui.a_string", "Hello Pangolin");

    pangolin::Var<bool> SAVE_IMG("ui.save_img", false, false);
    pangolin::Var<bool> SAVE_WIN("ui.save_win", false, false);
    pangolin::Var<bool> RECORD_WIN("ui.record_win", false, false);

    pangolin::Var<std::function<void()>> reset("ui.Reset", SampleMethod);


    // demonstration of how we can register a keyboard hook to alter a Var
    pangolin::RegisterKeyPressCallback(pangolin::PANGO_CTRL+'b', pangolin::SetVarFunctor<double>("ui.a_slider", 3.5));

    // demonstration of how we can register a keyboard hook to trigger a method
    pangolin::RegisterKeyPressCallback(pangolin::PANGO_CTRL+'r', SampleMethod);


    // we must use pangolin::Pushed(Button) to check if the button has been typed
    while (!pangolin::ShouldQuit()) {
        // clear entire screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // callback function of each control
        if (pangolin::Pushed(A_Button)) {
            cout << "Push button A..." << endl;
        }

        if (A_Checkbox) {
            Int_Slider = Double_Slider;
        }

        // save all win
        if (pangolin::Pushed(SAVE_WIN)) {
            pangolin::SaveWindowOnRender("Window");
        }

        // save view
        if (pangolin::Pushed(SAVE_IMG)) {
            d_cam.SaveOnRender("cube");
        }

        // record
        if (pangolin::Pushed(RECORD_WIN)) {
            pangolin::DisplayBase().RecordOnRender("ffmpeg:[fps=50,bps=8388608,unique_filename]//screencap.avi");
        }

        d_cam.Activate(s_cam);

        pangolin::glDrawColouredCube();

        // swap frames and process events
        pangolin::FinishFrame();
    }

    return 0;
}