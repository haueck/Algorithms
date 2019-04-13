/*
 *
 *
 * Author: Rafal Kozik
 */

#include <bits/stdc++.h>
#include <gtest/gtest.h>

#define LOG(x) std::cout << x << std::endl

/*
Steps

1. This part is always the same:

    int lo = 0;
    int hi = data.size() - 1;
    while (hi >= lo) {
        int mid = (hi + lo) / 2;

2. Identify what we want to skip. For example, if we look for
   a number greater than some value, then we want to skip all
   numbers lower or equal than that value. 

   if (data[mid] <= value) {
       lo = mid + 1;
   }

3. Otherwise we change the other boundary

   else {
       hi = mid - 1;
   }

4. We return the boundary that is updated when we want to skip.
   Why? If lo == hi == mid, and they point to the value that
   should be skipped, then this boundary will be properly updated
   (lo in our example). On the other hand, if they point to correct value,
   boundary in the else statement will be updated (hi in this example),
   and we don't want to return it.

5. What appens in case of duplicates? Let's draw a line between what
    should be skipped and what. If we are looking for a number greater
    than 5:

    1 1 2 3 3 5 5 || 7 7 7
    
   Everything on the left hand side of the line will be skipped.
   The algorithm will always return a value that is closest to the
   line and is on the side that is not skipped. 


*/
int lower_or_equal(const std::vector<int>& data, int value) {
    int lo = 0;
    int hi = data.size() - 1;
    while (hi >= lo) {
        int mid = (hi + lo) / 2;
        if (data[mid] > value) {
            hi = mid - 1;
        }
        else {
            lo = mid + 1;
        }
    }
    return hi;
}

int lower(const std::vector<int>& data, int value) {
    int lo = 0;
    int hi = data.size() - 1;
    while (hi >= lo) {
        int mid = (hi + lo) / 2;
        if (data[mid] >= value) {
            hi = mid - 1;
        }
        else {
            lo = mid + 1;
        }
    }
    return hi;
}

int equal(const std::vector<int>& data, int value) {
    int lo = 0;
    int hi = data.size() - 1;
    while (hi >= lo) {
        int mid = (hi + lo) / 2;
        if (data[mid] == value) {
            return mid;
        }
        else if (data[mid] > value) {
            hi = mid - 1;
        }
        else {
            lo = mid + 1;
        }
    }
    return -1;
}

int greater_or_equal(const std::vector<int>& data, int value) {
    int lo = 0;
    int hi = data.size() - 1;
    while (hi >= lo) {
        int mid = (hi + lo) / 2;
        if (data[mid] < value) {
            lo = mid + 1;
        }
        else {
            hi = mid - 1;
        }
    }
    return lo;
}

int greater(const std::vector<int>& data, int value) {
    int lo = 0;
    int hi = data.size() - 1;
    while (hi >= lo) {
        int mid = (hi + lo) / 2;
        if (data[mid] <= value) {
            lo = mid + 1;
        }
        else {
            hi = mid - 1;
        }
    }
    return lo;
}

int rotated(const std::vector<int>& data) {
    int lo = 0;
    int hi = data.size() - 1;
    while (hi >= lo) {
        int mid = (hi + lo) / 2;
        if (data[mid] >= data.front()) {
            lo = mid + 1;
        }
        else {
            hi = mid -1;
        }
    }
    if (lo == static_cast<int>(data.size())) {
        return 0;
    }
    else {
        return lo;
    }
}

std::vector<int> unique{ 1, 3, 5, 10, 13 };
std::vector<int> duplicates{ 1, 1, 3, 3, 3, 5, 7, 7, 7 };

TEST(LowerEqual, Equal) {
    EXPECT_EQ(lower_or_equal(unique, 1), 0);
    EXPECT_EQ(lower_or_equal(unique, 3), 1);
    EXPECT_EQ(lower_or_equal(unique, 13), 4);
}

