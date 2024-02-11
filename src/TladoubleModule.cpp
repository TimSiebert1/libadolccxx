#include <jlcxx/jlcxx.hpp>
#include <iostream>
#include <adolc/adtl.h>
typedef adtl::adouble tladouble;

tladouble add(tladouble const &a, tladouble const &b)
{
    return a + b;
}

tladouble add_right(tladouble const &a, double const v)
{
    return a + v;
}

tladouble add_left(double const v, tladouble const &a)
{
    return v + a;
}

tladouble diff(tladouble const &a, tladouble const &b)
{
    return a - b;
}

tladouble diff_right(tladouble const &a, double const v)
{
    return a - v;
}

tladouble diff_left(double const v, tladouble const &a)
{
    return v - a;
}
tladouble diff_unary(tladouble const &a)
{
    return (-1) * a;
}

tladouble mult(tladouble const &a, tladouble const &b)
{
    return a * b;
}

tladouble mult_right(tladouble const &a, double const v)
{
    return a * v;
}

tladouble mult_left(double const v, tladouble const &a)
{
    return v * a;
}

tladouble div2(tladouble const &a, tladouble const &b)
{
    return a / b;
}

tladouble div_right(tladouble const &a, double const v)
{
    return a / v;
}

tladouble div_left(double const v, tladouble const &a)
{
    return v / a;
}

tladouble fabs2(tladouble const &a)
{
    return fabs(a);
}

tladouble sqrt2(tladouble const &a)
{
    return sqrt(a);
}
tladouble exp2(tladouble const &a)
{
    return exp(a);
}

tladouble log2(tladouble const &a)
{
    return log(a);
}

tladouble sin2(tladouble const &a)
{
    return sin(a);
}
tladouble cos2(tladouble const &a)
{
    return cos(a);
}
tladouble tan2(tladouble const &a)
{
    return tan(a);
}
tladouble asin2(tladouble const &a)
{
    return asin2(a);
}
tladouble acos2(tladouble const &a)
{
    return acos(a);
}
tladouble atan2(tladouble const &a)
{
    return atan(a);
}
tladouble pow2(tladouble const &a, double const & x)
{
    return pow(a, x);
}
tladouble log10_2(tladouble const &a)
{
    return log10(a);
}

tladouble sinh2(tladouble const &a)
{
    return sinh(a);
}
tladouble cosh2(tladouble const &a)
{
    return cosh(a);
}
tladouble tanh2(tladouble const &a)
{
    return tanh(a);
}

tladouble asinh2(tladouble const &a)
{
    return asinh(a);
}
tladouble acosh2(tladouble const &a)
{
    return acosh(a);
}
tladouble atanh2(tladouble const &a)
{
    return atanh(a);
}
tladouble erf2(tladouble const &a)
{
    return erf(a);
}

tladouble ceil2(tladouble const &a)
{
    return ceil(a);
}
tladouble floor2(tladouble const &a)
{
    return floor(a);
}

tladouble max_left(tladouble const &a, double const &x)
{
    return fmax(a, x);
}
tladouble max_right(double const &x, tladouble const &a)
{
    return fmax(x, a);
}
tladouble max2(tladouble const &a, tladouble const &b)
{
    return fmax(a, b);
}
tladouble min2(tladouble const &a, const tladouble &b)
{
    return fmin(a, b);
}
tladouble min_right(double const &x, const tladouble &a)
{
    return fmin(x, a);
}
tladouble min_left(const tladouble &a, double const &x)
{
    return fmin(a, x);
}

tladouble ldexp2(const tladouble &a, int n)
{
    return ldexp(a, n);
}
tladouble frexp2(const tladouble &a, int *n)
{
    return frexp(a, n);
}

tladouble cbrt2(tladouble const &a)
{
  return cbrt(a);
}


tladouble *tl_init_for_gradient(double const *data, int const &n)
{
    adtl::setNumDir(n);
    tladouble *x = new tladouble[n];

    for (int i = 0; i < n; ++i) // Initialize x_i
    {
        x[i] = data[i];
        for (int j = 0; j < n; ++j)
            if (i == j)
                x[i].setADValue(j, 1);
    }
    return x;
}


