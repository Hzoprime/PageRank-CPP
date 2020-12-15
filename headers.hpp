//
// Created by 何博 on 2020/11/24.
//

#pragma once
#include <iostream>
#include <cmath>
#include <eigen3/Eigen/Sparse>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Core>
#include <chrono>
#include <vector>
#include <numeric>
#include <algorithm>
#include <fstream>
#include <set>
#include <unordered_map>
#include <map>
#include <eigen3/Eigen/Eigenvalues>
#include <iomanip>
#include <cstring>
#include <sstream>

// const double epsilon = std::numeric_limits<double>::epsilon();
const double epsilon = 1e-8;
using Eigen::ColMajor;
using Eigen::Dense;
using Eigen::Dynamic;
using Eigen::Matrix;
using Eigen::RealSchur;
using Eigen::RowMajor;
using Eigen::RowVectorXd;
using Eigen::SparseMatrix;

using std::accumulate;
using std::cout;
using std::endl;
using std::ifstream;
using std::ios;
using std::make_pair;
using std::map;
using std::ofstream;
using std::pair;
using std::pow;
using std::set;
using std::setfill;
using std::setiosflags;
using std::setprecision;
using std::sort;
using std::sqrt;
using std::transform;
using std::unordered_map;
using std::vector;
using std::strcmp;
using std::accumulate;
using std::transform;
using std::stringstream;
