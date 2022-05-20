#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <bitset/bitset.h>
#include <doctest/doctest.h>

#include <fstream>

bool operator==(const BitSet& first, const BitSet& second) {
  std::stringstream strout1;
  std::stringstream strout2;

  strout1 << first;
  strout2 << second;

  return strout1.str() == strout2.str();
}

TEST_CASE("Simple") {
  SUBCASE("Constructors + Fill and operator<<") {
    BitSet first(12);
    std::stringstream strout;
    strout << first;
    CHECK(strout.str() == "000000000000");

    BitSet second(first);
    CHECK(first == second);

    BitSet third(12, true);
    std::stringstream strout_third;
    strout_third << third;
    CHECK(strout_third.str() == "111111111111");
  }

  SUBCASE("Operator=") {
    BitSet first(12);
    BitSet second = first;
    CHECK(first == second);
  }

  SUBCASE("Size") {
    for (size_t i = 1; i < 20; i++) {
      BitSet first(i);
      CHECK(first.Size() == i);
    }
  }

  SUBCASE("operator>> and |, ^, &") {
    std::stringstream strin_first("10101");
    std::stringstream strin_second("00011");

    BitSet first;
    BitSet second;
    strin_first >> first;
    strin_second >> second;

    std::vector<std::string> strs{"00001", "10111", "10110", "00011", "00000"};
    std::vector<BitSet> results;
    for (size_t i = 0; i < strs.size(); i++) {
      std::stringstream strin(strs[i]);
      BitSet res;
      strin >> res;
      results.push_back(res);
    }

    CHECK((first & second) == results[0]);
    CHECK((first | second) == results[1]);
    CHECK((first ^ second) == results[2]);

    CHECK((first &= second) == results[0]);
    CHECK((first |= second) == results[3]);
    CHECK((first ^= second) == results[4]);
  }

  SUBCASE("Bitholder") {
    BitSet first(12);

    for (size_t i = 0; i < 12; i++) {
      CHECK(first[i] == false);
      first[i] = true;
      CHECK(first[i] == true);
    }
  }
}

TEST_CASE("Exceptions") {
  CHECK_THROWS(BitSet(0));

  BitSet first(12);
  BitSet second(15);

  CHECK_THROWS(first |= second);
  CHECK_THROWS(first ^= second);
  CHECK_THROWS(first &= second);

  CHECK_THROWS(first | second);
  CHECK_THROWS(first ^ second);
  CHECK_THROWS(first & second);

  CHECK_THROWS(first.Resize(0));
  CHECK_THROWS(first.Resize(-1));

  CHECK_THROWS(second[-1]);
}