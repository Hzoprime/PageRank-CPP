//
// Created by 何博 on 2020/11/24.
//

#include "block_stripe.hpp"

double norm2(vector<vector<double>> &old_v, vector<vector<double>> &new_v)
{
    double total = 0.0;
    for (size_t i = 0; i < old_v.size(); i++)
    {
        for (size_t j = 0; j < old_v.front().size(); j++)
        {
            total += sqrt(pow(old_v[i][j] - new_v[i][j], 2));
        }
    }
    return sqrt(total);
}

int block_strip(double teleport_parameter = 0.85)
{
    unordered_map<int, int> file2matrix, matrix2file;
    get_node_map(file2matrix, matrix2file);

    const unsigned int block_size = 100;
    const unsigned int node_number = file2matrix.size();
    const unsigned int block_number = node_number / block_size + 1;

    vector<pair<int, int>> sparse_matrix;
    vector<int> out_degree(node_number, 0);

    get_sparse_matrix(file2matrix, sparse_matrix, out_degree);
    vector<vector<set<int>>> block(block_number, vector<set<int>>(block_size));

    for (auto &i : sparse_matrix)
    {
        block[i.second / block_size][i.second % block_size].insert(i.first);
    }


    vector<vector<double>>
        old_v(block_number, vector<double>(block_size, 1.0 / node_number)),
        new_v(block_number, vector<double>(block_size, 1.0 / node_number)),
        base(block_number, vector<double>(block_size, 0));
    cout << "begin" << endl;

    for (size_t i = 0; i < block_number; i++)
    {
        for (size_t j = 0; j < block_size; j++)
        {
            if (i * block_size + j >= node_number)
            {
                base[i][j] = old_v[i][j] = new_v[i][j] = 0;
                assert(new_v[i][j] < epsilon);
            }
        }
    }

    double current_delta = 1.0;
    double s = 0;
    while (current_delta >= epsilon)
    {
        old_v = new_v;
        new_v = base;
        for (int i = 0; i < block_number; i++)
        {
            for (int j = 0; j < block_size; j++)
            {
                for (auto it = block[i][j].begin(); it != block[i][j].end(); it++)
                {
                    new_v[i][j] += teleport_parameter * old_v[(*it) / block_size][(*it) % block_size] * ((1.0) / out_degree[*it]);
                }
            }
        }
        s = accumulate(new_v.begin(), new_v.end(), 0.0, [](const double &last_result, vector<double> &next_v) {
            return last_result + accumulate(next_v.begin(), next_v.end(), 0.0);
        });
        s = (1.0 - s) / node_number;

        for (int i = 0; i < block_number; i++)
        {
            for (int j = 0; j < block_size; j++)
            {
                if (i * block_size + j >= node_number)
                {
                    break;
                }
                new_v[i][j] += s;
            }
        }
        current_delta = norm2(old_v, new_v);
        cout << current_delta << endl;
    }
    write_result(new_v, matrix2file, teleport_parameter);
    cout << "in block strip" << endl;
    return 0;
}
