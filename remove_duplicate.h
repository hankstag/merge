#ifndef REMOVE_DUPLICATE_H
#define REMOVE_DUPLICATE_H

#include <igl/sortrows.h>

void remove_duplicate(
    Eigen::MatrixXd& V,
    Eigen::MatrixXi& F,
    Eigen::VectorXi& C
);

#endif