#include <array>
#include <cerrno>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <nlohmann/json.hpp>

using namespace std;

char get_char(const string& display)
{
    return ' ';
}
int setup_socket()
{
// get socket path
    FILE* pipe = popen("sway --get-socketpath", "r");
    if (!pipe) return -1;

    char buffer[512];
    string path;
    if (fgets(buffer, sizeof(buffer), pipe))
        path = buffer;
    int status = pclose(pipe);
    if (status) {
        cout << status << endl; return -1;
    }

    while (!path.empty() && (path.back() == '\n' || path.back() == '\r'))
        { path.pop_back(); }
// connect
    int fd = socket(AF_UNIX, SOCK_STREAM, 0);
    sockaddr_un address{};
    address.sun_family = AF_UNIX;
    strncpy(address.sun_path, path.c_str(), sizeof(address.sun_path) - 1);

    connect(fd, reinterpret_cast<sockaddr*>(&address), sizeof address);
    return fd;
}
bool send(int i3_ipc)
{
    string message = "";
    uint32_t len = message.size();
    uint32_t type = 1; // get workspaces
    std::string buffer = "i3-ipc";
    buffer.append(reinterpret_cast<char*>(&len), 4);
    buffer.append(reinterpret_cast<char*>(&type), 4);
    buffer += message;

    const char* p = buffer.data();
    size_t left = buffer.size();
    while (left > 0) {
        ssize_t n = write(i3_ipc, p, left);
        if (n <= 0) { cout << "no write :(" << endl; perror("write"); return false; }
        p += n;
        left -= n;
    }
    return true;
}
string read_from_socket(int i3_ipc)
{
    char output_pre[14];
    char* output = output_pre;
    size_t bytes_to_read = 14;
    while (bytes_to_read > 0) {
        //cout << "hi" << endl;
        ssize_t read_data = read(i3_ipc, output, bytes_to_read);
        if (read_data <= 0) { cerr << "broken connection " << read_data << endl; perror("read"); return "e"; }
        output += read_data;
        bytes_to_read -= read_data;
    }

    //cout << "hi" << endl;

    uint32_t length;
    memcpy(&length, output_pre + 6, 4);           // bytes 6-9
    //cout << "json length: " << length << endl;

    string json(length, '\0');
    char* json_pointer = json.data();
    size_t bytes_left = length;
    while (bytes_left > 0) {
        ssize_t read_data2 = read(i3_ipc, json_pointer, bytes_left);
        if (read_data2 <= 0) { cerr << "broken something else" << read_data2 << endl; perror("read"); return "e"; }
        json_pointer += read_data2;
        bytes_left -= read_data2;
    }
    return json;
}
string format_line(
	char seperator, int name_lenght, 
	int lenght_per_workspace, bool active, 
	bool visible, string name, string display, 
	int num, string primary, string primary_subtle, 
	string secondary, string text_color, string gray,
	string special_seperator_0, string special_seperator_1,
	string white_text, bool is_last) 
{
    //PANGO
    //cout << "formatting" << endl;
    string correct_length_name;
    if (name.length() >= name_lenght)
    {
        correct_length_name = name.substr(0, name_lenght);
    } else {
        correct_length_name = name;
        for (int i = name.length(); i<name_lenght; i++) {
            correct_length_name += ' ';
        }
    }
    //cout << correct_length_name << endl;

    string colored_name;
    if (active) colored_name = "<span background='"+gray+"'>";
    else colored_name = "";
	//colored_name = "";
    colored_name += "<span weight='bold' foreground='" + primary + "'>";
    colored_name += special_seperator_1;
    colored_name += "</span>";
    colored_name += (' ');

    if (active) {
        colored_name += "<span weight='bold' foreground='" + white_text + "'>"+correct_length_name + "</span>";
    } else if (visible) { 
        colored_name += "<span weight='bold' foreground='" + primary + "'>" + to_string(num) + "</span> <span weight='normal' foreground='" + secondary + "'>" + correct_length_name.substr(3, correct_length_name.length()-1) + "</span>";  // If you have a different naming scheme, modify arg 1 in substr
    } else {
        colored_name += "<span weight='bold' foreground='" + primary + "'>" + to_string(num) + "</span> <span weight='normal' foreground='" + text_color + "'>" + correct_length_name.substr(3, correct_length_name.length()-1) + "</span>"; // also works with bold // If you have a different naming scheme, modify arg 1 in substr
    }

    char screen = get_char(display);
    colored_name += "<span weight='bold' foreground='" + white_text + "'>";
    colored_name += (' ');
    colored_name += screen;
    colored_name += "</span>";
    colored_name += (' ');
    if (is_last) colored_name += "<span weight='bold' foreground='" + secondary + "'>";
    else colored_name += "<span weight='bold' foreground='" + primary + "'>";
    colored_name += special_seperator_0;
    colored_name += "</span>";
    if (active) colored_name += "</span>";
    return colored_name;
}
int main()
{
// constants
    const int lenght = 150;
    const int workspace_amount = 5;
    const int lenght_per_workspace = lenght / workspace_amount;
    const char seperator = '\\';
    const string extra_seperator_0 = "";
    const string extra_seperator_1 = ""; 
    // has to be split up because the character is long
    const int name_lenght = lenght_per_workspace - 5; // space, window, space, seperator, space
    const float cd = 1.0; // seconds
    const float err_cd = 0.1; // also seconds

    const string primary   = "#ef8528";
    const string primary_subtle = "#efbc8f";
    const string text      = "#0A050F";
    const string secondary = "#2892ef";
    const string gray = "#6d6b60";
    const string white_text = "#e7e3e0";
    cout << "{\"version\":1}" << endl;
    cout << "[" << endl;
    bool first_update = true;

    if (name_lenght < 1) {cout << "NO SPACE FOR NAME"; return 0;}

    int i3_ipc = setup_socket();
    if (i3_ipc == -1) {cout << "failed to setup socket"; return 0;}
    //cout << i3_ipc << endl;
    while (true){
        if (send(i3_ipc)) int a;//cout << "success!" << endl;
        string json = read_from_socket(i3_ipc);
        if (json == "e") {sleep(err_cd); continue;}
        //cout << json << endl;

        string line = "";

        line += "<span weight='normal' foreground='" + primary + "'>";
        line += extra_seperator_0;
        line += "</span>";

        auto workspaces = nlohmann::json::parse(json);
        for (int i = 1; i<workspace_amount+1; i++) {
            const nlohmann::json* match = nullptr; // for some reason segfaults if defined without nullptr value
            for (auto& ws : workspaces) {
                if (ws["num"].get<int>() == i) {
                    match = &ws;
                    break;
                }
            }
            if (!match) {
                //cout << "no match" << endl;
                line += format_line(seperator,name_lenght,lenght_per_workspace,
                    false,false,
                    "","", i,
                    primary, primary_subtle, secondary, text,
                    gray, extra_seperator_0, extra_seperator_1,
                    white_text, i==workspace_amount);
            } else {
                //cout << "match" << endl;
                line += format_line(seperator, name_lenght, lenght_per_workspace,
                    match->at("focused").get<bool>(),
                    match->at("visible").get<bool>(),
                    match->at("name").get<string>(),
                    match->at("output").get<string>(),
                    i, primary, primary_subtle, secondary, text,
                    gray, extra_seperator_0, extra_seperator_1,
                    white_text, i==workspace_amount);
            }
        }
        line += "<span weight='normal' foreground='" + secondary + "' background='" + gray + "'>";
        line += extra_seperator_1;
        line += "</span>";
        line += "<span weight='bold' foreground='" + white_text + "' background='" + gray + "'>";
        line += " WORK "; // extra
        line += "</span>";
        line += "<span weight='normal' foreground='" + secondary + "' background='" + gray + "'>";
        line += extra_seperator_0;
        line += "</span>";
        line += "<span weight='normal' foreground='" + secondary + "'>";
        line += extra_seperator_1;
        line += "</span>";
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

// 


    
}
