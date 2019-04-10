/*
 *
 *
 * Author: Rafal Kozik
 */

#include <bits/stdc++.h>
#include <gtest/gtest.h>

#define LOG(x) std::cout << x << std::endl

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

std::vector<int> data{ 1, 3, 5, 10, 13 };

TEST(LowerEqual, Equal) {
    EXPECT_EQ(lower_or_equal(data, 1), 0);
    EXPECT_EQ(lower_or_equal(data, 3), 1);
    EXPECT_EQ(lower_or_equal(data, 13), 4);
}

TEST(LowerEqual, Lower) {
    EXPECT_EQ(lower_or_equal(data, 2), 0);
    EXPECT_EQ(lower_or_equal(data, 4), 1);
    EXPECT_EQ(lower_or_equal(data, 9), 2);
    EXPECT_EQ(lower_or_equal(data, 11), 3);
    EXPECT_EQ(lower_or_equal(data, 100), 4);
}

TEST(LowerEqual, Outside) {
    EXPECT_EQ(lower_or_equal(data, -4), -1);
}

TEST(Lower, Lower) {
    EXPECT_EQ(lower(data, 2), 0);
    EXPECT_EQ(lower(data, 3), 0);
    EXPECT_EQ(lower(data, 4), 1);
    EXPECT_EQ(lower(data, 5), 1);
    EXPECT_EQ(lower(data, 9), 2);
    EXPECT_EQ(lower(data, 100), 4);
}

TEST(Lower, Outside) {
    EXPECT_EQ(lower(data, 1), -1);
    EXPECT_EQ(lower(data, 0), -1);
}

TEST(Equal, Exists) {
    EXPECT_EQ(equal(data, 1), 0);
    EXPECT_EQ(equal(data, 3), 1);
    EXPECT_EQ(equal(data, 5), 2);
    EXPECT_EQ(equal(data, 10), 3);
    EXPECT_EQ(equal(data, 13), 4);
}

TEST(Equal, Missing) {
    EXPECT_EQ(equal(data, -1), -1);
    EXPECT_EQ(equal(data, 2), -1);
    EXPECT_EQ(equal(data, 4), -1);
    EXPECT_EQ(equal(data, 7), -1);
    EXPECT_EQ(equal(data, 11), -1);
    EXPECT_EQ(equal(data, 111), -1);
}

TEST(GreaterEqual, Equal) {
    EXPECT_EQ(greater_or_equal(data, 1), 0);
    EXPECT_EQ(greater_or_equal(data, 3), 1);
    EXPECT_EQ(greater_or_equal(data, 10), 3);
    EXPECT_EQ(greater_or_equal(data, 13), 4);
}

TEST(GreaterEqual, Greater) {
    EXPECT_EQ(greater_or_equal(data, 0), 0);
    EXPECT_EQ(greater_or_equal(data, 2), 1);
    EXPECT_EQ(greater_or_equal(data, 4), 2);
    EXPECT_EQ(greater_or_equal(data, 6), 3);
    EXPECT_EQ(greater_or_equal(data, 11), 4);
}

TEST(GreaterEqual, Outside) {
    EXPECT_EQ(greater_or_equal(data, 113), 5);
}

TEST(Greater, Greater) {
    EXPECT_EQ(greater(data, -7), 0);
    EXPECT_EQ(greater(data, 2), 1);
    EXPECT_EQ(greater(data, 4), 2);
    EXPECT_EQ(greater(data, 6), 3);
    EXPECT_EQ(greater(data, 12), 4);
}

TEST(Greater, Outside) {
    EXPECT_EQ(greater(data, 13), 5);
    EXPECT_EQ(greater(data, 15), 5);
}

TEST(LowerBound, LowerBound) {
    std::vector<int> data{ 1, 3, 3, 3, 3, 7 };
    EXPECT_EQ(greater_or_equal(data, 1), 0);
    EXPECT_EQ(greater_or_equal(data, 2), 1);
    EXPECT_EQ(greater_or_equal(data, 3), 1);
    EXPECT_EQ(greater_or_equal(data, 4), 5);
    EXPECT_EQ(greater_or_equal(data, 7), 5);
    EXPECT_EQ(greater_or_equal(data, 9), 6);
}

TEST(UpperBound, UpperBound) {
    std::vector<int> data{ 1, 3, 3, 3, 3, 7 };
    EXPECT_EQ(lower_or_equal(data, 0), -1);
    EXPECT_EQ(lower_or_equal(data, 1), 0);
    EXPECT_EQ(lower_or_equal(data, 2), 0);
    EXPECT_EQ(lower_or_equal(data, 3), 4);
    EXPECT_EQ(lower_or_equal(data, 4), 4);
    EXPECT_EQ(lower_or_equal(data, 7), 5);
    EXPECT_EQ(lower_or_equal(data, 9), 5);
}

