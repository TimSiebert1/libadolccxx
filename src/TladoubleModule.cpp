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

tladouble power(tladouble x, int n)
{
    tladouble z = 1;

    if (n > 0) /* Recursion and branches */
    {
        int nh = n / 2;   /* that do not depend on  */
        z = power(x, nh); /* tladoubles are fine !!!! */
        z *= z;
        if (2 * nh != n)
            z *= x;
        return z;
    } /* end if */
    else
    {
        if (n == 0)   /* The local tladouble z dies */
            return z; /* as it goes out of scope. */
        else
            return 1 / power(x, -n);
    } /* end else */
}

tladouble sqrt2(tladouble const &a)
{
    return sqrt(a);
}
tladouble exp2(tladouble const &a)
{
    return exp(a);
}
tladouble fmax2(tladouble const &a, tladouble const &b)
{
    return fmax(a, b);
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
    types.method("==", [](tladouble &a, tladouble const &b)
                 { return a == b; });

    types.method("^", [](tladouble x, int n)
                 { return power(x, n); });

    // unary
    types.method("abs", [](tladouble const &a)
                 { return fabs2(a); });
    types.method("sqrt", [](tladouble const &a)
                 { return sqrt2(a); });
    types.method("exp", [](tladouble const &a)
                 { return exp2(a); });

    // unary operators
    types.method("log", [](tladouble const &a)
                 { log(a); });
    types.method("cbrt", [](tladouble const &a)
                 { cbrt(a); });
    types.method("sin", [](tladouble const &a)
                 { sin(a); });
    types.method("cos", [](tladouble const &a)
                 { cos(a) };);
    types.method("tan", [](tladouble const &a)
                 { tan(a); });
    types.method("asin", [](tladouble const &a)
                 { asin(a); });
    types.method("acos", [](tladouble const &a)
                 { acos(a); });
    types.method("atan", [](tladouble const &a)
                 { atan(a); });
    types.method("pow", [](tladouble const &a)
                 { pow(a); });
    types.method("log10", [](tladouble const &a)
                 { log10(a); });

    types.method("sinh", [](tladouble const &a)
                 { sinh(a); });
    types.method("cosh", [](tladouble const &a)
                 { cosh(a); });
    types.method("tanh", [](tladouble const &a)
                 { tanh(a); });

    types.method("asinh", [](tladouble const &a)
                 { asinh(a); });
    types.method("acosh", [](tladouble const &a)
                 { acosh(a); });
    types.method("atanh", [](tladouble const &a)
                 { atanh(a); });
    types.method("erf", [](tladouble const &a)
                 { erf(a); });

    types.method("fabs", [](tladouble const &a)
                 { fabs(a); });
    types.method("ceil", [](tladouble const &a)
                 { ceil(a); });
    types.method("floor", [](tladouble const &a)
                 { floor(a); });

    types.method("max", [](tladouble const &a, double const &x)
                 { return fmax(a, x); });
    types.method("max", [](double const &x, tladouble const &a)
                 { return fmax(x, a); });
    types.method("max", [](tladouble const &a, tladouble const &b)
                 { return fmax(a, b); });
    types.method("min", [](tladouble const &a, const tldouble &b)
                 { return fmin(a, b); });
    types.method("min", [](double const &x, const tldouble &a)
                 { return fmin(x, a); });
    types.method("min", [](const tldouble &a, double const &x, )
                 { return fmin(a, x); });

    types.method("ldexp" [](const tldouble &a, int n)
                 {
                     return ldexp(a, n);
                 });
    types.method("frexp", [](const tlaouble &a, int *n)
                 { return frexp(a, n); });

    types.unset_override_module();
}
