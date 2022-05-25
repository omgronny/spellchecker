#ifndef LAB1_FILEREADER_H
#define LAB1_FILEREADER_H

#include <fstream>
#include <iostream>
#include <optional>

class FileReader {
private:
    std::ifstream input;
public:

    FileReader(const std::string&);
    ~FileReader() = default;

    std::optional<std::string> read_word();

};


#endif //LAB1_FILEREADER_H
