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

using namespace std;

enum PackageManager
{
    zypper,
    pacman,
    apt,
    dnf,
    unsupported
};
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
const float cd = 1.0;     // seconds
const int bonus_cd = 30;  // multiples of cd
const float err_cd = 0.1; // also seconds
const string BAT = "BAT1";
const bool direction = 1; // 0 left 1 right
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
PackageManager package_manager;
string pkg = "";
int pkg_i = 16;
const int pkg_cd = 16;
int cpu_i = 60;
const int cpu_cd = 60;
string cpu = "";
const float scale = 0.9;
const float x = 1920;
const int part_x = (int)(x / scale) / 2;
int get_max_bright()
{
    char bright_capacity_cmd[] = "brightnessctl m";
    array<char, 128> buffer;
    string bright_capacity;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(bright_capacity_cmd, "r"),
                                             pclose);
    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) !=
           nullptr)
    {
        bright_capacity += buffer.data();
    }
    // cout << bright_capacity << endl;
    return stoi(bright_capacity);
}
const int max_bright = get_max_bright();

string parse_proc(string line, char unit_char_1, char start_char)
{
    size_t start = line.find(start_char);
    size_t first_number =
        min(min(min(min(line.find('0', start), line.find('1', start)),
                    min(line.find('2', start), line.find('3', start))),
                min(min(line.find('4', start), line.find('5', start)),
                    min(line.find('6', start), line.find('7', start)))),
            min(line.find('8', start), line.find('9', start)));
    // scuffed af
    size_t numbers_end = line.find(unit_char_1, first_number) - 1;
    size_t number_amount = numbers_end - first_number;
    return line.substr(first_number, number_amount);
}
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
        int total = stoi(parse_proc(mem_total, 'k', ' '));
        getline(file, mem_free);
        getline(file, mem_avail);
        int avail = stoi(parse_proc(mem_avail, 'k', ' '));
        int avail_percent = 100 - (avail * 100) / total;
        return to_string(avail_percent);
    }
    catch (int e)
    {
        return "ERR!" + to_string(e);
    }
}
string get_cpu()
{
    try
    {
        if (cpu_i == cpu_cd)
        {
            char cmd[] = "top -bn1 | grep \"Cpu\"";
            array<char, 128> buffer;
            string result;
            unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
            while (fgets(buffer.data(), static_cast<int>(buffer.size()),
                         pipe.get()) != nullptr)
            {
                result += buffer.data();
            }
            // correct line is 4th
            cpu = to_string(100 - stoi(parse_proc(result, 'i', 'i')));
        }
        else
            cpu_i++;
        return cpu;
        // TODO stop using top
    }
    catch (int e)
    {
        return "ERR!" + to_string(e);
    }
}
string get_bat(string BAT)
{
    try
    {
        ifstream full("/sys/class/power_supply/" + BAT + "/charge_full");
        ifstream current("/sys/class/power_supply/" + BAT + "/charge_now");
        string full_str, current_str;
        int full_val, current_val;
        getline(full, full_str);
        getline(current, current_str);
        full_val = stoi(full_str);
        current_val = stoi(current_str);
        int percent_full = (current_val * 100) / full_val;
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
string get_brightness()
{
    try
    {
        char cmd[] = "brightnessctl g";
        array<char, 128> buffer;
        string result;
        unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
        while (fgets(buffer.data(), static_cast<int>(buffer.size()),
                     pipe.get()) != nullptr)
        {
            result += buffer.data();
        }
        int result_val = stoi(result);
        return to_string((result_val * 100) / max_bright);
    }
    catch (int e)
    {
        return "ERR!" + to_string(e);
    }
}
string get_gpu()
{
    try
    {
        return "0";
        if (!filesystem::exists("/usr/bin/nvidia-smi"))
        {
            return "ERR!U";
        }
        char cmd[] = "nvidia-smi --query-gpu=utilization.gpu "
                     "--format=csv,noheader,nounits";
        array<char, 128> buffer;
        string result;
        unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
        while (fgets(buffer.data(), static_cast<int>(buffer.size()),
                     pipe.get()) != nullptr)
        {
            // cout << buffer.data() << endl;
            result += buffer.data();
        }
        return remove_escape(result);
    }
    catch (int e)
    {
        return "ERR!" + to_string(e);
    }
}
string get_pkg(PackageManager package_manager)
{
    char cmd[64];
    if (pkg_i == pkg_cd)
    {
        switch (package_manager)
        {
        case zypper:
            strcpy(cmd, "zypper lu | grep '|' | wc -l");
            break;
        case pacman:
            strcpy(cmd, "checkupdates | wc -l");
            break;
        case apt:
            strcpy(cmd, "apt list --upgradable | wc -l");
            break;
        case dnf:
            strcpy(cmd, "dnf check-update | grep '.' | grep ':' | wc -l");
            break;
        default:
            return "ERR!U";
        }

        array<char, 128> buffer;
        string result;

        unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
        while (fgets(buffer.data(), static_cast<int>(buffer.size()),
                     pipe.get()) != nullptr)
        {
            result += buffer.data();
        }
        if (package_manager == zypper)
            result[size(result) - 1] = result[size(result) - 1] - 1;
        pkg = remove_escape(result);
    }
    else
    {
        pkg_i += 1;
    }
    return pkg;
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
    char cmd[] = "date +%H:%M:%S";
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
string gen_l_bar()
{
    string line;
    line += clock_format(get_date(), true);
    // cout << "date" << endl;
    line += full_seperator_secondary;
    line +=
        standard_format("BAT", get_bat(BAT), true, get_charging(BAT), false, 3);
    line += full_seperator;
    line += standard_format("PKG", get_pkg(package_manager), false, irrelevant,
                            false, 4);
    line += full_seperator;
    line +=
        standard_format("BRI", get_brightness(), true, irrelevant, false, 3);
    return line;
}
string gen_r_bar()
{
    string line;
    // cout << "CPU" << endl;
    line += standard_format("CPU", get_cpu(), true, irrelevant, false, 3);
    line += full_seperator;
    // cout << "RAM" << endl;
    line += standard_format("RAM", get_ram(), true, irrelevant, false, 3);
    line += full_seperator;
    // cout << "GPU" << endl;
    line += standard_format("GPU", get_gpu(), true, irrelevant, false, 3);
    line += full_seperator_secondary;
    // cout << "HOUR" << endl;
    line += clock_format(get_hour(), true);
    // cout << "line" << endl;
    return line;
}
int main()
{
    string align;
    // if (direction) align = "right";
    // else align = "left";
    if (filesystem::exists("/usr/bin/zypper"))
        package_manager = zypper;
    else if (filesystem::exists("/usr/bin/pacman"))
        package_manager = pacman;
    else if (filesystem::exists("/usr/bin/apt"))
        package_manager = apt;
    else if (filesystem::exists("/usr/bin/dnf"))
        package_manager = dnf;
    else
        package_manager = unsupported;

    cout << "{\"version\":1}" << endl;
    cout << "[" << endl;
    bool first_update = true;
    // string line;
    string line_l, line_r;
    int count = bonus_cd - 1;
    while (true)
    {
        count++;
        if (count >= bonus_cd)
        {
            // cout << "lbar" << endl;
            line_l = gen_l_bar();
            count = 0;
        }
        // cout << "rbar" << endl;
        line_r = gen_r_bar();

        nlohmann::json block_l = {
            {"full_text", line_l}, {"markup", "pango"},
            {"separator", false},  {"separator_block_width", 0},
            {"min_width", part_x}, {"align", "left"},
        };
        nlohmann::json block_r = {
            {"full_text", line_r}, {"markup", "pango"},
            {"separator", false},  {"separator_block_width", 0},
            {"min_width", part_x}, {"align", "right"},
        };

        if (!first_update) cout << ",";
        // cout << "block" << endl;
        // cout << line_r << endl;
        // cout << line_l << endl;
        // cout << nlohmann::json::array({block}).dump() << endl;
        // cout << nlohmann::json::array({block_l}).dump() << endl;
        cout << nlohmann::json::array({block_l, block_r}).dump() << endl;
        first_update = false;
        if (!direction)
            sleep(bonus_cd);
        else
            sleep(cd);
    }
}
