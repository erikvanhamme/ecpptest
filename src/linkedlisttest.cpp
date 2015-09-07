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

#include "allocator.h"
#include "countingallocator.h"
#include "linkedlist.h"

TEST(LinkedListTest, testConstructor) {
    CountingAllocator allocator;
    ecpp::LinkedList<int> list(allocator);

    ASSERT_EQ(0, list.size());
    ASSERT_EQ(0, allocator.getAllocations());
}

TEST(LinkedListTest, emptyListBehavior) {

    CountingAllocator allocator;
    ecpp::LinkedList<int> list(allocator);

    ASSERT_EQ(0, list.size());

    ASSERT_EQ(0, allocator.getAllocations());

    auto b = list.begin();
    auto e = list.end();

    ASSERT_EQ(0, *b);
    ASSERT_EQ(0, *e);

    ASSERT_FALSE(b != e);

    for (auto i: list) {
        ASSERT_FALSE(true);
    }

    const auto constList = list;

    auto cb = constList.begin();
    auto ce = constList.end();

    ASSERT_EQ(0, *cb);
    ASSERT_EQ(0, *ce);

    ASSERT_FALSE(cb != ce);

    for (auto i: constList) {
        ASSERT_FALSE(true);
    }
}

TEST(LinkedListTest, testAppend) {

    CountingAllocator allocator;
    ecpp::LinkedList<int> list(allocator);

    ASSERT_TRUE(list.append(1));
    ASSERT_TRUE(list.append(2));
    ASSERT_TRUE(list.append(3));

    ASSERT_EQ(3, list.size());
    ASSERT_EQ(3, allocator.getAllocations());

    const auto constList = list;

    int i = 1;
    for (const int value: constList) {
        ASSERT_EQ(i, value);
        ++i;
    }
}

TEST(LinkedListTest, testPrepend) {

    CountingAllocator allocator;
    ecpp::LinkedList<int> list(allocator);

    ASSERT_TRUE(list.prepend(1));
    ASSERT_TRUE(list.prepend(2));
    ASSERT_TRUE(list.prepend(3));

    ASSERT_EQ(3, list.size());
    ASSERT_EQ(3, allocator.getAllocations());

    const auto constList = list;

    int i = 3;
    for (const int value: constList) {
        ASSERT_EQ(i, value);
        --i;
    }
}

TEST(LinkedListTest, testConstIteration) {

    ecpp::Allocator allocator;
    ecpp::LinkedList<int> list(allocator);

    for (int i = 0; i < 3; ++i) {
        list.append(i);
    }

    const auto constList = list;

    int i = 0;
    for (int value: constList) {
        ASSERT_EQ(i, value);
        ++i;
    }

    auto it = constList.begin();

    ++it;
    ASSERT_EQ(1, *it);

    ++it;
    ASSERT_EQ(2, *it);

    ++it;
    ASSERT_EQ(0, *it);

    it = constList.end();

    --it;
    ASSERT_EQ(1, *it);

    --it;
    ASSERT_EQ(0, *it);

    --it;
    ASSERT_EQ(0, *it);
}

TEST(LinkedListTest, testIteration) {

    ecpp::Allocator allocator;
    ecpp::LinkedList<int> list(allocator);

    for (int i = 0; i < 3; ++i) {
        list.append(i);
    }

    int i = 0;
    for (int value: list) {
        ASSERT_EQ(i, value);
        ++i;
    }

    auto it = list.begin();

    ++it;
    ASSERT_EQ(1, *it);

    ++it;
    ASSERT_EQ(2, *it);

    ++it;
    ASSERT_EQ(0, *it);

    auto it2 = list.end();

    --it2;
    ASSERT_EQ(1, *it2);

    --it2;
    ASSERT_EQ(0, *it2);

    --it2;
    ASSERT_EQ(0, *it2);
}

TEST(LinkedListTest, testAt) {

    ecpp::Allocator allocator;
    ecpp::LinkedList<int> list(allocator);

    for (int i = 0; i < 3; ++i) {
        list.append(i);
    }

    for (int i = 0; i < 3; ++i) {
        ASSERT_EQ(i, list.at(i));
    }

    ASSERT_EQ(0, list.at(list.size()));
    ASSERT_EQ(0, list.at(list.size() + 1));
}

TEST(LinkedListTest, testPointerContent) {

    ecpp::Allocator allocator;
    ecpp::LinkedList<int *> list(allocator);

    int a = 1;
    int b = 2;
    int c = 3;

    list.append(&a);
    list.append(&b);
    list.append(&c);

    ASSERT_EQ(3, list.size());

    auto it = list.begin();

    ASSERT_EQ(1, **it);

    ++it;

    ASSERT_EQ(2, **it);

    ++it;

    ASSERT_EQ(3, **it);

    ++it;

    ASSERT_EQ(nullptr, *it);

    auto end = list.end();

    ASSERT_EQ(3, **end);

    ++end;

    ASSERT_EQ(nullptr, *end);
}

