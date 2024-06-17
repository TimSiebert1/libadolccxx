#include <jlcxx/jlcxx.hpp>
#include <adolc/adolc.h>
#include <iostream>

adouble add(adouble const &a, adouble const &b)
{
  return a + b;
}

adouble add_right(adouble const &a, double const v)
{
  return a + v;
}

adouble add_left(double const v, adouble const &a)
{
  return v + a;
}

adouble diff(adouble const &a, adouble const &b)
{
  return a - b;
}

adouble diff_right(adouble const &a, double const v)
{
  return a - v;
}

adouble diff_left(double const v, adouble const &a)
{
  return v - a;
}
adouble diff_unary(adouble const &a)
{
  return (-1) * a;
}

adouble mult(adouble const &a, adouble const &b)
{
  return a * b;
}

adouble mult_right(adouble const &a, double const v)
{
  return a * v;
}

adouble mult_left(double const v, adouble const &a)
{
  return v * a;
}

adouble div2(adouble const &a, adouble const &b)
{
  return a / b;
}

adouble div_right(adouble const &a, double const v)
{
  return a / v;
}

adouble div_left(double const v, adouble const &a)
{
  return v / a;
}

void assign(adouble &x, double val)
{
  x <<= val;
}

double dassign(adouble &x, double &val)
{
  x >>= val;
  return val;
}

adouble max_left(adouble const &a, double const &x)
{
  return fmax(a, x);
}
adouble max_right(double const &x, adouble const &a)
{
  return fmax(x, a);
}
adouble max2(adouble const &a, adouble const &b)
{
  return fmax(a, b);
}

adouble min_right(double const &x, const adouble &a)
{
  return fmin(x, a);
}
adouble min_left(const adouble &a, double const &x)
{
  return fmin(a, x);
}

adouble min2(adouble const &a, const adouble &b)
{
  return fmin(a, b);
}

adouble fabs2(adouble const &a)
{
  return fabs(a);
}

adouble sqrt2(adouble const &a)
{
  return sqrt(a);
}

adouble exp2(adouble const &a)
{
  return exp(a);
}

adouble log2(adouble const &a)
{
  return log(a);
}

adouble sin2(adouble const &a)
{
  return sin(a);
}
adouble cos2(adouble const &a)
{
  return cos(a);
}
adouble tan2(adouble const &a)
{
  return tan(a);
}

adouble asin2(adouble const &a)
{
  return asin2(a);
}
adouble acos2(adouble const &a)
{
  return acos(a);
}
adouble atan2(adouble const &a)
{
  return atan(a);
}

adouble log10_2(adouble const &a)
{
  return log10(a);
}

adouble sinh2(adouble const &a)
{
  return sinh(a);
}
adouble cosh2(adouble const &a)
{
  return cosh(a);
}
adouble tanh2(adouble const &a)
{
  return tanh(a);
}

adouble asinh2(adouble const &a)
{
  return asinh(a);
}
adouble acosh2(adouble const &a)
{
  return acosh(a);
}
adouble atanh2(adouble const &a)
{
  return atanh(a);
}
adouble erf2(adouble const &a)
{
  return erf(a);
}

adouble cbrt2(adouble const &a)
{
  return cbrt(a);
}

adouble ceil2(adouble const &a)
{
  return ceil(a);
}
adouble floor2(adouble const &a)
{
  return floor(a);
}

adouble ldexp2(const adouble &a, int n)
{
  return ldexp(a, n);
}
adouble frexp2(const adouble &a, int *n)
{
  return frexp(a, n);
}

