//
// Created by 何博 on 2020/11/24.
//

#include "dense_dynamic.hpp"

int dense_dynamic(double teleport_parameter = 0.85)
{
    unordered_map<int, int> file2matrix, matrix2file;
    get_node_map(file2matrix, matrix2file);
    const unsigned int node_number = file2matrix.size();

    Matrix<double, Dynamic, Dynamic> adjacency_matrix(node_number, node_number);
    adjacency_matrix.setZero();
    read_into_matrix(adjacency_matrix, file2matrix);

    Matrix<double, Dynamic, Dynamic> transform_matrix = teleport_parameter * adjacency_matrix;

    RowVectorXd new_v(node_number), old_v(node_number), base(node_number);
    old_v.setConstant(1.0 / node_number);
    new_v.setConstant(1.0 / node_number);
    base.setConstant((1.0 - teleport_parameter) / node_number);

    double current_delta = 1.0;
    while (current_delta > epsilon)
    {
        new_v *= transform_matrix;
        base.setConstant((1.0 - new_v.sum()) / node_number);
        new_v += base;
        current_delta = (new_v - old_v).norm();
        old_v = new_v;
    }
    write_result(new_v, matrix2file, teleport_parameter);
    cout << "in dense dynamic" << endl;
    return 0;
}
