#include <iostream>
#include <array>
#include <cmath>
#include "parameter.hpp"
#include "gnuplot.hpp"

constexpr int INTV = 1;

void setFunc(std::array<std::array<double, N>, N>& u){
    double a = 0.5;
    double x, y;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; ++j){
            x = i * dx;
            y = j * dy;
            u[i][j] = std::exp( - 100 * ((x - a) * (x - a) + (y - a) * (y - a)));
        }
    }
}

using Array = std::array<std::array<double, N>, N>;

void nextStep(Array &u1, Array& u2, Array& u3){
    for(int i=1; i<N-1; ++i){
        for(int j=1; j<N-1; ++j){
            u3[i][j] = 2.0 * u2[i][j] - u1[i][j] + (dt * dt) / (dx * dx) * (u2[i-1][j] - 2.0 * u2[i][j] + u2[i+1][j])
                                                 + (dt * dt) / (dy * dy) * (u2[i][j-1] - 2.0 * u2[i][j] + u2[i][j+1]);
        }
    }
}

int main(){
    auto u1 = std::array<std::array<double, N>, N>{};
    auto u2 = std::array<std::array<double, N>, N>{};
    auto u3 = std::array<std::array<double, N>, N>{};

    for(int i=0; i<N; ++i){
        for(int j=0; j<N; ++j){
            u1[i][j] = 0.0;
            u2[i][j] = 0.0;
            u3[i][j] = 0.0;
        }
    }

    setFunc(u1);
    setFunc(u2);
    
    double t = 0.0;

    auto gp = mino2357::gnuplot();

    for(int i=0; t<tLimit; ++i){
        t += dt;
        nextStep(u1, u2 ,u3);
        if(i%INTV == 0){
            gp.print(u1);
        }

        for(int i=1; i<N-1; ++i){
            for(int j=1; j<N-1; ++j){
                u1[i][j] = u2[i][j];
                u2[i][j] = u3[i][j];
            }
        }
    }
}
