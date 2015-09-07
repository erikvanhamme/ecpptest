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

#ifndef COMPOSITE_H
#define COMPOSITE_H

#include "base.h"
#include "registry.h"

#include "factory.h"

#include <memory>

class Composite {
public:
    Composite(ecpp::Factory &factory) {
        pBase = factory.create<Base>(7u);
        Registry::getInstance().hit("Composite::Composite(Factory &)");
    }

    virtual ~Composite() {
        Registry::getInstance().hit("Composite::~Composite()");
    }

private:
    std::shared_ptr<Base> pBase;
};

#endif // COMPOSITE_H
