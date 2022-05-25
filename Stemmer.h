#ifndef INC_01_SPELLCHECKER_STEMMER_H
#define INC_01_SPELLCHECKER_STEMMER_H

#include <iostream>
#include <vector>
#include <map>

namespace stemmer {

    namespace {

        std::string clean(const std::string &word) {

            std::string res;
            res.resize(word.size());
            size_t idx = 0;

            for (const char ch: word) {
                if (std::isalpha(ch) && !std::isspace(ch)) {
                    res[idx++] = std::tolower(ch);
                }
            }
            res[idx] = 0;

            return res;
        }

        std::string add_dots_and_clean(const std::string &word) {

            std::string res = ".";
            res += clean(word);
            res += ".";

            return res;
        }

    }

    std::vector<std::string> get_bigrams(const std::string& word) {

        std::vector<std::string> res(word.size() - 1);

        for (size_t i = 1; i < word.size(); ++i) {
            res[i - 1] = word.substr(i - 1, 2);
        }

        return res;
    }

    std::vector<std::string> get_trigrams(const std::string& word) {
        std::vector<std::string> res(word.size() - 2);

        for (size_t i = 1; i < word.size() - 1; ++i) {
            res[i - 1] = word.substr(i - 1, 3);
        }

        return res;
    }

};


#endif //INC_01_SPELLCHECKER_STEMMER_H
