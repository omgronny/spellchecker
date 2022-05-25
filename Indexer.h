#ifndef INC_01_SPELLCHECKER_INDEXER_H
#define INC_01_SPELLCHECKER_INDEXER_H

#include <iostream>
#include <vector>
#include <map>
#include <cmath>

#include <cds/container/impl/feldman_hashmap.h>
#include <cds/gc/hp.h>

namespace indexer {

    double get_index(const std::string& word,
                     cds::container::FeldmanHashMap<cds::gc::HP, std::string, size_t, map_traits> & bigrams,
                     cds::container::FeldmanHashMap<cds::gc::HP, std::string, size_t, map_traits> & trigrams) {

        double res = 0;

        for (size_t i = 1; i < word.size() - 1; ++i) {

            std::string tgram = word.substr(i - 1, 3);
            std::string first_bigram = word.substr(i - 1, 2);
            std::string second_bigram = word.substr(i, 2);

            double nab = bigrams.get(first_bigram)->second;
            double nbc = bigrams.get(second_bigram)->second;
            double nabc = trigrams.get(tgram)->second;

            nab = nab > 1 ? std::log(nab - 1) : -10;
            nbc = nbc > 1 ? std::log(nbc - 1) : -10;
            nabc = nabc > 1 ? std::log(nabc - 1) : -10;

            double small_index = 0.5 * (nab + nbc) - nabc;
            res += small_index * small_index;

        }

        res /= (word.size() - 2);
        res = std::pow(res, 0.5);

        return res;

    }

};


#endif //INC_01_SPELLCHECKER_INDEXER_H
