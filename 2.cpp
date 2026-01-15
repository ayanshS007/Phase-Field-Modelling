#include <bits/stdc++.h>
#include <fstream> // Required for file output

using namespace std;

void solveDiffusion(int nx, int total_timesteps, double D, double dt, double dx) {
    double r = (D * dt) / (dx * dx);

    if (r >= 0.5) {
        cout << "Warning: Stability condition r < 0.5 not met! r = " << r << endl;
    }

    vector<double> c(nx);
    vector<double> c_next(nx);

    for (int i = 0; i < nx; i++) {
        if (i >= nx/4 && i <= (3*nx)/4) c[i] = 1.0;
        else c[i] = 0.0;
    }

    for (int t = 0; t < total_timesteps; t++) {
        for (int i = 0; i < nx; i++) {
            int left = (i == 0) ? nx - 1 : i - 1;
            int right = (i == nx - 1) ? 0 : i + 1;
            c_next[i] = c[i] + r * (c[left] - 2.0 * c[i] + c[right]);
        }
        c = c_next;
    }

    // --- NEW: Export to CSV ---
    ofstream outFile("results.csv");
    outFile << "x,concentration\n"; // Header
    for (int i = 0; i < nx; i++) {
        outFile << i * dx << "," << c[i] << "\n";
    }
    outFile.close();
    cout << "Results saved to results.csv" << endl;
}

int main() {
    int nx = 100;
    int steps = 4000;
    double D = 1.0;
    double dt = 0.25; // Note: r = 0.25 here, which is stable
    double dx = 1.0;

    solveDiffusion(nx, steps, D, dt, dx);
    return 0;
}