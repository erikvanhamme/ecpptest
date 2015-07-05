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

#include "base.h"
#include "composite.h"
#include "countingallocator.h"
#include "derived.h"

#include "allocator.h"
#include "factory.h"

#include <memory>

TEST(FactoryTest, testMockups) {
    ecpp::mem::Allocator allocator;
    ecpp::mem::Factory factory(allocator);

    Registry &reg = Registry::getInstance();
    reg.reset();

    Base *base = new Base();
    delete(base);

    base = new Base(10);
    delete(base);

    base = new Base(10u);
    delete(base);

    ASSERT_EQ(1, reg.getHits("Base::Base()"));
    ASSERT_EQ(1, reg.getHits("Base::Base(int)"));
    ASSERT_EQ(1, reg.getHits("Base::Base(unsigned int)"));
    ASSERT_EQ(3, reg.getHits("Base::~Base()"));
    ASSERT_EQ(6, reg.getTotalHits());

    reg.reset();

    Composite *composite = new Composite(factory);
    delete(composite);

    ASSERT_EQ(1, reg.getHits("Base::Base(unsigned int)"));
    ASSERT_EQ(1, reg.getHits("Base::~Base()"));
    ASSERT_EQ(1, reg.getHits("Composite::Composite(Factory &)"));
    ASSERT_EQ(1, reg.getHits("Composite::~Composite()"));
    ASSERT_EQ(4, reg.getTotalHits());

    reg.reset();

    Derived *derived = new Derived(10u);
    delete(derived);

    ASSERT_EQ(1, reg.getHits("Base::Base(unsigned int)"));
    ASSERT_EQ(1, reg.getHits("Base::~Base()"));
    ASSERT_EQ(1, reg.getHits("Derived::Derived(unsigned int)"));
    ASSERT_EQ(1, reg.getHits("Derived::~Derived()"));
    ASSERT_EQ(4, reg.getTotalHits());

    reg.reset();

    ASSERT_EQ(0, reg.getHits("Certainly non-existing string"));
    ASSERT_EQ(0, reg.getTotalHits());

    CountingAllocator *pCountingAllocator = new CountingAllocator();
    delete (pCountingAllocator);
}

TEST(FactoryTest, testCreate) {
    ecpp::mem::Allocator allocator;
    ecpp::mem::Factory factory(allocator);

    Registry &reg = Registry::getInstance();
    reg.reset();

    {
        auto ptr = factory.create<Base>();

        ASSERT_NE(nullptr, ptr.get());

        ASSERT_EQ(1, reg.getHits("Base::Base()"));
        ASSERT_EQ(1, reg.getTotalHits());

        reg.reset();
    }

    ASSERT_EQ(1, reg.getHits("Base::~Base()"));
    ASSERT_EQ(1, reg.getTotalHits());

    reg.reset();

    {
        auto ptr = factory.create<Base>(10);

        ASSERT_NE(nullptr, ptr.get());

        ASSERT_EQ(1, reg.getHits("Base::Base(int)"));
        ASSERT_EQ(1, reg.getTotalHits());

        reg.reset();
    }

    ASSERT_EQ(1, reg.getHits("Base::~Base()"));
    ASSERT_EQ(1, reg.getTotalHits());

    reg.reset();

    {
        auto ptr = factory.create<Base>(10u);

        ASSERT_NE(nullptr, ptr.get());

        ASSERT_EQ(1, reg.getHits("Base::Base(unsigned int)"));
        ASSERT_EQ(1, reg.getTotalHits());

        reg.reset();
    }

    ASSERT_EQ(1, reg.getHits("Base::~Base()"));
    ASSERT_EQ(1, reg.getTotalHits());

    reg.reset();

    {
        auto ptr = factory.create<Composite, ecpp::mem::Factory &>(factory);

        ASSERT_NE(nullptr, ptr.get());

        ASSERT_EQ(1, reg.getHits("Base::Base(unsigned int)"));
        ASSERT_EQ(1, reg.getHits("Composite::Composite(Factory &)"));
        ASSERT_EQ(2, reg.getTotalHits());

        reg.reset();
    }

    ASSERT_EQ(1, reg.getHits("Base::~Base()"));
    ASSERT_EQ(1, reg.getHits("Composite::~Composite()"));
    ASSERT_EQ(2, reg.getTotalHits());

    reg.reset();

    {
        auto ptr = factory.create<Derived>(10u);

        ASSERT_NE(nullptr, ptr.get());

        ASSERT_EQ(1, reg.getHits("Base::Base(unsigned int)"));
        ASSERT_EQ(1, reg.getHits("Derived::Derived(unsigned int)"));
        ASSERT_EQ(2, reg.getTotalHits());

        reg.reset();
    }

    ASSERT_EQ(1, reg.getHits("Base::~Base()"));
    ASSERT_EQ(1, reg.getHits("Derived::~Derived()"));
    ASSERT_EQ(2, reg.getTotalHits());

    reg.reset();
}

TEST(FactoryTest, testCreateArray) {
    CountingAllocator allocator;
    ecpp::mem::Factory factory(allocator);

    Registry &reg = Registry::getInstance();
    reg.reset();

    {
        auto pShorts = factory.createArray<short>(4);

        ASSERT_NE(nullptr, pShorts.get());

        ASSERT_EQ(1, allocator.getAllocations());
        ASSERT_EQ(0, allocator.getDeallocations());
        ASSERT_EQ(8, allocator.getAllocatedSize());

        allocator.reset();

        ASSERT_EQ(0, reg.getTotalHits());

        reg.reset();
    }

    ASSERT_EQ(0, reg.getTotalHits());

    ASSERT_EQ(0, allocator.getAllocations());
    ASSERT_EQ(1, allocator.getDeallocations());
    ASSERT_EQ(0, allocator.getAllocatedSize());

    allocator.reset();

    {
        auto pBase = factory.createArray<Base>(2);

        ASSERT_NE(nullptr, pBase.get());

        ASSERT_EQ(1, allocator.getAllocations());
        ASSERT_EQ(0, allocator.getDeallocations());
        ASSERT_EQ(sizeof(Base) * 2, allocator.getAllocatedSize());

        allocator.reset();

        ASSERT_EQ(2, reg.getHits("Base::Base()"));
        ASSERT_EQ(2, reg.getTotalHits());

        reg.reset();
    }

    ASSERT_EQ(2, reg.getHits("Base::~Base()"));
    ASSERT_EQ(2, reg.getTotalHits());

    ASSERT_EQ(0, allocator.getAllocations());
    ASSERT_EQ(1, allocator.getDeallocations());
    ASSERT_EQ(0, allocator.getAllocatedSize());
}
