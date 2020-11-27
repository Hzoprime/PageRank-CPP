//
// Created by 何博 on 2020/11/24.
//

#include "io.hpp"

template <typename M>
void devided_by_row_sum(M &matrix)
{
    for (int i = 0; i < matrix.rows(); i++)
    {
        double r = matrix.row(i).sum();
        if (r <= epsilon)
        {
            continue;
        }
        matrix.row(i) /= r;
    }
}

void get_node_map(unordered_map<int, int> &file2matrix, unordered_map<int, int> &matrix2file)
{
    ifstream f("./data/WikiData.txt");
    int source, target;
    int count = 0;
    while (f >> source >> target)
    {
        if (!file2matrix.count(source))
        {
            file2matrix[source] = count;
            matrix2file[count++] = source;
        }
        if (!file2matrix.count(target))
        {
            file2matrix[target] = count;
            matrix2file[count++] = target;
        }
    }
}

void read_into_matrix(Matrix<double, Dynamic, Dynamic> &matrix, unordered_map<int, int> &file2matrix)
{
    ifstream f("./data/WikiData.txt");
    if (!f.is_open())
    {
        cout << "not open in read_into_matrix" << endl;
    }
    int source, target;
    while (f >> source >> target)
    {
        matrix(file2matrix[source], file2matrix[target]) = 1;
    }
    devided_by_row_sum(matrix);
}

void read_into_matrix_d(Matrix<double, Dynamic, Dynamic> &matrix)
{
    ifstream f("./data/WikiData.txt");
    int source, target;
    while (f >> source >> target)
    {
        matrix(source, target) = 1;
    }
    devided_by_row_sum(matrix);
}

void write_result(RowVectorXd &result_vector, unordered_map<int, int> &matrix2file, const double &teleport_parameter)
{
    vector<pair<double, int>> v;
    v.reserve(result_vector.size());
    for (int i = 0; i < result_vector.size(); ++i)
    {
        v.emplace_back(result_vector(i), i);
    }
    sort(
        v.begin(),
        v.end(),
        [](const pair<double, int> &a, const pair<double, int> &b) {
            if (a.first != b.first)
            {
                return a.first > b.first;
            }
            return a.second > b.second;
        });
    ofstream f("./data/result.txt");
    cout << setprecision(14) << setiosflags(ios::fixed);
    f << setprecision(14) << setiosflags(ios::fixed);
    for (int i = 0; i < 100; i++)
    {
        auto &p = v[i];
        cout << matrix2file[p.second] << ' ' << p.first << endl;
        f << matrix2file[p.second] << ' ' << p.first << endl;
    }
}

auto comparator = [](const pair<int, int> &a, const pair<int, int> &b) {
    if (a.second != b.second)
    {
        return a.second < b.second;
    }
    return a.first < b.first;
};

void get_sparse_matrix(unordered_map<int, int> &file2matrix, vector<pair<int, int>> &sparse_matrix, vector<int> &out_degree)
{
    ifstream f("./data/WikiData.txt");

    int source, target;

    while (f >> source >> target)
    {
        sparse_matrix.emplace_back(file2matrix[source], file2matrix[target]);
        out_degree[file2matrix[source]]++;
    }

    sort(sparse_matrix.begin(), sparse_matrix.end(), comparator);
}

void write_result(vector<vector<double>> &result_vector, unordered_map<int, int> &matrix2file, const double &teleport_parameter)
{
    const unsigned int block_size = result_vector.front().size();
    vector<pair<double, int>> v;
    for (size_t i = 0; i < result_vector.size(); i++)
    {
        for (size_t j = 0; j < result_vector.front().size(); j++)
        {
            v.emplace_back(result_vector[i][j], i * block_size + j);
        }
    }

    sort(
        v.begin(),
        v.end(),
        [](const pair<double, int> &a, const pair<double, int> &b) {
            if (a.first != b.first)
            {
                return a.first > b.first;
            }
            return a.second > b.second;
        });
    ofstream f("./data/block_result.txt");
    cout << setprecision(14) << setiosflags(ios::fixed);
    f << setprecision(14) << setiosflags(ios::fixed);
    for (int i = 0; i < 100; i++)
    {
        auto &p = v[i];
        cout << matrix2file[p.second] << ' ' << p.first << endl;
        f << matrix2file[p.second] << ' ' << p.first << endl;
    }
}