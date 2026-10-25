#include <array>
#include <cerrno>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <algorithm>

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <nlohmann/json.hpp>

using namespace std;
string parse_proc(string line, char unit_char_1, char start_char) 
{
	size_t start = line.find(start_char);
	size_t first_number = min(
		min(
			min(
				min(line.find('0', start), line.find('1', start)),
				min(line.find('2', start), line.find('3', start))
			),
			min(
				min(line.find('4', start), line.find('5', start)),
				min(line.find('6', start), line.find('7', start))
			)
		),
		min(line.find('8', start), line.find('9', start)));
		// scuffed af
	size_t numbers_end = line.find(unit_char_1, first_number) - 1;
	size_t number_amount = numbers_end - first_number;
	return line.substr(first_number, number_amount);
}

string get_ram()
{
	ifstream file("/proc/meminfo");
	string mem_total, mem_free, mem_avail;
	getline(file, mem_total);
	int total = stoi(parse_proc(mem_total, 'k', ' '));
	getline(file, mem_free);
	getline(file, mem_avail);
	int avail = stoi(parse_proc(mem_avail, 'k', ' '));
	int avail_percent = 100 - (avail*100)/total;
	return to_string(avail_percent);
}
string get_cpu()
{
	char cmd[] = "top -bn1 | grep \"Cpu\"";
	array<char, 128> buffer;
	string result;
	unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
	while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
	    result += buffer.data();
	}
	// correct line is 4th
	return to_string(100 - stoi(parse_proc(result, 'i', 'i')));	
}
string get_bat(string BAT)
{
	ifstream full("/sys/class/power_supply/" + BAT + "/charge_full");
	ifstream current("/sys/class/power_supply/" + BAT + "/charge_now");
	string full_str, current_str;
	int full_val, current_val; 
	getline(full, full_str); getline(current, current_str); 
	full_val = stoi(full_str); current_val = stoi(current_str);
	int percent_full = (current_val*100)/full_val;
	return to_string(percent_full);
	
}
string get_charging(string BAT)
{
	ifstream status("/sys/class/power_supply/" + BAT + "/status");
	string status_str;
	getline(status, status_str);
	return status_str;
}
int main()
{
// constants
    const int lenght = 150;
    const int base_unit_lenght = 10;
    const char seperator = '\\';
    const string extra_seperator_0 = "";
    const string extra_seperator_1 = ""; 
    const float cd = 1.0; // seconds
    const float err_cd = 0.1; // also seconds
    const string BAT = "BAT1";

    const string primary   = "#ef8528";
    const string primary_subtle = "#efbc8f";
    const string text      = "#0A050F";
    const string secondary = "#2892ef";
    const string gray = "#6d6b60";
    const string white_text = "#e7e3e0";
    cout << "{\"version\":1}" << endl;
    cout << "[" << endl;
    bool first_update = true;
	string line = "";
	cout << get_ram() << endl;
	cout << get_cpu() << endl;
	cout << get_bat(BAT) << endl;
	cout << get_charging(BAT) << endl;
    while (true){
        nlohmann::json block = {
            {"full_text", line},
            {"markup", "pango"},
            {"separator", false},
            {"separator_block_width", 0},
            {"min_width", 1920},
            {"align", "center"}
        };

        if (!first_update) cout << ",";
        cout << nlohmann::json::array({block}).dump() << endl;
        first_update = false;
        sleep(cd);
    }
}
