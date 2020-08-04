#include <pangolin/pangolin.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

int main(int argc, char** argv) {

    ifstream fp_gt("/home/ypc/xiaoc/dataset/EUROC/MH_01_easy/state_groundtruth_estimate0/data.csv");
    if (!fp_gt.is_open()) {
        cout << "Failed to open file." << endl;
        return -1;
    }

    // jump the first line
    string line;
    getline(fp_gt, line);

    // create window
    pangolin::CreateWindowAndBind("cameraPose", 752*2, 480*2);

    // open depth measurement
    glEnable(GL_DEPTH_TEST);

    // create camera
    pangolin::OpenGlRenderState s_cam = pangolin::OpenGlRenderState(
        pangolin::ProjectionMatrix(752*2, 480*2, 420, 420, 320, 240, 0.1, 1000),
        pangolin::ModelViewLookAt(5, -3, 5, 0, 0, 0, pangolin::AxisZ)
    );

    // create display view
    pangolin::View& d_cam = pangolin::CreateDisplay()
        .SetBounds(0., 1., 0., 1., -752/480.0f)
        .SetHandler(new pangolin::Handler3D(s_cam));


    // camera pose 
    vector<Eigen::Vector3d> traj;
    ulong timeStamp(0);
    double px(0.), py(0.), pz(0.);
    double qw(0.), qx(0.), qy(0.), qz(0.);
    double vx(0.), vy(0.), vz(0.);
    double bwx(0.), bwy(0.), bwz(0.), bax(0.), bay(0.), baz(0.);

    while (getline(fp_gt, line)) {
        // clear color and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // activate camera in display window
        d_cam.Activate(s_cam);

        
        // read camera pose from gt file
        stringstream ss(line);
        vector<string> result;
        string tempLine;
        while (getline(ss, tempLine, ',')) {
            result.push_back(tempLine);
        }
        
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
        cout << timeStamp << ": " << px << " " << py << " " << pz << endl;

        // draw coordinate
        glLineWidth(3);
        glBegin(GL_LINES);
            glColor3f(1.0f, 0.0f, 0.0f);
                glVertex3f(0, 0, 0);    glVertex3f(1, 0, 0);
            glColor3f(0.0f, 1.0f, 0.0f);
                glVertex3f(0, 0, 0);    glVertex3f(0, 1, 0);
            glColor3f(0.0f, 0.0f, 1.0f);
                glVertex3f(0, 0, 0);    glVertex3f(0, 0, 1);
        glEnd();

        // -------draw camera pose-----------
        // construct pose transform matrix
        Eigen::Matrix3d R = quat.toRotationMatrix();

        glPushMatrix();
            vector<GLdouble> Twc = {
                R(0, 0), R(1, 0), R(2, 0), 0.,
                R(0, 1), R(1, 1), R(2, 1), 0.,
                R(0, 2), R(1, 2), R(2, 2), 0.,
                pos.x(), pos.y(), pos.z(), 1,
            };
        glMultMatrixd(Twc.data());

        // draw camera 
        const float w = 0.2;
        const float h = w * 0.75;
        const float z = w * 0.6;
        glLineWidth(2);
        glBegin(GL_LINES);
            glColor3f(0.0, 1.0f, 1.0f);
                glVertex3f(0, 0, 0);    glVertex3f(w, h, z);
                glVertex3f(0, 0, 0);    glVertex3f(w, -h, z);
                glVertex3f(0, 0, 0);    glVertex3f(-w, -h, z);
                glVertex3f(0, 0, 0);    glVertex3f(-w, h, z);
                glVertex3f(w, h, z);    glVertex3f(w, -h, z);
                glVertex3f(-w, h, z);    glVertex3f(-w, -h, z);
                glVertex3f(-w, h, z);    glVertex3f(w, h, z);
                glVertex3f(-w, -h, z);    glVertex3f(w, -h, z);
        glEnd();
        glPopMatrix();

        // draw camera trajectory
        glLineWidth(2);
        glBegin(GL_LINES);
            glColor3f(0.0f, 1.0f, 0.0f);
            for (int i = 1; i < traj.size()-1; i++) {
                glVertex3d(traj[i].x(), traj[i].y(), traj[i].z());
                glVertex3d(traj[i+1].x(), traj[i+1].y(), traj[i+1].z());
            }
        glEnd();
        
        pangolin::FinishFrame();

        if (pangolin::ShouldQuit()) {
            break;
        }
    }
    cout << "Finished drawing..." << endl;
    

    return 0;
}