TEST(LowerEqual, Lower) {
    EXPECT_EQ(lower_or_equal(unique, 2), 0);
    EXPECT_EQ(lower_or_equal(unique, 4), 1);
    EXPECT_EQ(lower_or_equal(unique, 9), 2);
    EXPECT_EQ(lower_or_equal(unique, 11), 3);
    EXPECT_EQ(lower_or_equal(unique, 100), 4);
}

TEST(LowerEqual, Outside) {
    EXPECT_EQ(lower_or_equal(unique, -4), -1);
    EXPECT_EQ(lower_or_equal(duplicates, -4), -1);
}

TEST(LowerEqual, EqualDuplicates) {
    EXPECT_EQ(lower_or_equal(duplicates, 1), 1);
    EXPECT_EQ(lower_or_equal(duplicates, 3), 4);
    EXPECT_EQ(lower_or_equal(duplicates, 7), 8);
}

TEST(LowerEqual, LowerDuplicates) {
    EXPECT_EQ(lower_or_equal(duplicates, 2), 1);
    EXPECT_EQ(lower_or_equal(duplicates, 4), 4);
    EXPECT_EQ(lower_or_equal(duplicates, 9), 8);
}

TEST(Lower, Lower) {
    EXPECT_EQ(lower(unique, 2), 0);
    EXPECT_EQ(lower(unique, 3), 0);
    EXPECT_EQ(lower(unique, 4), 1);
    EXPECT_EQ(lower(unique, 5), 1);
    EXPECT_EQ(lower(unique, 9), 2);
    EXPECT_EQ(lower(unique, 100), 4);
}

TEST(Lower, LowerDuplicates) {
    EXPECT_EQ(lower(duplicates, 2), 1);
    EXPECT_EQ(lower(duplicates, 3), 1);
    EXPECT_EQ(lower(duplicates, 4), 4);
    EXPECT_EQ(lower(duplicates, 5), 4);
    EXPECT_EQ(lower(duplicates, 7), 5);
    EXPECT_EQ(lower(duplicates, 100), 8);
}

TEST(Lower, Outside) {
    EXPECT_EQ(lower(unique, 1), -1);
    EXPECT_EQ(lower(unique, 0), -1);
}

TEST(Equal, Exists) {
    EXPECT_EQ(equal(unique, 1), 0);
    EXPECT_EQ(equal(unique, 3), 1);
    EXPECT_EQ(equal(unique, 5), 2);
    EXPECT_EQ(equal(unique, 10), 3);
    EXPECT_EQ(equal(unique, 13), 4);
}

TEST(Equal, Missing) {
    EXPECT_EQ(equal(unique, -1), -1);
    EXPECT_EQ(equal(unique, 2), -1);
    EXPECT_EQ(equal(unique, 4), -1);
    EXPECT_EQ(equal(unique, 7), -1);
    EXPECT_EQ(equal(unique, 11), -1);
    EXPECT_EQ(equal(unique, 111), -1);
}

TEST(GreaterEqual, Equal) {
    EXPECT_EQ(greater_or_equal(unique, 1), 0);
    EXPECT_EQ(greater_or_equal(unique, 3), 1);
    EXPECT_EQ(greater_or_equal(unique, 10), 3);
    EXPECT_EQ(greater_or_equal(unique, 13), 4);
}

TEST(GreaterEqual, Greater) {
    EXPECT_EQ(greater_or_equal(unique, 0), 0);
    EXPECT_EQ(greater_or_equal(unique, 2), 1);
    EXPECT_EQ(greater_or_equal(unique, 4), 2);
    EXPECT_EQ(greater_or_equal(unique, 6), 3);
    EXPECT_EQ(greater_or_equal(unique, 11), 4);
}

TEST(GreaterEqual, EqualDuplicates) {
    EXPECT_EQ(greater_or_equal(duplicates, 1), 0);
    EXPECT_EQ(greater_or_equal(duplicates, 3), 2);
    EXPECT_EQ(greater_or_equal(duplicates, 7), 6);
}

