#pragma once

constexpr int N = 103;
constexpr double Lx = 1.0;
constexpr double Ly = 1.0;
constexpr double dx = Lx / static_cast<double>(N - 3);
constexpr double dy = Ly / static_cast<double>(N - 3);
constexpr double dt = 0.001;
constexpr double tLimit = 100;
