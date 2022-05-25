#include "FileReader.h"
#include <fstream>
#include <streambuf>

FileReader::FileReader(const std::string& filename):input(std::ifstream(filename))
{}

std::optional<std::string> FileReader::read_word() {

    std::string word;

    if (!(input >> word)) {
        return std::nullopt;
    }

    return word;

}


