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

//    cds::container::FeldmanHashMap<cds::gc::HP, std::string, int32_t, map_traits> test_map;
//
//    test_map.insert("1", 2);
//
//    if (auto gp = test_map.get("1"); gp) {
//        std::cout << "found" << std::endl;
//    } else {
//        std::cout << "not found" << std::endl;
//    }
//
//    if (test_map.find("1", [](std::pair<const std::string&, int32_t>) { std::cout << "found" << std::endl; }) ) {
//        std::cout << "found" << std::endl;
//    } else {
//        std::cout << "not found" << std::endl;
//    }
//
//    for (auto [a1, a2] : test_map) {
//        std::cout << a1 << " " << a2 << std::endl;
//    }

    cds::Terminate();
    return 0;

}


//int main(int argc, char** argv)
//{
//    // Initialize libcds
//    cds::Initialize();
//
//    // Initialize Hazard Pointer singleton
//    cds::gc::HP hpGC;
//    // If main thread uses lock-free containers
//    // the main thread should be attached to libcds infrastructure
//    cds::threading::Manager::attachThread();
//    // Now you can use HP-based containers in the main thread
//    //...
//    cds::container::FeldmanHashMap<cds::gc::HP, int32_t, int32_t> test_map;
//
//    //auto k = test_map.get(1);
//    //std::cout << k->second << std::endl;
//
////    std::cout << test_map.contains(1) << std::endl;
////
////    std::cout << test_map.insert(1, 2) << std::endl;
////    std::cout << test_map.insert(1, 2) << std::endl;
////
////    std::cout << test_map.contains(1) << std::endl;
//
//    // Terminate libcds
//    cds::Terminate();
//}