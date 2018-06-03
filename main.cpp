#include <igl/opengl/glfw/Viewer.h>
#include "remove_duplicate.h"
#include <igl/readOBJ.h>
#include <igl/writeOBJ.h>
#include <igl/boundary_loop.h>

int main(int argc, char *argv[])
{
  
  if(argc < 2){
    std::cout<<"usage: ./example_bin path_to_file"<<std::endl;
    return 0;
  }
  std::string fname = argv[1];
  Eigen::MatrixXd V;
  Eigen::MatrixXd uv;
  Eigen::MatrixXi F;
  Eigen::MatrixXi Fuv,FN;
  Eigen::MatrixXd CN;
  igl::readOBJ(fname,V,uv,CN,F, Fuv,FN);
  std::vector<std::vector<int>> bd;
  igl::boundary_loop(F,bd);
  std::cout<<"before #bd("<<bd.size()<<")"<<std::endl;
  Eigen::VectorXi I;
  remove_duplicate(V,F,I);
  std::cout<<"merging ... "<<std::endl;
  bd.clear();
  igl::boundary_loop(F,bd);
  std::cout<<"result #bd("<<bd.size()<<")"<<std::endl;
  // Plot the mesh
//   igl::opengl::glfw::Viewer viewer;
//   viewer.data().set_mesh(V, F);
//   viewer.data().set_face_based(true);
//   viewer.launch();
   // output mesh
  std::string file = fname + "_merged.obj";
  igl::writeOBJ(file,V,F,CN,FN,uv,F);
}
