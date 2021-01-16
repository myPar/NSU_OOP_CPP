#include "pch.h"
#include <limits>
#include <unordered_map>
#include "Trit.h"

enum {block_size = int32_size / trit_size};
enum sizes{size_count = 5, size1 = 10, size2 = 1000, size3 = 10000, size4 = 100000, size5 = 1000000};

// checking correctness of memory allocation in TritSet creating and initialisation process:

// Creating Test body:
TEST(TestMemoryAllocation, TestCreating) {
    size_t capacity = 1;
    size_t bound_idx = 15;

    for (size_t i = 1; i < size5 /5; i++) {
        if (i > 1 && i % 16 == 1) {
            capacity++;
            bound_idx += block_size;
        }
        TritSet set(i);
        ASSERT_EQ(set.get_capacity(), capacity) << "capacity failed on trit number: " << i;
        ASSERT_EQ(set.get_last_idx(), 0) << "last_idx failed on trit number: " << i;
        ASSERT_EQ(set.get_bound_idx(), bound_idx) << "bound_idx failed on trit number: " << i;
    }
}
// Initialization Test body:
TEST(TestMemoryAllocation, TestInitialization) {
    TritSet set(10);
    size_t capacity = 1;
    size_t bound_idx = 15;
    Trit cur_trit = Unknown;
    // store Trit in TritSet and check memory allocation:
    for (size_t i = 0; i < size5; i++) {
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

// simple tests - checks that Unknown does not allocate memory:
        // we have already checked that TritSet fields initialization in creating 
        // and in TritSet initialisation works correctly so we can use fields data
    // SimpleTest1 body:
TEST(TestMemoryAllocation, SimpleTest1) {
    TritSet set(size1);
    set[10000] = Unknown;
    ASSERT_EQ(set.get_capacity(), 1) << "capacity failed";
    ASSERT_EQ(set.get_last_idx(), 0) << "last_idx failed";
    ASSERT_EQ(set.get_bound_idx(), 15) << "bound_idx failed on index";
}
    // SimpleTest2 body:
TEST(TestMemoryAllocation, SimpleTest2) {
    TritSet set(size2);
    size_t cap = set.get_capacity();
    size_t b_idx = set.get_bound_idx();

    set[10000] = Unknown;

    ASSERT_EQ(set.get_capacity(), cap) << "capacity failed";
    ASSERT_EQ(set.get_last_idx(), 0) << "last_idx failed";
    ASSERT_EQ(set.get_bound_idx(), b_idx) << "bound_idx failed on index";
}
    // SimpleTest3 body:
TEST(TestMemoryAllocation, SimpleTest3) {
    TritSet set(size2);
    size_t cap = set.get_capacity();
    size_t b_idx = set.get_bound_idx();

    set[100000] = Unknown;

    ASSERT_EQ(set.get_capacity(), cap) << "capacity failed";
    ASSERT_EQ(set.get_last_idx(), 0) << "last_idx failed";
    ASSERT_EQ(set.get_bound_idx(), b_idx) << "bound_idx failed on index";
}

// checking memory free by calling TritSet::shrink() method (on trit sets with different size):
    // TestMemoryFree body:
TEST(TestMemoryFree, Test) {
    size_t limits_number = sizes(0);
    // loop for each size
    for (size_t i = 1; i <= limits_number; i++) {
        size_t size = sizes(i);

        size_t capacity = 1;
        size_t bound_idx = 15;

        for (size_t j = 0; j < size; j++) {
            if (i > 0 && i % 16 == 0) {
                capacity++;
                bound_idx += block_size;
            }
            // allocate memory
            TritSet set(size);
            // initialize trit in position i
            set[i] = Trit(i % 3);
            // free memory
            set.shrink();
            ASSERT_EQ(set.get_capacity(), capacity) << "set size: " << size << "; capacity failed on index: " << i;
            ASSERT_EQ(set.get_last_idx(), i) << "set size: " << size << "; last_idx failed on index: " << i;
            ASSERT_EQ(set.get_bound_idx(), bound_idx) << "set size: " << size << "; bound_idx failed on index: " << i;
        }
    }
}

// checking correctness of Trit storing
    // simple large test:
TEST(TestDataStoring, Test0) {  // Test0
    TritSet set(size5);
    
    for (size_t i = 0; i < size5; i++) {
        set[i] = Trit(i % 3);
        ASSERT_TRUE(set[i] == Trit(i % 3)) << "failed on index: " << i;
    }
}
    // test some non standart setuations:
TEST(TestDataStoring, Test1) {  // Test1
    TritSet set(size1);
    set[0] = True;
    ASSERT_TRUE(set[0] == True);
    set[0] = False;
    ASSERT_TRUE(set[0] == False);
    set[0] = Unknown;
    ASSERT_TRUE(set[0] == Unknown);
}
TEST(TestDataStoring, Test2) {  // Test2
    TritSet set(size1);
    ASSERT_TRUE(set[-1] == Unknown);
    ASSERT_EQ(set.get_capacity(), 1);

    ASSERT_TRUE(set[-1000] == Unknown);
    ASSERT_EQ(set.get_capacity(), 1);

    ASSERT_TRUE(set[-100000] == Unknown);
    ASSERT_EQ(set.get_capacity(), 1);

    ASSERT_TRUE(set[100000] == Unknown);
    ASSERT_EQ(set.get_capacity(), 1);
}

TEST(TestTritSetIterator, Test1) {  // test iterator's work
    TritSet set(16);
    set[10] = True;
    set[0] = False;
    set[11] = True;
    set[15] = True;

    int count = 0;
    
    // first form
    for (auto iter : set) {
        if (iter == True) {
            count++;
        }
    }
    ASSERT_EQ(count, 3);
    
    // second form
    for (TritSet::iterator iter = set.begin(); iter != set.end(); ++iter) {
        if (iter.idx == 10) {
            ASSERT_EQ(*iter, True);
        }
        else if (iter.idx == 0) {
            ASSERT_EQ(*iter, False);
        }
        else if (iter.idx == 11) {
            ASSERT_EQ(*iter, True);
        }
        else if (iter.idx == 15) {
            ASSERT_EQ(*iter, True);
        }
        else {
            ASSERT_EQ(*iter, Unknown);
        }
    }
}

// Test binary operations AND, OR
TEST(TestBinaryOperations, Test1) {     // Test1
    TritSet set1(size4);
    TritSet set2(size4);

    // init sets
    for (size_t i = 0; i < size4; i++) {
        set1[i] = Trit(i % 3);
        set2[i] = Trit(i % 3);
    }
    TritSet result1 = set1 & set2;
    TritSet result2 = set1 | set2;
    // check result data
    for (size_t i = 0; i < size4; i++) {
        ASSERT_TRUE(result1[i] == Trit(i % 3)) << "AND operation failed on index: " << i;
        ASSERT_TRUE(result2[i] == Trit(i % 3)) << "OR operation failed on index: " << i;
    }
}
TEST(TestBinaryOperations, Test2) {     // Test2
    TritSet set1(size4);
    TritSet set2(size4);

    // init sets
    for (size_t i = 0; i < size4; i++) {
        set1[i] = True;
        set2[i] = False;
    }
    TritSet result1 = set1 & set2;
    TritSet result2 = set1 | set2;
    // check result data
    for (size_t i = 0; i < size4; i++) {
        ASSERT_TRUE(result1[i] == False) << "AND operation failed on index: " << i;
        ASSERT_TRUE(result2[i] == True) << "OR operation failed on index: " << i;
    }
}
TEST(TestBinaryOperations, Test3) {     // Test3
    TritSet set1(size4);
    TritSet set2(size4);

    // init sets
    for (size_t i = 0; i < size4; i++) {
        set1[i] = True;
        set2[i] = Unknown;
    }
    TritSet result1 = set1 & set2;
    TritSet result2 = set1 | set2;
    // check result data
    for (size_t i = 0; i < size4; i++) {
        ASSERT_TRUE(result1[i] == Unknown) << "AND operation failed on index: " << i;
        ASSERT_TRUE(result2[i] == True) << "OR operation failed on index: " << i;
    }
}
TEST(TestBinaryOperations, Test4) {     // Test4
    TritSet set1(size4);
    TritSet set2(size4);

    // init sets
    for (size_t i = 0; i < size4; i++) {
        set1[i] = False;
        set2[i] = Unknown;
    }
    TritSet result1 = set1 & set2;
    TritSet result2 = set1 | set2;
    // check result data
    for (size_t i = 0; i < size4; i++) {
        ASSERT_TRUE(result1[i] == False) << "AND operation failed on index: " << i;
        ASSERT_TRUE(result2[i] == Unknown) << "OR operation failed on index: " << i;
    }
}
    // args have different size
TEST(TestBinaryOperations, Test5) {     // Test5
    TritSet set1(16);
    set1[0] = True;
    set1[3] = False;
    set1[7] = True;
    set1[15] = False;
    TritSet set2(size4);
    set2[size4 - 1] = True;

    TritSet result1 = set1 & set2;
    TritSet result2 = set1 | set2;
    // swap args
    TritSet result3 = set2 & set1;
    TritSet result4 = set2 | set1;

    // check result1 and result3:
    ASSERT_TRUE(result1[0] == Unknown);
    ASSERT_TRUE(result3[0] == Unknown);
    ASSERT_TRUE(result1[3] == False);
    ASSERT_TRUE(result3[3] == False);
    ASSERT_TRUE(result1[7] == Unknown);
    ASSERT_TRUE(result3[7] == Unknown);
    ASSERT_TRUE(result1[15] == False);
    ASSERT_TRUE(result3[15] == False);

    // check result2 and result4:
    ASSERT_TRUE(result2[0] == True);
    ASSERT_TRUE(result4[0] == True);
    ASSERT_TRUE(result2[3] == Unknown);
    ASSERT_TRUE(result4[3] == Unknown);
    ASSERT_TRUE(result2[7] == True);
    ASSERT_TRUE(result4[7] == True);
    ASSERT_TRUE(result2[15] == Unknown);
    ASSERT_TRUE(result4[15] == Unknown);

    // check data from 16 to size4 - 2 index (all trits should be equal Unknown)
    for (size_t i = 16; i < size4 - 1; i++) {
        ASSERT_TRUE(result1[i] == Unknown);
        ASSERT_TRUE(result2[i] == Unknown);
        ASSERT_TRUE(result3[i] == Unknown);
        ASSERT_TRUE(result4[i] == Unknown);
    }
    // check last trit
    ASSERT_TRUE(result1[size4 - 1] == Unknown);
    ASSERT_TRUE(result2[size4 - 1] == True);
    ASSERT_TRUE(result3[size4 - 1] == Unknown);
    ASSERT_TRUE(result4[size4 - 1] == True);
}
    // Test binary operation NOT:
TEST(TestBinaryOperations, Test_NOT) {
    // init set
    TritSet set(16);
    set[0] = True;
    set[15] = True;
    set[3] = False;
    set[4] = False;

    for (size_t i = 16; i < size4 / 2; i++) {
        set[i] = True;
    }
    for (size_t i = size4 / 2 + 1; i < size4; i++) {
        set[i] = False;
    }
    // invert set
    TritSet result = !set;
    // check the result
    ASSERT_TRUE(result[0] == False);
    ASSERT_TRUE(result[15] == False);
    ASSERT_TRUE(result[3] == True);
    ASSERT_TRUE(result[4] == True);

    // check result data
    for (size_t i = 16; i < size4 / 2; i++) {
        ASSERT_TRUE(result[i] == False);
    }
    for (size_t i = size4 / 2 + 1; i < size4; i++) {
        ASSERT_TRUE(result[i] == True);
    }
}

// Testing other public methods:
    // check TritSet::trim() method
TEST(TestOtherPublicMethods, TestTrim) {
    TritSet set(size4);
    
    // increment value is size4 / 100 because of O(N^2) time asimpthotic
    for (size_t start_idx = 0; start_idx < size4; start_idx += size4 / 100) {   
        // init set
        for (size_t i = 0; i < size4; i++) {
            set[i] = Trit(i % 3);
        }
        // forget data from start_idx
        set.trim(start_idx);
        // check data
        for (size_t cur_idx = 0; cur_idx < size4; cur_idx++) {
            if (cur_idx < start_idx) {
                // check copied data
                ASSERT_TRUE(set[cur_idx] == Trit(cur_idx % 3));
            }
            else {
                // check forgotten data
                ASSERT_TRUE(set[cur_idx] == Unknown);
            }
        }
    }
}
    //check TritSet::cardinality() methods
TEST(TestOtherPublicMethods, TestCardinality) {
    TritSet set(size5);

    for (size_t i = 0; i < size5; i++) {
        set[i] = Trit(i % 3);
    }
    ASSERT_EQ(set.cardinality(True), size5 / 3);
    ASSERT_EQ(set.cardinality(False), size5 / 3);
    ASSERT_EQ(set.cardinality(Unknown), size5 / 3 + 1);

    unordered_map<Trit, size_t> map = set.cardinality();
    
    ASSERT_EQ(map[True], size5 / 3);
    ASSERT_EQ(map[False], size5 / 3);
    ASSERT_EQ(map[Unknown], size5 / 3 + 1);
}
    // check TritSet::length() method
TEST(TestOtherPublicMethods, TestLength) {
    TritSet set(size5);
    set[size5 - 1] = True;
    ASSERT_EQ(set.length(), size5);
    set[size5 - 1] = Unknown;
    ASSERT_EQ(set.length(), 0);
    set[size5 - 1] = False;
    ASSERT_EQ(set.length(), size5);
}

TEST(TestAnnotationExample, Test1) {
    TritSet set(1000);
    // length of internal array
    size_t allocLength = set.get_capacity();
    ASSERT_TRUE(allocLength >= 1000 * 2 / 8 / sizeof(int32_t));
    // 1000*2 - min bits count
    // 1000*2 / 8 - min bytes count
    // 1000*2 / 8 / sizeof(uint) - min uint[] size

    //не выделяет никакой памяти
    set[1000000000] = Unknown;
    ASSERT_TRUE(allocLength == set.get_capacity());

    // false, but no exception or memory allocation
    if (set[2000000000] == True) {}
    ASSERT_TRUE(allocLength == set.get_capacity());

    //выделение памяти
    set[1000000000] = True;
    ASSERT_TRUE(allocLength < set.get_capacity());

    //no memory operations
    allocLength = set.get_capacity();
    set[1000000000] = Unknown;
    set[1000000] = False;
    ASSERT_TRUE(allocLength == set.get_capacity());

    TritSet set2(1000);
    set2[100] = True;
    allocLength = set2.get_capacity();

    set2.shrink();
    ASSERT_TRUE(allocLength > set2.get_capacity());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}