#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

int main(){
    int weights[] = {8, 2, 1, 1};
    int sum = 0;
    for (int i=0; i<size(weights); i++) {
        sum+=weights[i];
    }
    double colorChanges[size(weights)] = {0};
    for (int i=0; i<size(weights); i++) {
        colorChanges[i] = static_cast<double>(weights[i]) / static_cast<double>(sum) * 100;
        if (i>0) {
            colorChanges[i] += colorChanges[i-1];
        }
    }
    for (int i=0; i<size(colorChanges); i++) {
        cout << colorChanges[i] << ", ";
    }
}
