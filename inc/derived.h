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

#ifndef DERIVED_H
#define DERIVED_H

#include "base.h"
#include "registry.h"

class Derived : public Base {
public:
    Derived(unsigned int i) : Base(i) {
        Registry::getInstance().hit("Derived::Derived(unsigned int)");
    }

    virtual ~Derived() {
        Registry::getInstance().hit("Derived::~Derived()");
    }
};

#endif // DERIVED_H
