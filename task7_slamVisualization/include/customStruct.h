#ifndef CUSTOM_STRUCT_H
#define CUSTOM_STRUCT_H

#include <eigen3/Eigen/Core>
#include <iostream>
#include <iomanip>

struct VecXd {
    Eigen::VectorXd vec_ = Eigen::Vector3d::Zero();
};

inline std::ostream& operator << (std::ostream& out, const VecXd& r) {
    int N = r.vec_.size();
    out.setf(std::ios::fixed);
    out << " = " << "[";
    for (int i = 0; i < N; ++i) {
        out << std::setprecision(2) << r.vec_(i) << ", ";
    }
    out << r.vec_(N-1) << "]";
    return out;
}

inline std::istream& operator >> (std::istream& in, VecXd& r) {
    return in;
}

#endif /* CUSTOM_STRUCT_H */