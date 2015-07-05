
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

#include "fraction.h"
#include "pid.h"

#include <iostream>

typedef ecpp::control::Pid<int, int, float> float_pid_t;

typedef ecpp::control::Pid<int, int, ecpp::util::Fraction<int, int>> fraction_pid_t;

TEST(PidDemo, runDemo) {

    /*
    struct Config {
        Tsignal setPoint;
        Tcfg p;
        Tcfg i;
        Tcfg d;
        ecpp::util::Range<Tout> outRange;
        ecpp::util::Range<Tout> pRange;
        ecpp::util::Range<Tout> iRange;
        ecpp::util::Range<Tout> dRange;
    };
    */

    float_pid_t::Config pidCfgFloat = {
        6600, // in mA 6.6A
        0.3f,
        2.7f,
        0.2f,
        {0, 50000}, // in mV 50V
        {-10000, 10000},
        {-50000, 50000},
        {-10000, 10000}
    };

    fraction_pid_t::Config pidCfgFraction = {
        6600,
        {3, 10},
        {37, 10},
        {2, 10},
        {0, 50000},
        {-10000, 10000},
        {-50000, 50000},
        {-10000, 10000}
    };

    float_pid_t pidFloat(pidCfgFloat);
    fraction_pid_t pidFraction(pidCfgFraction);

    int resistance = 5; // 5 ohms
    int voltage1 = 0; // voltage
    int voltage2 = 0; // voltage

    for (int i = 0; i < 50; ++i) {

        if (i == 15) {
            resistance = 3;
        }

        if (i == 30) {
            resistance = 7;
        }

        int current1 = voltage1 / resistance; // Ohm's law
        int current2 = voltage2 / resistance; // Ohm's law

        pidFloat.update(current1);
        voltage1 = pidFloat.output();

        pidFraction.update(current2);
        voltage2 = pidFloat.output();

        std::cout << voltage1 << ", " << current1 << ", " << voltage2 << ", " << current2 << std::endl;
    }
}
