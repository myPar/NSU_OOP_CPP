#include "pch.h"
#include <limits>
#include "Trit.h"

enum {max_trit_count = 1000000, block_size = int32_size / trit_size};

// checking correctness of memory allocation in TritSet initialisation process
    // Test body
TEST(TestMemoryAllocation, Test) {
    TritSet set(10);
    size_t capacity = 1;
    size_t bound_idx = 15;
    Trit cur_trit = Unknown;
    // store Trit in TritSet and check memory allocation:
    for (size_t i = 0; i < max_trit_count; i++) {
        if (i > 0 && i % 16 == 0) {
            capacity++;
            bound_idx += block_size;    
        }
        cur_trit = Trit(i % 2 + 1);     // just True and False init values, because Unknown doesn't allocate memory
        set[i] = cur_trit;
        ASSERT_EQ(set.get_capacity(), capacity) << "capacity failed on index: " << i;
        ASSERT_EQ(set.get_last_idx(), i) << "last_idx failed on index: " << i;
        ASSERT_EQ(set.get_bound_idx(), bound_idx) << "bound_idx failed on index: " << i;
    }
}
// checking memory free by calling TritSet::shrink() method:
    // number of constants
size_t counts_number = 6;   
    // constants of max number of Trits
enum Trit_Count{trit_count0 = 0, 
                trit_count1 = 10,
                trit_count2 = 100,
                trit_count3 = 1000,
                trit_count4 = 10000,
                trit_count5 = 1000000};
    // calculate capacity method
size_t calc_capacity(size_t trit_number) {
    size_t result = trit_number / block_size;
    // check if block number is non-integer value
    if (trit_number % block_size != 0) {
        result++;
    }
    return result;
}
    // calculate bound index method
size_t calc_bound_idx(size_t trit_number) {
    return calc_capacity(trit_number) * block_size - 1;
}
    // Test body
TEST(TestMemoryFree, Test) {
    for (size_t enum_idx = 0; enum_idx < counts_number; enum_idx++) {
        size_t trit_count = Trit_Count(enum_idx);

        for (size_t i = 0; i < trit_count; i++) {
            TritSet set(trit_count);
            set[i] = Trit(i % 3);
            set.shrink();
        }
    }
}

// checking correctness of Trit storing
TEST(TestDataStoring, TestName) {
}
// check correctness of public functions execution
TEST(TestPublicFunctions, TestName) {
}
// checking correctness of sequence executing of all TritSet functional
TEST(ComplexTest, TestName) {
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}