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

#ifndef BASE_H
#define BASE_H

#include "registry.h"

class Base {
public:
    Base() {
        Registry::getInstance().hit("Base::Base()");
    }

    Base(int i) {
        (void) i;
        Registry::getInstance().hit("Base::Base(int)");
    }

    Base(unsigned int u) {
        (void) u;
        Registry::getInstance().hit("Base::Base(unsigned int)");
    }

    virtual ~Base() {
        Registry::getInstance().hit("Base::~Base()");
    }
};

#endif // BASE_H
