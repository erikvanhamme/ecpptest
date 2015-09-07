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

#include <cstddef>

TEST(AllocatorTest, testCtorDtor) {
    ecpp::Allocator *allocator = new ecpp::Allocator();
    ASSERT_NE(nullptr, allocator);

    delete(allocator);
}

TEST(AllocatorTest, testAllocateDeallocate) {
    ecpp::Allocator allocator;

    allocator.deallocate(nullptr);

    int *pInt = static_cast<int *>(allocator.allocate(sizeof(int)));
    ASSERT_NE(nullptr, pInt);

    allocator.deallocate(pInt);

    float *pFloat = static_cast<float *>(allocator.allocate(sizeof(float) * 4));
    ASSERT_NE(nullptr, pFloat);

    allocator.deallocate(pFloat);
}
