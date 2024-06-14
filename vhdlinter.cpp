#include <iostream>
#include <fstream>
#include <regex>
#include <string>

using namespace std;

void check_comments(const string &file_path) {
    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Could not open the file: " << file_path << endl;
        return;
    }

    string line;
    regex signal_pattern(R"(\b(signal|port)\b)");
    regex comment_pattern(R"(--)");
    int line_number = 0;

    while (getline(file, line)) {
        line_number++;
        if (regex_search(line, signal_pattern) && !regex_search(line, comment_pattern)) {
            cout << "Missing comment on line " << line_number << ": " << line << endl;
        }
    }

    file.close();
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <vhdl_file>" << endl;
        return EXIT_FAILURE;
    }

    check_comments(argv[1]);
    cout << "SUCCESS!!" << endl;
    return EXIT_SUCCESS;
}
