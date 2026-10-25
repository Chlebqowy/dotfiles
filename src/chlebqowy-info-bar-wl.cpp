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

enum PackageManager {zypper, pacman, apt, dnf, unsupported};
enum Battery {charging, discharging, irrelevant};

const int base_unit_lenght = 10;
const int lenght = 150;
const char seperator = '\\';
const string extra_seperator_0 = "";
const string extra_seperator_1 = ""; 
const float cd = 1.0; // seconds
const float bonus_cd = 30.0; // seconds
const float err_cd = 0.1; // also seconds
const string BAT = "BAT1";
const bool direction = 1; // 0 left 1 right
const string primary   = "#ef8528";
const string primary_subtle = "#efbc8f";
const string text      = "#0A050F";
const string secondary = "#2892ef";
const string gray = "#6d6b60";
const string white_text = "#e7e3e0";
const string full_seperator = "<span foreground='" + primary + "'> " + seperator + " </span>";
const string full_seperator_secondary = "<span foreground='" + secondary + "'> " + seperator + " </span>";
PackageManager package_manager;
const float scale = 0.9;
const float x = 1920;
const int part_x = (int) (x/scale)/2;

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
	try {
	ifstream file("/proc/meminfo");
	string mem_total, mem_free, mem_avail;
	getline(file, mem_total);
	int total = stoi(parse_proc(mem_total, 'k', ' '));
	getline(file, mem_free);
	getline(file, mem_avail);
	int avail = stoi(parse_proc(mem_avail, 'k', ' '));
	int avail_percent = 100 - (avail*100)/total;
	return to_string(avail_percent);
	} catch(int e) {
		return "ERR!"+ to_string(e);
	}
}
string get_cpu()
{
	try {
	char cmd[] = "top -bn1 | grep \"Cpu\"";
	array<char, 128> buffer;
	string result;
	unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
	while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
	    result += buffer.data();
	}
	// correct line is 4th
	return to_string(100 - stoi(parse_proc(result, 'i', 'i')));	
	} catch(int e) {
		return "ERR!"+ to_string(e);
	}
}
string get_bat(string BAT)
{
	try {
	ifstream full("/sys/class/power_supply/" + BAT + "/charge_full");
	ifstream current("/sys/class/power_supply/" + BAT + "/charge_now");
	string full_str, current_str;
	int full_val, current_val; 
	getline(full, full_str); getline(current, current_str); 
	full_val = stoi(full_str); current_val = stoi(current_str);
	int percent_full = (current_val*100)/full_val;
	return to_string(percent_full);
	} catch(int e) {
		return "ERR!"+ to_string(e);
	}
}
Battery get_charging(string BAT)
{
	try {
	ifstream status("/sys/class/power_supply/" + BAT + "/status");
	string status_str;
	getline(status, status_str);
	if (status_str == "Charging") return charging;
	return discharging;
	} catch(int e) {
		return irrelevant;
	}
}
string get_gpu(){
	try {
	if (!filesystem::exists("/usr/bin/nvidia-smi")) { return "ERR!U"; }
	char cmd[] = "nvidia-smi --query-gpu=utilization.gpu --format=csv,noheader,nounits";
	array<char, 128> buffer;
	string result;
	unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
	while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
	    result += buffer.data();
	}
	return result;
	} catch(int e) {
		return "ERR!"+ to_string(e);
	}
}
string get_pkg(PackageManager package_manager){
	char cmd[64];
	switch(package_manager) 
	{
		case zypper:
			strcpy(cmd, "zypper lu | grep '|' | wc -l"); break;
		case pacman:
			strcpy(cmd, "checkupdates | wc -l"); break;
		case apt:
			strcpy(cmd, "apt list --upgradable | wc -l"); break;
		case dnf:
			strcpy(cmd, "dnf check-update | grep '.' | grep ':' | wc -l"); break;
		default:
			return "ERR!U";
	}

	array<char, 128> buffer;
	string result;

	unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
	while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
	    result += buffer.data();
	}
	if (package_manager == zypper) result[size(result)-1] = result[size(result)-1] - 1;
	return result;
}
string get_date(){
	char cmd[] = "date +%a\\ %Y/%m/%d";
	array<char, 128> buffer;
	string result;

	unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
	while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
	    result += buffer.data();
	}
	result = result.substr(0, size(result)-1);
	result[0] -= 32;
	result[1] -= 32;
	result[2] -= 32;
	return result;
}
string get_hour(){
	char cmd[] = "date +%H:%M:%S";
	array<char, 128> buffer;
	string result;

	unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
	while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
	    result += buffer.data();
	}
	result = result.substr(0, size(result)-1);
	return result;
}
string standard_format(string name, string value, bool is_percent, Battery bat, bool is_secondary, int value_len)
{
	string module_txt;
	if (is_secondary) module_txt += "<span foreground='" + secondary + "'>";
	else module_txt += "<span foreground='" + primary + "'>";
	module_txt += extra_seperator_0;
	module_txt += "</span>";
	module_txt += "<span background='" + gray + "'>";
	if (is_secondary) module_txt += "<span foreground='" + secondary + "'>";
	else module_txt += "<span foreground='" + primary + "'>";
	module_txt += extra_seperator_1;
	module_txt += "</span>";
	module_txt += "<span weight='bold' foreground='" + white_text + "'>";
	module_txt += name;
	if (bat == charging) module_txt += "+";
	else if (bat == discharging) module_txt += " ";
	module_txt += "</span>";
	if (is_secondary) module_txt += "<span foreground='" + secondary + "'>";
	else module_txt += "<span foreground='" + primary + "'>";
	module_txt += extra_seperator_0;
	module_txt += "</span>";
	module_txt += "</span>";
	if (is_secondary) module_txt += "<span foreground='" + secondary + "'>";
	else module_txt += "<span foreground='" + primary + "'>";
	module_txt += extra_seperator_1;
	module_txt += "</span>";
	module_txt += " ";
	module_txt += "<span foreground='" + text + "'>";
	if (size(value) >= value_len)
	{
		for (int i = value_len; i<size(value); i++)
		{
			module_txt += " ";
		}
	} else {
		value = value.substr(0, value_len);
	}
	module_txt += value;
	if (is_percent) module_txt += "%";
	module_txt += " ";
	module_txt += "</span>";
	return module_txt;
	// maybe try extra seperator name\\ value extra seperator
}
string clock_format(string value, bool is_secondary){
	string module_txt;
	if (is_secondary) module_txt += "<span foreground='" + secondary + "'>";
	else module_txt += "<span foreground='" + primary + "'>";
	module_txt += extra_seperator_0;
	module_txt += "</span>";
	module_txt += "<span background='" + gray + "'>";
	if (is_secondary) module_txt += "<span foreground='" + secondary + "'>";
	else module_txt += "<span foreground='" + primary + "'>";
	module_txt += extra_seperator_1;
	module_txt += "</span>";
	module_txt += "<span weight='bold' foreground='" + white_text + "'>";
	module_txt += value;
	module_txt += "</span>";
	if (is_secondary) module_txt += "<span foreground='" + secondary + "'>";
	else module_txt += "<span foreground='" + primary + "'>";
	module_txt += extra_seperator_0;
	module_txt += "</span>";
	module_txt += "</span>";
	if (is_secondary) module_txt += "<span foreground='" + secondary + "'>";
	else module_txt += "<span foreground='" + primary + "'>";
	module_txt += extra_seperator_1;
	module_txt += "</span>";
	return module_txt;
}
string gen_l_bar()
{
	string line;
	line += clock_format(get_date(), true);
	line += full_seperator_secondary;
	line += standard_format("BAT", get_bat(BAT), true, get_charging(BAT), false, 3);
	line += full_seperator;
	line += standard_format("PKG", get_pkg(package_manager), false, irrelevant, false, 4);
	return line;
}
string gen_r_bar()
{
	string line;
	line += standard_format("CPU", get_cpu(), true, irrelevant, false, 3);
	line += full_seperator;
	line += standard_format("RAM", get_ram(), true, irrelevant, false, 3);
	line += full_seperator;
	line += standard_format("GPU", get_gpu(), true, irrelevant, false, 3);
	line += full_seperator_secondary;
	line += clock_format(get_hour(), true);
	return line;
}
int main()
{
	string align;
	//if (direction) align = "right";
	//else align = "left";
	if (filesystem::exists("/usr/bin/zypper")) package_manager = zypper;
	else if (filesystem::exists("/usr/bin/pacman")) package_manager = pacman;
	else if (filesystem::exists("/usr/bin/apt")) package_manager = apt;
	else if (filesystem::exists("/usr/bin/dnf")) package_manager = dnf;
	else package_manager = unsupported;

    cout << "{\"version\":1}" << endl;
    cout << "[" << endl;
    bool first_update = true;
	//string line;
	string line_l, line_r;
    while (true){
    	line_l = gen_l_bar();
    	line_r = gen_r_bar();

        nlohmann::json block_l = {
           {"full_text", line_l},
           {"markup", "pango"},
           {"separator", false},
           {"separator_block_width", 0},
           {"min_width", part_x},
           {"align", "left"},
        };
        nlohmann::json block_r = {
           {"full_text", line_r},
           {"markup", "pango"},
           {"separator", false},
           {"separator_block_width", 0},
           {"min_width", part_x},
           {"align", "right"},
        };

        if (!first_update) cout << ",";
        //cout << nlohmann::json::array({block}).dump() << endl;
        cout << nlohmann::json::array({block_l, block_r}).dump() << endl;
        first_update = false;
        if (!direction) sleep(bonus_cd);
        else sleep(cd);
    }
}
