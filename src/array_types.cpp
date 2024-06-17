#include <jlcxx/jlcxx.hpp>
#include <adolc/adolc.h>

JLCXX_MODULE julia_module_array_types(jlcxx::Module &types)
{

    types.method("alloc_vec_double", myalloc1);
    types.method("alloc_vec_short", [](int i)
                 { return new short[i]; });
    types.method("alloc_mat_short", [](int const rows, int const cols)
                 { short ** A = new short*[rows];
                    for(int i=0; i<rows; i++)
                    {
                        A[i] = new short[cols];
                    }
                    return A; });
    types.method("myalloc2", myalloc2);
    types.method("myalloc3", myalloc3);

    types.method("free_vec_double", myfree1);
    types.method("free_vec_sizet", [](size_t *v)
                 { delete[] v; });
    types.method("free_vec_short", [](short *i)
                 { delete[] i; });
    types.method("free_mat_short", [](short **A, int const rows)
                 {
                    for(int i=0; i<rows; i++)
                    {
                        delete [] A[i];
                    }
                    delete [] A; });
    types.method("myfree2", myfree2);
    types.method("myfree3", myfree3);

    // utils for accessing tensor, matrices or vectors
    types.method("getindex_tens", [](double ***A, const int &dim)
                 { return A[dim - 1]; });
    types.method("getindex_tens", [](double ***A, const int &dim, const int &row, const int &col)
                 { return A[dim - 1][row - 1][col - 1]; });
    types.method("setindex_tens", [](double ***A, const double val, const int &dim, const int &row, const int &col)
                 { A[dim - 1][row - 1][col - 1] = val; });
    types.method("getindex_mat", [](double **A, const int &row, const int &col)
                 { return A[row - 1][col - 1]; });
    types.method("setindex_mat", [](double **A, const double val, const int &row, const int &col)
                 { A[row - 1][col - 1] = val; });
    types.method("getindex_vec", [](const double *A, const int &row)
                 { return A[row - 1]; });
    types.method("setindex_vec", [](double *A, const double val, const int &row)
                 { A[row - 1] = val; });

    types.method("setindex_vec", [](short *A, const short &val, const int &row)
                 { A[row - 1] = val; });
    types.method("getindex_vec", [](const short *A, const int &row)
                 { return A[row - 1]; });
    types.method("setindex_vec", [](size_t *A, const short &val, const int &row)
                 { A[row - 1] = val; });
    types.method("getindex_vec", [](size_t *A, const int &row)
                 { return A[row - 1]; });
}
