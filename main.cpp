#include "grepFunction.h"


int main(int argc, const char* argv[]) {

    std::string pattern;
    std::vector<std::string> files;
    char command = configuration(pattern, files, argc, argv);
    bool many_files = files.size() > 1;
    for (auto& file: files) {
        grep(file, pattern, many_files, command);
    }

    //Grep


    return 0;
}