JLCXX_MODULE Tladouble_module(jlcxx::Module &types)
{
    types.add_type<tladouble>("TladoubleCxx", jlcxx::julia_type("AbstractFloat", "Base"))
        .constructor<double>();
    types.method("tl_init_for_gradient", [](double const *data, int const &n)
                 { return tl_init_for_gradient(data, n); });
    types.method("getValue", [](tladouble &a)
                 { return a.getValue(); });
    types.method("getADValue", [](tladouble const &a)
                 { return *a.getADValue(); });
    types.method("getADValue", [](tladouble const &a, int const &i)
                 { return a.getADValue(i - 1); });
    types.method("setADValue", [](tladouble &a, double const val)
                 { return a.setADValue(&val); });

    types.method("getindex_tl", [](tladouble *A, const int &row)
                 { return A[row - 1]; });

    // basic arithmetic operations
    types.set_override_module(jl_base_module);

    // binary
    types.method("+", add);
    types.method("+", add_right);
    types.method("+", add_left);

    types.method("-", diff);
    types.method("-", diff_right);
    types.method("-", diff_left);
    types.method("-", diff_unary);

    types.method("*", mult);
    types.method("*", mult_left);
    types.method("*", mult_right);

    types.method("/", div2);
    types.method("/", div_left);
    types.method("/", div_right);

    types.method("<", [](double const &val, tladouble const &a)
                 { return val < a; });
    types.method("<", [](tladouble const &a, double const &val)
                 { return a < val; });
    types.method("<", [](tladouble const &a, tladouble const &b)
                 { return a < b; });

    types.method(">", [](double const &val, tladouble const &a)
                 { return val > a; });
    types.method(">", [](tladouble const &a, double const &val)
                 { return a > val; });
    types.method(">", [](tladouble const &a, tladouble const &b)
                 { return a > b; });

    types.method(">=", [](tladouble const &a, double const &val)
                 { return a >= val; });
    types.method(">=", [](double const &val, tladouble const &a)
                 { return val >= a; });
    types.method(">=", [](tladouble const &a, tladouble const &b)
                 { return a >= b; });

    types.method("<=", [](tladouble const &a, double const &val)
                 { return a <= val; });
    types.method("<=", [](double const &val, tladouble const &a)
                 { return val <= a; });
    types.method("<=", [](tladouble const &a, tladouble const &b)
                 { return a <= b; });

    types.method("==", [](tladouble const &a, double const &val)
                 { return a == val; });
    types.method("==", [](double const &val, tladouble const &a)
                 { return val == a; });
    types.method("==", [](tladouble const &a, tladouble const &b)
                 { return a == b; });

    types.method("^", [](tladouble const & a, double const& x)
                 { return pow(a, x); });

    // unary
    types.method("abs", [](tladouble const &a)
                 { return fabs2(a); });
    types.method("sqrt", [](tladouble const &a)
                 { return sqrt2(a); });
    types.method("exp", [](tladouble const &a)
                 { return exp2(a); });
    types.method("log", [](tladouble const &a)
                 { return log2(a); });
    types.method("sin", [](tladouble const &a)
                 { return sin2(a); });
    types.method("cos", [](tladouble const &a)
                 { return cos2(a); });
    types.method("tan", [](tladouble const &a)
                 { return tan2(a); });
    types.method("asin", [](tladouble const &a)
                 { return asin2(a); });
    types.method("acos", [](tladouble const &a)
                 { return acos2(a); });
    types.method("atan", [](tladouble const &a)
                 { return atan2(a); });
    types.method("log10", [](tladouble const &a)
                 { return log10_2(a); });

    types.method("sinh", [](tladouble const &a)
                 { return sinh2(a); });
    types.method("cosh", [](tladouble const &a)
                 { return cosh2(a); });
    types.method("tanh", [](tladouble const &a)
                 { return tanh2(a); });

    types.method("asinh", [](tladouble const &a)
                 { return asinh2(a); });
    types.method("acosh", [](tladouble const &a)
                 { return acosh2(a); });
    types.method("atanh", [](tladouble const &a)
                 { return atanh2(a); });


    types.method("ceil", [](tladouble const &a)
                 { return ceil2(a); });
    types.method("floor", [](tladouble const &a)
                 { return floor2(a); });

    types.method("max", [](tladouble const &a, double const &x)
                 { return max_left(a, x); });
    types.method("max", [](double const &x, tladouble const &a)
                 { return max_right(x, a); });
    types.method("max", [](tladouble const &a, tladouble const &b)
                 { return max2(a, b); });
    types.method("min", [](const tladouble &a, double const &x)
                 { return min_left(a, x); });
    types.method("min", [](double const &x, const tladouble &a)
                 { return min_right(x, a); });
    types.method("min", [](tladouble const &a, const tladouble &b)
                 { return min2(a, b); });

    types.method("ldexp", [](const tladouble &a, int n)
                 {
                     return ldexp2(a, n);
                 });
    types.method("frexp", [](const tladouble &a, int *n)
                 { return frexp2(a, n); });

    types.unset_override_module();


    types.method("erf", [](tladouble const &a)
                 { return erf2(a); });
    types.method("cbrt", [](tladouble const &a)
               { return cbrt2(a); });
}
int main()
{
  std::cout << "hi" << std::endl;
}