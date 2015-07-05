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

#include "byteutils.h"

TEST(ByteUtilsTest, testByteSwapGeneric) {

    struct S {
        S() : a(0x00), b(0x11), c(0x22), d(0x33) {
        }

        uint8_t a;
        uint8_t b;
        uint8_t c;
        uint8_t d;
    };

    S s;

    ecpp::util::byteSwap(s);

    ASSERT_EQ(0x33, s.a);
    ASSERT_EQ(0x22, s.b);
    ASSERT_EQ(0x11, s.c);
    ASSERT_EQ(0x00, s.d);
}

TEST(ByteUtilsTest, testByteSwapUint8_t) {
    uint8_t c = 0xa5;

    ecpp::util::byteSwap(c);

    ASSERT_EQ(0xa5, c);
}

TEST(ByteUtilsTest, testByteSwapInt8_t) {
    int8_t c = 0x5a;

    ecpp::util::byteSwap(c);

    ASSERT_EQ(0x5a, c);
}

TEST(ByteUtilsTest, testByteSwapUint16_t) {
    uint16_t s = 0x0011;

    ecpp::util::byteSwap(s);

    ASSERT_EQ(0x1100, s);
}

TEST(ByteUtilsTest, testByteSwapInt16_t) {
    int16_t s = 0x0011;

    ecpp::util::byteSwap(s);

    ASSERT_EQ(0x1100, s);
}

TEST(ByteUtilsTest, testByteSwapUint32_t) {
    uint32_t w = 0x00112233;

    ecpp::util::byteSwap(w);

    ASSERT_EQ(0x33221100, w);
}

TEST(ByteUtilsTest, testByteSwapInt32_t) {
    int32_t w = 0x00112233;

    ecpp::util::byteSwap(w);

    ASSERT_EQ(0x33221100, w);
}

TEST(ByteUtilsTest, testByteSwapUint64_t) {
    uint64_t dw = 0x0011223344556677;

    ecpp::util::byteSwap(dw);

    ASSERT_EQ(0x7766554433221100, dw);
}

TEST(ByteUtilsTest, testByteSwapInt64_t) {
    int64_t dw = 0x0011223344556677;

    ecpp::util::byteSwap(dw);

    ASSERT_EQ(0x7766554433221100, dw);
}
