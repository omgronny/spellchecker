//
// Created by glins on 10.04.2022.
//

#ifndef LAB1_SPELLCHECKER_H
#define LAB1_SPELLCHECKER_H

#include <iostream>
#include <map>
#include <vector>
#include <queue>

#include <cds/container/impl/feldman_hashmap.h>
#include <cds/gc/hp.h>

struct map_traits: public cds::container::feldman_hashmap::traits
{
    typedef std::hash<std::string> hash;
};

class SpellChecker {
private:
    const size_t n;
    const bool n_or_count;

    std::map<std::string, std::pair<size_t, double>> words_count_index;
    std::map<std::string, size_t> bigrams;
    std::map<std::string, size_t> threegrams;

    cds::container::FeldmanHashMap<cds::gc::HP, std::string, std::pair<size_t, double>, map_traits> cds_words_count_index;
    cds::container::FeldmanHashMap<cds::gc::HP, std::string, size_t, map_traits> cds_bigrams;
    cds::container::FeldmanHashMap<cds::gc::HP, std::string, size_t, map_traits> cds_threegrams;

    void init_map(const std::string& filename);

    void init_ngrams();
    void init_map_indices();

    void print_result_if_count();
    void print_result_if_n();

public:
    SpellChecker(size_t, bool);
    ~SpellChecker() = default;

    void spell_check(const std::string&);
    void print_map();
    void print_result();
};


#endif //LAB1_SPELLCHECKER_H
