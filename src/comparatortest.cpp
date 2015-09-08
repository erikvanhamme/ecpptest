/*
 * Copyright 2015 Erik Van Hamme
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "gtest/gtest.h"

#include "comparator.h"

TEST(ComparatorTest, testLessThanSame) {
    ecpp::Comparator<int> &comp = ecpp::LessThanComparator<int>::getInstance();

    ASSERT_GT(comp.compare(1, 2), 0);
    ASSERT_LT(comp.compare(2, 1), 0);
    ASSERT_EQ(0, comp.compare(1, 1));
}

TEST(ComparatorTest, testLessThanDifferent) {
    ecpp::Comparator<int, float> &comp = ecpp::LessThanComparator<int, float>::getInstance();

    ASSERT_GT(comp.compare(1, 2.0f), 0);
    ASSERT_LT(comp.compare(2, 1.0f), 0);
    ASSERT_EQ(0, comp.compare(1, 1.0f));
}

TEST(ComparatorTest, testGreaterThanSame) {
    ecpp::Comparator<int> &comp = ecpp::GreaterThanComparator<int>::getInstance();

    ASSERT_LT(comp.compare(1, 2), 0);
    ASSERT_GT(comp.compare(2, 1), 0);
    ASSERT_EQ(0, comp.compare(1, 1));
}

TEST(ComparatorTest, testGreaterThanDifferent) {
    ecpp::Comparator<int, float> &comp = ecpp::GreaterThanComparator<int, float>::getInstance();

    ASSERT_LT(comp.compare(1, 2.0f), 0);
    ASSERT_GT(comp.compare(2, 1.0f), 0);
    ASSERT_EQ(0, comp.compare(1, 1.0f));
}
