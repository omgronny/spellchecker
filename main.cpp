#include "SpellChecker.h"
#include "ArgumentsParser.h"

#include <cds/init.h>
#include <cds/gc/hp.h>


int main(int argc, char** argv) {

    cds::Initialize();
    cds::gc::HP hpGC;
    cds::threading::Manager::attachThread();

    if (argc < 2) {
        return -1;
    }

    std::pair<size_t, bool> args = {10, true};
    if (argc == 3) {
        std::string key(argv[2]);
        args = ArgumentsParser::parse_input(key);
    }

    SpellChecker sc = SpellChecker(args.first, args.second);
    sc.spell_check(argv[1]);
    sc.print_result();

    cds::Terminate();
    return 0;

}

