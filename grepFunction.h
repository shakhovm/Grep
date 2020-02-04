//
// Created by user on 04.02.2020.
//

#ifndef GREP_GREPFUNCTION_H
#define GREP_GREPFUNCTION_H
#include <iostream>
#include <vector>
#include <fstream>
#include <regex>


static void do_action(bool action, bool many_files, const std::string& filename,
                      const std::regex& reg, const std::string& line, std::smatch m);

void grep(const std::string& filename, const std::string& pattern, bool many_files=false, char command='r');

char configuration(std::string& pattern, std::vector<std::string>& files,
                   int argc, const char* argv[]);


void do_action(bool action, bool many_files, const std::string& filename,
               const std::regex& reg, const std::string& line, std::smatch m) {
    if (regex_search(line, m, reg) == action)
    {
        if (many_files)
            std::cout << filename << ":";
        std::cout << line << std::endl;
    }
}

void grep(const std::string& filename, const std::string& pattern, bool many_files, char command)
{
    std::ifstream file(filename);
    if (!file)
    {
        std::cout << "grep: " << filename << " : No such file!";
        return;
    }
    std::string line;

    std::smatch m;
    switch(command)
    {
        case 'v':
            while(getline(file, line))
                do_action(false, many_files, filename, std::regex(pattern), line, m);
            break;

        case 'r':
            while(getline(file, line))
                do_action(true, many_files, filename, std::regex(pattern), line, m);
            break;

        case 'i':

            while(getline(file, line))
                do_action(true, many_files, filename,
                          std::regex(pattern,
                                  std::regex_constants::ECMAScript | std::regex_constants::icase), line, m);
            break;

        default:
            std::cout << "Wrong command!" << std::endl;
            break;
    }
    file.close();
}

char configuration(std::string& pattern, std::vector<std::string>& files,
                   int argc, const char* argv[]) {
    char command = 'r';
    bool pattern_checked = false;
    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] == '-') {
            command = argv[i][1];
        }
        else if (!pattern_checked){
            pattern = argv[i];
            pattern_checked = true;
        }
        else {
            files.emplace_back(argv[i]);
        }
    }
    return command;
}

#endif //GREP_GREPFUNCTION_H
