#include "remove_duplicate.h"
#include <map>
void remove_duplicate(
    Eigen::MatrixXd& V,
    Eigen::MatrixXi& F,
    Eigen::VectorXi& C
){
    Eigen::VectorXi I;
    Eigen::MatrixXd S;
    Eigen::MatrixXd Vn = V;
    igl::sortrows(V,true,S,I);

    Eigen::VectorXi U; // map from initial index to Vn
    U.setConstant(V.rows(),-1);
    C.setConstant(V.rows(),0);

    // set first row of Vn
    Vn.row(0)<<S.row(0);
    U(I(0)) = 0;
    C(0) = I(0);

    int n = 0;
    for(int i=1;i<S.rows();i++){
        if((Vn.row(n)-S.row(i)).norm() > 0){
            Vn.row(++n)<<S.row(i);
            U(I(i)) = n;
            C(n) = I(i);
        }else{
            U(I(i)) = n;
            if(I(i) < C(n)) // always keep the smaller index since sortrows is not stable 
                C(n) = I(i);
        }
    }
    Vn.conservativeResize(n+1,V.cols());
    C.conservativeResize(n+1);

    // sort again to preserve the initial ordering
    Eigen::MatrixXd S2(Vn.rows(),Vn.cols()+1);
    S2 << C.cast<double>(),Vn;
    Eigen::VectorXi II;
    Eigen::MatrixXd Tn;
    igl::sortrows(S2,true,Tn,II);
    C = Tn.leftCols(1).cast<int>();
    Vn = Tn.rightCols(Tn.cols()-1);

    std::map<int,int> Z;
    for(int i=0;i<II.rows();i++)
        Z[II(i)] = i;
    for(int i=0;i<F.rows();i++){
        for(int k=0;k<3;k++){
            F(i,k) = Z[U(F(i,k))];
        }
    }
    V = Vn;
}