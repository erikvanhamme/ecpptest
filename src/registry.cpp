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

#include "registry.h"

#include <map>
#include <string>

Registry &Registry::getInstance() {
    static Registry instance;
    return instance;
}

void Registry::hit(std::string s) {
    auto search = _hits.find(s);
    if (search != _hits.end()) {
        search->second = search->second + 1;
    } else {
        _hits.insert(std::make_pair(s, 1));
    }
    ++_totalHits;
}

int Registry::getHits(std::string s) const {
    auto search = _hits.find(s);
    if (search != _hits.end()) {
        return search->second;
    } else {
        return 0;
    }
}

int Registry::getTotalHits() const {
    return _totalHits;
}

void Registry::reset() {
    _hits.clear();
    _totalHits = 0;
}

Registry::Registry() {
    reset();
}
