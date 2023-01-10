#include "my_hash_table.hpp"
#include <gtest/gtest.h>

TEST(HashTable, Insert) {
//    HashTable ht;
//    ht.Insert("lol");
//    ht.Insert("anal");
//    ht.Insert("kek");
//    ht.Insert("lmao");
//    ht.Insert("loh");

    HashTableLinearProbe htlp;
    htlp.Insert("lol");
    htlp.Insert("kek");
    htlp.Insert("lmao");
    htlp.Insert("kuril");
    htlp.Insert("manda");
    htlp.Insert("hui");
    htlp.Insert("hui");
//    htlp.Insert("fj;d");
//    htlp.Insert("fsd;a");
//    htlp.Insert("fppdss");
//    htlp.Insert("gdgdgd");
//    htlp.Insert("fdsoa[[");
    std::cout << htlp << std::endl;

}

TEST(HashTable, Find) {
    HashTableLinearProbe htlp;
    htlp.Insert("lol");
    htlp.Insert("kek");
    htlp.Insert("lmao");
    htlp.Insert("kuril");
    htlp.Insert("manda");
    htlp.Insert("hui");
    htlp.Insert("hui");

    std::cout << htlp.Find("hui") << std::endl;
    std::cout << htlp.Find("lmao") << std::endl;
    std::cout << htlp.Find("manda") << std::endl;
    std::cout << htlp.Find("kek") << std::endl;
    std::cout << htlp.Find("fsfsgsghf") << std::endl;
}

TEST(HashTable, Remove) {
    HashTableLinearProbe htlp;
    htlp.Insert("lol");
    htlp.Insert("kek");
    htlp.Insert("lmao");
    htlp.Insert("kuril");
    htlp.Insert("manda");
    htlp.Insert("hui");
    htlp.Insert("hui");

    std::cout << htlp << std::endl;

    htlp.Remove("kek");

    std::cout << htlp << std::endl;

}

//TEST(HashTable, Rehash) {
//    HashTableLinearProbe htlp;
//    htlp.Insert("lol");
//    htlp.Insert("kek");
//    htlp.Insert("lmao");
//    htlp.Insert("kuril");
//    htlp.Insert("manda");
//    htlp.Insert("hui");
//    htlp.Insert("hui");
//
//    htlp.Remove("kek");
//    htlp.Remove("manda");
//    htlp.Remove("lmao");
//
//
//    std::cout << htlp << std::endl;
//
//    htlp.Rehash();
//
//    std::cout << htlp << std::endl;
//}

TEST(HashTable, RehashCoefficient) {
    HashTableLinearProbe htlp;
    htlp.Insert("lol");
    htlp.Insert("kek");
    htlp.Insert("lmao");
    htlp.Insert("kuril");
    htlp.Insert("manda");
    htlp.Insert("hui");
    htlp.Insert("hui");
    htlp.Insert("fsfss");
    htlp.Insert("adipdipa");
    htlp.Insert("pop");
    htlp.Remove("manda");
    htlp.Insert("apdls");


    std::cout << htlp.GetFillCoefficient() << std::endl;

    std::cout << htlp << std::endl;

    htlp.Insert("kok");

    std::cout << htlp.GetFillCoefficient()<< std::endl;
    std::cout << htlp << std::endl;
}
