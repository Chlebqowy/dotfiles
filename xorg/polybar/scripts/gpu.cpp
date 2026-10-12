#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
using namespace std;

int main(){
    char cmd[] = "nvidia-smi --query-gpu=utilization.gpu --format=csv,noheader,nounits";
    array<char, 128> buffer;
    string result;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    double cmdOutput = stod(result);
    double colorChanges[] = {66.6667, 83.3333, 91.6667, 100};
    string colors[] = {"#75ff98","#faa", "#f55", "#f00"};
    string color = "";
    int i = 0;
    while (color == "" && i < size(colorChanges)) {
        if (cmdOutput < colorChanges[i]) {
            color = colors[i];
        }
        i += 1;
    } 
    cout << "%{T2}%{F" << color << "}GPU %{T1}%{F-}" << cmdOutput;
}
