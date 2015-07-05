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

#ifndef COUNTINGALLOCATOR_H
#define COUNTINGALLOCATOR_H

#include "allocator.h"

#include <cstddef>

class CountingAllocator : public ecpp::mem::Allocator {
public:
    CountingAllocator() : Allocator() {
        reset();
    }

    virtual ~CountingAllocator() {
    }

    void reset() {
        _allocations = 0;
        _deallocations = 0;
        _allocatedSize = 0;
    }

    int getAllocations() const {
        return _allocations;
    }

    int getDeallocations() const {
        return _deallocations;
    }

    std::size_t getAllocatedSize() const {
        return _allocatedSize;
    }

    virtual void *allocate(std::size_t size) override {
        ++_allocations;
        _allocatedSize += size;
        return Allocator::allocate(size);
    }

    virtual void deallocate(void *address) override {
        ++_deallocations;
        Allocator::deallocate(address);
    }

private:
    int _allocations;
    int _deallocations;
    std::size_t _allocatedSize;
};

#endif // COUNTINGALLOCATOR_H
