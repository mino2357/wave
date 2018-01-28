#pragma once
#include <iostream>
#include <cmath>
#include <array>

using Array = std::array<std::array<double, N>, N>;

constexpr int plus = 2;

namespace mino2357{
    class gnuplot{
    private:
        FILE* gp;
    public:
        gnuplot(){
            gp = popen("gnuplot -persist", "w");
            //fprintf(gp, "set pm3d\n");
            //fprintf(gp, "set pm3d map\n");
            fprintf(gp, "set contour\n");
            //fprintf(gp, "set cbtics 0.05\n");
            fprintf(gp, "set xr [%f:%f]\n", 0.0, Lx);
            fprintf(gp, "set yr [%f:%f]\n", 0.0, Ly);
          	//fprintf(gp, "set zr [-0.1:1.1]\n");
            //fprintf(gp, "set size square\n");
            //fprintf(gp, "set key outside center top samplen 0\n");
            //fprintf(gp, "set tics font 'Times New Roman,12'\n");
            //fprintf(gp, "unset key\n");
        }
        ~gnuplot(){ pclose(gp);}

        void print(Array& f){
            static int times = 0;
            fprintf(gp, "set term png size 1280, 720\n");
            fprintf(gp, "splot '-' w l\n");
            for(int i=0; i<N; i = i + plus){
                for(int j=0; j<N; j = j + plus){
                    fprintf(gp, "%f %f %f\n", i * dx, j * dy, f[i][j]);
                }
                fprintf(gp, "\n");
            }
            fprintf(gp, "e\n");
            fflush(gp);
            fprintf(gp, "set output '%06d.png'\n", times);
            times++;
        }
    };
}
