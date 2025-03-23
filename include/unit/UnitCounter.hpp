#pragma once 

#include <unordered_map>

template <typename UnitType, int MaxCount>
class UnitCounter {
private:
    static int count_;
public:
    UnitCounter() { ++count_; }
    UnitCounter(const UnitCounter&) : UnitCounter() {}
    UnitCounter(UnitCounter&&) {}
    UnitCounter& operator=(const UnitCounter& rhs) { if (this != &rhs) ++count_; return *this; };
    UnitCounter& operator=(UnitCounter&&) { return *this; }
    ~UnitCounter() { --count_; }

    static int get_count() { return count_; }
    static int get_max_count() { return MaxCount; }
};

template <typename UnitType, int MaxCount>
int UnitCounter<UnitType, MaxCount>::count_ = 0;

class RegularUnitCounter {
private:
    static std::unordered_map<int, int> count_;
    int unit_value_{0};
public:
    explicit RegularUnitCounter(const int unit_value);
    RegularUnitCounter(const RegularUnitCounter&);
    RegularUnitCounter(RegularUnitCounter&&);
    RegularUnitCounter& operator=(const RegularUnitCounter&);
    RegularUnitCounter& operator=(RegularUnitCounter&&);
    ~RegularUnitCounter();

    static int get_count(int unit_value);
    static int get_max_count(int unit_value);
};