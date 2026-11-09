#include <algorithm>
#include <array>
#include <cerrno>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include <nlohmann/json.hpp>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

//lighter alternative to the info bar with less modules
// TODO implement some optimisations from here to full bars
// particularly removing direction
using namespace std;

enum Battery
{
    charging,
    discharging,
    irrelevant
};

const int base_unit_lenght = 10;
const int lenght = 150;
const char seperator = '\\';
const string extra_seperator_0 = "";
const string extra_seperator_1 = "";
const float cd = 10.0;     // seconds
const string BAT = "BAT1";
const string primary = "#ef8528";
const string primary_subtle = "#efbc8f";
const string text = "#0A050F";
const string secondary = "#2892ef";
const string gray = "#6d6b60";
const string white_text = "#e7e3e0";
const string full_seperator =
    "<span foreground='" + primary + "'> " + seperator + " </span>";
const string full_seperator_secondary =
    "<span foreground='" + secondary + "'> " + seperator + " </span>";
string parse_proc(string line, char unit_char_1)
{
    size_t first_number = min(min(min(min(line.find('0'), line.find('1')),
                                      min(line.find('2'), line.find('3'))),
                                  min(min(line.find('4'), line.find('5')),
                                      min(line.find('6'), line.find('7')))),
                              min(line.find('8'), line.find('9')));
    // scuffed af
    size_t numbers_end = line.find(unit_char_1, first_number) - 1;
    size_t number_amount = numbers_end - first_number;
    return line.substr(first_number, number_amount);
}
string remove_escape(string line)
{
    size_t first_number = 0;
    size_t numbers_end =
        min(line.find('\x0A', first_number), line.find('\x09', first_number));
    size_t number_amount = numbers_end - first_number;
    // cout << number_amount << endl;
    return line.substr(first_number, number_amount);
}
string get_ram()
{
    try
    {
        ifstream file("/proc/meminfo");
        string mem_total, mem_free, mem_avail;
        getline(file, mem_total);
        int total = stoi(parse_proc(mem_total, 'k'));
        getline(file, mem_free);
        getline(file, mem_avail);
        int avail = stoi(parse_proc(mem_avail, 'k'));
        int avail_percent = 100 - (avail * 100) / total;
        return to_string(avail_percent);
    }
    catch (int e)
    {
        return "ERR!" + to_string(e);
    }
}
int get_max_bat(string BAT){
	try
	{
        ifstream full("/sys/class/power_supply/" + BAT + "/charge_full");
        string full_str;
        int full_val;
        getline(full, full_str);
        full_val = stoi(full_str);
        return full_val;
    }
    catch (int e)
    {
        return 0; //cause div by 0 and error for get_bar
    }
}
const int max_bat = get_max_bat(BAT);
string get_bat(string BAT)
{
    try
    {
        ifstream current("/sys/class/power_supply/" + BAT + "/charge_now");
        string current_str;
        int current_val;
        getline(current, current_str);
        current_val = stoi(current_str);
        int percent_full = (current_val * 100) / max_bat;
        return to_string(percent_full);
    }
    catch (int e)
    {
        return "ERR!" + to_string(e);
    }
}
Battery get_charging(string BAT)
{
    try
    {
        ifstream status("/sys/class/power_supply/" + BAT + "/status");
        string status_str;
        getline(status, status_str);
        if (status_str == "Charging") return charging;
        return discharging;
    }
    catch (int e)
    {
        return irrelevant;
    }
}
string get_date()
{
    char cmd[] = "date +%a\\ %Y/%m/%d";
    array<char, 128> buffer;
    string result;

    unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) !=
           nullptr)
    {
        result += buffer.data();
    }
    // cout << result << endl;
    result = result.substr(0, size(result) - 1);
    if (result.substr(0, 2) == "ś")
    {
        result[1] = 's';
        result = result.substr(1, size(result) - 1);
    }
    if (result.substr(2, 2) == "ą")
    {
        result[1] = 'a';
        result = result.substr(2, size(result) - 1);
    }
    if (result[0] >= 'a' && result[0] <= 'z')
    {
        result[0] -= 32;
    }
    else
    {
        result[1] = '?';
        result = result.substr(1, size(result) - 1);
    }
    if (result[1] >= 'a' && result[1] <= 'z')
    {
        result[1] -= 32;
    }
    else
    {
        result[1] = '?';
        result = result.substr(0, 1) + result.substr(2, size(result) - 2);
    }
    if (result[2] >= 'a' && result[2] <= 'z')
    {
        result[2] -= 32;
    }
    else
    {
        result[1] = '?';
        result = result.substr(0, 2) + result.substr(3, size(result) - 3);
    }
    return result;
}
string get_hour()
{
    char cmd[] = "date +%H:%M";
    array<char, 128> buffer;
    string result;

    unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) !=
           nullptr)
    {
        result += buffer.data();
    }
    result = result.substr(0, size(result) - 1);
    return result;
}
string standard_format(string name, string value, bool is_percent, Battery bat,
                       bool is_secondary, int value_len)
{
    string module_txt;
    if (is_secondary)
        module_txt += "<span foreground='" + secondary + "'>";
    else
        module_txt += "<span foreground='" + primary + "'>";
    module_txt += extra_seperator_0;
    module_txt += "</span>";
    module_txt += "<span background='" + gray + "'>";
    if (is_secondary)
        module_txt += "<span foreground='" + secondary + "'>";
    else
        module_txt += "<span foreground='" + primary + "'>";
    module_txt += extra_seperator_1;
    module_txt += "</span>";
    module_txt += "<span weight='bold' foreground='" + white_text + "'>";
    module_txt += name;
    if (bat == charging)
        module_txt += "+";
    else if (bat == discharging)
        module_txt += " ";
    module_txt += "</span>";
    if (is_secondary)
        module_txt += "<span foreground='" + secondary + "'>";
    else
        module_txt += "<span foreground='" + primary + "'>";
    module_txt += extra_seperator_0;
    module_txt += "</span>";
    module_txt += "</span>";
    if (is_secondary)
        module_txt += "<span foreground='" + secondary + "'>";
    else
        module_txt += "<span foreground='" + primary + "'>";
    module_txt += extra_seperator_1;
    module_txt += "</span>";
    module_txt += " ";
    module_txt += "<span foreground='" + text + "'>";
    if (size(value) >= value_len)
    {
        for (int i = value_len; i < size(value); i++)
        {
            module_txt += " ";
        }
    }
    else
    {
        // cout << value << endl;
        value = value.substr(0, value_len);
        // cout << value << endl;
    }
    module_txt += value;
    if (is_percent) module_txt += "%";
    module_txt += " ";
    module_txt += "</span>";
    return module_txt;
    // maybe try extra seperator name\\ value extra seperator
}
string clock_format(string value, bool is_secondary)
{
    string module_txt;
    if (is_secondary)
        module_txt += "<span foreground='" + secondary + "'>";
    else
        module_txt += "<span foreground='" + primary + "'>";
    module_txt += extra_seperator_0;
    module_txt += "</span>";
    module_txt += "<span background='" + gray + "'>";
    if (is_secondary)
        module_txt += "<span foreground='" + secondary + "'>";
    else
        module_txt += "<span foreground='" + primary + "'>";
    module_txt += extra_seperator_1;
    module_txt += "</span>";
    module_txt += "<span weight='bold' foreground='" + white_text + "'>";
    module_txt += value;
    module_txt += "</span>";
    if (is_secondary)
        module_txt += "<span foreground='" + secondary + "'>";
    else
        module_txt += "<span foreground='" + primary + "'>";
    module_txt += extra_seperator_0;
    module_txt += "</span>";
    module_txt += "</span>";
    if (is_secondary)
        module_txt += "<span foreground='" + secondary + "'>";
    else
        module_txt += "<span foreground='" + primary + "'>";
    module_txt += extra_seperator_1;
    module_txt += "</span>";
    // cout << "clock format" << endl;
    return module_txt;
}
string gen_bar()
{
    string line;
    line += full_seperator_secondary;
    line += clock_format(get_date(), true);
    line += full_seperator_secondary;
    line +=
        standard_format("BAT", get_bat(BAT), true, get_charging(BAT), false, 3);
    line += standard_format("RAM", get_ram(), true, irrelevant, false, 3);
    line += full_seperator_secondary;
    line += clock_format(get_hour(), true);
    line += full_seperator_secondary;
    return line;
}
int main()
{
    cout << "{\"version\":1}" << endl;
    cout << "[" << endl;
    bool first_update = true;
    while (true)
    {
        nlohmann::json block = {
            {"full_text", gen_bar()}, {"markup", "pango"},
            {"separator", false},  {"separator_block_width", 0},
            {"min_width", lenght}, {"align", "center"},
        };
        if (!first_update) cout << ",";
        // cout << nlohmann::json::array({block}).dump() << endl;
        first_update = false;
        sleep(cd);
    }
}
