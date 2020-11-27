//
// Created by 何博 on 2020/11/24.
//

#pragma once

#include "headers.hpp"

void get_node_map(unordered_map<int, int> &file2matrix, unordered_map<int, int> &matrix2file);

void read_into_matrix(Matrix<double, Dynamic, Dynamic> &matrix, unordered_map<int, int> &file2matrix);

void get_sparse_matrix(unordered_map<int, int> &file2matrix, vector<pair<int, int> > &sparse_matrix, vector<int> &out_degree);

void read_into_matrix_d(Matrix<double, Dynamic, Dynamic> &matrix);

void write_result(RowVectorXd &result_vector, unordered_map<int, int> &matrix2file, const double &teleport_parameter);

void write_result(vector<vector<double> > &result_vector, unordered_map<int, int> &matrix2file, const double &teleport_parameter);