JLCXX_MODULE Tbadouble_module(jlcxx::Module &types)
{
  types.add_type<adouble>("TbadoubleCxx", jlcxx::julia_type("AbstractFloat", "Base"))
      .constructor<double>();
  types.method("getValue", [](adouble &a)
               { return a.getValue(); });

  // tape utils
  types.method("trace_on", [](int tag)
               { return trace_on(tag); });
  types.method("trace_on", [](int tag, int keep)
               { return trace_on(tag, keep); });
  types.method("trace_off", []()
               { trace_off(); });
  types.method("trace_off", trace_off);
  types.method("num_independents", [](int tag)
               { size_t stats[STAT_SIZE];
                 tapestats(tag, stats);
                 return (int) stats[NUM_INDEPENDENTS]; });
  types.method("num_dependents", [](int tag)
               { size_t stats[STAT_SIZE];
                 tapestats(tag, stats);
                 return (int) stats[NUM_DEPENDENTS]; });

  // easy to use drivers

  types.method("gradient", [](int tag, int n, double *x, double *g)
               { return gradient(tag, n, x, g); });
  types.method("jacobian", jacobian);
  types.method("hessian", hessian);
  types.method("vec_jac", vec_jac);
  types.method("jac_vec", jac_vec);
  types.method("hess_vec", hess_vec);
  types.method("hess_mat", hess_mat);
  types.method("lagra_hess_vec", lagra_hess_vec);
  types.method("jac_solv", jac_solv);

  types.method("ad_forward", [](short tag, int m, int n,
                                int d,
                                int keep,
                                double **X,
                                double **Y)
               { forward(tag,
                         m,
                         n,
                         d,
                         keep,
                         X,
                         Y); });
  types.method("ad_reverse", [](short tag,
                                int m,
                                int n,
                                int d,
                                double *u,
                                double **Z)
               { reverse(tag, m, n, d, u, Z); });

  types.method("zos_forward", zos_forward);
  types.method("fos_forward", fos_forward);
  types.method("hos_forward", hos_forward);
  types.method("hov_wk_forward", hov_wk_forward);

  types.method("fov_forward", fov_forward);
  types.method("hov_forward", hov_forward);

  types.method("fos_reverse", fos_reverse);
  types.method("hos_reverse", hos_reverse);

  types.method("fov_reverse", fov_reverse);
  types.method("hov_reverse", hov_reverse);

  // easy to use higher order drivers
  types.method("tensor_address", tensor_address);
  types.method("tensor_eval", tensor_eval);

  // pointwise-smooth functions
  types.method("enableMinMaxUsingAbs", enableMinMaxUsingAbs);
  types.method("get_num_switches", get_num_switches);
  types.method("zos_pl_forward", zos_pl_forward);
  types.method("fos_pl_forward", fos_pl_forward);
  types.method("fov_pl_forward", fov_pl_forward);
  types.method("abs_normal", abs_normal);

  //--------------------

  // basic arithmetic operations
  types.set_override_module(jl_base_module);

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

  types.method("<<", assign);
  types.method(">>", dassign);

  types.method("<", [](double const &val, adouble const &a)
               { return val < a; });
  types.method("<", [](adouble const &a, double const &val)
               { return a < val; });
  types.method("<", [](adouble const &a, adouble const &b)
               { return a < b; });

  types.method(">", [](double const &val, adouble const &a)
               { return val > a; });
  types.method(">", [](adouble const &a, double const &val)
               { return a > val; });
  types.method(">", [](adouble const &a, adouble const &b)
               { return a > b; });

  types.method(">=", [](adouble const &a, double const &val)
               { return a >= val; });
  types.method(">=", [](double const &val, adouble const &a)
               { return val >= a; });
  types.method(">=", [](adouble const &a, adouble const &b)
               { return a >= b; });

  types.method("<=", [](adouble const &a, double const &val)
               { return a <= val; });
  types.method("<=", [](double const &val, adouble const &a)
               { return val <= a; });
  types.method("<=", [](adouble const &a, adouble const &b)
               { return a <= b; });

  types.method("==", [](adouble const &a, double const &val)
               { return a == val; });
  types.method("==", [](double const &val, adouble const &a)
               { return val == a; });
  types.method("==", [](adouble const &a, adouble const &b)
               { return a == b; });

  /*
  types.method("^", [](adouble x, int n)
               { return pow(x, n); });
  */
  types.method("max", [](adouble const &a, double const &x)
               { return max_left(a, x); });
  types.method("max", [](double const &x, adouble const &a)
               { return max_right(x, a); });
  types.method("max", [](adouble const &a, adouble const &b)
               { return max2(a, b); });
  types.method("min", [](const adouble &a, double const &x)
               { return min_left(a, x); });
  types.method("min", [](double const &x, const adouble &a)
               { return min_right(x, a); });
  types.method("min", [](adouble const &a, const adouble &b)
               { return min2(a, b); });

  types.method("abs", [](adouble const &a)
               { return fabs2(a); });
  types.method("sqrt", [](adouble const &a)
               { return sqrt2(a); });
  types.method("exp", [](adouble const &a)
               { return exp2(a); });
  types.method("log", [](adouble const &a)
               { return log2(a); });
  types.method("sin", [](adouble const &a)
               { return sin2(a); });
  types.method("cos", [](adouble const &a)
               { return cos2(a); });
  types.method("tan", [](adouble const &a)
               { return tan2(a); });

  types.method("asin", [](adouble const &a)
               { return asin2(a); });
  types.method("acos", [](adouble const &a)
               { return acos2(a); });
  types.method("atan", [](adouble const &a)
               { return atan2(a); });
  types.method("log10", [](adouble const &a)
               { return log10_2(a); });

  types.method("sinh", [](adouble const &a)
               { return sinh2(a); });
  types.method("cosh", [](adouble const &a)
               { return cosh2(a); });
  types.method("tanh", [](adouble const &a)
               { return tanh2(a); });

  types.method("asinh", [](adouble const &a)
               { return asinh2(a); });
  types.method("acosh", [](adouble const &a)
               { return acosh2(a); });
  types.method("atanh", [](adouble const &a)
               { return atanh2(a); });

  types.method("ceil", [](adouble const &a)
               { return ceil2(a); });
  types.method("floor", [](adouble const &a)
               { return floor2(a); });

  types.method("ldexp", [](const adouble &a, int n)
               { return ldexp2(a, n); });
  types.method("frexp", [](const adouble &a, int *n)
               { return frexp2(a, n); });

  types.unset_override_module();

  types.method("cbrt", [](adouble const &a)
               { return cbrt2(a); });
  types.method("erf", [](adouble const &a)
               { return erf2(a); });
  types.unset_override_module();
}
