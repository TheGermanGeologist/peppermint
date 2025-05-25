#include "gtest/gtest.h"
#include "test_wrapper.h" // Include the wrapper instead of individual C headers
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime> // Added for time() in stress test
#include <numeric> // For std::iota

// Example test case
TEST(SortingAlgos, HandlesEmptyArray) {
    KeyType* arr = NULL;
    int* indices = NULL;
    // The primary concern here is that adapt_sort_ki handles n=0
    // (and potentially NULL pointers) without crashing.
    // An empty array is trivially sorted.
    adapt_sort_ki(arr, indices, 0);
}

TEST(SortingAlgos, HandlesSingleElementArray) {
    KeyType arr[] = {5};
    int indices[] = {0};
    adapt_sort_ki(arr, indices, 1);
    ASSERT_TRUE(std::is_sorted(arr, arr + 1));
    ASSERT_EQ(indices[0], 0);
}

TEST(SortingAlgos, HandlesAlreadySortedArray) {
    KeyType arr[] = {1, 2, 3, 4, 5};
    int indices[] = {0, 1, 2, 3, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    adapt_sort_ki(arr, indices, n);
    ASSERT_TRUE(std::is_sorted(arr, arr + n));
    // Check if indices are also sorted according to keys
    for(int i = 0; i < n; ++i) {
        ASSERT_EQ(arr[i], i + 1); // Assuming keys are 1 to n for simplicity
        ASSERT_EQ(indices[i], i); // Assuming original indices were 0 to n-1
    }
}

TEST(SortingAlgos, HandlesReverseSortedArray) {
    KeyType arr[] = {5, 4, 3, 2, 1};
    int initial_indices[] = {0, 1, 2, 3, 4};
    int indices[5]; 
    for(int i=0; i<5; ++i) indices[i] = initial_indices[i];
    int n = sizeof(arr) / sizeof(arr[0]);
    adapt_sort_ki(arr, indices, n);
    ASSERT_TRUE(std::is_sorted(arr, arr + n));
    // Check if indices were permuted correctly
    // Original: (5,0), (4,1), (3,2), (2,3), (1,4)
    // Sorted:   (1,4), (2,3), (3,2), (4,1), (5,0)
    // Expected indices: 4, 3, 2, 1, 0
    for(int i=0; i < n; ++i) {
      ASSERT_EQ(arr[i], i+1);
      ASSERT_EQ(indices[i], n-1-i);
    }
}

TEST(SortingAlgos, HandlesArrayWithDuplicates) {
    KeyType arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    int initial_indices[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    const int n = 11;
    int indices[n]; 
    for(int i=0; i<n; ++i) indices[i] = initial_indices[i];

    KeyType sorted_arr_expected[n];
    for(int i=0; i<n; ++i) sorted_arr_expected[i] = arr[i];
    std::sort(sorted_arr_expected, sorted_arr_expected + n);

    adapt_sort_ki(arr, indices, n);
    ASSERT_TRUE(std::is_sorted(arr, arr + n));
    for(int i=0; i < n; ++i) {
      ASSERT_EQ(arr[i], sorted_arr_expected[i]);
    }
    // We can't easily predict final indices with duplicates without stable sort
    // or more complex check. For now, just check keys are sorted.
}

TEST(SortingAlgos, HandlesArrayWithAllIdenticalElements) {
    KeyType arr[] = {7, 7, 7, 7, 7};
    int indices[] = {0, 1, 2, 3, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    adapt_sort_ki(arr, indices, n);
    ASSERT_TRUE(std::is_sorted(arr, arr + n));
    // Indices should remain in original order if sort is stable for identical keys
    // or be in some valid permutation if not explicitly stable.
    // For now, primarily check keys.
    for(int i = 0; i < n; ++i) {
        ASSERT_EQ(arr[i], 7);
    }
}

TEST(SortingAlgos, RandomizedStressTest) {
    // Seed random number generator once for this test case.
    // For more controlled reproducibility, consider a fixed seed or gtest's --gtest_random_seed.
    srand(static_cast<unsigned int>(time(nullptr)));

    const int num_iterations = 100; // Number of random arrays to test
    const int max_array_size = 1000; // Maximum size of the random arrays (must be > 0)
    const int min_array_size = 1;   // Minimum size of the random arrays

    for (int iter = 0; iter < num_iterations; ++iter) {
        int n = (rand() % (max_array_size - min_array_size + 1)) + min_array_size;

        std::vector<KeyType> arr_to_sort(n);
        std::vector<int> indices_to_sort(n);
        std::vector<KeyType> arr_expected(n);

        for (int i = 0; i < n; ++i) {
            // Generate random KeyType values. Adjust range/distribution as needed.
            // Example: values between -5000 and 4999 for integer-like KeyType
            arr_to_sort[i] = static_cast<KeyType>((rand() % 10000) - 5000);
            indices_to_sort[i] = i; // Initial indices: 0, 1, ..., n-1
        }
        
        arr_expected = arr_to_sort; // Copy elements for sorting with std::sort

        // Sort the expected array to establish the correct order of keys
        std::sort(arr_expected.begin(), arr_expected.end());

        // Call the sorting function to be tested
        adapt_sort_ki(arr_to_sort.data(), indices_to_sort.data(), n);

        // Check 1: Is the array sorted?
        if (!std::is_sorted(arr_to_sort.begin(), arr_to_sort.end())) {
            std::stringstream error_details;
            error_details << "std::is_sorted failed in iteration " << iter << " with size " << n << ".\\n";
            error_details << "Attempting to find first unsorted pair:\\n";
            bool found_error_pair = false;
            for (size_t i = 0; i < arr_to_sort.size(); ++i) {
                if (i + 1 < arr_to_sort.size()) {
                    if (arr_to_sort[i] > arr_to_sort[i+1]) { // Assuming KeyType uses > for out of order
                        error_details << "Unsorted pair found: arr_to_sort[" << i << "] = " << arr_to_sort[i]
                                      << ", arr_to_sort[" << i+1 << "] = " << arr_to_sort[i+1] << ".\\n";
                        error_details << "Segment around error: ";
                        size_t start_print = (i > 5) ? i - 5 : 0;
                        size_t end_print = std::min(arr_to_sort.size(), i + 1 + 5);
                        for (size_t k = start_print; k < end_print; ++k) {
                            if (k == i || k == i + 1) error_details << "[";
                            error_details << arr_to_sort[k];
                            if (k == i || k == i + 1) error_details << "]";
                            error_details << " ";
                        }
                        error_details << "\\n";
                        found_error_pair = true;
                        break; 
                    }
                }
            }
            if (!found_error_pair && n > 0) {
                 error_details << "Could not find specific unsorted pair with simple scan, but std::is_sorted failed. Printing first few elements:\\n";
                 for(size_t i=0; i < std::min((size_t)20, arr_to_sort.size()); ++i) {
                    error_details << arr_to_sort[i] << " ";
                 }
                 if (arr_to_sort.size() > 20) error_details << "...";
                 error_details << "\\n";
            }
            FAIL() << error_details.str();
        }


        // Check 2: Does the sorted array contain the correct elements?
        // This verifies correctness, especially with duplicate values.
        ASSERT_EQ(arr_to_sort, arr_expected)
            << "Sorted array elements do not match expected elements in iteration " << iter 
            << " with size " << n;

        // Note: Checking the 'indices_to_sort' array after the sort can also be done here.
        // However, as mentioned in your 'HandlesArrayWithDuplicates' test,
        // predicting the final state of indices with non-stable sorts and duplicates is complex.
        // If 'adapt_sort_ki' is expected to be stable, you could generate expected indices
        // by sorting pairs of (value, original_index) and then compare.
        // For this general stress test, focusing on key correctness is a strong first step.
    }
}

TEST(SortingAlgos, RandomizedIndicesCorrectnessTest) {
    srand(static_cast<unsigned int>(time(nullptr)));

    const int array_size = 5000; // Size of the large random array

    std::vector<KeyType> array_to_sort(array_size);
    std::vector<KeyType> original_values(array_size);
    std::vector<int> final_indices(array_size);

    // Populate with random data and initial indices
    for (int i = 0; i < array_size; ++i) {
        array_to_sort[i] = static_cast<KeyType>((rand() % 20000) - 10000); // Example range
        original_values[i] = array_to_sort[i]; // Store original value
        final_indices[i] = i;                   // Initial index
    }

    // Call the sorting function
    adapt_sort_ki(array_to_sort.data(), final_indices.data(), array_size);

    // First, ensure the primary array is actually sorted
    if (!std::is_sorted(array_to_sort.begin(), array_to_sort.end())) {
        std::stringstream error_details;
        error_details << "std::is_sorted failed for RandomizedIndicesCorrectnessTest with size " << array_size << ".\\n";
        error_details << "Attempting to find first unsorted pair:\\n";
        bool found_error_pair = false;
        for (size_t i = 0; i < array_to_sort.size(); ++i) {
            if (i + 1 < array_to_sort.size()) {
                if (array_to_sort[i] > array_to_sort[i+1]) { // Assuming KeyType uses > for out of order
                    error_details << "Unsorted pair found: array_to_sort[" << i << "] = " << array_to_sort[i]
                                  << ", array_to_sort[" << i+1 << "] = " << array_to_sort[i+1] << ".\\n";
                    error_details << "Segment around error: ";
                    size_t start_print = (i > 5) ? i - 5 : 0;
                    size_t end_print = std::min(array_to_sort.size(), i + 1 + 5);
                    for (size_t k = start_print; k < end_print; ++k) {
                        if (k == i || k == i + 1) error_details << "[";
                        error_details << array_to_sort[k];
                        if (k == i || k == i + 1) error_details << "]";
                        error_details << " ";
                    }
                    error_details << "\\n";
                    found_error_pair = true;
                    break; 
                }
            }
        }
        if (!found_error_pair && array_size > 0) {
             error_details << "Could not find specific unsorted pair with simple scan, but std::is_sorted failed. Printing first few elements:\\n";
             for(size_t i=0; i < std::min((size_t)20, array_to_sort.size()); ++i) {
                error_details << array_to_sort[i] << " ";
             }
             if (array_to_sort.size() > 20) error_details << "...";
             error_details << "\\n";
        }
        FAIL() << error_details.str();
    }

    // Check if the sorted indices correctly map to original values
    bool indices_correct = true;
    for (int i = 0; i < array_size; ++i) {
        if (array_to_sort[i] != original_values[final_indices[i]]) {
            indices_correct = false;
            // Log detailed information on the first mismatch found
            FAIL() << "Index mismatch at sorted position " << i << ":\n"
                   << "  Sorted array value (array_to_sort[i]): " << array_to_sort[i] << "\n"
                   << "  Original value at permuted index (original_values[final_indices[i]]): " 
                   << original_values[final_indices[i]] << "\n"
                   << "  Value of final_indices[i]: " << final_indices[i];
            break; // Stop on first error for clarity
        }
    }
    ASSERT_TRUE(indices_correct) << "Indices do not correctly map sorted array back to original values.";
}

// Define a simple struct for testing map_varray_to_indices
struct TestStruct {
    int id;
    float val;
    // Equality operator for ASSERT_EQ
    bool operator==(const TestStruct& other) const {
        return id == other.id && val == other.val;
    }
};

// GTest printer for TestStruct to make test output readable
std::ostream& operator<<(std::ostream& os, const TestStruct& ts) {
    return os << "TestStruct{id=" << ts.id << ", val=" << ts.val << "f}";
}

// New test suite for array permutation functions
class ArrayPermutationTests : public ::testing::Test {
protected:
    // Helper to initialize the 'visited' array, as required by the C functions
    bool* create_and_init_visited(size_t n) {
        bool* visited = new bool[n](); // Value-initializes to false
        return visited;
    }
};

// Tests for map_farray_to_indices
TEST_F(ArrayPermutationTests, MapFloatArrayEmpty) {
    const size_t n = 0;
    float* arr_to_permute = nullptr;
    int* indices = nullptr;
    bool* visited = create_and_init_visited(n);

    map_farray_to_indices(arr_to_permute, indices, visited, n);
    SUCCEED(); // Test passes if it doesn't crash

    delete[] visited;
}

TEST_F(ArrayPermutationTests, MapFloatArraySingleElement) {
    const size_t n = 1;
    std::vector<float> arr_to_permute = {123.45f};
    std::vector<int> permutation_indices = {0};
    std::vector<float> expected_arr = {123.45f};
    bool* visited = create_and_init_visited(n);

    std::vector<float> working_arr = arr_to_permute;
    map_farray_to_indices(working_arr.data(), permutation_indices.data(), visited, n);
    ASSERT_EQ(working_arr, expected_arr);
    delete[] visited;
}

TEST_F(ArrayPermutationTests, MapFloatArrayReverse) {
    const size_t n = 5;
    std::vector<float> arr_to_permute = {10.0f, 20.0f, 30.0f, 40.0f, 50.0f};
    std::vector<int> permutation_indices = {4, 3, 2, 1, 0}; 
    // Expected: element at old_pos i moves to new_pos permutation_indices[i]
    // old[0] (10.0f) -> pos 4
    // old[1] (20.0f) -> pos 3
    // old[2] (30.0f) -> pos 2
    // old[3] (40.0f) -> pos 1
    // old[4] (50.0f) -> pos 0
    // Result: {50.0f, 40.0f, 30.0f, 20.0f, 10.0f}
    std::vector<float> expected_arr = {50.0f, 40.0f, 30.0f, 20.0f, 10.0f};
    bool* visited = create_and_init_visited(n);

    std::vector<float> working_arr = arr_to_permute;
    map_farray_to_indices(working_arr.data(), permutation_indices.data(), visited, n);
    ASSERT_EQ(working_arr, expected_arr);
    delete[] visited;
}

TEST_F(ArrayPermutationTests, MapFloatArrayCycle) {
    const size_t n = 4;
    std::vector<float> arr_to_permute = {1.0f, 2.0f, 3.0f, 4.0f};
    std::vector<int> permutation_indices = {1, 2, 0, 3}; 
    // Permutation P = {1, 2, 0, 3}
    // Expected: new_arr[i] = old_arr[P[i]]
    // new_arr[0] = old_arr[P[0]] = old_arr[1] = 2.0f
    // new_arr[1] = old_arr[P[1]] = old_arr[2] = 3.0f
    // new_arr[2] = old_arr[P[2]] = old_arr[0] = 1.0f
    // new_arr[3] = old_arr[P[3]] = old_arr[3] = 4.0f
    // Result: {2.0f, 3.0f, 1.0f, 4.0f}
    std::vector<float> expected_arr = {2.0f, 3.0f, 1.0f, 4.0f};
    bool* visited = create_and_init_visited(n);

    std::vector<float> working_arr = arr_to_permute;
    map_farray_to_indices(working_arr.data(), permutation_indices.data(), visited, n);
    ASSERT_EQ(working_arr, expected_arr);
    delete[] visited;
}

// Tests for map_iarray_to_indices
TEST_F(ArrayPermutationTests, MapIntArrayEmpty) {
    const size_t n = 0;
    int* arr_to_permute = nullptr;
    int* permutation_indices = nullptr;
    bool* visited = create_and_init_visited(n);
    map_iarray_to_indices(arr_to_permute, permutation_indices, visited, n);
    SUCCEED();
    delete[] visited;
}

TEST_F(ArrayPermutationTests, MapIntArraySingleElement) {
    const size_t n = 1;
    std::vector<int> arr_to_permute = {123};
    std::vector<int> permutation_indices = {0};
    std::vector<int> expected_arr = {123};
    bool* visited = create_and_init_visited(n);

    std::vector<int> working_arr = arr_to_permute;
    map_iarray_to_indices(working_arr.data(), permutation_indices.data(), visited, n);
    ASSERT_EQ(working_arr, expected_arr);
    delete[] visited;
}

TEST_F(ArrayPermutationTests, MapIntArrayReverse) {
    const size_t n = 5;
    std::vector<int> arr_to_permute = {10, 20, 30, 40, 50};
    std::vector<int> permutation_indices = {4, 3, 2, 1, 0}; 
    std::vector<int> expected_arr = {50, 40, 30, 20, 10};
    bool* visited = create_and_init_visited(n);

    std::vector<int> working_arr = arr_to_permute;
    map_iarray_to_indices(working_arr.data(), permutation_indices.data(), visited, n);
    ASSERT_EQ(working_arr, expected_arr);
    delete[] visited;
}

// ...existing code...
TEST_F(ArrayPermutationTests, MapIntArrayCycle) {
    const size_t n = 4;
    std::vector<int> arr_to_permute = {1, 2, 3, 4};
    std::vector<int> permutation_indices = {1, 2, 0, 3}; 
    // Expected: new_arr[i] = old_arr[P[i]]
    // new_arr[0] = old_arr[1] = 2
    // new_arr[1] = old_arr[2] = 3
    // new_arr[2] = old_arr[0] = 1
    // new_arr[3] = old_arr[3] = 4
    // Result: {2, 3, 1, 4}
    std::vector<int> expected_arr = {2, 3, 1, 4};
    bool* visited = create_and_init_visited(n);

    std::vector<int> working_arr = arr_to_permute;
    map_iarray_to_indices(working_arr.data(), permutation_indices.data(), visited, n);
    ASSERT_EQ(working_arr, expected_arr);
    delete[] visited;
}

// Tests for map_barray_to_indices
TEST_F(ArrayPermutationTests, MapBoolArrayEmpty) {
    const size_t n = 0;
    bool* arr_to_permute = nullptr;
    int* permutation_indices = nullptr;
    bool* visited = create_and_init_visited(n);
    map_barray_to_indices(arr_to_permute, permutation_indices, visited, n);
    SUCCEED();
    delete[] visited;
}

TEST_F(ArrayPermutationTests, MapBoolArraySingleElement) {
    const size_t n = 1;
    bool* working_arr = new bool[n]; 
    working_arr[0] = true;
    std::vector<int> permutation_indices = {0};
    bool expected_val = true;
    bool* visited = create_and_init_visited(n);

    map_barray_to_indices(working_arr, permutation_indices.data(), visited, n);
    ASSERT_EQ(working_arr[0], expected_val);
    
    delete[] working_arr;
    delete[] visited;
}

TEST_F(ArrayPermutationTests, MapBoolArrayReverse) {
    const size_t n = 4;
    bool initial_contents[] = {true, false, true, false};
    std::vector<int> permutation_indices = {3, 2, 1, 0}; 
    bool expected_contents[] = {false, true, false, true};
    
    bool* working_arr = new bool[n];
    for(size_t i=0; i<n; ++i) working_arr[i] = initial_contents[i];
    bool* visited = create_and_init_visited(n);

    map_barray_to_indices(working_arr, permutation_indices.data(), visited, n);
    for(size_t i=0; i<n; ++i) {
        ASSERT_EQ(working_arr[i], expected_contents[i]) << "at index " << i;
    }
    delete[] working_arr;
    delete[] visited;
}

TEST_F(ArrayPermutationTests, MapBoolArrayCycle) {
    const size_t n = 4;
    bool initial_contents[] = {true, false, true, false}; // T F T F
    std::vector<int> permutation_indices = {1, 2, 0, 3}; 
    // Expected: new_arr[i] = old_arr[P[i]]
    // new_arr[0] = old_arr[1] = false
    // new_arr[1] = old_arr[2] = true
    // new_arr[2] = old_arr[0] = true
    // new_arr[3] = old_arr[3] = false
    // Result: {false, true, true, false}
    bool expected_contents[] = {false, true, true, false};
    
    bool* working_arr = new bool[n];
    for(size_t i=0; i<n; ++i) working_arr[i] = initial_contents[i];
    bool* visited = create_and_init_visited(n);

    map_barray_to_indices(working_arr, permutation_indices.data(), visited, n);
    for(size_t i=0; i<n; ++i) {
        ASSERT_EQ(working_arr[i], expected_contents[i]) << "at index " << i;
    }
    delete[] working_arr;
    delete[] visited;
}

// Tests for map_varray_to_indices
TEST_F(ArrayPermutationTests, MapGenericArrayEmpty) {
    const size_t n = 0;
    void* arr_to_permute = nullptr;
    int* permutation_indices = nullptr;
    bool* visited = create_and_init_visited(n);
    size_t el_size = sizeof(int); 

    map_varray_to_indices(arr_to_permute, permutation_indices, visited, n, el_size);
    SUCCEED();
    delete[] visited;
}

TEST_F(ArrayPermutationTests, MapGenericArrayIntCycle) {
    const size_t n = 3;
    std::vector<int> arr_to_permute = {100, 200, 300};
    std::vector<int> permutation_indices = {2, 0, 1}; 
    // Expected: new_arr[i] = old_arr[P[i]]
    // new_arr[0] = old_arr[2] = 300
    // new_arr[1] = old_arr[0] = 100
    // new_arr[2] = old_arr[1] = 200
    // Result: {300, 100, 200}
    std::vector<int> expected_arr = {300, 100, 200};
    bool* visited = create_and_init_visited(n);
    size_t el_size = sizeof(int);

    std::vector<int> working_arr = arr_to_permute;
    map_varray_to_indices(static_cast<void*>(working_arr.data()), permutation_indices.data(), visited, n, el_size);
    ASSERT_EQ(working_arr, expected_arr);
    delete[] visited;
}

TEST_F(ArrayPermutationTests, MapGenericArrayStructReverse) {
    const size_t n = 3;
    std::vector<TestStruct> arr_to_permute = {{1, 1.0f}, {2, 2.0f}, {3, 3.0f}};
    std::vector<int> permutation_indices = {2, 1, 0}; // Reverse
    // old[0]({1,1}) -> pos 2
    // old[1]({2,2}) -> pos 1
    // old[2]({3,3}) -> pos 0
    // Expected: {{3, 3.0f}, {2, 2.0f}, {1, 1.0f}}
    std::vector<TestStruct> expected_arr = {{3, 3.0f}, {2, 2.0f}, {1, 1.0f}};
    bool* visited = create_and_init_visited(n);
    size_t el_size = sizeof(TestStruct);

    std::vector<TestStruct> working_arr = arr_to_permute;
    map_varray_to_indices(static_cast<void*>(working_arr.data()), permutation_indices.data(), visited, n, el_size);
    ASSERT_EQ(working_arr, expected_arr);
    delete[] visited;
}

TEST_F(ArrayPermutationTests, MapGenericArrayFloatIdentity) {
    const size_t n = 4;
    std::vector<float> arr_to_permute = {1.1f, 2.2f, 3.3f, 4.4f};
    std::vector<int> permutation_indices = {0, 1, 2, 3}; // Identity
    std::vector<float> expected_arr = {1.1f, 2.2f, 3.3f, 4.4f};
    bool* visited = create_and_init_visited(n);
    size_t el_size = sizeof(float);

    std::vector<float> working_arr = arr_to_permute;
    map_varray_to_indices(static_cast<void*>(working_arr.data()), permutation_indices.data(), visited, n, el_size);
    ASSERT_EQ(working_arr, expected_arr);
    delete[] visited;
}