TEST(GreaterEqual, GreaterDuplicates) {
    EXPECT_EQ(greater_or_equal(duplicates, 0), 0);
    EXPECT_EQ(greater_or_equal(duplicates, 2), 2);
    EXPECT_EQ(greater_or_equal(duplicates, 4), 5);
    EXPECT_EQ(greater_or_equal(duplicates, 6), 6);
}

TEST(GreaterEqual, Outside) {
    EXPECT_EQ(greater_or_equal(unique, 113), 5);
}

TEST(Greater, Greater) {
    EXPECT_EQ(greater(unique, -7), 0);
    EXPECT_EQ(greater(unique, 2), 1);
    EXPECT_EQ(greater(unique, 4), 2);
    EXPECT_EQ(greater(unique, 6), 3);
    EXPECT_EQ(greater(unique, 12), 4);
}

TEST(Greater, Outside) {
    EXPECT_EQ(greater(unique, 13), 5);
    EXPECT_EQ(greater(unique, 15), 5);
}

TEST(Greater, GreaterDuplicates) {
    EXPECT_EQ(greater(duplicates, 0), 0);
    EXPECT_EQ(greater(duplicates, 1), 2);
    EXPECT_EQ(greater(duplicates, 2), 2);
    EXPECT_EQ(greater(duplicates, 3), 5);
    EXPECT_EQ(greater(duplicates, 4), 5);
    EXPECT_EQ(greater(duplicates, 5), 6);
    EXPECT_EQ(greater(duplicates, 6), 6);
}

TEST(Range, LowerBound) {
    std::vector<int> unique{ 1, 3, 3, 3, 3, 7 };
    EXPECT_EQ(greater_or_equal(unique, 1), 0);
    EXPECT_EQ(greater_or_equal(unique, 2), 1);
    EXPECT_EQ(greater_or_equal(unique, 3), 1);
    EXPECT_EQ(greater_or_equal(unique, 4), 5);
    EXPECT_EQ(greater_or_equal(unique, 7), 5);
    EXPECT_EQ(greater_or_equal(unique, 9), 6);
}

TEST(Range, UpperBound) {
    std::vector<int> unique{ 1, 3, 3, 3, 3, 7 };
    EXPECT_EQ(lower_or_equal(unique, 0), -1);
    EXPECT_EQ(lower_or_equal(unique, 1), 0);
    EXPECT_EQ(lower_or_equal(unique, 2), 0);
    EXPECT_EQ(lower_or_equal(unique, 3), 4);
    EXPECT_EQ(lower_or_equal(unique, 4), 4);
    EXPECT_EQ(lower_or_equal(unique, 7), 5);
    EXPECT_EQ(lower_or_equal(unique, 9), 5);
}

TEST(Step, Step) {
    std::vector<int> step{ 0, 0, 0, 0, 1, 1, 1, 1 };
    EXPECT_EQ(lower(step, 1), 3);
    EXPECT_EQ(greater(step, 0), 4);
}

TEST(Rotated, Trivial) {
    std::vector<int> data{ 5, 7, 9, 0, 2, 4 };
    EXPECT_EQ(rotated(data), 3);
}

TEST(Rotated, Sorted) {
    std::vector<int> data{ -2, -1, 0, 2, 4 };
    EXPECT_EQ(rotated(data), 0);
}

TEST(Rotated, Last) {
    std::vector<int> data{ -2, -1, 0, 2, 4, -5 };
    EXPECT_EQ(rotated(data), 5);
}

TEST(Rotated, Single) {
    std::vector<int> data{ 0 };
    EXPECT_EQ(rotated(data), 0);
}

TEST(Rotated, Double) {
    std::vector<int> data{ 2, 1 };
    EXPECT_EQ(rotated(data), 1);
}
