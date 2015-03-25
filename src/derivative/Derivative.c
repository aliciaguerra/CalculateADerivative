typedef double (*TFunc)(double);

// general approximation of derivative using central difference
double diff(TFunc f, double x, double dx=1e-10)
{
  double dy = f(x+dx)-f(x-dx);
  return dy/(2.*dx);
}

// more or less arbitrary function from double to double:
double f(double x)
{
   return x*x;
}

// and here is how you get the derivative of f at specified location
double fp = diff(f, 5.);
