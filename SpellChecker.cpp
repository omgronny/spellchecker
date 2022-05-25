#include "SpellChecker.h"
#include "FileReader.h"
#include "Indexer.h"
#include "Stemmer.h"

static void add_count_or_init(cds::container::FeldmanHashMap<cds::gc::HP, std::string, size_t, map_traits>& ngram,
                              const std::string& word,
                              size_t count_of_word) {

    if (auto gp = ngram.get(word); gp) {
        gp->second += count_of_word;
    } else {
        ngram.insert(word, count_of_word);
    }

}

SpellChecker::SpellChecker(size_t n, bool n_or_count) : n(n), n_or_count(n_or_count) {}

void SpellChecker::spell_check(const std::string& filename) {

    init_map(filename);
    init_ngrams();
    init_map_indices();

}

void SpellChecker::init_map(const std::string& filename) {

    FileReader reader(filename);

    while (true) {

        std::optional<std::string> optional_word = reader.read_word();

        if (!optional_word) {
            break;
        }

        std::string word = stemmer::add_dots_and_clean(optional_word.value());

        if (auto gp = cds_words_count_index.get(word); gp) {
            gp->second.first++;
        } else {
            cds_words_count_index.insert(word, std::make_pair(1, 0));
        }

    }

}

void SpellChecker::init_ngrams() {

    #pragma omp parallel for schedule(static, 500)
    for (const auto& [word, count_index] : cds_words_count_index) {

        std::vector<std::string> bgrams = stemmer::get_bigrams(word);
        std::vector<std::string> tgrams = stemmer::get_trigrams(word);

        for (const auto& bgram : bgrams) {
            add_count_or_init(cds_bigrams, bgram, count_index.first);
        }

        for (const auto& tgram : tgrams) {
            add_count_or_init(cds_threegrams, tgram, count_index.first);
        }

    }
}

void SpellChecker::init_map_indices() {

    #pragma omp parallel for schedule(static, 500)
    for (auto& [word, count_index]  : cds_words_count_index) {
        count_index.second = indexer::get_index(word, cds_bigrams, cds_threegrams);
    }

}

void SpellChecker::print_map() {

    for (const auto& [word, count_index] : cds_words_count_index) {
        std::cout << word << " <" << count_index.first << " " << count_index.second << ">" << std::endl;
    }

}

void SpellChecker::print_result_if_count() {

    std::priority_queue<std::pair<double, std::string>> queue_for_print;

    for (const auto& [word, count_index] : cds_words_count_index) {
        queue_for_print.push({count_index.second, word});
    }

    for (size_t i = 0; i < n; ++i) {
        auto [index, word] = queue_for_print.top();
        std::cout << word << "    <" << index << ">" << std::endl;
        queue_for_print.pop();
    }

}

void SpellChecker::print_result_if_n() {
    for (const auto& [word, count_index] : cds_words_count_index) {
        if (count_index.second > n) {
            std::cout << word << "    <" << count_index.first << " " << count_index.second << ">" << std::endl;
        }
    }
}

void SpellChecker::print_result() {

    if (n_or_count) {
        print_result_if_n();
    } else {
        print_result_if_count();
    }

}






