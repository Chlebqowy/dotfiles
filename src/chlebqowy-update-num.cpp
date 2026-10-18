#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <filesystem>
using namespace std;

int main(){
    double cmdOutput;
    if (filesystem::exists("/usr/bin/zypper")) { 
        char cmd[] = "zypper lu | grep '|' | wc -l"; // list updates and count lines. there's an extra line for table info to remove later
        
        array<char, 128> buffer;
        string result;

        unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
        while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
            result += buffer.data();
        }
        cmdOutput = stod(result);
        if (cmdOutput > 0) {
            cmdOutput-=1; // remove that line
        } 
    } else if (filesystem::exists("/usr/bin/pacman")) { 
        char cmd[] = "checkupdates | wc -l";

        array<char, 128> buffer;
        string result;

        unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
        while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
            result += buffer.data();
        }
        cmdOutput = stod(result);
        if (cmdOutput > 0) {
            cmdOutput-=1; // remove that line
        } 
    } else if (filesystem::exists("/usr/bin/apt")) {
        char cmd[] = "apt list --upgradable | wc -l";

        array<char, 128> buffer;
        string result;

        unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
        while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
            result += buffer.data();
        }
        cmdOutput = stod(result);
        if (cmdOutput > 0) {
            cmdOutput-=1; // remove that line
        } 
    } else { cout << "Unsupported package manager"; return 1; }
    double colorChanges[] = {20, 50, 200, 10000};
    string colors[] = {"#75ff98","#faa", "#f55", "#f00"};
    string color = "";
    int i = 0;
    while (color == "" && i < size(colorChanges)) {
        if (cmdOutput < colorChanges[i]) {
            color = colors[i];
        }
        i += 1;
    } 
    cout << "%{T2}%{F" << color << "}PKG %{T1}%{F-}" << cmdOutput;
}
