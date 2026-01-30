//
// Created by Kiefer on 2026-01-29.
//
#include <functional>
#include <roots.hpp>
#include <cmath>
#include <iostream>
#include <ostream>

bool bisection(std::function<double(double)> f,
               double a, double b,
               double *root) {
    bool found = false;
    double min = a;
    double max = b;
    if (f(min)*f(max) > 0) {
        return false;
    }
    if (f(min) > 0) {
    std::swap(min, max);}
    while (!found) {
        double mid = ((max + min)/2.0);
        if (fabs(max-min) < 2*1e-7 || fabs(f(mid)) < 1e-10) {
            found = true;
            *root = mid;
        }
        else if (f(mid) < 0.0) {
            min = mid;
        }
        else {
            max = mid;
        }
    }
return found;
}


bool regula_falsi(std::function<double(double)> f,
                  double a, double b,
                  double *root) {
    bool found = false;
    double c = a - (f(a)*(b - a))/(f(b) - f(a));
    if (f(a)*f(b) > 0) {
        return false;
    }
    int iters = 0;
    int maxiters = 1e6;
    while (iters <= maxiters && !found) {
        if (fabs(f(c)) < 1e-8) {
            found = true;
            *root = c;
        }
        else if (f(a)*f(c) < 0.0){
            b = c;
            c = a - (f(a)*(b - a))/(f(b) - f(a));
        }
        else {
            a = c;
            c = b - (f(b)*(b - a))/(f(b) - f(a));
        }
        iters += 1;
    }
    return found;
}


bool newton_raphson(std::function<double(double)> f,
                    std::function<double(double)> g,
                    double a, double b, double c,
                    double *root) {
    bool found = false;

    double xn = c;
    double xn_plus1 = a + 1; // declares xn_plus1 so that regardless of x0 value the if won't trigger on the first run
    int iters = 0;
    int maxiters = 1e6;
    while (!found && iters < maxiters) {
        if (fabs(g(xn)) < 1e-12) {
            return false;
        }
        if (fabs(xn - xn_plus1) < 1e-6 && fabs(f(xn))<1e-8) {
            found = true;
            *root = xn;
        }
        else {
            xn_plus1 = xn - f(xn)/g(xn);
            xn = xn_plus1;
        }
        iters += 1;
    }
    return found;
}



bool secant(std::function<double(double)> f,
            double a, double b, double c,
            double *root) {
    bool found = false;
    double xn_minus1 = c;
    double xn = xn_minus1 + 0.05*(b-a);
    if (fabs(f(xn)-f(xn_minus1)) < 1e-6) {
        xn = xn_minus1 + 0.1*(b-a);
    }
    double xn_plus1 = a + 1;
    int iters = 0;
    int maxiters = 1e6;
    while (!found && iters < maxiters) {
        if (xn_plus1 - xn < 1e-6 && fabs(f(xn))<1e-8) {
            found = true;
            *root = xn;
        }
        else {
            xn_plus1 = xn - f(xn)*(xn - xn_minus1)/(f(xn) - f(xn_minus1));
            xn_minus1 = xn;
            xn = xn_plus1;
        }
        iters += 1;
    }
return found;
}