TEST(LinkedListTest, testInsertAfter) {

    ecpp::Allocator allocator;

    // test insert after to empty list with begin() iterator
    ecpp::LinkedList<int> list1(allocator);
    auto i1 = list1.begin();
    ASSERT_TRUE(i1.insertAfter(1));
    ASSERT_EQ(1, list1.size());
    ASSERT_EQ(1, *i1);

    // test insert after to non-empty list
    ASSERT_TRUE(i1.insertAfter(2));
    ASSERT_EQ(2, list1.size());
    ASSERT_EQ(2, *i1);
    ASSERT_TRUE(i1.insertAfter(3));
    ASSERT_EQ(3, list1.size());
    ASSERT_EQ(3, *i1);

    // verify ordering
    int i = 1;
    for(int value: list1) {
        ASSERT_EQ(i, value);
        ++i;
    }

    // test insert after to empty list with end() iterator
    ecpp::LinkedList<int> list2(allocator);
    auto i2 = list2.end();
    ASSERT_TRUE(i2.insertAfter(1));
    ASSERT_EQ(1, list2.size());
    ASSERT_EQ(1, *i2);

    // test insert after to non-empty list
    ASSERT_TRUE(i2.insertAfter(2));
    ASSERT_EQ(2, list2.size());
    ASSERT_EQ(2, *i2);
    ASSERT_TRUE(i2.insertAfter(3));
    ASSERT_EQ(3, list2.size());
    ASSERT_EQ(3, *i2);

    // verify ordering
    i = 1;
    for(int value: list2) {
        ASSERT_EQ(i, value);
        ++i;
    }
}

TEST(LinkedListTest, testInsertBefore) {

    ecpp::Allocator allocator;

    // test insert before to empty list with begin() iterator
    ecpp::LinkedList<int> list1(allocator);
    auto i1 = list1.begin();
    ASSERT_TRUE(i1.insertBefore(1));
    ASSERT_EQ(1, list1.size());
    ASSERT_EQ(1, *i1);

    // test insert after to non-empty list
    ASSERT_TRUE(i1.insertBefore(2));
    ASSERT_EQ(2, list1.size());
    ASSERT_EQ(2, *i1);
    ASSERT_TRUE(i1.insertBefore(3));
    ASSERT_EQ(3, list1.size());
    ASSERT_EQ(3, *i1);

    // verify ordering
    int i = 3;
    for(int value: list1) {
        ASSERT_EQ(i, value);
        --i;
    }

    // test insert before to empty list with end() iterator
    ecpp::LinkedList<int> list2(allocator);
    auto i2 = list2.end();
    ASSERT_TRUE(i2.insertBefore(1));
    ASSERT_EQ(1, list2.size());
    ASSERT_EQ(1, *i2);

    // test insert after to non-empty list
    ASSERT_TRUE(i2.insertBefore(2));
    ASSERT_EQ(2, list2.size());
    ASSERT_EQ(2, *i2);
    ASSERT_TRUE(i2.insertBefore(3));
    ASSERT_EQ(3, list2.size());
    ASSERT_EQ(3, *i2);

    // verify ordering
    i = 3;
    for(int value: list2) {
        ASSERT_EQ(i, value);
        --i;
    }
}

TEST(LinkedListTest, testRemove) {

    CountingAllocator allocator;
    ecpp::LinkedList<int> list(allocator);

    ASSERT_TRUE(list.append(1));
    ASSERT_TRUE(list.append(2));
    ASSERT_TRUE(list.append(3));
    ASSERT_TRUE(list.append(4));
    ASSERT_TRUE(list.append(5));

    ASSERT_EQ(5, list.size());
    ASSERT_EQ(5, allocator.getAllocations());

    // Test delete from the middle.

    auto it1 = list.begin();
    ++it1;
    ++it1;

    ASSERT_EQ(3, *it1);

    it1.remove();

    ASSERT_EQ(4, *it1); // Should have moved to next item.

    ASSERT_EQ(4, list.size());
    ASSERT_EQ(5, allocator.getAllocations());
    ASSERT_EQ(1, allocator.getDeallocations());

    ASSERT_EQ(1, list.at(0));
    ASSERT_EQ(2, list.at(1));
    ASSERT_EQ(4, list.at(2));
    ASSERT_EQ(5, list.at(3));

    // Test delete from the beginning.
    auto it2 = list.begin();

    ASSERT_EQ(1, *it2);

    it2.remove();

    ASSERT_EQ(2, *it2); // Should have moved to next item.

    ASSERT_EQ(3, list.size());
    ASSERT_EQ(5, allocator.getAllocations());
    ASSERT_EQ(2, allocator.getDeallocations());

    ASSERT_EQ(2, list.at(0));
    ASSERT_EQ(4, list.at(1));
    ASSERT_EQ(5, list.at(2));

    // Test delete from the end.

    auto it3 = list.end();

    ASSERT_EQ(5, *it3);

    it3.remove();

    ASSERT_EQ(0, *it3); // Should have moved to next item, which is nullptr and invalid, hence 0.

    ASSERT_EQ(2, list.size());
    ASSERT_EQ(5, allocator.getAllocations());
    ASSERT_EQ(3, allocator.getDeallocations());

    ASSERT_EQ(2, list.at(0));
    ASSERT_EQ(4, list.at(1));
}

TEST(LinkedListTest, testClear) {

    CountingAllocator allocator;
    ecpp::LinkedList<int> list(allocator);

    ASSERT_TRUE(list.append(1));
    ASSERT_TRUE(list.append(2));
    ASSERT_TRUE(list.append(3));
    ASSERT_TRUE(list.append(4));
    ASSERT_TRUE(list.append(5));

    ASSERT_EQ(5, list.size());
    ASSERT_EQ(5, allocator.getAllocations());

    list.clear();

    ASSERT_EQ(0, list.size());
    ASSERT_EQ(5, allocator.getAllocations());
    ASSERT_EQ(5, allocator.getDeallocations());
}
